#ifndef LAB10ES4_GRAPH_H
#define LAB10ES4_GRAPH_H

#include "ST.h"

typedef struct graph *Graph;

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

Graph GRAPHload(FILE *fin);
Graph GRAPHinit(int V, ST st);
void GRAPHfree(Graph G);
void GRAPHprintEdges(Graph G);
void GRAPHadjListFromMat(Graph G);
int GRAPHsubGraphMat(Graph G, char *label1, char *label2, char *label3);
int GRAPHsubGraphList(Graph G, char *label1, char *label2, char *label3);

#endif