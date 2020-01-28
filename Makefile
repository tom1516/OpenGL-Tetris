all: main

Cube.o: Cube.cpp
	g++ -c -fpcc-struct-return -I/usr/include -g Cube.cpp -L/usr/lib/ -lGLU -lglut -lm	
	
Object.o: Cube.o Object.cpp
	g++ -c -fpcc-struct-return -I/usr/include -g Object.cpp -L/usr/lib/ -lGLU -lglut -lm

main: Cube.o Object.o main.cpp
	g++ -fpcc-struct-return -I/usr/include -g main.cpp -L/usr/lib/ -lGLU -lglut -lm Cube.o Object.o 

clean: 
	rm -f *.o
