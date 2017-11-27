//----------------------------------
// Graph.c			   |
// Implementation for Graph ADT    |
// 				   |
// Robert Mushkot		   |
// rmushkot			   |
// 1543374			   |
// pa4				   |
// ---------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"


// Structs ------------------------------------------


// private GraphObj type
typedef struct GraphObj{
	int order;  // Number of vertices
	int size;  // Number of edges
	int source; // most recent source of BFS()

	List* vertices;
	char* color;

	int* parent;
	int* dist;

} GraphObj;





// Constructors - Destructors-----------------------------------------------------

// newGraph()
// returns a reference to new empty Graph object 
Graph newGraph(int n){
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->source = NIL; 

	G->vertices = calloc(n+1,sizeof(List*));
	G->color = calloc(n+1,sizeof(char*));

	G->parent = calloc(n+1,sizeof(int*));
	G->dist = calloc(n+1,sizeof(int*));

	for(int i = 1; i<=n; i++){

		G->vertices[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->dist[i] = INF;
	}

	return G;
}


// freeGraph()
// frees all heap mempry associated with Graph *pG and sets *pG to NULL.
void freeGraph(Graph* pG){
	if(pG != NULL && *pG != NULL){

		for(int i = 1; i <= getOrder(*pG); i++){

			freeList(&(*pG)->vertices[i]);
		}
		free((*pG)->vertices);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->dist);


		free(*pG);
		*pG = NULL;
	}
}



// Access funtions---------------------------------------------------------------

// getOrder()
// Returns the field value of order.
int getOrder(Graph G){

	return G->order;

}


// getSize()
// Returns the field value of size.
int getSize(Graph G){

	return G->size;

}


// getSource()
// Returns the source vertex most recently used in BFS().
int getSource(Graph G){

	return G->source;

}


// getParent()
// Returns the parent of vertex u in the Breadth-First tree created in BFS().
// Pre: 1<= u <= getOrder(G)
int getParent(Graph G, int u){

	if(G == NULL){

		printf("Graph Error: calling getParent on NULL Graph reference");
		exit(1);

	}

	if( u >= 1 && u <= getOrder(G)){
	
		return G->parent[u];
	
	}

	else{

		printf("Graph Error: getParent Prerequisites are not fulfilled.");
		exit(1);
	}

}


// getDist()
// returns the distance from the most recent BFS() source to vertex u, or INF if BFS() has not been called.
// Pre: 1<= u <= getOrder(G)
int getDist(Graph G, int u){

	if( G == NULL){

		printf("Graph Error: calling getParent on NULL Graph reference");
		exit(1);

	}

	if( u>=1 && u <= getOrder(G)){

		return G->dist[u];

	}

	else{

		printf("Graph Error: getParent Prerequisites not met");
		exit(1);

	}
	return INF;
}


// getPath()
// appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no
// no such path exists.
// Pre: getSource(G) != NIL && 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){

	if( G == NULL){
		printf("Graph Error: calling getPath on NULL Graph reference");
		exit(1);
	}

	if(getSource(G) != NIL && u >=1 && u<= getOrder(G)){

		if( u == G->source){

			append(L, u);

		}

		else if( G->parent[u] == NIL){
			append(L, NIL);

		} else {

			getPath(L, G, G->parent[u]);
			append(L,u);
		}
	}
	else{
		printf("Graph error: calling getPath with unmet prerequisites.");
		exit(1);
	}
}


// Manipulation procedures--------------------------------------------------


// makeNUll()
// deletes all edges of G restoring it to its original state. 
void makeNull(Graph G){

	if(G == NULL){
		printf("Graph Error: calling makeNULL on null graph reference.");
		exit(1);
	}

	for(int i = 1; i<= getOrder(G); i++){

		freeList(&G->vertices[i]);
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->dist[i] = INF;

	}
}


// addEdge()
// inserts a new edge joining u to v: u added to adjacency List of v and v to the adjacnecy list of u.
// Pre: 1 <= u,v <= getOrder()
void addEdge(Graph G, int u, int v){

	if(G == NULL){

		printf("Graph Error: calling addEdge on NULL Graph reference.");
		exit(1);

	}

	if( u >= 1 && v >=1 && u <= getOrder(G) && v <= getOrder(G)){
	
		addArc(G,u,v);
		addArc(G,v,u);
		G->size--;

	}else{

		printf("Graph error: addEdge u or v out of range 1<=u,v<=getOrder()");
		exit(1);

	}
}
 


// addArc()
// inserts a new directed edge from u to v v is added to the adjacency List of u
// Pre: 1 <= u,v <= getOrder(G)
void addArc(Graph G, int u, int v){

	if( G == NULL){
		
		printf("Graph error: addArc() calling on NULL graph reference");
		exit(1);

	}

	if(u >= 1 && v >=1 && u <= getOrder(G) && v <= getOrder(G)){

		if(length(G->vertices[u]) == 0){

			append(G->vertices[u], v);
		}

		moveFront(G->vertices[u]);

		while(v > get(G->vertices[u])){ // Puts the value v into the sorted order of u's adjacency list.

			if(length(G->vertices[u]) == index(G->vertices[u]) + 1){ // If v belongs at the back.

				append(G->vertices[u],v);
			}
			
			moveNext(G->vertices[u]);
		}

		if( v < get(G->vertices[u])){ // v is in the right spot and inserts before.

			insertBefore(G->vertices[u], v);

		}
		G->size++;

	}

	else{
		printf("Graph Error: addArc u or v out of range 1<=u,v<=getOrder()");
		exit(1);
	}
}


// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s){

	if( G != NULL){

		G->source = s;

		for(int i = 1; i<= getOrder(G); i++){
			
			G->color[i] = 'w';
			G->dist[i] = INF;
			G->parent[i] = NIL;

		}

		G->color[s] = 'g';
		G->dist[s] = 0;
		G->parent[s] = NIL;

		List Q = newList();

		append(Q, s);

		while(length(Q) != 0){

			moveFront(Q);
			int x = get(Q);
			deleteFront(Q);


			if(length(G->vertices[x]) > 0){

				moveFront(G->vertices[x]);

			}

			for(int i = 1; i <= length(G->vertices[x]); i++){

				int y = get(G->vertices[x]);
				if( G->color[y] == 'w'){

					G->color[y] = 'g';
					G->dist[y] = G->dist[x] + 1;
					G->parent[y] = x;
					append(Q,y);

				}
				moveNext(G->vertices[x]);
			}
			
			G->color[x] = 'b';
		}

		freeList(&Q);
		
	}else{
		printf("Graph Error: calling BFS on NULL graph reference.");
		exit(1);
	}
}



// Other Operations----------------------------------------------------------


// printGraph()
// prints the adjacency list represnetaion of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
	
	for(int i=  1; i<=getOrder(G); i++){

		fprintf(out,"%i: ", i);
		printList(out, G->vertices[i]);
		
		fprintf(out,"\n");
	}
} 


 
