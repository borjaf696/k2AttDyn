#ifndef KTREEMULTI_H
#define KTREEMULTI_H

#include "kTree.h"
#include "kTreeMulti.h"
#include "schema.h"

void compactTreeRangeQueryLinks(LINKS * links, TREP * trep, uint p1, uint p2, uint q1, uint q2);

void compactTreeAdjacencyListLinks(LINKS * links, TREP * trep, int x, int idIni, int idEnd);

#endif