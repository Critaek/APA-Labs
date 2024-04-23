#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false ,true} bool;

char *dispRip(int pos, char *val, char *sol, int n, int k, int *numeri);
bool pruning(char *sol, int pos, int *numeri);
void setvoid(char *sol, int pos, int k);
bool isvoid(char *sol, int k);

int main() {
    int k = 0, i;
    int z, s, r, t, tot;

    char val[4];
    int *numeri = malloc(4*sizeof(int));

    printf("Inserire il numero di zaffiri: ");
    scanf("%d", &z);
    printf("Inserire il numeri di smeraldi: ");
    scanf("%d", &s);
    printf("Inserire il numero di rubini: ");
    scanf("%d", &r);
    printf("Inserire il numero di topazi: ");
    scanf("%d", &t);

    numeri[0] = z;
    numeri[1] = s;
    numeri[2] = r;
    numeri[3] = t;

    tot = z+r+s+t;

    val[0] = 'z';
    val[1] = 's';
    val[2] = 'r';
    val[3] = 't';

    char *sol;
    sol = malloc(tot*sizeof(char));
    setvoid(sol, 0, tot);

    for(k=tot; k>0; k--) {

        sol = dispRip(0, val, sol, 4, k, numeri);

        if(!isvoid(sol, k)) {
            printf("Zaffiri = %d, smeraldi = %d, rubini = %d, topazi = %d, TOT = %d\n",z,s,r,t,tot);
            printf("Collana massima di lunghezza: %d\n", k);
            for (i = 0; i < k; i++) {
                printf("%c ", sol[i]);
            }
            printf("\n");
            break;
        }
    }

    free(sol);
    free(numeri);


    return 0;
}

char *dispRip(int pos, char *val, char *sol, int n, int k, int *numeri){
    int i;

    if(pos>=k){
        return sol;
    }

    for(i=0; i<n; i++){
        sol[pos] = val[i];
        if(pos>0){
            if (pruning(sol, pos, numeri)) {
                sol = dispRip(pos + 1, val, sol, n, k, numeri);
                if (sol[pos] != '0')
                    return sol;
            }
        }
        else {
            sol = dispRip(pos + 1, val, sol, n, k, numeri);
            if (!isvoid(sol,k))
                return sol;
        }

        sol[pos] = '0';
    }
    return sol;
}

bool pruning(char *sol, int pos, int *numeri){
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

        if(cnt_z <= numeri[0] && cnt_s <= numeri[1] && cnt_r <= numeri[2] && cnt_t <= numeri[3] && cnt == 0)
            ok = true;
        else
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