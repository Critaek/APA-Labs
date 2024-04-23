#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int n_scambi;
    int n_tot_i;
    int n_CI_CE;
    int n_CicEst;
}iterazioni;

iterazioni insertionSort(int V[], int l, int r);
iterazioni selectionSort(int V[], int l, int r);
iterazioni shellSort(int V[], int l, int r);
void leggiFile(void);
void copia(int *a, int *b, int n);

int main() {

    leggiFile();

    return 0;
}

iterazioni insertionSort(int *V, int l, int r) {
    int i, j, x;
    iterazioni insS;
    insS.n_tot_i = insS.n_CI_CE = insS.n_CicEst = insS.n_scambi = 0;

    for (i = l + 1; i <= r; i++) {
        x = V[i];
        j = i - 1;
        while (j >= l && x < V[j]) {
            V[j + 1] = V[j];
            j--;
            insS.n_scambi++;
        }
        V[j + 1] = x;
    }
    insS.n_tot_i = i*insS.n_scambi;
    insS.n_CI_CE = insS.n_scambi/i;
    insS.n_CicEst = i;

    return insS;
}

iterazioni selectionSort(int V[], int l, int r) {
    int i, j, min, tmp;
    iterazioni selS;
    selS.n_tot_i = selS.n_CI_CE = selS.n_CicEst = selS.n_scambi = 0;

    for (i = l; i < r; i++) {
        min = i;
        for (j = i + 1; j <= r; j++) {
            if (V[j] < V[min])
                min = j;
        }
        tmp = V[j];
        V[i] = V[min];
        V[min] = tmp;
        selS.n_scambi++;
    }

    selS.n_CicEst = i;
    selS.n_tot_i = i*selS.n_scambi;
    selS.n_CI_CE = selS.n_scambi/i;

    return selS;
}

iterazioni shellSort(int V[], int l, int r) {
    int i, j, tmp, h, n;
    iterazioni sheS;
    sheS.n_tot_i = sheS.n_CI_CE = sheS.n_CicEst = sheS.n_scambi = 0;

    h = 1;
    n = r - l + 1;

    while (h < (n / 3))
        h = 3 * h + 1;

    while (h >= 1) {
        for (i = h + l; i <= r; i++) {
            j = i;
            tmp = V[i];
            while ((j >= l + h) && (tmp < V[j - h])) {
                V[j] = V[j - h];
                j -= h;
            }
            V[j] = tmp;
            sheS.n_scambi++;
        }
        h = h / 3;
        sheS.n_CicEst++;
    }

    sheS.n_tot_i = sheS.n_CicEst * sheS.n_scambi;
    sheS.n_CI_CE = sheS.n_scambi/sheS.n_CicEst;

    return sheS;
}

void leggiFile(void){
    FILE *fp;
    int S, i, j, n;
    iterazioni shell, insert, selec;

    fp = fopen("sort.txt", "r");

    if(fp == NULL) exit(0);

    fscanf(fp, "%d", &S);

    for(i=0; i<S; i++){
        fscanf(fp, "%d", &n);
        int vett[n];
        int vett1[n], vett2[n];

        for(j=0; j<n; j++){
            fscanf(fp, "%d", &vett[j]);
        }

        copia(vett, vett1, n);
        copia(vett, vett2, n);

        shell = shellSort(vett,0, n-1);
        insert = insertionSort(vett1,0, n-1);
        selec = selectionSort(vett2,0, n-1);

        printf("ALGORITMO/N DI SCAMBI/N ITERAZIONI CICLO ESTERNO/N ITERAZIONI CICLO INT. PER CICLO EST./ N TOT ITERAZIONI \n");
        printf("shellSort %d/%d/%d/%d\n", shell.n_scambi, shell.n_CicEst, shell.n_CI_CE, shell.n_tot_i);
        printf("insertionSort %d/%d/%d/%d\n", insert.n_scambi, insert.n_CicEst, insert.n_CI_CE, insert.n_tot_i);
        printf("selectionSort %d/%d/%d/%d\n", selec.n_scambi, selec.n_CicEst, selec.n_CI_CE, selec.n_tot_i);
    }
}

void copia(int *a, int *b, int n){
    int i;
    for(i=0; i<n; i++)
        b[i] = a[i];
}