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

int getOrder(Graph G){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	}
	return G->order;
}

int getSize(Graph G){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	}
	return G->size;
}

int getSource (Graph G){
	if (G == NULL ){
		printf ("G CALLED ON NULL GRAPH.");
		exit (1);
	}
	return G->source;
}

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


void printGraph(FILE* out, Graph G){
  for (int i=1;i<=getOrder(G);i++){
  	fprintf(out,"%d: ",i);
  	printList(out,G->matrix[i]);
  	fprintf(out,"\n");
  }
}






