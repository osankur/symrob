all:
#	ocamlbuild -use-ocamlfind uta.inferred.mli
	ocamlbuild -use-ocamlfind utaReader.native
	ocamlbuild -use-ocamlfind utaReader.cmxa
	ocamlbuild -use-ocamlfind utaReader.cma
parse.byte:
	ocamlbuild -use-ocamlfind utaReader.byte
allbyte:
	ocamlbuild -use-ocamlfind enlarge_uppaal.byte
parse.cmxa:
	ocamlbuild -use-ocamlfind utaReader.cmxa
parse.cma:
	ocamlbuild -use-ocamlfind utaReader.cma
other:
	ocamllex guardLexer.mll
	ocamlyacc guardParser.mly
	ocamlc -c guardParser.ml
install:
	@ocamlfind install uppaal_parser META _build/*.cm* _build/*.[oa]
uninstall:
	@ocamlfind remove uppaal_parser
reinstall:
	@ocamlfind remove uppaal_parser
	@ocamlfind install uppaal_parser META _build/*.cm* _build/*.[oa]
clean:
	rm -rf _build
