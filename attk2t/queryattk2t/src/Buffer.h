#ifndef ___BUFFERATT
#define ___BUFFERATT

typedef struct result
{
	int numResults;
	char ** labels;
	int * ids;
	int * ids2;
}RESULT;

RESULT BUFFER;

void initBuffer();
void endBuffer();

void printNumIds();
void printIds();
void printIds2();
void printLabels();

#endif