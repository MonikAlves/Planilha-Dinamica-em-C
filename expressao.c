#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "grafo.h"

int coordenada_para_id(int x, int y, int colunas) {
    return x * colunas + y;
}

// Função para converter o ID de volta para coordenada (x, y)
int id_para_linha(int id, int colunas) {
    return id / colunas;
}

int id_para_coluna(int id, int colunas) {
    return id % colunas;
}

void toA1(int row, int col, char *result) {
    // Convertendo a coluna para letras (base 26)
    char colStr[10];  // Buffer para armazenar a representação da coluna
    int index = 0;
    
    while (col >= 0) {
        colStr[index++] = 'A' + (col % 26);
        col = (col / 26) - 1;  // Ajusta a coluna para a próxima iteração
    }
    colStr[index] = '\0';

    // Reverter a string de letras
    for (int i = 0; i < index / 2; i++) {
        char temp = colStr[i];
        colStr[i] = colStr[index - i - 1];
        colStr[index - i - 1] = temp;
    }

    // Convertendo a linha para o número (começa com 1)
    int rowNumber = row + 1;
    
    // Formatando a string no formato A1
    sprintf(result, "%s%d", colStr, rowNumber);
}

// Função para retornar a precedência dos operadores
int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Função para retornar a associatividade dos operadores
char associativity(char c) {
    if (c == '^')
        return 'R';
    return 'L'; // Padrão: associativo à esquerda
}

void infixToPostfix(char s[], char result[]) {
    int resultIndex = 0;
    int len = strlen(s);
    char stack[1000];
    int stackIndex = -1;

    for (int i = 0; i < len; i++) {
        char c = s[i];

        // Ignora espaços
        if (c == ' ') {
            continue;
        }

        // Se o caractere for uma letra ou número, adiciona ao resultado
        if (isalnum(c)) {
            result[resultIndex++] = c;

            // Verifica se os próximos caracteres também fazem parte do número ou variável
            while (isalnum(s[i + 1])) {
                result[resultIndex++] = s[++i]; // Adiciona os próximos caracteres do número ou variável
            }

            result[resultIndex++] = ' '; // Adiciona espaço após o operando
        }
        // Se o caractere for um '(', empilha
        else if (c == '(') {
            stack[++stackIndex] = c;
        }
        // Se o caractere for um ')', desempilha até encontrar '('
        else if (c == ')') {
            while (stackIndex >= 0 && stack[stackIndex] != '(') {
                result[resultIndex++] = stack[stackIndex--];
                result[resultIndex++] = ' '; // Adiciona espaço após o operador
            }
            stackIndex--; // Remove '('
        }
        // Se o caractere for um operador
        else {
            while (stackIndex >= 0 && (prec(s[i]) < prec(stack[stackIndex]) ||
                                       (prec(s[i]) == prec(stack[stackIndex]) &&
                                           associativity(s[i]) == 'L'))) {
                result[resultIndex++] = stack[stackIndex--];
                result[resultIndex++] = ' '; // Adiciona espaço após o operador
            }
            stack[++stackIndex] = c; // Empilha o operador atual
        }
    }

    // Desempilha todos os operadores restantes
    while (stackIndex >= 0) {
        result[resultIndex++] = stack[stackIndex--];
        result[resultIndex++] = ' '; // Adiciona espaço após o operador
    }

    result[resultIndex - 1] = '\0'; // Remove o último espaço e finaliza a string
}

int contemAlpha(char *str) {
    while (*str) {
        if (isalpha(*str)) {
            return 1; // Retorna 1 se encontrar uma letra
        }
        str++;
    }
    return 0; // Retorna 0 se não encontrar nenhuma letra
}

int from_A1_to_Id(char *a1,int C) {
    // Encontrar a parte da coluna
    char *p = a1;
    int colNumber = 0;
    int row,col;
    
    // Ler letras e calcular a coluna
    while (isalpha(*p)) {
        *p = toupper(*p);
        colNumber = colNumber * 26 + (*p - 'A' + 1);
        p++;
    }

    col = colNumber - 1;  // Ajusta para zero-based index
    
    // Encontrar a parte do número da linha
    int rowNumber = atoi(p);
    row = rowNumber - 1;
    
    return  coordenada_para_id(row,col,C);  // Ajusta para zero-based index
}


char ** extrair_id(char * expressão,int col,int *indice){
    int size = strlen(expressão);
    *indice = 0;
    char ** variaveis = (char**) malloc(sizeof(char*));
    variaveis[*indice] = NULL;

    for(int i =0;i<size;i++){
        int loop = 1;
        int caracter = 0;
        
        variaveis[*indice] = (char *)malloc(sizeof(char));

        while(loop){
            if(expressão[i] == ' ' || expressão[i] == '\0'){
                loop = 0;
            }else{
                variaveis[*indice] = (char*) realloc(variaveis[*indice],(caracter+1) * sizeof(char));
                variaveis[*indice][caracter] = expressão[i];
                caracter++;
            i++;
            }
        }
            variaveis[*indice] = (char*) realloc(variaveis[*indice],(caracter+1) * sizeof(char*));
            variaveis[*indice][caracter] = '\0';
            *indice++;

            variaveis = (char **)realloc(variaveis, (*indice + 1) * sizeof(char *));
            variaveis[*indice] = NULL;

    }

    return variaveis;

    for(int i =0;i<*indice;i++){
        free(variaveis[i]);
    }
    free(variaveis);
}

bool add_formula(Vertice ** planilha, int id_Atual,char * expressao,int col,int linha){
    int indice = 0;
    char ** variaveis = extrair_id(expressao,col,&indice);
    int * ids = (int*) malloc((indice) * sizeof(int));
    int quantity=0;
    bool erro;

    for(int i = 0;i <indice;i++){
        if(contemAlpha(variaveis[i])){
            ids[quantity++] = from_A1_to_Id(variaveis[i],col);
        }
    }


    Vertice * atual = get_from_id(planilha,linha,col,id_Atual);

    for(int i = 0;i<quantity;i++){
        Vertice * adjacente = get_from_id(planilha,linha,col,ids[i]);        
        erro = adicionar_Adjacentes(planilha,atual,adjacente,linha,col);

        if(!erro) return false;
    }

    int j;
    char junto[20];

    for(int i =0,j =0;i<strlen(*variaveis);i++){
        if(contemAlpha(variaveis[i])){
            itoa(ids[j++],variaveis[i],10);
        }
        strcat(junto,variaveis[i]);
    }
    
    char tess[7];

    infixToPostfix(junto,tess);

    printf("%s - ",tess);

}

// int main(){
//     char * aux = (char*) malloc(10000* sizeof(char));

//     printf("Digite a expressão: ");
//     scanf("%[^\n]%*c",aux);
    
//     char * expressão = (char *) malloc(strlen(aux) * sizeof(char));

//     strcpy(expressão,aux);

//     char result[1000]; // Para armazenar a expressão pós-fixada

//     // Converte a expressão infixa para pós-fixada
//     infixToPostfix(aux, result);

//     printf("Expressão pós-fixada: %s\n", result);

//     // Extrai os IDs (variáveis/operandos) da expressão pós-fixada
//     extrair_id(result, 9);

//     free(aux);
//     free(expressão);


//     return 0;
// }

// //a1+b1*(c1^d1-e1)^(f1+g1*h1)-i1