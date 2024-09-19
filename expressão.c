#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char * aux = (char*) malloc(10000* sizeof(char));

    printf("Digite a expressão: ");
    scanf("%[^\n]%*c",aux);
    
    char * expressão = (char *) malloc(strlen(aux) * sizeof(char));

    strcpy(expressão,aux);

    printf("%s",expressão);

    free(aux);
    free(expressão);


    return 0;
}
