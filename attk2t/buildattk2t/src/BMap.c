#include "BMap.h"

int setBMAP(BMAP * vector, int x);

int destroy(BMAP * bmap);

BMAP * crearBMap(int len){
	int i;


	BMAP * bmap=(BMAP *) malloc(sizeof(BMAP));
	bmap->tamanio=len/(8*(sizeof(uint)))+1;
	bmap->data=(uint *)malloc(bmap->tamanio*sizeof(uint));
	for (i=0;i<bmap->tamanio;i++){
		bmap->data[i]=0;
	}
	return bmap;
}

int setBMAP(BMAP * bmap, int x){
	if (x == bmap->tamanio){
		fprintf(stderr,"ERROR!");
		exit(1);
	}
	bitset(bmap->data,x);
	return 0;
}

int destroyBMAP(BMAP * bmap){
	free(bmap->data);
	free(bmap);
	return 0;

}

bitRankW32Int * crearBitRank(BMAP * bmap, int numElementos){
	return createBitRankW32Int ( bmap->data, numElementos, 0, 5);
}