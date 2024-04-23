#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
}

void stat_print(FILE *fp, stat_t *statp){
    fprintf(fp, "<%d> <%d> <%d> <%d> <%d> <%d>\n", statp->hp, statp->mp, statp->atk, statp->def, statp->mag, statp->spr);
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, &invp->stat);
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "<%s> <%s> ", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat);
}