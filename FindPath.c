//----------------------------------
// FindPath.c                      |
//				   |
// Takes input file of vertices    |
// and finds paths and distance    |
// between specified vertices      |
// 				   |
// Robert Mushkot                  |
// rmushkot                        |
// 1543374                         |
// pa4                             |
// ---------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

int main(int argc, char* argv[]){

	int n=0; 
	FILE *in, *out;
	char line[100];


	if( argc != 3){

		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);

	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if( in == NULL){

		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);

	}

	if(out == NULL){

		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);

	}

	fgets(line, sizeof(line), in);
	sscanf(line, "%d", &n);


	Graph G = newGraph(n);

	while(fgets(line,sizeof(line), in) != NULL){

		int v1 = 0;
		int v2 = 0;

		sscanf(line, "%d %d", &v1, &v2);
		
		
		if(v1 == 0 && v2 == 0) break;

		addEdge(G,v1,v2);

	}

	printGraph(out,G);
	fprintf(out, "\n");

	while(fgets(line,sizeof(line), in) != NULL){

		int v1;
		int v2;

		sscanf(line, "%i %i", &v1, &v2);
		
		if(v1 == 0 && v2 == 0) break;

		BFS(G,v1);
		
		if(getDist(G, v2) == INF)
			fprintf(out, "The distance from %i to %i is %s\n", v1, v2, "infinity");

		else
			fprintf(out, "The distance from %i to %i is %i\n", v1, v2, getDist(G,v2));

		
		List L = newList();
		getPath(L, G, v2);

		if(front(L) == -1)

			fprintf(out, "No %i-%i path exists", v1, v2);

		else{
			fprintf(out, "A shortest %i-%i path is: ", v1, v2);
			printList(out, L);
		}


		fprintf(out,"\n\n");
		freeList(&L);
	}

	fclose(in);
	fclose(out);
	freeGraph(&G);
		

	return 0;
}
