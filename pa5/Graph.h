// Elijah Cordova
// ejcordov
// pa5
// Graph.h

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include <stdio.h>
#include "List.h"
#define INF -2
#define NIL -3


typedef struct GraphObj* Graph;

// Constructors-Destructors 
Graph newGraph(int n);
//Frees up all memory created by graph in the heap
void freeGraph(Graph* pG);

// Access functions 
//Gets order of graph G: pre: G is not NULL
int getOrder(Graph G);
//Gets size of graph G: pre: G is not NUL
int getSize(Graph G);
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u); 
// Pre: 1<=u<=n=getOrder(G) 
int getDiscover(Graph G, int u); 
// Pre: 1<=u<=n=getOrder(G) 
int getFinish(Graph G, int u); 

// Manipulation procedures 
// Pre: 1<=u<=n, 1<=v<=n 
void addArc(Graph G, int u, int v); 
// Pre: 1<=u<=n, 1<=v<=n 
void addEdge(Graph G, int u, int v); 
// Pre: length(S)==getOrder(G) 
void DFS(Graph G, List S); 
/* Other Functions */

// returns transpose of Graph G. pre: G is not null
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif

