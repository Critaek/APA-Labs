#include "Graph.h"

struct graph{
    int V, E;
    ST tab;
    int **madj;
    Edge *archi;
};

static int **matrixInit(int V){
    int i;

    int **M = malloc(V * sizeof(int*));

    for(i=0; i<V; i++)
        M[i] = calloc(V, sizeof(int));

    return M;
}

Graph GRAPHinit(int V){
    Graph G = malloc(sizeof(Graph));

    G->madj = matrixInit(V);
    G->tab = STinit(V);
    G->V = V;
    G->E = 0;
    G->archi = malloc((V*V) * sizeof(Edge));

    return G;
}

static void Edgeinsert(Graph G, int i, int id1, int id2){
    G->archi[i].v = id1;
    G->archi[i].w = id2;
}

Graph GRAPHload(FILE *fin){
    int V, i;
    char label1[MAXC], label2[MAXC];
    int id1, id2;

    fscanf(fin, "%d", &V);

    Graph G = GRAPHinit(V);

    for(i=0; i<V; i++){
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    i = 0;

    while(fscanf(fin, "%s %s", label1, label2) != EOF){
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);

        GRAPHinsertE(G, id1, id2);
        Edgeinsert(G, i++, id1, id2);
        STupdateg(G->tab, id1);
        STupdateg(G->tab, id2);
    }

    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2){
    if(G->madj[id1][id2] == 0)
        G->E++;

    G->madj[id1][id2] = 1;
    G->madj[id2][id1] = 1;
}

static void updateVertici(int *vert, int id, Graph G) {
    int i;

    for(i=0; i<G->E; i++){
        if(G->archi[i].v == id){
            vert[G->archi[i].w]--;
            vert[id]--;
        }

        if(G->archi[i].w == id){
            vert[G->archi[i].v]--;
            vert[id]--;
        }
    }
}

void k_core(Graph G, int k){
    int i, j;
    char c[MAXC];

    int *vertici = malloc(G->V * sizeof(int));

    for(i=0; i<G->V; i++)
        vertici[i] = STgetg(G->tab, i);

    for(i=1; i<=k; i++){
        for(j=0; j<G->V; j++)
            if(vertici[j] < k && vertici[j] > 0)
                updateVertici(vertici, j, G);
    }

    for(i=0; i<G->V; i++){
        if(vertici[i] >= k){
            printf("%s \n", STsearchByIndex(G->tab, i));
        }
    }

    free(vertici);
}

void GRAPHfree(Graph G){
    int i;

    for(i=0; i<G->V; i++)
        free(G->madj[i]);

    free(G->madj);
    free(G->archi);

    STfree(G->tab);

    free(G);
}
