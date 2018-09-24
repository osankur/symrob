open Batteries
open Printf
open Num
open Common
open Pervasives
open Uta

let infty_val = max_int
let minfty_val = -infty_val


type dbm_inequality_type = DBM_STRICT | DBM_WEAK

let string_of_ineq = function
  |DBM_WEAK -> "<="
  |DBM_STRICT -> "<"

let compare_inequality_type a b = match (a,b) with
  DBM_STRICT, DBM_STRICT
  | DBM_WEAK, DBM_WEAK -> 0
  | DBM_STRICT, DBM_WEAK -> -1
  | DBM_WEAK , DBM_STRICT -> 1


module type ALGEBRA  =
sig
  type t
  val add : t -> t -> t
  val min : t -> t -> t
  val max : t -> t -> t
  val compare : t -> t -> int
  val infty : t
  val zero : t
  val is_zero : t -> bool
  val is_infty : t -> bool
  val to_string : t -> string
  val compare_int : t -> int -> int
  (** Get a weak constraint from given int; e.g. for the classic algebra,
      [weak_from_int v] yields (v,DBM_WEAK) *)
  val weak_from_int : int -> t
  val strict_from_int : int -> t
  val scale : t -> int -> t
end

module type GENERIC_DBM = 
sig
  module Alg : ALGEBRA
  type t
  type clock_constraint = int * int * Alg.t

  val elementAt : t -> int -> int -> Alg.t
  val set_zero : t -> unit
  val copy : t -> t
  val create : int -> t
  val dimension : t -> int
  val is_empty : t -> bool
  val set_empty : t -> unit
  val make_empty : int -> t
  val reduce : t -> unit
  val set_constraint : t -> int -> int -> Alg.t -> unit
  val constrain : t -> int -> int -> Alg.t -> unit
  val assign_constraint : t -> int -> int -> Alg.t -> unit
  val from_constraints : int -> clock_constraint list -> t
  val to_string : t -> string
  val intersect : t -> t -> unit
  val pretime : t -> unit
  val posttime : t -> unit
  val free : t -> ClockSet.t -> unit
  val unreset : t -> ClockSet.t -> unit
  val reset : t -> ClockSet.t -> unit
  val leq : t -> t -> bool
  val equal : t -> t -> bool
  val extrapolate_lu : t -> int array -> int array -> unit
  val closure_leq : int array -> t -> t -> bool
  val constrainByName : string VarContext.t -> t -> string -> string -> Alg.t -> unit
  val pretty_print : 'a BatIO.output -> string VarContext.t -> t -> unit
  val is_rectangular : t -> bool
  val bounded_universe : (int*int) array -> t
  (** From array representation of guards, and given dimension, return a dbm *)
  val from_flat : Alg.t array -> int -> t
  val to_flat : t -> Alg.t array
end

(** All DBM operations raise this exception if the resulting DBM is empty *)
exception EmptyDBM

module GenericDBM = 
  functor (Alg : ALGEBRA) ->
  struct
    type t = (Alg.t array) array
  type clock_constraint = int * int * Alg.t

    (** Create a DBM with no constraints. The dimension is the number of clocks plus one *)
    let create dimension =
      let result = Array.make dimension (Array.make dimension Alg.infty) in
      for i = 0 to dimension - 1 do
        result.(i) <- Array.make dimension Alg.infty
      done; 
      for i = 0 to dimension - 1 do
        result.(i).(i) <- Alg.zero;
        result.(0).(i) <- Alg.zero;
      done;
      result

    let elementAt t i j = t.(i).(j)

    let dimension mdbm = Array.length mdbm

    let set_zero mdbm =
      let dimension = dimension mdbm in
      for i = 0 to dimension - 1 do
        for j = 0 to dimension - 1 do
          mdbm.(i).(j) <- Alg.zero
        done;
      done



    let copy t = 
      let nt0 = Array.create (dimension t) Alg.zero in
      let nt = Array.create (dimension t) nt0 in
      let dim = dimension t in
      for i = 0 to dim - 1 do
        nt.(i) <- Array.copy t.(i)
      done;
      nt

    let set_empty mdbm =
      mdbm.(0).(0) <- Alg.weak_from_int (-1)

    let make_empty d =
      let d = create d in
      set_empty d;
      d

    let is_empty mdbm =
      let dimension = dimension mdbm in
      let rec aux i = if (i = dimension) then false else
        if (Alg.compare Alg.zero  mdbm.(i).(i) = 1) then (
          true
        )
        else aux (i+1)
      in aux 0

    let to_string mdbm = 
      if is_empty mdbm then 
        "false"
      else 
      let dim = dimension mdbm in
      let b = Buffer.create (dim*dim*20) in
      for i = 0 to dim-1 do
        for j = 0 to dim - 1 do
          bprintf b "%s\t" (Alg.to_string mdbm.(i).(j))
        done;
        bprintf b "\\\n"
      done;
      Buffer.contents b

    let reduce mdbm =
      if (is_empty mdbm) then raise EmptyDBM else 
        (
        let dim = dimension mdbm in
        for i = 0 to dim-1 do
          for j = 0 to dim - 1 do
            for k = 0 to dim - 1 do
              mdbm.(i).(j) <- Alg.min (mdbm.(i).(j)) (Alg.add (mdbm.(i).(k)) (mdbm.(k).(j)))
            done
          done;
          if (Alg.compare mdbm.(i).(i) Alg.zero = -1) then
            raise EmptyDBM
        done
      )

    (** The same as reduce but does not raise an exception on empty DBM *)
    let silent_reduce mdbm =
      let dim = dimension mdbm in
      for i = 0 to dim-1 do
        for j = 0 to dim - 1 do
          for k = 0 to dim - 1 do
            mdbm.(i).(j) <- Alg.min (mdbm.(i).(j)) (Alg.add (mdbm.(i).(k)) (mdbm.(k).(j)))
          done
        done;
      done

    (** Set constraint but do not reduce *)
    let assign_constraint mdbm x y k = 
      mdbm.(x).(y) <- k

    (** Set the constraint of mdbm on component (x,y) to k *)
    let set_constraint mdbm x y k =
      let k =
        if ( x = 0 ) then
          Alg.min Alg.zero k
        else
          k
      in
      let dim = dimension mdbm in
      if ( x < 0 || x >= dim || y < 0 || y >= dim) then
        raise (Failure (sprintf "Clock index out of bounds: %d or %d; dimension\ is %d" x y dim));
      mdbm.(x).(y) <- k;
      reduce mdbm

    (** *Add* to mdbm the constraint k on component (x,y) (intuitively x - y <= k).
        This is equivalent to intersecting m1 with this constraint. *)
    let constrain mdbm x y k =
      if is_empty mdbm then raise EmptyDBM else
      let dim = dimension mdbm in
      if ( x < 0 || x >= dim || y < 0 || y >= dim) then
        raise (Failure (sprintf "Clock index out of bounds: %d or %d; dimension\ is %d" x y dim));
      set_constraint mdbm x y (Alg.min (mdbm.(x).(y)) k)

    (** m1 is modified to contain the DBM m1&m2 *)
    let intersect m1 m2 =
      if is_empty m1 then raise EmptyDBM
      else
      let dim = dimension m1 in
      if (dimension m2 <> dim ) then
        raise (Failure (sprintf "Intersection of DBMs with different dimensions %d and %d" dim (dimension m2)));
      for i = 0 to dim-1 do
        for j = 0 to dim - 1 do
          m1.(i).(j) <- Alg.min m1.(i).(j) m2.(i).(j)
        done
      done;
      reduce m1

    (** Time predecessors a.k.a. down operation *)
    let pretime m1 =
      if is_empty m1 then raise EmptyDBM else
      let dim = dimension m1 in
      for i = 0 to dim - 1 do
        m1.(0).(i) <- Alg.zero
      done;

      reduce m1

    (** Time successors a.k.a. up operation *)
    let posttime m1 =
      if is_empty m1 then raise EmptyDBM else
      let dim = dimension m1 in
      for i = 1 to dim - 1 do
        m1.(i).(0) <- Alg.infty
      done
    (* Note that the result is already normalized *)


    (** Free all constraints on clocks clocks *)
      (*
    let free m1 clocks =
      let dim = dimension m1 in 
      for i = 0 to dim - 1 do
        if (ClockSet.mem i clocks) then
          (
            m1.(0).(i) <- Alg.zero;
            m1.(i).(0) <- Alg.infty
          )
      done;
      for i = 0 to dim - 1 do
        for j = 0 to dim - 1 do
         (* FIXME The following seems buggy to me *)
          if (i<>j && i <> 0 && j <> 0 && ((ClockSet.mem i clocks) || (ClockSet.mem j clocks)) ) then
            m1.(i).(j) <- Alg.infty;
        done
      done;
      reduce m1
         *)
    let free m1 clocks =
      if is_empty m1 then raise EmptyDBM else
      let dim = dimension m1 in 
      for i = 0 to dim - 1 do
        ClockSet.iter 
          (fun k -> 
            m1.(k).(i) <- Alg.infty;
            m1.(i).(k) <- m1.(i).(0)
          ) clocks
      done

    (** The reverse of the reset(clocks) operation: intersect with the guard
     * clocks=0, and free the clocks *)
    let unreset m1 clocks = 
      if is_empty m1 then raise EmptyDBM else
      let dim = dimension m1 in
      let reset = create dim in
      ClockSet.iter (fun c -> set_constraint reset c 0 Alg.zero; set_constraint
                        reset c 0 Alg.zero) clocks;
      intersect m1 reset;
      free m1 clocks

    let reset m1 clocks =
      if is_empty m1 then raise EmptyDBM else
      free m1 clocks;
      ClockSet.iter (fun c -> 
          m1.(c).(0) <- Alg.zero;
        ) clocks;
      reduce m1

    (** Inclusion check: returns true iff m1 is included in m2*)
    let leq m1 m2 =
      if is_empty m1 then true
      else if is_empty m2 then is_empty m1
      else
      let dim = dimension m1 in
      if (dimension m2 <> dim ) then
        raise (Failure "Comparison of DBMs with different dimensions");
      (
        try
          Array.iteri 
            (fun i m1row ->
               Array.iteri (fun j a -> 
                   if (Alg.compare a m2.(i).(j)>0) then
                     raise Found
                 ) m1row
            ) m1;
          true
        with Found -> 
          false
           | _ as a -> raise a
      )

    let equal m1 m2 =
      if is_empty m1 || is_empty m2 then is_empty m1 && (is_empty m2) else
      let dim = dimension m1 in
      if (dimension m2 <> dim ) then
        raise (Failure "Comparison of DBMs with different dimensions");
      (
        try
          for i = 0 to dim - 1 do
            for j = 0 to dim - 1 do
              if ( Alg.compare m1.(i).(j) m2.(i).(j) <> 0 ) then
                raise Found
            done
          done;
          true
        with Found -> false
           | _ as a -> raise a
      )

    let constrainByName context mdbm x y k =
      if is_empty mdbm then raise EmptyDBM else
      mdbm.(VarContext.var2index context x).(VarContext.var2index context y) <- 
        Alg.min mdbm.(VarContext.var2index context x).(VarContext.var2index context y) k;
      reduce mdbm

    let is_rectangular mdbm = 
      let dim = dimension mdbm  in
      let o = create dim in
      for i = 0 to dim - 1 do
        o.(i).(0) <- mdbm.(i).(0);
        o.(0).(i) <- mdbm.(0).(i)
      done;
      reduce o;
      if (equal o mdbm) then true else false


    let bounded_universe lu_bounds = 
      let alpha_bounds = Array.map (fun (l,u) -> max l u) lu_bounds
      in
      let largest_constant = Array.fold_left (+) 0 alpha_bounds in
      (* The global invariant that bounds the clocks, given the largets constants that appear *)
      let dim = Array.length lu_bounds in
      let z = create dim in
      for i = 0 to dim - 1 do
        for j = 0 to dim - 1 do
          constrain z i j (Alg.weak_from_int largest_constant)
        done
      done;
      z


  let from_flat boundar dim = 
    let g = create dim in 
    for i = 0 to dim - 1 do
      for j = 0 to dim - 1 do
        g.(i).(j) <- boundar.(i*dim + j)
      done;
    done;
    g


    let to_flat g =
      let dim = dimension g in
      let f = Array.make (dim*dim) Alg.zero in
      for i = 0 to dim - 1 do
        for j = 0 to dim - 1 do
          f.(i*dim +j) <- elementAt g i j
        done;
      done;
      f

    let from_constraints dim cclist =
    let dbm = create dim in
    List.iter (fun (x,y,b) -> (constrain dbm x y b)) cclist;
    dbm
  end

module ClassicDBMAlgebra =
struct
  type t = int * dbm_inequality_type

  let infty = (infty_val,DBM_STRICT)

  let weak_from_int i = (i,DBM_WEAK)
  let strict_from_int i = (i,DBM_STRICT)
  let scale (n,ineq) s = 
    (if (n = infty_val) then infty_val else (n*s)), ineq

  let add a b = match (a,b) with
      ((a,_),(b,_)) when a = infty_val || b = infty_val ->  infty
    |((k,tk),(l,tl)) when tk = DBM_STRICT || tl = DBM_STRICT ->  ((k+l),DBM_STRICT)
    |((k,tk),(l,tl)) ->  ((k+l),DBM_WEAK)

  let compare a b = match (a,b) with
    | (k,_), (l,_) when l = infty_val && k = infty_val -> 0
    | (k,_), _ when k = infty_val -> 1
    | _, (l,_) when l = infty_val -> -1
    | (k,_), (l,_) when k < l -> -1
    | (k,_), (l,_) when k > l -> 1
    | (_,ink), (_,inl) -> compare_inequality_type ink inl

  let compare_int a bint = compare a (bint,DBM_WEAK)

  let min a b = match (compare a b) with 
    | 0 | -1 -> a
    | _ -> b

  let max a b = match (compare a b) with 
    | 0 | -1 -> a
    | _ -> b

  let zero = (0, DBM_WEAK)

  let is_zero a = (a = zero)

  let is_infty (a,_) = (a = infty_val) 
    (* this is faster *)

  let to_string = function
    | a when a = infty -> "<INF"
    | (a, DBM_WEAK) -> "<=" ^ (string_of_int a)
    | (a, DBM_STRICT) -> "<" ^ (string_of_int a)

  let invert_inequality = function
    | DBM_WEAK -> DBM_STRICT
    | DBM_STRICT -> DBM_WEAK

  let invert_raw (k,ineq) = (-k, invert_inequality ineq)

  let negate_constraint (x,y,(b,ineq)) =
    (y,x,invert_raw (b,ineq))

end




module ClassicDBM = struct
  module Alg = ClassicDBMAlgebra
  include GenericDBM(ClassicDBMAlgebra)

  exception Punctual

  (** Create an empty dbm *)
  let empty dimension = 
    let t = create dimension in
    t.(0).(0) <- (-1,DBM_WEAK);
    t

  (** Checks if the dbm contains an equality constraint *)
  let punctual mdbm = 
    let dim = dimension mdbm in 
    (try
       for i = 1 to dim - 1 do
         match mdbm.(i).(0), mdbm.(0).(i) with
           (a,_) when (Alg.is_infty a) -> ()
         |  (_,b) when (Alg.is_infty b) -> ()
         |(a,_),(b,_) when a = -b -> 
           raise Punctual
         |_ -> ()
       done;
       false
     with Punctual -> true
        | _ as a -> raise a
    )

  (** Diagonal LU Bounds extrapolation *)
  let extrapolate_lu guard lbounds ubounds =
    let dim = dimension guard in
  (*
for i = 1 to dim - 1 do
printf "Clock %d, L: %d, U: %d\n" i lbounds.(i) ubounds.(i);
done;
*)
    let to_number = fst
    in
    for i = 1 to dim - 1 do
      let infij = (to_number guard.(0).(i)) < (-lbounds.(i)) in
      for j = 0 to dim - 1 do
        if (i = j ) then ()
        else (
          let bound = to_number guard.(i).(j) in
          if (infij || bound > lbounds.(i) ||
              (to_number guard.(0).(j)) < -ubounds.(j)) then(
            guard.(i).(j) <- Alg.infty
          )
        )
      done;
    done;
    (* 1st row *)
    for j = 1 to dim - 1 do
      if ( (to_number guard.(0).(j)) < -ubounds.(j)  ) then (
        guard.(0).(j) <-
          if ( ubounds.(j) >= 0 ) then(
            ((-ubounds.(j)), DBM_STRICT)
          ) else (
            Alg.zero
          )
      )
    done;
    reduce guard

  (** [closure_leq alpha m1 m2] Check whether m1 \not\subseteq closure_alpha(m2) *)
  let closure_leq alpha m1 m2 = 
    let dim = dimension m1 in
    (try 
       for x = 1 to dim - 1 do
         if ( (Alg.compare m2.(x).(0) m1.(x).(0) = -1) && (Alg.compare_int m2.(x).(0) alpha.(x) <= 0) ) then
           raise Found
         else if (((Alg.compare m2.(0).(x) m1.(0).(x) = -1)) && (Alg.compare_int m1.(0).(x) (-alpha.(x)) >= 0)) then
           raise Found;
         for y = 1 to dim - 1 do
           if (
             x <> y
             && (Alg.compare_int m1.(0).(x) (-alpha.(x)) >= 0)
             && (Alg.compare m2.(y).(x) m1.(y).(x)  = -1)
           ) then (
             let aym0x = (alpha.(y),DBM_WEAK) in
             if ( Alg.compare m2.(y).(x) (Alg.add aym0x m1.(0).(x)) <= 0) then
               raise Found
           )
         done;
       done;
       true
     with Found -> false)


  let _pretty_print chan context string_of_ineq mdbm =
    let open Batteries in
    let dimension = dimension mdbm in
    let outputlist = Queue.create () in
    let negate = function
      | a when a = infty_val -> a
      | a -> -a
    in
    let _print i j =
      begin
        let (m,ineq) = mdbm.(i).(j) in
        if ( i <> 0 && j <> 0 && 
             (Alg.compare mdbm.(i).(0) Alg.zero = 0 || 
              Alg.compare mdbm.(j).(0) Alg.zero = 0 ) 
           )
        then 
          ()
        else if (mdbm.(i).(j) = Alg.zero && mdbm.(j).(i) = Alg.zero ) then 
          (
            if ( i < j ) then 
              Queue.add (sprintf "%s = %s" (VarContext.index2var context i)
                           (VarContext.index2var context j)) outputlist			
          )
        else if (j = 0) then
          Queue.add (sprintf "%s %s %s" (VarContext.index2var context i)
                       (string_of_ineq ineq) (string_of_int m)) outputlist 
        else if (i = 0) then
          (
            Queue.add (sprintf "%s %s %s" (string_of_int (negate m))
                         (string_of_ineq ineq) (VarContext.index2var context j)) outputlist ;
          )
        else
          Queue.add (sprintf "%s - %s %s %s" 
                       (VarContext.index2var context i)
                       (VarContext.index2var context j)
                       (string_of_ineq ineq)
                       (string_of_int m)
                    ) outputlist ;
      end
    in
    let open_paranthesis_of_ineq = function
      |DBM_WEAK -> "["
      |DBM_STRICT -> "("
    in
    let closed_paranthesis_of_ineq = function
      |DBM_WEAK -> "]"
      |DBM_STRICT -> ")"
    in
    if (is_empty mdbm) then fprintf chan "false"
    else if (mdbm = (create dimension)) then
      fprintf chan "true"
    else (
      for i = 1 to dimension - 1 do
        let (mi0,ineqi0) = mdbm.(i).(0) in
        let (m0i,ineq0i) = mdbm.(0).(i) in
        let string_neg_int = function
          | a when a = infty_val -> "-Infty"
          | a -> string_of_int(-a)
        in
        if (mi0 <> infty_val || m0i <> 0 || ineq0i <> DBM_WEAK ) then
          (
            Queue.add (sprintf "%s in %s%s,%s%s\n" (VarContext.index2var context i)
                         (open_paranthesis_of_ineq ineq0i) (string_neg_int m0i)
                         (string_of_int mi0) (closed_paranthesis_of_ineq ineqi0)
                      ) outputlist
          )
      done;
      let added = ref false in
      for i = 0 to dimension-1 do
        for j = 0 to dimension-1 do
          if (i = 0 || j = 0 || i = j ||
              (Alg.is_infty mdbm.(i).(j))) then ((*continue*))
          else
            (
              _print i j;
              added := true
            )
        done;
        if ( !added ) then Queue.add "\n" outputlist;
        added := false
      done;
      let hasPre = ref false in
      Queue.iter (fun s ->
          if ( s <> "" && s <> "\n" ) then
            (
              if !hasPre  then
                (
                  fprintf chan " and ";
                  hasPre := false
                );
              fprintf chan "%s" s;
              hasPre := true
            )
        )
        outputlist
    )
  let pretty_print chan context mdbm =
    let open Batteries in
    _pretty_print chan context string_of_ineq mdbm

  let pretty_print_uppaal chan context mdbm =
    let open Batteries in
    let uppaal_string_of_ineq = function
      | DBM_WEAK -> "&lt;="
      | DBM_STRICT -> "&lt;"
    in
    _pretty_print chan context uppaal_string_of_ineq mdbm


  module Interpolant =
    struct
      (** Find and return a negative cycle in a (possibly non-canonical) matrix of 
          raw_t
          @pre There is a negative cycle (the corresponding dbm is empty)
      *)
      let find_neg_cycle a =
        (* Find a negative cycle in a, and add its predicates *)
        let dim = Array.length a in
        let bellman_ford source =
          let dist = Array.create dim Alg.infty in
          dist.(source) <- (0,DBM_WEAK);
          let pred = Array.create dim (-1) in
          for it = 0 to dim do
            for i = 0 to dim - 1 do
              for j = 0 to dim - 1 do
                if ( Alg.add dist.(i) a.(i).(j) < dist.(j) ) then  (
                  dist.(j) <- Alg.add dist.(i) a.(i).(j);
                  pred.(j) <- i
                )
              done
            done
          done;
          (pred, dist)
        in
        let exception Found of (int * int * Alg.t) list in
        try
          for source = 0 to dim - 1 do
            (* Check whether node source appears in a negative cycle *)
            let (pred, dist) = bellman_ford source in
            if dist.(source) < (0, DBM_WEAK) then (
              (* Now the table pred contains a simple negative cycle. 
                 This cycle induced by pred may not contain source,
                 so we find some node that belongs to the cycle first.
                 And add all constraints that appear in the cycle to the interpolant.
              *)
              let visited = Array.create dim false in
              let k = ref pred.(source) in
              visited.(source) <- true;
              (* This cycle finds an element k0 of the simple cycle *)
              while not visited.(!k) do
                visited.(!k) <- true;
                k := pred.(!k)
              done;
              let source = !k in
              let prev = ref source in
              k := pred.(source);
              let preds = ref [] in
              while !k <> source do
                preds := (!k,!prev,a.(!k).(!prev)) :: !preds;
                prev := !k;
                k := pred.(!k)
              done;
              preds := (!k,!prev,a.(!k).(!prev)) :: !preds;
              raise (Found !preds)
            )
          done;
          failwith "Could not find any negative cycle"
        with Found preds -> preds

      (** Return some interpolant of (a,b),
          that is, the constraints that appear in a negative cycle
          of min(a,b) *)
      let interpolant a b =
        if ((is_empty a) || (is_empty b)) then (
          failwith "interpolant called with an empty dbm"
        );
        let tmp = copy a in
        (try
           intersect tmp b;
           failwith "Interpolant called with intersecting dbms"
         with EmptyDBM -> ());
        let dim = (dimension a) in
        let inter = Array.init dim
            (fun x ->
               Array.init dim
                 (fun y ->
                    min (elementAt a x y) (elementAt b x y)
                 )
            )
        in
        find_neg_cycle inter
    end

end

module Guard = ClassicDBM

module type ENLARGED_DBM =
sig
  include GENERIC_DBM
  val extrapolate_deltalu : t -> Alg.t array -> Alg.t array -> unit
  val closure_deltaleq : Alg.t array -> t -> t -> bool
  val quantified_leq : t -> t -> bool
  (** Checks if given extended states are equal for delta=0 *)
  val equal_non_enlarged_zones : t ->  t -> bool
  val width : t -> int
  val enlarge_guard : Guard.t -> t
  val from_ints : int -> int -> Alg.t
  val to_guard : t -> Guard.t
  val largest_delta : unit -> Num.t
end







(** Infinitesimally enlarged DBM Algebra with a shared variable largest_delta.
    As a rule of thumb, all functions that actually return an enlarged DBM, or one of their elements update
    the bound largest_delta. Other functions, such as compare, do not modify it.*)
module InfEnlargedDBMAlgebra =
struct

  let infty = (infty_val,0)

  let zero = (0,0)

  let is_zero a = (a = zero)

  let is_infty (a,_) = (a = infty_val)

  (** A shared variable that is updated after each operation.
      After a series of operations on InfEnlargedDBMs, all equations hold if delta is between 0 and largest_delta0*)
  let largest_delta0 = ref (Num.num_of_string "1000000")
  let largest_delta () = !largest_delta0
  let bound_delta d = largest_delta0 := (Num.min_num !largest_delta0 d)
  let smallest_delta0 = ref (Num.num_of_string "0")
  let initialize_bound ?lower:(l=Num.num_of_string "0") ?upper:(u=Num.num_of_string "1000000") () =
    largest_delta0 := u;
    smallest_delta0 := l

  let weak_from_int i = (i,0)
  let strict_from_int i = failwith "No strict guard in enlarged automata"

  let scale (n,p) s = 
    (if (n = infty_val) then (n,p) else (n*s,p*s))

  (** An element (m,p) is a component of an enlarged DBM. Note that the inqualities are always closed, since this data structure will be only used for closed timed automata. The bounds on delta are stored in the global variables
      [!smallest_delta0, !largest_delta0]*)
  type t = int * int

  let add a b = match (a,b) with
      ((a,_),(b,_)) when a = infty_val || b = infty_val -> infty
    |((k,pk),(l,pl)) -> (k + l,pk + pl)

  (** The comparison function does not modify largest_delta0. Returns that a is smaller than b if it is the case for small enough delta.
      *)
  let compare a b = match (a,b) with
    | (k,_), (l,_) when l = infty_val && k = infty_val -> 0
    | (k,_), _ when k = infty_val -> 1
    | _, (l,_) when l = infty_val -> -1
    | (k,_), (l,_) when k < l -> -1
    | (k,_), (l,_) when k > l -> 1
    | (_,pk), (_,pl) -> Pervasives.compare pk pl

  (** [quantified_compare a b] Returns the result of the comparison of a and b and the delta bound under which this holds.
      *)
  let quantified_compare a b = match (a,b) with 
      _ when (is_infty a) && (is_infty b) -> (0,!largest_delta0)
    | _ when (is_infty b) -> (-1 , !largest_delta0)
    | _ when (is_infty a) -> (1, !largest_delta0)
    | (k,pk), (l,pl) when k < l -> 
      if (pk <= pl ) then
        (-1, !largest_delta0)
      else
        (-1, (((Num.num_of_int l) -/ (Num.num_of_int k)) //
              ((Num.num_of_int pk) -/ (Num.num_of_int pl))))
    | (k,pk), (l,pl) when k > l ->
      if ( pk >= pl ) then
        (1, !largest_delta0)
      else 
        (1, (((Num.num_of_int k) -/ (Num.num_of_int l)) //
             ((Num.num_of_int pl) -/ (Num.num_of_int pk))))
    | (_,pk), (_,pl) ->
      (Pervasives.compare pk pl, !largest_delta0)

  let compare_int a bint = compare a (bint,0)

  let min a b = match (a,b) with 
    _ when (is_infty a) && (is_infty b) -> a
    | _ when (is_infty b) -> a
    | _ when (is_infty a) -> b
    | ((k,pk) as a), (l,pl) when k < l ->
      if (pk > pl) then
        bound_delta (((Num.num_of_int l) -/ (Num.num_of_int k)) //
                     ((Num.num_of_int pk) -/ (Num.num_of_int pl)));
      a
    | (k,pk), ((l,pl) as b) when k > l ->
      if (pl > pk) then
        (bound_delta
           (((Num.num_of_int k) -/ (Num.num_of_int l)) //
            ((Num.num_of_int pl) -/ (Num.num_of_int pk)))
        );
      b
    | ((_,pk) as a), ((_,pl) as b) ->
      if (pk < pl) then 
        a
      else 
        b

  let max a b = 
    let minab = min a b in
    if ( minab = a ) then b
    else a



  let to_string = function
    | ((a, p) as t)when t <> infty -> sprintf "(%d + %d delta, <=)" a p
    | _ -> "(INF, <)"

end


module InfEnlargedDBM = 
struct
  module Alg = InfEnlargedDBMAlgebra
  include GenericDBM(Alg)

  let largest_delta () = !Alg.largest_delta0

  let from_flat boundar dim =
    let g = create dim in 
    for i = 0 to dim - 1 do
      for j = 0 to dim - 1 do
        g.(i).(j) <- match boundar.(i*dim + j) with
            t when (fst t = infty_val) -> Alg.infty
          | b,_ -> (b,0)
      done;
    done;
    g


  (** FIXME: Redefine the following two functions of module Guard with lbounds, ubounds, and alpha
      as Dbm.t array types (obtained by adding weak inequalities). In this way, we unify their usage *)
  let extrapolate_lu guard lbounds ubounds = failwith "not implemented: see extrapolate_deltalu"
  let closure_leq alpha m1 m2 = failwith "not implemented: see closure_deltaleq"

  let extrapolate_deltalu guard lbounds ubounds =
    let alg_negate = function
      | a when (Alg.is_infty a) -> failwith "LU bounds are not suppoed to be Infty"
      | (m,p) -> (-m,-p)
    in
    let quantified_compare a b = 
      let (r,bound) = Alg.quantified_compare a b in
      Alg.bound_delta bound;
      r
    in
    let dim = dimension guard in
    (** Diagonals *)
    for i = 1 to dim - 1 do
      let infij = (quantified_compare 
                     guard.(0).(i) (alg_negate lbounds.(i))) = (-1) in
      for j = 0 to dim - 1 do
        if (i <> j) then
          (
            if (infij
                || quantified_compare guard.(i).(j) lbounds.(i) = 1
                || quantified_compare guard.(0).(j) (alg_negate ubounds.(j)) = - 1) then(
              guard.(i).(j) <- Alg.infty
            )
          )
      done;
    done;
    (* 1st row *)
    for j = 1 to dim - 1 do
      if ( quantified_compare guard.(0).(j)  (alg_negate ubounds.(j)) =(-1)  ) then (
        let m = match ubounds.(j) with
          | ((m,_) as t) when not (Alg.is_infty t) -> m
          | _ -> failwith "Ubounds cannot be Infty"
        in				 
        guard.(0).(j) <-
          if ( m >= 0 ) then(
            ((-m-1), 0)
          ) else (
            (0, 0)
          )
      )
    done;
    reduce guard


  (** [closure_deltaleq alpha m1 m2] Check whether m1 \not\subseteq closure_alpha(m2) *)
  (** FIXME: Either buggy or not correct for robust exploration *)
  let closure_deltaleq alpha m1 m2 = 
    let dim = dimension m1 in
    let local_delta0 = ref !Alg.largest_delta0 in
    let quantified_compare a b = 
      let (r,bound) = Alg.quantified_compare a b in
      local_delta0 := Num.min_num !local_delta0 bound;
      r
    in
    let alg_negate = function
      | ((m,p) as t) when not (Alg.is_infty t) -> (-m,-p)
      | _ -> failwith "LU bounds are not suppoed to be Infty"
    in
    (try 
       for x = 1 to dim - 1 do
         if ( (quantified_compare m2.(x).(0) m1.(x).(0) = -1) 
              && (quantified_compare m2.(x).(0) alpha.(x) <= 0) ) then
           (
             raise Found
           )
         else if (((quantified_compare m2.(0).(x) m1.(0).(x) = -1)) 
                  && (quantified_compare m1.(0).(x) (alg_negate alpha.(x)) >= 0)) then
           (
             raise Found
           );
         for y = 1 to dim - 1 do
           if (
             x <> y
             && (quantified_compare m1.(0).(x) (alg_negate alpha.(x)) >= 0)
             && (quantified_compare m2.(y).(x) m1.(y).(x)  = -1)
           ) then (
             if ( quantified_compare m2.(y).(x) (Alg.add alpha.(y) m1.(0).(x)) <= 0) then
               (
                 raise Found
               )
           )
         done;
       done;
       Alg.bound_delta !local_delta0;
       true
     with Found -> false)

  (** Create an empty DBM *)
  let create_empty dimension =
    let result = Array.make dimension (Array.make dimension Alg.infty) in
    for i = 0 to dimension - 1 do
      result.(i) <- Array.make dimension Alg.infty
    done; 
    for i = 0 to dimension - 1 do
      result.(i).(i) <- (-1,0);
    done;
    result


  let width m = 
    Array.fold_left (fun v t -> max v (Array.fold_left (fun v x-> max v (snd x)) 0 t)) 0 m

  let initialize_bound = Alg.initialize_bound

  let get_delta_bound () = Alg.largest_delta0

  let bound_delta = Alg.bound_delta


  (** Quantified inclusion check: Returns the same result as leq, but updates largest_delta0
      by the upper bound under which the inclusion holds; no changes are made to largest_delta0 if no inclusion.*)
  let quantified_leq m1 m2 =
    let dim = dimension m1 in
    let local_delta0 = ref !Alg.largest_delta0 in
    let bound_localdelta d =
      local_delta0 := Num.min_num !local_delta0 d
    in
    if (dimension m2 <> dim ) then
      raise (Failure "Comparison of DBMs with different dimensions");
    (
      try
        Array.iteri 
          (fun i m1 ->
             Array.iteri (fun j a -> 
                 let (res, d) = Alg.quantified_compare a m2.(i).(j) in
                 if (res > 0 ) then raise Found
                 else bound_localdelta d
               ) m1
          ) m1;
        bound_delta !local_delta0;
        true
      with Found -> false
         | _ as a -> raise a
    )

  let to_guard g =
    let dim = dimension g in
    let z = Array.make (dim*dim) (0,DBM_WEAK) in
    for i = 0 to dim - 1 do
      for j = 0 to dim - 1 do
        let ((a,p) as t)= g.(i).(j) in
        z.(i * dim + j) <-
          match a with
          | _ when (Alg.is_infty t) -> (infty_val,DBM_STRICT)
          | m -> (m,DBM_WEAK)
      done;
    done;
    Guard.from_flat z dim

  (** Construct an enlarged DBM with 0 enlargements identical to the given  guard*)
  let from_guard g = 
    let dim = dimension g in
    let z2 = create dim in
    for i = 0 to dim - 1 do
      for j = 0 to dim - 1 do
        let (a,ineq) = g.(i).(j) in
        z2.(i).(j) <- (a,0)
      done;
    done;
    z2

  let from_ints a b = (a,b)

  (** Given a classic DBM, returns an InfEnlargedDBM.t
      where the DBM is enlarged by 1delta at all *rectangular* constraints.
      This enlargement is valid only if the guard has no diagonal constraints.*)
  let enlarge_guard guard = 
    let dim = dimension guard in
    let eguard = from_guard guard in
    (* Free all diagonal constraints *)
    for i = 1 to dim - 1 do
      for j = 1 to dim - 1 do
        if (i <> j) then
          eguard.(i).(j) <- Alg.infty
      done;
    done;
    for i = 1 to dim - 1 do
      let ((m,_) as t) = eguard.(i).(0) in
      if ( not (Alg.is_infty t) ) then
        eguard.(i).(0) <- (m,1);
      let ((m,_) as t) = eguard.(0).(i) in
      if ( not (Alg.is_infty t) && m <> 0) then
        eguard.(0).(i) <- (m,1)
    done;
    silent_reduce eguard;
    eguard

  let enlarge_from_flat boundar dim = 
    enlarge_guard (Guard.from_flat boundar dim)


  let print chan mdbm = 
    let dim = dimension mdbm in
    for i = 0 to dim - 1 do
      for j = 0 to dim - 1 do
        let (m,p) = mdbm.(i).(j) in
        fprintf chan "(%s,%s) " (string_of_int m) (string_of_int p)
      done;
      fprintf chan "\n";
    done

  let pretty_print chan context mdbm =
    let dimension = dimension mdbm in
    let outputlist = Queue.create () in
    let negate = function
      | a when a = infty_val -> infty_val
      | a -> -a
    in
    if (is_empty mdbm) then fprintf chan "false"
    else if (mdbm = (create dimension)) then
      fprintf chan "true"
    else (
      for i = 0 to dimension-1 do
        for j = 0 to dimension-1 do
          if (i = 0 && Alg.zero = mdbm.(i).(j) || i = j ||
              (Alg.is_infty mdbm.(i).(j))) then ((*continue*))
          else 
            begin
              let (m,p) = mdbm.(i).(j) in
              let deltasign = if (i = 0) then "-" else "+" in
              let minusdelta = if (p=0) then "" else (sprintf "%s %s[delta]" deltasign (string_of_int p))
              in
              if (j = 0) then
                Queue.add (sprintf "%s <= %s %s" (VarContext.index2var context i)
                             (string_of_int m) minusdelta)
                  outputlist
              else if (i = 0) then
                (
                  Queue.add (sprintf "%s %s <= %s" (string_of_int (negate m)) 
                               minusdelta  (VarContext.index2var context j)) outputlist ;
                )
              else
                Queue.add (sprintf "%s - %s <= %s %s" 
                             (VarContext.index2var context i)
                             (VarContext.index2var context j)
                             (string_of_int m)
                             minusdelta
                          ) outputlist ;
            end
        done;
      done;
      let b = ref false in
      Queue.iter (fun s -> if !b then fprintf chan " and " else b := true; fprintf
                     chan "%s" s) outputlist
    );
    fprintf chan "\t(given delta <= %s)" (string_of_num !Alg.largest_delta0)


  let equal_non_enlarged_zones m1 m2 = 
    let dim = dimension m1 in
    if (dimension m2 <> dim ) then
      raise (Failure "Comparison of DBMs with different dimensions");
    (
      try
        Array.iteri 
          (fun i m1 ->
             Array.iteri (fun j a -> if (compare (fst a) (fst m2.(i).(j)) <> 0) then raise Found) m1
          ) m1;
        true
      with Found -> false
         | e -> raise e
    )

end


(** Location number and a guard *)
type extended_zone = int * ClassicDBM.t

