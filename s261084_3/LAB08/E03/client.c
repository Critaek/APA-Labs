#include <stdio.h>
#include <string.h>
#include "personaggi.h"

void stampaMenu(void);

int main() {
    tabPg_t tabella;
    tabInv_t inventario;
    pg_t newPg;
    char nome[MAXC];
    char obj[MAXC];
    int scelta;
    FILE *fp;

    do{
        printf("Inserire nome file personaggi: ");
        scanf("%s", nome);
        fp = fopen(nome, "r");
        if(fp != NULL) {
            tabella = leggiFilePg(fp);
            printf("Elenco personaggi caricato\n");
        }
        else
            printf("File non esistente!\n");
    }while(fp == NULL);

    fclose(fp);

    do{
        printf("Inserire nome file inventario: ");
        scanf("%s", nome);
        fp = fopen(nome, "r");
        if(fp != NULL) {
            inventario = leggiFileInv(fp);
            printf("Elenco oggetti caricato\n");
        }
        else
            printf("File non esistente!\n");
    }while(fp == NULL);

    do{
        stampaMenu();
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                printf("Inserire dati personaggio:\n");
                printf("Inserire codice, nome e classe: ");
                scanf("%s %s %s", newPg.codice, newPg.nome, newPg.classe);
                printf("Inserire statistiche <hp> <mp> <atk> <def> <mag> <spr>: ");
                scanf("%d %d %d %d %d %d", &newPg.stat.hp, &newPg.stat.mp, &newPg.stat.atk, &newPg.stat.def, &newPg.stat.mag, &newPg.stat.spr);
                tabella.headPg = newNodeHead(newPg, tabella.headPg);
                tabella.nPg++;
                break;
            case 2:
                printf("Inserire nome del personaggio da eliminare: ");
                scanf("%s", nome);
                newPg = delNode(&tabella.headPg, nome);
                if(!strcmp(newPg.nome, "0"))
                    printf("Personaggio non trovato\n");
                else {
                    printf("Personaggio eliminato\n");
                    stampaPg(newPg);
                    printf("\n");
                }
                break;
            case 3:
                printf("Inserire codice personaggio da cercare: ");
                scanf("%s", nome);
                cercaPg(tabella, nome);
                break;
            case 4:
                printf("Inserire nome del personaggio da cercare: ");
                scanf("%s", nome);
                stampaCompleta(tabella, nome);
                break;
            case 5:
                printf("Inserire nome personaggio: "); //dato un nome di un personaggio e un oggetto, rimuove o aggiunge a seconda della scelta dell'utente
                scanf("%s", nome);
                printf("1 - Aggiungi oggetto\n"
                       "2 - Elimina oggetto\n");
                scanf("%d", &scelta);
                if(scelta == 1){
                    tabella = addObj(inventario, tabella, nome);
                }
                else{
                    tabella = delObj(tabella, nome);
                }
                break;
            case 6:
                printf("Inserire nome oggetto da cercare: ");
                scanf("%s", nome);
                cercaObj(inventario, nome);
                break;
        }
        printf("\n");
    }while(scelta != 0);

    return 0;
}

void stampaMenu(void) {
    printf("0 - Uscita\n"
           "1 - Aggiungi personaggio\n"
           "2 - Elimina personaggio\n"
           "3 - Ricerca personaggio per codice\n"
           "4 - Stampa personaggio\n"
           "5 - Aggiungi/rimuovi un oggetto dall'equipaggiamento di un personaggio\n"
           "6 - Ricerca di un oggetto per nome\n");
}