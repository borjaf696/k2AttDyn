#ifndef ___ATTLIST
#define ___ATTLIST

#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct attlist{
	char ** etiq;
	int numEtiq;
	int * order;
} ATTLIST;

ATTLIST * loadAttList(char * basename, int isNode, int indexAtt);

#endif