#ifndef KTREE_H
#define KTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitrankw32int.h"
#include "basic.h"
#define MAX_INFO 100000
#define MAX 100
#ifndef uint
#define uint unsigned int
#endif
#define K 2


typedef struct node
{
    int data;
    struct node** child;
}NODE;



typedef struct matrixRep
{
    bitRankW32Int * bt;		//Bitmap representando el arbol
    bitRankW32Int * bn; 	//Bitmap representando las hojas con informacion
    uint bt_len;			//Numero de bits de BT
    uint bn_len;				//Numero de bits de BN
    uint nleaves;				//Numero de hojas con informacion
    uint numberOfNodes;
    uint numberOfEdges;
    bitRankW32Int * il;     //Bitmap representando info de las hojas
    uint il_len;
    uint * leavesInf;		//Informacion de las hojas
}MREP;


typedef struct treeRep{
	uint part;
    uint tamSubm;
    uint numberOfNodes;
    uint numberOfEdges;
    uint maxLevel;			//Nivel maximo del arbol ref K2
    uint * div_level_table;
    uint * info;
    uint * info2[2];
	uint fila;
	uint columna;
    uint * element;
    uint * basex;
    uint * basey;
    int iniq;
    int finq;
    MREP *** submatrices;
} TREP;

uint numberNodes;
uint numberLeaves;
uint numberTotalLeaves;

uint exp_pow(uint base, uint pow);

NODE * createKTree(int maxlevels);

void insertNode(NODE * root, int x, int y);

MREP * createRepresentation(NODE *root, uint numberOfNodes, uint numberOfEdges, int isMulti);

TREP * createTreeRep(uint nodesOrig,uint edges,uint part,uint subm, uint max_level);

void insertIntoTreeRep(TREP * trep, MREP * rep, uint i, uint j);

MREP * loadRepresentation(char * basename);

void adjacencyList(NODE * root, int x);

uint * compactAdjacencyList(TREP * trep,MREP * rep, int x);

uint * compact2AdjacencyList(TREP * trep,MREP * rep, int x);

uint * compactInverseList(TREP * trep,MREP * rep, int y);

void destroyRepresentation(MREP * rep, int isMulti);

uint * compactTreeAdjacencyList(TREP * trep, int x);

uint * compactTreeInverseList(TREP * trep, int x);

uint ** compactTreeRangeQuery(TREP * trep, uint p1, uint p2, uint q1, uint q2);

void destroyTreeRepresentation(TREP * trep, int isMulti);

void saveTreeRep(TREP * trep, char * basename, int isMulti);

TREP * loadTreeRepresentation(char * basename);

#endif
