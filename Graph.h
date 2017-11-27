//----------------------------------
// Graph.h                         |
// Header file for Graph ADT       |
//                                 |
// Robert Mushkot                  |
// rmushkot                        |
// 1543374                         |
// pa4                             |
// ---------------------------------


#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"

#define INF -10
#define NIL -1


// Exported Type ----------------------------------------------------------------

typedef struct GraphObj* Graph;


// Constructors - Destructors-----------------------------------------------------

// newGraph()
// returns a reference to new empty Graph object 
Graph newGraph(int n);

// freeGraph()
// frees all heap mempry associated with Graph *pG and sets *pG to NULL.
void freeGraph(Graph* pG);


// Access funtions---------------------------------------------------------------

// getOrder()
// Returns the field value of order.
int getOrder(Graph G);


// getSize()
// Returns the field value of size.
int getSize(Graph G);


// getSource()
// Returns the source vertex most recently used in BFS().
int getSource(Graph G);


// getParent()
// Returns the parent of vertex u in the Breadth-First tree created in BFS().
// Pre: 1<= u <= getOrder(G)
int getParent(Graph G, int u);


// getDist()
// returns the distance from the most recent BFS() source to vertex u, or INF if BFS() has not been called.
// Pre: 1<= u <= getOrder(G)
int getDist(Graph G, int u);


// getPath()
// appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no
// no such path exists.
// Pre: getSource(G) != NIL && 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);


// Manipulation procedures--------------------------------------------------


// makeNUll()
// deletes all edges of G restoring it to its original state. 
void makeNull(Graph G);


// addEdge()
// inserts a new edge joining u to v: u added to adjacency List of v and v to the adjacnecy list of u.
// Pre: 1 <= u,v <= getOrder()
void addEdge(Graph G, int u, int v);


// addArc()
// inserts a new directed edge from u to v v is added to the adjacency List of u
// Pre: 1 <= u,v <= getOrder(G)
void addArc(Graph G, int u, int v);


// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s);


// Other Operations----------------------------------------------------------


// printGraph()
// prints the adjacency list represnetaion of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);


#endif

