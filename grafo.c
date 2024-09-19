#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include <string.h>
#include <ctype.h>

int coordenada_para_id(int x, int y, int colunas) {
    return x * colunas + y;
}

// Função para converter o ID de volta para coordenada (x, y)
int id_para_linha(int id, int colunas) {
    return id / colunas;
}

int id_para_coluna(int id, int colunas) {
    return id % colunas;
}

void toA1(int row, int col, char *result) {
    // Convertendo a coluna para letras (base 26)
    char colStr[10];  // Buffer para armazenar a representação da coluna
    int index = 0;
    
    while (col >= 0) {
        colStr[index++] = 'A' + (col % 26);
        col = (col / 26) - 1;  // Ajusta a coluna para a próxima iteração
    }
    colStr[index] = '\0';

    // Reverter a string de letras
    for (int i = 0; i < index / 2; i++) {
        char temp = colStr[i];
        colStr[i] = colStr[index - i - 1];
        colStr[index - i - 1] = temp;
    }

    // Convertendo a linha para o número (começa com 1)
    int rowNumber = row + 1;
    
    // Formatando a string no formato A1
    sprintf(result, "%s%d", colStr, rowNumber);
}

Vertice * get_from_id(Vertice** planilha,int lin, int col,int id){
    for(int i =0;i<lin;i++){
        for(int j=0;j<col;j++){
            if(planilha[i][j].id == id) return &planilha[i][j]; 
        }
    }
    printf("célula com id = %d não encontrada",id);
    return NULL;
}

int from_A1_to_Id(char *a1,int C) {
    // Encontrar a parte da coluna
    char *p = a1;
    int colNumber = 0;
    int row,col;
    
    // Ler letras e calcular a coluna
    while (isalpha(*p)) {
        colNumber = colNumber * 26 + (*p - 'A' + 1);
        p++;
    }

    col = colNumber - 1;  // Ajusta para zero-based index
    
    // Encontrar a parte do número da linha
    int rowNumber = atoi(p);
    row = rowNumber - 1;
    
    return coordenada_para_id(row,col,C);  // Ajusta para zero-based index
}

// Função auxiliar para verificar ciclos
bool isCyclicUtil(Vertice *v, bool visitado[], bool recStack[]) {
    if (!visitado[v->id]) {
        visitado[v->id] = true;
        recStack[v->id] = true;

        for (int i = 0; i < v->numeroAdj; i++) {
            Vertice *adj = v->adj[i];
            if (!visitado[adj->id] && isCyclicUtil(adj, visitado, recStack)) {
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
bool isCyclic(Vertice **matrix, int l,int C) {
    bool visitado[l * C];
    bool recStack[l * C];

    for (int i = 0; i < l * C; i++) {
        visitado[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < C; j++) {
            Vertice *v = &matrix[i][j];
            if (!visitado[v->id] && isCyclicUtil(v, visitado, recStack)) {
                return true;
            }
        }
    }

    return false;
}

void adicionarAdjacentes(Vertice ** planilha,Vertice* atual,Vertice* destino,int l,int c){
    if(planilha == NULL || atual == NULL || destino == NULL) return;
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

        if (isCyclic(planilha, l,c)) {
            printf("Ciclo detectado! Não adicionando a adjacência entre %d e %d.\n", atual->id, destino->id);
            atual->numeroAdj--;
            atual->adj = (Vertice **)realloc(atual->adj, indice * sizeof(Vertice*)); 
            return; // Remove o último adjacente
        } else {
            printf("Adjacência adicionada entre %d e %d.\n", atual->id, destino->id);
        }

    return;
}

void print(Vertice ** celulas,int L, int C){
    for(int i = 0;i<L;i++){
        for(int j=0;j<C;j++){
            printf("Célula (%d, %d) com ID %d tem %d adjacente(s): ", i, j, celulas[i][j].id, celulas[i][j].numeroAdj);
                if(celulas[i][j].numeroAdj){
                    for(int k = 0; k < celulas[i][j].numeroAdj;k++){
                        printf("%d",celulas[i][j].adj[k]->id);
                    }
                }else{
                    printf("--");
                }
            printf("\n");
        }
    }
}

void print_alfabeto(int col){
    printf("[%*s%c%*s]", 1, "", " ", 1, "");
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
        printf("[%*s%s%*s]", 3, "",columnName , 4, "");
    }
    printf("\n");
}

int main(){
    Vertice ** celulas;
    int col,lin;
    int id =0;

    scanf("%d %d%*c",&lin,&col);

    celulas = (Vertice**) malloc(lin*sizeof(Vertice*));
    for(int i =0;i<lin;i++){
        celulas[i] = (Vertice*) malloc(col*sizeof(Vertice));
    }

    for(int i =0;i<lin;i++){
        for(int j=0;j<col;j++){
            celulas[i][j].id =  coordenada_para_id(i,j,col);
            celulas[i][j].adj = NULL;
            celulas[i][j].numeroAdj = 0; 
        }
    }

    
    adicionarAdjacentes(celulas,get_from_id(celulas,lin,col,1),get_from_id(celulas,lin,col,5),lin,col);
    adicionarAdjacentes(celulas,get_from_id(celulas,lin,col,0),get_from_id(celulas,lin,col,3),lin,col);
    adicionarAdjacentes(celulas,get_from_id(celulas,lin,col,2),get_from_id(celulas,lin,col,5),lin,col);
    adicionarAdjacentes(celulas,get_from_id(celulas,lin,col,5),get_from_id(celulas,lin,col,2),lin,col);

    print_alfabeto(col);
    
    for(int i =0;i<lin;i++){
        printf("[%*s%d%*s]", 1, "", i+1, 1, "");
        for(int j=0;j<col;j++){
            printf("[%*s%.2f%*s]", 2, "", celulas[i][j].id, 2, "");
        }
        printf("\n");
    }

    // Liberação de memória (recomendado para evitar vazamento de memória)
    for (int i = 0; i < lin; i++) {
        free(celulas[i]);
    }
    free(celulas);

    return 0;
}
