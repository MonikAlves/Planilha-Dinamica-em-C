#include "grafo.h"
#include "stdbool.h"
#ifndef __EXPRESSAO_H__
#define __EXPRESSAO_H__

int id_para_linha(int id, int colunas) ;
int id_para_coluna(int id, int colunas) ;
void toA1(int size[0], char *result);
int prec(char c);
char associativity(char c) ;
void infixToPostfix(char s[], char result[]) ;
bool add_formula(Vertice ** planilha, int id_Atual,char * expressao,int size[]);
int coordenada_para_id(int x, int y, int colunas) ;
int contemAlpha(char *str) ;
int from_A1_to_Id(char *a1,int C);
int * extrair_id(char * expressão,int col,int *indice);
bool mudar_valor(Vertice** planilha,Vertice * atual,int size[],int valor);
bool recalcular_valor_formula(Vertice ** planilha, Vertice * atual, int size[]);

#endif