//Elijah Cordova
//ejcordov
//pa5
//FindComponents.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#define MAX_LEN 1000

FILE *in, *out;
 // main()
 // pre:
 // post: reads file input, and performs approproiate operations
int main(int argc, char *argv[]){
  if (argc!=3){
  	printf("Usage : %s <input file> <output file>\n",argv[0]);
  	exit(1);
  }

  in = fopen (argv[1],"r");
  if (in == NULL){
    printf("Unable to open file input %s",argv[1]);
    exit(1);
  }


  out= fopen (argv[2],"w");
  if (out == NULL){
    printf("Unable to open file output %s",argv[2]);
    exit(1);
  }

  int input1;
  int input2;
  //scans the 1st line : Graph Order
  fscanf (in,"%d",&input1);
  Graph G= newGraph(input1);
  fprintf(out,"Adjacency list representation of G:\n");
  //Scans the next set of lines :Graph Vertices, terminates when line1 and line2=0
  while(fscanf (in,"%d %d",&input1,&input2) != EOF && (input1 != 0 && input2 !=0)){
    addArc(G,input1,input2);
  }
  printGraph(out,G);
  fprintf(out,"\n");
  List L= newList();
  for (int i=1;i<=getOrder(G);i++){
    append(L,i);
  }
  DFS(G,L);
  Graph GT= transpose(G);
  DFS(GT,L);
  int SCC=0;
  for (int i=1;i<=getOrder(GT);i++){
    if(getParent(GT,i)==NIL){
      SCC++;
    }
  }

  List *SCCL;
  SCCL=calloc(SCC+1,sizeof(List));
  for(int i=1;i<=SCC;i++){
    SCCL[i]=newList();
  }
  int count=1;

  moveBack(L);
  for (int i=1;i<=getOrder(G);i++){
    prepend(SCCL[count],get(L));
    if (getParent(GT,get(L))==NIL){
      count++;
    }
    movePrev(L);
  }
  fprintf(out,"G contains %d strongly connected components:\n",SCC);
  for (int i=1;i<=SCC;i++){
    fprintf(out,"Component %d: ",i);
    printList(out,SCCL[i]);
    fprintf(out,"\n");
  }
  

  freeList(&L);
  for (int i=1;i<=SCC;i++){
    freeList(&SCCL[i]);
  }
  free(SCCL);
  freeGraph(&G);
  freeGraph(&GT);
  fclose(in);
  fclose(out);
  return(0);
}