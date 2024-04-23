#include <stdio.h>
#include <string.h>

#define MAX 200

typedef struct{
    char orig[MAX];
    char ricod[MAX];
}new;

int leggiDizionario(new dizionario[]);
void Ricodifica(FILE *sor, new dizionario[], int N, FILE *end);

int main() {
    FILE *sor;
    FILE *end;
    new dizionario[30];
    int N;

    sor = fopen("sorgente.txt","r");
    end = fopen("ricodificato.txt","w");

    N = leggiDizionario(dizionario);

    if(sor == NULL || end == NULL || N == 0){
        printf("Errore apertura file\n");
        return -1;
    }

    Ricodifica(sor, dizionario, N, end);

    fclose(sor);
    fclose(end);

    return 0;
}

int leggiDizionario(new dizionario[]){
    int N, i;
    FILE *diz;

    diz = fopen("dizionario.txt","r");
    if(diz == NULL) return 0;

    fscanf(diz,"%d",&N);

    for(i=0;i<N;i++){
        fscanf(diz,"%s %s",dizionario[i].ricod,dizionario[i].orig);
    }

    fclose(diz);

    return N;
}

void Ricodifica(FILE *sor, new dizionario[], int N, FILE *end){
    char parola[MAX], c;
    int i;
    char *aux;

    while(fscanf(sor,"%s%c",parola, &c) != EOF){
        for(i=0; i<N; i++) {
            aux = strstr(parola, dizionario[i].orig);
            if (aux != NULL) {
                strcpy(aux, dizionario[i].ricod);
            }
        }
        if(c == '\n') {
            fprintf(end, "%s \n", parola);
        }
        else{
            fprintf(end, "%s ", parola);
        }
    }
}