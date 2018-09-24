native:
#	ocamlbuild -use-ocamlfind -cflags '-I /home/sankur/work/program/symrob/uppaal/_build' -lflags '-I /home/sankur/work/program/symrob/uppaal/_build parse.cmxa' main.native
	ocamlbuild -use-ocamlfind main.native
	mv main.native symrob
byte:
#	ocamlbuild -use-ocamlfind -lib nums -lib str -cflags -linkpkg -libs batteries main.native
#	ocamlbuild -cflags -g -lib nums -lib str main.native
	ocamlbuild -ocamlc ocamlcp -use-ocamlfind main.byte
binary:
	ocamlbuild -use-ocamlfind binarySearch.native
clean:
	rm -rf _build
