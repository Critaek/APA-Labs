#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 30
#define maxC 20

typedef struct{
    int r;
    int c;
}rc;

void ruota(int v[maxN], int N, int P, int dir);
void ruotaMatrice(int mat[][maxN], int target, int righe, int colonne, int P, char direzione[maxC], char scelta[maxC]);
rc leggiMatrice(char nome[20], int mat[][maxN]);
void stampaMatrice(int mat[][maxN], int r, int c);

int main() {
    char nomefile[maxC];
    int Mat[maxN][maxN];
    int r,c, indice, p;
    char selettore[maxC], dir[maxC];

    printf("Inserire nome del file: ");
    scanf("%s",nomefile);

    rc matrice = leggiMatrice(nomefile,Mat);

    r = matrice.r;
    c = matrice.c;

    do{
        stampaMatrice(Mat,r,c);
        printf("Inserire i comandi: ");
        scanf("%s %d %s %d", selettore, &indice, dir, &p);
        ruotaMatrice(Mat,indice,r,c,p,dir,selettore);
    }while(strcmp(selettore,"fine") != 0);



    return 0;
}

rc leggiMatrice(char nome[20], int mat[][maxN]){
    FILE *fp;
    int i, j;
    rc rigcol;

    fp = fopen(nome,"r");
    if(fp == NULL) exit(-1);

    fscanf(fp,"%d %d", &rigcol.r, &rigcol.c);

    for(i=0;i<rigcol.r;i++){
        for(j=0;j<rigcol.c;j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
    fclose(fp);
    return rigcol;
}

void ruotaMatrice(int mat[][maxN], int target, int righe, int colonne, int P, char direzione[maxC], char scelta[maxC]){
    int i, vet[maxN], dir;

    if((strcmp(direzione, "destra") == 0) || (strcmp(direzione, "giu") == 0))
        dir = -1;
    else if((strcmp(direzione, "sinistra") == 0) || (strcmp(direzione, "su") == 0))
        dir = 1;

    if(strcmp(scelta,"riga") == 0){
        ruota(mat[target-1], colonne, P, dir);
    }
    else if(strcmp(scelta,"colonna") == 0) {
        for (i = 0; i < colonne; i++) {
            vet[i] = mat[i][target - 1];
        }
        ruota(vet, righe, P, dir);
        for (i = 0; i < colonne; i++) {
            mat[i][target - 1] = vet[i];
        }
    }

    }

void ruota(int v[maxN], int N, int P, int dir){
    int i,j,tmp;
    for (j=0; j<P; j++) {
        if (dir == -1) {
            tmp = v[N-1];
            for (i=N-1; i>0; i--)
                v[i] = v[i-1];
            v[0] = tmp;
        } else {
            tmp = v[0];
            for (i=0; i<N-1; i++)
                v[i] = v[i+1];
            v[N-1] = tmp;
        }
    }
}

void stampaMatrice(int mat[][maxN], int r, int c){
    int i,j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}