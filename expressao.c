#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "grafo.h"
#include "calculadora.h"

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

char *toA1(int size[], int id) {
    int numCols = size[1];  // Número de colunas na planilha

    // Calcula a linha e a coluna a partir do id
    int rowNumber = (id / numCols) + 1;  // Linha (id dividido pelo número de colunas) + 1
    int colNumber = id % numCols;        // Coluna (resto da divisão do id pelo número de colunas)

    // Convertendo a coluna para letras (base 26)
    char colStr[10];  // Buffer para armazenar a representação da coluna
    int index = 0;

    while (colNumber >= 0) {
        colStr[index++] = 'A' + (colNumber % 26);  // Obter a letra correspondente
        colNumber = (colNumber / 26) - 1;          // Ajusta para a próxima iteração
    }
    colStr[index] = '\0';

    // Reverter a string de letras, já que as letras estão na ordem inversa
    for (int i = 0; i < index / 2; i++) {
        char temp = colStr[i];
        colStr[i] = colStr[index - i - 1];
        colStr[index - i - 1] = temp;
    }

    // Calcula o número de dígitos necessários para a linha
    int numDigits = snprintf(NULL, 0, "%d", rowNumber);

    // Aloca memória suficiente para colStr + número + '\0'
    char *result = (char*) malloc((strlen(colStr) + numDigits + 1) * sizeof(char));

    // Formatando a string no formato A1
    sprintf(result, "%s%d", colStr, rowNumber);

    return result;
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

int from_A1_to_Id(char *a1,int C,int tipo) {
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
    return coordenada_para_id(row+tipo,col,C);  // Ajusta para zero-based index
}


char ** extrair_id(char * expressão,int col,int *numero){
    int size = strlen(expressão);
    int indice = 0;
    char ** variaveis = (char**) malloc(sizeof(char*));
    variaveis[indice] = NULL;

    for(int i =0;i<size;i++){
        int loop = 1;
        int caracter = 0;
        
        variaveis[indice] = (char *)malloc(sizeof(char));

        while(loop){
            if(expressão[i] == ' ' || expressão[i] == '\0'){
                loop = 0;
            }else{
                variaveis[indice] = (char*) realloc(variaveis[indice],(caracter+1) * sizeof(char));
                variaveis[indice][caracter] = expressão[i];
                caracter++;
            i++;
            }
        }
            variaveis[indice] = (char*) realloc(variaveis[indice],(caracter+1) * sizeof(char*));
            variaveis[indice][caracter] = '\0';
            indice++;

            variaveis = (char **)realloc(variaveis, (indice + 1) * sizeof(char *));
            variaveis[indice] = NULL;

    }
    *numero = indice;
    return variaveis;
}

bool add_formula(Vertice ** planilha, int id_Atual,char * expressao,int size[],int tipo){
    int indice = 0;
    char *aux = (char*) malloc(10000* sizeof(char));
    infixToPostfix(expressao,aux);
    char ** variaveis = extrair_id(aux,size[1],&indice);

    free(aux);

    int * ids = (int*) malloc((indice) * sizeof(int));
    int quantity=0;
    bool erro;

    for(int i = 0;i <indice;i++){
        if(contemAlpha(variaveis[i])){
            ids[quantity++] = from_A1_to_Id(variaveis[i],size[1],tipo);
        }
    }

    Vertice * atual = get_from_id(planilha,size,id_Atual);
    atual->formula = (char*) malloc((strlen(expressao) + 1)* sizeof(char));  // Aloca espaço para a fórmula
    strcpy(atual->formula, expressao);  

    for(int i = 0;i<quantity;i++){
        Vertice * adjacente = get_from_id(planilha,size,ids[i]);        
        erro = adicionar_Adjacentes(planilha,atual,adjacente,size);

        if(!erro) return false;
    }

    int j;
    char *junto = (char *)malloc(1 * sizeof(char));
    junto[0] = '\0';

    size_t total_length = 1;
    for(int i =0,j =0;i<indice;i++){
        if(contemAlpha(variaveis[i])){
            double valor =get_from_id(planilha,size,ids[j])->number;
            sprintf(variaveis[i], "%lf", valor);
            j++;
        }
        total_length += strlen(variaveis[i]) + 1; 
        junto = (char *) realloc(junto,total_length * sizeof(char));
        strcat(junto, variaveis[i]);
        strcat(junto, " ");
    }
    double resultado = calculadora(junto);// Adicione esta linha para debug

    atual->number = resultado;
    //printf("%s -> %.2f ",junto,resultado);

    free(junto);
    free(ids);

    // Liberação de memória (recomendado para evitar vazamento de memória)
    for (int i = 0; i < indice; i++) {
        free(variaveis[i]);
    }
    free(variaveis);

    atual->isText = false;

    return true;

}

bool recalcular_valor_formula(Vertice ** planilha, Vertice * atual, int size[]) {
    if (atual->formula == NULL) {
        return false; // Se não há fórmula, nada a recalcular
    }

    int indice = 0;
    
    char *aux = (char*) malloc(10000* sizeof(char));
    
    
    // Converte a fórmula para a notação pós-fixada
    infixToPostfix(atual->formula, aux);
    
    // Extrai os IDs das variáveis usadas na fórmula
    char **variaveis = extrair_id(aux, size[1], &indice);

    free(aux);

    int *ids = (int*) malloc((indice) * sizeof(int));
    int quantity = 0;
    
    for (int i = 0; i < indice; i++) {
        if (contemAlpha(variaveis[i])) {
            ids[quantity++] = from_A1_to_Id(variaveis[i], size[1],0);
        }
    }

    // Constrói a fórmula com os valores dos adjacentes
    int j;
    char *junto = (char *)malloc(1 * sizeof(char));
    junto[0] = '\0';

    size_t total_length = 1;
    for(int i =0,j =0;i<indice;i++){
        if(contemAlpha(variaveis[i])){
            double valor =get_from_id(planilha,size,ids[j])->number;
            sprintf(variaveis[i], "%lf", valor);
            j++;
        }
        total_length += strlen(variaveis[i]) + 1; 
        junto = (char *) realloc(junto,total_length * sizeof(char));
        strcat(junto, variaveis[i]);
        strcat(junto, " ");
    }

    // Calcula o resultado da fórmula reconstruída
    double resultado = calculadora(junto);
    atual->number = resultado; // Atualiza o valor na célula

    // Libera memória alocada
    free(ids);
    free(junto);
    for (int i = 0; i < indice; i++) {
        free(variaveis[i]);
    }
    free(variaveis);

    return true;
}


bool mudar_valor(Vertice** planilha,Vertice * atual,int size[],int valor){
    atual->number = valor;
    if (atual->formula) {
        free(atual->formula);  // Libera a memória alocada para a fórmula
        atual->formula = NULL;
    } 
    if (atual->adj) {
        for (int i = 0; i < atual->numeroAdj; i++) {
            if (atual->adj[i]) {
                atual->adj[i] = NULL;
            }
        }
        free(atual->adj);
        atual->adj = NULL; 
    }
    atual->numeroAdj = 0;

    if(atual->isText) atual->isText = false;

    atualizar_formulas(planilha,size);

    return true;

}
