#include <stdio.h>
#include <stdlib.h>

#define MAX_C 31

int **leggiFile(char *nomeFile, int *nr, int *nc);
void separa(int **mat, int nr, int nc, int **bianchi, int **neri, int *n_bianchi, int *n_neri);

int main() {
    char nome[MAX_C];
    int **mat;
    int *white = NULL, *black = NULL;
    int nc, nr;
    int n_neri, n_bianchi;

    printf("Inserire nome file: ");
    scanf("%s", nome);

    mat = leggiFile(nome, &nr, &nc);

    separa(mat, nr, nc, &white, &black, &n_bianchi, &n_neri);

    for(int i = 0; i<n_bianchi; i++){ //stampo i bianchi
        printf("%d\n", white[i]);
    }
    printf("\n");
    for(int i = 0; i<n_neri; i++){ //stampo i neri
        printf("%d\n", black[i]);
    }

    free(white); //libero
    free(black);
    free(mat);

    return 0;
}

int **leggiFile(char *nomeFile, int *nr, int *nc){ //legge il file e lo ritorna al chiamante (matrice dinamica)
    FILE *fp;
    int i, j;
    int **mat;

    fp = fopen(nomeFile, "r");

    if(fp == NULL)
        exit(-1);

    fscanf(fp,"%d %d", nr, nc);

    mat = (int **) malloc(*nr * sizeof(int*));

    for(i=0; i<*nr; i++) {
        mat[i] = (int *) malloc(*nc * sizeof(int));
        for (j=0; j<*nc; j++){
            fscanf(fp,"%d", &mat[i][j]);
        }
    }

    fclose(fp);
    return mat;
}

void separa(int **mat, int nr, int nc, int **bianchi, int **neri, int *n_bianchi, int *n_neri){
    int i, j, cnt_b = 0, cnt_n = 0, elementi = (nr*nc)/2;

    if(nr*nc % 2 == 0) //calcolo il numero di elementi a seconda delle caratteristiche della matrice
        *n_bianchi = *n_neri = elementi;
    else{
        *n_bianchi = elementi + 1;
        *n_neri = elementi;
    }

    *bianchi = malloc(*n_bianchi * sizeof(int)); //inizializzo i due vettori che dovrò ritornare by reference
    *neri = malloc(*n_neri * sizeof(int));

    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if((j+i) % 2 == 0){ //se la somma degli indici della matrice è pari, l'elemento è bianco
                (*bianchi)[cnt_b] = mat[i][j];
                cnt_b++;
            }
            if((j+i) % 2 != 0){ //se è dispari, è nero
                (*neri)[cnt_n] = mat[i][j];
                cnt_n++;
            }
        }
    }

}