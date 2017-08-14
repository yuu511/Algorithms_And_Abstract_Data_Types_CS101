// Elijah Cordova
// ejcordov
// pa5
// Graph.c
#include "Graph.h"
#include <stdlib.h>
#include <string.h>

typedef struct GraphObj{
	int order;
	int size;
	List* matrix;
	int* parent;
	int* discover;
	int* finish;
	char* color;
}GraphObj;

// newGraph(int n);
// pre: n>0
// post: creates new graph with Order n
Graph newGraph(int n){
	  Graph G = calloc(1,sizeof(GraphObj));
	  G -> matrix = calloc (n+1,sizeof(List));
	  G -> parent = calloc (n+1,sizeof(int));
	  G -> discover = calloc (n+1,sizeof(int));
	  G -> finish = calloc (n+1,sizeof(int));
	  G -> color = calloc (n+1,sizeof(char));
	  G->order= n;
	  G->size = 0;
	  for (int i=1;i<=n;i++){
	  G->matrix[i]=newList();
	  G->parent[i]=NIL;
    G->discover[i]=UNDEF;
    G->finish[i]=UNDEF;
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
	  free((*pG)->matrix);	
	  free((*pG)->parent);
    free((*pG)->discover);
    free((*pG)->finish);
    free((*pG)->color);
	  free(*pG);
    *pG=NULL;
	}
}

// getOrder(Graph G)
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


// getParent(Graph G, int u);
// pre: G must not be null, u must be an existing vertice in the graph, G must have DFS performed on it
// post: returns parent of specified vertice u based on the last DFS
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

// getDiscover(Graph G, int u);
// pre: G must not be null, u must be an existing vertice in the graph, G must have DFS performed on it
// post: returns discover time of specified vertice u based on the last DFS
int getDiscover (Graph G,int u){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	} else if ((u<1|| u>getOrder(G))&& (u!=NIL)){
		printf ("Invalid parameters for u!");
  	    exit (1);
    }
	return G->discover[u];
}

// getDiscover(Graph G, int u);
// pre: G must not be null, u must be an existing vertice in the graph, G must have DFS performed on it
// post: returns finish time of specified vertice u based on the last DFS
int getFinish (Graph G,int u){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	} else if ((u<1|| u>getOrder(G))&& (u!=NIL)){
		printf ("Invalid parameters for u!");
  	    exit (1);
    }
	return G->finish[u];
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

//helper function for DFS (below)
void traverse(int *time,int x,List S,Graph G){
  G->color[x]='G'; 
  (*time)++;
  G->discover[x]=*time;
  moveFront(G->matrix[x]);
  while (index(G->matrix[x])!=-1){
    if (G->color[get(G->matrix[x])]=='W'){
    	G->parent[get(G->matrix[x])]=x;
    	traverse (time,get(G->matrix[x]),S,G);
    }
    moveNext(G->matrix[x]);
  }
  G->color[x]='B';
  (*time)++;
  G->finish[x]=*time;
  insertAfter(S,x);
}


// DFS (Graph G, List S)
// Pre: length(S)==getOrder(G)
// Post: Performs dfs in graph G and records discover and finish times. 
void DFS(Graph G, List S){
  if (G ==NULL){
  	printf("BFS called on NULL graph!");
  	exit(1);
  } else if (length(S)!=getOrder(G)){
  	printf("wrong parameters for s in DFS!");
  	exit(1);
  }
  for (int i=1;i<=getOrder(G);i++){
	 G->parent[i]=NIL;
	 G->color[i]='W';
   G->discover[i]=UNDEF;
   G->finish[i]=UNDEF;
  }
  int time =0;
  moveBack(S);
    for (int i=1;i<=getOrder(G);i++){
      if(G->color[front(S)]=='W'){
	    traverse(&time,front(S),S,G);
	  }
	  deleteFront(S);
  }
}



// transpose (Graph G)
// pre: G is not null
// post: returns transpose of graph G
Graph transpose(Graph G){
  Graph graphT=newGraph(getOrder(G));
  for (int i=1;i<=getOrder(G);i++){
  	for (moveFront(G->matrix[i]);index(G->matrix[i])>=0;moveNext(G->matrix[i])){
      addArc(graphT,get(G->matrix[i]),i);
    }
  }
  return graphT;
}

// copyGraph (Graph G)
// pre: G is not null
// post: returns copy of graph G
Graph copyGraph(Graph G){
  Graph graphC=newGraph(getOrder(G));
  for (int i=1;i<=getOrder(G);i++){
  	for (moveFront(G->matrix[i]);index(G->matrix[i])>=0;moveNext(G->matrix[i])){
      addArc(graphC,i,get(G->matrix[i]));
    }
  }
  return graphC;
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