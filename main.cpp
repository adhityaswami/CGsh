/*
	Created by Adhitya Swaminathan as an internship project under Prof. Rupesh Nasre of IIT-M
	from December 15th to December 29th
*/

// The main program. Execution and shell interface is built here


#include "graph.h"

int main(void) {
	system("clear");
	graph *G = NULL;
	std::cout << "\n\nCombinatorial Graph SHell (cgsh)\n";
	std::cout << "type \"help\" for a list of commands\n\n\n";
	std::cout << " >> ";
	std::string command;
	std::getline(std::cin, command);
	while (true) {
		std::vector<std::string> parsedCommand;
		parsedCommand = stringSplit(command);
		if (parsedCommand[0] == "help") {
			system("clear");
			std::cout << "\n\t\t\tThis is cgsh\n\n";
			std::cout << "  It is a shell aimed specifically at combinatorial graph applications\n\n";
			std::cout << "  The following commands can be used now: \n\n";
			std::cout << "  1) load : Load a graph from the specified file. Usage \"load filename\"\n";
			std::cout << "  2) new : Load an empty graph of specified number of vertices into memory. Usage \"new nVertices\"\n";
			std::cout << "  3) random : Create a random graph with input number of vertices and edges. Usage \"random nVertices nEdges\"\n";
			std::cout << "  4) print : Prints the graph loaded in the memory. Usage \"print\"\n";
			std::cout << "  5) nvertices : Prints the number  of vertices in the graph. Usage \"nvertices\"\n";
			std::cout << "  6) nedges : Prints the number of edges in the graph. Usage \"nedges\"\n";
			std::cout << "  7) add : add a weighted edge set to the graph. Weight is 1 by default. Usage \"add nodeX nodeY weight\"\n";
			std::cout << "  8) delete : Delete an edge set from the graph, if it exists. Usage \"delete nodeX nodeY\"\n";
			std::cout << "  9) degree : Prints the degree of the input vertices. Usage \"degree nodeX nodeY etc.\"\n";
			std::cout << "  10) degree max : Prints the maximum degree of the graph, along with the corresponding vertex. Usage \"degree max\"\n";
			std::cout << "  11) neighbours : Prints the neighbours of the input vertices. Usage \"neighbours nodeX nodeY etc.\"\n";
			std::cout << "  12) dfs show : Depth First Traversal sequence. Usage \"dfs show nodeX\"\n";
			std::cout << "  13) dfs path : Checks if there is a path between nodes by the DFS algorithm. If so, it prints the first such path found by DFS. Usage \"dfs path nodeX nodeY\"\n";
			std::cout << "  14) bfs show : Breadth First Traversal sequence. Usage \"bfs show nodeX\"\n";
			std::cout << "  15) dfs path : Checks if there is a path between nodes by the BFS algorithm. This path is also the shortest. Usage \"bfs path nodeX nodeY\"\n";
			std::cout << "  16) distance : Prints the shortest distance between two nodes. Usage \"distance nodeX nodeY\"\n";
			std::cout << "  17) diameter : Only for small graphs. The longest shortest-path in the graph. Usage \"diameter\"\n";
			std::cout << "  18) write : Writes the graph to a file, overwriting the original contents. If file doesn't exist, it creates it.Usage \"write filename\"\n";
			std::cout << "  19) randomweights : Adds random weights ranging from 1 - 100 to an unweighted graph. Usage \"randomweights\"\n";
			std::cout << "  20) djik sd : Calculates the minimum distance between vertices in an edge weighted graph, by Dijkstra's algorithm. Use only for connected graphs. Usage \"djik sd nodeX nodeY\"\n";
			std::cout << "  20) djik sp : Prints the shortest path in the graph with Dijkstra's Algorithm. Use only for connected graphs. Usage \"djik sp nodeX nodeY\"\n";
			std::cout << "  21) unload : Unloads the existing graph from memory. Usage \"unload\"\n";
			std::cout << "  22) quit : Quits the shell and exits to the terminal environment\n\n";
			std::cout << " >> ";
			std::getline(std::cin, command);
			continue;
		}
		else if (parsedCommand[0] == "load") {
			if (G == NULL) {
				if (fileStatus(parsedCommand[1])) {
					system("clear");
					G = new graph(parsedCommand[1]);
					std::cout << "\n\nGraph has been loaded from graph file \"" << parsedCommand[1] << "\"\n\n";
					std::cout << " >> ";
					std::getline(std::cin, command);
					continue;
				}
				else {
					std::cout << "\n\nThe specified file doesn't exist!\n\n";
					std::cout << " >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
			else {
				std::cout << "\n\nA Graph already exists in memory\n\n";
				std::cout << " >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "new") {
			if (parsedCommand.size() == 2) {
				if (G == NULL) {
					system("clear");
					int v = stoi(parsedCommand[1], nullptr);
					G = new graph(v);
					std::cout << "\n\nAn empty graph of " << parsedCommand[1] << " vertices has been generated\n\n";
					std::cout << " >> ";
					std::getline(std::cin, command);
					continue;
				}
				else {
					std::cout << "\n\nA Graph already exists in memory\n\n";
					std::cout << " >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
			else {
				std::cout << "Incorrect Usage\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "random") {
			if (parsedCommand.size() == 3) {
				if (G == NULL) {
					system("clear");
					int v = stoi(parsedCommand[1], nullptr);
					int e = stoi(parsedCommand[2], nullptr);
					if (e <= (v * (v - 1) / 2)) {
						G = new graph(v, e);
						std::cout << "\n\nA random of " << parsedCommand[1] << " vertices and " << parsedCommand[2] << " edges has been generated\n\n";
						std::cout << " >> ";
						std::getline(std::cin, command);
						continue;
					}
					else {
						std::cout << "\n\nGraph already exists in memory\n\n";
						std::cout << " >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
				else {
					std::cout << "\n\nInvalid number of edges. Graph cannot be generated\n\n";
					std::cout << " >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
			else {
				std::cout << "Incorrect Usage\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "print") {
			if (parsedCommand.size() == 1) {
				if (G == NULL) {
					std::cout << "\nNo graph has been loaded into memory\n";
					std::cout << "\n\n >> ";
					std::getline(std::cin, command);
					continue;
				}
				else {
					std::cout << std::endl << "The graph is\n";
					G -> print();
					std::cout << "\n\n >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
			else {
				std::cout << "Incorrect Usage\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "nvertices") {
			if (G == NULL) {
				std::cout << "\nNo graph has been loaded into memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				std::cout << "\nThe number of vertices in the graph is " << G -> nVertices();
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "nedges") {
			if (G == NULL) {
				std::cout << "\nNo graph has been loaded into memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				std::cout << "\nThe number of edges in the graph is " << G -> nEdges();
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "add") {
			system("clear");
			if (G == NULL) {
				std::cout << "\nNo graph has been loaded into memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			if (parsedCommand.size() == 3) {
				int x = stoi(parsedCommand[1], nullptr);
				int y = stoi(parsedCommand[2], nullptr);
				G -> addEdge(x, y);
				std::cout << "\nSuccess\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else if (parsedCommand.size() == 4) {
				int x = stoi(parsedCommand[1], nullptr);
				int y = stoi(parsedCommand[2], nullptr);
				int weight = stoi(parsedCommand[3], nullptr);
				G -> addEdge(x, y, weight);
				std::cout << "\nSuccess\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				std::cout << "Incorrect Usage\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "delete") {
			system("clear");
			if (G == NULL) {
				std::cout << "\nNo graph has been loaded into memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			if (parsedCommand.size() == 3) {
				int x = stoi(parsedCommand[1], nullptr);
				int y = stoi(parsedCommand[2], nullptr);
				if (G -> edgeCheck(x, y)) {
					G -> deleteEdge(x, y);
					std::cout << "\nSuccess\n\n >> ";
				}
				else {
					std::cout << "\nGiven edge set does not exist in the graph\n\n >> ";
				}
				std::getline(std::cin, command);
				continue;
			}
			else {
				std::cout << "Incorrect Usage\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "degree") {
			if (G == NULL) {
				std::cout << "\nNo graph has been loaded into memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			if (parsedCommand[1] == "max") {
				int max, vertex;
				std::vector<int> vertexList = G -> verticesList();
				max = G -> nNeighbours(vertexList[0]);
				vertex = vertexList[0];
				for (int i = 1; i < vertexList.size(); i++) {
					if (G -> nNeighbours(vertexList[i]) > max) {
						max = G -> nNeighbours(vertexList[i]);
						vertex = vertexList[i];
					}
				}
				std::cout << "\nNode " << vertex << " has the maximum degree of " << max;
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			std::vector<int> vertices;
			vertices.resize(parsedCommand.size() - 1);
			for (int i = 1; i < parsedCommand.size(); i++) {
				vertices[i] = stoi(parsedCommand[i], nullptr);
				if (G -> vertexCheck(vertices[i])) {
					std::cout << "\nThe degree of " << vertices[i] << " is ";
					std::cout << G -> nNeighbours(vertices[i]) << std::endl;
				}
				else {
					std::cout << "\n" << vertices[i] << " is not a node in the graph";
				}
			}
			std::cout << "\n\n >> ";
			std::getline(std::cin, command);
			continue;
		}
		else if (parsedCommand[0] == "neighbours") {
			system("clear");
			if (G == NULL) {
				std::cout << "\nNo graph has been loaded into memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			std::vector<int> vertices;
			vertices.resize(parsedCommand.size() - 1);
			for (int i = 1; i < parsedCommand.size(); i++) {
				vertices[i] = stoi(parsedCommand[i], nullptr);
				if (G -> vertexCheck(vertices[i])) {
					list holder;
					holder.resize(G -> nNeighbours(vertices[i]));
					holder = G -> adjVertices(vertices[i]);
					std::cout << "\nThe neighbours of " << vertices[i] << " are ";
					for (int j = 1; j < holder.size(); j++) {
						if (j == holder.size() - 1) {
							std::cout << holder[j].data;
						}
						else {
							std::cout << holder[j].data << ",";
						}
					}
					std::cout << std::endl;
				}
				else {
					std::cout << "\n" << vertices[i] << " is not a node in the graph";
				}
			}
			std::cout << "\n\n >> ";
			std::getline(std::cin, command);
			continue;
		}
		else if (parsedCommand[0] == "dfs") {
			if (G == NULL) {
				std::cout << "\nNo graph exists in memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				if (parsedCommand[1] == "show") {
					int vertex = stoi(parsedCommand[2], nullptr);
					if (G -> vertexCheck(vertex) == true) {
						depthFirstSearch *newDfs = new depthFirstSearch(G, vertex, 2);
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
					else {
						std::cout << "Vertex does not exist\n";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
				else if (parsedCommand[1] == "path") {
					int vertex = stoi(parsedCommand[2], nullptr);
					int checkVertex = stoi(parsedCommand[3], nullptr);
					if (G -> vertexCheck(vertex) == true) {
						depthFirstSearch *newDfs = new depthFirstSearch(G, vertex, 3);
						bool checkFlag = newDfs -> ispath(checkVertex);
						if (checkFlag == true) {
							std::cout << "\nDFS search concludes that a path exists\nThe path is : ";
							std::vector<int> holder = newDfs -> pathTrace(checkVertex);
							std::cout << holder[holder.size() - 1];
							for (int i = holder.size() - 2; i >= 0; i--) {
								std::cout << "," << holder[i];
							}
						}
						else
							std::cout << "\nPath doesn't exist";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
					else {
						std::cout << "Vertex does not exist\n";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
				else {
					std::cout << "Incorrect Command\n";
					std::cout << "\n\n >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
		}
		else if (parsedCommand[0] == "bfs") {
			if (G == NULL) {
				std::cout << "\nNo graph exists in memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				if (parsedCommand[1] == "show") {
					int vertex = stoi(parsedCommand[2], nullptr);
					if (G -> vertexCheck(vertex) == true) {
						breadthFirstSearch *newBfs = new breadthFirstSearch(G, vertex, 2);
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
					else {
						std::cout << "Vertex does not exist\n";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
				else if (parsedCommand[1] == "path") {
					int vertex = stoi(parsedCommand[2], nullptr);
					int checkVertex = stoi(parsedCommand[3], nullptr);
					if (G -> vertexCheck(vertex) == true) {
						breadthFirstSearch *newBfs = new breadthFirstSearch(G, vertex, 3);
						bool checkFlag = newBfs -> ispath(checkVertex);
						if (checkFlag == true) {
							std::cout << "\nBFS search concludes that a path exists\nThe shortest path is : ";
							std::vector<int> holder = newBfs -> pathTrace(checkVertex);
							std::cout << holder[holder.size() - 1];
							for (int i = holder.size() - 2; i >= 0; i--) {
								std::cout << "," << holder[i];
							}
						}
						else
							std::cout << "\nPath doesn't exist";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
					else {
						std::cout << "Vertex does not exist\n";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
				else {
					std::cout << "Incorrect Command\n";
					std::cout << "\n\n >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
		}
		else if (parsedCommand[0] == "distance") {
			if (G == NULL) {
				std::cout << "\nNo graph exists in memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				if (parsedCommand.size() == 3) {
					int a = std::stoi(parsedCommand[1], nullptr);
					int b = std::stoi(parsedCommand[2], nullptr);
					if (G -> vertexCheck(a) == true && G -> vertexCheck(b) == true) {
						breadthFirstSearch *newBfs = new breadthFirstSearch(G, a, 3);
						bool checkFlag = newBfs -> ispath(b);
						if (checkFlag == true) {
							std::vector<int> holder = newBfs -> pathTrace(b);
							std::cout << "The shortest distance between the two vertices is " << holder.size() - 1;
						}
						else
							std::cout << "\nPath doesn't exist";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
					else {
						std::cout << "One/Both of the vertices does not exist\n";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
				else {
					std::cout << "Incorrect Usage\n";
					std::cout << "\n\n >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
		}
		else if (parsedCommand[0] == "diameter") {
			if (G == NULL) {
				std::cout << "\nNo graph exists in memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				if (parsedCommand.size() == 1) {
					std::vector<int> vertexList = G -> verticesList();
					int start, endNode, max;
					start = vertexList[0];
					endNode = vertexList[1];
					breadthFirstSearch *dummyBfs = new breadthFirstSearch(G, start, 3);
					std::vector<int> dummyholder = dummyBfs -> pathTrace(endNode);
					max = dummyholder.size() - 1;
					for (int i = 0; i < vertexList.size(); i++) {
						int newStart, newEnd;
						newStart = vertexList[i];
						breadthFirstSearch *newBfs = new breadthFirstSearch(G, newStart, 3);
						for (int j = i + 1; j < vertexList.size(); j++) {
							bool checkFlag = newBfs -> ispath(vertexList[j]);
							if (checkFlag) {
								std::vector<int> newHolder = newBfs -> pathTrace(vertexList[j]);
								if ((newHolder.size() - 1) > max) {
									max = (newHolder.size() - 1);
									start = newStart;
									endNode = vertexList[j];
								}
							}
						}
					}
					std::cout << "\nThe diameter of the graph is " << max << " and the last such path is:\n";
					breadthFirstSearch *finalBfs = new breadthFirstSearch(G, start, 3);
					std::vector<int> finalholder = finalBfs -> pathTrace(endNode);
					std::cout << finalholder[finalholder.size() - 1];
					for (int i = finalholder.size() - 2; i >= 0; i--) {
						std::cout << "," << finalholder[i];
					}
					std::cout << "\n\n >> ";
					std::getline(std::cin, command);
					continue;
				}
				else {
					std::cout << "Incorrect Usage\n";
					std::cout << "\n\n >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
		}
		else if (parsedCommand[0] == "write") {
			if (G == NULL) {
				std::cout << "\nNo graph exists in memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				if (parsedCommand.size() == 2) {
					std::string filename = parsedCommand[1];
					bool checkFlag = fileStatus(filename);
					if (checkFlag) {
						std::cout << "\nFile already exists. Sure to overwrite(Y/N)?\n";
						char c;
						c = getchar();
						if (c == 'Y' || c == 'y') {
							if (std::remove(filename.c_str()) == 0) {
								getchar();
								std::ofstream outfile(filename);
								std::string mainString;
								mainString = std::to_string(G -> nVertices());
								outfile << mainString;
								outfile << "\n";
								mainString = std::to_string(G -> nEdges());
								outfile << mainString;
								outfile << "\n";
								graph *counter = new graph(G -> nVertices());
								std::vector<int> vertexList = G -> verticesList();
								for (int i = 0; i < G -> nVertices(); i++) {
									list adj = G -> adjVertices(vertexList[i]);
									for (int j = 1; j < adj.size(); j++) {
										int first = vertexList[i];
										int next = adj[j].data;
										int edgeWeight = adj[j].edgeweight;
										if (!counter -> edgeCheck(first, next)) {
											counter -> addEdge(first, next);
											std::string write = std::to_string(first) + " " + std::to_string(next) + " " + std::to_string(edgeWeight);
											outfile << write;
											outfile << "\n";
										}
									}
								}
								outfile.close();
								std::cout << "\nSuccess";
								std::cout << "\n\n >> ";
								std::getline(std::cin, command);
								continue;
							}
							else {
								std::cout << "\n\nUnable to overwrite due to memory errors\n\n";
								std::cout << "\n\n >> ";
								std::getline(std::cin, command);
								continue;
							}
						}
						else if (c == 'N' || c == 'n') {
							std::cout << "\n\n >> ";
							std::getline(std::cin, command);
							continue;
						}
						else {
							std::cout << "\n\nIncorrect command\n\n";
							std::cout << "\n\n >> ";
							std::getline(std::cin, command);
							continue;
						}
					}
					else {
						std::ofstream outfile(filename);
						std::string mainString;
						mainString = std::to_string(G -> nVertices());
						outfile << mainString;
						outfile << "\n";
						mainString = std::to_string(G -> nEdges());
						outfile << mainString;
						outfile << "\n";
						graph *counter = new graph(G -> nVertices());
						std::vector<int> vertexList = G -> verticesList();
						for (int i = 0; i < G -> nVertices(); i++) {
							list adj = G -> adjVertices(vertexList[i]);
							for (int j = 1; j < adj.size(); j++) {
								int first = vertexList[i];
								int next = adj[j].data;
								int edgeWeight = adj[j].edgeweight;
								if (!counter -> edgeCheck(first, next)) {
									counter -> addEdge(first, next);
									std::string write = std::to_string(first) + " " + std::to_string(next) + " " + std::to_string(edgeWeight);
									outfile << write;
									outfile << "\n";
								}
							}
						}
						outfile.close();
						std::cout << "\nSuccess";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
				else {
					std::cout << "Incorrect Usage\n";
					std::cout << "\n\n >> ";
					std::getline(std::cin, command);
					continue;
				}
			}
		}
		else if (parsedCommand[0] == "randomweights") {
			if (G == NULL) {
				std::cout << "\nNo graph exists in memory\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
			else {
				G -> randomWeightGenerator();
				std::cout << "\nRandom weights added\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "djik") {
			if (parsedCommand.size() == 4) {
				if (parsedCommand[1] == "sd") {
					int a = std::stoi(parsedCommand[2], nullptr);
					int b = std::stoi(parsedCommand[3], nullptr);
					if (G -> vertexCheck(a) && G -> vertexCheck(b)) {
						breadthFirstSearch *newBfs = new breadthFirstSearch(G, a, 3);
						bool checkFlag = newBfs -> ispath(b);
						if (checkFlag) {
							djikstraShortestPath *newDjik = new djikstraShortestPath(G, a);
							std::cout << "The shortest distance between the vertices is " << newDjik -> shortestDistance(G, b);
							std::cout << "\n\n >> ";
							std::getline(std::cin, command);
							continue;
						}
						else {
							std::cout << "The vertices are not connected. No path exists";
							std::cout << "\n\n >> ";
							std::getline(std::cin, command);
							continue;
						}
					}
					else {
						std::cout << "One/Both vertices don't exist";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
				else if (parsedCommand[1] == "sp") {
					int a = std::stoi(parsedCommand[2], nullptr);
					int b = std::stoi(parsedCommand[3], nullptr);
					if (G -> vertexCheck(a) && G -> vertexCheck(b)) {
						breadthFirstSearch *newBfs = new breadthFirstSearch(G, a, 3);
						bool checkFlag = newBfs -> ispath(b);
						if (checkFlag) {
							djikstraShortestPath *newDjik = new djikstraShortestPath(G, a);
							std::cout << "\nThe shortest path is : ";
							newDjik -> shortestPath(G, b);
							std::cout << "\n\n >> ";
							std::getline(std::cin, command);
							continue;
						}
						else {
							std::cout << "The vertices are not connected. No path exists";
							std::cout << "\n\n >> ";
							std::getline(std::cin, command);
							continue;
						}
					}
					else {
						std::cout << "One/Both vertices don't exist";
						std::cout << "\n\n >> ";
						std::getline(std::cin, command);
						continue;
					}
				}
			}
			else {
				std::cout << "Incorrect Usage\n";
				std::cout << "\n\n >> ";
				std::getline(std::cin, command);
				continue;
			}
		}
		else if (parsedCommand[0] == "unload") {
			if (G == NULL) {
				std::cout << "\nNo graph exists in memory\n";
			}
			else {
				G = NULL;
				std::cout << "\nGraph unloaded\n\n";
			}
			std::cout << "\n\n >> ";
			std::getline(std::cin, command);
			continue;
		}
		else if (parsedCommand[0] == "quit") {
			if (G != NULL)
				delete(G);
			system("clear");
			std::cout << "\nGoodbye!\n\n";
			break;
		}
		else {
			std::cout << "Incorrect Command\n";
			std::cout << "\n\n >> ";
			std::getline(std::cin, command);
			continue;
		}
	}
	return 0;
}