//Elijah Cordova
//ejcordov
//pa4
//FindPath.c


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
  	printf("Usage : %s <input file> <output file>",argv[0]);
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
  //Scans the next set of lines :Graph Vertices
  while(fscanf (in,"%d %d",&input1,&input2) != EOF && (input1 != 0 && input2 !=0)){
    addEdge(G,input1,input2);
  }
  printGraph(out,G);
  //Scans the next set of lines : Graph Queries
  while(fscanf (in,"%d %d",&input1,&input2) != EOF && (input1 != 0 && input2 !=0)){
  	 fprintf(out,"\n");
     List L=newList();
     BFS(G,input1);
     getPath(L,G,input2);
     if (getDist(G,input2)!=INF){
     	fprintf(out,"The distance from %d to %d is %d\n",input1,input2,getDist(G,input2));
        fprintf(out,"The shortest %d-%d path is:",input1,input2);
        printList(out,L);
         } else{
        fprintf(out,"The distance from %d to %d is infinity\n",input1,input2);
        fprintf(out,"No %d-%d path exists",input1,input2);	
     }
        freeList(&L);
  }
  freeGraph(&G);
  fclose(in);
  fclose(out);
  return(0);
}