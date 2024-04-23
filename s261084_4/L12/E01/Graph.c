#include "Graph.h"

struct graph{
    int V;
    int E;
    int **madj;
    ST tab;
};

static int **matrixINIT(int v){
    int i, j;

    int **m = malloc(v * sizeof(int*));

    for(i=0; i<v; i++) {
        m[i] = malloc(v * sizeof(int));
        for(j=0; j<v; j++)
            m[i][j] = -1;
    }

    return m;
}

void GRAPHinsertE(Graph G, Edge e){
    int v = e.v, w = e.w, wt = e.wt;

    G->madj[v][w] = wt;
    G->E++;
}

Graph GRAPHinit(int V){
    int i;
    Graph G = malloc(sizeof(*G));

    if(G == NULL)
        return NULL;

    G->V = V;
    G->E = 0;

    G->madj = matrixINIT(V);
    G->tab = STinit(V);

    return G;
}

static Edge EDGEcreate(int id1, int id2, int wt){
    Edge e;

    e.v = id1;
    e.w = id2;
    e.wt = wt;

    return e;
}

Graph GRAPHload(FILE *fin){
    int V, i, id1, id2, wt;
    Graph G;
    char label1[MAXC], label2[MAXC];

    fscanf(fin, "%d", &V);

    G = GRAPHinit(V);

    for(i=0; i<V; i++){
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin, "%s %s %d", label1, label2, &wt) != EOF){
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);

        if(id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, EDGEcreate(id1, id2, wt));
    }

    return G;
}

void GRAPHfree(Graph G){
    int i;

    for(i=0; i<G->V; i++)
        free(G->madj[i]);

    free(G->madj);
    STfree(G->tab);

    free(G);
}

void dfsR(Graph G, int start, int *time, int *pre, int *post, int *isAcyclic) {
    int v;
    pre[start] = (*time)++;

    for (v=0; v<G->V;v++) {
        if (G->madj[start][v] != -1) {
            if (pre[v] == -1)
                dfsR(G, v, time, pre, post, isAcyclic);
            else if (post[v] == -1)
                *isAcyclic = 0;
        }
    }

    post[start] = (*time)++;
}

void GRAPHdfs(Graph g, int *isAcyclic) {
    int *pre, *post, v, time = 0;

    pre = calloc(g->V, sizeof(int));
    post = calloc(g->V, sizeof(int));

    for(v=0;v<g->V;v++)
        pre[v] = post[v] = -1;

    for(v=0;v<g->V;v++)
        if (pre[v] == -1)
            dfsR(g, v, &time, pre, post, isAcyclic);

    free(pre);
    free(post);
}

int GRAPHgetE(Graph G){
    return G->E;
}

int GRAPHgetV(Graph G){
    return G->V;
}

void GRAPHremoveE(Graph G, Edge e) {
    int v = e.v, w = e.w;

    if (G->madj[v][w] != -1)
        G->E--;

    G->madj[v][w] = -1;
}

int GRAPHedgesWt(Graph G, Edge *a, int *subset, int k) {
    int i, totWt=0;

    if (G == NULL)
        return 0;

    for (i=0; i<k; i++)
        totWt +=a[subset[i]].wt;

    return totWt;
}

void EDGEprint(Graph G, Edge e){
    printf( "%s %s %d\n", STsearchByIndex(G->tab, e.v), STsearchByIndex(G->tab, e.w), e.wt);
}

void GRAPHedges(Graph G, Edge *a){
    int v, w, E = 0;

    for(v = 0; v < G->V; v++)
        for(w = 0; w < G->V; w++)
            if(G->madj[v][w] != -1)
                a[E++] = EDGEcreate(v,w,G->madj[v][w]);
}

void GRAPHprint(Graph G){
    int i;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));

    GRAPHedges(G, a);

    printf("%d\n", G->V);

    for(i=0; i<G->V; i++)
        printf("%s\n", STsearchByIndex(G->tab, i));

    for(i=0; i<G->E; i++)
        printf("%s %s %d\n",STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
}

static void TSdfsR(Graph G, int v, int *ts, int *pre, int *time){
    int w;
    pre[v] = 0;

    for(w = 0; w < G->V; w++)
        if(G->madj[w][v] != -1)
            if(pre[w] == -1)
                TSdfsR(G, w, ts, pre, time);

    ts[(*time)++] = v;
}

static void DAGts(Graph G, int *ts){
    int v, time = 0, *pre;

    pre = malloc(G->V * sizeof(int));

    for(v = 0; v < G->V; v++){
        pre[v] = -1;
        ts[v] = -1;
    }

    for(v = 0; v < G->V; v++)
        if(pre[v] == -1)
            TSdfsR(G, v, ts, pre, &time);


    printf("Ordinamento topologico: \n");
    for(v = 0; v < G->V; v++)
        printf("%s ", STsearchByIndex(G->tab, ts[v]));

    printf("\n");

    free(pre);
}

void DAGmaxDist(Graph G){
    int v, w, i, j, k;
    int *dist = malloc(G->V * sizeof(int));
    int *ts = malloc(G->V * sizeof(int));

    DAGts(G, ts);

    for(i=0; i<G->V; i++){
        v = ts[i];

        printf("Start: %s\n", STsearchByIndex(G->tab, i));

        for(j=0; j<G->V; j++)
            dist[j] = -1;

        dist[v] = 0;

        for(j = i; j < G->V; j++){
            w = ts[j];

            if(dist[w] == -1)
                continue;

            for(k = 0; k<G->V; k++){
                if(G->madj[w][k] != -1)
                    if(dist[k] == -1 || dist[w] + G->madj[w][k] > dist[k])
                        dist[k] = dist[w] + G->madj[w][k];
            }
        }

        for(j = 0; j<G->V; j++){
            if(j == i)
                continue;
            else
                printf("\t %s Distanza: %d\n", STsearchByIndex(G->tab, j), dist[j]);
        }
    }

    free(dist);
    free(ts);
}