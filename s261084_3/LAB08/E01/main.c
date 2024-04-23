#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int s, f; //inizio e fine
    int d;
}att;

int leggiFile(att **v, char *nomefile);
void attSel(int n, att *v);
void powerset(int pos, att *val, int *sol, int *dTot, int *max, int *bestsol, int n);
int compatibile(att *val, int *sol, int pos);
int distanza(att *val, int *sol, int n);

int main() {
    int n;
    char nomefile[50];
    att *v;

    printf("Inserire nome file: ");
    scanf("%s", nomefile);

    n = leggiFile(&v, nomefile);
    attSel(n, v);

    free(v);
    return 0;
}

void attSel(int n, att *v){
    int *sol = calloc(n, sizeof(int));
    int *bestsol = malloc(n*sizeof(int));
    int durata = 0, max = -1;
    powerset(0, v, sol, &durata, &max, bestsol, n);
    int i;

    for(i=0; i<n; i++) {
        if (bestsol[i] != 0)
            printf("(%d,%d) ", v[i].s, v[i].f);
    }
    printf("\nDurata totale = %d", max);

    free(sol);
    free(bestsol);
    return;
}

int leggiFile(att **v, char *nomefile){
    FILE *fp = fopen(nomefile, "r");
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

void powerset(int pos, att *val, int *sol, int *dTot, int *max, int *bestsol, int n){
    int i;

    if(pos >= n){
        *dTot = distanza(val, sol, n);
        if(*dTot > *max) {
            *max = *dTot;
            for (i = 0; i < n; i++)
                bestsol[i] = sol[i];
        }
        return;
    }

    sol[pos] = 0;
    powerset(pos+1, val, sol, dTot, max, bestsol, n);
    if(compatibile(val, sol, pos)){
        sol[pos] = 1;
        powerset(pos+1, val, sol, dTot, max , bestsol, n);
    }

    return;
}

int compatibile(att *val, int *sol, int pos){
    int i;

    for (i=0; i<pos; i++) {
        if (sol[i] != 0) {
            if (val[i].s < val[pos].f && val[pos].s < val[i].f)
                return 0;
        }
    }
    return 1;
}

int distanza(att *val, int *sol, int n){
    int d = 0, i;
    for(i=0; i<n; i++)
        if(sol[i] != 0)
            d += val[i].d;

    return d;
}