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
  printGraph(out,G);
  List newL=newList();
  for (int i=1;i<=8;i++){
    append(newL,i);
  }
  DFS(G,newL);
  fprintf(out,"\nafter preforming DFS on G:\n");
  for (int i=1;i<=getOrder(G);i++){
    fprintf(out,"Vertex %d Parent % d Discover %d Finish % d\n",i,getParent(G,i),getDiscover(G,i),getFinish(G,i));
  }
  freeGraph(&G);
  freeGraph(&GT);
  freeGraph(&GC);
  freeList(&newL);
  fclose(out);
  return(0);
}

// Expected output:
// -GRAPH TEST-
// graph 1: order 8,size 13
// 1: 2 
// 2: 3 5 6 
// 3: 4 7 
// 4: 3 8 
// 5: 1 6 
// 6: 7 
// 7: 6 8 
// 8: 8 
// graph 1 copy:
// 1: 2 
// 2: 3 5 6 
// 3: 4 7 
// 4: 3 8 
// 5: 1 6 
// 6: 7 
// 7: 6 8 
// 8: 8 
// graph 1 transpose:
// 1: 2 
// 2: 3 5 6 
// 3: 4 7 
// 4: 3 8 
// 5: 1 6 
// 6: 7 
// 7: 6 8 
// 8: 8 

// after preforming DFS on G:
// Vertex 1 Parent -3 Discover 1 Finish  16
// Vertex 2 Parent  1 Discover 2 Finish  15
// Vertex 3 Parent  2 Discover 3 Finish  12
// Vertex 4 Parent  3 Discover 4 Finish  7
// Vertex 5 Parent  2 Discover 13 Finish  14
// Vertex 6 Parent  7 Discover 9 Finish  10
// Vertex 7 Parent  3 Discover 8 Finish  11
// Vertex 8 Parent  4 Discover 5 Finish  6