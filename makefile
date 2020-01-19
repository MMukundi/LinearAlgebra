CC = g++ -std=c++17 -ggdb -g

sourceFiles := $(wildcard *.cpp)

headerFiles := $(wildcard *.h)

LinAlg.h.gch: $(headerFiles) $(sourceFiles)
	$(CC) -c -o LinAlg.h.gch LinAlg.hpp

Main: LinAlg.h.gch
	$(CC) main.cpp -o Main


