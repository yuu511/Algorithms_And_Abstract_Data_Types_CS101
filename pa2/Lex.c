//-----------------------------------------------------------------------------
// Lex.c
// arranges up to 1001 different strings in lexical order
//-----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#define MAX_LEN 1001

FILE *in, *out;

 /*
  * performOperations (char** words, int amountOfWords)
  * preconditions: String array containing words to be sorted.
  * postconditions: reads an array, sorts the indices into a list, then prints it out on the specified 
  * output file in lexical order.
  */

void performOperations(char** words,int amountOfWords){
  List N = newList();
  append(N,0);
  for (int i=1;i<amountOfWords;i++){
    moveBack(N);
    char key[256];
    strcpy(key,words[i]);
    int j;
    for (j=i-1; j>=0 && strcmp(key,words[get(N)])<0;j--){
       movePrev(N);
    }
    if (get(N)==-1){
      prepend(N,i);    
    }
    else{
      insertAfter(N,i);    
    }
  }

  for(moveFront(N); index(N)>=0; moveNext(N)){
    fprintf(out,"%s",words[get(N)]);
  }

//Frees and clears all memory of list. 
  clear(N);
  freeList(&N);
}

 /*
  *main()
  *pre:
  *post: reads file input, stores it in array, and sends it to performOperations()
  */

int main(int argc, char *argv[]){
  char line[MAX_LEN];
  int count=0;
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
  
  char* Strings[MAX_LEN];

//allocates the appropriate amount of memory dynamically for strings
  while( fgets(line, MAX_LEN, in) != NULL){
        Strings[count]=calloc(256,sizeof(char*)); 
        strcpy(Strings[count],line);
        count++;
  }

  performOperations(Strings,count);

//Frees all memory of input array.
  for(int i=0;i<count;i++){
    free(Strings[i]);
  }

  fclose(in);
  fclose(out);
  return(0);
}