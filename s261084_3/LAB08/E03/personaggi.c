#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "personaggi.h"

link newNodeHead(pg_t val, link head){
    int i;
    link x = malloc(sizeof *x);
    if(x == NULL)
        return NULL;
    x->val = val;
    x->val.equip.inUso = 0;
    x->val.equip.vettEq = malloc(MAXOBJ * sizeof(inv_t));
    for(i=0; i<MAXOBJ; i++)
        strcpy(x->val.equip.vettEq[i].nome, NULLO);
    x->next = head;
    return x;
}

tabPg_t leggiFilePg(FILE *fp){
    tabPg_t tab;
    tab.headPg = NULL;
    tab.tailPg = NULL;
    tab.nPg = 0;
    pg_t item;
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", item.codice, item.nome, item.classe, &item.stat.hp, &item.stat.mp, &item.stat.atk, &item.stat.def, & item.stat.mag, &item.stat.spr) == 9){
        tab.headPg = newNodeHead(item, tab.headPg);
        tab.nPg++;
        if(tab.tailPg == NULL)
            tab.tailPg = tab.headPg;
    }
    fclose(fp);
    return tab;
}

pg_t delNode(link *hp, char *nome){
    link *xp, t;
    pg_t i;
    strcpy(i.nome, "0");
    for(xp=hp; (*xp) != NULL; xp=&((*xp)->next)){
        if(!strcmp(nome, (*xp)->val.nome)){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

void stampaPg(pg_t pg){
    printf("<%s> <%s> <%s> <%d> <%d> <%d> <%d> <%d> <%d>\n", pg.codice, pg.nome, pg.classe, pg.stat.hp, pg.stat.mp, pg.stat.atk, pg.stat.def, pg.stat.mag, pg.stat.spr);
}

tabPg_t addObj(tabInv_t inventario, tabPg_t tabella, char *nome){
    link x;
    int i, pos;
    bool pgTrovato = false;

    for (x = tabella.headPg; x != NULL; x = x->next)
        if (!strcmp(x->val.nome, nome)) {
            pgTrovato = true;
            break;
        }

    if(pgTrovato && x->val.equip.inUso < 8) {

        for(i=0; i<inventario.nInv; i++) {
            printf("%d - ", i);
            stampaObj(inventario.vettInv[i]);
        }

        printf("\n");
        printf("Inserire numero oggetto che si vuole inserire: ");
        scanf("%d", &pos);

        for (i = 0; i < MAXOBJ; i++)
            if (!strcmp(x->val.equip.vettEq[i].nome, NULLO)) {
                x->val.equip.vettEq[i] = inventario.vettInv[pos];
                x->val.equip.inUso++;
                break;
            }
        stampaPg(x->val);
            printf("\n %s aggiunto\n", inventario.vettInv[pos].nome);
            printf("%d", x->val.equip.inUso);
    }
    else if(!pgTrovato)
        printf("Personaggio non presente\n");
    else
        printf("Inventario pieno\n");

    return tabella;
}

tabPg_t delObj(tabPg_t tabella, char *nome){
    int i, pos;
    link x;
    bool trovato = false;

    for(x=tabella.headPg; x != NULL; x=x->next)
        if(!strcmp(x->val.nome, nome)){
            trovato = true;
            break;
        }

    if(trovato) {
        for (i = 0; i < x->val.equip.inUso; i++){
            printf("%d - ", i);
            stampaObj(x->val.equip.vettEq[i]);
        }

        if(x->val.equip.inUso > 0){
            printf("\nInserire numero oggetto da eliminare: ");
            scanf("%d", &pos);
            printf("\n %s eliminato\n", x->val.equip.vettEq[pos].nome);
            x->val.equip.inUso--;
            x->val.equip.vettEq[pos] = x->val.equip.vettEq[x->val.equip.inUso];
        }
        else
            printf("Il personaggio non ha alcun oggetto\n");
    }
    else
        printf("Personaggio non presente in lista\n");

    return tabella;
}

void stampaCompleta(tabPg_t tabella, char *nome){
    int i;
    pg_t pg;
    link x;
    bool pgTrovato = false;
    for(x=tabella.headPg; x != NULL; x = x->next)
        if(!strcmp(x->val.nome, nome)){
            pg = x->val;
            pgTrovato = true;
        }

    if(pgTrovato) {
        stampaPg(pg);

        if(pg.equip.inUso != 0) {
            printf("\nElenco oggetti nell'inventario: \n");
            for (i = 0; i < pg.equip.inUso; i++) {
                stampaObj(pg.equip.vettEq[i]);
                pg.stat.hp += pg.equip.vettEq[i].stat.hp;
                pg.stat.mp += pg.equip.vettEq[i].stat.mp;
                pg.stat.atk += pg.equip.vettEq[i].stat.atk;
                pg.stat.def += pg.equip.vettEq[i].stat.def;
                pg.stat.mag += pg.equip.vettEq[i].stat.mag;
                pg.stat.spr += pg.equip.vettEq[i].stat.spr;
            }
            setta1(&pg.stat);
            printf("\nStatistiche con oggetti applicati: \n");
            stampaPg(pg);
        }
    }
    else
        printf("Personaggio non trovato\n");
}

void cercaPg(tabPg_t tabella, char *codice){
    link x;
    bool trovato = false;
    for(x=tabella.headPg; x != NULL; x = x->next)
        if(!strcmp(x->val.codice, codice)){
            trovato = true;
            break;
        }
    if(trovato){
        printf("Personaggio trovato\n");
        stampaPg(x->val);
    }
    else
        printf("Personaggio non trovato\n");
}

void setta1(stat_t *equip){
    if(equip->mp < 1)
        equip->mp = 1;
    if(equip->hp < 1)
        equip->hp = 1;
    if(equip->atk < 1)
        equip->atk = 1;
    if(equip->def < 1)
        equip->def = 1;
    if(equip->mag < 1)
        equip->mag = 1;
    if(equip->spr < 1)
        equip->spr = 1;
}