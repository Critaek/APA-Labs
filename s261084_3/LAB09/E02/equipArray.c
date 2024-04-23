#include "equipArray.h"

struct equipArray_s{
    int inUso;
    inv_t *equip;
};

equipArray_t equipArray_init(){
    equipArray_t equipArray = malloc(sizeof(equipArray_t));
    int i;

    equipArray->equip = malloc(EQUIP_SLOT * sizeof(inv_t));
    equipArray->inUso = 0;

    for(i=0; i<EQUIP_SLOT; i++)
        strcpy(equipArray->equip[i].nome, "0");

    return equipArray;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray->equip);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray){
    int i;

    for(i=0; i<equipArray->inUso; i++)
        inv_print(fp, &equipArray->equip[i]);
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    char nome[LEN];
    int scelta, index ,i;
    bool found = false;

    printf("1 - Inserisci oggetto\n"
           "2 - Elimina oggetto\n");
    scanf("%d", &scelta);

    if(scelta == 1) { //aggiungo un oggetto nell'equipaggiamento
        printf("Inserire nome oggetto da aggiungere: ");
        scanf("%s", nome);
        index = invArray_searchByName(invArray, nome);

        for(i=0; i<EQUIP_SLOT; i++) {
            if (!strcmp(equipArray->equip[i].nome, "0")) { //se ho uno spazio vuoto
                equipArray->equip[i] = *invArray_getByIndex(invArray, index);
                equipArray->inUso++;
                found = true;
                break;
            }
        }

        if(found)
            printf("%s aggiunto\n", equipArray->equip[i].nome);
    }

    if(scelta == 2){ //rimuovo un oggetto dall'equipaggiamento
        printf("Inserire nome oggetto da rimuovere: ");
        scanf("%s", nome);

        for (i = 0; i < equipArray->inUso; i++) {
            if (!strcmp(equipArray->equip[i].nome, nome)) {
                equipArray->inUso--;
                equipArray->equip[i] = equipArray->equip[equipArray->inUso];
                found = true;
                break;
            }
        }

        if(found)
            printf("%s rimosso\n", equipArray->equip[i].nome);
    }
}

void equipStat_update(equipArray_t  equip, stat_t b, stat_t *eq){
    int i;

    for(i=0; i<equip->inUso; i++){
        eq->hp += b.hp;
        eq->mp += b.mp;
        eq->mag += b.mag;
        eq->atk += b.atk;
        eq->def += b.def;
        eq->spr += b.spr;
    }

    if(eq->hp < 1)
        eq->hp = 1;
    if(eq->mp < 1)
        eq->mp = 1;
    if(eq->mag < 1)
        eq->mag = 1;
    if(eq->atk < 1)
        eq->atk = 1;
    if(eq->def < 1)
        eq->def = 1;
    if(eq->spr < 1)
        eq->spr = 1;
}