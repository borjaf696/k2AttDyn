#ifndef K2T_H
#define K2T_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "basic.h"
#include "readValues.h"
#include "dict.h"
#include "kTree.h"

void parserAndBuildLinks(char * baseName, int nodes, int edges, int tamSubm);

int buildTreeAttK2T(char * basename, int isNode, int indexAtt, char ** dicionario, int lenDic, int nodes, int tamSubm);

#endif