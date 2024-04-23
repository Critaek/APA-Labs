#include "ST.h"

struct symbtab {
    char **A;
    int maxN;
};

ST STinit(int maxN){
    int i;

    ST st = malloc(sizeof(*st));
    st->A = malloc(maxN * sizeof(char *));
    st->maxN = maxN;

    for (i = 0; i < maxN; i++)
        st->A[i] = NULL;

    return st;
}

void STfree(ST st){
    int i;

    for (i = 0; i < st->maxN; i++)
        if(st->A[i] != NULL)
            free(st->A[i]);

    free(st->A);
    free(st);
}

void STinsert(ST st, char *string, int id){

    st->A[id] = strdup(string);
}

int STsearch(ST st, char *string){
    int i = 0;

    for (i = 0; i < st->maxN; i++)
        if(st->A[i] != NULL && !strcmp(string, st->A[i]))
            return i;

    return -1;
}

void STsort(ST st, int V){
    int i, j, l = 0, r = V-1;
    char temp[MAXC];

    for (i = l; i < r; i++)
        for (j = l; j < r - i + l; j++)
            if (strcmp(st->A[j], st->A[j + 1]) > 0) {
                strcpy(temp, st->A[j]);
                strcpy(st->A[j], st->A[j+1]);
                strcpy(st->A[j+1], temp);
            }
}

char *STsearchByIndex(ST st, int i){
    return st->A[i];
}

ST STupdate(ST st, int V){
    int i;
    ST newST = STinit(V);

    for(i=0; i<V; i++)
        newST->A[i] = strdup(st->A[i]);

    STfree(st);
    return newST;
}