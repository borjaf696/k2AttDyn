#include "AttList.h"

ATTLIST * loadAttList(char * basename, int isNode, int indexAtt){
	int i;
	ATTLIST * attlist = (ATTLIST *)mymalloc(sizeof(ATTLIST));

	char nameFileEtiq[1024], nameFileInd[1024], nameFileOrd[1024];

	(isNode)?sprintf(nameFileInd,"%s.nodes.att%d.ind",basename, indexAtt):sprintf(nameFileInd,"%s.edges.att%d.ind",basename, indexAtt);
	(isNode)?sprintf(nameFileEtiq,"%s.nodes.att%d.etiq",basename, indexAtt):sprintf(nameFileEtiq,"%s.edges.att%d.etiq",basename, indexAtt);
	(isNode)?sprintf(nameFileOrd,"%s.nodes.att%d.ord",basename, indexAtt):sprintf(nameFileOrd,"%s.edges.att%d.ord",basename, indexAtt);

	FILE * fInd 	= fopen(nameFileInd,"r+");
	FILE * fEtiq 	= fopen(nameFileEtiq,"r+");
	FILE * fOrd 	= fopen(nameFileOrd,"r+");
	
	//Número de elementos
	fread(&(attlist->numEtiq), sizeof(int),1,fInd);
	int * index = (int *) malloc(sizeof(int)*(attlist->numEtiq+1));
	fread(index,sizeof(int),attlist->numEtiq+1,fInd);

	//Carga de etiquetas
	attlist->etiq = (char **)mymalloc(sizeof(char *)*(attlist->numEtiq));
	for (i=0;i<attlist->numEtiq;i++){
		int len=index[i+1]-index[i];
		attlist->etiq[i]=(char *)mymalloc(sizeof(char)*(len+1));
		fread(attlist->etiq[i],sizeof(char),len,fEtiq);
		attlist->etiq[i][len]='\0';
	}
	free(index);

	//Carga de orden
	attlist->order = (int *)malloc(sizeof(int)*attlist->numEtiq);
	fread(attlist->order,sizeof(int),attlist->numEtiq,fOrd);
	fclose(fOrd);

	return attlist;
}