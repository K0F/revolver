.PHONY: 
	program

program:
	g++ -Wall -std=c++11 -O2 -c main.cpp -o main.o
	g++ -ldl main.o -o main

