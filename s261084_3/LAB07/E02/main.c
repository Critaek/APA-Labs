#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false ,true} bool;
typedef enum {zaffiro, smeraldo, rubino, topazio} tipoPietra;

typedef struct{
    tipoPietra tipo;
    int n;
    int val;
}pietra;

char *dispRip(int pos, char *val, char *sol, int n, int k, pietra *vet, int maxrip);
bool pruning(char *sol, int pos, pietra *vet, int maxrip);
void setvoid(char *sol, int pos, int k);
bool isvoid(char *sol, int k);
int valoreTot(char *sol, int k, pietra *vet);

int main() {
    int k = 0, i, maxrip;
    int tot = 0, valtot;

    char val[4];
    pietra *vet = malloc(4 * sizeof(pietra));

    for(i=0; i<4; i++)
        vet[i].tipo = i;

    printf("Inserire il numero di zaffiri con rispettivo valore: ");
    scanf("%d %d", &vet[0].n, &vet[0].val);

    printf("Inserire il numeri di smeraldi con rispettivo valore: ");
    scanf("%d %d", &vet[1].n, &vet[1].val);

    printf("Inserire il numero di rubini con rispettivo valore: ");
    scanf("%d %d", &vet[2].n, &vet[2].val);

    printf("Inserire il numero di topazi con rispettivo valore: ");
    scanf("%d %d", &vet[3].n, &vet[3].val);

    printf("Inserire il numero massimo di ripetizioni possibili: ");
    scanf("%d", &maxrip);

    printf("\n");

    for(i=0; i<4; i++)
        tot += vet[i].n;

    val[0] = 'z';
    val[1] = 's';
    val[2] = 'r';
    val[3] = 't';

    char *sol;
    sol = malloc(tot*sizeof(char));
    setvoid(sol, 0, tot);

    for(k=tot; k>0; k--) {

        sol = dispRip(0, val, sol, 4, k, vet, maxrip);

        if(!isvoid(sol, k)) {
            printf("Zaffiri = %d, smeraldi = %d, rubini = %d, topazi = %d, TOT = %d, MaxRip = %d\n",vet[0].n,vet[1].n,vet[2].n,vet[3].n,tot, maxrip);
            valtot = valoreTot(sol, k, vet);
            printf("Soluzione ottima di valore %d usando %d gemme\n",valtot, k);
            for (i = 0; i < k; i++) {
                printf("%c ", sol[i]);
            }
            printf("\n");
            break;
        }
    }

    free(sol);

    return 0;
}

char *dispRip(int pos, char *val, char *sol, int n, int k, pietra *vet, int maxrip){
    int i;

    if(pos>=k){
            return sol;
    }

    for(i=0; i<n; i++){
        sol[pos] = val[i];
        if(pos>0){
            if (pruning(sol, pos, vet, maxrip)) {
                sol = dispRip(pos + 1, val, sol, n, k, vet, maxrip);
                if (sol[pos] != '0')
                    return sol;
            }
        }
        else {
            sol = dispRip(pos + 1, val, sol, n, k, vet, maxrip);
            if (!isvoid(sol,k))
                return sol;
        }

        sol[pos] = '0';
    }
    return sol;
}

bool pruning(char *sol, int pos, pietra *vet, int maxrip){
    bool ok = false;
    char x = sol[pos];
    int cnt_z, cnt_s, cnt_r, cnt_t, cnt, i;
    cnt_z = cnt_s = cnt_r = cnt_t = cnt =  0;

    switch(sol[pos-1]){
        case 'z':
            if(x == 'z' || x == 'r')
                ok = true;
            break;
        case 's':
            if(x == 's' || x == 't')
                ok = true;
            break;
        case 'r':
            if(x == 's' || x == 't')
                ok = true;
            break;
        case 't':
            if(x == 'z' || x == 'r')
                ok = true;
            break;
    }

    if(ok == true) {
        for (i = 0; i <= pos; i++) {
            x = sol[i];
            switch (x) {
                case 't':
                    cnt_t++;
                    break;
                case 'z':
                    cnt_z++;
                    break;
                case 'r':
                    cnt_r++;
                    break;
                case 's':
                    cnt_s++;
                    break;
                case '0':
                    cnt++;
                    break;
            }
        }

        if(cnt_z <= vet[zaffiro].n && cnt_s <= vet[smeraldo].n && cnt_r <= vet[rubino].n && cnt_t <= vet[topazio].n && cnt == 0)
            ok = true;
        else
            ok = false;
    }

    if(ok == true)
        if(cnt_z > cnt_s)
            ok = false;


    if(ok == true && pos >= maxrip){
        cnt = 0;
        for(i=pos; i >= pos-maxrip + 1; i--) {
            if (sol[i] == sol[i - 1])
                cnt++;
        }
        if(cnt >= maxrip)
            ok = false;
    }

    return ok;
}

void setvoid(char *sol, int pos, int k){
    for(int i=pos; i<k; i++)
        sol[i] = '0';
}

bool isvoid(char *sol, int k){
    int i, cnt = 0;
    for(i=0; i<k; i++)
        if(sol[i] == '0')
            cnt++;

    if(cnt > 0)
        return true;

    return false;
}

int valoreTot(char *sol, int k, pietra *vet){
    int valtot = 0;
    char x;
    int cnt_z, cnt_s, cnt_r, cnt_t, i;
    cnt_z = cnt_s = cnt_r = cnt_t =  0;
    for (i = 0; i <= k; i++) {
        x = sol[i];
        switch (x) {
            case 't':
                cnt_t++;
                break;
            case 'z':
                cnt_z++;
                break;
            case 'r':
                cnt_r++;
                break;
            case 's':
                cnt_s++;
                break;
            default:
                break;
        }
    }
    valtot = cnt_z*vet[zaffiro].val + cnt_s*vet[smeraldo].val + cnt_r*vet[rubino].val + cnt_t*vet[topazio].val;

    return valtot;
}