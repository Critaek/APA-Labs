#ifndef LAB11ES1_DATAORA_H
#define LAB11ES1_DATAORA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int GG;
    int MM;
    int AA;
}Data;

typedef struct{
    int HH;
    int MM;
}Ora;

Data DATAload(char *string);
int DATAcmp(Data d1, Data d2);
void DATAprint(Data d);
Data DATAsetNull();

#endif
