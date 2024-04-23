#include <stdio.h>

int gcd(int a, int b);

int main() {
    int a, b;
    printf("Inserire 2 numeri: ");
    scanf("%d%d", &a, &b);

    printf("%d",gcd(a,b));

    return 0;
}

gcd(int a, int b){
    int tmp;

    if(a < b){
        tmp = a;
        a = b;
        b = tmp;
    }

    if(a == 0)
        return b;

    if(b == 0)
        return a;

    if(a % 2 == 0 && b % 2 == 0)
        return 2*gcd(a/2,b/2);

    if(a % 2 != 0 && b % 2 == 0)
        return gcd(a, b/2);

    if(a % 2 == 0 && b % 2 != 0)
        return gcd(a/2, b);

    if(a % 2 != 0 && b % 2 != 0)
        return gcd((a-b)/2, b);

}