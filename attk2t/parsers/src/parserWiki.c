#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

long buscarId(long id, long * idIni, long * idFin, long * idReal){
	int i=0;
	while(1){
		if (idIni[i]<=id && idFin[i]>=id){
			return idReal[i]+ id -idIni[i];
		}
		i++;
	}
	return id;
}

int main(int argc, char** argv){
	int i;


	if (argc<6){
		fprintf(stderr,"uso: ./%s <titles> <images> <edgesRef> <edgesRel> <baseName>\n",argv[0]);
		return 1;
	}

	int numRuns = 500;

	//Estructura para guardar el mapeo de ids de articulos
	long * idIniA 		= (long *)malloc(sizeof(long)*numRuns);
	long * idFinA 		= (long *)malloc(sizeof(long)*numRuns);
	long * idRealIniA 	= (long *)malloc(sizeof(long)*numRuns);
	
	long * idIniI 		= (long *)malloc(sizeof(long)*numRuns);
	long * idFinI 		= (long *)malloc(sizeof(long)*numRuns);
	long * idRealIniI 	= (long *)malloc(sizeof(long)*numRuns);

	FILE * ftitles   = fopen(argv[1],"r");
	FILE * fimages 	 = fopen(argv[2],"r");
	FILE * fedgesRef = fopen(argv[3],"r");
	FILE * fedgesRel = fopen(argv[4],"r");


	// ===============
	// TABLA DE NODOS
	// ===============

	char nameFile [256];
	sprintf(nameFile,"%s.nodes.val",argv[5]);
	fprintf(stderr,"Creando %s...\n",nameFile);
	FILE * fnodeVal = fopen(nameFile,"w+");
	long id;char nlc[1024];char title[4096];
	
	// == Lectura de nodos título
	long numTitles = 0, ultimoId = 0, idRuns = 0;
	idIniA[0]=1; idRealIniA[0] = 0;
	fscanf(ftitles,"%*s");
	while (fscanf(ftitles,"%ld;%[^;];%[^\n]\n",&id,nlc,title)>0){
		fprintf(fnodeVal,"%ld\t%s\t%s\t\n",numTitles,nlc,title);
		if (ultimoId+1!=id){
			idFinA[idRuns] = ultimoId;
			idRuns++;
			idIniA[idRuns] = id;
			idRealIniA[idRuns] = numTitles;
		}
		ultimoId = id;
		numTitles++;
	}
	idFinA[idRuns++]=ultimoId;

	for (i=0;i<idRuns;i++){
		fprintf(stderr,"%ld\t%ld\t%ld\n",idIniA[i],idFinA[i],idRealIniA[i]);
	}
	fprintf(stderr,"Artículos procesados: %ld\n",numTitles);


	// == Lectura de nodos imagen
	int numImages = 0;
	fscanf(fimages,"%*s");
	idRuns = 0;
	idIniI[0] 		= 1;
	idRealIniI[0] 	= numTitles;
	ultimoId = 0;

	while (fscanf(fimages,"%ld;%[^;];%[^\n]\n",&id,nlc,title)>0){
		fprintf(fnodeVal,"%ld\t%s\t\t%s\n",numTitles+numImages,nlc,title);
		
		if (ultimoId+1!=id){
			idFinI[idRuns++] = ultimoId;
			idIniI[idRuns] = id;
			idRealIniI[idRuns] = numImages + numTitles;
		}

		ultimoId = id;
		numImages++;
	}
	idFinI[idRuns++]=ultimoId;
	fclose(ftitles);


	// =======================
	// TABLA DE TIPOS DE NODOS
	// =======================
	sprintf(nameFile,"%s.nodes.typ",argv[5]);
	fprintf(stderr,"Creando %s...\n",nameFile);
	FILE * fnodeTyp = fopen(nameFile,"w+");
	fprintf(fnodeTyp,"Articles\t%ld\n",numTitles);
	fprintf(fnodeTyp,"Images\t%d\n",numImages);
	fclose(fnodeTyp);


	// ==========================
	// TABLA DE TIPOS DE ATRIBUTO
	// ==========================
	// Una fila por cada tipo de nodo
	// 0-> no tiene ese atributo 1->es k2t 2->es lista
	sprintf(nameFile,"%s.nodes.att",argv[5]);
	fprintf(stderr,"Creando %s...\n",nameFile);
	FILE * fnodeAtt = fopen(nameFile,"w+");
	//Número de atributos:
	fprintf(fnodeAtt,"3\n");
	//Articulo: nlc y title
	fprintf(fnodeAtt,"%d\t%d\t%d\n",1,2,0);
	//Imagen: nlc y title
	fprintf(fnodeAtt,"%d\t%d\t%d\n",1,0,2);
	fclose(fnodeAtt);


	// ================
	// TABLA DE ARISTAS
	// ================
	sprintf(nameFile,"%s.edges.lnk",argv[5]);
	FILE * fedgesLinks = fopen(nameFile,"w+"); 
	sprintf(nameFile,"%s.edges.val",argv[5]);
	FILE * fedgesVal = fopen(nameFile,"w+");

	long id2;int numElementos;long numEdge = 0;int numBabel=0;int numRel=0;int numRefs=0;

	// Relaciones entre artículos
	fscanf(fedgesRel,"%*s");
	while ((numElementos = fscanf(fedgesRel,"%ld;%ld;%[^;];%[^\n]\n",&id,&id2,nlc,title))>0){
		//Sólo tiene el tipo, no tiene nlc
		if (numElementos!=4){
			fscanf(fedgesRel,";%[^\n]\n",title);
			fprintf(fedgesVal,"%ld\t\n",numEdge);
			numRel++;
		}else{
			fprintf(fedgesVal,"%ld\t%s\t\n",numEdge,nlc);
			numBabel++;
		}
		fprintf(fedgesLinks,"%ld\t%ld\t%ld\n",numEdge,buscarId(id,idIniA,idFinA,idRealIniA),buscarId(id2,idIniA,idFinA,idRealIniA));
		numEdge++;
	}

	//Relaciones entre imágenes
	fscanf(fedgesRef,"%*s");
	while ((numElementos = fscanf(fedgesRef,"%ld;%ld;\n]\n",&id,&id2))>0){
		fprintf(fedgesVal,"%ld\t\n",numEdge);
		fprintf(fedgesLinks,"%ld\t%ld\t%ld\n",numEdge,buscarId(id,idIniA,idFinA,idRealIniA),buscarId(id2,idIniI,idFinI,idRealIniI));
		numRefs++;
		numEdge++;
	}

	//Tipos de arista
	sprintf(nameFile,"%s.edges.typ",argv[5]);
	FILE * fedgesTyp = fopen(nameFile,"w+");
	fprintf(fedgesTyp, "Rels\t%d\n",numRel);
	fprintf(fedgesTyp, "Babel\t%d\n",numBabel);
	fprintf(fedgesTyp, "Refs\t%d\n",numRefs);

	//Atributos de arista
	sprintf(nameFile,"%s.edges.att",argv[5]);
	fprintf(stderr,"Creando %s...\n",nameFile);
	FILE * fedgeAtt = fopen(nameFile,"w+");
	//Número de atributos:
	fprintf(fedgeAtt,"1\n");
	//Rels
	fprintf(fedgeAtt,"%d\t\n",0);
	//Babel
	fprintf(fedgeAtt,"%d\t\n",1);
	//Refs
	fprintf(fedgeAtt,"%d\t\n",0);

	fclose(fedgeAtt);
	fclose(fedgesTyp);
	fclose(fedgesLinks);
	fclose(fedgesVal);

	return 0;
}