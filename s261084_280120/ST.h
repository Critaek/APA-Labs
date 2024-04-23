#ifndef ESAME_ST_H
#define ESAME_ST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 11

typedef struct symbol_t *ST;

typedef struct{
    char *nome;
    int g;
}Vertex;

Vertex *Vertexinit(int maxN);
ST STinit(int maxN);
void STupdateg(ST st, int id);
int STgetg(ST st, int id);
int STsearch(ST st, char *label);
char *STsearchByIndex(ST st, int id);
void STinsert(ST st, char *label, int id);
void STfree(ST st);

#endif
