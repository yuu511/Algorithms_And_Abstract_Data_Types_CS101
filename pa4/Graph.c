// Elijah Cordova
// ejcordov
// pa4
// Graph.c
#include "Graph.h"
#include <stdlib.h>
#include <string.h>

typedef struct GraphObj{
	int order;
	int size;
	int source;
	List* matrix;
	int* parent;
	int* distance;
	char* color;
}GraphObj;

// newGraph(int n);
// pre: n>0
// post: creates new graph with Order n
Graph newGraph(int n){
	  Graph G = calloc(1,sizeof(GraphObj));
	  G -> matrix = calloc (n+1,sizeof(List));
	  G -> parent = calloc (n+1,sizeof(int));
	  G -> distance = calloc (n+1,sizeof(int));
	  G -> color = calloc (n+1,sizeof(int));
	  G->order= n;
	  G->size = 0;
	  G->source = NIL;
	  for (int i=1;i<=n;i++){
	  G->matrix[i]=newList();
	  G->parent[i]=NIL;
	  G->distance[i]=INF;
	  G->color[i]='W';
	  }
	  return G;
}

// freeGraph(Graph* pG)
// pre: graph must not be null
// post: frees all memory associated with specified graph
void freeGraph(Graph* pG){
	if (pG!=NULL && *pG!=NULL){
		for (int i=1;i<=getOrder(*pG);i++){
			freeList(&((*pG)->matrix[i]));
		}
	  free((*pG)->parent);
      free((*pG)->distance);
      free((*pG)->matrix);
      free((*pG)->color);
	  free(*pG);
      *pG=NULL;
	}
}

// getOrdeR(Graph G)
// pre: G must not be null
// post: returns order of graph G.
int getOrder(Graph G){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	}
	return G->order;
}

// getSize(Graph G)
// pre: G must not be null
// post: returns size of graph G (# of edges)
int getSize(Graph G){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	}
	return G->size;
}

// getSource (Graph G)
// pre: G must not be null, G must have BFS performed on it
// post: returns the source of BFS on graph G
int getSource (Graph G){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	}
	return G->source;
}

// getParent(Graph G, int u);
// pre: G must not be null, u must be an existing vertice in the graph, G must have BFS performed on it
// post: returns parent of specified vertice u based on the last BFS
int getParent (Graph G,int u){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	} else if ((u<1|| u>getOrder(G))&& (u!=NIL)){
		printf ("Invalid parameters for u!");
  	    exit (1);
    }
	return G->parent[u];
}

//  GetDist(Graph G, int u)
// pre: G must not be null, u must be an existing vertice on the graph, G must have BFS performed on it
// post: returns distance of vertice u from the source of the last BFS

int getDist (Graph G,int u){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	} else if (u<1|| u>getOrder(G)){
		printf ("Invalid parameters for u!");
  	    exit (1);
    }
	return G->distance[u];
}

// getPath( List L, graph G, int u)
// pre: G must not be null, u must be an existing vertice on the graph, G must have BFS performed on it
// post: finds shortest path of vertice u from source and writes it in a list (Based on last BFS)
void getPath(List L, Graph G, int u){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	} else if (u<1|| u>getOrder(G)){
		printf ("Invalid parameters for u!");
  	    exit (1);
    }

    if (getSource(G)==u){
      prepend(L,u);
      return;
    } else if(getParent(G,u)==NIL){
      append(L,INF);
      return;
    } else{
    	getPath(L,G,getParent(G,u));
    	append(L,u);
    }
}

// makeNull (Graph G)
//pre:
//post: removes all edges from matrix G

void makeNull(Graph G){
	for (int i=1;i<=getOrder(G);i++){
      clear(G->matrix[i]);
      G->parent[i]=NIL;
	  G->distance[i]=INF;
	  G->color[i]='W';
	}
	G->size=0;
	G->source=NIL;
}

// addArc(Graph G,int u,int v)
// pre: G is not null, u and v are valid vertices within G
// post: adds directed edge from u to v
void addArc(Graph G, int u, int v){
  if (u<1 || u>getOrder(G)){
  	printf ("Invalid parameters for u!");
  	exit (1);
  } else if (v<1 || v>getOrder(G)){
  	printf ("Invalid parameters for v!");
  	exit (1);
  } else  if (G==NULL){
  	printf ("addARC called on NULL GRAPH");
  	exit(1);
  }

  if (getSize(G)==0){
  	append (G->matrix[u],v);
    G->size++;
  	return;
  }
  moveFront (G->matrix[u]);
  while (index(G->matrix[u])!=-1){
  	if (get(G->matrix[u])>v){
  		insertBefore(G->matrix[u],v);
  		G->size++;
  		break;
  	}
    moveNext(G->matrix[u]);
  }
  if (index(G->matrix[u])==-1){
  	append (G->matrix[u],v);
  	G->size++;
  }
}

// addEdge(Graph G,int u,int v)
// pre: G is not null, u and v are valid vertices within G
// post: adds undirected edge from u to v
void addEdge(Graph G, int u, int v){
  if (u<1 || u>getOrder(G)){
  	printf ("Invalid parameters for u!");
  	exit (1);
  }
  if (v<1 || v>getOrder(G)){
  	printf ("Invalid parameters for v!");
  	exit (1);
  }
  addArc (G,u,v);
  addArc (G,v,u);
  G->size--;
}

// BFS(Graph G, int s)
// pre: G is not null, s is a valid vertice in graph G
// post: performs Breadth first search in graph G with source s.
void BFS (Graph G, int s){
  int current;
  if (G ==NULL){
  	printf("BFS called on NULL graph!");
  	exit(1);
  } else if (s<1||s>getOrder(G)){
  	printf("wrong parameters for s in BFS!");
  	exit(1);
  }
  for (int i=1;i<=getOrder(G);i++){
  	  G->parent[i]=NIL;
	  G->distance[i]=INF;
	  G->color[i]='W';
  }
  List Queue= newList();
  G->color[s]='B';
  G->source=s;
  G->distance[s]=0;
  append(Queue,s);
  while(length(Queue)!=0){
  	moveFront(Queue);
    current=get(Queue);
    deleteFront(Queue);
    moveFront(G->matrix[current]);
    while (index(G->matrix[current])!=-1 ){
    	if (G->color[get(G->matrix[current])]=='W'){
    		G->color[get(G->matrix[current])]='B';
    		G->distance[get(G->matrix[current])]=G->distance[current]+1;
    		G->parent[get(G->matrix[current])]=current;
    		append(Queue,get(G->matrix[current]));
    		moveNext(G->matrix[current]);
        } else {
        	moveNext(G->matrix[current]);
        }
          G->color[current]='B';
        }     
    }
  freeList(&Queue);
}

// PrintGraph (file * out , graph G)
// pre: 
// post: prints out graph to specified file
void printGraph(FILE* out, Graph G){
  for (int i=1;i<=getOrder(G);i++){
  	fprintf(out,"%d: ",i);
  	printList(out,G->matrix[i]);
  	fprintf(out,"\n");
  }
}






