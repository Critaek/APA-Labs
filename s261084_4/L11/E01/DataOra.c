#include "DataOra.h"

Data DATAload(char *string){
    Data d;

    sscanf(string, "%d/%d/%d", &d.AA, &d.MM, &d.GG);

    return d;
}

int DATAcmp(Data d1, Data d2){
    if(d1.AA != d2.AA)
        return (d1.AA - d2.AA);

    if(d1.MM != d2.MM)
        return (d1.MM - d2.MM);

    if(d1.GG != d2.GG)
        return (d1.GG - d2.GG);

    return 0; //se solo uguali
}

void DATAprint(Data d){
    printf("%d/%d/%d ", d.GG, d.MM, d.AA);
}

Data DATAsetNull(){
    Data d;
    d.AA = d.MM = d.GG = -1;
    return d;
}