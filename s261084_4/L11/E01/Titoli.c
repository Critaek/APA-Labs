#include "Titoli.h"

struct title{
    char cod[MAXC];
    BST bst;
    float min, max;
};

typedef struct node *link;

struct node{
    Titolo t;
    link next;
};

struct list{
    link head;
    int cnt;
};

int TITOLOcmp(char *t1, char *t2){
    return strcmp(t1, t2);
}

void TITOLOprint(Titolo t){
    printf("%s Min: %f  Max: %f\n", t->cod, t->min, t->max);
}

Titolo TITOLOnew(char *cod){
    Titolo t = malloc(sizeof(*t));

    strcpy(t->cod, cod);
    t->min = t->max = -1;
    t->bst = BSTinit();

    return t;
}

static void updateMinMax(Titolo t){
    float min = -1, max = -1;
    BSTgetMinMax(t->bst, &min, &max);
    t->min = min;
    t->max = max;
}

void TITOLOinsertTransazione(Titolo t, Quotazione q){
    BSTinsert(t->bst, q);
    updateMinMax(t);
}

float TITOLOgetMin(Titolo t){
    return t->min;
}

float TITOLOgetMax(Titolo t){
    return t->max;
}

Quotazione TITOLOgetQuotazione(Titolo t, Data d){
    if(t == NULL || t->bst == NULL)
        return QUOTAZIONEsetNull();

    return BSTsearch(t->bst, d);
}

void TITOLOminmaxRange(Titolo t, Data d1, Data d2, float *min, float *max){
    int cmp = DATAcmp(d1, d2);

    if(cmp < 0)
        BSTminMaxRange(t->bst, d1, d2, min, max);

    if(cmp > 0)
        BSTminMaxRange(t->bst, d2, d1, min, max);

    if(cmp == 0)
        *min = *max = QUOTAZIONEgetValore(BSTsearch(t->bst, d1));
}

void TITOLObalance(Titolo t, int S){
    if(t->bst == NULL || BSTempty(t->bst))
        return;

    BSTbalance(t->bst, S);
}


/*.............................................................................................*/


LIST LISTinit(){
    LIST list = malloc(sizeof(*list));
    list->head = NULL;
    list->cnt = 0;
    return list;
}

Titolo LISTsearch(LIST list, char *cod){
    link x;

    if(LISTempty(list))
        return NULL;

    for(x = list->head; x != NULL; x = x->next)
        if(!TITOLOcmp(cod, x->t->cod))
            return x->t;

    return NULL;
}

int LISTempty(LIST list){
    if(list->cnt == 0 || list->head == NULL)
        return 1;

    return 0;
}

static link newNode(Titolo t, link next){
    link x = malloc(sizeof(*x));

    if(x == NULL)
        return NULL;

    x->t = t;
    x->next = next;

    return x;
}

void LISTinsert(LIST list, Titolo t){
    link x, p;

    char cod[MAXC];
    strcpy(cod, t->cod);

    if(list->head == NULL || TITOLOcmp(t->cod, list->head->t->cod) < 0)
        list->head = newNode(t, list->head);
    else {
        for (x = list->head->next, p = list->head; x != NULL && TITOLOcmp(t->cod, list->head->t->cod) > 0; p = x, x = x->next);
        p->next = newNode(t, x);
    }

    list->cnt++;
}