#include "zorden.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kTree.h"
#include "BMap.h"

int TAM_SUBM;

int compare(const void *_a, const void *_b) {
	CELL a, b;

	int fila, columna;
	int v1, v2;

	a.x = ((CELL *) _a)->x;
	a.y = ((CELL *) _a)->y;

	b.x = ((CELL *) _b)->x;
	b.y = ((CELL *) _b)->y;

	int aSubX = a.x / (TAM_SUBM);
	int aSubY = a.y / (TAM_SUBM);
	int bSubX = b.x / (TAM_SUBM);
	int bSubY = b.y / (TAM_SUBM);

	if (aSubX != bSubX)
		return (aSubX - bSubX);
	if (aSubY != bSubY)
		return (aSubY - bSubY);

	a.x = a.x % (TAM_SUBM);
	b.x = b.x % (TAM_SUBM);
	a.y = a.y % (TAM_SUBM);
	b.y = b.y % (TAM_SUBM);

	int rTemp = (TAM_SUBM) / K;

	while (1) {
		fila = a.x / rTemp;
		columna = a.y / rTemp;
		v1 = fila * K + columna;
		fila = b.x / rTemp;
		columna = b.y / rTemp;
		v2 = fila * K + columna;

		if (v1 != v2) {
			return (v1 - v2);
		}

		if (rTemp == 1)
			break;
		rTemp = rTemp / K;
	};
	return 1;
}



int ordenar(CELL * matrix,int numAristas) {
	qsort(matrix, numAristas, sizeof(CELL), compare);
	return 1;
}


int ordenarAristasZORDEN(char * baseName, int tamSubm, int numEdges){
	TAM_SUBM=tamSubm;
	int edgesRead,aristaX,aristaY,idArista;
	char nameFile[256];
	sprintf(nameFile,"%s.edges.lnk",baseName);
	FILE * f=fopen(nameFile,"r");
	CELL * aristasM = (CELL *) malloc(sizeof(CELL) * numEdges);
		
	//Leemos el fichero de aristas	
	int numIteraciones=0;
	for (edgesRead = 0; edgesRead < numEdges; edgesRead++) {
		numIteraciones++;
		if (fscanf(f, "%d\t%d\t%d\n", &idArista, &aristaX, &aristaY) < 0){
			fprintf(stderr,"Error de lectura de aristas\n");exit(1);
		}
		aristasM[edgesRead].x=aristaX;
		aristasM[edgesRead].y=aristaY;
		aristasM[edgesRead].id=idArista;
	}
	fclose(f);

	// Ordenación de las aristas
	ordenar(aristasM,numEdges);

	char nameFileMulti[256], nameFileFirst[256], nameFileNext[256], nameFileInfo[256];
	sprintf(nameFileMulti,"%s.ids.multi",nameFile);
	sprintf(nameFileFirst,"%s.ids.first",nameFile);
	sprintf(nameFileNext,"%s.ids.next",nameFile);
	sprintf(nameFileInfo,"%s.ids.info",nameFile);


	
	fprintf(stderr,"abriendo %s\n",nameFileFirst);
	FILE * fFirst = fopen (nameFileFirst,"w+");
	if (fFirst == NULL) fprintf(stderr,"error de apertura\n");
	FILE * fNext = fopen (nameFileNext,"w+");

	BMAP * bmap 		= crearBMap(numEdges); 
	int posicionBMAP 	= 0;

	//Escritura de los ids de las aristas ordenadas
	aristaX = -1; aristaY = -1;
	int contadorMulti = 0;
	int elemsFirst=0;
	int elemsNext=0;
	for (edgesRead = 0; edgesRead < numEdges; edgesRead++){
		// Arista duplicada respecto a la anterior
		if (aristasM[edgesRead].x == aristaX && aristasM[edgesRead].y == aristaY){
			fwrite(&(aristasM[edgesRead].id),sizeof(int),1,fNext);
			elemsNext++;
			contadorMulti++;
		}
		//Es diferente: nuevo run
		else{
			//Comparamos con la siguiente para ver de que run se trata
			if (edgesRead != (numEdges - 1) && 
				aristasM[edgesRead].x == aristasM[edgesRead+1].x &&
				aristasM[edgesRead].y == aristasM[edgesRead+1].y){
				//Empezamos un run de iguales
				fwrite(&contadorMulti,sizeof(int),1,fFirst);
				elemsFirst++;
				setBMAP(bmap,posicionBMAP++);
				fwrite(&(aristasM[edgesRead].id),sizeof(int),1,fNext);
				elemsNext++;
				contadorMulti++;
			}
			else{
				//Empezamos un run de distintos
				fwrite(&(aristasM[edgesRead].id),sizeof(int),1,fFirst);
				elemsFirst++;
				posicionBMAP++;
			}
		}
		aristaX = aristasM[edgesRead].x;
		aristaY = aristasM[edgesRead].y;
	}
	fclose(fFirst);
	fclose(fNext);


	//Info de tamaño de vectores 
	FILE * fInfo = fopen(nameFileInfo,"w+");
	fwrite(&elemsFirst,sizeof(int),1,fInfo);
	fwrite(&elemsNext,sizeof(int),1,fInfo);
	fclose(fInfo);

	//Guardamos bitmap
	FILE * fMulti = fopen(nameFileMulti,"w+");
	bitRankW32Int * brank = createBitRankW32Int(bmap->data, posicionBMAP, 1, 5);
	save(brank,fMulti);
	fclose(fMulti);
	free(aristasM);
	return 0;
}
