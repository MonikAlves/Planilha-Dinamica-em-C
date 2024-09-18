#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void adicionarAdjacentes(Vertice ** planilha,Vertice* celula,int id){
    //Percorre a linhas
    for(int i =0;i<2;i++){
        //Percorre as colunas
        for(int j=0;j<2;j++){
            //Se tem algum vertice com o id
            if(planilha[i][j].id == id){
                int indice = celula->numeroAdj;
                //Primeiro
                if(indice == 0){
                    celula->adj = (Vertice*) malloc(sizeof(Vertice));
                //Outros
                }else{
                    celula->adj = (Vertice*) realloc(celula->adj,(indice+1) * sizeof(Vertice));
                }
                celula->adj[indice] = planilha[i][j];
                celula->numeroAdj++;
                return;

            }
        }
    }

    printf("Não foi encontrado célula com id = %d",id);

    return;
}

void print(Vertice ** celulas){
    for(int i =0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("Célula (%d, %d) com ID %d tem %d adjacente(s): ", i, j, celulas[i][j].id, celulas[i][j].numeroAdj);
                if(celulas[i][j].numeroAdj){
                    for(int k = 0; k < celulas[i][j].numeroAdj;k++){
                        printf("%d",celulas[i][j].adj[k].id);
                    }
                }else{
                    printf("--");
                }
            printf("\n");
        }
    }
}

int main(){
    Vertice ** celulas;
    int id =0;

    celulas = (Vertice**) malloc(2*sizeof(Vertice*));
    for(int i =0;i<2;i++){
        celulas[i] = (Vertice*) malloc(2*sizeof(Vertice));
    }

    for(int i =0;i<2;i++){
        for(int j=0;j<2;j++){
            celulas[i][j].id =  id++;
            celulas[i][j].adj = NULL;
            celulas[i][j].numeroAdj = 0; 
        }
    }

    adicionarAdjacentes(celulas,&celulas[0][1],5);

    // Imprimir adjacências
    print(celulas);

    // Liberação de memória (recomendado para evitar vazamento de memória)
    for (int i = 0; i < 2; i++) {
        free(celulas[i]);
    }
    free(celulas);

    return 0;
}
