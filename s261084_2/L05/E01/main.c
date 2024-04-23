#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int n_brani;
    char **brano;
}entry;

entry *leggiFile(int *n);
int princ_molt(int pos, entry *val, char **sol, int n, int count, FILE *fp);

int main() {
    entry *mat;
    int n_amici, i;
    int count;
    mat = leggiFile(&n_amici);
    char **sol, nomefile[256];
    FILE *fp;

    sol = malloc(n_amici*sizeof(char*));

    for(i=0; i<n_amici; i++)
        sol[i] = malloc(256*sizeof(char));

    printf("Nome del file su cui salvare le combinazioni: ");
    scanf("%s", nomefile);

    fp = fopen(nomefile,"w");

    princ_molt(0,mat, sol, n_amici, count,fp);

    fclose(fp);
    free(mat); //libero
    free(sol);
    return 0;
}

entry *leggiFile(int *n){ //legge il file e ritorna una matrice allocata dinamicamente con esattamente n_amici elementi
    FILE *fp;
    int n_amici, n_brani, i, j;
    entry *mat;

    fp = fopen("brani.txt", "r");

    if(fp == NULL) {
        printf("File non trovato\n");
        exit(-1);
    }

    fscanf(fp, "%d", &n_amici);

    mat = malloc(n_amici*sizeof(entry));

    *n = n_amici;

    for(i=0; i<n_amici; i++){
        fscanf(fp, "%d", &n_brani);

        mat[i].brano = malloc(n_brani*sizeof(char*)); //ogni campo brano è una matrice, dico quanti puntatori a char (brani) dovra contenere
        mat[i].n_brani = n_brani;

        for(j=0; j<n_brani; j++){
            mat[i].brano[j] = malloc(256*sizeof(char)); //inizializzo ogni brano con 256 char (dimensione massima 255)
            fscanf(fp, "%s", mat[i].brano[j]);
        }
    }

    fclose(fp);
    return mat;
}

int princ_molt(int pos, entry *val, char **sol, int n, int count, FILE *fp){ //funzione ricorsiva che calcola tutte le possibili combinazioni
    int i;                                                                   //per ogni amico prende un brano alla volta

    if(pos >= n){
        for(i=0; i<n; i++)
            fprintf(fp,"%s ", sol[i]);
        fprintf(fp,"\n");
        return count+1;
    }

    for(i=0; i<val[pos].n_brani; i++){
        strcpy(sol[pos], val[pos].brano[i]);
        count = princ_molt(pos+1, val, sol, n, count, fp);
    }

    return count;
}