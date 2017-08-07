// Elijah Cordova
// ejcordov
// pa4
// Graph.h

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include <stdio.h>
#include "List.h"
#define INF -2
#define NIL -3

typedef struct GraphObj* Graph;

// Constructors-Destructors

//Creates a new Graph with order N
Graph newGraph(int n);
//Frees up all memory created by graph in the heap
void freeGraph(Graph* pG);

// Access functions 

//Gets order of graph G: pre: G is not NULL
int getOrder(Graph G);
//Gets size of graph G: pre: G is not NULL
int getSize(Graph G);
//Gets source of graph G: pre : G is not NULL, G has had BFS(G,s) performed on it
int getSource(Graph G);
//Gets parent of specified vertice: pre : G is not NULL, G has had BFS(G,s) performed on it, u is within the order of G
int getParent(Graph G, int u);
//Gets source of graph G: pre : G is not NULL, G has had BFS(G,s) performed on it, u is within the order of G
int getDist(Graph G, int u);
//Gets source of graph G: pre : G is not NULL, G has had BFS(G,s) performed on it,u is within the order of G
void getPath(List L, Graph G, int u);

// Manipulation procedures

//Clears all edges from graph 
void makeNull(Graph G);
//Add edge u->v in specified graph, pre:G is not NULL, u and v must be within the order of G
void addEdge(Graph G, int u, int v);
//Add arc u->v in specified graph, pre:G is not NULL, u and v must be within the order of G
void addArc(Graph G, int u, int v);
//Add BFS with source s, pre:G is not NULL, s must be within the order of G
void BFS(Graph G, int s);
// Other Operations
//Print out graph to specified output file.
void printGraph(FILE* out, Graph G);

#endif