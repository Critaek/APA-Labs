#include <stdio.h>
#include <stdlib.h>

#define MAXRC 50

typedef struct{
    int nr;
    int nc;
}t_numeri;

typedef struct{
    int x;
    int y;
    int b;
    int h;
    int A;
}t_parametri;

t_numeri leggiMatrice(int mat[][MAXRC], char nomefile[]);
void scansiona(int mat[][MAXRC], t_numeri rc, t_parametri vett[]);
void H_Max(int n_punti, t_parametri vett[]);
void B_Max(int n_punti, t_parametri vett[]);
void A_Max(int n_punti, t_parametri vett[]);


int main() {
    t_numeri rc;
    int Mat[MAXRC][MAXRC];
    char nome[MAXRC];
    int n_punti;

    printf("Inserire il nome del file: ");
    scanf("%s", nome);

    rc = leggiMatrice(Mat,nome);

    n_punti = rc.nr * rc.nc;
    t_parametri vettore[n_punti];
    scansiona(Mat, rc, vettore);
    B_Max(n_punti,vettore);
    A_Max(n_punti,vettore);
    H_Max(n_punti,vettore);

    return 0;
}

t_numeri leggiMatrice(int mat[][MAXRC], char nomefile[]){
    t_numeri rigcol;
    FILE *fin;
    int i, j;

    fin = fopen(nomefile, "r");

    if(fin == NULL)
        exit(1);

    fscanf(fin, "%d %d", & rigcol.nr, &rigcol.nc);

    for(i=0; i<rigcol.nr; i++)
        for(j=0; j<rigcol.nc; j++)
            fscanf(fin,"%d", &mat[i][j]);

    fclose(fin);
    return rigcol;
}

void scansiona(int mat[][MAXRC], t_numeri rc, t_parametri vett[]){
    int i, j, k;
    int n_punti = rc.nc * rc.nr;
    int riga, colonna;

    i = j = 0;
    for(k=0; k<n_punti; k++) {

        vett[k].x = i;
        vett[k].y = j;
        vett[k].b = 0;
        vett[k].h = 0;

        if(mat[i][j] == 1) {
            vett[k].b++;
            vett[k].h++;

            riga = i;
            colonna = j;

            while(mat[i][colonna+1] == 1 && colonna+1 < rc.nc){
                vett[k].b++;
                colonna++;
            }

            while(mat[riga+1][j] == 1 && riga+1 < rc.nr) {
                vett[k].h++;
                riga++;
            }

        }

        vett[k].A = vett[k].b * vett[k].h;
        j++;

        if(j == rc.nc){
            i++;
            j = 0;
        }

    }
}

void H_Max(int n_punti, t_parametri vett[]){
    int max = -1;
    int k, pos;

    for(k=0; k<n_punti; k++){
        if(vett[k].h > max) {
            max = vett[k].h;
            pos = k;
        }
    }

    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d \n", vett[pos].x, vett[pos].y,
            vett[pos].b, vett[pos].h, vett[pos].A);

}

void B_Max(int n_punti, t_parametri vett[]){
    int max = -1;
    int k, pos;

    for(k=0; k<n_punti; k++){
        if(vett[k].b > max) {
            max = vett[k].b;
            pos = k;
        }
    }

    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d \n", vett[pos].x, vett[pos].y,
           vett[pos].b, vett[pos].h, vett[pos].A);

}

void A_Max(int n_punti, t_parametri vett[]){
    int max = -1;
    int k, pos;

    for(k=0; k<n_punti; k++){
        if(vett[k].A > max) {
            max = vett[k].A;
            pos = k;
        }
    }

    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d \n", vett[pos].x, vett[pos].y,
           vett[pos].b, vett[pos].h, vett[pos].A);

}