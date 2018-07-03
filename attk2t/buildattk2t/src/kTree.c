/*
    k-ary tree
        creation
        traversal  
        
    Notes: 
    1.  both creation and traversal follow BFS      
    2.  parent pointer is stored just to show that the tree is created
        correctly, its not used in any way to aid in creation and 
        traversal of the tree
*/

#include "kTree.h"

typedef struct QUEUE
{
    NODE *element;
    struct QUEUE *link;
    int basex;
    int basey;
}QUEUE;/*for implementing BFS*/

typedef struct QUEUE2
{
    int element;
    struct QUEUE2 *link;
    int basey;
    int basex;
}QUEUE2;/*for implementing BFS*/

typedef struct QUEUECONS
{
    NODE *element;
    struct QUEUECONS *link;

}QUEUECONS;/*for implementing BFS*/

QUEUE * finalQUEUE;
QUEUE2 * finalQUEUE2;
QUEUECONS * finalQUEUECONS;
int max_Level;


uint *div_level_table;

QUEUE * AddItem (QUEUE * listpointer, NODE * elem, int cantx, int canty) {

    if(listpointer != NULL){
	  	QUEUE * lp = (QUEUE  *) malloc (sizeof (struct QUEUE));
	  	finalQUEUE -> link = lp;
			lp -> link = NULL;
			lp -> element = elem;
			lp -> basex = cantx;
			lp -> basey = canty;
			finalQUEUE = lp;
			return listpointer;
		}
		else{
			listpointer = (QUEUE  *) malloc (sizeof (struct QUEUE));
			listpointer -> link = NULL;
			listpointer -> element = elem;
			listpointer -> basex = cantx;
			listpointer -> basey = canty;
			finalQUEUE = listpointer;
			return listpointer;
		}
	
}

QUEUE * RemoveItem (QUEUE * listpointer) {

    QUEUE * tempp;
//    printf ("Element removed is %d\n", listpointer -> dataitem);
    tempp = listpointer -> link;
    free (listpointer);
    return tempp;
}

void ClearQueue (QUEUE * listpointer) {

    while (listpointer != NULL) {
				listpointer = (QUEUE *)RemoveItem (listpointer);
    }
}




void AddItem2 (TREP *rep, int elem, int cantx,int canty) {
  	if(rep->iniq!=-1){
	    rep->finq++;
			rep -> element[rep->finq] = elem;
			rep -> basex[rep->finq] = cantx;
			rep -> basey[rep->finq] = canty;
			
		}
		else{
			rep->iniq=0;
			rep->finq=0;
			rep -> element[rep->iniq] = elem;
			rep -> basex[rep->iniq] = cantx;
			rep -> basey[rep->iniq] = canty;
		}
}

void RemoveItem2 (TREP * rep) {

	rep->iniq++;
}

QUEUECONS * AddItemCONS (QUEUECONS * listpointer, NODE * elem) {

  	if(listpointer!=NULL){
	    QUEUECONS * lp = (QUEUECONS  *) malloc (sizeof (struct QUEUECONS));
	  	finalQUEUECONS -> link = lp;
			lp -> link = NULL;
			lp -> element = elem;
			finalQUEUECONS = lp;
			return listpointer;
		}
		else{
			listpointer = (QUEUECONS  *) malloc (sizeof (struct QUEUECONS));
			listpointer -> link = NULL;
			listpointer -> element = elem;
			finalQUEUECONS = listpointer;
			return listpointer;
		}
}

QUEUECONS * RemoveItemCONS (QUEUECONS * listpointer) {
    QUEUECONS * tempp;
    tempp = listpointer -> link;
    free (listpointer);
    return tempp;
}

uint exp_pow(uint base, uint pow){
	uint i, result = 1;
	for(i=0;i<pow;i++)
		result*=base;
	return result;
}

NODE * createKTree(int maxlevels){
	NODE * n = (NODE *) malloc(sizeof(struct node));
	n->child=NULL;
	n->data=0;
	max_Level = maxlevels;
	numberNodes =0;
	numberLeaves = 0;
	numberTotalLeaves=0;
	return n;
}


MREP * loadRepresentation(char * basename){
	MREP * rep;
	rep = (MREP *) malloc(sizeof(struct matrixRep));
	rep->bt = (bitRankW32Int *) malloc(sizeof(struct sbitRankW32Int));
	rep->bn = (bitRankW32Int *) malloc(sizeof(struct sbitRankW32Int));	
	
	fprintf(stderr,"Recovering tree bitmap\n");
	char *filename = (char *) malloc(sizeof(char)*(strlen(basename)+4));
  	strcpy(filename,basename);
  	strcat(filename,".tr");
  	FILE * ft = fopen(filename,"r");
  	load(rep->bt,ft);
  	fclose(ft);
  	rep->bt_len = rep->bt->n;
  	fprintf(stderr,"Bitmap recovered (len: %d bits)\n",rep->bt_len);
  	  
  	fprintf(stderr,"Recovering leaves bitmap\n");
  	strcpy(filename,basename);
	strcat(filename,".lv");
	FILE * fn = fopen(filename,"r");
	load(rep->bn,fn);
	fclose(fn);  
	rep->bn_len = rep->bn->n;
	fprintf(stderr,"Bitmap recovered (len: %d bits)\n",rep->bn_len);
	  
	fprintf(stderr,"Recovering leaves information\n");
	strcpy(filename,basename);
	strcat(filename,".il");
	FILE * fi = fopen(filename,"r");
	fread(&(rep->numberOfNodes),sizeof(uint),1,fi);
	fprintf(stderr,"Number of nodes : %d\n",rep->numberOfNodes);
	fread(&(rep->numberOfEdges),sizeof(uint),1,fi);
	fprintf(stderr,"Number of edges : %d\n",rep->numberOfEdges);
  	fread(&(rep->nleaves),sizeof(uint),1,fi);
  	fprintf(stderr,"Leaves to read: %d\n",rep->nleaves);
  	rep->leavesInf = (uint *)malloc(sizeof(uint)*(rep->nleaves*K*K/W+1));
  	fread(rep->leavesInf,sizeof(uint),rep->nleaves*K*K/W+1,fi);
  	fclose(fi);  
  	fprintf(stderr,"Leaves information recovered (len: %d bits)\n",rep->nleaves*K*K);
  	free(filename);
  	return rep;
}

void destroyRepresentation(MREP * rep, int isMulti){
	if (rep->numberOfEdges){
		destroyBitRankW32Int(rep->bt);
		destroyBitRankW32Int(rep->bn);
	}	
	if (isMulti){
		destroyBitRankW32Int(rep->il);
	}
	else{
		free(rep->leavesInf);
	}
	free(rep);
}

void adjacencyList(NODE * root, int x){
	QUEUE * q = NULL;
	finalQUEUE = q;
	int i, k, j, queuecont, conttmp,node,div_level,xrelat;
	q = AddItem(q,root,0,0);
	queuecont = 1;
	for(i=0;i<max_Level;i++){
		conttmp = 0;
		div_level = exp_pow(K,max_Level-i);
		for(k=0;k<queuecont;k++){
			if(q->element->child!=NULL){
				for(j=0;j<K;j++){
					xrelat = (x-(q->basey));
					node = xrelat/div_level*K + j;
					conttmp++;
					q=AddItem(q,q->element->child[node],q->basex+j*div_level,q->basey+xrelat/div_level*div_level);
				}
			}
			q = (QUEUE *)RemoveItem(q);
		}
		queuecont = conttmp;
	}
	while(q!=NULL){
		for(i=0;i<K;i++){
			if((((q->element)->data)&(0x1<<(i+(x%K)*K))))
				printf("%d\n",q->basex+i);
			}
		q = (QUEUE *)RemoveItem(q);
	}
}


uint * compactAdjacencyList(TREP * trep, MREP * rep, int x){
	trep->info[0]=0;
	if(rep->numberOfEdges==0)
		return trep->info;
	trep->iniq=-1;
	trep->finq=-1;
	uint nleaf,posInf, nleafrelat;
	int i, k, j, queuecont, conttmp,node,div_level,xrelat;
	AddItem2(trep,0,0,x);
	queuecont = 1;
	for(i=0;i<trep->maxLevel-1;i++){
		conttmp = 0;
		div_level = trep->div_level_table[i];
		for(k=0;k<queuecont;k++){
				for(j=0;j<K;j++){
					xrelat = trep->basey[trep->iniq];
					node = xrelat/div_level*K + j;				
					node += trep->element[trep->iniq];
					if(isBitSet(rep->bt,node)){
						conttmp++;
						AddItem2(trep,rank(rep->bt,node)*K*K,trep->basex[trep->iniq]+j*div_level,trep->basey[trep->iniq]%div_level);
					}
				}
			
			RemoveItem2(trep);
		}
		queuecont = conttmp;
	}
	while(trep->iniq<=trep->finq){
		nleaf = trep->element[trep->iniq]-rep->bt_len;
		for(j=0;j<K;j++){
			nleafrelat = nleaf + (trep->basey[trep->iniq]/K)*K+j;
			if(isBitSet(rep->bn,nleafrelat)){
				posInf = (rank(rep->bn,nleafrelat)-1)*K*K;
				for(i=0;i<K;i++){
					if(bitget(rep->leavesInf,posInf+(i+(x%K)*K))){
						trep->info[0]++;
						trep->info[trep->info[0]]=trep->basex[trep->iniq]+i+K*j+trep->columna*trep->tamSubm;
					}
				}
			}
		}
		RemoveItem2(trep);
	}
	return trep->info;
}



uint * compactInverseList(TREP * trep, MREP * rep, int y){
	if(rep->numberOfEdges==0)
		return trep->info;
	trep->iniq=-1;
	trep->finq=-1;
	uint nleaf,posInf, nleafrelat;
//	uint summemoria =0;

	int i, k, j, queuecont, conttmp,node,div_level,yrelat;
	//fprintf(stderr,"Aqui llego0\n");
	AddItem2(trep,0,y,0);
	//fprintf(stderr,"Tama�o de la estructura: %d\n",(int) sizeof(struct QUEUE2));
//	summemoria+=sizeof(struct QUEUE2);
	//fprintf(stderr,"Aqui llego1\n");
	queuecont = 1;
	for(i=0;i<trep->maxLevel-1;i++){
		conttmp = 0;
		//	fprintf(stderr,"Aqui llego2\n");

		div_level = trep->div_level_table[i];
		//div_level_x = x/div_level*K;
		//fprintf(stderr,"Nivel: %d, div_level %d, queuecont %d\n",i,div_level,queuecont);
		for(k=0;k<queuecont;k++){
				for(j=0;j<K;j++){
					yrelat = trep->basex[trep->iniq];
					node = K*j+yrelat/div_level;
					node += trep->element[trep->iniq];
			//		fprintf(stderr,"node: %d %d\n",node,rep->basey[rep->iniq]);
		
					if(isBitSet(rep->bt,node)){
				//		fprintf(stderr,"Isbitsetnode: %d %d\n",node,yrelat);
						conttmp++;
					//	fprintf(stderr,"Anhadiendo nodo hijo con basex %d basey %d\n",rep->basex[rep->iniq]%div_level,rep->basey[rep->iniq]+j*div_level);
						//fprintf(stderr,"Y con element: rank(%d)=%d\n",node,rank(rep->bt,node)*K*K);
						AddItem2(trep,rank(rep->bt,node)*K*K,trep->basex[trep->iniq]%div_level,trep->basey[trep->iniq]+j*div_level);
	//						summemoria+=sizeof(struct QUEUE2);
					}
				}
			
			RemoveItem2(trep);
		}
		queuecont = conttmp;
	}
	while(trep->iniq<=trep->finq){
		nleaf = trep->element[trep->iniq]-rep->bt_len;
		//fprintf(stderr,"\nMirando la hoja %d (bt_len = %d)con basey %d\n",nleaf,rep->bt_len,rep->basey[rep->iniq]);
		for(j=0;j<K;j++){
			nleafrelat = nleaf + j*K+ (trep->basex[trep->iniq]/K);
			//fprintf(stderr,"Relativo %d:, isbitset: %d\n",nleafrelat,isBitSet(rep->bn,nleafrelat));

			if(isBitSet(rep->bn,nleafrelat)){
				//fprintf(stderr,"Esta el bit a 1! posinf sera: %d\n",(rank(rep->bn,nleafrelat)-1)*K*K);
				posInf = (rank(rep->bn,nleafrelat)-1)*K*K;
				//fprintf(stderr,"quecont: %d\n Datos: %x\n",queuecont,rep->element[rep->iniq]);
				for(i=0;i<K;i++){
					//fprintf(stderr,"probando relativo %d, total %d....Acierto: bitget%d\n",i*K+(y%K), posInf+(i*K+(y%K)),bitget(rep->leavesInf,posInf+(i*K+(y%K))));
					if(bitget(rep->leavesInf,posInf+(i*K+(y%K)))){
						
						trep->info[0]++;
						trep->info[trep->info[0]]=trep->basey[trep->iniq]+i+j*K+trep->fila*trep->tamSubm;
					}
				}
			}
		}
		RemoveItem2(trep);
	}
	//fprintf(stderr,"suma de memoria total....%d\n",summemoria);
	
	return trep->info;
}


MREP * createRepresentation(NODE * root, uint numberOfNodes,uint numberOfEdges, int isMulti){
	MREP * rep;
	rep = malloc(sizeof(struct matrixRep));
	//rep->maxLevel = max_Level;
	rep->numberOfNodes = numberOfNodes;
	rep->numberOfEdges = numberOfEdges;

	uint bits_BT_len = numberNodes;
	uint bits_BN_len = numberTotalLeaves;
	uint bits_LI_len = numberLeaves*K*K;

	uint i, k, j, queuecont, conttmp,node, pos=0;


	
	bitRankW32Int *BT, *BN;
//	fprintf(stderr,"bits_BT_len= %u bits_BN_len= %u bits_LI_len= %u\n",bits_BT_len,bits_BN_len,bits_LI_len);
	uint * bits_BT = (uint*)malloc(sizeof(uint)*((bits_BT_len/W+1)));
	//fprintf(stderr,"malloc for bits_BT = %x", bits_BT);
	uint * bits_BN = (uint*)malloc(sizeof(uint)*((bits_BN_len/W+1)));
	//fprintf(stderr,"malloc for bits_BN = %x", bits_BN);
	uint * bits_LI = (uint*)malloc(sizeof(uint)*((bits_LI_len/W+1)));
	//fprintf(stderr,"malloc for bits_LI = %x", bits_LI);
	for(i=0; i<bits_BT_len/W+1;i++)
		bits_BT[i]=0;
	for(i=0; i<bits_BN_len/W+1;i++)
		bits_BN[i]=0;
	for(i=0; i<bits_LI_len/W+1;i++)
		bits_LI[i]=0;
		
	char isroot=1;
	QUEUECONS * q=NULL;
	finalQUEUECONS = q;
	q = AddItemCONS(q,root);
	queuecont = 1;
	for(i=0;i<max_Level;i++){
		conttmp = 0;
		//div_level_x = x/div_level*K;
		//printf("Nivel: %d, div_level %d, queuecont %d\n",i,div_level,queuecont);
		for(k=0;k<queuecont;k++){
		//	fprintf(stderr,"Nivel: %d, div_level %d, queuecont %d k %d\n",i,div_level,queuecont, k);

			if(q->element->child!=NULL){
				for(j=0;j<K*K;j++){
					node = j;
			//		fprintf(stderr,"node: %d\n",node);
					conttmp++;
				//	fprintf(stderr,"Anhadiendo nodo hijo con basex %d basey %d\n",q->basex+j*div_level,q->basey+xrelat/div_level*div_level);
					q=AddItemCONS(q,q->element->child[node]);
					
					}
					if(!isroot)
						bitset(bits_BT,pos);
					free(q->element->child);
					
			}
			if(!isroot)
				pos++;
			isroot=0;
			//fprintf(stderr,"Contenido bitmap:  ");
			//for(j=0; j<pos;j++)
			//	fprintf(stderr,"%x",bitget(bits_BT,j));
			//fprintf(stderr,"\n");
			free(q->element);
			q = (QUEUECONS *)RemoveItemCONS(q);
		}
		queuecont = conttmp;
	}
//	fprintf(stderr,"Longitud bit_Array: %d\n",pos);
//		fprintf(stderr,"Contenido bitmap:  ");
//		for(i=0; i<600;i++){
//			if((i==4)||(i==20)||(i==56)||(i==156)||(i==556))
//				fprintf(stderr,"\n");
//			fprintf(stderr,"%x",bitget(bits_BT,i));
//		}
//		fprintf(stderr,"\n");

	//TODO: VER SI ESTA BIEN AÑADIDA LA CONDICION

	//fprintf(stderr,"bit_len:%d\n",bits_BT_len);
//	if (bits_BT_len!=0){
		BT = createBitRankW32Int(bits_BT, bits_BT_len , 1, 20);
		rep->bt = BT;
		rep->bt_len = pos;
	/*}else{
		rep->bt=NULL;
		rep->bt_len = 0;
	}*/

	pos=0;
	uint pos_inf=0;
//	fprintf(stderr,"Empezando bitmap de hojas utiles\n");
	while(q!=NULL){
//		fprintf(stderr,"quecont: %d\n Datos: %x\n",queuecont,q->element->data);
		if(((q->element)->data)){
//			fprintf(stderr,"poniendo a uno el bit %d\n",pos);
				bitset(bits_BN,pos);
			
				for(i=0;i<K*K;i++){
			//fprintf(stderr,"probando %d, %x %x %x\n",i+(x%K)*K,(q->element)->data,(0x1<<(i+(x%K)*K)),((q->element)->data)&(0x1<<(i+(x%K)*K)));
					if(((q->element)->data)&(0x1<<i)){
						bitset(bits_LI,pos_inf);
						//fprintf(stderr,"cont_idList: %d\n",cont_idList);
					}
					pos_inf++;
			}

		}
					pos++;
			free(q->element);

//			fprintf(stderr,"Contenido bitmap:  ");
//			for(i=0; i<pos;i++)
//				fprintf(stderr,"%x",bitget(bits_BN,i));
//			fprintf(stderr,"\n");
		q = (QUEUECONS *)RemoveItemCONS(q);
	}
//			fprintf(stderr,"Contenido bitmap BN (long: %d):  ", pos);
//		for(i=0; i<pos;i++)
//			fprintf(stderr,"%x",bitget(bits_BN,i));
//		fprintf(stderr,"\n");


//			fprintf(stderr,"Contenido bitmap LI (long: %d):  ", pos_inf);
//		for(i=0; i<pos_inf;i++)
//			fprintf(stderr,"%x",bitget(bits_LI,i));
//		fprintf(stderr,"\n");

	if (bits_BN_len!=0){
		BN = createBitRankW32Int(bits_BN, bits_BN_len , 1, 20);
		rep->bn = BN;
		rep->bn_len = pos;
	}
	else {
		rep->bn=     NULL;
		rep->bn_len= 0;
	}

	if (isMulti){
		rep->il = createBitRankW32Int(bits_LI,bits_LI_len , 1, 20); 
		rep->il_len = bits_LI_len;
	}
	else{
		rep->leavesInf = bits_LI;
		rep->nleaves = numberLeaves;
	}
	
	return rep;
}

void insertNode(NODE * root, int x, int y){
	uint l=0, i,node, div_level;
	NODE * n = root;
	while(l<=max_Level){
		div_level = exp_pow(K,max_Level-l);
		node = (x / div_level)*K+y /div_level;
		if(l==max_Level){
			if(n->data==0){
				numberLeaves++;
			}
			n->data=n->data|(0x1<<node);
		}
		else{
			if(n->child==NULL){
				if(l<max_Level-1)
					numberNodes+=K*K;
				else
					numberTotalLeaves+=K*K;
				n->child = (NODE **)malloc(sizeof(NODE *)*K*K);
				for(i=0;i<K*K;i++){
					n->child[i]=(NODE *) malloc(sizeof(struct node));
					n->child[i]->child=NULL;
					n->child[i]->data=0;
				}
			}
			n = n->child[node];
		}
		x = x % div_level;
		y = y % div_level;
		l++;
	}
	
}


TREP * createTreeRep(uint nodesOrig,uint edges,uint part,uint subm, uint max_level){
		TREP * trep;
		trep = malloc(sizeof(struct treeRep));
		trep->part=part;
    trep->tamSubm=subm;
    trep->numberOfNodes=nodesOrig;
    trep->numberOfEdges=edges;
    trep->maxLevel=max_level;
    
    trep->submatrices=(MREP ***)malloc(sizeof(MREP **)*part);
    int i;
    for(i=0;i<part;i++){
    	trep->submatrices[i]=(MREP **)malloc(sizeof(MREP *)*part);
    }


		
		trep->info = (uint *)malloc(sizeof(uint)*MAX_INFO);
			
		trep->info2[0] = (uint *)malloc(sizeof(uint)*MAX_INFO);
	
		trep->info2[1] = (uint *)malloc(sizeof(uint)*MAX_INFO);
	
		trep->element = (uint *)malloc(sizeof(uint)*MAX_INFO);	
	
		trep->basex = (uint *)malloc(sizeof(uint)*MAX_INFO);
	
		trep->basey = (uint *)malloc(sizeof(uint)*MAX_INFO);
	
		trep->iniq = -1;
		trep->finq =-1;
		trep->div_level_table = (uint *)malloc(sizeof(uint)*trep->maxLevel);
	
		for(i=0;i<trep->maxLevel;i++){
			trep->div_level_table[i]=exp_pow(K,trep->maxLevel-i);
		}

    return trep;

}

void insertIntoTreeRep(TREP * trep, MREP * rep, uint i, uint j){
	trep->submatrices[i][j]=rep;
	
}


void saveTreeRep(TREP * trep, char * basename, int isMulti){
  char *filename = (char *) malloc(sizeof(char)*(strlen(basename)+4));
  strcpy(filename,basename);
  strcat(filename,".tr");
  FILE * ft = fopen(filename,"w");
  uint part= trep->part;
	int fila,columna;
	MREP* rep;
	for(fila=0;fila<part;fila++){
		for(columna=0;columna<part;columna++){
			if(trep->submatrices[fila][columna]->numberOfEdges!=0)
				save(trep->submatrices[fila][columna]->bt,ft);
		}
	}
  fclose(ft);

  strcpy(filename,basename);
  strcat(filename,".lv");
  FILE * fn = fopen(filename,"w");
	for(fila=0;fila<part;fila++){
		for(columna=0;columna<part;columna++){
				if(trep->submatrices[fila][columna]->numberOfEdges!=0){
				  save(trep->submatrices[fila][columna]->bn,fn);
				}
			}
		}
  fclose(fn);  
  
  strcpy(filename,basename);
  strcat(filename,".il");
  FILE * fi = fopen(filename,"w");

  fwrite(&(trep->part),sizeof(uint),1,fi);
  fwrite(&(trep->tamSubm),sizeof(uint),1,fi);

  fwrite(&(trep->numberOfNodes),sizeof(uint),1,fi);
  fwrite(&(trep->numberOfEdges),sizeof(uint),1,fi);
  
  fwrite(&(trep->maxLevel),sizeof(uint),1,fi);
 
	for(fila=0;fila<part;fila++){
		for(columna=0;columna<part;columna++){  
		  rep=trep->submatrices[fila][columna];
		  fwrite(&(rep->numberOfNodes),sizeof(uint),1,fi);
		  fwrite(&(rep->numberOfEdges),sizeof(uint),1,fi);
 		  if(rep->numberOfEdges==0)
				continue;

		  fwrite(&(rep->nleaves),sizeof(uint),1,fi);
		  if (isMulti){
		  	save(rep->il,fi);
		  }
		  else{
		  	fwrite (rep->leavesInf,sizeof(uint),rep->nleaves*K*K/W+1,fi);	
		  }
		  
		}
	}
  	fclose(fi);   
	free(filename);
}



TREP * loadTreeRepresentation(char * basename){
	TREP * trep;
	MREP * rep;
	int i,j,k;
	
	trep = malloc(sizeof(struct treeRep));
	char *filename = (char *) malloc(sizeof(char)*(strlen(basename)+4));

	strcpy(filename,basename);
  	strcat(filename,".il");
  	FILE * fi = fopen(filename,"r");

  	fread(&(trep->part),sizeof(uint),1,fi);
  	fread(&(trep->tamSubm),sizeof(uint),1,fi);

  	fread(&(trep->numberOfNodes),sizeof(uint),1,fi);
  	fread(&(trep->numberOfEdges),sizeof(uint),1,fi);
	
	fread(&(trep->maxLevel),sizeof(uint),1,fi);
	
	trep->div_level_table = (uint *)malloc(sizeof(uint)*trep->maxLevel);
	for(k=0;k<trep->maxLevel;k++)
		trep->div_level_table[k]=exp_pow(K,trep->maxLevel-k);
	
	trep->info = (uint *)malloc(sizeof(uint)*MAX_INFO);
	trep->info2[0] = (uint *)malloc(sizeof(uint)*MAX_INFO);
	trep->info2[1] = (uint *)malloc(sizeof(uint)*MAX_INFO);
	trep->element = (uint *)malloc(sizeof(uint)*MAX_INFO);	
	if (trep->element==NULL) fprintf(stderr,"error!\n");
	trep->basex = (uint *)malloc(sizeof(uint)*MAX_INFO);
	trep->basey = (uint *)malloc(sizeof(uint)*MAX_INFO);
	trep->iniq = -1;
	trep->finq =-1;

    trep->submatrices=(MREP ***)malloc(sizeof(MREP **)*trep->part);

    int fila,columna;
    for(i=0;i<trep->part;i++){
    	trep->submatrices[i]=(MREP **)malloc(sizeof(MREP *)*trep->part);
    }

	for(i=0;i<trep->part;i++){
		for(j=0;j<trep->part;j++){
			rep = (MREP *) malloc(sizeof(struct matrixRep));
			rep->bt = (bitRankW32Int *) malloc(sizeof(struct sbitRankW32Int));
			rep->bn = (bitRankW32Int *) malloc(sizeof(struct sbitRankW32Int));				
			trep->submatrices[i][j]=rep;
				}
	}
   
	for(fila=0;fila<trep->part;fila++){
		for(columna=0;columna<trep->part;columna++){   		
		  rep=trep->submatrices[fila][columna];
  		  fread(&(rep->numberOfNodes),sizeof(uint),1,fi);
		  fread(&(rep->numberOfEdges),sizeof(uint),1,fi);
		  if(rep->numberOfEdges==0)
				continue;
		  fread(&(rep->nleaves),sizeof(uint),1,fi);
		  rep->leavesInf = (uint *)malloc(sizeof(uint)*(rep->nleaves*K*K/W+1));
		  fread(rep->leavesInf,sizeof(uint),rep->nleaves*K*K/W+1,fi);
		}
	}

  	fclose(fi);   
  	strcpy(filename,basename);
 	strcat(filename,".tr");
  	FILE * ft = fopen(filename,"r");
	for(fila=0;fila<trep->part;fila++){
		for(columna=0;columna<trep->part;columna++){  
		  rep=trep->submatrices[fila][columna];
			if(rep->numberOfEdges==0)
				continue;
  		load(rep->bt,ft);
  		rep->bt_len = rep->bt->n;
  
		}
	}

  	fclose(ft);
  	strcpy(filename,basename);
  	strcat(filename,".lv");
  	FILE * fn = fopen(filename,"r");
  	for(fila=0;fila<trep->part;fila++){
		for(columna=0;columna<trep->part;columna++){  
		  rep=trep->submatrices[fila][columna];
		  
		  if(rep->numberOfEdges==0)
				continue;
		  load(rep->bn,fn);
		  rep->bn_len = rep->bn->n;
		}
	}
  	fclose(fn);  
  
	trep->div_level_table = (uint *)malloc(sizeof(uint)*trep->maxLevel);
	for(i=0;i<trep->maxLevel;i++){
		trep->div_level_table[i]=exp_pow(K,trep->maxLevel-i);
	
	}
	free(filename);
	return trep;
}


uint * compactTreeAdjacencyList(TREP * trep, int x){
	trep->info[0]=0;
	MREP * rep;
	uint i;
	uint xrelatIn = x/trep->tamSubm;

	x = x%trep->tamSubm;

	for(i=0;i<trep->part;i++){
		rep=trep->submatrices[xrelatIn][i];
		trep->columna=i;
		compactAdjacencyList(trep,rep,x);

	}
	return trep->info;
		
}


uint * compactTreeInverseList(TREP * trep, int y){
	trep->info[0]=0;
	MREP * rep;
	uint i;
	uint yrelatIn = y/trep->tamSubm;
	y = y%trep->tamSubm;
	for(i=0;i<trep->part;i++){
		rep=trep->submatrices[i][yrelatIn];
		trep->fila= i;
		compactInverseList(trep,rep,y);
	}
	return trep->info;
}

void destroyTreeRepresentation(TREP *trep, int isMulti){
	int i,j;
	for(i=0;i<trep->part;i++){
		for(j=0;j<trep->part;j++){
			destroyRepresentation(trep->submatrices[i][j],isMulti);
		}
		free(trep->submatrices[i]);
	}
	free(trep->submatrices);
	free(trep->div_level_table);
	free(trep->info2[0]);
	free(trep->info2[1]);
	free(trep->info);
	free(trep->element);
	free(trep->basex);
	free(trep->basey);
	free(trep);		
}


void recursiveRangeQuery(TREP * trep, MREP * rep,uint p1, uint p2, uint q1, uint q2, uint dp, uint dq,uint x,int l);

void recursiveRangeQuery(TREP * trep, MREP * rep,uint p1, uint p2, uint q1, uint q2, uint dp, uint dq,uint x,int l){
	int i,j,leaf;
	uint y, divlevel, p1new, p2new, q1new, q2new;
	if(l==trep->maxLevel){	
		for(i=p1;i<=p2;i++){
			//Movido de sitio! (sandra)
			leaf = x+i*p1;
			for(j=q1;j<=q2;j++){
				leaf=x+j;
				if(bitget(rep->leavesInf,leaf)){
					(trep->info2)[0][0]=(trep->info2)[0][0]+1;
						(trep->info2)[0][(trep->info2)[0][0]]=dp+i+trep->fila*trep->tamSubm;;
					(trep->info2)[1][(trep->info2)[0][0]]=dq+j+trep->columna*trep->tamSubm;;
				}
			}
			leaf+=K;
		}
			
	}
		
		
	if(((l==trep->maxLevel-1)&&(bitget(rep->bn->data,x-rep->bt_len)))){
		y=(rank(rep->bn,x-rep->bt_len)-1)*K*K;
		for(i=p1;i<=p2;i++){				
 				for(j=q1;j<=q2;j++){
	 				recursiveRangeQuery(trep,rep,0,0,0,0,dp + i,dq+j,y+K*i+j,l+1);	 		
  				}
 		}
	}
	
 		if((x==-1)||((l<trep->maxLevel-1)&&(bitget(rep->bt->data,x)))){
 			y = (rank(rep->bt,x))*K*K;	
 			divlevel =	trep->div_level_table[l+1];
 			for(i=p1/divlevel;i<=p2/divlevel;i++){
 				p1new=0;
 				if(i==p1/divlevel)
 					p1new=p1 % divlevel;
 				p2new=divlevel-1;
 				if(i==p2/divlevel)
 					p2new=p2 % divlevel;
 				for(j=q1/divlevel;j<=q2/divlevel;j++){
	 				q1new=0;
	 				if(j==q1/divlevel)
	 					q1new=q1 % divlevel;
	 				q2new=divlevel-1;
	 				if(j==q2/divlevel)
	 					q2new=q2 % divlevel;
	 				recursiveRangeQuery(trep,rep,p1new,p2new,q1new,q2new,dp + divlevel*i,dq+divlevel*j,y+K*i+j,l+1);	 		
	 			}
 			}		
 		}	
}


uint ** compactTreeRangeQuery(TREP * trep, uint p1, uint p2, uint q1, uint q2){

	trep->info2[0][0]=0;
	MREP * rep;
	uint x1,x2,y1,y2,p1new,p2new,q1new,q2new,fila,columna;
	

	if(p2>=trep->numberOfNodes)
		p2=trep->numberOfNodes-1;


	if(q2>=trep->numberOfNodes)
		q2=trep->numberOfNodes-1;

	x1=p1/trep->tamSubm;
	x2=p2/trep->tamSubm;
	y1=q1/trep->tamSubm;
	y2=q2/trep->tamSubm;


	for(fila=x1;fila<=x2;fila++){
				p1new=0;
				if(fila==x1)
 					p1new=p1 % trep->tamSubm;
 				p2new=trep->tamSubm;
 				if(fila==x2)
 					p2new=p2 % trep->tamSubm;

		for(columna=y1;columna<=y2;columna++){

			rep=trep->submatrices[fila][columna];
			
			if(rep->numberOfEdges==0)
				continue;
 				 				
	 				q1new=0;
	 				if(columna==y1)
	 					q1new=q1 %trep->tamSubm;	
	 				q2new=trep->tamSubm-1;
	 				if(columna==y2)
	 					q2new=q2 % trep->tamSubm;
			trep->fila= fila;
			trep->columna= columna;
			recursiveRangeQuery(trep,rep, p1new,p2new,q1new,q2new,0,0,-1,-1);
		}
	}
	return trep->info2;
	
}



