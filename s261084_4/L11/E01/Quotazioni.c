#include "Quotazioni.h"

typedef struct node* link;

struct node{
    Quotazione q;
    link l, r;
    int cnt;
};

struct BSTq{
    link root;
    int count;
    link z;
};

static link NEW(Quotazione q, link l, link r){
    link x = malloc(sizeof *x);

    x->q = q;
    x->q.val = q.val * q.n;
    x->l = l;
    x->r = r;
    x->cnt = 1;

    return x;
}

static float media(Quotazione q){
    if(q.n != 0)
        return q.val / (float) q.n;
    return -1;
}

void QUOTAZIONEprint(Quotazione q){
    DATAprint(q.data);
    printf("%f\n", media(q));
}

float QUOTAZIONEgetValore(Quotazione q){
    return media(q);
}

Data QUOTAZIONEgetData(Quotazione q){
    if(q.n == 0)
        return DATAsetNull();

    return q.data;
}

Quotazione QUOTAZIONEsetNull(){
    Quotazione q;
    q.data = DATAsetNull();
    q.val = 0;
    q.n = 0;

    return q;
}

Quotazione QUOTAZIONEset(char *data, char *ora, float val, int n){
    Quotazione q;
    q.data = DATAload(data);
    q.val = val;
    q.n = n;

    return q;
}


/*.............................................................................................*/


BST BSTinit(){
    BST bst = calloc(1,sizeof(*bst));

    bst->root = bst->z = NEW(QUOTAZIONEsetNull(), NULL, NULL);
    bst->count = 0;

    return bst;
}

int BSTempty(BST bst){
    if(bst == NULL || bst->root == 0)
        return 1;

     return 0;
}

static Quotazione searchR(link h, Data d, link z){
    int cmp;

    if(h == z)
        return QUOTAZIONEsetNull();

    cmp = DATAcmp(d, QUOTAZIONEgetData(h->q));

    if(cmp == 0)
        return h->q;

    if(cmp < 0)
        return searchR(h->l, d, z);

    return searchR(h->r, d, z);
}

Quotazione BSTsearch(BST bst, Data d){
    return searchR(bst->root, d, bst->z);
}

static link insertR(link h, Quotazione q, link z, int *add){
    int cmp;

    if(h == z) {
        *add = 1;
        return NEW(q, z, z);
    }

    cmp = DATAcmp(q.data, h->q.data);

    if(cmp < 0)
        h->l = insertR(h->l, q, z, add);
    else if(cmp > 0)
        h->r = insertR(h->r,q,z, add);
    else{
        h->q.val += (float) q.n * q.val;
        h->q.n += q.n;
    }

    if(*add) h->cnt++;

    return h;
}

void BSTinsert(BST bst, Quotazione q){
    int add = 0;

    bst->root = insertR(bst->root, q, bst->z, &add);
    if(add) bst->count++;
}

static void treeFree(link h, link z){
    if(h == z)
        return;

    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

void BSTfree(BST bst){
    if(bst == NULL)
        return;

    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}

void BSTgetMinMaxR(link h, float *min, float *max, link z){
    float q = QUOTAZIONEgetValore(h->q);

    if(h == z)
        return;

    if(*min < 0 || q < *min)
        *min = q;

    if(*max < 0 || q > *max)
        *max = q;

    if(h->r != z)
        BSTgetMinMaxR(h->r, min, max, z);

    if(h->l != z)
        BSTgetMinMaxR(h->l, min, max, z);
}

void BSTgetMinMax(BST bst, float *min, float *max){ //funzione che trova minimo e massimo tra le varie giornate
    if(BSTempty(bst))
        return;

    BSTgetMinMaxR(bst->root, min, max, bst->z);
}

static void treePrintR(link h, link z){ //Stampa BST in-order
    if(h == z)
        return;

    treePrintR(h->l, z);
    QUOTAZIONEprint(h->q);
    treePrintR(h->r, z);
}

void BSTprint(BST bst){
    if(BSTempty(bst))
        return;

    treePrintR(bst->root, bst->z);
}

static void treeMinMaxRangeR(link root, Data d1, Data d2, float *min, float *max, link z){
    int cmp1 = DATAcmp(d1, QUOTAZIONEgetData(root->q));
    int cmp2 = DATAcmp(d2, QUOTAZIONEgetData(root->q));
    float valore;

    if(root == z)
        return;

    if(cmp1 < 0)
        treeMinMaxRangeR(root->l, d1, d2, min, max, z);

    if(cmp2 > 0)
        treeMinMaxRangeR(root->r, d1, d2, min, max, z);

    if(cmp1 <= 0 && cmp2 >= 0) {
        valore = QUOTAZIONEgetValore(root->q);

        if (*min < 0 || valore < *min)
            *min = valore;

        if (*max < 0 || valore > *max)
            *max = valore;
    }
}

void BSTminMaxRange(BST bst, Data d1, Data d2, float *min, float *max){
    if(bst == NULL || bst->root == NULL || bst->count == 0)
        return;
    treeMinMaxRangeR(bst->root, d1, d2, min, max, bst->z);

}

static int min(int a, int b){
    if(a < b)
        return a;
    else
        return b;
}

static int minDepht(link root, link z){
    int min_l, min_r;

    if(root == z)
        return 0;

    if(root->l == z && root->r == z)
        return 1;

    min_l = minDepht(root->l, z);
    min_r = minDepht(root->r, z);

    return min(min_l, min_r) + 1;
}

static int max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

static int maxDepht(link root, link z){
    int SX, DX;

    if(root == z)
        return 0;

    SX = maxDepht(root->l, z);
    DX = maxDepht(root->r, z);

    return max(SX, DX) + 1;
}

static link rotR(link h){
    link x = h->l;

    h->l = x->r;
    x->r = h;
    x->cnt = h->cnt;
    h->cnt = 1;
    h->cnt += (h->l) ? h->l->cnt : 0;
    h->cnt += (h->r) ? h->r->cnt : 0;

    return x;
}

static link rotL(link h) {
    link x = h->r;

    h->r = x->l;
    x->l = h;
    x->cnt = h->cnt;
    h->cnt = 1;
    h->cnt += (h->l) ? h->l->cnt : 0;
    h->cnt += (h->r) ? h->r->cnt : 0;

    return x;
}

static link partR(link root, int r, link z){
    int t = (root->l != z) ? root->l->cnt : 0;

    if(t>r){
        root->l = partR(root->l, r, z);
        root = rotR(root);
    }

    if(t < r){
        root->r = partR(root->r, r-t-1, z);
        root = rotL(root);
    }

    return root;
}

static link balanceR(link root, link z){
    int r;

    if(root == z)
        return z;

    r = (root->cnt + 1)/2 - 1;
    root = partR(root, r, z);

    return root;
}

void BSTbalance(BST bst, int S){
    int min, max;

    min = minDepht(bst->root, bst->z);
    max = maxDepht(bst->root, bst->z);

    if(min == 0)
        printf("Albero rimasto inalterato, solo radice presente\n");

    if((float) max / (float) min <= (float) S)
        printf("Albero gia bilanciato\n");

    if((float) max / (float) min > (float) S){
        printf("Altezza minima e massima prima del bilanciamento: %d %d\n", min, max);

        bst ->root = balanceR(bst->root, bst->z);

        min = minDepht(bst->root, bst->z);
        max = maxDepht(bst->root, bst->z);

        printf("Altezza minima e massima dopo il bilanciamento: %d %d\n", min, max);
    }
}