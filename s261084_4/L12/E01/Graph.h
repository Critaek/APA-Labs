#ifndef LAB12_GRAPH_H
#define LAB12_GRAPH_H

#include "ST.h"

#define MAXC 31

typedef struct graph *Graph;

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

Graph GRAPHinit(int V);
Graph GRAPHload(FILE *fin);
void GRAPHfree(Graph G);
void  GRAPHdfs(Graph G, int *isAcyclic);
int GRAPHgetE(Graph G);
int GRAPHgetV(Graph G);
void GRAPHremoveE(Graph G, Edge e);
int GRAPHedgesWt(Graph G, Edge *a, int *subset, int k);
void GRAPHinsertE(Graph G, Edge e);
void EDGEprint(Graph G, Edge e);
void GRAPHprint(Graph G);
void GRAPHedges(Graph G, Edge *a);
void DAGmaxDist(Graph G);

#endif