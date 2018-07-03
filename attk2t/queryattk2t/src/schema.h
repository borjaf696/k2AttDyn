#ifndef ATTSCHEMA_H
#define ATTSCHEMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"
#include "AttK2T.h"
#include "AttList.h"

typedef struct type
{
	//Nombre del tipo
	char * tag;
	//Id del primer elemento de este tipo
	int initial;
	//Número de elementos que contiene este tipo
	int numElems;
	//Indica si tiene ese atributo o no 
	int * attributes;

}TYPE;

typedef struct attributes{

	int isK2T;

	ATTK2T * attK2T;

	ATTLIST * attList;

} ATTRIBUTE;

typedef struct links{

	
	int * first;
	int lenFirst;

	int * next;
	int lenNext;
	
	TREP * tree;
	
	bitRankW32Int * bitmap;

} LINKS;

typedef struct schema 
{
	TYPE * nodes;
	int numTypeNodes;
	
	TYPE * edges;
	int numTypeEdges;

	ATTRIBUTE * attNodes;
	int numAttNodes;

	ATTRIBUTE * attEdges;
	int numAttEdges;

	LINKS * links;

} SCHEMA;

SCHEMA GRAPH;

TYPE * loadNodeTypes(char * basename, int * number);

TYPE * loadEdgeTypes(char * basename, int * number);

int getNumberAttNodes(char * basename);

int getNumberAttEdges(char * basename);

ATTRIBUTE * loadNodeAttSchema(char * basename);

ATTRIBUTE * loadEdgeAttSchema(char * basename);

LINKS * loadLinks(char * basename);

void printGraph();

#endif