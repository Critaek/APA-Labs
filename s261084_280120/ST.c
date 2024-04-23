#include "ST.h"

struct symbol_t{
    Vertex *A;
    int N;
};

ST STinit(int maxN){
    ST st = malloc(sizeof(ST));

    st->A = Vertexinit(maxN);
    st->N = 0;

    return st;
}

Vertex *Vertexinit(int maxN){
    int i;

    Vertex *V = malloc(maxN * sizeof(Vertex));

    for(i=0; i<maxN; i++){
        V[i].nome = malloc(MAXC * sizeof(char));
        V[i].g = 0;
    }

    return V;
}

void STupdateg(ST st, int id){
    st->A[id].g++;
}

int STgetg(ST st, int id){
    return st->A[id].g;
}

int STsearch(ST st, char *label){
    int i;

    for(i=0; i<st->N; i++)
        if(!strcmp(label, st->A[i].nome))
            return i;

    return -1;
}

char *STsearchByIndex(ST st, int id){
    return st->A[id].nome;
}

void STinsert(ST st, char *label, int id){
    st->A[id].nome = strdup(label);
    st->N++;
}

void STfree(ST st){
    int i;

    for(i=0; i<st->N; i++)
        free(st->A[i].nome);

    free(st->A);

    free(st);
}