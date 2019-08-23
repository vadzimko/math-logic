.PHONY: pack all run clean
GENERATED=src/parser.mli src/parser.ml src/lexer.ml
OCAMLC=ocamlc # ocamlopt for speed
PACKAGE=hw3.zip

CXXFLAGS+=-std=c++14 -Wall -O2
CXX=g++

ifeq ($(OS),Windows_NT)
	DEL=del /f
else
	DEL=rm -f
endif

all: main.exe out out/main.o

run: main.exe out out/main.o
	@./main.exe
	@./out/main.o

src/tree.cmi:
	@cd src && $(OCAMLC) -c tree.ml

main.exe: $(GENERATED) src/tree.cmi
	@cd src && $(OCAMLC) str.cma tree.ml $(GENERATED:src/%=%) main.ml -o ../main.exe

out:
	@mkdir -p out

out/main.o: src/main.cpp
	@$(CXX) $^ $(CXXFLAGS) -o out/main.o

pack: $(GENERATED)
	@zip $(PACKAGE) -r Makefile src

$(GENERATED): src/lexer.mll src/parser.mly
	@ocamllex src/lexer.mll
	@ocamlyacc src/parser.mly

clean:
	rm -rf out
	cd src && $(DEL) $(GENERATED:src/%=%) *.c *.cmo *.cmi *.o*
	$(DEL) main.exe $(PACKAGE)
