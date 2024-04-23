#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventario.h"

tabInv_t leggiFileInv(FILE *fp){
    tabInv_t inv;
    int nInv, i;
    fscanf(fp, "%d", &nInv);
    inv.nInv = nInv;
    inv.vettInv = malloc(nInv*sizeof(inv_t));
    for(i=0; i<nInv; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", inv.vettInv[i].nome, inv.vettInv[i].tipo, &inv.vettInv[i].stat.hp, &inv.vettInv[i].stat.mp, &inv.vettInv[i].stat.atk, &inv.vettInv[i].stat.def, &inv.vettInv[i].stat.mag, &inv.vettInv[i].stat.spr);
    }
    fclose(fp);
    return inv;
}

void cercaObj(tabInv_t inventario, char *nome){
    bool found = false;
    int i, pos;

    for(i=0; i<inventario.nInv; i++)
        if(!strcmp(inventario.vettInv[i].nome, nome)){
            found = true;
            pos = i;
            break;
        }

    if(found)
        stampaObj(inventario.vettInv[pos]);
    else
        printf("Oggetto non presente\n");
}

void stampaObj(inv_t obj){
    printf("<%s> <%s> <%d> <%d> <%d> <%d> <%d> <%d>\n",obj.nome, obj.tipo, obj.stat.hp, obj.stat.mp, obj.stat.atk, obj.stat.def,
           obj.stat.mag, obj.stat.spr);
}