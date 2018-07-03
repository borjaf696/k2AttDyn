#include "dict.h"


 static int
   cmpstringp(const void *p1, const void *p2)
   {
       return strcmp(* (char * const *) p1, * (char * const *) p2);
   }

 static int
   cmpDicc(const void *p1, const void *p2)
   {
   	   DICT * d1 = (DICT *) p1;
   	   DICT * d2 = (DICT *) p2;
       return strcmp((*d1).val, (*d2).val);
   }


//Obtiene el diccionario de un atributo
//Para eso sólo tiene en cuenta los valores que tienen los elementos
//de un tipo que tengan ese atributo activo
char ** getDictAttK2T(char * basename, int numElems, int att, int isNode, int * numD){
	int i,j;
	char nameFile[256],val[1024];
	int * iniRun[1]; int * finRun[1];
	int maxLen = 0;

	int numRuns = getRunsAtt(basename, isNode, iniRun, finRun, att);

	for (i=0;i<numRuns;i++){
		fprintf(stderr,"de %d a %d\n",iniRun[0][i],finRun[0][i]);
	}

	(isNode)?sprintf(nameFile,"%s.nodes.val",basename):sprintf(nameFile,"%s.edges.val",basename);
	
	//Recuperar etiquetas diferentes
	FILE * fVal = fopen(nameFile,"r+");

	int indexRun = 0;

	int indexDicc=0;
	for (i=0;i<numElems;i++){
		//Controlamos que caiga dentro de un run activo
		while(indexRun < (numRuns - 1) && i>finRun[0][indexRun] ) 
			indexRun++;
		if (i<iniRun[0][indexRun] || i>finRun[0][indexRun]){
			//Si no está en un run activo Ignoramos la fila
			fscanf(fVal,"%*[^\n]\n");
		} 
		else{
			//Parseamos la fila
			//Siempre nos saltamos el id del nodo 
			// y los atributos anteriores
			fscanf(fVal,"%*d\t");
			for (j=0;j<att;j++){
				fscanf(fVal,"%*[^\t]\t");
			}
			fscanf(fVal,"%[^\t]",val);
			fscanf(fVal,"%*[^\n]\n");
			if (strlen(val)>maxLen){
				maxLen = strlen(val);
			}
			indexDicc++;
		}
	}

	//Almacenamos todas las cadenas
	char ** cadenas = (char **) malloc(sizeof(char *) * indexDicc);
	for (i=0;i<indexDicc;i++){
		cadenas[i]= malloc(sizeof(char)*(maxLen+1));
	}

	rewind(fVal);
	indexRun = 0;
	indexDicc=0;
	for (i=0;i<numElems;i++){
		while(indexRun < (numRuns - 1) && i>finRun[0][indexRun] ) {
			indexRun++;
		}
		if (i<iniRun[0][indexRun] || i>finRun[0][indexRun]){
			//Si no está en un run activo Ignoramos la fila
			fscanf(fVal,"%*[^\n]\n");
		} 
		else{
			fscanf(fVal,"%*d\t");
			for (j=0;j<att;j++){
				fscanf(fVal,"%*[^\t]\t");
			}
			
			fscanf(fVal,"%[^\t]",cadenas[indexDicc]);
			if (indexDicc<10)
				fprintf(stderr,"Elemento %s en linea %d\n",cadenas[indexDicc],i);
			fscanf(fVal,"%*[^\n]\n");
			indexDicc++;
		}	
	}
	fprintf(stderr,"Salgo\n");
	qsort(cadenas,indexDicc,sizeof(char *),cmpstringp);	

	int numDistintos = 1;
	for (i=0;i<indexDicc-1;i++){
		if(strcmp(cadenas[i],cadenas[i+1]))
			numDistintos++;
	}
	char ** diccionario = (char **)malloc(sizeof(char *)*numDistintos);
	for (i=0;i<numDistintos;i++){
		diccionario[i] = (char *)malloc(sizeof(char)*(maxLen+1));
	}
	numDistintos = 0;
	strcpy(diccionario[numDistintos++],cadenas[0]);
	for (i=0;i<indexDicc-1;i++){
		if(strcmp(cadenas[i],cadenas[i+1])){
			strcpy(diccionario[numDistintos],cadenas[i+1]);
			numDistintos++;
		}
	}	
	fclose(fVal);
	*numD = numDistintos;
	for (i=0;i<indexDicc;i++) free(cadenas[i]);
	free(cadenas);
	return diccionario;
}



//Obtiene el diccionario de un atributo
//Para eso sólo tiene en cuenta los valores que tienen los elementos
//de un tipo que tengan ese atributo activo
DICT * getDictAttList(char * basename, int numElems, int att, int isNode, int * numD){
	int i,j;
	char nameFile[256],val[1024];
	int * iniRun[1]; int * finRun[1];
	int maxLen = 0;

	int numRuns = getRunsAtt(basename, isNode, iniRun, finRun, att);
	for (i=0;i<numRuns;i++){
		fprintf(stderr,"de %d a %d\n",iniRun[0][i],finRun[0][i]);
	}
	(isNode)?sprintf(nameFile,"%s.nodes.val",basename):sprintf(nameFile,"%s.edges.val",basename);
	
	//Recuperar etiquetas diferentes
	FILE * fVal = fopen(nameFile,"r+");

	int indexRun = 0;
	int indexDicc = 0;
	for (i=0;i<numElems;i++){
		//Controlamos que caiga dentro de un run activo
		while(indexRun < (numRuns - 1) && i>finRun[0][indexRun] ) 
			indexRun++;
		if (i<iniRun[0][indexRun] || i>finRun[0][indexRun]){
			//Si no está en un run activo Ignoramos la fila
			fscanf(fVal,"%*[^\n]\n");
		} 
		else{
			//Parseamos la fila
			//Siempre nos saltamos el id del nodo 
			// y los atributos anteriores
			fscanf(fVal,"%*d\t");
			for (j=0;j<att;j++){
				fscanf(fVal,"%*[^\t]\t");
			}
			fscanf(fVal,"%[^\t]",val);
			fscanf(fVal,"%*[^\n]\n");
			if (strlen(val)>maxLen){
				maxLen = strlen(val);
			}
			indexDicc++;
		}
	}
	//Almacenamos todas las cadenas

	DICT * diccionario = (DICT *)malloc(sizeof(DICT) * indexDicc);
	for (i=0;i<indexDicc;i++){
		diccionario[i].val = (char *)malloc(sizeof(char)*(maxLen+1));
	}
	rewind(fVal);
	indexRun = 0;
	indexDicc = 0;
	for (i=0;i<numElems;i++){
		while(indexRun < (numRuns - 1) && i>finRun[0][indexRun] ) 
			indexRun++;
		
		if (i<iniRun[0][indexRun] || i>finRun[0][indexRun]){
			//Si no está en un run activo Ignoramos la fila
			fscanf(fVal,"%*[^\n]\n");
		} 
		else{
			fscanf(fVal,"%*d\t");
			for (j=0;j<att;j++){
				fscanf(fVal,"%*[^\t]\t");
			}
			//Seteamos el elemento del diccionario
			fscanf(fVal,"%[^\t]",diccionario[indexDicc].val);
			diccionario[indexDicc].pos = indexDicc;
			indexDicc++;
			fscanf(fVal,"%*[^\n]\n");
		}	
	}
	*numD = indexDicc;
	//qsort(diccionario,indexDicc,sizeof(char *),cmpDicc);	

	return diccionario;
}

int saveList(char * basename, DICT * diccionario, int lenDic,int isNode, int indexAtt){
	int i;
	char nameFileInd[512], nameFileEtiq[512], nameFileOrd[512];
	
	if (isNode){
		sprintf(nameFileEtiq,"%s.nodes.att%d.etiq",basename,indexAtt);
		sprintf(nameFileInd,"%s.nodes.att%d.ind",basename,indexAtt);
		sprintf(nameFileOrd,"%s.nodes.att%d.ord",basename,indexAtt);
	}
	else{
		sprintf(nameFileEtiq,"%s.edges.att%d.etiq",basename,indexAtt);
		sprintf(nameFileInd,"%s.edges.att%d.ind",basename,indexAtt);		
		sprintf(nameFileOrd,"%s.edges.att%d.ord",basename,indexAtt);		
	}

	FILE * fEtiq 	= fopen(nameFileEtiq,"w+");
	FILE * fInd 	= fopen(nameFileInd,"w+");
	FILE * fOrd 	= fopen(nameFileOrd,"w+");

	fwrite(&lenDic,sizeof(int),1,fInd);
	int acumulador = 0;
	fprintf(stderr,"Len dic:%d\n",lenDic);
	for (i=0;i<lenDic;i++){
		fwrite(diccionario[i].val,sizeof(char),strlen(diccionario[i].val),fEtiq);
		fwrite(&acumulador,sizeof(int),1,fInd);
		acumulador+=strlen(diccionario[i].val);
	}
	fwrite(&acumulador,sizeof(int),1,fInd);


	qsort(diccionario,lenDic,sizeof(DICT),cmpDicc);	

	for (i=0;i<lenDic;i++){
		fwrite(&(diccionario[i].pos),sizeof(int),1,fOrd);
	}
	fclose(fOrd);
	fclose(fEtiq);
	fclose(fInd);

	return 0;
}

int saveDict(char * basename, char ** diccionario,int lenDic,int isNode,int indexAtt){
	int i;
	char nameFileInd[512], nameFileEtiq[512];
	
	if (isNode){
		sprintf(nameFileEtiq,"%s.nodes.att%d.etiq",basename,indexAtt);
		sprintf(nameFileInd,"%s.nodes.att%d.ind",basename,indexAtt);	
	}
	else{
		sprintf(nameFileEtiq,"%s.edges.att%d.etiq",basename,indexAtt);
		sprintf(nameFileInd,"%s.edges.att%d.ind",basename,indexAtt);		
	}

	FILE * fEtiq 	= fopen(nameFileEtiq,"w+");
	FILE * fInd 	= fopen(nameFileInd,"w+");
	
	fwrite(&lenDic,sizeof(int),1,fInd);
	int acumulador = 0;
	for (i=0;i<lenDic;i++){
		fwrite(diccionario[i],sizeof(char),strlen(diccionario[i]),fEtiq);
		fwrite(&acumulador,sizeof(int),1,fInd);
		acumulador+=strlen(diccionario[i]);
	}
	fwrite(&acumulador,sizeof(int),1,fInd);

	fclose(fEtiq);
	fclose(fInd);

	return 0;
}

int searchValDic(char ** diccionario,int lenDic,char * val){
	int i;
	for (i=0;i<lenDic;i++)
		if (!strcmp(diccionario[i],val)) return i;
	fprintf(stderr,"Error:%s no encontrado en el diccionario\n",val);
	exit(1);
}
