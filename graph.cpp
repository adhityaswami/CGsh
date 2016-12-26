/*
	Created by Adhitya Swaminathan as an internship project under Prof. Rupesh Nasre of IIT-M
	from December 15th to December 29th
*/

// The graph function file. Contains all the functions within and associated with the graph
// class in the program

#include "graph.h"

bool fileStatus(std::string fileName) {
	std::ifstream infile(fileName);
	return infile.good();
}

bool graph::weightedChecker() {
	for (int i = 0; i < this -> adj.size(); i++) {
		for (int j = 1; j < this -> adj[i].size(); j++) {
			if (this -> adj[i][j].edgeweight != 1)
				return true;
		}
	}
	return false;
}

void graph::randomWeightGenerator() {
	if (this -> weightedChecker() == false) {
		srand((int)time(NULL));
		for (int i = 0; i < adj.size(); i++) {
			for (int j = 1; j < adj[i].size(); j++) {
				adj[i][j].edgeweight = rand() % 100;
			}
		}
	}
}

std::vector<std::string> stringSplit(std::string line) {
	std::istringstream buffer (line);
	std::vector<std::string> parsed;
	std::copy(std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>(), std::back_inserter(parsed));
	return parsed;
}

int graph::nNeighbours(int vertex) {
	list newList = adjVertices(vertex);
	return (newList.size() - 1);
}

graph::graph(int vertices) {
	this -> adj.resize(vertices);
	for (int i = 0; i < vertices; i++) {
		this -> adj[i].resize(1);
		this -> adj[i][0].data = INVALID_DATA;
		this -> adj[i][0].edgeweight = 0;
	}
	this -> vertices = vertices;
	this -> edges = 0;
}

graph::graph(int vertices, int edges) {
	if (edges <= (vertices * (vertices - 1) / 2)) {
		srand((int)time(NULL));
		this -> adj.resize(vertices);
		for (int i = 0; i < vertices; i++) {
			this -> adj[i].resize(1);
			this -> adj[i][0].data = INVALID_DATA;
			this -> adj[i][0].edgeweight = 0;
		}
		this -> vertices = vertices;
		this -> edges = edges;
		std::vector<int> randomVertices(vertices);
		for (int i = 0; i < vertices; i++) {
			randomVertices[i] = rand() % 10000000;
			this -> adj[i][0].data = randomVertices[i];
			this -> adj[i][0].edgeweight = 0;
		}
		std::vector<int> vertexSelector(vertices);
		for (int i = 0; i < vertices; i++) {
			vertexSelector[i] = i;
		}
		random_shuffle(vertexSelector.begin(), vertexSelector.end());
		int edgecount = 0;
		for (edgecount; edgecount < edges; edgecount++) {
			bool vertexChecker;
			random_shuffle(vertexSelector.begin(), vertexSelector.end());
			int a = randomVertices[vertexSelector[0]];
			random_shuffle(vertexSelector.begin(), vertexSelector.end());
			int b = randomVertices[vertexSelector[0]];
			vertexChecker = vertexCheck(a) && vertexCheck(b);
			if (vertexChecker) {
				if (a == b) {
					edgecount--;
					continue;
				}
				if (edgeCheck(a, b)) {
					edgecount--;
					continue;
				}
				addEdge(a, b, rand() % 100);
			}
			else {
				edgecount--;
				continue;
			}
		}
	}
}

graph::graph(std::string fileName) {
	std::ifstream fileRead;
	fileRead.open(fileName);
	std::string line;
	std::getline(fileRead, line);
	int ver = std::stoi(line, nullptr);
	std::getline(fileRead, line);
	int edg = std::stoi(line, nullptr);
	this -> adj.resize(ver);
	for (int i = 0; i < ver; i++) {
		this -> adj[i].resize(1);
		this -> adj[i][0].data = INVALID_DATA;
		this -> adj[i][0].edgeweight = 0;
	}
	while (std::getline(fileRead, line)) {
		std::vector<std::string> s;
		s = stringSplit(line);
		int a, b, weight;
		a = stoi(s[0], nullptr);
		b = stoi(s[1], nullptr);
		if (s.size() == 2) {
			this -> addEdge(a, b);
		}
		else {
			weight = stoi(s[2], nullptr);
			this -> addEdge(a, b, weight);
		}
	}
	fileRead.close();
	this -> vertices = ver;
	this -> edges = edg;
}

int graph::nVertices() {
	return this -> vertices;
}

int graph::nEdges() {
	return this -> edges;
}

bool graph::vertexCheck(int vertex) {
	for (int i = 0; i < this -> adj.size(); i++) {
		if (this -> adj[i][0].data == vertex)
			return true;
	}
	return false;
}

bool graph::edgeCheck(int a, int b) {
	if (!(vertexCheck(a) && vertexCheck(b)))
		return false;
	for (int i = 0; i < this -> adj.size(); i++) {
		if (this -> adj[i][0].data == a) {
			for (int j = 0; j < this -> adj[i].size(); j++) {
				if (adj[i][j].data == b)
					return true;
			}
		}
	}
	return false;
}

std::vector<int> graph::verticesList() {
	std::vector<int> actual;
	actual.resize(this -> nVertices());
	for (int i = 0; i < this -> vertices; i++) {
		actual[i] = this -> adj[i][0].data;
	}
	return actual;
}

void graph::addEdge(int a, int b, int weight) {
	int flag = 0, flag1 = 0, flag2 = 0, invalidcount = 0;
	bool edgeFlag = edgeCheck(a, b);
	if (!edgeFlag) {
		if (a == b) {
			std::cout << "\nSelf-Edges not allowed\n\n";
			flag = -1;
		}
		for (int i = 0; i < this -> adj.size(); i++) {
			if (this -> adj[i][0].data == a) {
				flag1++;
			}
			else if (this -> adj[i][0].data == b) {
				flag2++;
			}
		}
		for (int i = 0; i < this -> adj.size(); i++) {
			if (this -> adj[i][0].data == INVALID_DATA) {
				if (flag1 == 0) {
					this -> adj[i][0].data = a;
					flag1++;
				}
				else if (flag2 == 0) {
					this -> adj[i][0].data = b;
					flag2++;
				}
			}
		}
		flag = flag1 + flag2;
		if (flag == 0) {
			listNode x, y;
			x.data = a;
			x.edgeweight = weight;
			y.data = b;
			y.edgeweight = weight;
			this -> edges++;
			this -> adj.resize(adj.size() + 2);
			this -> adj[vertices].push_back(x);
			this -> adj[vertices + 1].push_back(y);
			this -> adj[vertices].push_back(y);
			this -> adj[vertices + 1].push_back(x);
			this -> vertices += 2;
		}

		else if (flag == 1) {
			listNode x, y;
			x.data = a;
			x.edgeweight = weight;
			y.data = b;
			y.edgeweight = weight;
			this -> edges++;
			this -> adj.resize(adj.size() + 1);
			int dummy;
			listNode holder;
			for (int i = 0; i < this -> adj.size(); i++) {
				if (this -> adj[i][0].data == a) {
					this -> adj[i].push_back(y);
					dummy = b;
					holder = y;
				}
				if (this -> adj[i][0].data == b) {
					this -> adj[i].push_back(x);
					dummy = a;
					holder = x;
				}
			}
			this -> adj[vertices].push_back(holder);
			if (dummy  == a)
				this -> adj[vertices].push_back(y);
			else
				this -> adj[vertices].push_back(x);
			this -> vertices++;
		}

		else if (flag == 2) {
			listNode x, y;
			x.data = a;
			x.edgeweight = weight;
			y.data = b;
			y.edgeweight = weight;
			this -> edges++;
			for (int i = 0; i < this -> adj.size(); i++) {
				if (this -> adj[i][0].data == a)
					this -> adj[i].push_back(y);
				else if (this -> adj[i][0].data == b)
					this -> adj[i].push_back(x);
			}
		}
	}
}

void graph::addEdge(int a, int b) {
	this -> addEdge(a, b, 1);
}

list graph::adjVertices(int vertex) {
	for (int i = 0; i < this -> adj.size(); i++) {
		if (this -> adj[i][0].data == vertex)
			return this -> adj[i];
	}
}

void graph::deleteEdge(int a, int b) {
	int mainFlag = 0;
	int flag1, flag2, k = 0;
	flag1 = this -> nNeighbours(a);
	flag2 = this -> nNeighbours(b);
	bool checkFlag = edgeCheck(a, b);
	if (checkFlag == true) {
		if (this -> nNeighbours(a) == 1)
			this -> vertices--;
		if (this -> nNeighbours(b) == 1)
			this -> vertices--;
		for (int i = 0; i < this -> adj.size(); i++) {
			k = 0;
			if (flag1 != 1 && flag2 != 1) {
				if (this -> adj[i][0].data == a) {
					std::vector<listNode> x(this -> adj[i].size() - 1);
					for (int j = 0; j < this -> adj[i].size(); j++) {
						if (adj[i][j].data != b) {
							x[k] = this -> adj[i][j];
							k++;
						}
					}
					this -> adj[i] = x;
				}
				if (this -> adj[i][0].data == b) {
					std::vector<listNode> x(this -> adj[i].size() - 1);
					for (int j = 0; j < this -> adj[i].size(); j++) {
						if (adj[i][j].data != a) {
							x[k] = this -> adj[i][j];
							k++;
						}
					}
					this -> adj[i] = x;
				}
			}
			else if (flag1 == 1 && flag2 != 1) {
				if (this -> adj[i][0].data == b) {
					std::vector<listNode> x(this -> adj[i].size() - 1);
					for (int j = 0; j < this -> adj[i].size(); j++) {
						if (adj[i][j].data != a) {
							x[k] = this -> adj[i][j];
							k++;
						}
					}
					this -> adj[i] = x;
				}
				if (this -> adj[i][0].data == a) {
					for (int l = i; l < this -> adj.size() - 1; l++) {
						this -> adj[l] = this -> adj[l + 1];
					}
					this -> adj.resize(this -> adj.size() - 1);
				}
			}
			else if (flag1 != 1 && flag2 == 1) {
				if (this -> adj[i][0].data == a) {
					std::vector<listNode> x(this -> adj[i].size() - 1);
					for (int j = 0; j < this -> adj[i].size(); j++) {
						if (adj[i][j].data != b) {
							x[k] = this -> adj[i][j];
							k++;
						}
					}
					this -> adj[i] = x;
				}
				if (this -> adj[i][0].data == b) {
					for (int l = i; l < this -> adj.size() - 1; l++) {
						this -> adj[l] = this -> adj[l + 1];
					}
					this -> adj.resize(this -> adj.size() - 1);
				}
			}
			else {
				if (this -> adj[i][0].data == a) {
					for (int l = i; l < this -> adj.size() - 1; l++) {
						this -> adj[l] = this -> adj[l + 1];
					}
					this -> adj.resize(this -> adj.size() - 1);
				}
				if (this -> adj[i][0].data == b) {
					for (int l = i; l < this -> adj.size() - 1; l++) {
						this -> adj[l] = this -> adj[l + 1];
					}
					this -> adj.resize(this -> adj.size() - 1);
				}
			}
		}
		this -> edges--;
	}
	else {
		std::cout << "\nThe given node(s) doesn't exist in the graph\n\n >> ";
	}
}

void graph::print() {
	for (int i = 0; i < this -> adj.size(); i++) {
		for (int j = 0; j < this -> adj[i].size(); j++) {
			if (adj[i][0].data != INVALID_DATA) {
				if (j == (this -> adj[i].size() - 1))
					std::cout << adj[i][j].data;
				else {
					if (adj[i][j + 1].edgeweight == 0)
						std::cout << adj[i][j].data << " ----> ";
					else
						std::cout << adj[i][j].data << " --" << adj[i][j + 1].edgeweight << "--> ";

				}
			}
			else {
				std::cout << "(EmptyVertex)";
			}
		}
		std::cout << std::endl;
	}
}