#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

const char soma = '+';
const char subtração = '-';
const char multiplicação = '*';
const char divisão = '/';
const char elevado = '^';

typedef struct no{
    double numero;
    struct no* next;
}No;

No* createNo(){
    No* new =(No*) malloc(sizeof(No));
    new->next=NULL;
    return new;
}

double add(double number,char converter){
    number *=10;
    number += converter - '0';
    return number;
}

int expoente(double expo){
    int number = 1;
    int size = (int) expo;
    while(size){
        number *= 10;
        size /= 10; 
    }
    return number;    
}

void empilhar(No** new,double number){
    //printf("entrou %.2f",number);
    No* aux = createNo();
    aux->next = *new;    
    aux->numero = number;
    *new = aux;
}

double desimpilhar(No** new){
    if(*new == NULL){
        return 0;
    }

    No* aux = (*new)->next;
    double numero = (*new)->numero;
    free(*new);
    *new = aux;
    //printf("saiu %.2f",numero);
    return numero;
}

void operação(No ** new, char operação){
    double segundo = desimpilhar(new);
    double primeiro = desimpilhar(new);
    double resultado;
    if(operação == soma) resultado = primeiro + segundo;
    if(operação == subtração) resultado = primeiro - segundo;
    if(operação == multiplicação) resultado = primeiro * segundo;
    if(operação == divisão) resultado = primeiro / segundo;
    if(operação == elevado) resultado = pow(primeiro,segundo);
    empilhar(new,resultado);
}

double getresultado(No* no){
    No* aux = no;
    while(aux != NULL){
        return aux->numero;
    }
}

double calculadora(char* expressão){
    double resultado;
    No * new = NULL;
    for(unsigned int i=0;i<strlen(expressão);i++){
        int aux = 1;
        double decimal = 0;
        double integer = 0;
        double number = 0;
        int sumDecimal = 0;
        int isNegative = 0; 

         if (i == 0 && expressão[i] == '-') {
            isNegative = 1;
            i++;
        } else if (expressão[i] == '-') {
            if (i > 0 && expressão[i - 1] == ' ' && expressão[i+1] != ' ' && expressão[i+1] != '\0') {
                isNegative = 1;
                i++;
            }
        } 

        while(aux){
            if(expressão[i] == ' ' || expressão[i] == '\0'){
                aux = 0;
                number = integer + (decimal/expoente(decimal));
                if (isNegative) number = -number; 
                empilhar(&new,number);
                break;
            }

            if(expressão[i] == '.'){
                sumDecimal = 1;
                i++;
            }

            if(expressão[i] == 42 || expressão[i] == 43 || expressão[i] == 45 ||expressão[i] == 47 || expressão[i] == 94 ){

                operação(&new,expressão[i]);
                i++;

                break;
            } else if(expressão[i] < 48 || expressão[i] > 57) {
                printf("%c não é reconhecido\n",expressão[i]);
                return 0;
            }

            if(sumDecimal){
                decimal = add(decimal,expressão[i]);

            }else{
                integer = add(integer,expressão[i]);
            }
            i++;

        }
    }
    //printf("Resultado final: ");
    return getresultado(new);

}