//Elijah Cordova
//ejcordov
//pa4
//GraphTest.c
//Instructions: compile with List.c and Graph.c, run graphtest with one argument for test file output (./graphTest <outputfile>)

#include "Graph.h"
#include <stdlib.h>
#include <string.h>
FILE *out;

int main(int argc, char *argv[]){
  if (argc!=2){
  	printf("Usage : %s <output file>",argv[0]);
  	exit(1);
  }
  out= fopen (argv[1],"w");
  if (out == NULL){
    printf("Unable to open file output %s",argv[1]);
    exit(1);
  }
	Graph G= newGraph(10);
	fprintf(out,"ORDER:%d\n",getOrder(G));
	fprintf(out,"SIZE BEFORE INSERTIONS:%d\n",getSize(G));
    fprintf(out,"GRAPH G:\n");
    printGraph(out,G);
    fprintf(out,"\n");
	addEdge(G,1,2);
	addArc(G,2,3);
	addEdge(G,5,6);
	addEdge(G,3,4);
	addEdge(G,4,5);
	addEdge(G,6,7);
	addEdge(G,9,10);
	addEdge(G,7,8);
	addEdge(G,8,9);
	addEdge(G,10,1);
	fprintf(out,"SIZE AFTER INSERTIONS:%d\n",getSize(G));
	fprintf(out,"GRAPH G:\n");
    printGraph(out,G);
    fprintf(out,"\n");
	fprintf(out,"\n");
	for (int i=1;i<=getOrder(G);i++){
		BFS (G,i);
		List L=newList();
		getPath(L,G,getOrder(G)-i+1);
		fprintf (out,"BFS SOURCE %d, PATH FROM %d to %d: ",i,i,getOrder(G)-i+1);
		printList(out,L);
		fprintf(out,"\n");
		freeList(&L);
	}
	fprintf(out,"\n");
	for (int i=1;i<=getOrder(G);i++){
		fprintf(out,"Distance of %d:%d from Source %d\n",i,getDist(G,i),getSource(G));
		fprintf(out,"Parent of %d:%d\n",i,getParent(G,i));
	}
	fprintf(out,"\n");
	makeNull(G);
	fprintf(out,"SIZE AFTER CALLING makeNull ON G: %d",getSize(G));
	freeGraph(&G);
	fclose(out);
	return(0);
}

//EXPECTED OUTPUT:

// ORDER:10
// SIZE BEFORE INSERTIONS:0
// GRAPH G:
// 1: 
// 2: 
// 3: 
// 4: 
// 5: 
// 6: 
// 7: 
// 8: 
// 9: 
// 10: 

// SIZE AFTER INSERTIONS:10
// GRAPH G:
// 1: 2 10 
// 2: 1 3 
// 3: 4 
// 4: 3 5 
// 5: 4 6 
// 6: 5 7 
// 7: 6 8 
// 8: 7 9 
// 9: 8 10 
// 10: 1 9 


// BFS SOURCE 1, PATH FROM 1 to 10: 1 10 
// BFS SOURCE 2, PATH FROM 2 to 9: 2 1 10 9 
// BFS SOURCE 3, PATH FROM 3 to 8: 3 4 5 6 7 8 
// BFS SOURCE 4, PATH FROM 4 to 7: 4 5 6 7 
// BFS SOURCE 5, PATH FROM 5 to 6: 5 6 
// BFS SOURCE 6, PATH FROM 6 to 5: 6 5 
// BFS SOURCE 7, PATH FROM 7 to 4: 7 6 5 4 
// BFS SOURCE 8, PATH FROM 8 to 3: 8 7 6 5 4 3 
// BFS SOURCE 9, PATH FROM 9 to 2: 9 10 1 2 
// BFS SOURCE 10, PATH FROM 10 to 1: 10 1 

// Distance of 1:1 from Source 10
// Parent of 1:10
// Distance of 2:2 from Source 10
// Parent of 2:1
// Distance of 3:3 from Source 10
// Parent of 3:2
// Distance of 4:4 from Source 10
// Parent of 4:3
// Distance of 5:5 from Source 10
// Parent of 5:4
// Distance of 6:4 from Source 10
// Parent of 6:7
// Distance of 7:3 from Source 10
// Parent of 7:8
// Distance of 8:2 from Source 10
// Parent of 8:9
// Distance of 9:1 from Source 10
// Parent of 9:10
// Distance of 10:0 from Source 10
// Parent of 10:-3

// SIZE AFTER CALLING makeNull ON G: 0

