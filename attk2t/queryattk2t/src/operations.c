#include "operations.h"

/* Operación 1: GetType */
void getTypes(int isNode){
	int i;
	TYPE * type = (isNode)?GRAPH.nodes:GRAPH.edges;
	BUFFER.numResults = (isNode)?GRAPH.numTypeNodes:GRAPH.numTypeEdges;
	for (i=0;i<BUFFER.numResults;i++){
		BUFFER.labels[i]=type[i].tag;
	}
}

void getNodeTypes(){
	return getTypes(1);
}

void getEdgeTypes(){
	return getTypes(0);
}

/* Operacion 2: Scan */

void scan(int isNode, char * label){
	int i;
	TYPE * type  = (isNode)?GRAPH.nodes:GRAPH.edges;
	int numTypes = (isNode)?GRAPH.numTypeNodes:GRAPH.numTypeEdges; 
	BUFFER.numResults = 0;
	for (i=0;i<numTypes;i++){
		if (!strcmp(type[i].tag,label)){
			BUFFER.numResults = 2;
			BUFFER.ids[0] =  type[i].initial;
			BUFFER.ids[1] =	 type[i].initial + type[i].numElems - 1;
			break;
		}
	}

}

void scanNode(char * label){
	scan(1,label);
}

void scanEdge(char * label){
	scan(0,label);
}

/* Operación 3 */

void getType(int isNode, int id){
	int i;
	TYPE * type = (isNode)?GRAPH.nodes:GRAPH.edges;
	int numTypes = (isNode)?GRAPH.numTypeNodes:GRAPH.numTypeEdges; 

	BUFFER.numResults = 0;
	for (i=0;i<numTypes;i++){
		if (id>=type[i].initial && id<(type[i].initial + type[i].numElems)){
			BUFFER.numResults = 1;
			BUFFER.labels[0]=type[i].tag;
			break;
		}
	}
}

void getNodeType(int id){
	getType(1,id);
}

void getEdgeType(int id){
	getType(0,id);
}

/* Operación 4 */

void getAttribute(int isNode, int id, int indexAtt){
	int i;
	ATTRIBUTE * atts = (isNode)?GRAPH.attNodes:GRAPH.attEdges;
	if (atts[indexAtt].isK2T){
		compactTreeAdjacencyList(atts[indexAtt].attK2T->tree,id);
		if (!BUFFER.numResults) return;
		BUFFER.labels[0] = atts[indexAtt].attK2T->etiq[BUFFER.ids[0]];
	}
	else{
		TYPE * type = (isNode)?GRAPH.nodes:GRAPH.edges;
		int numTypes = (isNode)?GRAPH.numTypeNodes:GRAPH.numTypeEdges;
		BUFFER.numResults = 0; 
		for (i=0;i<numTypes;i++){
			if (id>=type[i].initial && id<(type[i].initial + type[i].numElems)){
				BUFFER.numResults = 1;
				int idRel = id -type[i].initial;
				BUFFER.labels[0] = atts[indexAtt].attList->etiq[idRel];
				break;
			}
		}
	}
}

void getNodeAttribute(int id, int indexAtt){
	getAttribute(1,id,indexAtt);
}

void getEdgeAttribute(int id, int indexAtt){
	getAttribute(0,id,indexAtt);
}

char ** selectEtiq;

int cmpEtiq(const void * a, const void * b)
{
   char * label = (char *)a;
   int posB = *(int *)b;
   return strcmp(label,selectEtiq[posB]);
}

/* Operación 5 */
void selectOp(char * type, int isNode, int indexAtt, char * label){
	int i;
	//rango ids del tipo
	scan(isNode, type);
	if (!BUFFER.numResults) return;
	int initialId = BUFFER.ids[0];
	int endId = BUFFER.ids[1];
	ATTRIBUTE * atts = (isNode)?GRAPH.attNodes:GRAPH.attEdges;
	BUFFER.numResults = 0;
	if (atts[indexAtt].isK2T){
		int indexLabel = -1;
		for (i=0;i<atts[indexAtt].attK2T->numEtiq;i++){
			if (!strcmp(atts[indexAtt].attK2T->etiq[i],label)){
				indexLabel = i;
				break;
			}
		}
		if (indexLabel == -1) return;
		struct timeval tv1, tv2;
		gettimeofday(&tv1, NULL);
		compactTreeRangeQuery(atts[indexAtt].attK2T->tree,initialId,endId,indexLabel,indexLabel);
		/*gettimeofday(&tv2, NULL);
		fprintf(stderr,
			"Tiempo total: %ld en us\n",
			(tv2.tv_sec - tv1.tv_sec) * 1000000
			+ (tv2.tv_usec - tv1.tv_usec));*/
	}
	else{
		// Busqueda binaria de la etiqueta
		selectEtiq = atts[indexAtt].attList->etiq;
		int * pos = bsearch(label,atts[indexAtt].attList->order,atts[indexAtt].attList->numEtiq,sizeof(int),cmpEtiq);
		if (pos == NULL){
			BUFFER.numResults = 0;
		}
		else{
			int indexOrder = pos - atts[indexAtt].attList->order;
			int posOrder = indexOrder - 1;
			BUFFER.numResults = 1;
			BUFFER.ids[0] = *pos + initialId;
			//Buscamos anteriores y siguientes por si hay repetidos
			while (posOrder >=0 && !strcmp(label, atts[indexAtt].attList->etiq[atts[indexAtt].attList->order[posOrder]])){
				BUFFER.ids[BUFFER.numResults++] = atts[indexAtt].attList->order[posOrder] + initialId;
				posOrder--;
			}
			posOrder = indexOrder + 1;
			while (posOrder < atts[indexAtt].attList->numEtiq && !strcmp(label, atts[indexAtt].attList->etiq[atts[indexAtt].attList->order[posOrder]])){
				BUFFER.ids[BUFFER.numResults++] = atts[indexAtt].attList->order[posOrder] + initialId;
				posOrder++;
			}
		}
	}
}

void selectNode(char * type, int indexAtt, char * label){
	selectOp(type, 1, indexAtt, label);
}

void selectEdge(char * type, int indexAtt, char * label){
	selectOp(type, 0, indexAtt, label);
}

/* Operación 6 */

void getNeighbours(char * labelType, int id){
	//rango ids del tipo
	scan(1, labelType);
	if (!BUFFER.numResults) return;
	int initialId 	= BUFFER.ids[0];
	int endId 		= BUFFER.ids[1];
	compactTreeRangeQueryLinks(GRAPH.links, GRAPH.links->tree, id, id, initialId, endId);
}


/* Operación 7 */

void getRelated (char * labelType,int id){
	scan(0, labelType);
	if (!BUFFER.numResults) return;
	int initialId 	= BUFFER.ids[0];
	int endId 		= BUFFER.ids[1];
	compactTreeAdjacencyListLinks(GRAPH.links,GRAPH.links->tree,id,initialId,endId);
}

