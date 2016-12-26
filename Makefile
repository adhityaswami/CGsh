
# A Makefile for desh Compilation.
DEBUG=-g

all: graph
	
graph:	main.cpp graph.cpp algo.cpp graph.h
	g++ $(DEBUG) main.cpp graph.cpp algo.cpp -o graph
clean:
	rm -f graph *~

