#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXL 211
#define MAXC 30
#define MAXR 1000

typedef struct{
    char codice_tratta[MAXC];
    char partenza[MAXC];
    char destinazione[MAXC];
    char data[MAXC];
    char ora_partenza[MAXC];
    char ora_arrivo[MAXC];
    int ritardo;
}t_info;

typedef enum{
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
}comando_e;

void selezionaDati(int N, t_info v[]);
comando_e leggiComando(void);
int leggiFile(t_info V[]);
void date(t_info v[], char riga[], int N);
int comparaDate(char daConfrontare[], char Min[], char Max[]);
void partenze(t_info v[], char riga[], int N);
void capolinea(t_info v[], char riga[], int N);
void ritardo(t_info v[], char riga[], int N);
void ritardo_tot(t_info v[], char riga[], int N);

int main() {
    t_info vett[MAXR];
    int nr;

    nr = leggiFile(vett);
    if(nr == 0) {
        printf("Errore apertura file\n");
        return -1;
    }

    selezionaDati(nr, vett);

    return 0;
}

comando_e leggiComando(void){
    comando_e c;
    char cmd[MAXL];
    char *tabella[r_err] = {
            "date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"
    };
    printf("comando  (date/partenza/capolinea/ritardo/ritardo_tot/fine): ");
    scanf("%s",cmd);
    c = r_date;
    while(c<r_err && strcmp(cmd, tabella[c]) != 0)
        c++;

    return c;
}

void selezionaDati(int N, t_info v[]){
    comando_e codice;
    char riga[MAXL];
    int continua = 1;
    while(continua){
        codice = leggiComando();
        gets(riga);

        switch(codice){
            case r_date:
                date(v,riga,N);
                break;
            case r_partenza:
                partenze(v,riga,N);
                break;
            case r_capolinea:
                capolinea(v,riga,N);
                break;
            case r_ritardo:
                ritardo(v,riga,N);
                break;
            case r_ritardo_tot:
                ritardo_tot(v,riga,N);
                break;
            case r_fine:
                continua = 0;
                break;
            case r_err:
            default: printf("comando errato \n");
        }
    }
}

int leggiFile(t_info V[]){
    int N, i;
    FILE *fp;

    fp = fopen("corse.txt", "r");
    if(fp == NULL)
        return 0;

    fscanf(fp, "%d", &N);

    for(i=0; i<N; i++){
        fscanf(fp,"%s %s %s %s %s %s %d", V[i].codice_tratta, V[i].partenza, V[i].destinazione,
                V[i].data, V[i].ora_partenza, V[i].ora_arrivo, &V[i].ritardo);
    }

    fclose(fp);
    return N;
}

void date(t_info v[], char riga[], int N){
    char dataMin[MAXC], dataMax[MAXC];
    int i;

    sscanf(riga, "%s %s", dataMin, dataMax);

    for(i=0; i<N; i++){
        if(comparaDate(v[i].data, dataMin, dataMax))
            printf("%s %s %s %s %s %s %d \n", v[i].codice_tratta, v[i].partenza, v[i].destinazione,
                    v[i].data, v[i].ora_partenza, v[i].ora_arrivo, v[i].ritardo);
    }


}

int comparaDate(char daConfrontare[], char Min[], char Max[]){
    int GG, MM, AA, GG_Min, MM_Min, AA_Min, GG_Max, MM_Max, AA_Max;
    int daCon, min, max, tmp;

    sscanf(daConfrontare,"%d/%d/%d", &GG, &MM, &AA);
    sscanf(Min, "%d/%d/%d", &GG_Min, &MM_Min, &AA_Min);
    sscanf(Max, "%d/%d/%d", &GG_Max, &MM_Max, &AA_Max);

    daCon = (AA*10000) + (MM*100) + GG;
    min = (AA_Min*10000) + (MM_Min*100) + GG_Min;
    max = (AA_Max*10000) + (MM_Max*100) + GG_Max;

    if(max<min){
        tmp = min;
        min = max;
        max = tmp;
    }

    if(daCon >= min && daCon <= max)
        return 1;

    return 0;
}

void partenze(t_info v[], char riga[], int N){
    char partenza[MAXC];
    int i;

    sscanf(riga,"%s", partenza);

    for(i=0; i<N; i++){
        if(!strcmp(v[i].partenza, partenza)) {
            printf("%s %s %s %s %s %s %d \n", v[i].codice_tratta, v[i].partenza, v[i].destinazione,
                   v[i].data, v[i].ora_partenza, v[i].ora_arrivo, v[i].ritardo);
        }
    }
}

void capolinea(t_info v[], char riga[], int N){
    char capolinea[MAXC];
    int i;

    sscanf(riga,"%s", capolinea);

    for(i=0; i<N; i++){
        if(!strcmp(capolinea, v[i].destinazione))
            printf("%s %s %s %s %s %s %d \n", v[i].codice_tratta, v[i].partenza, v[i].destinazione,
                   v[i].data, v[i].ora_partenza, v[i].ora_arrivo, v[i].ritardo);
    }
}

void ritardo(t_info v[], char riga[], int N){
    char destinazione[MAXC], dataMin[MAXC], dataMax[MAXC];
    int i;

    sscanf(riga, "%s %s %s", destinazione, dataMin, dataMax);

    for(i=0; i<N; i++){
        if(!strcmp(destinazione,v[i].destinazione) && v[i].ritardo>0 && comparaDate(v[i].data, dataMin, dataMax))
            printf("%s %s %s %s %s %s %d \n", v[i].codice_tratta, v[i].partenza, v[i].destinazione,
                   v[i].data, v[i].ora_partenza, v[i].ora_arrivo, v[i].ritardo);
    }
}

void ritardo_tot(t_info v[], char riga[], int N){
    char tratta[MAXC];
    int i, rit_tot = 0, flag = 0;

    sscanf(riga, "%s", tratta);

    for(i=0; i<N; i++) {
        if (!strcmp(tratta, v[i].codice_tratta)) {
            rit_tot += v[i].ritardo;
            flag = 1;
        }
    }

    if(flag == 1)
        printf("Il ritardo totale accumulato dalle tratte con il codice %s e' %d \n", tratta, rit_tot);
    else
        printf("Nessuna tratta trovata con il codice %s\n", tratta);

}