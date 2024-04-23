#ifndef PERSONAGGI_H
#define PERSONAGGI_H

#include "inventario.h"
#define MAXOBJ 8
#define NULLO "0"

typedef struct{
    int inUso;
    inv_t *vettEq;
}tabEquip_t;

typedef struct{
    char codice[MAXC];
    char nome[MAXC];
    char classe[MAXC];
    tabEquip_t equip;
    stat_t stat;
}pg_t;

typedef struct nodoPg_t *link;

struct nodoPg_t{
    pg_t val;
    link next;
};

typedef struct{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

link newNodeHead(pg_t val, link head);
tabPg_t leggiFilePg(FILE *fp);
pg_t delNode(link *hp, char *nome);
void stampaPg(pg_t pg);
void cercaPg(tabPg_t tabella, char *codice);
tabPg_t addObj(tabInv_t inventario, tabPg_t tabella, char *nome);
tabPg_t delObj(tabPg_t tabella, char *nome);
void stampaCompleta(tabPg_t tabella, char *nome);
void setta1(stat_t *equip);

#endif