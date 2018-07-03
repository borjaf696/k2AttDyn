#include "Buffer.h"
#include "mymalloc.h"
#include <stdio.h>


#define DEBUG 0

void initBuffer(){
	BUFFER.labels 		= (char ** ) mymalloc2(sizeof(char)*100000);
	BUFFER.ids 			= (int *) mymalloc2(sizeof(int)*4000000); 
}

void endBuffer(){
	free(BUFFER.labels);
	free(BUFFER.ids);
}


void printLabels(){
	int i;
	for (i=0;i<BUFFER.numResults;i++){
		if (DEBUG)
			fprintf(stderr,"%s\n",BUFFER.labels[i]);
	}
/*	if (DEBUG)	
	fprintf(stderr,"\n");*/
}

void printNumIds(){
	if (DEBUG)
	fprintf(stderr,"%d\n",BUFFER.numResults); 
}

void printIds(){
	int i;
	for (i=0;i<BUFFER.numResults;i++){
		if (DEBUG)
			fprintf(stderr,"%d\n",BUFFER.ids[i]);
	}
/*	if (DEBUG)
		fprintf(stderr,"\n");	
*/
}
