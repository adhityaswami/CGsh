/*
	Created by Adhitya Swaminathan as an internship project under Prof. Rupesh Nasre of IIT-M
	from December 15th to December 29th
*/

// The graph header. Contains all the declarations and definitions required in all the 
// associated files

#ifndef GRAPH_HEADER__
#define GRAPH_HEADER__


#define INVALID_DATA -5476
#define DJIK_INFINITY 1281

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <iterator>
#include <sstream>
#include <queue>

struct listNodeStructure {
	int data;
	int edgeweight;
};

typedef struct listNodeStructure listNode;
typedef std::vector<listNode> list;
typedef	std::vector<list> adjList;

class graph {
	private:
		// V denotes vertices, and E denotes Edges
		int vertices, edges;
		// Instead of a linked list, I decided to use a two dimensional vector of the node
		// structure I created above. Avoiding pointers makes the code less prone
		// to errors and NULL references.
		adjList adj;

	public:
		void addEdge(int, int);
		void addEdge(int, int, int);
		void addEdgeFromFile(int, int);
		void addEdgeFromFile(int, int, int);
		graph(int);
		graph(int, int);
		graph(std::string);
		int nVertices();
		int nEdges();
		int nNeighbours(int);
		list adjVertices(int);
		bool vertexCheck(int);
		bool edgeCheck(int, int);
		void print();
		void deleteEdge(int, int);
		std::vector<int> verticesList(void);
		bool weightedChecker();
		void randomWeightGenerator();
};

std::vector<std::string> stringSplit(std::string);
bool fileStatus(std::string);

class depthFirstSearch {
	private:
		std::vector<int> marked;
		std::vector<int> edgeList;
		int source;
		void dfsActual(graph *, int);
		void dfsTrace(graph *, int);
     	std::vector<int> verticesList;

	public:
		bool ispath(int);
		depthFirstSearch(graph *, int, int);
		std::vector<int> pathTrace(int);
};

class breadthFirstSearch {
	private:
		std::vector<int> marked;
		std::vector<int> edgeList;
		std::vector<int> verticesList;
		int source;
		void bfsActual(graph *, int);
		void bfsTrace(graph *, int);

	public:
		bool ispath(int);
		breadthFirstSearch(graph*, int, int);
		std::vector<int> pathTrace(int);
};

struct dijkstraPrototype {
	bool explored;
	int distance;
	std::vector<int> shortestSubPath;
};

typedef std::vector<struct dijkstraPrototype> djikstra;

class djikstraShortestPath {
	private:
		djikstra djikstraTracker;
	public:
		void djikstrasAlgorithm(graph *, int);
		djikstraShortestPath(graph *, int);
		bool markedChecker();
		int shortestDistance(graph *, int);
		void shortestPath(graph *, int);
};

#endif