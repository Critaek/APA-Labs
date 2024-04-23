#include <stdio.h>
#include "Graph.h"

#define MAXCHAR 256

int main() {
    char nome[MAXCHAR];
    int k;

    printf("Inserire nome file: ");
    scanf("%s", nome);

    FILE *fp = fopen(nome, "r");

    if(fp == NULL)
        exit(-1);

    Graph G = GRAPHload(fp);

    printf("Inserire k: ");
    scanf("%d", &k);

    k_core(G, k);

    GRAPHfree(G);
    fclose(fp);

    return 0;
}