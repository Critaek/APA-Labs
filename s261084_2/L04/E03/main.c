#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {false, true} bool;

char *cercaRegexp(char *src, char *regexp);
char *cercaRegexpR(char *src, char *regexp, int l, bool *trovato);

int main() {
    char *px;
    char stringa[100];
    char regexp[100] = {0};
    printf("Inserire la stringa e l'espressione regolare nell'ordine in cui sono state nominate: ");
    scanf("%s %s", stringa, regexp);

    px = cercaRegexp(stringa,regexp);

    if(px != NULL) //se ho qualcosa
        printf("%s\n", px); //stampo
    else
        printf("Non trovato\n"); //altrimenti avviso l'utente che non ho trovato niente

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    char *px;
    int i;
    bool trovato = false;

    for(i=0; i<strlen(src); i++){ //per ogni carattere della stringa
        px = cercaRegexpR(&src[i], regexp, strlen(regexp), &trovato);
        if(px != NULL)
            return px;
    }

    return px;
}

char *cercaRegexpR(char *src, char *regexp, int l, bool *trovato){ //dato un punto della stringa src ritorna NULL se non soddisfa la regexp, un puntatore se lo soddisfa
    char *x = regexp;
    int cnt = 1, p;
    int i, contatore, n_char, n;
    char *stringa;
    char *caratteri;

    if(l == 0)
        return NULL;

    while(regexp[cnt]!='.' && regexp[cnt]!='/' && regexp[cnt]!='[' && regexp[cnt]!='\0'){
        cnt++;
    }
    cnt--; //cnt mi dice quanti caratteri ci sono tra un "carattere buono" e l'altro tipo tra punto e punto .ciao.albero la prima volta mi da 4 (lunghezza di ciao)

    switch(*x){
        case '.':
            stringa = calloc(cnt, sizeof(char));

            for(i=0; i<cnt; i++) //dentro stringa salvo i caratteri dopo il punto fino all'altro carattere della regexp (es. [cg]iao, dentro stringa avro iao)
                stringa[i] = regexp[i+1];

            for(i = 0, contatore = 0; i<cnt; i++){ //se dal secondo carattere della src trovo un match con la stringa, aumento un contatore
                if(src[i+1] == stringa[i])
                    contatore++;
            }

            if(contatore == cnt){ //se il contatore è uguale al numero di caratteri dopo il punto, ho trovato cio che cercavo (es. stringa = "iao" trovo la parola ciao)
                *trovato = true;
            }
            else
                *trovato = false;

            free(stringa);
            p=cnt + 1; //p conta i cratteri che ho gia considerato della mia src
            break;

        case '[':
            if(regexp[1] != '^') { //se ho il caso senza apice
                n_char = 1;

                while (regexp[n_char] != ']')
                    n_char++;

                n_char--; //numero di caratteri da considerare

                caratteri = calloc(n_char, sizeof(char)); //alloco vettore dove mettero' i caratteri da considerare

                for (i = 0; i < n_char; i++)
                    caratteri[i] = regexp[i + 1]; //riempio il vettore

                n = cnt - n_char - 1; //calcolo il numero di caratteri dopo le parentesi come cnt (caratteri tra una regexp e l'altra) - n_char (numero caratteri tra le parentesi)
                                                                // - 1 (la mia parentesi chiusa)
                stringa = malloc(n * sizeof(char));

                for (i = 0; i < n; i++)
                    stringa[i] = regexp[n_char + 2 + i]; //riempio mettendo i caratteri dopo la parentesi chiusa fino alla prossima regexp

                for (i = 0, contatore = 0; i < n; i++) { //conto quanti caratteri coincidono
                    if (src[i + 1] == stringa[i])
                        contatore++;
                }

                if(contatore == n){ //se coincidono tutti ([cg]iao e ciao, se contatore è = a 3 va bene, dove 3 è il numero di caratteri dopo ])
                    for(i=0; i<n_char; i++) //per ogni carattere da considerare
                        if(src[0] == caratteri[i]) { //se lo trovo
                            *trovato = true;
                            break;
                        }
                        else
                            *trovato = false;
                }

                free(caratteri); //libero
                free(stringa);
                p = n + 1; //numero di caratteri considerati nella src
            }
            else{
                n_char = 1;

                while (regexp[n_char] != ']')
                    n_char++;

                n_char -= 2; //n di caratteri da considerare (-2 perchè l'apice e la parentesi chiusa non sono da considerare)

                caratteri = calloc(n_char, sizeof(char));

                for (i = 0; i < n_char; i++)
                    caratteri[i] = regexp[i + 2]; // +2 perche la prima parentesi e l'apice non mi servono

                n = cnt - n_char - 2; //calcolo caratteri dopo ]

                stringa = malloc(n * sizeof(char));

                for (i = 0; i < n; i++)
                    stringa[i] = regexp[n_char + 3 + i]; //riempio stringa con i caratteri dopo la ] fino alla prossima regexp

                for (i = 0, contatore = 0; i < n; i++) { //conto quanti di essi coincidono
                    if (src[i + 1] == stringa[i])
                        contatore++;
                }
                if(contatore == n){ //se coincidono tutti
                    *trovato = true; //inizializzo a true
                    for(i=0; i<n_char; i++)
                        if(src[0] == caratteri[i]) { //se il primo carattere è uguale a uno di quelli da NON considerare
                            *trovato = false;
                        }
                }

                free(stringa);
                free(caratteri);
                p = n + 1; //caratteri considerati della src
            }
            break;

        case '/':
            if(isupper(regexp[1])){ //se sono nel caso /A
                n = cnt - 1; //numero di caratteri dopo A
                stringa = calloc(n ,sizeof(char));

                for(i=0; i<n; i++)
                    stringa[i] = regexp[i+2]; //riempio stringa (+2 perchè non considero /A)

                for(i=0, contatore = 0; i<n; i++) { //conto quanti coincidono
                    if (src[i + 1] == stringa[i])
                        contatore++;
                }

                if(contatore == n){ //se coincidono tutti
                    if(isupper(src[0])) //se il primo carattere della src è maiuscolo
                        *trovato = true;
                    else
                        *trovato = false;
                }

                p = n + 1; //caratteri considerati della src
                free(stringa);
            }
            else{
                n = cnt - 1;
                stringa = calloc(n ,sizeof(char));

                for(i=0; i<n; i++)
                    stringa[i] = regexp[i+2];

                for(i=0, contatore = 0; i<n; i++) {
                    if (src[i + 1] == stringa[i])
                        contatore++;
                }
                if(contatore == n){
                    if(islower(src[0])) //stessa cosa ma con carattere minuscolo
                        *trovato = true;
                    else
                        *trovato = false;
                }
                p = n + 1;
                free(stringa);
            }
            break;

    }

    if(*trovato)
        cercaRegexpR(&src[p], &regexp[cnt+1], l - cnt - 1, trovato); //se ho trovato richiamo la funzione dandogli come inizio della src il punto in cui sono arrivato, come regexp il punto
                                                                                //fino a dove è stata considerata, come l il numero di caratteri della nuova regexp e il puntatore a trovato
    if(*trovato) //se tutte le chiamate ricorsive hanno dato esito positivo (trovato = true)
        return src; //ritorno il puntatore alla prima src che è il punto in cui ho la prima occorrenza della regexp

    return NULL; //altrimenti torno NULL
}