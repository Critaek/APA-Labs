#ifndef LAB11ES1__H
#define LAB11ES1__H

#include "DataOra.h"

typedef struct{
    Data data;
    float val;
    int n;
}Quotazione;

typedef struct BSTq *BST;

void QUOTAZIONEprint(Quotazione q);
float QUOTAZIONEgetValore(Quotazione q);
Data QUOTAZIONEgetData(Quotazione q);
Quotazione QUOTAZIONEsetNull();
Quotazione QUOTAZIONEset(char *data, char *ora, float val, int n);

BST BSTinit();
int BSTempty(BST bst);
void BSTfree(BST bst);
Quotazione BSTsearch(BST bst, Data d);
void BSTinsert(BST bst, Quotazione q);
void BSTminMaxRange(BST bst, Data d1, Data d2, float *min, float *max);
void BSTprint(BST bst);
void BSTbalance(BST bst, int S);
void BSTgetMinMax(BST bst, float *min, float *max);

#endif //LAB11ES1__H
