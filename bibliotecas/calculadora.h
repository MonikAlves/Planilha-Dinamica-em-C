#ifndef __CALCULADORA_H__
#define __CALCULADORA_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no No;

No* createNo();
double add(double number,char converter);
void empilhar(No** new,double number);
double desimpilhar(No** new);
void operação(No ** new, char operação);
double getresultado(No* no);
double calculadora(char* expressão);
void exibirMenu() ;

#endif