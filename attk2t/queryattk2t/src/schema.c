#include "schema.h"


/* LOAD TYPES */

TYPE * loadTypes(char * basename, int isNode, int * number){
	char nameType [1024]; char val [1024]; int i;
	(isNode)?sprintf(nameType,"%s.nodes.typ",basename):sprintf(nameType,"%s.edges.typ",basename);

	//Get number types
	FILE * fType = fopen(nameType,"r+");
	int numberTypes = 0;
	while (fscanf(fType,"%*[^\t]\t%d\n",&i)==1) numberTypes++;

	//Creamos el array para los elementos existentes
	TYPE * types = (TYPE *) mymalloc(sizeof(TYPE)*numberTypes);
	rewind(fType);

	//Cargamos la información general de cada tipo: rango de ids y etiqueta
	int totalAcum = 0;
	for (i=0;i<numberTypes;i++){
		fscanf(fType,"%[^\t]\t%d\n",val,&(types[i].numElems));
		types[i].tag = (char *) mymalloc(sizeof(char)*(strlen(val)+1));
		strcpy(types[i].tag,val);
		types[i].initial = totalAcum;
		totalAcum+=types[i].numElems;
	}
	*number = numberTypes;
	return types;
}

TYPE * loadNodeTypes(char * basename, int * number){
	return loadTypes(basename,1,number);
}

TYPE * loadEdgeTypes(char * basename, int * number){
	return loadTypes(basename,0,number);
}

/* NUMBER ATTS */

int getNumberAtts(char * basename,int isNode){
	int numAtts;
	//Archivo de atributos
	char nameFile[256];
	if (isNode){
		sprintf(nameFile,"%s.nodes.att",basename);
	}
	else{
		sprintf(nameFile,"%s.edges.att",basename);		
	}
	FILE * f = fopen(nameFile,"r");

	fscanf(f,"%d\n",&numAtts);
	fclose(f);
	return numAtts;
}

int getNumberAttNodes(char * basename){
	return getNumberAtts(basename,1);
}

int getNumberAttEdges(char * basename){
	return getNumberAtts(basename,0);
}

/* LOAD ATT SCHEMA */


ATTRIBUTE * loadAttSchema(char * basename, int isNode){
	int numAtts, j, att;
	//Archivo de atributos
	char nameFile[256];
	if (isNode){
		sprintf(nameFile,"%s.nodes.att",basename);
	}
	else{
		sprintf(nameFile,"%s.edges.att",basename);		
	}
	FILE * f = fopen(nameFile,"r");
	fscanf(f,"%d\n",&numAtts);
	ATTRIBUTE * atts = (ATTRIBUTE *) malloc(sizeof(ATTRIBUTE)*numAtts);

	// Recorremos los atributos para ver cuales son de tipo k2t
	int hayElems = 1;
	while(hayElems){	
		for (j=0;j<numAtts;j++){
			if (fscanf(f,"%d",&att)<1){hayElems = 0; break;}
			(j==numAtts-1)?fscanf(f,"\n"):fscanf(f,"\t");
			if (att!=0){
				atts[j].isK2T = (att==2)?0:1;
			}
		}
	}
	fclose(f);
	return atts;
}

ATTRIBUTE * loadNodeAttSchema(char * basename){
	return loadAttSchema(basename,1);
}

ATTRIBUTE * loadEdgeAttSchema(char * basename){
	return loadAttSchema(basename,0);
}


LINKS * loadLinks(char * basename){
	char nameFile[256]; 
	int sizeFirst,sizeNext;

	LINKS * links = (LINKS *)mymalloc(sizeof(LINKS));
	
	//Leemos tamaños de vector first y next
	sprintf(nameFile,"%s.edges.lnk.ids.info",basename);
	FILE * fInfo = fopen(nameFile,"r");
	fread(&sizeFirst,sizeof(int),1,fInfo);
	links->lenFirst = sizeFirst;
	links->first = (int *)mymalloc(sizeof(int)*sizeFirst);
	fread(&sizeNext,sizeof(int),1,fInfo);
	links->lenNext = sizeNext;
	links->next = (int *)mymalloc(sizeof(int)*sizeNext);
	fclose(fInfo);

	//Leemos vector de first
	sprintf(nameFile,"%s.edges.lnk.ids.first",basename);
	fInfo = fopen(nameFile,"r");
	fread(links->first,sizeof(int),sizeFirst,fInfo);
	fclose(fInfo);	

	//Leemos vector de next
	sprintf(nameFile,"%s.edges.lnk.ids.next",basename);
	fInfo = fopen(nameFile,"r");
	fread(links->next,sizeof(int),sizeNext,fInfo);
	fclose(fInfo);

	sprintf(nameFile,"%s.edges.lnk.ids.multi",basename);
	links->bitmap = (bitRankW32Int *)mymalloc(sizeof(bitRankW32Int));
	fInfo = fopen(nameFile,"r");
	load(links->bitmap, fInfo);

	sprintf(nameFile,"%s.edges.lnk",basename);
	links->tree = loadTreeRepresentation(nameFile,1);
	return links;
}

void printGraph(){
	int i,j;
	fprintf(stderr,"======== GRAFO ===========\n");
	fprintf(stderr,"Tipos de nodos diferentes:%d\n",GRAPH.numTypeNodes);
	for (i=0;i<GRAPH.numTypeNodes;i++){
		fprintf(stderr,"%s: %d elementos desde id %d\n",GRAPH.nodes[i].tag,GRAPH.nodes[i].numElems,GRAPH.nodes[i].initial);
	}
	fprintf(stderr,"---\n");
	fprintf(stderr,"Tipos de aristas diferentes:%d\n",GRAPH.numTypeEdges);
	for (i=0;i<GRAPH.numTypeEdges;i++){
		fprintf(stderr,"%s: %d elementos desde id %d\n",GRAPH.edges[i].tag,GRAPH.edges[i].numElems,GRAPH.edges[i].initial);
	}

	fprintf(stderr,"--\n");
	fprintf(stderr,"Número de atributos para nodos:%d\n",GRAPH.numAttNodes);
	for (i=0;i<GRAPH.numAttNodes;i++){
		fprintf(stderr,"Atributo %d:",i);
		if (GRAPH.attNodes[i].isK2T){
			fprintf(stderr," tipo k2t\n");
			for (j=0;j<GRAPH.attNodes[i].attK2T->numEtiq;j++){
				fprintf(stderr,"%s-",GRAPH.attNodes[i].attK2T->etiq[j]);
			}
			fprintf(stderr,"\n");
		}
		else {
			fprintf(stderr,"tipo lista\n");
			fprintf(stderr,"Etiq:");
			for (j=0;j<GRAPH.attNodes[i].attList->numEtiq;j++){
				fprintf(stderr,"%s-",GRAPH.attNodes[i].attList->etiq[j]);
			}
			fprintf(stderr,"\n");
			fprintf(stderr,"Orden:");
			for (j=0;j<GRAPH.attNodes[i].attList->numEtiq;j++){
				fprintf(stderr,"%d-",GRAPH.attNodes[i].attList->order[j]);
			}
			fprintf(stderr,"\n");
			fprintf(stderr,"tipo lista\n");
		}
	}

	fprintf(stderr,"--\n");
	fprintf(stderr,"Número de atributos para aristas:%d\n",GRAPH.numAttEdges);
	for (i=0;i<GRAPH.numAttEdges;i++){
		fprintf(stderr,"Atributo %d:",i);
		if (GRAPH.attEdges[i].isK2T){
			fprintf(stderr,"tipo k2t\n");
			for (j=0;j<GRAPH.attEdges[i].attK2T->numEtiq;j++){
				fprintf(stderr,"%s-",GRAPH.attEdges[i].attK2T->etiq[j]);
			}
			fprintf(stderr,"\n");
		}
		else{
			fprintf(stderr,"tipo lista\n");
			fprintf(stderr,"Etiq:");
			for (j=0;j<GRAPH.attEdges[i].attList->numEtiq;j++){
				fprintf(stderr,"%s-",GRAPH.attEdges[i].attList->etiq[j]);
			}
			fprintf(stderr,"\n");
			fprintf(stderr,"Orden:");
			for (j=0;j<GRAPH.attEdges[i].attList->numEtiq;j++){
				fprintf(stderr,"%d-",GRAPH.attEdges[i].attList->order[j]);
			}
			fprintf(stderr,"\n");
		}
	}
	fprintf(stderr,"--");
	fprintf(stderr,"ARISTAS:\n");
	
	fprintf(stderr,"First:");
	for (i=0;i<GRAPH.links->lenFirst;i++){
		fprintf(stderr,"%d-",GRAPH.links->first[i]);
	}
	fprintf(stderr,"\n");

	fprintf(stderr,"Next:");
	for (i=0;i<GRAPH.links->lenNext;i++){
		fprintf(stderr,"%d-",GRAPH.links->next[i]);
	}
	fprintf(stderr,"\n");

}
