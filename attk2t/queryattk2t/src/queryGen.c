#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main(int argc, char ** argv){
	char nameFile[1024],nameType[1024],val[1024],nameFile2[1024], valAux[1024];
	int i, j;
	srand(time(NULL));

	if (argc<4){
		fprintf(stderr,"usage:%s <graphBaseName> <queryBaseName> <numQueries>\n",argv[0]);
		return 1;
	}

	int numQueries = atoi(argv[3]);

	// ==== Operación GetTypes

	//Node
	sprintf(nameFile,"%s.q1",argv[2]);
	FILE * fQuery = fopen(nameFile,"w+");
	fprintf(fQuery,"11	1\n");
	fprintf(fQuery,"-1\n");
	fclose(fQuery);

	//Edge
	sprintf(nameFile,"%s.q2",argv[2]);
	fQuery = fopen(nameFile,"w+");
	fprintf(fQuery,"12	1\n");
	fprintf(fQuery,"-1\n");
	fclose(fQuery);
	printf("Fin\n");
	// ==== Operación Scan

	//Node 
	sprintf(nameFile,"%s.q3",argv[2]);
	fQuery = fopen(nameFile,"w+");
	sprintf(nameType,"%s.nodes.typ",argv[1]);
	FILE * fType = fopen(nameType,"r+");
	int numberTypes = 0;
	while (fscanf(fType,"%*[^\t]\t%d\n",&i)==1) numberTypes++;
	fprintf(fQuery,"21\t%d\n",numberTypes);
	rewind(fType);
	while (fscanf(fType,"%[^\t]\t%*d\n",val)==1){
		fprintf(fQuery,"%s\n",val);
	} 
	fclose(fType);
	fclose(fQuery);

	//Edge
	sprintf(nameFile,"%s.q4",argv[2]);
	fQuery = fopen(nameFile,"w+");
	sprintf(nameType,"%s.edges.typ",argv[1]);
	fType = fopen(nameType,"r+");
	numberTypes = 0;
	while (fscanf(fType,"%*[^\t]\t%d\n",&i)==1) numberTypes++;
	fprintf(fQuery,"22\t%d\n",numberTypes);
	rewind(fType);
	while (fscanf(fType,"%[^\t]\t%*d\n",val)==1){
		fprintf(fQuery,"%s\n",val);
	} 
	fclose(fType);
	fclose(fQuery);

	// === Operación GetType

	//Nodos 
	sprintf(nameFile,"%s.q5",argv[2]);
	fQuery = fopen(nameFile,"w+");
	sprintf(nameType,"%s.nodes.typ",argv[1]);
	fType = fopen(nameType,"r+");
	int numberNodos = 0;
	while (fscanf(fType,"%*[^\t]\t%d\n",&i)==1) numberNodos+=i;
	fprintf(fQuery,"31\t%d\n",numQueries);
	for (i=0;i<numQueries;i++){
		fprintf(fQuery,"%d\n",rand()%numberNodos);
	} 
	fclose(fType);
	fclose(fQuery);

	//Aristas
	sprintf(nameFile,"%s.q6",argv[2]);
	fQuery = fopen(nameFile,"w+");
	sprintf(nameType,"%s.edges.typ",argv[1]);
	fType = fopen(nameType,"r+");
	numberNodos = 0;
	while (fscanf(fType,"%*[^\t]\t%d\n",&i)==1) numberNodos+=i;
	fprintf(fQuery,"32\t%d\n",numQueries);
	for (i=0;i<numQueries;i++){
		fprintf(fQuery,"%d\n",rand()%numberNodos);
	} 
	fclose(fType);
	fclose(fQuery);

	// ==== GetAttribute
	int * idN     = malloc(sizeof(int)*numQueries);
	int * nAtt    = malloc(sizeof(int)*numQueries);
	char ** nTyp  = malloc(sizeof(char *)*numQueries);
	for (i=0;i<numQueries;i++) nTyp[i]=malloc(sizeof(char)*1024);	
	int * idE     = malloc(sizeof(int)*numQueries);
	int * eAtt	  = malloc(sizeof(int)*numQueries);
	char **  eTyp = malloc(sizeof(char *)*numQueries);
	for (i=0;i<numQueries;i++) {
		eTyp[i]=malloc(sizeof(char)*2048);	
	}
	//Nodos
	sprintf(nameFile,"%s.q7",argv[2]);
	fQuery = fopen(nameFile,"w+");
	fprintf(fQuery,"41\t%d\n",numQueries);
	//Calculamos número de runs, dependiendo de cuantos valores !=0 hay en la tabla de atributos
	sprintf(nameType,"%s.nodes.att",argv[1]);
	fType = fopen(nameType,"r");
	int numAtts;
	fscanf(fType,"%d\n",&numAtts);
	int hayElems = 1; int numAtt = 0, att;
	while(hayElems){	
		for (j=0;j<numAtts;j++){
			if (fscanf(fType,"%d",&att)<1){hayElems = 0; break;}
			(j==numAtts-1)?fscanf(fType,"\n"):fscanf(fType,"\t");
			if (att!=0) numAtt++;
		}
	}
	rewind(fType);
	fscanf(fType,"%*d\n");
	int tamBloque = 1 + (numQueries / numAtt);
	sprintf(nameFile2,"%s.nodes.typ",argv[1]);
	FILE * f = fopen(nameFile2,"r");
	int idIni=0;
	int idEnd=-1;
	hayElems = 1;
	int contador = 0;
	
	while(hayElems){	
		fscanf(f,"%[^\t]\t%d\n",valAux,&i);
		idIni = idEnd + 1;
		idEnd = idIni + i - 1;
		for (j=0;j<numAtts;j++){
			if (fscanf(fType,"%d",&att)<1){hayElems = 0; break;}
			(j==numAtts-1)?fscanf(fType,"\n"):fscanf(fType,"\t");
			if (att!=0){
				for (i=0;i<tamBloque;i++){
					if (contador<numQueries){
						int num = rand()%(idEnd - idIni + 1);
						idN[contador]=num + idIni;
						nAtt[contador]=j;
						strcpy(nTyp[contador],valAux);
						contador++;
						fprintf(fQuery,"%d\t%d\n",idIni + num,j);
					}
				}
			} 
		}
	}
	fclose(f);
	fclose(fType);
	fclose(fQuery);	

	contador = 0;
	//Aristas
	sprintf(nameFile,"%s.q8",argv[2]);
	fQuery = fopen(nameFile,"w+");
	fprintf(fQuery,"42\t%d\n",numQueries);
	//Calculamos número de runs, dependiendo de cuantos valores !=0 hay en la tabla de atributos
	sprintf(nameType,"%s.edges.att",argv[1]);
	fType = fopen(nameType,"r");
	fscanf(fType,"%d\n",&numAtts);
	hayElems = 1; numAtt = 0;
	while(hayElems){	
		for (j=0;j<numAtts;j++){
			if (fscanf(fType,"%d",&att)<1){hayElems = 0; break;}
			(j==numAtts-1)?fscanf(fType,"\n"):fscanf(fType,"\t");
			if (att!=0) numAtt++;
		}
	}
	rewind(fType);
	fscanf(fType,"%*d\n");
	tamBloque = 1 + (numQueries / numAtt);
	sprintf(nameFile2,"%s.edges.typ",argv[1]);
	f = fopen(nameFile2,"r");
	idIni=0;
	idEnd=-1;
	hayElems = 1;
	while(hayElems){	
		fscanf(f,"%[^\t]\t%d\n",valAux,&i);
		idIni = idEnd + 1;
		idEnd = idIni + i - 1;
		for (j=0;j<numAtts;j++){
			if (fscanf(fType,"%d",&att)<1){
				hayElems = 0; 
				break;
			}
			(j==numAtts-1)?fscanf(fType,"\n"):fscanf(fType,"\t");
			if (att!=0){
				for (i=0;i<tamBloque;i++){
					if (contador<numQueries){
						int num = rand()%(idEnd - idIni + 1);
						idE[contador]=num + idIni;
						eAtt[contador]=j;
						strcpy(eTyp[contador],valAux);
						contador++;
						fprintf(fQuery,"%d\t%d\n",idIni + num,j);
					}
				}
			} 
		}
	}
	fclose(f);
	fclose(fType);
	fclose(fQuery);	


	// ==== Select
	sprintf(nameFile,"%s.q9",argv[2]);
	fQuery = fopen(nameFile,"w+");
	fprintf(fQuery,"51\t%d\n",numQueries);
	//Calculamos número de runs, dependiendo de cuantos valores !=0 hay en la tabla de atributos
	sprintf(nameType,"%s.nodes.val",argv[1]);
	fType = fopen(nameType,"r");
	char valC[1024];

	for (i=0;i<numQueries;i++){
		for (j=0;j<idN[i];j++) fscanf(fType,"%*[^\n]\n");
		fscanf(fType,"%*d\t");
		for (j=0;j<nAtt[i];j++){
			fscanf(fType,"%*[^\t]\t");
		}
		fscanf(fType,"%[^\t]",valC);
		fprintf(fQuery,"%s\t%d\t%s\n",nTyp[i],nAtt[i],valC);
		rewind(fType);
	}
	fclose(fQuery);
	fclose(fType);


	sprintf(nameFile,"%s.q10",argv[2]);
	fQuery = fopen(nameFile,"w+");
	fprintf(fQuery,"52\t%d\n",numQueries);
	//Calculamos número de runs, dependiendo de cuantos valores !=0 hay en la tabla de atributos
	sprintf(nameType,"%s.edges.val",argv[1]);
	fType = fopen(nameType,"r");
	for (i=0;i<numQueries;i++){
		for (j=0;j<idE[i];j++) fscanf(fType,"%*[^\n]\n");
		fscanf(fType,"%*d\t");
		for (j=0;j<eAtt[i];j++){
			fscanf(fType,"%*[^\t]\t");
		}
		fscanf(fType,"%[^\t]",valC);
		fprintf(fQuery,"%s\t%d\t%s\n",eTyp[i],eAtt[i],valC);
		rewind(fType);
	}
	fclose(fQuery);
	fclose(fType);


	// ==== Neighbours 

	sprintf(nameFile,"%s.q11",argv[2]);
	fQuery = fopen(nameFile,"w+");
	sprintf(nameType,"%s.nodes.typ",argv[1]);
	fType = fopen(nameType,"r+");
	numberTypes = 0;
	fprintf(fQuery,"6\t%d\n",numQueries);
	int totalNodes = 0;
	while (fscanf(fType,"%*[^\t]\t%d\n",&i)==1){
		numberTypes++;
		totalNodes+=i;	
	} 
	tamBloque = numQueries / numberTypes + 1;
	rewind(fType);
	int total = 0;
	int numElems;
	while (fscanf(fType,"%[^\t]\t%d\n",val,&numElems)==2){
		for (i=0;i<tamBloque;i++){
			if (total<numQueries){
				fprintf(fQuery,"%d\t%s\n",rand()%(totalNodes), val);
				total++;
			}
		}
	} 
	fclose(fType);
	fclose(fQuery);



	// === Related
	sprintf(nameFile,"%s.q12",argv[2]);
	fQuery = fopen(nameFile,"w+");
	sprintf(nameType,"%s.edges.typ",argv[1]);
	fType = fopen(nameType,"r+");
	numberTypes = 0;
	fprintf(fQuery,"7\t%d\n",numQueries);
	while (fscanf(fType,"%*[^\t]\t%d\n",&i)==1){
		numberTypes++;
	} 
	tamBloque = numQueries / numberTypes + 1;
	rewind(fType);
	total = 0;
	while (fscanf(fType,"%[^\t]\t%d\n",val,&numElems)==2){
		for (i=0;i<tamBloque;i++){
			if (total<numQueries){
				fprintf(fQuery,"%d\t%s\n",rand()%(totalNodes), val);
	
				total++;
			}
		}
	} 
	fclose(fType);
	fclose(fQuery);

}
