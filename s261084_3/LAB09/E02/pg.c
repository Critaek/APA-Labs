#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    int cnt = 0;
    cnt = fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe);
    stat_read(fp, &pgp->b_stat);
    pgp->equip = equipArray_init();

    return cnt;
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp, "Stampa con statistiche base: \n");
    fprintf(fp, "<%s> <%s> <%s> ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &pgp->b_stat);
    printf("\n");
    if(equipArray_inUse(pgp->equip)){
        pgp->eq_stat = pgp->b_stat;
        equipStat_update(pgp->equip, pgp->b_stat, &pgp->eq_stat);
        fprintf(fp, "Oggetti nell'inventario: \n");
        equipArray_print(fp, pgp->equip);
        printf("\n");

        fprintf(fp, "Stampa con statistiche modificate: \n");
        fprintf(fp, "<%s> <%s> <%s> ", pgp->cod, pgp->nome, pgp->classe);
        stat_print(fp, &pgp->eq_stat);
    }
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
}

void pg_printSemplice(FILE *fp, pg_t *pgp){
    fprintf(fp, "<%s> <%s> <%s> ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &pgp->b_stat);
}

char *getName(pg_t *pg){
    return pg->nome;
}