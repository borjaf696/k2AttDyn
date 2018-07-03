#include "kTree.h"
#include "kTreeMulti.h"
#include "Buffer.h"


void recursiveRangeQueryLinks(LINKS * links, TREP * trep, MREP * rep,uint p1, uint p2, uint q1, uint q2, uint dp, uint dq,uint x,int l);

void recursiveRangeQueryLinks(LINKS * links,TREP * trep, MREP * rep,uint p1, uint p2, uint q1, uint q2, uint dp, uint dq,uint x,int l){


	int i,j,leaf;
	uint y, divlevel, p1new, p2new, q1new, q2new;
	if(l==trep->maxLevel){	
		for(i=p1;i<=p2;i++){
			leaf = x+i*p1;
			for(j=q1;j<=q2;j++){
				leaf=x+j;
				if(isBitSet(rep->il,leaf)){
					int indexLeaves = rank(rep->il,leaf)-1;
					//Es multi
					if (isBitSet(links->bitmap,indexLeaves)){
						int posB = rank(links->bitmap,indexLeaves);
						int nextMulti = bselect(links->bitmap,posB+1);
						int tope = (nextMulti == links->lenFirst)? GRAPH.links->lenNext : links->first[nextMulti]; 
						for (i=links->first[indexLeaves];i<tope;i++){
							BUFFER.ids[BUFFER.numResults++] = links->next[i];
						}
					}
					else{
						BUFFER.ids[BUFFER.numResults++] = links->first[indexLeaves];
					}
				}
			}
			leaf+=K;
		}
	}
		
	if(((l==trep->maxLevel-1)&&(bitget(rep->bn->data,x-rep->bt_len)))){
		y=(rank(rep->bn,x-rep->bt_len)-1)*K*K;
		for(i=p1;i<=p2;i++){				
 				for(j=q1;j<=q2;j++){
	 				recursiveRangeQueryLinks(links, trep,rep,0,0,0,0,dp + i,dq+j,y+K*i+j,l+1);	 		
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
				recursiveRangeQueryLinks(links, trep,rep,p1new,p2new,q1new,q2new,dp + divlevel*i,dq+divlevel*j,y+K*i+j,l+1);	 		
			}
		}		
	}	
 	return;
}


void compactTreeRangeQueryLinks(LINKS * links, TREP * trep, uint p1, uint p2, uint q1, uint q2){
	BUFFER.numResults = 0;
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
			recursiveRangeQueryLinks(links, trep,rep, p1new,p2new,q1new,q2new,0,0,-1,-1);
		}
	}

}



// VECINOS DIRECTOS PARA LINKS


void compactAdjacencyListLinks(LINKS * links, TREP * trep, MREP * rep, int x, int idIni, int idEnd){
	int m;
	if(rep->numberOfEdges==0)
		return;
	BUFFER.numResults=0;
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

					int pos = posInf+(i+(x%K)*K);
					if(isBitSet(rep->il, pos)){
						int indexLeaves = rank(rep->il,pos)-1;
						//Es multi
						if (isBitSet(links->bitmap,indexLeaves)){
							int posB = rank(links->bitmap,indexLeaves);
							int nextMulti = bselect(links->bitmap,posB+1);
							int tope = (nextMulti == links->lenFirst)? GRAPH.links->lenNext : links->first[nextMulti]; 
							for (m=links->first[indexLeaves];m<tope;m++){
								if (links->next[m]>=idIni && links->next[m]<=idEnd){
									BUFFER.ids[BUFFER.numResults++] = links->next[m];	
								}
							}
						}
						else{
							if (links->first[indexLeaves]>=idIni && links->first[indexLeaves]<=idEnd)
								BUFFER.ids[BUFFER.numResults++] = links->first[indexLeaves];
						}
					}
				}
			}
		}
		RemoveItem2(trep);
	}
}

void compactTreeAdjacencyListLinks(LINKS * links, TREP * trep, int x, int idIni, int idEnd){
	BUFFER.numResults=0;
	MREP * rep;
	uint i;
	uint xrelatIn = x/trep->tamSubm;

	x = x%trep->tamSubm;

	for(i=0;i<trep->part;i++){
		rep=trep->submatrices[xrelatIn][i];
		trep->columna=i;
		compactAdjacencyListLinks(links, trep,rep,x,idIni,idEnd);

	}
	return;
		
}


