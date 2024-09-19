#include <stdbool.h>
#ifndef __CALCULADORA_H__
#define __CALCULADORA_H__

typedef struct vertice{
    int id;
    double number;
    char * formula;
    struct vertice ** adj;
    int numeroAdj;
    bool change;
}Vertice;

int coordenada_para_id(int x, int y, int colunas) ;
int id_para_linha(int id, int colunas) ;
int id_para_coluna(int id, int colunas) ;
void toA1(int row, int col, char *result);
Vertice * get_from_id(Vertice** planilha,int lin, int col,int id);
int from_A1_to_Id(char *a1,int C) ;
bool isCyclicUtil(Vertice *v, bool visitado[], bool recStack[]) ;
bool isCyclic(Vertice **matrix, int l,int C) ;
void adicionarAdjacentes(Vertice ** planilha,Vertice* atual,Vertice* destino,int l,int c);


#endif