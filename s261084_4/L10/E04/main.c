#include "Graph.h"

int main(int argc, char **argv) {
    int scelta = 1;
    Graph G;
    char label1[MAXC], label2[MAXC], label3[MAXC];

    if(argc != 2)
        return -1;

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL)
        return -1;

    G = GRAPHload(fp);

    do{
        printf("0 - Uscita\n"
               "1 - Elenco vertici e rispettivi nodi\n"
               "2 - Adiacenza a coppie dati 3 vertici\n"
               "3 - Generazione lista adiacenza da matrice\n");

        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                GRAPHprintEdges(G);
                break;
            case 2 :
                printf("Inserire i nomi di tre vertici: ");
                scanf("%s %s %s", label1, label2, label3);

                printf("Calcolare a partire da:\n"
                       "1 - Matrice adiacenza\n"
                       "2 - Lista adiacenza\n");
                scanf("%d", &scelta);

                if(scelta == 1) {
                    if (GRAPHsubGraphMat(G, label1, label2, label3))
                        printf("I 3 vertici formano un sottografo completo\n");
                    else
                        printf("I 3 vertici non formano un sottografo completo\n");
                }
                else{
                    if(GRAPHsubGraphList(G, label1, label2, label3))
                        printf("I 3 vertici formano un sottografo completo\n");
                    else
                        printf("I 3 vertici non formano un sottografo completo\n");
                }
                break;
            case 3:
                GRAPHadjListFromMat(G);
                printf("Lista generata\n");
                break;
            default:
                break;
        }

        printf("\n");

    }while(scelta);

    fclose(fp);
    GRAPHfree(G);
    return 0;
}