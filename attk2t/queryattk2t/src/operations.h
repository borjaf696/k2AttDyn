#ifndef ___ATTOPERATIONS
#define ___ATTOPERATIONS

#include "schema.h"
#include "Buffer.h"
#include "kTree.h" 
#include "kTreeMulti.h"

void getNodeTypes();

void getEdgeTypes();

void scanNode(char * label);

void scanEdge(char * label);

void getNodeType(int id);

void getEdgeType(int id);

void getNodeAttribute(int id, int indexAtt);

void getEdgeAttribute(int id, int indexAtt);

void selectNode(char * type, int indexAtt, char * label);

void selectEdge(char * type, int indexAtt, char * label);

void getNeighbours(char * labelType, int id);

void getRelated (char * labelType, int id);

#endif