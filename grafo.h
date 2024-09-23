#include "stdbool.h"
#ifndef __GRAFO_H__
#define __GRAFO_H__

typedef struct vertice{
    int id;
    double number;
    char * formula;
    struct vertice ** adj;
    int numeroAdj;
    bool isText;
    bool change;
}Vertice;


Vertice * get_from_id(Vertice** planilha,int size[],int id);
bool is_Cyclic_Util(Vertice *v, bool visitado[], bool recStack[]) ;
bool is_Cyclic(Vertice **matrix, int size[]) ;
bool adicionar_Adjacentes(Vertice ** planilha,Vertice* atual,Vertice* destino,int size[]);
void print_celulas(Vertice ** celulas,int size[]);
void print_formulas(Vertice ** celulas,int size[]);
void atualizar_formulas(Vertice **planilha, int size[]);



#endif