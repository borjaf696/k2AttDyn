#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "kTree.h"
#include "zorden.h"
#include "readValues.h"
#include "dict.h"
#include "k2t.h"






int main(int argc, char* argv[]){
	int i, lenDic;
	if(argc<2){
		fprintf(stderr,"USAGE: %s <baseName>\n",argv[0]);
		return(-1);
	}

	fprintf(stderr,"Paramétros de configuración\n");
	int nodes = getNumberNodes(argv[1]);
	fprintf(stderr,"Nodes:%d\n",nodes);
	int edges = getNumberEdges(argv[1]);
	fprintf(stderr,"Edges:%d\n",edges);
	int tamSubm = getTamSubm(nodes);
	fprintf(stderr,"Tam subm:%d\n",tamSubm);
	//Construimos k2-tree de links (basename.edges.lnk.tr)

	fprintf(stderr,"Construyendo links\n");
	parserAndBuildLinks(argv[1],nodes,edges,tamSubm);


	//Vector de ids de los links (basename.edges.lnk.ids)
	fprintf(stderr,"Construyendo vector de ids de aristas\n");
	ordenarAristasZORDEN(argv[1], tamSubm, edges);
	
	// === ATRIBUTOS TIPO K2T
	//Construyendo atts en forma de k2-tree para los nodos	
	int * attsActivos = getAttsK2T(argv[1],1,getNumberTypes(argv[1],1));
	for (i=0;i<attsActivos[0];i++){
		char ** diccionario = getDictAttK2T(argv[1],nodes,attsActivos[i+1],1,&lenDic);
		saveDict(argv[1],diccionario,lenDic,1,attsActivos[i+1]);
		buildTreeAttK2T(argv[1],1,attsActivos[i+1],diccionario,lenDic,nodes,tamSubm);
	}

	fprintf(stderr,"== Construyendo atributos para aristas\n");
	//Construyendo atts en forma de k2-tree para las aristas
	attsActivos = getAttsK2T(argv[1],0,getNumberTypes(argv[1],0));
	for (i=0;i<attsActivos[0];i++){
		fprintf(stderr,"ARISTAS: atributo %d\n",attsActivos[i+1]);
		char ** diccionario = getDictAttK2T(argv[1],edges,attsActivos[i+1],0,&lenDic);
		saveDict(argv[1],diccionario,lenDic,0,attsActivos[i+1]);
		buildTreeAttK2T(argv[1],0,attsActivos[i+1],diccionario,lenDic,edges,getTamSubm(edges));
	}



	fprintf(stderr,"== Construyendo atributos tipo lista\n");
	//ATRIBUTOS TIPO LISTA
	attsActivos = getAttsList(argv[1],1,getNumberTypes(argv[1],1));
	for (i=0;i<attsActivos[0];i++){
		fprintf(stderr,"Atributo lista de nodos:%d\n",attsActivos[i]);
		DICT * diccionario = getDictAttList(argv[1],nodes,attsActivos[i+1],1,&lenDic);
		saveList(argv[1],diccionario,lenDic,1,attsActivos[i+1]);
	}	

	attsActivos = getAttsList(argv[1],0,getNumberTypes(argv[1],0));
	for (i=0;i<attsActivos[0];i++){
		fprintf(stderr,"Atributo lista de aristas:%d\n",attsActivos[i]);
		DICT * diccionario = getDictAttList(argv[1],edges,attsActivos[i+1],0,&lenDic);
		saveList(argv[1],diccionario,lenDic,0,attsActivos[i+1]);
	}	
	fprintf(stderr,"Fin build\n");
  	return 0;
}


