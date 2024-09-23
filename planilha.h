#include "stdbool.h"
#include "grafo.h"
#ifndef __PLANILHA_H__
#define __PLANILHA_H__


void limparterminal();
bool numero(Vertice ** planilha,int size[], int tipo);
bool texto(Vertice ** planilha,int size[], int tipo);
bool formula(Vertice ** planilha,int size[], int tipo);

#endif