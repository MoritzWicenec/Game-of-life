PROG = src/Source.cpp
EXE = gol

comp:
	mkdir -p build
	c++ $(PROG) -o build/$(EXE)

clean:
	rm -rf build

test: comp
	build/$(EXE)
