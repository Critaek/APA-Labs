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
void ricercaLineare(tabella mat, int n_corse, char *partenza);


int main() {
    Menu();
    return 0;
}

void Menu(void){
    int scelta, n;
    tabella tab;
    char stringa[MAX_C];
    Ordinamento ordine = NONORDINATO;

    tab = leggiCorse(&n);

    printf("0 - Uscita\n"
           "1 - Stampa a video\n"
           "2 - Stampa su file\n"
           "3 - Ordina per data\n"
           "4 - Ordina per codice tratta\n"
           "5 - Ordina per stazione di partenza\n"
           "6 - ordina per stazione di arrivo\n"
           "7 - Ricerca per stazione di partenza\n");

    do{
        printf("Inserire un valore: ");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                stampaVideo(tab, n); //stampo a video
                break;

            case 2:
                printf("Inserire il nome del file su cui stampare: ");
                scanf("%s", &stringa);
                stampaFile(tab, n, stringa); //stampo su file
                break;

            case 3:
                ordinaStabile(&tab, DATA, n);
                printf("Elenco ordinato per data\n");
                ordine = DATA;
                break;

            case 4:
                ordinaStabile(&tab, TRATTA, n);
                printf("Elenco ordinato per tratta\n");
                ordine = TRATTA;
                break;

            case 5:
                ordinaStabile(&tab, PARTENZA, n);
                printf("Elenco ordinato per stazione di partenza\n");
                ordine = PARTENZA;
                break;

            case 6:
                ordinaStabile(&tab, ARRIVO, n);
                printf("Elenco ordinato per stazione di arrivo");
                ordine = ARRIVO;
                break;

            case 7:
                printf("Inserire la stazione di partenza da ricercare: ");
                scanf("%s", stringa);
                if(ordine == PARTENZA)
                    ricercaBinaria(tab, stringa, 0, n-1); //se è ordinato per partenza posso usare la ricerca binaria
                else
                    ricercaLineare(tab, n, stringa);
                break;

            default:
                break;
        }
        printf("\n");
    }while(scelta != 0);

}

tabella leggiCorse(int *n_corse){ //funzione che legge un file e riempie una matrice che poi viene ritornata al chiamante
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

void stampaFile(tabella mat, int n, char *nomeFile){ //stampa una mat di tipo tabella su un file
    int i;
    FILE *fp;
    fp = fopen(nomeFile, "w");

    for(i=0; i<n; i++) {
        fprintf(fp, "%s %s %s %s %s %s %d\n", mat.log[i].codice, mat.log[i].partenza, mat.log[i].destinazione,
                mat.log[i].data_str, mat.log[i].ora_P_str, mat.log[i].ora_D_str, mat.log[i].ritardo);
    }
}

void stampaVideo(tabella mat, int n){ //stampa una mat di tipo tabella a video (stdout)
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
    tmp = mat->log[i];  //salvo in un elemento temporaneo il primo elemento
    j = i - 1;
    while(j>=l && confronta(tmp, mat->log[j], ordine) < 0){ //finche sono dentro il vettore (j>l (left)) e fino a che tmp viene prima di mat->log[j]
        mat->log[j+1] = mat->log[j];
        j--;
    }
    mat->log[j+1] = tmp;
    }
}

int confronta(entry prima, entry seconda, Ordinamento ordine){ //funzione che confronta a seconda dell'ordinamento richiesto, < se "prima" viene prima di "seconda", > per il viceversa
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

void ricercaLineare(tabella mat, int n_corse, char *partenza){ //dato un vettore non ordinato esegue una ricerca lineare O(n)
    int i, trovato = 0;

    for(i=0; i<n_corse; i++){
        if(!strcmp(mat.log[i].partenza, partenza))
            printf("%s %s %s %s %s %s %d\n", mat.log[i].codice, mat.log[i].partenza, mat.log[i].destinazione,
                   mat.log[i].data_str, mat.log[i].ora_P_str, mat.log[i].ora_D_str, mat.log[i].ritardo);
            trovato = 1;
    }
    if(trovato == 0)
        printf("Nontrovato\n");
}

void ricercaBinaria(tabella mat, char *partenza, int l, int r){ //dato un vettore ordinato esegue una ricerca binaria O(logn)
    int centro, x, n_corse = r + 1;
    int trovato = 0;
    int i, j;

    while(l<=r && trovato == 0){
        centro = (l+r)/2; //calcolo centro
        x = strcmp(mat.log[centro].partenza, partenza);
        if(x==0) //se l'elemento si trova al centro lo ho trovato
            trovato = 1;
        if(x<0) //se l'elemento è minore considero il vettore destro
            l = centro + 1;
        if(x>0) //se è maggiore considero quello sinistro
            r = centro - 1;
    }

    if(trovato) {
        i = centro;
        j = centro - 1;

        while (i < n_corse && !strcmp(mat.log[i].partenza, partenza)) { //trovato l'elemento stampo andando a destra fino a che ho elementi ricercati
            printf("%s %s %s %s %s %s %d\n", mat.log[i].codice, mat.log[i].partenza, mat.log[i].destinazione,
                   mat.log[i].data_str, mat.log[i].ora_P_str, mat.log[i].ora_D_str, mat.log[i].ritardo);
            i++;
        }

        while (j > 0 && !strcmp(mat.log[j].partenza, partenza)) { //se non sono a destra sono a sinistra, stampo andando a sinistra fino a che ho elementi validi
            printf("%s %s %s %s %s %s %d\n", mat.log[j].codice, mat.log[j].partenza, mat.log[j].destinazione,
                   mat.log[j].data_str, mat.log[j].ora_P_str, mat.log[j].ora_D_str, mat.log[j].ritardo);
            j--;
        }
    }
    else
        printf("Elemento non trovato\n");
}