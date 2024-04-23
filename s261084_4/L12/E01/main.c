#include <stdio.h>

#include "Graph.h"

void generaSetE(Graph G);
void space();

int main() {
    int a = 1;
    Graph G = NULL;
    FILE *fp;

    fp = fopen("grafo3.txt", "r");

    if(fp == NULL)
        exit(-1);

    G = GRAPHload(fp);

    printf("Grafo originale: \n");
    GRAPHprint(G);

    GRAPHdfs(G, &a);

    if(!a){
        printf("Grafo originale ciclico\n\n");
        generaSetE(G);
        space();
        printf("Il DAG risultante e': \n");
        GRAPHprint(G);
    }
    else
        printf("Il grafo originale e' gia un DAG\n");

    space();

    DAGmaxDist(G);

    GRAPHfree(G);
    fclose(fp);
    return 0;
}

void comb_sempl(int pos, int *sol, Graph g, Edge *vE, int n, int k, int start, int *stop, int *bestSol, int *bestWt) {
    int i, a=1, solWt;
    if (pos >= k) {

        for (i=0; i<k; i++)
            GRAPHremoveE(g, vE[sol[i]]);

        solWt = GRAPHedgesWt(g, vE, sol, k);

        GRAPHdfs(g, &a);

        if (a) {
            *stop = 1;
            if (solWt > *bestWt) {
                *bestWt = solWt;
                for(i=0;i<k;i++)
                    bestSol[i] = sol[i];
            }
        }

        for (i=0; i<k; i++)
            GRAPHinsertE(g, vE[sol[i]]);

        return;
    }

    for (i=start; i<n; i++) {
        sol[pos] = i;
        comb_sempl(pos+1, sol, g, vE, n, k, i+1, stop, bestSol, bestWt);
    }
}

void generaSetE(Graph G){
    int i, j, stop = 0, bestWt = 0;
    int E = GRAPHgetE(G);
    int V = GRAPHgetV(G);

    Edge *vE = malloc(E * sizeof(Edge));

    int *sol;
    int *bestsol = calloc(E, sizeof(int));

    int ub = E - (V - 1);

    if( ub <= 0)
        return;

    printf("V = %d, E = %d, numero massimo di archi da rimuovere: %d\n", V, E, ub);

    GRAPHedges(G, vE);

    for(i = 1; i <= ub && !stop; i++){
        sol = malloc(i * sizeof(int));
        printf("Generazione set di cardinalita': %d\n", i);
        comb_sempl(0, sol, G, vE, E, i, 0, &stop, bestsol, &bestWt);
    }

    space();
    printf("Elenco archi rimossi: ");

    for(j = 0; j <i-1; j++)
        EDGEprint(G, vE[bestsol[j]]);

    if(stop)
        for(j=0; j< i-1; j++){
            GRAPHremoveE(G, vE[bestsol[j]]);
        }
}

void space(){
    printf("\n");
}