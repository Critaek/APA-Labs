#include <stdio.h>
#include <stdlib.h>

enum {zaffiro, smeraldo, rubino, topazio};

int fZ(int z, int s, int r, int t, int *****M);
int fS(int z, int s, int r, int t, int *****M);
int fR(int z, int s, int r, int t, int *****M);
int fT(int z, int s, int r, int t, int *****M);
int ****iniziaMat(int z, int s, int r, int t);
void stampaSoluzioni(int z, int s, int r, int t);

int main() {
    int z, s, r, t, i, nRighe;
    char nomeFile[256];

    printf("Inserire nome file: ");
    scanf("%s", nomeFile);

    FILE *fp = fopen(nomeFile, "r");

    if(fp == NULL)
        return -1;

    fscanf(fp,"%d", &nRighe);

    for(i=0; i<nRighe; i++){
        printf("TEST #%d\n", i+1);
        fscanf(fp, "%d %d %d %d", &z, &r, &t, &s);
        stampaSoluzioni(z,s,r,t);
        printf("\n");
    }

    fclose(fp);

    return 0;
}

int fZ(int z, int s, int r, int t, int *****M) {
    int max1 = M[zaffiro][z][s][r][t];
    int max2 = max1;

    if (z == 0)
        return 0;

    if (max1 != -1)
        return max1;

    z--;

    max1 = fZ(z, s, r, t, M) + 1;

    max2 = fR(z, s, r, t, M) + 1;

    if (max1 >= max2) {
        M[zaffiro][z+1][s][r][t] = max1;
        return max1;
    } else {
        M[zaffiro][z+1][s][r][t] = max2;
        return max2;
    }

}

int fS(int z, int s, int r, int t, int *****M){
    int max1 = M[smeraldo][z][s][r][t];
    int max2 = max1;

    if(s == 0)
        return 0;

    if(max1 != -1)
        return max1;

    s--;

    max1 = fS(z,s,r,t,M) + 1;

    max2 = fT(z,s,r,t,M) + 1;

    if (max1 >= max2) {
        M[smeraldo][z][s+1][r][t] = max1;
        return max1;
    } else {
        M[smeraldo][z][s+1][r][t] = max2;
        return max2;
    }
}

int fR(int z, int s, int r, int t, int *****M) {
    int max1 = M[rubino][z][s][r][t];
    int max2 = max1;

    if (r == 0)
        return 0;

    if (max1 != -1)
        return max1;

    r--;

    max1 = fS(z, s, r, t, M) + 1;

    max2 = fT(z, s, r, t, M) + 1;


    if (max1 >= max2) {
        M[rubino][z][s][r+1][t] = max1;
        return max1;
    } else {
        M[rubino][z][s][r+1][t] = max2;
        return max2;
    }

}

int fT(int z, int s, int r, int t, int *****M){
    int max1 = M[topazio][z][s][r][t];
    int max2 = max1;

    if(t == 0)
        return 0;

    if(max1 != -1)
        return max1;

    t--;

    max1 = fZ(z,s,r,t,M) + 1;

    max2 = fR(z,s,r,t,M) + 1;

    if (max1 >= max2) {
        M[topazio][z][s][r][t+1] = max1;
        return max1;
    } else {
        M[topazio][z][s][r][t+1] = max2;
        return max2;
    }

}

int ****iniziaMat(int z, int s, int r, int t){
    int i, j, k, u;

    int ****M = calloc(z+1, sizeof(int***));

    for (i = 0; i < z + 1; i++) {
        M[i] = calloc(s+1, sizeof(int **));

        for (j = 0; j < s+1; j++) {
            M[i][j] = calloc(r+1, sizeof(int *));

            for (k = 0; k < r+1; k++) {
                M[i][j][k] = calloc(t+1, sizeof(int));

                for (u = 0; u < t+1; u++) {
                    M[i][j][k][u] = -1;
                }
            }
        }
    }

    return M;
}

void stampaSoluzioni(int z, int s, int r, int t){
    int i;
    int *****M;
    int max = -1, tmp;

    M = malloc(4 * sizeof(int****));

    for(i=0; i<4; i++) {
        M[i] = iniziaMat(z, s, r, t);
    }

    printf("Zaffiri: %d, Smeraldi: %d, Rubini: %d, Topazi: %d  TOT: %d\n",z,s,r,t,z+s+r+t);

    M[zaffiro][z][s][r][t] = fZ(z,s,r,t,M);
    M[smeraldo][z][s][r][t] = fS(z,s,r,t,M);
    M[rubino][z][s][r][t] = fR(z,s,r,t,M);
    M[topazio][z][s][r][t] = fT(z,s,r,t,M);

    for(i=0; i<4; i++){
        tmp = M[i][z][s][r][t];

        if(tmp > max)
            max = tmp;
    }

    printf("Collana massima di lunghezza: %d\n", max);

    free(M);
}