open Batteries
open Printf
open Pdbm
open Uta
open TimedAutomaton

module type CPABSTRACTION =
sig
  type t = ClassicDBMAlgebra.t Batteries.DynArray.t array array
  val empty_abstraction : 'a array
  val init_syntax : Uta.system -> ClassicDBMAlgebra.t Batteries.DynArray.t array array
  val init_empty : Uta.system ->  ClassicDBMAlgebra.t Batteries.DynArray.t array array
  val init_complete : Uta.system ->  ClassicDBMAlgebra.t Batteries.DynArray.t array array
  val over_approximate :
    'a Batteries.DynArray.t array array -> int -> int -> 'a -> 'a option
  val over_approximate_udbm :
    ClassicDBMAlgebra.t Batteries.DynArray.t array array ->
    Guard.t -> Guard.t
  val under_approximate :
    'a Batteries.DynArray.t array array -> int -> int -> 'a -> 'a option
  val add_predicate :
    'a Batteries.DynArray.t array array -> int * int -> 'a -> unit
  val print : Uta.system -> ClassicDBMAlgebra.t Batteries.DynArray.t array array -> unit
  val to_string : Uta.system -> ClassicDBMAlgebra.t Batteries.DynArray.t array array -> string
  val size : t -> int
  val refine_separate : t -> ClassicDBM.t -> ClassicDBM.t -> unit
  val refine_empty : t -> ClassicDBM.clock_constraint list -> unit
end

(**
   This module implements the quantization abstraction for clock constraints.
   Given a table t, where each component t.(x).(y), for clocks x,y, contains
   an array of values k, the abstraction consists in considering the domain
   of zones which can be written with constraints x-y<k or x-y<=k with
   k in t.(x).(y).
*)
module ClockPredicateAbstraction  =
  struct
    (** For each pair (x,y), the abstraction is induced by a table (dynarray)
       of constants k which define the predicates 'x-y<k' or 'x-y<=k'.
        The type elt is customizable so to we allow storing:
        - only arrays of constants (of type bound_t = int)
        - arrays of raw_t = bound_t * inequality_t
        Beware: !These values are sorted using the generic compare function!
    *)
    type t = (ClassicDBMAlgebra.t DynArray.t) array array

    let empty_abstraction = [||]


    let init_empty ta =
      let nb_clocks = Uautomaton.nb_clocks ta in
      Array.init (nb_clocks+1)
          (fun x -> Array.init (nb_clocks+1) (fun y -> DynArray.create()))


    let over_approximate abs x y b =
      let vect = abs.(x).(y) in
      let rec aux = function
        | (l,r) when r = l -> DynArray.get vect l
        | (l,r) when r = l + 1 ->
          if (DynArray.get vect l) < b then DynArray.get vect r
          else DynArray.get vect l
        | (l,r) ->
          let m = (r + l) /2 in
          if (DynArray.get vect m) = b then 
            b
          else (
            if (DynArray.get vect m) < b then
              (aux (m,r))
            else (aux (l,m))
          )
      in
      let n = DynArray.length vect in
      if n = 0 then None
      else if b <= (DynArray.get vect 0) then 
        Some(DynArray.get vect 0)
      else if b > (DynArray.get vect (n-1)) then
        None
      else Some(aux (0,n-1))


    let under_approximate abs x y b =
      let vect = abs.(x).(y) in
      (* Invariant vect(l) < b <= vect(r) *)
      let rec aux = function
        | (l,r) when r = l -> DynArray.get vect l
        | (l,r) when r = l + 1 ->
          if (DynArray.get vect r) = b then DynArray.get vect r
          else DynArray.get vect l
        | (l,r) ->
          let m = (r + l) /2 in
          if (DynArray.get vect m) = b then 
            b
          else (
            if (DynArray.get vect m) < b then
              (aux (m,r))
            else (aux (l,m))
          )
      in
      let n = DynArray.length vect in
      if n = 0 then None
      else if b < (DynArray.get vect 0) then
        None
      else if b = (DynArray.get vect 0) then
        Some (DynArray.get vect 0)
      else if b > (DynArray.get vect (n-1)) then
        Some (DynArray.get vect (n-1))
      else Some(aux (0,n-1))

    (** Add predicate x-y<b in the abstraction *)
    let add_predicate abs (x,y) b =
      let values = abs.(x).(y) in
      (* We add the constant b while conserving sortedness with bsearch *)
      (* Return greatest pos such that values.(pos) is <= than b.
         @pre abs.(l) <= b <= abs.(r)
      *)
      let rec find_pos = function
        (* invariant: abs.(l) <= b <= abs.(r) *)
        | (l,r) when r - l > 1 ->
              let m = (r + l) /2 in
              if (DynArray.get values m) = b then m
              else (
                if (DynArray.get values m) < b then
                  (find_pos (m,r))
                else (find_pos (l,m))
              )
        | (l,r) when r - l = 1 ->
          if (DynArray.get values r) <= b then r else l
        | (l,r) -> 
          (* it remains the case l=r and by the invariant, we must have values.(l) <= b <= values.(l) *)
          l
      in
      let nvalues = DynArray.length values in
      if nvalues = 0 || b < (DynArray.get values 0) then(
        DynArray.insert values 0 b
      ) else if b > (DynArray.get values (nvalues-1)) then(
        DynArray.insert values nvalues b
      ) else (
        let pos = (find_pos (0,nvalues-1)) in
        if (DynArray.get values pos) < b then(
          DynArray.insert values (pos+1) b
        )
      )


    (** Make predicates of the form x-y<=k and x-y<k
        with all possible constants up to max bound per clock.
        This renders the abstraction precise.
    let init_complete bta =
      let abs = init_empty bta in
      let bounds = TA.guard_and_invar_constants bta in
      let nbclocks = TA.nb_clocks bta in
      (* Add rectangular *)
      for x = 0 to nbclocks do
        for y = 0 to nbclocks do
          if x <> 0 && x <> y then (
            let (maxb,_) = Array.max bounds.(x).(0) in
            for k = 0 to maxb do
              ignore(refine abs (x,y) (k,DBM_STRICT));
              ignore(refine abs (x,y) (k,DBM_WEAK))
            done
          )
        done;
        (* lower bounds *)
        if x <> 0 then (
          let(minb,_) = Array.min bounds.(0).(x) in
          for k = minb to 0 do
            ignore(refine abs (0,x) (k, DBM_STRICT));
            ignore(refine abs (0,x) (k, DBM_WEAK));
          done
        )
      done;
      abs
    *)

    let print bta abs =
      let dim = Uautomaton.nb_clocks bta in
      printf "Printing abstraction\n";
      for x = 0 to dim do
        for y = 0 to dim do
          if (DynArray.length abs.(x).(y)) > 0 then(
            printf "Predicates(%d, %d): " x y;
            for i = 0 to (DynArray.length abs.(x).(y)) - 1 do
              printf "%s " (ClassicDBMAlgebra.to_string (DynArray.get abs.(x).(y) i))
            done;
            printf "\n"
          )
        done;
      done




    let init_syntax bta =
      let bounds = Uautomaton.guard_and_invar_constants bta in
      let abs = init_empty bta in
      Array.iteri (fun x arx ->
          Array.iteri (fun y arxy ->
              Array.iter
                (fun (k, ineq) ->
                   if x > y then (
                     if not(y=0 && (k,ineq) < Guard.Alg.zero) then 
                       add_predicate abs (x,y) (k,ineq);
                   )
                   else (
                     let k' = (ClassicDBMAlgebra.invert_raw (k,ineq)) in
                     if not(x=0 && k' < Guard.Alg.zero) then
                       add_predicate abs (y,x) k';
                   );
                ) arxy
            ) arx
        ) bounds;
      abs

    (** Make predicates of the form x-y<=k and x-y<k
        with all possible constants up to max bound per clock.
        This does not necessarily render the abstraction precise.
    *)
    let init_complete bta =
      let abs = init_empty bta in
      let bounds = Uautomaton.guard_and_invar_constants bta in
      let nbclocks = Uautomaton.nb_clocks bta in
      (* Add rectangular *)
      for x = 0 to nbclocks -1 do
        for y = 0 to nbclocks -1 do
          if x <> 0 && x <> y then (
            let (maxb,_) =
              if bounds.(x).(0) = [||] then Pdbm.Guard.Alg.zero
              else Array.max bounds.(x).(0)
            in
            for k = 0 to maxb do
              ignore(add_predicate abs (x,y) (k,DBM_STRICT));
              ignore(add_predicate abs (x,y) (k,DBM_WEAK))
            done
          )
        done;
        (* lower bounds *)
        if x <> 0 then (
          let(minb,_) =
            if bounds.(0).(x) = [||] then Pdbm.Guard.Alg.zero
            else Array.min bounds.(0).(x) in
          for k = minb to 0 do
            ignore(add_predicate abs (0,x) (k, DBM_STRICT));
            ignore(add_predicate abs (0,x) (k, DBM_WEAK));
          done
        )
      done;
      abs

    let init_bounded b bta =
      let abs = init_empty bta in
      let nbclocks = Uautomaton.nb_clocks bta in
      (* Add rectangular *)
      for x = 0 to nbclocks -1 do
        for y = 0 to nbclocks -1 do
          if x <> y then (
            Enum.iter (fun k ->
                if not (y=0 && k <= 0 || x=0 && k > 0) then
                  ignore(add_predicate abs (x,y) (k,DBM_STRICT));
                if not (y=0 && k < 0 || x=0 && k > 0 ) then
                  ignore(add_predicate abs (x,y) (k,DBM_WEAK))
                )
              ) ((-b)--b)
        done;
      done;
      abs



    let to_string bta abs =
      let buf = Buffer.create 1024 in
      let dim = Uautomaton.nb_clocks bta in
      for x = 0 to dim do
        for y = 0 to dim do
          if (DynArray.length abs.(x).(y)) > 0 then(
            Buffer.add_string buf
              (sprintf "Predicates(%d, %d): " x y);
            for i = 0 to (DynArray.length abs.(x).(y)) - 1 do
              Buffer.add_string buf
                (sprintf "%s " (ClassicDBMAlgebra.to_string (DynArray.get abs.(x).(y) i)))
            done;
            Buffer.add_string buf "\n"
          )
        done;
      done;
      Buffer.contents buf

    let size abs =
      Array.map (fun ar -> Array.sum (Array.map DynArray.length ar)) abs
      |> Array.sum

    let over_approximate_udbm abs dbm =
      let open ClassicDBMAlgebra in
      let dim = Guard.dimension dbm in
      let raw = Guard.to_flat dbm in
      for x = 0 to dim - 1 do
        for y = 0 to dim - 1 do
          if x <> y then (
            raw.(x*dim+y) <- match over_approximate abs x y raw.(x*dim+y) with
              None ->
              if x <> 0 then Guard.Alg.infty
              else (0,DBM_WEAK)
              |Some r -> r
          )
        done
      done;
      let dbm' = Guard.from_flat raw dim in
      dbm'

  (**
     Given two DBMs a and b with a /\ b = empty,
     refine abstractions abs such that
     abs(a) /\ abs(b) = empty.
  *)
  let refine_separate abs a b =
    let module Dbm = Guard in 
    (* Test *)
    (*
    printf "Refine-separate for a b:\n";
    printf "a is\n%s\n" (Dbm.to_string a);
    printf "b is\n%s\n" (Dbm.to_string b);
       *)
(*    printf "Found following interpolant: ";*)
    let interp = Guard.Interpolant.interpolant a b in

    Log.debug (sprintf "refine_separate: Got interpolant of size %d:\n" (List.length interp));
    List.iter
      (fun (x,y,r) ->
         add_predicate abs (x,y) r;
         Log.debug (sprintf "\t(%d - %d %s)\n" x y (Dbm.Alg.to_string r));
      ) interp;
    Log.debug "And partial sums:\n";

    List.fold_left
      (fun (x,y,r) (x',y',r') ->
         if y <> x' then failwith "";
           let rr' = Dbm.Alg.add r r' in
           let acc = (x,y', Dbm.Alg.add r r') in
           if x <> y' then (
             add_predicate abs (x,y') rr';

             Log.debug (sprintf "\t%d - %d %s\n" x y' (Dbm.Alg.to_string r'));

           );
           acc
      ) (List.hd interp) (List.tl interp)
    |> ignore
    (*
    let a' = CPAbs.over_approximate_udbm abs a in
    let b' = CPAbs.over_approximate_udbm abs b in
    printf "a' is\n%s\n" (Dbm.to_string a');
    printf "b' is\n%s\n" (Dbm.to_string b');
       *)

  (** Given a list of constraints constr whose conjunction is unsatisfiable
      Refine abs so that (abs constr) is also unsatisfiable
      @pre constr is an unsat list of constrainsts

  *)
  let refine_empty abs constr =
    let module Dbm = Guard in 
    (* Bad design: *)
    let dim = (Array.length abs) in
    Log.debug "refine_empty: Original unsat constraints:\n";
    List.iter (fun (x,y,r) -> Log.debug (sprintf "\t%d - %d %s\n" x y (Dbm.Alg.to_string r))) constr;
    (* debugging *)
    (*
    let debug_dbm = Dbm.create dim in
    List.iter (Dbm.constrain debug_dbm) constr;
    if not(Dbm.is_empty debug_dbm) then (
      Log.fatal "refine_empty: called with non-empty DBM\n";
      failwith "Bug"
    );
    *)
    (* *)
    (* Initialize matrix as a universal DBM*)
    let ar = Array.init dim
        (fun x ->
           Array.init dim
             (fun y ->
                if x = 0 || x = y then (0, DBM_WEAK)
                else Dbm.Alg.infty
             )
        )
    in
    (* Copy the constraints in the matrix
       This matrix is not a reduced DBM *)
    List.iter (fun (x,y,r) ->
        ar.(x).(y) <- min ar.(x).(y) r;
      ) constr;
    let cycle = Guard.Interpolant.find_neg_cycle ar in
    Log.debug (sprintf "Negative cycle of length %d:\n" (List.length cycle));
(*    List.iter (fun (x,y,r) -> Log.debug (sprintf "\t%d - %d %s\n" x y (string_of_raw r))) cycle;*)
    (* Add single constraints along this path *)
    List.iter
      (fun (x,y,r) ->
         add_predicate abs (x,y) r;
         Log.debug (sprintf "\t%d - %d %s\n" x y (Dbm.Alg.to_string r))
      ) cycle;
    Log.debug "And partial sums:\n";
    (* Also add partial sums *)
    List.fold_left
      (fun (x,y,r) (x',y',r') ->
         if y <> x' then failwith "";
         let rr' = Dbm.Alg.add r r' in
         let acc = (x,y', Dbm.Alg.add r r') in
         if x <> y' then (
           add_predicate abs (x,y') rr';
           Log.debug (sprintf "\t%d - %d %s\n" x y' (Dbm.Alg.to_string r'));
         );
         acc
      ) (List.hd cycle) (List.tl cycle)
    |> ignore



  end
