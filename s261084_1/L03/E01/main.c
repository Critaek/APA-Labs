#include <stdio.h>
#include <stdlib.h>

#define MAXRC 50

typedef enum { false, true } bool;

typedef struct{
    int x;
    int y;
    int b;
    int h;
    int A;
}t_parametri;

void leggiMatrice(int mat[][MAXRC], int *nr, int *nc);
void scansiona(int mat[][MAXRC], int *nr, int *nc, t_parametri vett[]);
int H_Max(int n_punti, t_parametri vett[]);
int B_Max(int n_punti, t_parametri vett[]);
bool riconosciRegione(int mat[][MAXRC], int nr, int nc, int r, int c, int *b, int *h);


int main() {
    int nr, nc;
    int Mat[MAXRC][MAXRC];
    int b, h, r, c;

    leggiMatrice(Mat, &nr, &nc);

    for(r=0; r < nr; r++) {
        for (c = 0; c < nc; c++) {
            if (riconosciRegione(Mat, nr, nc, r, c, &b, &h)) {
                printf("Rettangolo con estremo in (%d,%d) con altezza %d, base %d, e area %d\n", r, c, h, b, b*h);
            }
        }
    }


    return 0;
}

void leggiMatrice(int mat[][MAXRC], int *nr, int *nc){
    FILE *fin;
    int i, j;
    char nome[MAXRC];

    printf("Inserire il nome del file: ");
    scanf("%s", nome);

    fin = fopen(nome, "r");

    if(fin == NULL)
        exit(1);

    fscanf(fin, "%d %d", nr, nc);

    for(i=0; i<*nr; i++)
        for(j=0; j<*nc; j++)
            fscanf(fin,"%d", &mat[i][j]);

    fclose(fin);
}

bool riconosciRegione(int mat[][MAXRC], int nr, int nc, int r, int c, int *b, int *h){
    int n_punti = nr*nc;
    int hMax, bMax, base, altezza;
    t_parametri vettore[n_punti];
    scansiona(mat, &nr, &nc, vettore);
    bMax = B_Max(n_punti,vettore);
    hMax = H_Max(n_punti,vettore);
    base = altezza = 0;

    if(mat[r][c] == 1) {

        base = altezza = 1;

        while (mat[r][c + 1] == 1 && c + 1 < nc) {
            base++;
            c++;
        }

        while (mat[r + 1][c] == 1 && r + 1 < nr) {
            altezza++;
            r++;
        }
    }


    if(altezza == hMax || base == bMax) {
        *h = altezza;
        *b = base;
        return true;
    }

    return false;
}

void scansiona(int mat[][MAXRC], int *nr, int *nc, t_parametri vett[]){
    int i, j, k;
    int n_punti = *nc * *nr;
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

            while(mat[i][colonna+1] == 1 && colonna+1 < *nc){
                vett[k].b++;
                colonna++;
            }

            while(mat[riga+1][j] == 1 && riga+1 < *nr) {
                vett[k].h++;
                riga++;
            }

        }

        vett[k].A = vett[k].b * vett[k].h;
        j++;

        if(j == *nc){
            i++;
            j = 0;
        }

    }
}

int H_Max(int n_punti, t_parametri vett[]){
    int max = -1;
    int k;

    for(k=0; k<n_punti; k++)
        if(vett[k].h > max)
            max = vett[k].h;

    return max;
}

int B_Max(int n_punti, t_parametri vett[]){
    int max = -1;
    int k;

    for(k=0; k<n_punti; k++)
        if(vett[k].b > max)
            max = vett[k].b;

    return max;
}