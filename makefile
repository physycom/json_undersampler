EXE = json_undersampler.exe

all: dirtree
	$(CXX) -std=c++11 -Isrc/jsoncons/src -o bin/$(EXE) src/json_undersampler.cpp 

dirtree:
	@mkdir -p bin

clean:
	rm -f bin/$(EXE)

cleanall:
	rm -rf bin obj
