#ifndef READVAL_H
#define READVAL_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "basic.h"

//Métodos auxiliares
int getNumberNodes(char * basename);

int getNumberEdges(char * basename);

int getNumberTypes(char * basename, int isNode);

int * getActTypes(char * basename,int isNode,int att);

int getTamSubm(int nodes);

int getNumberAtts(char * baseName, int isNode);

int * getAttsK2T(char * baseName, int isNode, int tipos);

int getRunsAtt(char * basename, int isNode, int ** iniRun, int ** finRun, int indexAtt);

int * getAttsList(char * baseName, int isNode, int tipos);

#endif