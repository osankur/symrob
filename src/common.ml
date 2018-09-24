
module StringSet = Set.Make(String)
module IntSet = Set.Make( 
    struct
          let compare = Pervasives.compare
              type t = int
    end )
(** Clocks are given unique indices from 0 to nb_clocks -1.*)
type clock_t = int

module ClockSet = Set.Make( 
struct
  let compare = Pervasives.compare
  type t = clock_t
end )

exception Found
exception DiagonalGuard

(**
   Just a generic map from arbitrary elements to indices in 0..size-1
*)
module Indexer(Elt : sig type t end)(HT : Hashtbl.HashedType with type t = Elt.t) =
struct
  type key = Elt.t

  module H = Hashtbl.Make(HT)

  type t = {key2index : int H.t;
            mutable index2key : key array;
            mutable next_pos : int;
            size : int
           }

  let create ?init:(init=0) n=
    {key2index = H.create n;
     index2key = [||];
     next_pos = init;
     size = n
    }
  let size indexer = indexer.size

  let add indexer elt =
    H.add indexer.key2index elt indexer.next_pos;
    if(indexer.index2key = [||]) then (
      indexer.index2key <- Array.make indexer.size elt
    );
    assert(indexer.next_pos < indexer.size);
    indexer.index2key.(indexer.next_pos) <- elt;
    indexer.next_pos <- indexer.next_pos + 1

  let get_key indexer i =
    assert(0 <= i && i < indexer.size);
    indexer.index2key.(i)

  let get_keys indexer =
    H.fold (fun e _ l -> e::l) indexer.key2index []

  let get_index indexer elt =
    H.find indexer.key2index elt

  let _test indexer str_of_edge =
    for i = 0 to indexer.size-1 do
      assert ((H.find indexer.key2index indexer.index2key.(i)) = i);
      Printf.printf "-- Edge(%d) = %s\n" i (str_of_edge i)
    done
end
