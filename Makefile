IN:=program.bf

MODE:=Debug

PHONY+=run
run: out/_build/bf
	$<

PHONY+=compiler
compiler: _build/bf2c

out/_build/bf: _build/bf2c out/_build/Makefile
	$< < ${IN} > out/bf.c
	cd out/_build && ${MAKE}

_build:
	mkdir -p $@

_build/Makefile: _build CMakeLists.txt
	cd $< && cmake -DCMAKE_BUILD_TYPE=${MODE} ..

_build/bf2c: _build/Makefile src/bf2c.cpp
	cd _build && ${MAKE}

out/_build:
	mkdir -p $@

out/_build/Makefile: out/_build out/CMakeLists.txt out/bf.c
	cd $< && cmake -DCMAKE_BUILD_TYPE=${MODE} ..

PHONY+=clean
clean:
	-rm -rf _build
	-rm -rf out/_build

.PHONY: $(PHONY)
