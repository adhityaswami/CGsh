# CGsh

Combinatorial Graph Shell

Winter Internship Project at IIT Madras, supervised by Prof. Rupesh Nasre.

Purely for academic purposes. It's pretty feature rich.

I've tested as much as possible for segfaults. If any arise, do let me know at: adhitya.s.met15@itbhu.ac.in 

Run "make all" or "make graph" to compile. "make clean" deletes the binary.

./graph to run the program

Algorithms implemented are :

1) DFS algorithm
2) BFS algorithm
3) Dijkstra's Shortest Path algorithm

Currently only works with integers data values for the graph, but I'm pretty sure it can be modified to work with any composite structure. Scales to quite an extent, but becomes slow for certain functions at such densities. Eg : Diameter works practically only for small graphs.