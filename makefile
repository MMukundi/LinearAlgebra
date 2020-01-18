CC = g++ -std=c++17 -ggdb

source := $(wildcard *.cpp)

objects := $(patsubst %.cpp,ObjectFiles/%.o,$(source))

ObjectFiles/%.o: %.cpp LinAlg.h
	$(CC) $< -c -o $@

LinAlg.h: Vector.h Space.h

LinAlg.h.gch: LinAlg.h
	$(CC) -c -o LinAlg.h.gch LinAlg.h

Main: LinAlg.h.gch
	$(CC) main.cpp -o Main


