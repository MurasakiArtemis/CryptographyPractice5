all: Main.out

Main.out: Main.cpp Functions.o Functions.hpp
	g++ Functions.o aes.o Main.cpp -Wall -std=c++11 -o Main.out
Functions.o: Functions.cpp Functions.hpp aes.o
	g++ Functions.cpp -c -Wall -std=c++11
aes.o: aes.c aes.h
	g++ aes.c -c -Wall -std=c++11

clean:
	rm *.*~ *.o *.out
