.PHONY: 
	program

program:
	g++ -Wall -std=c++11 -O2 -c revolver.cpp -o revolver.o
	g++ -ldl revolver.o -o revolver

