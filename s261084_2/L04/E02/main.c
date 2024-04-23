#include <stdio.h>

int majority(int *a, int N);
int conta(int *a, int fine, int num);

int main() {
    int N = 7;
    int vet[7] = {3, 3, 9, 4, 3, 5, 3};

    int c = majority(vet, N);

    if(c != -1)
        printf("Il numero con occorrenze > N/2 e': %d", c);
    else
        printf("Nessun numero con occorrenze > N/2");

    return 0;
}

int majority(int *a, int N) //funzione ricorsiva che ritorna l'elemento maggioritario
{
    if(N == 1) return a[0];
    int mid = N/2;

    int sinistra = majority(a, mid); //elemento maggioritario di sinistra
    int destra = majority(a+mid, N-mid); //elemento maggioritario di destra

    if(sinistra == destra)
        return sinistra;

    if(conta(a, N, sinistra) > N/2)
        return sinistra;

    if(conta(a, N, destra) > N/2)
        return destra;

    return -1 ;
}

int conta(int *a, int fine, int num){ //funzione che conta quante volte num appare in un vettore di "fine" elementi
    int i, cnt = 0;
    for(i=0; i<fine; i++){
        if(a[i] == num)
            cnt++;
    }
    return cnt;
}
