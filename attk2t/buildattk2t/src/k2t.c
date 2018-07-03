#include "k2t.h"


// Construcción de estructuras
// K2-tree links
void parserAndBuildLinks(char * baseName, int nodes, int edges, int tamSubm){
	MREP * rep;	
	int fila,columna,id1,id2; NODE * tree;
	uint max_level = floor(log(nodes)/log(K));
	uint part = nodes/tamSubm+1;
	char nameFile[256];
	sprintf(nameFile,"%s.edges.lnk",baseName);
	FILE * fedges = fopen(nameFile,"r");
	uint maxLevel = floor(log(nodes)/log(K));

	fprintf(stderr,"Tamaño de submatriz:	%d\n",tamSubm);
	fprintf(stderr,"Nodos:	%d\n",nodes);
	fprintf(stderr,"matriz de submatrices:%dx%d\n",part,part);
	fprintf(stderr,"maxLevel:%d\n",maxLevel);

	TREP * trep = createTreeRep(nodes,edges,part,tamSubm, max_level);
	int i=0;
	for(fila=0;fila<part;fila++){
		for(columna=0;columna<part;columna++){
			int edges_sub = 0;
			rewind(fedges);
			tree = createKTree(max_level);
			for (i=0;i<edges;i++){
				int numElementos = fscanf(fedges,"%*d\t%d\t%d\n",&id1,&id2);
				if (numElementos<2){ fprintf(stderr,"Error de lectura\n");exit(1);} 
				if((id1>=fila*tamSubm)&&(id1<(fila+1)*tamSubm)&&(id2>=columna*tamSubm)&&(id2<(columna+1)*tamSubm)){
					insertNode(tree,id1-fila*tamSubm,id2-columna*tamSubm);
					edges_sub++;
				}
			}
		 	rep = createRepresentation(tree,nodes,edges_sub,1);
		 	insertIntoTreeRep(trep, rep, fila, columna);
		}
	}

	trep->div_level_table = (uint *)malloc(sizeof(uint)*trep->maxLevel);
	for(i=0;i<trep->maxLevel;i++)
		trep->div_level_table[i]=exp_pow(K,trep->maxLevel-i);
	saveTreeRep(trep,nameFile,1);
	destroyTreeRepresentation(trep,1);
}

int buildTreeAttK2T(char * basename, int isNode, int indexAtt, char ** dicionario, int lenDic, int nodes, int tamSubm){
	int i,j;
	int * iniRun[1]; int * finRun[1];
	char nameFile[256],val[1024];
	int numRuns;
	
	//En estos runs es dd tenemos que sacar las aristas
	numRuns = getRunsAtt(basename, isNode, iniRun, finRun, indexAtt);
	int edges = 0;
	for (i=0;i<numRuns;i++){
		edges+=finRun[0][i]-iniRun[0][i]+1;
	}
	//Fichero de lectura
	(isNode)?sprintf(nameFile,"%s.nodes.val",basename):sprintf(nameFile,"%s.edges.val",basename);
	FILE * f = fopen(nameFile,"r");

	MREP * rep;	int fila,columna; NODE * tree;
	uint max_level = floor(log(nodes)/log(K)); uint part = nodes/tamSubm+1;
	TREP * trep = createTreeRep(nodes,edges,part,tamSubm, max_level);
	int indexRun = 0;
	fprintf(stderr,"construyendo arbol\n");
	for(fila=0;fila<part;fila++){
		for(columna=0;columna<part;columna++){
			int edges_sub = 0;
			tree = createKTree(max_level);
			for (i=0;i<nodes;i++){

				while(i>finRun[0][indexRun]  && indexRun < numRuns - 1 ) indexRun++;
				if (i<iniRun[0][indexRun] || i>finRun[0][indexRun]){
					//Si no está en un run activo Ignoramos la fila
					fscanf(f,"%*[^\n]\n");
				} 
				else{
					//Parseamos la fila
					//Siempre nos saltamos el id del nodo 
					// y los atributos anteriores
					fscanf(f,"%*d\t");
					for (j=0;j<indexAtt;j++){
						fscanf(f,"%*[^\t]\t");
					}
					fscanf(f,"%[^\t]",val);
					fscanf(f,"%*[^\n]\n");
					//Buscar indice valor
					int indiceDict = searchValDic(dicionario,lenDic,val);
					if((i>=fila*tamSubm)&&(i<(fila+1)*tamSubm)&&(indiceDict>=columna*tamSubm)&&(indiceDict<(columna+1)*tamSubm)){
						insertNode(tree,i-fila*tamSubm,indiceDict-columna*tamSubm);
						edges_sub++;
					}
				}
			}
		 	rep = createRepresentation(tree,nodes,edges_sub,0);
		 	insertIntoTreeRep(trep, rep, fila, columna);
		}
	}

	trep->div_level_table = (uint *)malloc(sizeof(uint)*trep->maxLevel);
	for(i=0;i<trep->maxLevel;i++)
		trep->div_level_table[i]=exp_pow(K,trep->maxLevel-i);
	char nameFileTree[1024];

	(isNode)?sprintf(nameFileTree,"%s.nodes.att%d",basename,indexAtt):sprintf(nameFileTree,"%s.edges.att%d",basename,indexAtt);
	fprintf(stderr,"escribiendo en%s\n",nameFileTree);
	saveTreeRep(trep,nameFileTree,0);
	destroyTreeRepresentation(trep,0);

	return 0;
}
