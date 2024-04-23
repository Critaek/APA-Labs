#ifndef EQUIPARRAY_H_DEFINED
#define EQUIPARRAY_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EQUIP_SLOT 8

#include "invArray.h"

typedef enum {false, true} bool;

/* ADT di prima classe collezione di oggetti di equipaggiamento */
typedef struct equipArray_s *equipArray_t;

/* creatore e disruttore */
equipArray_t equipArray_init();
void equipArray_free(equipArray_t equipArray);

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray);

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray);
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray);

/* Si possono aggiungere altre funzioni se ritenute necessarie */
void equipStat_update(equipArray_t  equip, stat_t b, stat_t *eq);

#endif
