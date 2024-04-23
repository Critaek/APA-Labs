#include "pgList.h"

typedef struct pgNode_t *link;

struct pgNode_t{
    pg_t val;
    link next;
};

struct pgList_s{
    link head;
    link tail;
    int nPg;
};

pgList_t pgList_init(){
    pgList_t lista;
    lista = malloc(sizeof(pgList_t));
    lista->head = NULL;
    lista->tail = NULL;
    lista->nPg = 0;

    return lista;
}

void pgList_free(pgList_t pgList){
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){
    pg_t pg;

    while(pg_read(fp, &pg) == 3)
        pgList_insert(pgList, pg);
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;

    for(x = pgList->head; x != NULL; x = x->next)
        pg_printSemplice(fp, &x->val);
}

void pgList_insert(pgList_t pgList, pg_t pg) {
    link h = pgList->head;
    link x = malloc(sizeof(*x));

    x->val = pg;
    x->next = h;
    pgList->head = x;

    pgList->nPg++;

    if (pgList->tail == NULL)
        pgList->tail = pgList->head;
}

void pgList_remove(pgList_t pgList, char* cod){
    link *x, t;

    for(x = &pgList->head; (*x) != NULL; x = &((*x)->next))
        if(!strcmp(cod, (*x)->val.cod)){
            t = *x;
            *x = (*x)->next;
            pg_clean(&t->val);
            break;
        }
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link *x, t;

    for(x = &pgList->head; (*x) != NULL; x = &((*x)->next))
        if(!strcmp(cod, (*x)->val.cod)) {
            break;
        }

    return &(*x)->val;
}