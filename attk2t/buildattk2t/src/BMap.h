#ifndef ___BMAPPROPIO
#define ___BMAPPROPIO
#include <malloc.h>
#include "bitrankw32int.h"

typedef struct BMAP{
	uint * data;
	uint tamanio;
} BMAP;


BMAP * crearBMap(int len);

int setBMAP(BMAP * vector, int x);

int destroyBMAP(BMAP * bmap);

bitRankW32Int * crearBitRank(BMAP * bmap, int numEementos);

#endif