#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "expressao.h"
#include <string.h>
#include <ctype.h>


Vertice * get_from_id(Vertice** planilha,int lin, int col,int id){
    for(int i =0;i<lin;i++){
        for(int j=0;j<col;j++){
            if(planilha[i][j].id == id) return &planilha[i][j]; 
        }
    }
    printf("célula com id = %d não encontrada",id);
    return NULL;
}

void set_number(Vertice * celula,double number){
    celula->number = number;
}

// Função auxiliar para verificar ciclos
bool is_Cyclic_Util(Vertice *v, bool visitado[], bool recStack[]) {
    if (!visitado[v->id]) {
        visitado[v->id] = true;
        recStack[v->id] = true;

        for (int i = 0; i < v->numeroAdj; i++) {
            Vertice *adj = v->adj[i];
            if (!visitado[adj->id] && is_Cyclic_Util(adj, visitado, recStack)) {
                return true;
            } else if (recStack[adj->id]) {
                return true;
            }
        }
    }
    recStack[v->id] = false;
    return false;
}
// Função principal para verificar ciclos
bool is_Cyclic(Vertice **matrix, int l,int C) {
    bool visitado[l * C];
    bool recStack[l * C];

    for (int i = 0; i < l * C; i++) {
        visitado[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < C; j++) {
            Vertice *v = &matrix[i][j];
            if (!visitado[v->id] && is_Cyclic_Util(v, visitado, recStack)) {
                return true;
            }
        }
    }

    return false;
}

bool adicionar_Adjacentes(Vertice ** planilha,Vertice* atual,Vertice* destino,int l,int c){
    if(planilha == NULL || atual == NULL || destino == NULL) return false;
        int indice = atual->numeroAdj;
        //Primeiro
        if(indice == 0){
            atual->adj = (Vertice**) malloc(sizeof(Vertice*));
        //Outros
        }else{
            atual->adj = (Vertice**) realloc(atual->adj,(indice+1) * sizeof(Vertice*));
        }
        //add 
        atual->adj[indice] = destino;
        atual->numeroAdj++;

        if (is_Cyclic(planilha, l,c)) {
            printf("Ciclo detectado! Não adicionando a adjacência entre %d e %d.\n", atual->id, destino->id);
            atual->numeroAdj--;
            atual->adj = (Vertice **)realloc(atual->adj, indice * sizeof(Vertice*)); 
            return false; // Remove o último adjacente
        } else {
            printf("Adjacência adicionada entre %d e %d.\n", atual->id, destino->id);
        }

    return true;
}

void print_celulas(Vertice ** celulas,int lin, int col){
    for (int i = 0; i < lin; i++) {
    int rowPadding = (10 - 1) / 2;  // Centralizando o número da linha
    printf("[%*s%d%*s] | ", 1, "", i+1, 1, "");
    for (int j = 0; j < col; j++) {
        char buffer[20];
        int len = snprintf(buffer, sizeof(buffer), "%d", celulas[i][j].id);  // Tamanho do número
        int padding = (10 - len) / 2;  // Calcular o espaçamento para centralizar

        printf("[%*s%d%*s]", padding, "", celulas[i][j].id, 10 - len - padding, "");
    }
    printf("\n");
}
}

void print_alfabeto(int col){
    printf("[%*s%c%*s] | ", 1, "", " ", 1, "");
    for(int i = 0;i<col;i++){
        int temp = i+1;
        char columnName[10];
        int index = 0;

        while (temp > 0) {
            temp -= 1;
            columnName[index++] = ('A') + (((temp) % 26));
            temp /= 26;
        }

        for (int j = 0; j < index / 2; j++) {
            char tempChar = columnName[j];
            columnName[j] = columnName[index - j - 1];
            columnName[index - j - 1] = tempChar;
        }

        columnName[index] = '\0';
        int padding = (10 - 1) / 2;  // Calcular o espaçamento para centralizar
        printf("[%*s%s%*s]", padding, "", columnName, 10 - padding - 1, "");
    }
    printf("\n");
}



// int main(){
//     Vertice ** celulas;
//     int col,lin;
//     int id =0;

//     scanf("%d %d%*c",&lin,&col);

//     celulas = (Vertice**) malloc(lin*sizeof(Vertice*));
//     for(int i =0;i<lin;i++){
//         celulas[i] = (Vertice*) malloc(col*sizeof(Vertice));
//     }

//     for(int i =0;i<lin;i++){
//         for(int j=0;j<col;j++){
//             celulas[i][j].id =  coordenada_para_id(i,j,col);
//             celulas[i][j].adj = NULL;
//             celulas[i][j].numeroAdj = 0; 
//         }
//     }

    
//     adicionarAdjacentes(celulas,get_from_id(celulas,lin,col,1),get_from_id(celulas,lin,col,5),lin,col);
//     adicionarAdjacentes(celulas,get_from_id(celulas,lin,col,0),get_from_id(celulas,lin,col,3),lin,col);
//     adicionarAdjacentes(celulas,get_from_id(celulas,lin,col,2),get_from_id(celulas,lin,col,5),lin,col);
//     adicionarAdjacentes(celulas,get_from_id(celulas,lin,col,5),get_from_id(celulas,lin,col,2),lin,col);

//     print_alfabeto(col);
    
//     for(int i =0;i<lin;i++){
//         printf("[%*s%d%*s]", 1, "", i+1, 1, "");
//         for(int j=0;j<col;j++){
//             printf("[%*s%.2f%*s]", 2, "", celulas[i][j].id, 2, "");
//         }
//         printf("\n");
//     }

//     // Liberação de memória (recomendado para evitar vazamento de memória)
//     for (int i = 0; i < lin; i++) {
//         free(celulas[i]);
//     }
//     free(celulas);

//     return 0;
// }
