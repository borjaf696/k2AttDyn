#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "schema.h"
#include "Buffer.h"
#include "operations.h"
#include "AttK2T.h"
#include "AttList.h"
#include <sys/time.h>
#include <time.h>

int main(int argc, char ** argv){
	int number,i;
	struct timeval tv1, tv2;

	if (argc<4){
		fprintf(stderr,"usage:%s <basename> <basequeries> <maxQueries>\n",argv[0]);
		return 1;
	}

	fprintf(stderr,"Cargando grafo\n");
	//Carga del grafo
	GRAPH.nodes 		= loadNodeTypes(argv[1],&number);
	GRAPH.numTypeNodes 	= number;
	GRAPH.edges 		= loadEdgeTypes(argv[1],&number);
	GRAPH.numTypeEdges 	= number;

	//Carga de la estructura de atributos
	GRAPH.numAttNodes 	= getNumberAttNodes(argv[1]);
	GRAPH.numAttEdges 	= getNumberAttEdges(argv[1]);
	GRAPH.attNodes 		= loadNodeAttSchema(argv[1]);
	GRAPH.attEdges 		= loadEdgeAttSchema(argv[1]);
	
	fprintf(stderr,"Carga de atributos\n");
	//Carga de los atributos de tipo k2t
	for (i=0;i<GRAPH.numAttNodes;i++){
		if (GRAPH.attNodes[i].isK2T){
			GRAPH.attNodes[i].attK2T = loadAttK2T(argv[1],1,i);
		}
		else{
			GRAPH.attNodes[i].attList = loadAttList(argv[1],1,i); 
		}
	}
	for (i=0;i<GRAPH.numAttEdges;i++){
		if (GRAPH.attEdges[i].isK2T){
			GRAPH.attEdges[i].attK2T = loadAttK2T(argv[1],0,i);
		}
		else{
			GRAPH.attEdges[i].attList = loadAttList(argv[1],0,i);
		}
	}

	
	//Carga de links
	GRAPH.links = loadLinks(argv[1]);
	//printGraph();
	sleep(1000000000000);
	//Parseamos las consultas
	int numQueries = atoi(argv[3]);
	int * id1 = malloc(sizeof(int)*numQueries);
	int * id2 = malloc(sizeof(int)*numQueries);
	char ** label1 = malloc(sizeof(char *)*numQueries);
	char ** label2 = malloc(sizeof(char *)*numQueries);
	int index;
	for (index=0;index<numQueries;index++){
		label1[index]  = malloc(sizeof(char)*numQueries);
		label2[index] = malloc(sizeof(char)*numQueries);
	}

	initBuffer();

	fprintf(stderr,"========== CONSULTAS =============\n");

	char nameQueryFile[256];
	int tipoQuery,numq,j;


	for (i=1;i<=12;i++){
		sprintf(nameQueryFile,"%s.q%d",argv[2],i);
		fprintf(stderr,"Query %s\n",nameQueryFile);
		FILE * fQueries = fopen(nameQueryFile,"r");

		//Carga
		fscanf(fQueries,"%d\t%d\n",&tipoQuery,&numq);

		switch (tipoQuery){
			case 11: 
					break;
			case 12:
					break;
			case 21: case 22: 
					for (j=0;j<numq;j++){
						fscanf(fQueries,"%[^\t]\n",label1[j]);
					}
					break;
			case 31: case 32:  
					for (j=0;j<numq;j++){
						fscanf(fQueries,"%d\n",&id1[j]);
					}
					break;
					
			case 41: case 42:
					for (j=0;j<numq;j++){
						fscanf(fQueries,"%d\t%d\n",&id1[j],&id2[j]);
					}
					break;
			case 51: case 52:
					for (j=0;j<numq;j++){
						fscanf(fQueries,"%[^\t]\t%d\t%[^\n]\n",label1[j],&id1[j],label2[j]);
					}
					break;
			case 61: case 62:
					for (j=0;j<numq;j++){
						fscanf(fQueries,"%d\t%[^\n]\n",&id1[j],label1[j]);
					}
					break;
			default:fprintf(stderr,"No soportado\n");
		}



		gettimeofday(&tv1, NULL);
		int k;
		for (k=0;k<1;k++){
		//Ejecución
		switch (tipoQuery){
			case 11: 
					getNodeTypes();
					printLabels();
					break;
			case 12:
					getEdgeTypes();
					printLabels();
			case 21:

					for (j=0;j<numq;j++){
						scanNode(label1[j]);
						printIds();
					}
					break;
			case 22: 

					for (j=0;j<numq;j++){
						scanEdge(label1[j]);
						printIds();
					}
					break;

			case 31:
					for (j=0;j<numq;j++){
						getNodeType(id1[j]);
						printLabels();

					}
					break;
			case 32:

					for (j=0;j<numq;j++){
						getEdgeType(id1[j]);
						printLabels();
					}

					break;
			case 41:
					for (j=0;j<numq;j++){
						getNodeAttribute(id1[j],id2[j]);
						printLabels();
					}
					break;

			case 42: 
					for (j=0;j<numq;j++){
						getEdgeAttribute(id1[j],id2[j]);
						printLabels();
					}
					break;
			case 51:
					for (j=0;j<numq;j++){
						selectNode(label1[j],id1[j],label2[j]);
						printIds();
					}
					break;
			case 52:
					for (j=0;j<numq;j++){
						selectEdge(label1[j],id1[j],label2[j]);
						printNumIds();
					}
					break;
			case 61:
					for (j=0;j<numq;j++){
						getNeighbours(label1[j],id1[j]);
						printNumIds();
					}
					break;

			case 62:
					for (j=0;j<numq;j++){
						getRelated(label1[j],id1[j]);
						printNumIds();
					}
					break;

			default:fprintf(stderr,"No soportado\n");
		}
		}
		gettimeofday(&tv2, NULL);
		fprintf(stderr,
			"Tiempo total: %ld en us\n",
			(tv2.tv_sec - tv1.tv_sec) * 1000000
			+ (tv2.tv_usec - tv1.tv_usec));
		fclose(fQueries);	
	}
	


	exit(1);


	fprintf(stderr,"========== CONSULTAS =============\n");
	//Consultas

	//GetNodeTypes
	getNodeTypes();
	fprintf(stderr,"(getNodeTypes)\n");
	printLabels();

	//GetEdgeTypes
	getEdgeTypes();
	fprintf(stderr,"(getEdgeTypes)\n");
	printLabels();

	/* CONSULTA 2 */
	//ScanNode
	scanNode("USER");
	fprintf(stderr,"(scanNode USER)\n");
	printIds();

	scanNode("BOOK");
	fprintf(stderr,"(scanNode BOOK)\n");
	printIds();

	scanNode("WRITER");
	fprintf(stderr,"(scanNode WRITER)\n");
	printIds();

	//ScanEdge
	scanEdge("RATE");
	fprintf(stderr,"(scanNode RATE)\n");
	printIds();

	scanEdge("ESC");
	fprintf(stderr,"(scanNode ESC)\n");
	printIds();

	scanEdge("BUY");
	fprintf(stderr,"(scanNode BUY)\n");
	printIds();

	/* CONSULTA 3 */

	fprintf(stderr,"(getNodeType 5)\n");
	getNodeType(5);
	printLabels();

	fprintf(stderr,"(getNodeType 6)\n");
	getNodeType(6);
	printLabels();

	fprintf(stderr,"(getNodeType 11)\n");
	getNodeType(11);
	printLabels();	

	fprintf(stderr,"(getEdgeType 8)\n");
	getEdgeType(8);
	printLabels();

	fprintf(stderr,"(getEdgeType 11)\n");
	getEdgeType(11);
	printLabels();	

	/* CONSULTA 4 */

	//Nodos 

	fprintf(stderr,"(getNodeAttribute id 3 att 0)\n");
	getNodeAttribute(3,0);
	printLabels();	

	fprintf(stderr,"(getNodeAttribute id 5 att 0)\n");
	getNodeAttribute(5,0);
	printLabels();	

	fprintf(stderr,"(getNodeAttribute id 7 att 1)\n");
	getNodeAttribute(7,1);
	printLabels();	

	fprintf(stderr,"(getNodeAttribute id 10 att 2)\n");
	getNodeAttribute(10,2);
	printLabels();	

	// Aristas 
	fprintf(stderr,"(getNodeAttribute id 4 att 1)\n");
	getEdgeAttribute(4,1);
	printLabels();	

	fprintf(stderr,"(getNodeAttribute id 4 att 3)\n");
	getEdgeAttribute(4,3);
	printLabels();	

	fprintf(stderr,"(getNodeAttribute id 9 att 2)\n");
	getEdgeAttribute(9,2);
	printLabels();	

	fprintf(stderr,"(getNodeAttribute id 11 att 2)\n");
	getEdgeAttribute(11,2);
	printLabels();	

	/* CONSULTA 5 */

	//Nodos
	fprintf(stderr,"(scan USER 0 IT)\n");
	selectNode("USER",0,"IT");
	printIds();

	fprintf(stderr,"(scan USER 0 ESP)\n");
	selectNode("USER",0,"ESP");
	printIds();

	fprintf(stderr,"(scan WRITER 2 Pedro Feijoo)\n");
	selectNode("WRITER",2,"Pedro Feijoo");
	printIds();

	//Aristas
	fprintf(stderr,"(scan RATE 1 9)\n");
	selectEdge("RATE",1,"9");
	printIds();

	fprintf(stderr,"(scan RATE 3 05/07)\n");
	selectEdge("RATE",3,"05/07");
	printIds();

	fprintf(stderr,"(scan ESC 2 85)\n");
	selectEdge("ESC",2,"85");
	printIds();

	fprintf(stderr,"(scan BUY 2 86)\n");
	selectEdge("BUY",2,"86");
	printIds();	

	fprintf(stderr,"(scan BUY 0 NUEV0)\n");
	selectEdge("BUY",0,"NUEVO");
	printIds();	

	/* CONSULTA 6 */
	fprintf(stderr,"(getNeighbours 5 BOOK)\n");
	getNeighbours("BOOK",5);
	printIds();

	fprintf(stderr,"(getNeighbours 5 USER)\n");
	getNeighbours("USER",5);
	printIds();

	fprintf(stderr,"(getNeighbours 0 BOOK)\n");
	getNeighbours("BOOK",0);
	printIds();

	fprintf(stderr,"(getNeighbours 6 WRITER)\n");
	getNeighbours("WRITER",6);
	printIds();

	/* CONSULTA 7 */
	fprintf(stderr,"(getRelated 0 RATE)\n");
	getRelated("RATE",0);
	printIds();

	fprintf(stderr,"(getRelated 5 RATE)\n");
	getRelated("RATE",5);
	printIds();


	fprintf(stderr,"(getRelated 2 BUY)\n");
	getRelated("BUY",2);
	printIds();


	endBuffer();

}


