#ifndef LAB12_ST_H
#define LAB12_ST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);
void STinsert(ST st, char *string, int id);
int STsearch(ST st, char *string);
char *STsearchByIndex(ST st, int i);

#endif
