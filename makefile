CC = g++ -std=c++17 -ggdb

source := $(wildcard *.cpp)

objects := $(patsubst %.cpp,ObjectFiles/%.o,$(source))

ObjectFiles/%.o: %.cpp LinAlg.h
	$(CC) $< -c -o $@

LinAlg.h: Vector.h Space.h

LinAlg: LinAlg.h
	$(CC) -c -o LinAlg.h.gch LinAlg.h

Main: LinAlg
	$(CC) main.cpp -o Main


