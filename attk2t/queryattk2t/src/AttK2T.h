#ifndef ___ATTK2T
#define ___ATTK2T

#include "kTree.h"
#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct attk2t{
	TREP * tree;
	int numEtiq;
	char ** etiq;
} ATTK2T;

ATTK2T * loadAttK2T(char * basename, int isNode, int indexAtt);

#endif