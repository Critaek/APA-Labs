#ifndef TITOLI_H_DEFINED
#define TITOLI_H_DEFINED

#define MAXC 256

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "Quotazioni.h"

typedef struct title *Titolo;

typedef struct list *LIST;

void TITOLOprint(Titolo t);
int TITOLOcmp(char *t1, char *t2);
Titolo TITOLOnew(char *cod);
void TITOLOinsertTransazione(Titolo t, Quotazione q);
float TITOLOgetMin(Titolo t);
float TITOLOgetMax(Titolo t);
void TITOLOminmaxRange(Titolo t, Data d1, Data d2, float *min, float *max);
Quotazione TITOLOgetQuotazione(Titolo t, Data d);
void TITOLObalance(Titolo t, int S);

LIST LISTinit();
Titolo LISTsearch(LIST list, char *cod);
int LISTempty(LIST list);
void LISTinsert(LIST list, Titolo t);

#endif
