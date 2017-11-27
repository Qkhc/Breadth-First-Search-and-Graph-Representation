//----------------------------------
// List.c                          |
// Implementation for List ADT     |
//                                 |
// Robert Mushkot                  |
// rmushkot                        |
// 1543374                         |
// pa4                             |
// ---------------------------------


#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
	if( pN!=NULL && *pN!=NULL ){
		free(*pN);
		*pN = NULL;
	}
}


// newList()
// Returns reference to new empty List object.
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	return(L);
}


// freeList()
// Frees all heap memory associated with list *pL, and sets *pL to NULL.
void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL){

		clear(*pL);
		
		free(*pL);
		*pL = NULL;
	}
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L
int length(List L){
	if(L == NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->length);
}

// index()
int index(List L){
	if(L == NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	if(L->cursor == NULL){
		return -1;
	}

	int i = 0;
	Node N = L->front;

	while(N != L->cursor && N != NULL){
		N = N->next;
		i++;
	}
	N = NULL;
	return i;
}
		

// front()
// Returns the value at the front of L.
int front(List L){

	if(L == NULL){
                printf("List Error: calling front() on NULL List reference\n");
                exit(1);
        }

	if(length(L) == 0){
		printf("List Error: calling front() no empty list\n");
		exit(1);
	}
	
	 return L->front->data;
}


// back()
// Returns the value at the back of L.
int back(List L){
	if(L == NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}

	if(length(L) == 0){
		printf("List Error: calling back()on empty list\n");
		exit(1);
	}
	
	return L->back->data;
}



// get()
// returns the value at the cursor
int get(List L){
	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}

	if(length(L) == 0){
                printf("List Error: calling get() no empty list\n");
		exit(1);
        }

	return L->cursor->data;
}



// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if( A==NULL || B==NULL ){
		printf("Queue Error: calling equals() on NULL Queue reference\n");
		exit(1);
	}

	eq = ( A->length == B->length );
	N = A->front;
	M = B->front;

	while( eq && N!=NULL){

		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
	N = M = NULL;
	return eq;
}

// Manipulation procedures ----------------------------------------------------




// clear()
// clears/empties the list
void clear(List L){
	if(L == NULL){
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}

	if(length(L) == 0){
		L->cursor = NULL;
		return;
	}

	while(length(L) != 0){
		deleteFront(L);
	}
	L->cursor = NULL;
	

	
}



// moveFront()
// move the cursor to the front of L
void moveFront(List L){
        if(L == NULL){
                printf("List Error: calling moveFront() on NULL List reference\n");
                exit(1);
        }

        if(length(L) == 0){
                printf("List Error: calling moveFront() no empty list\n");
                exit(1);
        }
	L->cursor = L->front;
}



// moveBack()
// move the cursor to the back of L
void moveBack(List L){
        if(L == NULL){
                printf("List Error: calling moveBack() on NULL List reference\n");
                exit(1);
        }

        if(length(L) == 0){
                printf("List Error: calling moveBack() no empty list\n");
                exit(1);
        }
        L->cursor = L->back;
}


// movePrev()
// moves the cursor one element backward
void movePrev(List L){
        if(L == NULL){
                printf("List Error: calling movePrev() on NULL List reference\n");
                exit(1);
        }

        if(length(L) == 0){
                printf("List Error: calling movePrev() no empty list\n");
                exit(1);
        }

	if(L->cursor != NULL && L->cursor != L->front){
		L->cursor = L->cursor->prev;
	}
	else if(L->cursor == L->front){
		L->cursor = NULL;
	}
}



// moveNext()
// moves the cursor one element forward
void moveNext(List L){
	if(L == NULL){
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}

        if(length(L) == 0){
                printf("List Error: calling moveNext() on empty list\n");
                exit(1);
        }

        if(L->cursor != NULL && L->cursor != L->back){
                L->cursor = L->cursor->next;
        }
        else if(L->cursor == L->back){
                L->cursor = NULL;
        }
}


//  prepend()
//  Places new data element at the front of L
void prepend(List L, int data){
	Node N = newNode(data);
	if(L == NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	if(length(L) == 0){
		L->back = L->front = N;
	}
	else{
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
	}

	L->length++;
}


//  append()
//  Places new data element at the back of L
void append(List L, int data){
	Node N = newNode(data);
	
	if(L == NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	if( length(L) == 0){
		L->front = L->back = N;
	}
	else{
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
	}
	L->length++;

}


//  insertBefore()
//  inserts the data element before the cursor
void insertBefore(List L, int data){
	if(L== NULL){
                printf("List Error: calling insertBefore() on NULL list reference\n");
                exit(1);
        }
        if (length(L) == 0){
                printf("List error: calling insertBefore() on empty List\n");
                exit(1);
        }

	if(length(L) > 0 && index(L) >=0){
		Node N = newNode(data);
		N->next = L->cursor;
		
		if(L->cursor == L->front){
			N->prev = NULL;
			L->front = N;
		}

		else{

			N->prev = L->cursor->prev;
			L->cursor->prev->next = N;	
		}

		L->cursor->prev = N;
	}
	L->length++;
}


//  insertAfter()
//  inserts the data element after the cursor
void insertAfter(List L, int data){
        if(L== NULL){
                printf("List Error: calling deleteAfter() on NULL list reference\n");
                exit(1);
        }
        if (length(L) == 0){
                printf("List error: calling deleteAfter() on empty List\n");
                exit(1);
        }

	Node N = newNode(data);

        if(length(L) > 0 && index(L) >=0){

                N->prev = L->cursor;

		
                if(L->cursor == L->back){
                        N->next = NULL;
                        L->back = N;
                }

                else{
			N->next = L->cursor->next;
			L->cursor->next->prev  = N;
		}
		L->cursor->next = N;
	}
	L->length++;
}



	//  deleteFront()
	//  deleted the front element from L
void deleteFront(List L){
	Node N = NULL;
		
	if(L== NULL){
		printf("List Error: calling deleteFront() on NULL list reference\n");
		exit(1);
	}
	if (length(L) == 0){
		printf("List error: calling deleteFront() on empty List\n");
		exit(1);
	}
	if(L->cursor == L->front){
		L->cursor = NULL;
	}

 

	N = L->front;
	if(length(L) > 1){
		L->front = L->front->next;
		L->front->prev = NULL;
	}

	else{
		L->front = L->back = NULL;
	}
	L->length--;
	freeNode(&N);
	N = NULL;
}


//  deleteBack()
//  deletes the back element from L
void deleteBack(List L){
	Node N = NULL;

        if(L== NULL){
                printf("List Error: calling deleteBack() on NULL list reference\n");
                exit(1);
        }
        if (length(L) == 0){
                printf("List error: calling deleteBack() on empty List\n");
                exit(1);
        }
	if(L->cursor == L->back){
		L->cursor = NULL;
	}


        N = L->back;
        
	if(length(L) > 1){
        
	        L->back = L->back->prev;
		L->back->next = NULL;
        }
        else{
        	L->back = L->front = NULL;
        }

	L->length--;
        freeNode(&N);
	N = NULL;
}


//  delete()
//  deletes the cursor element from L
void delete(List L){
	if(L->cursor == L->back){
		deleteBack(L);
		return;
	}
	if(L->cursor == L->front){
		deleteFront(L);
		return;
	}

	
	Node N = NULL;
	N = L->cursor;
		
	if(length(L) > 0 && index(L) >= 0){	
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
	}
	L->cursor= NULL;
	L->length--;
	freeNode(&N);
	N = NULL;
}


//  Other Functions ------------------------------------------------------------

//  printList()
//  Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
	Node N = NULL;

	if( L==NULL ){
		fprintf(out,"List Error: calling printList() on NULL list reference\n");
		exit(1);
	}

	for(N = L->front; N != NULL; N = N->next){
		fprintf(out,"%d ", N->data);
	}
}

//  copyList
//  returns a new list that is an exact copy of L
List copyList(List L){
	
	if(L == NULL){

		printf("List Error: calling copyList() on NULL list reference\n");
		exit(1);

	}

	List nL = newList();
	if(length(L) != 0){
		
		Node dummy = L->front;
			
		for(int i =0; i< length(L);i++){

			append(nL, dummy->data);
			dummy = dummy->next;

		}

	}

	return nL;
}  
