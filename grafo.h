#include <stdbool.h>
#ifndef __GRAFO_H__
#define __GRAFO_H__

typedef struct vertice{
    int id;
    double number;
    char * formula;
    struct vertice ** adj;
    int numeroAdj;
    bool change;
}Vertice;

typedef struct planilha{
    int linha;
    int coluna;
    Vertice ** celulas;
}Planilha;



Vertice * get_from_id(Vertice** planilha,int lin, int col,int id);
bool is_Cyclic_Util(Vertice *v, bool visitado[], bool recStack[]) ;
bool is_Cyclic(Vertice **matrix, int l,int C) ;
bool adicionar_Adjacentes(Vertice ** planilha,Vertice* atual,Vertice* destino,int l,int c);
void print_celulas(Vertice ** celulas,int L, int C);



#endif