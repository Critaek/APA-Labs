#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 51

typedef struct{
    char codice[MAX_C];
    char nome[MAX_C];
    char cognome[MAX_C];
    char nascita[MAX_C];
    char via[MAX_C];
    char citta[MAX_C];
    int cap;
}Item;

typedef struct node *link;

struct node{
    Item val;
    link next;
};

typedef enum {false, true} bool;

void Menu();
void stampaItem(Item val, FILE *fp);
void stampaLista(link h, FILE *fp);
bool comparaDate(Item val1, Item val2);
link newNode(Item val, link next);
link insOrdinato(link h, Item val);
link leggiFile(link h, FILE *fp);
Item cercaCodice(link h, char *codice);
Item cancellaCodice(link *h, char *codice);
Item cancella2Date(link *h, char *dataMin, char *dataMax);
bool dataCompresa(char *data, char *dataMin, char *dataMax);

int main(){
    Menu();
    return 0;
}

void Menu(){
    int scelta;
    link head;
    head = malloc(sizeof(*head));
    head->next = NULL;
    char stringa[MAX_C];
    char data[MAX_C];
    Item aux;

    do{
        printf("0 - Uscita\n"
               "1 - Inserimento elemento da tastiera\n"
               "2 - Inserimento elementi da file\n"
               "3 - Ricerca per codice\n"
               "4 - Cancellazione elemento per codice\n"
               "5 - Cancellazione elementi compresi tra 2 date\n"
               "6 - Stampa lista su file\n");

        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                printf("Inserire dati da aggiungere: ");
                scanf("%s %s %s %s %s %s %d", aux.codice, aux.nome, aux.cognome, aux.nascita, aux.via, aux.citta, &aux.cap);
                head = insOrdinato(head,aux);
                break;
            case 2:
                printf("Nome del file: ");
                scanf("%s", stringa);
                FILE *in = fopen(stringa, "r");
                if(in == NULL)
                    break;
                head = leggiFile(head,in);
                fclose(in);
                break;
            case 3:
                printf("Inserire codice da ricercare: ");
                scanf("%s", stringa);
                aux = cercaCodice(head,stringa);
                if(!strcmp(aux.codice, stringa)) {
                    stampaItem(aux, stdout);
                    printf("Elemento eliminato!\n");
                }
                else
                    printf("Elemento non trovato!\n");
                break;
            case 4:
                printf("Inserire codice da cancellare: ");
                scanf("%s",stringa);
                aux = cancellaCodice(&head,stringa);
                if(!strcmp(aux.codice, stringa)) {
                    stampaItem(aux, stdout);
                    printf("Elemento eliminato!\n");
                }
                else
                    printf("Elemento non trovato!\n");
                break;
            case 5:
                printf("Inserire due date nel formato GG/MM/AAAA: ");
                scanf("%s %s", stringa, data);
                aux = cancella2Date(&head, stringa, data);
                do {
                    stampaItem(aux, stdout);
                    aux = cancella2Date(&head, stringa, data);
                }while(dataCompresa(aux.nascita,stringa,data));
                break;
            case 6:
                printf("Nome del file: ");
                scanf("%s", stringa);
                FILE *out = fopen(stringa, "w");
                stampaLista(head,out);
                fclose(out);
                break;
        }
        printf("\n");
    }while(scelta != 0);
    free(head);
}

void stampaItem(Item val, FILE *fp){
    fprintf(fp,"<%s> <%s> <%s> <%s> <%s> <%s> <%d>\n", val.codice, val.nome, val.cognome, val.nascita, val.via, val.citta, val.cap);
}

void stampaLista(link h, FILE *fp){
    while(h->next != NULL){
        stampaItem(h->val,fp);
        h = h->next;
    }
}

link newNode(Item val, link next){
    link x = malloc(sizeof *x);
    if(x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

link insOrdinato(link h, Item val){
    link x, p;

    if(h->next == NULL || comparaDate(h->val,val))
        return newNode(val, h);

    for(x=h->next, p=h; x->next!=NULL && comparaDate(val,x->val); p=x, x=x->next);
    p->next = newNode(val, x);

    return h;
}

bool comparaDate(Item val1, Item val2){ //ritorna true se data di val1 viene prima di data di val2
    int AA, MM, GG, aa, mm, gg;
    int data1, data2;
    sscanf(val1.nascita, "%d/%d/%d", &GG, &MM, &AA);
    sscanf(val2.nascita, "%d/%d/%d", &gg, &mm, &aa);
    data1 = (10000*AA) + (100*MM) + GG;
    data2 = (10000*aa) + (100*mm) + gg;

    if(data1 < data2)
        return true;

    return false;
}

link leggiFile(link h, FILE *fp){
    Item aux;
    while(fscanf(fp, "%s %s %s %s %s %s %d", aux.codice, aux.nome, aux.cognome, aux.nascita, aux.via, aux.citta, &aux.cap) == 7){
        h = insOrdinato(h, aux);
    }
    return h;
}

Item cercaCodice(link h, char *codice){
    link x;
    for(x=h; x->next != NULL; x=x->next)
        if(!strcmp(codice, x->val.codice))
            return x->val;
}

Item cancellaCodice(link *h, char *codice){
    link *x, t;
    Item i;
    i.codice[0] = '0';

    for(x=h; (*x) != NULL; x=&((*x)->next))
        if(!strcmp(codice, (*x)->val.codice)) {
            t = *x;
            *x = (*x)->next;
            i = t->val;
            free(t);
            break;
        }

    return i;
}

Item cancella2Date(link *h, char *dataMin, char *dataMax){
    link *x, t;
    Item i;
    int j;
    for(j=0; j<10; j++)
        i.nascita[j] = 0;

    for(x=h; (*x) != NULL; x=&((*x)->next))
        if(dataCompresa((*x)->val.nascita,dataMin, dataMax)){
            t = *x;
            *x = (*x)->next;
            i = t->val;
            free(t);
            break;
        }

    return i;
}

bool dataCompresa(char *data, char *dataMin, char *dataMax){
    int data_min, data_max, data_da_conf, tmp;
    int AA_min, MM_min, GG_min, AA_max, MM_max, GG_max, AA, MM, GG;
    sscanf(dataMin,"%d/%d/%d", &GG_min, &MM_min, &AA_min);
    sscanf(dataMax,"%d/%d/%d", &GG_max, &MM_max, &AA_max);
    sscanf(data, "%d/%d/%d", &GG, &MM, &AA);

    data_min = (AA_min*10000) + (MM_min*100) + GG_min;
    data_max = (AA_max*10000) + (MM_max*100) + GG_max;
    data_da_conf = (AA*10000) + (MM*100) + GG;

    if(data_max < data_min){
        tmp = data_max;
        data_max = data_min;
        data_min = tmp;
    }

    if(data_da_conf > data_min && data_da_conf < data_max)
        return true;

    return false;
}