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



#endif