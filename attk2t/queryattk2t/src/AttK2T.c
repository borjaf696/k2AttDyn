#include "AttK2T.h"


ATTK2T * loadAttK2T(char * basename, int isNode, int indexAtt){
	int i;
	ATTK2T * attk2t = (ATTK2T *)mymalloc(sizeof(ATTK2T));

	char nameFileEtiq[1024], nameFileInd[1024], nameBaseTree[1024];

	(isNode)?sprintf(nameFileInd,"%s.nodes.att%d.ind",basename, indexAtt):sprintf(nameFileInd,"%s.edges.att%d.ind",basename, indexAtt);
	(isNode)?sprintf(nameFileEtiq,"%s.nodes.att%d.etiq",basename, indexAtt):sprintf(nameFileEtiq,"%s.edges.att%d.etiq",basename, indexAtt);
	(isNode)?sprintf(nameBaseTree,"%s.nodes.att%d",basename, indexAtt):sprintf(nameBaseTree,"%s.edges.att%d",basename, indexAtt);

	FILE * fInd = fopen(nameFileInd,"r+");
	FILE * fEtiq = fopen(nameFileEtiq,"r+");

	
	//Número de elementos
	fread(&(attk2t->numEtiq), sizeof(int),1,fInd);
	int * index = (int *) malloc(sizeof(int)*(attk2t->numEtiq+1));
	fread(index,sizeof(int),attk2t->numEtiq+1,fInd);

	//Carga de etiquetas
	attk2t->etiq = (char **)mymalloc(sizeof(char *)*(attk2t->numEtiq));
	for (i=0;i<attk2t->numEtiq;i++){
		int len=index[i+1]-index[i];
		attk2t->etiq[i]=(char *)mymalloc(sizeof(char)*(len+1));
		fread(attk2t->etiq[i],sizeof(char),len,fEtiq);
		attk2t->etiq[i][len]='\0';
	}
	free(index);
	attk2t->tree = loadTreeRepresentation(nameBaseTree,0);
	return attk2t;
}