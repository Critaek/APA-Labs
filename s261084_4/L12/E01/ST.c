#include "ST.h"

struct symboltable {
    char **A;
    int maxN;
};

ST STinit(int maxN) {
    int i;

    ST st = malloc(sizeof(*st));
    st->A = malloc(maxN * sizeof(char *));
    st->maxN = maxN;

    for (i = 0; i < maxN; i++)
        st->A[i] = NULL;

    return st;
}

void STfree(ST st) {
    int i;

    for (i = 0; i < st->maxN; i++)
        if (st->A[i] != NULL)
            free(st->A[i]);

    free(st->A);
    free(st);
}

void STinsert(ST st, char *string, int id) {

    st->A[id] = strdup(string);
}

int STsearch(ST st, char *string){
    int i = 0;

    for (i = 0; i < st->maxN; i++)
        if(st->A[i] != NULL && !strcmp(string, st->A[i]))
            return i;

    return -1;
}

char *STsearchByIndex(ST st, int i){
    return st->A[i];
}