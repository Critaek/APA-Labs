#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXS 20
#define MAXC 6
#define MAXR 200

int leggiSequenza(char mat[][MAXC]);
void trovaOccorrenze(int N, char seq[][MAXC]);
int cerca(char parola[], char stringa[]);
void adatta(char riga[]);

int main() {
    char sequenze[MAXS][MAXC];
    int N;

    N = leggiSequenza(sequenze);
    trovaOccorrenze(N,sequenze);

    return 0;
}

int leggiSequenza(char mat[][MAXC]){
    FILE *fp;
    int i, j, N = 0;
    fp = fopen("sequenze.txt","r");

    if(fp == NULL)
        return 0;

    fscanf(fp, "%d", &N);

    for(i=0; i<N; i++)
        fscanf(fp, "%s", mat[i]);

    for(i=0; i<N; i++)
        for (j = 0; j < strlen(mat[i]); j++)
            mat[i][j] = toupper(mat[i][j]);

    fclose(fp);
    return N;
}

void trovaOccorrenze(int N, char seq[][MAXC]) {
    FILE *text;
    char *parola;
    int trovato;
    int pos, i;
    char riga[MAXR];

    text = fopen("testo.txt", "r");

    if (text == NULL)
        exit(1);

    for (i = 0; i < N; i++) {
        printf("Le parole che contengono %s sono: \n PAROLA/POSIZIONE \n", seq[i]);
        pos = 1;
        do {
            fgets(riga, MAXR, text);
            adatta(riga);
            parola = strtok(riga, " ");

            while(parola != NULL){
                trovato = cerca(parola, seq[i]);

                if (trovato)
                    printf(" %s %d \n", parola, pos);

                pos++;
                parola = strtok(NULL, " ");
            }

        } while (!feof(text));

        printf("\n");
        rewind(text);
    }

    fclose(text);
}

int cerca(char parola[], char stringa[]){
    char *aux;

    aux = strstr(parola, stringa);

    if(aux == NULL)
        return 0;

    return 1;
}

void adatta(char riga[]){
    int i;
    char c;

    for(i=0; i<strlen(riga); i++){
        c = riga[i];
        if(ispunct(c))
            riga[i] = ' ';
        else
            riga[i] = toupper(c);
    }
}