//-----------------------------------------------------------------------------
//
// GraphTest.c
//
// Robert Mushkot
// rmushkot
// 1543374 
// pa4
// 
// This is a test file used to test the functions of the Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	Graph H = newGraph(6);
	addEdge(H,1,2);
	addEdge(H,1,3);
	addEdge(H,2,6);
	addEdge(H,2,4);
	addEdge(H,2,5);
	addEdge(H,3,4);
	addEdge(H,4,5);
	addEdge(H,5,6);

	printGraph(stdout, H);
	printf("Order %i\n",getOrder(H));
	BFS(H,3);
	printf("Source %i\n", getSource(H));
	List L = newList();
	getPath(L, H, 6);
	printList(stdout, L);
	printf("Dist of 5: %i\n",getDist(H,5));
	printf("Size of H: %i\n", getSize(H));
	printf("Parent of 2: %i\n", getParent(H,2));

	makeNull(H);


	// Free objects 
	freeList(&L);
	freeGraph(&H);

	return(0);
}
