#ifndef ESAME_GRAPH_H
#define ESAME_GRAPH_H

#include "ST.h"

typedef struct{
    int v;
    int w;
}Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
Graph GRAPHload(FILE *fin);
void GRAPHinsertE(Graph G, int id1, int id2);
void k_core(Graph G, int k);
void GRAPHfree(Graph G);

#endif