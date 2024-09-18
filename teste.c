#include <stdio.h>
#include "calculadora.h"

int main(){
    double teste;
    char a[6] = "2 5 +";
    teste =calculadora(a);

    printf("%f",teste);
    return 0;
}