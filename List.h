//----------------------------------
// List.h                          |
// Header file for List ADT        |
//                                 |
// Robert Mushkot                  |
// rmushkot                        |
// 1543374                         |
// pa4                             |
// ---------------------------------


#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;
typedef struct NodeObj* Node;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);
Node newNode(int data);

// freeList()
// Frees all heap memory associated with list *pL, and sets *pL to NULL.
void freeList(List* pL);
void freeNode(Node* pN);


//  Access functions -----------------------------------------------------------

//  length()
//  Returns the length of L
int length(List L);

//  index()
//  Returns index of the cursor
int index(List L);

//  front()
//  Returns the value at the front of L.
int front(List L);

//  back()
//  Returns the value at the back of L.
int back(List L);

//  get()
//  returns the value at the cursor
int get(List L);

//  equals()
//  returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);


//  Manipulation procedures ----------------------------------------------------

//  clear()
//  clears/empties the list
void clear(List L);

//  moveFront()
//  move the cursor to the front of L
void moveFront(List L);


//  moveBack()
//  move the cursor to the back of L
void moveBack(List L);

//  movePrev()
//  moves the cursor one element backward
void movePrev(List L);

//  moveNext()
//  moves the cursor one element forward
void moveNext(List L);

//  prepend()
//  Places new data element at the front of L
void prepend(List L, int data);
  
//  append()
//  Places new data element at the back of L
void append(List L, int data);

//  insertBefore()
//  inserts the data element before the cursor
void insertBefore(List L, int data);

//  insertAfter()
//  inserts the data element after the cursor
void insertAfter(List L, int data);

//  deleteFront()
//  deleted the front element from L
void deleteFront(List L);

//  deleteBack()
//  deletes the back element from L
void deleteBack(List L);

//  delete()
//  deletes the cursor element from L
void delete(List L);

 

//  Other Functions ------------------------------------------------------------
//
//  printList()
//  Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

//  copyList
//  returns a new list that is an axact copy of L
List copyList(List L);

#endif

