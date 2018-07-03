#include "readValues.h"

//Métodos auxiliares
int getNumberNodes(char * basename){
	int freq;
	char nameFile[256];
	sprintf(nameFile,"%s.nodes.typ",basename);
	FILE * fNodesTyp = fopen(nameFile,"r");
	int totalNodes=0;
	while(fscanf(fNodesTyp,"%*s\t%d\n",&freq)==1){
		totalNodes += freq;
	}
	fclose(fNodesTyp);
	return totalNodes;
}

int getNumberEdges(char * basename){
	int freq;
	char nameFile[256];
	sprintf(nameFile,"%s.edges.typ",basename);
	FILE * fEdgesTyp = fopen(nameFile,"r");
	int totalEdges=0;
	while(fscanf(fEdgesTyp,"%*s\t%d\n",&freq)==1){
		totalEdges += freq;
	}
	fclose(fEdgesTyp);
	return totalEdges;
}

int getNumberTypes(char * basename, int isNode){
	int freq;
	char nameFile[256];
	
	if (isNode)
		sprintf(nameFile,"%s.nodes.typ",basename);
	else
		sprintf(nameFile,"%s.edges.typ",basename);

	FILE * fEdgesTyp = fopen(nameFile,"r");
	int totalTypes = 0;
	while(fscanf(fEdgesTyp,"%*s\t%d\n",&freq)==1) totalTypes++;
	fclose(fEdgesTyp);
	return totalTypes;
}

//Devuelve qué tipos tienen activo ese atributo
int * getActTypes(char * basename,int isNode,int indexAtt){
	int * types,i,j;
	int att;
	//Archivo de atributos
	char nameFile[256];
	if (isNode){
		sprintf(nameFile,"%s.nodes.att",basename);
	}
	else{
		sprintf(nameFile,"%s.edges.att",basename);		
	}
	FILE * f = fopen(nameFile,"r");

	int numElementos = getNumberTypes(basename,isNode);
	int numAtts = getNumberAtts(basename,isNode);

	types = (int *)malloc(sizeof(int)*numElementos);
	for (i=0;i<numElementos;i++){
		types[i]=0;
	}

	fscanf(f,"%*d\n");
	// Recorremos los atributos para ver cuales son de tipo k2t
	for (i=0;i<numElementos;i++){
		for (j=0;j<numAtts;j++){
			fscanf(f,"%d",&att);
			(j==numElementos-1)?fscanf(f,"\n"):fscanf(f,"\t");
			if (j==indexAtt && att!=0){
				fprintf(stderr,"tipo %d activo\n",i);
				types[i]=1;
			}
		}
	}
	return types;
}

int getTamSubm(int nodes){
	uint tamSubm = 1<<24;
	while (tamSubm>2*nodes){
		tamSubm/=2;
	}
	return tamSubm;
}

int getNumberAtts(char * baseName, int isNode){
	int numElementos;
	//LEctura del archivo	
	char nameFile[256];
	if (isNode){
		sprintf(nameFile,"%s.nodes.att",baseName);
	}
	else{
		sprintf(nameFile,"%s.edges.att",baseName);		
	}
	FILE * f = fopen(nameFile,"r");
	//Inicializamos el vector
	fscanf(f,"%d\n",&numElementos);
	fclose(f);
	return numElementos;
}

int * getAttsTipo(char * baseName, int isNode, int tipos, int tipo){
	int * atts,* attsK2T,i,j;
	int att;

	//Archivo de atributos
	char nameFile[256];
	if (isNode){
		sprintf(nameFile,"%s.nodes.att",baseName);
	}
	else{
		sprintf(nameFile,"%s.edges.att",baseName);		
	}
	FILE * f = fopen(nameFile,"r");


	int numElementos = getNumberAtts(baseName,isNode);
	atts = (int *)malloc(sizeof(int)*numElementos);
	for (i=0;i<numElementos;i++){
		atts[i]=0;
	}
	fscanf(f,"%*d\n");
	// Recorremos los atirbutos para ver cuales son de ese tipo
	for (i=0;i<tipos;i++){
		for (j=0;j<numElementos;j++){
			fscanf(f,"%d",&att);
			(j==numElementos-1)?fscanf(f,"\n"):fscanf(f,"\t");
			fprintf(stderr,"att %d tipo %d\n",j,att);
			if (att==tipo){
				atts[j]=1;
			}
		}
	}


	//Construimos la lista de atributos que son de ese tipo
	int numActivos = 0;
	for (i=0;i<numElementos;i++) if (atts[i]==1) numActivos++;
	int index=0;
	attsK2T = (int * )malloc(sizeof(int)*(numActivos+1));
	attsK2T[index++]=numActivos;
	for (i=0;i<numElementos;i++){
		if (atts[i]==1){
			attsK2T[index++]=i;
		}
	}

	return attsK2T;
}

int * getAttsK2T(char * baseName, int isNode, int tipos){
	return getAttsTipo(baseName, isNode, tipos, 1);
}

int * getAttsList(char * baseName, int isNode, int tipos){
	return getAttsTipo(baseName, isNode, tipos, 2);
}

int getRunsAtt(char * basename, int isNode, int ** iniRun, int ** finRun, int indexAtt){
	int i, freq;
	char nameFileTypes[256];
	//Ver los runs en los que está activo un atributo
	if (isNode){
		sprintf(nameFileTypes,"%s.nodes.typ",basename);
	}
	else{
		sprintf(nameFileTypes,"%s.edges.typ",basename);
	}
	int numTypes = getNumberTypes(basename,isNode);
	int * types  =  getActTypes(basename,isNode,indexAtt);
	FILE * fTypes = fopen(nameFileTypes,"r");
	int indexRun=0; int ultimo = -1;
	iniRun[0] = (int *) malloc(sizeof(int)*numTypes);
	finRun[0] = (int *) malloc(sizeof(int)*numTypes);
	for (i=0;i<numTypes;i++){
		fscanf(fTypes,"%*s\t%d\n",&freq);
		if (types[i]){
			iniRun[0][indexRun]=ultimo+1;
			finRun[0][indexRun++]=ultimo+freq;
		}
		ultimo+=freq;
	}
	// Fin cálculo runs
	return indexRun;
}