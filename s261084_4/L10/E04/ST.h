#ifndef LAB10ES4_ST_H
#define LAB10ES4_ST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 31

typedef struct symbtab *ST;

ST STinit(int maxN);
void STfree(ST st);
void STinsert(ST st, char *string, int id);
int STsearch(ST st, char *string);
char *STsearchByIndex(ST st, int i);
void STsort(ST st, int V);
ST STupdate(ST st, int V);

#endif
