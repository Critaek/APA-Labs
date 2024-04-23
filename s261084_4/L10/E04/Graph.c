#include "Graph.h"

typedef struct node *link;

struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int V;
    int E;
    int **madj;
    link *ladj;
    ST tab;
    link z;
};

static int **matrixINIT(int v){
    int i;

    int **m = malloc(v * sizeof(int*));

    for(i=0; i<v; i++)
        m[i] = calloc(v,sizeof(int));

    return m;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);

    if (x == NULL)
        return NULL;

    x->v = v;
    x->wt = wt;
    x->next = next;

    return x;
}

static void GRAPHinsertEMat(Graph G, int id1, int id2, int wt){
    if(G->madj[id1][id2] == 0)
        G->E++;

    G->madj[id1][id2] = wt;
    G->madj[id2][id1] = wt;
}

static void GRAPHinsertEList(Graph G, int id1, int id2){
    int wt = G->madj[id1][id2];

    G->ladj[id1] = NEW(id2, wt, G->ladj[id1]);
}

static int LISTsearch(link l, int id){
    link x;

    for(x = l; x != NULL; x = x->next){
        if(x->v == id)
            return 1;
    }

    return 0;
}

Graph GRAPHinit(int V, ST st){
    int i;
    Graph  G = malloc(sizeof(*G));

    if(G == NULL)
        return NULL;

    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    G->ladj = malloc(G->V * sizeof(link));

    for(i=0; i<G->V; i++){
        G->ladj[i] = G->z;
    }

    G->madj = matrixINIT(V);
    G->tab = STupdate(st, V);

    return G;
}

Graph GRAPHload(FILE *fin){
    int V = 0, i = 0, id1, id2, wt;
    Graph G;
    char label1[MAXC], label2[MAXC];

    while(fscanf(fin, "%*s %*s %*s %*s %*d") != EOF)
        V++;

    ST st = STinit(V*2);

    rewind(fin);

    while(fscanf(fin, "%s %*s %s %*s %*d", label1, label2) != EOF){

        if(STsearch(st, label1) == -1)
            STinsert(st, label1, i++);

        if(STsearch(st, label2) == -1)
            STinsert(st, label2, i++);
    }
    rewind(fin);

    G = GRAPHinit(i, st);

    STsort(G->tab, i);

    while(fscanf(fin, "%s %*s %s %*s %d", label1, label2, &wt) == 3){
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if(id1 >= 0 && id2 >= 0)
            GRAPHinsertEMat(G, id1, id2, wt);
    }

    return G;
}

void GRAPHfree(Graph G){
    int i;
    link t, next;

    for(i=0; i<G->V; i++) {
        free(G->madj[i]);
        for(t = G->ladj[i]; t != G->z; t = next){
            next = t->next;
            free(t);
        }
    }

    free(G->ladj);
    free(G->madj);

    free(G->z);

    STfree(G->tab);
    free(G);
}

void GRAPHprintEdges(Graph G){
    int i, j;

    for (i = 0; i < G->V; i++) {
        printf("%s: \n", STsearchByIndex(G->tab, i));
        for (j = 0; j < G->V; j++) {
            if (G->madj[i][j]) {
                printf("\t-%s\n", STsearchByIndex(G->tab, j));
            }
        }
    }
}

void GRAPHadjListFromMat(Graph G){
    int i, j;

    for(i = 0; i < G->V; i++){
        for(j = 0; j < G->V; j++){
            if (G->madj[i][j]){
                GRAPHinsertEList(G, i, j);
            }
        }
    }
}

int GRAPHsubGraphMat(Graph G, char *label1, char *label2, char *label3){
    int id1, id2, id3;
    int cnt = 0;

    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    id3 = STsearch(G->tab, label3);

    if(id1 == -1)
        printf("%s non presente!\n", label1);

    if(id2 == -1)
        printf("%s non presente!\n", label2);

    if(id3 == -1)
        printf("%s non presente!\n", label3);

    if(id1 != -1 && id2 != -1 && id3 != -1){
        if(G->madj[id1][id2] != 0 && G->madj[id1][id3] != 0)
            cnt++;

        if(G->madj[id2][id1] != 0 && G->madj[id2][id3] != 0)
            cnt++;

        if(G->madj[id3][id1] != 0 && G->madj[id3][id2] != 0)
            cnt++;
    }

    return cnt;
}

int GRAPHsubGraphList(Graph G, char *label1, char *label2, char *label3) {
    int id1, id2, id3;
    int cnt = 0;

    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    id3 = STsearch(G->tab, label3);

    if (id1 == -1)
        printf("%s non presente!\n", label1);

    if (id2 == -1)
        printf("%s non presente!\n", label2);

    if (id3 == -1)
        printf("%s non presente!\n", label3);

    if (id1 != -1 && id2 != -1 && id3 != -1) {
        if(LISTsearch(G->ladj[id1], id2) && LISTsearch(G->ladj[id1], id3))
            cnt++;

        if(LISTsearch(G->ladj[id2], id1) && LISTsearch(G->ladj[id2], id3))
            cnt++;

        if(LISTsearch(G->ladj[id3], id1) && LISTsearch(G->ladj[id3], id2))
            cnt++;
    }

    return cnt;
}