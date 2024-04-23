#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 50
#define MAXOBJ 8
#define NULLO "0"

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

typedef enum{false, true} bool;

link newNodeHead(pg_t val, link head);
tabPg_t leggiFilePg(void);
tabInv_t leggiFileInv(void);
void stampaMenu(void);
pg_t delNode(link *hp, char *nome);
void stampaPg(pg_t pg);
tabPg_t addObj(tabInv_t inventario, tabPg_t tabella, char *nome, char *obj);
tabPg_t delObj(tabPg_t tabella, char *nome, char *obj);
void calcolaStat(tabPg_t tabella, char *nome);


int main() {
    tabPg_t tabella;
    tabInv_t inventario;
    pg_t newPg;
    char nome[MAXC];
    char obj[MAXC];
    int scelta;
    do{
        stampaMenu();
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                tabella = leggiFilePg();
                printf("Elenco personaggi caricato\n");
                break;
            case 2:
                inventario = leggiFileInv();
                printf("Elenco oggetti caricato\n");
                break;
            case 3:
                printf("Inserire dati personaggio:\n");
                printf("Inserire codice, nome e classe: ");
                scanf("%s %s %s", newPg.codice, newPg.nome, newPg.classe);
                printf("Inserire statistiche <hp> <mp> <atk> <def> <mag> <spr>: ");
                scanf("%d %d %d %d %d %d", &newPg.stat.hp, &newPg.stat.mp, &newPg.stat.atk, &newPg.stat.def, &newPg.stat.mag, &newPg.stat.spr);
                tabella.headPg = newNodeHead(newPg, tabella.headPg);
                tabella.nPg++;
                break;
            case 4:
                printf("Inserire nome del personaggio da eliminare: ");
                scanf("%s", nome);
                newPg = delNode(&tabella.headPg, nome);
                if(!strcmp(newPg.nome, "0"))
                    printf("Oggetto non trovato\n");
                else {
                    printf("Oggetto eliminato\n");
                    stampaPg(newPg);
                    printf("\n");
                }
                break;
            case 5:
                printf("Inserire nome personaggio: "); //dato un nome di un personaggio e un oggetto, rimuove o aggiunge a seconda della scelta dell'utente
                scanf("%s", nome);
                printf("1 - Aggiungi oggetto\n"
                       "2 - Elimina oggetto\n");
                scanf("%d", &scelta);
                if(scelta == 1){
                    printf("Inserire nome dell'oggetto da aggiungere: ");
                    scanf("%s", obj);
                    tabella = addObj(inventario, tabella, nome, obj);
                }
                else{
                    printf("Inserire nome dell'oggetto da rimuovere: ");
                    scanf("%s", obj);
                    tabella = delObj(tabella, nome, obj);
                }
                break;
            case 6:
                printf("Inserire nome personaggio del quale si vogliono calcolare le statistiche: ");
                scanf("%s", nome);
                calcolaStat(tabella, nome);
                break;
        }
        printf("\n");
    }while(scelta != 0);

    return 0;
}

void stampaMenu(void) {
    printf("0 - Uscita\n"
           "1 - Carica l'elenco di personaggi\n"
           "2 - Carica l'elenco di oggetti\n"
           "3 - Aggiungi personaggio\n"
           "4 - Elimina personaggio\n"
           "5 - Aggiungi/rimuovi un oggetto dall'equipaggiamento di un personaggio\n"
           "6 - Calcola statistiche personaggio\n");
}

tabPg_t leggiFilePg(void){
    tabPg_t tab;
    tab.headPg = NULL;
    tab.tailPg = NULL;
    tab.nPg = 0;
    pg_t item;
    FILE *fp = fopen("pg.txt", "r");
    if(fp == NULL)
        exit(-1);
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", item.codice, item.nome, item.classe, &item.stat.hp, &item.stat.mp, &item.stat.atk, &item.stat.def, & item.stat.mag, &item.stat.spr) == 9){
        tab.headPg = newNodeHead(item, tab.headPg);
        tab.nPg++;
        if(tab.tailPg == NULL)
            tab.tailPg = tab.headPg;
    }
    fclose(fp);
    return tab;
}

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

tabInv_t leggiFileInv(void){
    tabInv_t inv;
    int nInv, i;
    FILE *fp = fopen("inventario.txt","r");
    if(fp ==NULL)
        exit(-1);
    fscanf(fp, "%d", &nInv);
    inv.nInv = nInv;
    inv.vettInv = malloc(nInv*sizeof(inv_t));
    for(i=0; i<nInv; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", inv.vettInv[i].nome, inv.vettInv[i].tipo, &inv.vettInv[i].stat.hp, &inv.vettInv[i].stat.mp, &inv.vettInv[i].stat.atk, &inv.vettInv[i].stat.def, &inv.vettInv[i].stat.mag, &inv.vettInv[i].stat.spr);
    }
    fclose(fp);
    return inv;
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

tabPg_t addObj(tabInv_t inventario, tabPg_t tabella, char *nome, char *obj){
    link x;
    int i, pos;
    bool objTrovato = false, pgTrovato = false;
    for(i=0; i<inventario.nInv; i++)
        if(!strcmp(inventario.vettInv[i].nome, obj)){
            objTrovato = true;
            pos = i;
            break;
        }

    if(objTrovato) {
        for (x = tabella.headPg; x != NULL; x = x->next)
            if (!strcmp(x->val.nome, nome)) {
                pgTrovato = true;
                break;
            }

        if(pgTrovato) {
            for (i = 0; i < MAXOBJ; i++)
                if (!strcmp(x->val.equip.vettEq[i].nome, NULLO)) {
                    x->val.equip.vettEq[i] = inventario.vettInv[pos];
                    x->val.equip.inUso++;
                    break;
                }
            stampaPg(x->val);
        }
        else
            printf("Personaggio non presente\n");
    }
    else
        printf("Oggetto non presente nell'inventario\n");

    return tabella;
}

tabPg_t delObj(tabPg_t tabella, char *nome, char *obj){
    int i;
    link x;
    for(x=tabella.headPg; x->next != NULL; x=x->next)
        if(!strcmp(x->val.nome, nome)){
            for(i=0; i<x->val.equip.inUso; i++)
                if(!strcmp(x->val.equip.vettEq[i].nome, obj)) {
                    strcpy(x->val.equip.vettEq[i].nome, NULLO);
                    x->val.equip.inUso--;
                }
            break;
        }
    return tabella;
}

void calcolaStat(tabPg_t tabella, char *nome){
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
        for (i = 0; i < pg.equip.inUso; i++) {
            pg.stat.hp += pg.equip.vettEq[i].stat.hp;
            pg.stat.mp += pg.equip.vettEq[i].stat.mp;
            pg.stat.atk += pg.equip.vettEq[i].stat.atk;
            pg.stat.def += pg.equip.vettEq[i].stat.def;
            pg.stat.mag += pg.equip.vettEq[i].stat.mag;
            pg.stat.spr += pg.equip.vettEq[i].stat.spr;
        }
        printf("Statistiche con oggetti applicati\n");
        stampaPg(pg);
    }
    else
    printf("Personaggio non trovato\n");
}