#ifndef __EXPRESSAO_H__
#define __EXPRESSAO_H__

int id_para_linha(int id, int colunas) ;
int id_para_coluna(int id, int colunas) ;
void toA1(int row, int col, char *result);
int prec(char c);
char associativity(char c) ;
void infixToPostfix(char s[], char result[]) ;
int coordenada_para_id(int x, int y, int colunas) ;
int contemAlpha(char *str) ;
int from_A1_to_Id(char *a1,int C);
int * extrair_id(char * expressão,int col);

#endif