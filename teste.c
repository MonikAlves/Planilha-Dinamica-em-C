#include <stdio.h>
#include "calculadora.h"

int main(){
    double teste;
    char a[6] = "2 5 +";
    teste =calculadora(a);

    printf("%f",teste);
    return 0;
}

void extrair_id(char *expressao) {
    int size = strlen(expressao);
    int indice = 0;
    
    // Inicializa uma matriz de strings
    char **variaveis = (char **)malloc(sizeof(char *));
    variaveis[indice] = NULL;

    for (int i = 0; i < size; i++) {
        int loop = 1;
        int caracter = 0;

        // Inicia uma nova string para armazenar o token
        variaveis[indice] = (char *)malloc(sizeof(char));

        while (loop && i < size) {
            if (expressao[i] == ' ' || expressao[i] == '\0') {
                loop = 0;  // Termina o loop ao encontrar um espaço ou o final da string
            } else {
                // Realoca espaço para o próximo caractere
                variaveis[indice] = (char *)realloc(variaveis[indice], (caracter + 1) * sizeof(char));
                variaveis[indice][caracter] = expressao[i];
                caracter++;
            }
            i++;
        }

        // Adiciona o terminador nulo para a string
        variaveis[indice] = (char *)realloc(variaveis[indice], (caracter + 1) * sizeof(char));
        variaveis[indice][caracter] = '\0';  // Finaliza a string

        indice++;  // Incrementa o índice para o próximo token

        // Realoca a matriz para comportar mais strings
        variaveis = (char **)realloc(variaveis, (indice + 1) * sizeof(char *));
        variaveis[indice] = NULL;  // Inicializa a nova posição
    }