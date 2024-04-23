#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RIGHE 1000
#define MAX_C 30+1

typedef enum {DATA, TRATTA, PARTENZA, ARRIVO, NONORDINATO} Ordinamento;

typedef struct{
    int Anno;
    int Mese;
    int Giorno;
}dataType;

typedef struct{
    int Ora;
    int Minuto;
}oraType;

typedef struct{
    char codice[MAX_C];
    char partenza[MAX_C];
    char destinazione[MAX_C];
    char data_str[MAX_C];
    char ora_P_str[MAX_C];
    char ora_D_str[MAX_C];
    int ritardo;
    dataType Data;
    oraType ora_P;
    oraType ora_D;
}entry;

typedef struct{
    entry log[MAX_RIGHE];
    Ordinamento ordine;
}tabella;

tabella leggiCorse(int *n_corse);
void Menu(void);
void stampaVideo(tabella mat, int n);
void stampaFile(tabella mat, int n, char *nomeFile);
void ordinaStabile(tabella *mat, Ordinamento ordine, int n);
int confronta(entry prima, entry seconda, Ordinamento ordine);
int comparaDate(dataType d1, dataType d2);
int comparaOre(oraType o1, oraType o2);
void ricercaBinaria(tabella mat, char *partenza, int l, int r);
void riempiMatrici(int n_corse, tabella mat, tabella *mat_ordine, int n_ordinamenti);


int main() {
    Menu();
    return 0;
}

void Menu(void){
    int scelta, n, i, Ordine_scelto;
    tabella tab;
    tabella tab_ordine[ARRIVO + 1]; //vettore di tabelle con un numero di elementi pari al numero massimo di ordinamenti possibili
    char stringa[MAX_C];

    tab = leggiCorse(&n);
    tab.ordine = NONORDINATO;

    riempiMatrici(n, tab, tab_ordine, ARRIVO + 1); //faccio una copia di tutta la tabella usata nelle nuove tabelle che sono in tab_ordine

    for(i=0; i<(ARRIVO + 1); i++) //per ogni tabella di tab_ordine eseguo un ordinamento
        ordinaStabile(&tab_ordine[i], i, n);

    do{
        printf("0 - Uscita\n"
               "1 - Stampa a video\n"
               "2 - Stampa su file\n"
               "3 - Ricerca per stazione di partenza\n");
        printf("Inserire un valore: ");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                printf("Stampa matrice ordinata per: \n"
                       "0 - Data\n"
                       "1 - Tratta\n"
                       "2 - Partenza\n"
                       "3 - Arrivo\n");
                scanf("%d", &Ordine_scelto);
                stampaVideo(tab_ordine[Ordine_scelto], n);
                break;

            case 2:
                printf("Inserire il nome del file su cui stampare: ");
                scanf("%s", &stringa);
                printf("Stampa matrice ordinata per: \n"
                       "0 - Data\n"
                       "1 - Tratta\n"
                       "2 - Partenza\n"
                       "3 - Arrivo\n");
                scanf("%d", &Ordine_scelto);
                stampaFile(tab_ordine[Ordine_scelto], n, stringa);
                break;

            case 3:
                printf("Inserire la stazione di partenza da ricercare: ");
                scanf("%s", stringa);
                ricercaBinaria(tab_ordine[PARTENZA],stringa,0,n-1);
                break;
        }
        printf("\n");
    }while(scelta != 0);

}

tabella leggiCorse(int *n_corse){
    FILE *fp;
    int i;
    tabella mat;

    fp = fopen("corse.txt", "r");
    if(fp == NULL)
        exit(-1);

    fscanf(fp,"%d", n_corse);

    for(i=0; i<*n_corse; i++){
        fscanf(fp,"%s %s %s %s %s %s %d", mat.log[i].codice, mat.log[i].partenza, mat.log[i].destinazione, mat.log[i].data_str,
               mat.log[i].ora_P_str, mat.log[i].ora_D_str, &mat.log[i].ritardo);
        sscanf(mat.log[i].data_str, "%d/%d/%d", &mat.log[i].Data.Anno, &mat.log[i].Data.Mese, &mat.log[i].Data.Giorno);
        sscanf(mat.log[i].ora_P_str, "%d:%d", &mat.log[i].ora_P.Ora, &mat.log[i].ora_P.Minuto);
        sscanf(mat.log[i].ora_D_str, "%d:%d", &mat.log[i].ora_D.Ora, &mat.log[i].ora_D.Minuto);
    }

    fclose(fp);
    return mat;
}

void stampaFile(tabella mat, int n, char *nomeFile){
    int i;
    FILE *fp;
    fp = fopen(nomeFile, "w");

    for(i=0; i<n; i++) {
        fprintf(fp, "%s %s %s %s %s %s %d\n", mat.log[i].codice, mat.log[i].partenza, mat.log[i].destinazione, mat.log[i].data_str, mat.log[i].ora_P_str, mat.log[i].ora_D_str, mat.log[i].ritardo);
    }
}

void stampaVideo(tabella mat, int n){
    int i;

    for(i=0; i<n; i++) {
        printf("%s %s %s %s %s %s %d\n", mat.log[i].codice, mat.log[i].partenza, mat.log[i].destinazione,
               mat.log[i].data_str, mat.log[i].ora_P_str, mat.log[i].ora_D_str, mat.log[i].ritardo);
    }
}

void ordinaStabile(tabella *mat, Ordinamento ordine, int n){
    int i, j;
    int l = 0, r = n-1;
    entry tmp;

    for(i=0;i<=r;i++){
        tmp = mat->log[i];
        j = i - 1;
        while(j>=l && confronta(tmp, mat->log[j], ordine) < 0){
            mat->log[j+1] = mat->log[j];
            j--;
        }
        mat->log[j+1] = tmp;
    }
    mat->ordine = ordine; //sfrutto l'enum ti tipo ordinamento
}

int confronta(entry prima, entry seconda, Ordinamento ordine){
    int cmp;
    switch(ordine) {
        case DATA:
            cmp = comparaDate(prima.Data, seconda.Data);
            if (cmp == 0) return comparaOre(prima.ora_P, seconda.ora_P);
            return cmp;

        case TRATTA:
            return strcmp(prima.codice, seconda.codice);

        case PARTENZA:
            return strcmp(prima.partenza, seconda.partenza);

        case ARRIVO:
            return strcmp(prima.destinazione, seconda.destinazione);
    }

    return 0;
}

int comparaDate(dataType d1, dataType d2){
    if (d1.Anno != d2.Anno)
        return (d1.Anno-d2.Anno);
    else if (d1.Mese != d2.Mese)
        return (d1.Mese-d2.Mese);
    else if (d1.Giorno != d2.Giorno)
        return (d1.Giorno-d2.Giorno);
    else return 0;
}

int comparaOre(oraType o1, oraType o2){
    if(o1.Ora != o2.Ora)
        return(o1.Ora-o2.Ora);
    if(o1.Minuto != o2.Minuto)
        return(o1.Minuto-o2.Minuto);
}

void ricercaBinaria(tabella mat, char *partenza, int l, int r){
    int centro, x, n_corse = r + 1;
    int trovato = 0;
    int i, j;

    while(l<=r && trovato == 0){
        centro = (l+r)/2;
        x = strcmp(mat.log[centro].partenza, partenza);
        if(x==0)
            trovato = 1;
        if(x<0)
            l = centro + 1;
        if(x>0)
            r = centro - 1;
    }

    if(trovato) {
        i = centro;
        j = centro - 1;

        while (i < n_corse && !strcmp(mat.log[i].partenza, partenza)) {
            printf("%s %s %s %s %s %s %d\n", mat.log[i].codice, mat.log[i].partenza, mat.log[i].destinazione,
                   mat.log[i].data_str, mat.log[i].ora_P_str, mat.log[i].ora_D_str, mat.log[i].ritardo);
            i++;
        }

        while (j > 0 && !strcmp(mat.log[j].partenza, partenza)) {
            printf("%s %s %s %s %s %s %d\n", mat.log[j].codice, mat.log[j].partenza, mat.log[j].destinazione,
                   mat.log[j].data_str, mat.log[j].ora_P_str, mat.log[j].ora_D_str, mat.log[j].ritardo);
            j--;
        }
    }
    else
        printf("Elemento non trovato\n");
}

void riempiMatrici(int n_corse, tabella mat, tabella *mat_ordine, int n_ordinamenti){
    int i, j;
    for(i=0; i<n_ordinamenti; i++)
        for(j=0; j<n_corse; j++)
            mat_ordine[i].log[j] = mat.log[j];
}