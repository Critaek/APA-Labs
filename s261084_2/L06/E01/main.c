#include <stdio.h>
#include <stdlib.h>

#define MAX_C 31

typedef enum {false, true} bool;

int **leggiFile(int *N, int *E, char *nome);
int vertexCover(int pos, int *val, int *sol, int k, int count, int **mat, int e);
bool verifica(int *val, int *sol, int **mat, int n, int e);

int main() {
    char nomeFile[MAX_C];
    int N, E, i;
    int **mat;
    int *vett;
    int *sol;

    printf("Inserire nome file: ");
    scanf("%s", nomeFile);

    mat = leggiFile(&N, &E, nomeFile);

    vett = malloc(N * sizeof(int));
    sol = malloc(N * sizeof(int));

    for(i=0; i<N; i++)
        vett[i] = i;

    vertexCover(0, vett, sol, N, 0, mat, E);

    free(vett); //libero
    free(sol);

    return 0;
}

int **leggiFile(int *N, int *E, char *nome){ //legge il file e ritorna la matrice contenente nelle righe i vari archi
    FILE *fp;
    int **mat, i;
    int n, e;

    fp = fopen(nome, "r");

    if(fp == NULL)
        exit(-1);

    fscanf(fp,"%d %d", &n, &e);

    mat = malloc(e * sizeof(int*));

    for(i=0; i<e; i++){
        mat[i] = malloc(2 * sizeof(int));
        fscanf(fp, "%d %d", &mat[i][0], &mat[i][1]);
    }

    fclose(fp);
    *N = n;
    *E = e;
    return mat;
}

int vertexCover(int pos, int *val, int *sol, int k, int count, int **mat, int e){
    int j;

    if(pos >= k){ //se ho considerato tutti i nodi
        if(verifica(val, sol, mat, k, e)){ //verifico se la combinazone va bene, se va bene stampo
            printf("{ ");
            for(j=0; j<k; j++)
                if(sol[j] != 0)
                    printf("%d ", val[j]);
            printf("}\n");
        }
        return count+1;
    }

    sol[pos] = 0;
    count = vertexCover(pos+1, val, sol, k, count, mat, e);
    sol[pos] = 1;
    count = vertexCover(pos+1, val, sol, k, count, mat, e);

    return count;
}

bool verifica(int *val, int *sol, int **mat, int n, int e){
    int *aux;
    aux = calloc(e, sizeof(int));
    int i, j, cnt = 0;

    for(i=0; i<n; i++) //per ogni nodo
        if(sol[i] == 1) //se viene considerato nella soluzione
            for(j=0; j<e; j++) //per ogni arco (che coincide con la riga della matrice)
                if(mat[j][0] == val[i] || mat[j][1] == val[i]) //se il nodo è considerato nella matrice (sia nella parte sinistra che destra)
                    aux[j]++; //aumento il valore dell'elemento j del vettore aux (inizializzato a 0), che coincide con la riga della matrice

    for(i=0; i<e; i++)
        if(aux[i] > 0) //se è > 0 vuol dire che l'arco è stato considerato
            cnt++;

    free(aux);

    if(cnt == e) //se ho considerato tutti gli archi la combinazione va bene e ritorno true
        return true;

    return false; //altrimenti ritorno false
}