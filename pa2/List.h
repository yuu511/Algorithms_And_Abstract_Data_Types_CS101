//-----------------------------------------------------------------------------
// List.h
// Header file for the List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include <stdio.h>
typedef struct ListNode* Node;
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

//Creates new list
List newList(void);
//Frees up memory of List Specified
void freeList(List* pL);

// Access functions -----------------------------------------------------------

//Returns Lenth of list
int length(List L);

//Returns index of list
int index(List L);

//Returns data of front of list
int front(List L);

//Returns data of back of list
int back(List L);

 //Returns data of cursor of list, Will return -1 if cursor is null.
 int get(List L);

/* Checks to see if two lists are equal to eachother:
 * a value of 1 singnifies they are equal,
 * a value of 0 signifies they are not.
 */
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

/*
 *Resets Cursor and index of cursor value
 *(freeList deletes the actual nodes)
 */
void clear(List L);

//Moves Cursor to Front
void moveFront(List L);

//Moves Cursor to back
void moveBack(List L);

//Decrements cursor by 1 (out of bounds cursor= cursor gets set to null)
void movePrev(List L);

//Increments cursor by 1
void moveNext(List L);

//adds new value to the front of the list
void prepend(List L, int data);

//adds new value to the back of the list
void append(List L, int data);

//adds new value before value the cursor is pointing to
void insertBefore(List L, int data);

//adds new value after value the cursor is pointing to
void insertAfter(List L, int data);

//deletes value in front of list
void deleteFront(List L);

//deletes value in back of list
void deleteBack(List L);

//delete value cursor is currently pointing at, and sets cursor to null
void delete(List L);

// Other operations -----------------------------------------------------------

//print out list to specified file.
void printList(FILE* out, List L);

//creates a copy of specified list.
List copyList(List L);

#endif