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
    uint bn_len;			//Numero de bits de BN
    bitRankW32Int * il;     //Bitmap representando info de las hojas
    uint il_len;
    uint nleaves;			//Numero de hojas con informacion
    uint numberOfNodes;
    uint numberOfEdges;
    uint * leavesInf;		//Informacion de las hojas
}MREP;


typedef struct treeRep{
	uint part;
    uint tamSubm;
    uint numberOfNodes;
    uint numberOfEdges;
    uint maxLevel;			//Nivel maximo del arbol ref K2
    uint * div_level_table;
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

void AddItem2 (TREP *rep, int elem, int cantx,int canty);

void RemoveItem2 (TREP * rep);

uint exp_pow(uint base, uint pow);

NODE * createKTree(int maxlevels);

void insertNode(NODE * root, int x, int y);

MREP * createRepresentation(NODE *root, uint numberOfNodes, uint numberOfEdges);

TREP * createTreeRep(uint nodesOrig,uint edges,uint part,uint subm, uint max_level);

void insertIntoTreeRep(TREP * trep, MREP * rep, uint i, uint j);

MREP * loadRepresentation(char * basename, int isMulti);

void adjacencyList(NODE * root, int x);

void compactAdjacencyList(TREP * trep,MREP * rep, int x);

uint * compact2AdjacencyList(TREP * trep,MREP * rep, int x);

void compactInverseList(TREP * trep,MREP * rep, int y);

void destroyRepresentation(MREP * rep, int isMulti);

void compactTreeAdjacencyList(TREP * trep, int x);

void compactTreeInverseList(TREP * trep, int x);

void compactTreeInverseListLimited(TREP * trep, int y, int initialId, int endId);

void compactTreeRangeQuery(TREP * trep, uint p1, uint p2, uint q1, uint q2);

void destroyTreeRepresentation(TREP * trep, int isMulti);

void saveTreeRep(TREP * trep, char * basename);

TREP * loadTreeRepresentation(char * basename, int isMulti);

#endif
