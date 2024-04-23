#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct{
    int s, f; //inizio e fine
    int d; //durata
}att;

int leggiFile(att **v);
void bubbleSort(att *v, int N);
void attSel(int N, att *vet);
void printSol(att *vet, int *P, int last);
bool compatibile(att *x, att *y);

int main() {
    att *v;
    int n;

    n = leggiFile(&v);
    bubbleSort(v, n);
    attSel(n, v);

	free(v);
    return 0;
}

int leggiFile(att **v){
    FILE *fp = fopen("att.txt", "r");
    if(fp == NULL)
        exit(-1);
    int n, i;
    fscanf(fp, "%d", &n);
    *v = malloc(n*sizeof(att));
    for(i=0; i<n; i++) {
        fscanf(fp, "%d %d", &(*v)[i].s, &(*v)[i].f);
        (*v)[i].d = (*v)[i].f - (*v)[i].s;
    }
    fclose(fp);
    return n;
}

void bubbleSort(att *v, int N){
    int i, j, l = 0, r = N - 1;
    att tmp;

    for(i=l; i<r; i++)
        for(j=l; j<r-i+l; j++)
            if(v[j].s > v[j+1].s){
                tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
}

void attSel(int N, att *vet) {
    int i, j, ris = 0, L[N], P[N], last = 1;
	
	//dentro L salvo la lunghezza della soluzione al passo i-esimo considerato, dentro P salvo la posizione della att collegata con la att i-esima

    L[0] = 1;
    P[0] = -1;

    for (i = 1; i < N; i++) {
        L[i] = vet[i].d;
        P[i] = -1;
        for (j = 0; j < i; j++)
            if (compatibile(&vet[i], &vet[j]) && L[i] < L[j] + vet[i].d) {
                L[i] = L[j] + vet[i].d;
                P[i] = j;
            }
        if (ris < L[i]) {
            ris = L[i];
            last = i;
        }
    }

    printSol(vet, P, last);
    printf("\nDurata totale = %d\n", ris);
}

bool compatibile(att *i, att *j){
    if(j->f <= i->s)
        return true;

    return false;
}

void printSol(att *vet, int *P, int last) {
    int i;

    //vettore ausiliario in cui salvo quali elementi in vet sono da stampare e quali no, serve solo per stampare in ordine crescente e non decrescente

    bool *daS = malloc((last + 1) * sizeof(bool));
    memset(daS, false, (last + 1) * sizeof(bool)); //inizilizzo tutto a true

    daS[last] = true;

    for (i = last; i >= 1; i = P[i])
        daS[P[i]] = true;

    for (i = 0; i <= last; i++)
        if (daS[i])
            printf("(%d, %d) ", vet[i].s, vet[i].f);

    free(daS);
}