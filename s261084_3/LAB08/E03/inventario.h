#ifndef INVENTARIO_H
#define INVENTARIO_H

#define MAXC 50

typedef enum{false, true} bool;

typedef struct{
    int hp, mp, atk, def, mag, spr;
}stat_t;

typedef struct{
    char nome[MAXC];
    char tipo[MAXC];
    stat_t stat;
}inv_t;

typedef struct{
    inv_t *vettInv;
    int nInv;
}tabInv_t;

tabInv_t leggiFileInv(FILE *fp);
void cercaObj(tabInv_t inventario, char *nome);
void stampaObj(inv_t obj);

#endif