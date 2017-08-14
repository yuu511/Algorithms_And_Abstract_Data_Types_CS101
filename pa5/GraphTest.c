//ELijah Cordova
//ejcordov
//pa5
//GraphTest.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#define MAX_LEN 1000

FILE *out;
 // main()
 // pre:
 // post: reads file input, and performs approproiate operations
int main(int argc, char *argv[]){
  if (argc!=2){
  	printf("Usage : %s <output file>",argv[0]);
  	exit(1);
  }

  out= fopen (argv[1],"w");
  if (out == NULL){
    printf("Unable to open file output %s",argv[2]);
    exit(1);
  }

  Graph G= newGraph(8);
  addArc(G,1,2);
  addArc(G,2,3);
  addArc(G,2,5);
  addArc(G,2,6);
  addArc(G,3,4);
  addArc(G,3,7);
  addArc(G,4,3);
  addArc(G,4,8);
  addArc(G,5,1);
  addArc(G,5,6);
  addEdge(G,6,7);
  addArc(G,7,8);
  addArc(G,8,8);
  fprintf(out,"-GRAPH TEST-\n");
  fprintf(out,"graph 1: order %d,size %d\n",getOrder(G),getSize(G));
  printGraph(out,G);
  fprintf(out,"graph 1 copy:\n");
  Graph GC=copyGraph(G);
  printGraph(out,GC);
  fprintf(out,"graph 1 transpose:\n");
  Graph GT= transpose(G);
  printGraph(out,GT);
  fprintf(out,"\nG contains d strongly connected components:\n");
  freeGraph(&G);
  freeGraph(&GT);
  freeGraph(&GC);
  fclose(out);
  return(0);
}