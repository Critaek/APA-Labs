#include "invArray.h"

struct invArray_s{
    int nInv;
    inv_t *vettInv;
};

invArray_t invArray_init() {
    invArray_t inv = malloc(sizeof(invArray_t));

    inv->vettInv = NULL;
    inv->nInv = 0;

    return inv;
}

void invArray_free(invArray_t invArray) {
    free(invArray->vettInv);
}

void invArray_read(FILE *fp, invArray_t invArray) {
    int n, i;

    fscanf(fp, "%d", &n);

    invArray->nInv = n;
    invArray->vettInv = malloc(n * sizeof(inv_t));

    for (i = 0; i < n; i++)
        inv_read(fp, &invArray->vettInv[i]);
}

void invArray_print(FILE *fp, invArray_t invArray){
    int i;

    for(i=0; i<invArray->nInv; i++)
        invArray_printByIndex(fp, invArray, i);
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, &invArray->vettInv[index]);
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->vettInv[index];
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;

    for(i=0; i<invArray->nInv; i++)
        if(invArray->vettInv[i].nome, name)
            return i;
}