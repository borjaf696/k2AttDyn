#ifndef MANDICT_H
#define MANDICT_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "basic.h"
#include "readValues.h"


typedef struct dict
{
    char * val;
    int pos;
}DICT;

char ** getDictAttK2T(char * basename, int numElems, int att, int isNode, int * numD);

DICT * 	getDictAttList(char * basename, int numElems, int att, int isNode, int * numD);

int saveList(char * basename, DICT * diccionario, int lenDic,int isNode, int indexAtt);

int saveDict(char * basename, char ** diccionario,int lenDic, int isNode, int indexAtt);

int searchValDic(char ** diccionario,int lenDic,char * val);

#endif
