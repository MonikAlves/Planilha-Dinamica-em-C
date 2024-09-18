#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void addadj(Vertice ** planilha,Vertice* celula,int id){

    for(int i =0;i<2;i++){
        for(int j=0;j<2;j++){
            if(planilha[i][j].id == id){
                int indice = celula->adj->numeroAdj;
                if(!indice){
                    celula->adj = (Vertice*) malloc(sizeof(Vertice));
                    celula->numeroAdj++;
                }
                celula->adj = (Vertice*) realloc(celula->adj,(indice+1) * sizeof(Vertice));
                celula->adj[indice] = planilha[i][j];
                celula->numeroAdj++;
                return;
            }
        }
    }

    return;
}

void print(Vertice ** celulas){
    for(int i =0;i<2;i++){
        for(int j=0;j<2;j++){
            if(celulas[i][j].numeroAdj){
                for(int k = celulas[i][j].numeroAdj;k>=0;k--){
                    printf("%d",celulas[i][j].adj[k].id);
                }
            }
        }
    }
}



int main(){
    Vertice ** celulas;
    int id =0;

    printf("opa");

    celulas = (Vertice**) malloc(2*sizeof(Vertice*));
    for(int i =0;i<2;i++){
        celulas[i] = (Vertice*) malloc(sizeof(Vertice));
    }

    for(int i =0;i<2;i++){
        for(int j=0;j<2;j++){
            celulas[i][j].id =  id++;
            celulas[i][j].adj = NULL;
            celulas[i][j].numeroAdj = 0; 
        }
    }

    addadj(celulas,&celulas[0][1],2);
    print(celulas);

    // for(int i =0;i<2;i++){
    //     for(int j=0;j<2;j++){
    //         printf("%d",celulas[i][j].adj->id);
    //     }
    // }



    return 0;
}