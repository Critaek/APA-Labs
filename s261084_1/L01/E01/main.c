#include <stdio.h>
#include <stdlib.h>

#define X 20

void CercaStampa(int mat[X][X], int nc, int nr);

int main(int argc, char **argv) {
    int Mat[X][X] = {{0}};
    int nr, nc, i, j;
    FILE *fp;

    if(argc != 4){
        printf("Numero argomenti errato");
        return -1;
    }

    nr = atoi(argv[2]);
    nc = atoi(argv[3]);

    fp = fopen(argv[1], "r");
    if(fp == NULL)
        printf("Errore apertura file\n");

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            fscanf(fp,"%d",&Mat[i][j]);
        }
    }

    CercaStampa(Mat, nr, nc);

    fclose(fp);
    return 0;
}

void CercaStampa(int mat[X][X], int nr, int nc){
    int max = -1, tot = -1, i, j, k, pos;
    for(k = 0; k < nc; k++) {
        max = -1;
        for (i = 0; i < nr; i++) {
            tot = 0;
            for (j = 0; j <= k; j++) {
                tot += mat[i][j];
            }
            if(tot > max){
                max = tot;
                pos = i;
            }
        }
        printf("La capolista e' nella posizione %d \n",pos+1);
    }
}