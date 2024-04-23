#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    false, true
} bool;

typedef struct {
    char coloreOr;
    int valoreOr;
    char coloreVe;
    int valoreVe;
} tile;

typedef struct {
    tile **board;
    int nr, nc;
} scacchiera;

typedef struct{
    tile *nonVuote;
    int nTile;
}tilePiene;

int leggiTiles(tile **vet);
void disp(int pos, tile *val, scacchiera *sol, scacchiera orig, scacchiera *bestsol, int *mark, int n, int k, int *punt);
scacchiera leggiScacchiera(tile *vet);
void setNULL(tile *t);
bool isNULL(tile t);
tile ruotaTile(tile t);
int calcolaPunt(scacchiera tab);
void calcolaRigCol(int *rig, int *col, int pos, int nc);
void copia(scacchiera tab, scacchiera *copy);
void displaySol(scacchiera sol);
scacchiera malloc2D(int nr, int nc);
tilePiene tileFisse(scacchiera orig);
void togliPiene(int *t, tile **tiles, tilePiene piene);
bool isEqual(tile t, tile t1);
void free2D(scacchiera tab);

int main() {
    tile *vett; //vettore delle tessere da aggiungere
    int T; //numero di tessere
    scacchiera tab; //scacchiera del file "board.txt"
    tilePiene piene; //vettore delle celle non vuote

    T = leggiTiles(&vett);
    tab = leggiScacchiera(vett);
    piene = tileFisse(tab); //metto le celle non vuote
    togliPiene(&T, &vett, piene); //le tolgo dal vettore di tile del file "tiles.txt" in caso ce ne siano e aggiorno T

    scacchiera sol = malloc2D(tab.nr, tab.nc);
    copia(tab, &sol); //copio dentro sol la mia scacchiera originale

    int *mark = calloc(T, sizeof(int));
    int punteggio = -1;

    scacchiera bestsol = malloc2D(tab.nr, tab.nc);

    disp(0, vett, &sol, tab, &bestsol, mark, T, tab.nc * tab.nr, &punteggio);

    printf("Il punteggio massimo trovato e': %d\n", punteggio);
    displaySol(bestsol);

    free(piene.nonVuote);
    free(mark);
    free(vett);
    free2D(tab);
    free2D(sol);
    free2D(bestsol);
    return 0;
}

int leggiTiles(tile **v) {
    FILE *fp = fopen("tiles.txt", "r");
    int T, i;

    if (fp == NULL)
        exit(-1);

    fscanf(fp, "%d", &T);
    fgetc(fp);

    *v = malloc(T * sizeof(tile));

    for (i = 0; i < T; i++) {
        fscanf(fp, "%c %d %c %d ", &(*v)[i].coloreOr, &(*v)[i].valoreOr, &(*v)[i].coloreVe, &(*v)[i].valoreVe);
    }

    fclose(fp);
    return T;
}

scacchiera leggiScacchiera(tile *vet) {
    FILE *fp = fopen("board.txt", "r");
    scacchiera v;
    int i, j, pos, rot;

    if (fp == NULL)
        exit(-1);

    fscanf(fp, "%d %d", &v.nr, &v.nc);

    v.board = malloc(v.nr * sizeof(tile *));

    for (i = 0; i < v.nr; i++) {
        v.board[i] = malloc(v.nc * sizeof(tile));
        for (j = 0; j < v.nc; j++) {
            fscanf(fp, "%d/%d", &pos, &rot);
            if (pos != -1 && rot != -1) {
                if (rot == 0)
                    v.board[i][j] = vet[pos];
                if (rot == 1)
                    v.board[i][j] = ruotaTile(vet[pos]);
            } else
                setNULL(&v.board[i][j]);
        }
    }

    return v;
}

void setNULL(tile *t) {
    t->valoreVe = 0;
    t->valoreOr = 0;
    t->coloreVe = '0';
    t->coloreOr = '0';
}

bool isNULL(tile t) {
    if (t.valoreVe == 0 && t.valoreOr == 0 && t.coloreVe == '0' && t.coloreOr == '0')
        return true;

    return false;
}

tile ruotaTile(tile t) {
    int tmpInt;
    char tmpChar;
    tile aux;

    tmpInt = t.valoreOr;
    aux.valoreOr = t.valoreVe;
    aux.valoreVe = tmpInt;

    tmpChar = t.coloreOr;
    aux.coloreOr = t.coloreVe;
    aux.coloreVe = tmpChar;

    return aux;
}

int calcolaPunt(scacchiera tab) {
    int i, j;
    int p = 0;
    int cnt = 1;

    //controllo sui tubi orizzontali
    for (i = 0; i < tab.nr; i++) {
        for (j = 1; j < tab.nc; j++) {
            if (tab.board[i][j].coloreOr == tab.board[i][j - 1].coloreOr)
                cnt++;
        }

        if (cnt == tab.nc)
            for (j = 0; j < tab.nc; j++)
                p += tab.board[i][j].valoreOr;

        cnt = 1;
    }

    //controllo sui tubi verticali
    for (i = 0; i < tab.nc; i++) {
        for (j = 1; j < tab.nr; j++) {
            if (tab.board[j][i].coloreVe == tab.board[j - 1][i].coloreVe)
                cnt++;
        }

        if (cnt == tab.nr)
            for (j = 0; j < tab.nr; j++)
                p += tab.board[i][j].valoreVe;

        cnt = 1;
    }

    return p;
}

void disp(int pos, tile *val, scacchiera *sol, scacchiera orig, scacchiera *bestsol, int *mark, int n, int k, int *punt) { //disposizioni semplici
    int i, puntAttuale, col, rig;
    calcolaRigCol(&rig, &col, pos, orig.nc);

    if (pos >= k) {
        puntAttuale = calcolaPunt(*sol);
        if (puntAttuale > *punt) {
            *punt = puntAttuale;
            copia(*sol, bestsol);
        }
        return;
    }

    if (!isNULL(orig.board[rig][col])) //se ho gia "qualcosa" mando avanti la ricorsione
        disp(pos + 1, val, sol, orig, bestsol, mark, n, k, punt);
    else
        for (i = 0; i < n; i++) {
            if (mark[i] == 0) {
                mark[i] = 1;

                sol->board[rig][col] = val[i]; //la prendo non ruotata
                disp(pos + 1, val, sol, orig, bestsol, mark, n, k, punt);

                sol->board[rig][col] = ruotaTile(val[i]); //la prendo ruotata
                disp(pos + 1, val, sol, orig, bestsol, mark, n, k, punt);

                mark[i] = 0;
            }
        }
}

void calcolaRigCol(int *rig, int *col, int pos, int nc) { //calcola indice di riga e colonna dalla posizione
    int j;

    *col = -1;
    *rig = 0;

    for (j = 0; j <= pos; j++) {
        *col = *col + 1;

        if (*col >= nc) {
            *col = 0;
            *rig = *rig + 1;
        }
    }
}

void copia(scacchiera tab, scacchiera *copy) {
    int i, j;

    copy->nc = tab.nc;
    copy->nr = tab.nr;

    for (i = 0; i < tab.nr; i++)
        for (j = 0; j < tab.nc; j++)
            copy->board[i][j] = tab.board[i][j];
}

void displaySol(scacchiera sol){
    int i, j;

    //tra una riga di "trattini" e l'altra c'è una riga, tra una riga di stampa e l'altra le colonne stampate cosi come sono
    // nel file tiles (colore tubo orizz/ valore orizz/ colore ve/ valore ve);

    printf("-------\n");

    for(i=0; i<sol.nr; i++){
        for(j=0; j<sol.nc; j++)
            printf("%c %d %c %d\n", sol.board[i][j].coloreOr,sol.board[i][j].valoreOr, sol.board[i][j].coloreVe, sol.board[i][j].valoreVe);

        printf("-------\n");
    }
}

scacchiera malloc2D(int nr, int nc){
    int i;
    scacchiera v;

    v.board = malloc(nr * sizeof(tile *));
    for (i = 0; i < nr; i++)
        v.board[i] = malloc(nc * sizeof(tile));

    return v;
}

tilePiene tileFisse(scacchiera orig) { //funzione che trova quali tessere sono non fisse nella scacchiera originale e le mette in un vettore
    tile *v;
    int i, j;
    int cnt = 0;
    tilePiene vett;

    for (i = 0; i < orig.nr; i++)
        for (j = 0; j < orig.nc; j++)
            if (!isNULL(orig.board[i][j]))
                cnt++;

    v = malloc(cnt * sizeof(tile));
    vett.nTile = cnt;

    cnt = 0;
    for (i = 0; i < orig.nr; i++)
        for (j = 0; j < orig.nc; j++)
            if (!isNULL(orig.board[i][j])) {
                v[cnt] = orig.board[i][j];
                cnt++;
            }

    vett.nonVuote = v;

    return vett;
}

void togliPiene(int *t, tile **tiles, tilePiene piene) { //funzione che toglie dalle tessere del file tiles le tessere gia usate nella matrice originale
    int i, k, cnt = 0, nuovadim;
    tile aux;
    tile *vett;
    bool *prendere = malloc(*t * sizeof(bool));
    memset(prendere, true, *t * sizeof(bool)); //inizializzo a true

    for (i = 0; i < *t; i++)
        for (k = 0; k < piene.nTile; k++) {
            aux = piene.nonVuote[k];
            if (isEqual(aux, (*tiles)[i])) {
                cnt++;
                prendere[i] = false;
            }

            aux = ruotaTile(aux);

            if(isEqual(aux, (*tiles)[i])) {
                cnt++;
                prendere[i] = false;
            }
        }

    nuovadim = *t - cnt;

    vett = malloc(nuovadim * sizeof(tile));

    for(i=0, k = 0; i<*t; i++)
        if(prendere[i])
            vett[k++] = (*tiles)[i];

    *t = *t - cnt;
    free(*tiles);
    free(prendere);
    *tiles = vett;
}

bool isEqual(tile t, tile t1) {
    if (t.valoreVe == t1.valoreVe && t.coloreVe == t1.coloreVe && t.valoreOr == t1.valoreOr &&
        t.coloreOr == t1.coloreOr)
        return true;
    return false;
}

void free2D(scacchiera tab) {
    int i;
    for (i = 0; i < tab.nr; i++)
        free(tab.board[i]);
    free(tab.board);
}