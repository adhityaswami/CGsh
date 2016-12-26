/*
	Created by Adhitya Swaminathan as an internship project under Prof. Rupesh Nasre of IIT-M
	from December 15th to December 29th
*/

// The algorithms file. Contains the code for all the algorithms implemented for the graph

#include "graph.h"

depthFirstSearch::depthFirstSearch(graph *G, int source, int flag) {
	int i = 0;
	verticesList = G -> verticesList();
	this -> marked.resize(G -> nVertices());
	this -> edgeList.resize(G -> nVertices());
	this -> source = source;
	for (i; i < G -> nVertices(); i++) {
		this -> marked[i] = 0;
	}
	for (i = 0; this -> verticesList[i] != source; i++);
	if (flag == 2)
		dfsTrace(G, i);
	else if (flag == 3)
		dfsActual(G, i);
}

void depthFirstSearch::dfsActual(graph *G, int vertex) {
	this -> marked[vertex] = 1;
	int i, k;
	list newList = G -> adjVertices(this -> verticesList[vertex]);
	for (i = 1; i < newList.size(); i++) {
		int data = newList[i].data;
		for (k = 0; this -> verticesList[k] != data; k++);
		if (marked[k] == 0) {
			this -> edgeList[k] = vertex;
			dfsActual(G, k);
		}
	}
}

void depthFirstSearch::dfsTrace(graph *G, int vertex) {
	this -> marked[vertex] = 1;
	int i, k;
	std::cout << std::endl << verticesList[vertex] << " - ";
	list newList = G -> adjVertices(this -> verticesList[vertex]);
	for (int j = 1; j < newList.size(); j++) {
		if (j == newList.size() - 1)
			std::cout << newList[j].data;
		else
			std::cout << newList[j].data << ",";
	}
	for (i = 1; i < newList.size(); i++) {
		int data = newList[i].data;
		for (k = 0; this -> verticesList[k] != data; k++);
		if (marked[k] == 0)
			dfsTrace(G, k);
	}
}

std::vector<int> depthFirstSearch::pathTrace(int vertex) {
	int i, j;
	for (i = 0; this -> verticesList[i] != vertex; i++);
	for (j = 0; this -> verticesList[j] != source; j++);
	std::vector<int> pathStack;
	std::cout << std::endl;
	std::cout << std::endl;
	for (int k = i; k != j; k = this -> edgeList[k]) {
		pathStack.push_back(verticesList[k]);
	}
	pathStack.push_back(this -> source);
	return pathStack;
}

bool depthFirstSearch::ispath(int b) {
	int k;
	for (k = 0; this -> verticesList[k] != b; k++);
	if (marked[k] == 1)
		return true;
	return false;
}

breadthFirstSearch::breadthFirstSearch(graph *G, int source, int flag) {
	int i = 0;
	verticesList = G -> verticesList();
	this -> marked.resize(G -> nVertices());
	this -> edgeList.resize(G -> nVertices());
	this -> source = source;
	for (i; i < G -> nVertices(); i++) {
		this -> marked[i] = 0;
	}
	for (i = 0; this -> verticesList[i] != source; i++);
	if (flag == 2)
		bfsTrace(G, i);
	else if (flag == 3)
		bfsActual(G, i);
}


void breadthFirstSearch::bfsActual(graph *G, int vertex) {
	int k, i;
	std::queue<int> bfsQueue;
	marked[vertex] = 1;
	bfsQueue.push(vertex);
	while (!bfsQueue.empty()) {
		int newVertex = bfsQueue.front();
		bfsQueue.pop();
		list newList = G -> adjVertices(this -> verticesList[newVertex]);
		for (i = 1; i < newList.size(); i++) {
			int data = newList[i].data;
			for (k = 0; this -> verticesList[k] != data; k++);
			if (this -> marked[k] == 0) {
				this -> edgeList[k] = newVertex;
				this -> marked[k] = 1;
				bfsQueue.push(k);
			}
		}
	}
	std::cout << std::endl;
}
void breadthFirstSearch::bfsTrace(graph *G, int vertex) {
	int k, i;
	std::queue<int> bfsQueue;
	marked[vertex] = 1;
	bfsQueue.push(vertex);
	while (!bfsQueue.empty()) {
		int newVertex = bfsQueue.front();
		std::cout << verticesList[newVertex] << " - ";
		bfsQueue.pop();
		list newList = G -> adjVertices(this -> verticesList[newVertex]);
		for (i = 1; i < newList.size(); i++) {
			int data = newList[i].data;
			for (k = 0; this -> verticesList[k] != data; k++);
			if (this -> marked[k] == 0) {
				std::cout << verticesList[k] << ",";
				this -> edgeList[k] = newVertex;
				this -> marked[k] = 1;
				bfsQueue.push(k);
			}
		}
		std::cout << std::endl;
	}
}

bool breadthFirstSearch::ispath(int b) {
	int k;
	for (k = 0; this -> verticesList[k] != b; k++);
	if (marked[k] == 1)
		return true;
	return false;
}

std::vector<int> breadthFirstSearch::pathTrace(int vertex) {
	int i, j;
	for (i = 0; this -> verticesList[i] != vertex; i++);
	for (j = 0; this -> verticesList[j] != source; j++);
	std::vector<int> pathStack;
	std::cout << std::endl;
	std::cout << std::endl;
	for (int k = i; k != j; k = this -> edgeList[k]) {
		pathStack.push_back(verticesList[k]);
	}
	pathStack.push_back(this -> source);
	return pathStack;
}

djikstraShortestPath::djikstraShortestPath(graph *G, int source) {
	std::vector<int> vertexList = G -> verticesList();
	djikstraTracker.resize(G -> nVertices());
	for (int i = 0; i < djikstraTracker.size(); i++) {
		djikstraTracker[i].explored = false;
		djikstraTracker[i].distance = DJIK_INFINITY;
	}
	int k;
	for (k = 0; vertexList[k] != source; k++);
	djikstraTracker[k].distance = 0;
	djikstraTracker[k].shortestSubPath.push_back(source);
	if (!this -> markedChecker()) {
		this -> djikstrasAlgorithm(G, source);
	}
}

void djikstraShortestPath::djikstrasAlgorithm(graph *G, int vertex) {
	std::vector<int> vertexList = G -> verticesList();
	int i, j, k;
	for (i = 0; vertexList[i] != vertex; i++);
	djikstraTracker[i].explored = true;
	list adj = G -> adjVertices(vertex);
	int newVertex, leastDistance = 2147483647;
	if (!this -> markedChecker()) {
		for (i = 1; i < adj.size(); i++) {
			for (k = 0; vertexList[k] != adj[i].data; k++);
			for (j = 0; vertexList[j] != vertex; j++);
			if (djikstraTracker[j].distance + adj[i].edgeweight < djikstraTracker[k].distance || djikstraTracker[k].distance == DJIK_INFINITY) {
				djikstraTracker[k].distance = djikstraTracker[j].distance + adj[i].edgeweight;
				djikstraTracker[k].shortestSubPath = djikstraTracker[j].shortestSubPath;
				djikstraTracker[k].shortestSubPath.push_back(vertex);
			}
		}
		for (i = 0; i < djikstraTracker.size(); i++) {
			if (!djikstraTracker[i].explored) {
				if (djikstraTracker[i].distance < leastDistance) {
					leastDistance = djikstraTracker[i].distance;
					newVertex = vertexList[i];
				}
			}
		}
		djikstrasAlgorithm(G, newVertex);
	}
}

bool djikstraShortestPath::markedChecker() {
	for (int i = 0; i < djikstraTracker.size(); i++) {
		if (djikstraTracker[i].explored == false)
			return false;
	}
	return true;
}

void djikstraShortestPath::shortestPath(graph *G, int vertex) {
	std::vector<int> vertexList = G -> verticesList();
	int k;
	for (k = 0; vertexList[k] != vertex; k++);
	for(int l = 1; l < djikstraTracker[k].shortestSubPath.size(); l++) {
		std::cout << djikstraTracker[k].shortestSubPath[l] << ",";
	}
	std::cout << vertex << std::endl;
}

int djikstraShortestPath::shortestDistance(graph *G, int vertex) {
	std::vector<int> vertexList = G -> verticesList();
	int k;
	for (k = 0; vertexList[k] != vertex; k++);
	return djikstraTracker[k].distance;
}
