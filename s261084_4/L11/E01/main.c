#include <stdio.h>
#include "Titoli.h"

void leggiFile(char *nome, LIST list);

int main() {
    LIST list = LISTinit();
    int scelta, S;
    char nome[MAXC], stringa[MAXC];
    Titolo t;
    float min, max;

    leggiFile("F1.txt", list);
    leggiFile("F2.txt", list);
    leggiFile("F3.txt", list);

    do{
        printf("0 - Uscita\n"
               "1 - Leggi file\n"
               "2 - Ricerca titolo\n"
               "3 - Ricerca quotazione in una certa data\n"
               "4 - Ricerca quotazione min e max in intervallo date\n"
               "5 - Ricerca quotazione min e max assoluti\n"
               "6 - Bilanciamento albero\n");

        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                printf("Inserire nome file: ");
                scanf("%s", nome);

                leggiFile(nome, list);

                break;
            case 2:
                printf("Inserire nome titolo: ");
                scanf("%s", nome);

                t = LISTsearch(list, nome);

                if(t != NULL)
                    TITOLOprint(t);
                else
                    printf("Titolo non presente!\n");

                break;
            case 3:
                printf("Inserire nome titolo: ");
                scanf("%s", nome);

                t = LISTsearch(list, nome);

                if(t != NULL){
                    printf("Inserire data nel formata AAAA/MM/GG: ");
                    scanf("%s", nome);
                    QUOTAZIONEprint(TITOLOgetQuotazione(t,DATAload(nome)));
                }
                else
                    printf("Titolo non presente!\n");

                break;
            case 4:
                printf("Inserire nome titolo: ");
                scanf("%s", nome);

                t = LISTsearch(list, nome);

                if(t != NULL){
                    printf("Inserire prima data nel formata AAAA/MM/GG: ");
                    scanf("%s", nome);

                    printf("Inserire seconda data nel formato AAAA/MM/GG: ");
                    scanf("%s", stringa);

                    TITOLOminmaxRange(t, DATAload(nome), DATAload(stringa), &min, &max);

                    printf("Min: %f   Max: %f\n", min, max);
                }
                else
                    printf("Titolo non presente!\n");

                break;
            case 5:
                printf("Inserire nome titolo: ");
                scanf("%s", nome);

                t = LISTsearch(list, nome);

                if(t != NULL)
                    printf("Min: %f Max: %f\n", TITOLOgetMin(t), TITOLOgetMax(t));
                else
                    printf("Titolo non presente!\n");

                break;
            case 6:
                printf("Inserire nome titolo: ");
                scanf("%s", nome);

                t = LISTsearch(list, nome);

                if(t != NULL) {
                    printf("Inserire soglia massima: ");
                    scanf("%d", &S);

                    TITOLObalance(t, S);
                }
                else
                    printf("Titolo non presente!\n");

                break;
        }
    }while(scelta);


    return 0;
}

void leggiFile(char *nome, LIST list){
    int i, j, n_titoli, n_quote, n;
    Quotazione q;
    float val;
    char cod[MAXC], data[MAXC], ora[MAXC];
    Titolo t;

    FILE *fp = fopen(nome, "r");

    if(fp == NULL)
        return;

    fscanf(fp, "%d", &n_titoli);

    for(i=0; i < n_titoli; i++){
        fscanf(fp, "%s %d", cod, &n_quote);

        t = LISTsearch(list, cod);

        if(t == NULL){
            t = TITOLOnew(cod);
            LISTinsert(list, t);
        }

        for(j=0; j<n_quote; j++){
            fscanf(fp, "%s %s %f %d", data, ora, &val, &n);
            TITOLOinsertTransazione(t, QUOTAZIONEset(data, ora, val, n));
        }
    }

    fclose(fp);
}