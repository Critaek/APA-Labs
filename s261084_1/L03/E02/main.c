#include <stdio.h>

int checkEndianness(void);
void stampaCodifica(void *p, int size, int bigEndian);

int main() {
    float af = 1;
    double ad = 1;
    long double ald = 1;
    int bigEndian;

    bigEndian = checkEndianness();

    printf("Dimensione float %d\n", sizeof(af));
    printf("Dimensione double %d\n", sizeof(ad));
    printf("Dimensione long double %d\n", sizeof(ald));
    printf("\n");

    if(bigEndian)
        printf("Bid Endian!\n");
    if(!bigEndian)
        printf("Little Endian!\n\n");

    printf("Inserire numero: ");
    scanf("%lf", &ad);
    af = (float)ad;
    ald = (long double)ad;
    printf("\n");

    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);
    stampaCodifica((void *)&ald,sizeof(ald),bigEndian);

    return 0;
}

int checkEndianness(void){
    int x = 1;
    char *cod = (char *)&x;
    if(cod[0] == 0)
        return 1;

    return 0;
}

void stampaCodifica(void *p, int size, int bigEndian){
    unsigned char *aux = p;
    int i, j, k, n_bit = size*8;
    int bit[n_bit], mantissa;

    switch(size){
        case 4:
            mantissa = 8;
            break;
        case 8:
            mantissa = 11;
            break;
        case 12:
            mantissa = 15;
            break;
        case 16:
            mantissa = 15;
            break;
    }

    if(bigEndian){
        for(i = 0, k = 0; i < size; i++, k++)
            for (j = 7; j >= 0; j--)
                bit[k] = aux[i] >> j & 1;
    }
    else{
        for(i = 0, k = n_bit-8; i < size; i++, k-=16)
            for (j = 7; j >= 0; j--)
                bit[k++] = aux[i] >> j & 1;

    }

    printf("Bit di segno: %d\n", bit[0]);

    printf("Bit di esponente: ");
    for(i=1; i<=mantissa; i++)
        printf("%d", bit[i]);
    printf("\n");

    printf("Bit di mantissa: ");
    for(i=mantissa+1; i<n_bit; i++)
        printf("%d", bit[i]);
    printf("\n\n");
}