//-----------------------------------------------------------------------------
// List.c
// implementation file for the List ADT
//-----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

//Node + new Node Constructor

typedef struct ListNode{
  int data;
  struct ListNode* next;
  struct ListNode* previous;
}ListNode;

//allocates the appropriate amount of memory for new nodes
Node newNode(int data){
  Node N= malloc(sizeof(ListNode));
  N->data=data;
  N->next = NULL;
  N->previous = NULL;
  return N;
}

 /*
  * void freeNode (Node *N)
  * pre: Node to be freed
  * post: frees memory in specified node.
  */
void freeNode (Node *N){
  if (*N!=NULL && N!=NULL){
    free (*N);
    N=NULL;
  }
}


//List + new List Constructor

typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int size;
  int cursorIndex;
}ListObj;


	
List newList(void){
  List L = malloc(sizeof(ListObj));
  L->front= NULL;
  L->back= NULL;
  L->cursor= NULL;
  L->size=0;
  return L;
}
 /*
  * void freeList (List pL)
  * pre: List to be freed
  * post: frees memory of all nodes of specified list,
  * and frees memory of the list itself.
  */
void freeList(List* pL){
   if( pL!=NULL && *pL!=NULL){
    Node N = (*pL)->front; 
    Node temp;
    while(N != NULL){
    temp = N->next;
    N->previous=NULL;
    freeNode(&N);
    N = temp; 
    }
    freeNode(&N);
    free(*pL);
     *pL = NULL;
   }
}

//Access Functions

//returns length of list
int length(List L){
  return L->size;
}


//returns index of cursor
int index(List L){
  if (L->cursor != NULL){
  return L->cursorIndex;
  }
  return -1;
}

/*
 * front(): returns front
 * preconditions : length()>0
 * postconditions: returns data from front
 */

int front(List L){
  return L->front->data;
}


/*
 * back(): returns back
 * preconditions : length()>0
 * postconditions: returns data from back
 */

int back(List L){
  return L->back->data;
}

 /*
  * returns data of cursor
  * precondtions: length()>0, index()>=0
  * postconditions: returns data of cursor
  */
int get(List L){
  if(L->cursor != NULL){
  	return L->cursor->data;
  }
  return -1;
}


/*
 * equals(List)
 * compares two lists to see if they are the same
 * precondtions: another List L
 * postconditions: returns true or false for if the two lists are the same
 */
int equals(List A, List B){
 if (A->size==B->size){
   Node firstFront=A->front;
   Node secondFront=B->front;
   for(moveFront(A); index(A)>=0; moveNext(A)){
     if (firstFront->data!=secondFront->data){
      return 0;
     }
   }
   return 1;
 }
 return 0;
}

// Manipulation procedures

//resets the size + cursor of list.
void clear(List L){
  L->size=0;
  L->cursor=NULL;
}

void moveFront(List L){
  if (L->size > 0){
  	L->cursor=L->front;
  	L->cursorIndex=0;
  }
}

//moves cursor to front
void moveBack(List L){
  if (L->size >0){
	L->cursor=L->back;
	L->cursorIndex=L->size-1;
  }
}

//moves cursor to back
void movePrev(List L){
  if (L->cursor != NULL){
    if (L->cursor==L->front){
    	L->cursor= NULL;
    }
    else{
    	L->cursor= L->cursor->previous;
    	L->cursorIndex--;
    }
  }
}

// moves cursor one step towards the front, if at front, moves cursor
// to undefined,if cursor is undefined, does nothing
void moveNext(List L){
  if (L->cursor != NULL){
    if (L->cursor==L->back){
    	L->cursor= NULL;
    }
    else{
    	L->cursor= L->cursor->next;
    	L->cursorIndex++;
    }
  }
}

/*
 * prepend(int)
 * preconditions: list must be created, paramater int for data to be inserted
 * postconditions: inserts data before front element, if list
 * is empty places data at the front and back (because size=1 after insertion)
 */
void prepend(List L, int data){
  Node N=newNode(data);
  if (L->size==0){
    L->front=N;
    L->back=N;
  }
  else{
    L->front->previous=N;
    N->next=L->front;
    L->front=N;
  }
  if (L->cursor!= NULL){
    L->cursorIndex++;
  }
  L->size++;
}

 /*
  * append(int)
  * preconditions: list must be created, paramater int for data to be inserted
  * postconditions: inserts data after back element, if list
  * is empty places data at front and back (because size=1 after insertion)
  */

void append(List L, int data){
  Node N=newNode(data);
  if (L->size==0){
    L->front=N;
    L->back=N;
  }
  else{
    L->back->next=N;
    N->previous=L->back;
    L->back=N;
  }
  L->size++;
}

/*
 * void insertBefore(int)
 * preconditions: length()>0 index >=0
 * postconditions: inserts new element before cursor.
 */

void insertBefore(List L, int data){
  if (L->cursor!=NULL){
  	if (L->cursor==L->front){
  		prepend(L,data);
  	}
  	else{
      Node N=newNode(data);
  	  L->cursor->previous->next=N;
  	  N->previous=L->cursor->previous;
  	  N->next=L->cursor;
  	  L->cursor->previous=N;
  	  L->size++;
  	  L->cursorIndex++;
  	}
  }
}


/*
 * void insertAfter(int)
 * preconditions: length()>0 index >=0
 * postconditions: inserts new element after cursor.
 */
void insertAfter(List L, int data){
  if (L->cursor!=NULL){
  	if (L->cursor==L->back){
  		append(L,data);
  	}
  	else{
      Node N=newNode(data);
  	  L->cursor->next->previous=N;
  	  N->next=L->cursor->next;
  	  N->previous=L->cursor;
  	  L->cursor->next=N;
  	  L->size++;
  	}
 }
}

/*
 * void deleteFront()
 * preconditions: length()>0
 * postconditions: delete front number 
 */
void deleteFront(List L){
  if (L->cursor==L->front){
    L->cursor=NULL;
  }

  if (L->size>1){
    L->front=L->front->next;
    L->front->previous->next=NULL;
    freeNode(&(L->front->previous));
    L->front->previous=NULL;
    L->size--;
  }
  else if (L->size==1){
    freeNode(&(L->front));
    L->front=NULL;
    L->back=NULL;
    L->size--;
  }

  if (L->cursor!=NULL){
    L->cursorIndex--;
  }
}

/*
 *  void deleteBack() 
 *
 *  preconditions: length()>0
 *  postconditions: delete back number 
 */

void deleteBack(List L){
  if (L->cursor==L->back){
    L->cursor=NULL;
  }

  if (L->size>1){
    L->back=L->back->previous;
    L->back->next->previous=NULL;
    freeNode(&(L->back->next));
    L->back->next=NULL;
    L->size--;
  }
  else if (L->size==1){
    freeNode(&(L->back));
    L->front=NULL;
    L->back=NULL;
    L->size--;
  }
}

/* void delete()
 *  preconditions: length()>0 index()>0
 *  postconditions: delete current item at cursor
 */

void delete(List L){
  if (L->cursor!=NULL){
    if  (L->cursor==L->front){
      deleteFront(L);
    }
    else if (L->cursor == L->back){
      deleteBack(L);
    }
    else{
      L->cursor->previous->next=L->cursor->next;
      L->cursor->next->previous=L->cursor->previous;
      freeNode (&(L->cursor));
      L->cursor=NULL;
      L->size--;
    }
  }
}


//OTHER METHODS

/*
 * copy()
 * precondtions: File to be outputted to, List L
 * postcondtions: prints out list contents to specified file.
 */

void printList(FILE* out, List L){
   for(moveFront(L); index(L)>=0; moveNext(L)){
      fprintf(out,"%d ", get(L));
   }
}

/*
 * copyList()
 * precondtions: List L
 * postcondtions: returns copy of list.
 */

List copyList(List L){
  List copy= newList();
  Node tempN = L->cursor;
  int tempI = L->cursorIndex;
  for(moveFront(L); index(L)>=0; moveNext(L)){
      append(copy,get(L));
   }
   L->cursor = tempN;
   L->cursorIndex = tempI;
   return copy;
}