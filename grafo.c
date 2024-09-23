#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "expressao.h"
#include <string.h>
#include <ctype.h>

Vertice * get_from_id(Vertice** planilha,int size[],int id){
    int lin = size[0];
    int col = size[1];
    for(int i =0;i<lin;i++){
        for(int j=0;j<col;j++){
            if(planilha[i][j].id == id) return &planilha[i][j]; 
        }
    }
    char* not = toA1(size,id);
    printf("célula %s não encontrada\n",not);
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
bool is_Cyclic(Vertice **matrix, int size[]) {
    int lin = size[0];
    int col = size[1];
    bool visitado[lin * col];
    bool recStack[lin * col];

    for (int i = 0; i < lin * col; i++) {
        visitado[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            Vertice *v = &matrix[i][j];
            if (!visitado[v->id] && is_Cyclic_Util(v, visitado, recStack)) {
                return true;
            }
        }
    }

    return false;
}

void recalcular_formulas(Vertice** planilha, Vertice * atual, bool visitado[],int size[]) {
    if (!visitado[atual->id]) {
        visitado[atual->id] = true;

        // Percorre os adjacentes primeiro (DFS vai ao fundo da dependência)
        for (int i = 0; i < atual->numeroAdj; i++) {
            Vertice *adj = atual->adj[i];
            recalcular_formulas(planilha,adj, visitado,size);
        }
        // Após processar os adjacentes, recalcula o valor da célula atual
        if (atual->formula != NULL) recalcular_valor_formula(planilha,atual,size);
    }
}

void atualizar_formulas(Vertice **planilha, int size[]) {
    int lin = size[0];
    int col = size[1];
    bool visitado[lin * col];

    // Inicializa o array de visitados
    for (int i = 0; i < lin * col; i++) {
        visitado[i] = false;
    }

    // Percorre toda a matriz de vértices
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            Vertice *atual = &planilha[i][j];
            if (!visitado[atual->id]) {
                if(atual->formula && atual->isText == false) recalcular_formulas(planilha,atual, visitado,size);
                visitado[atual->id] = true; 
            }
        }
    }
}


bool adicionar_Adjacentes(Vertice ** planilha,Vertice* atual,Vertice* destino,int size[]){
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

        if (is_Cyclic(planilha, size)) {
            printf("Ciclo detectado! Não adicionando a adjacência entre %d e %d.\n", atual->id, destino->id);
            atual->numeroAdj--;
            atual->adj = (Vertice **)realloc(atual->adj,  atual->numeroAdj * sizeof(Vertice*)); 
            return false; // Remove o último adjacente
        } else {
            //printf("Adjacência adicionada entre %d e %d.\n", atual->id, destino->id);
        }

    return true;
}

void print_celulas(Vertice ** celulas,int size[]){
    int lin = size[0];
    int col = size[1];
    int maxLength[col];
    memset(maxLength, 0, sizeof(maxLength)); // Inicializa com 0

    // Primeiro, calcular os tamanhos máximos
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < lin; i++) {
            int len;
            if (celulas[i][j].isText) {
                len = strlen(celulas[i][j].formula);
            } else {
                char buffer[20];
                snprintf(buffer, sizeof(buffer), "%.2lf", celulas[i][j].number);
                len = strlen(buffer);
            }
            if (len > maxLength[j]) {
                maxLength[j] = len; // Atualiza o comprimento máximo
            }
        }
    }

    // Imprimir cabeçalho
    printf("[%*s%c%*s] | ", 1, "", ' ', 1, "");
    for (int i = 0; i < col; i++) {
        char columnName[10];
        int temp = i + 1;
        int index = 0;

        while (temp > 0) {
            temp -= 1;
            columnName[index++] = 'A' + ((temp) % 26);
            temp /= 26;
        }

        // Reverter a string de letras
        for (int j = 0; j < index / 2; j++) {
            char tempChar = columnName[j];
            columnName[j] = columnName[index - j - 1];
            columnName[index - j - 1] = tempChar;
        }
        columnName[index] = '\0';

        int padding = (maxLength[i] - strlen(columnName)) / 2; // Calcular o espaçamento
        printf("[%*s %s%*s]", padding + 2, "", columnName, maxLength[i] - padding - strlen(columnName) + 2, ""); // +2 para o espaço adicional
    }
    printf("\n");

    // Imprimir linha de separação
    printf(" ————");
    for (int j = 0; j <= col; j++) {
        printf("———");  // Adiciona linha de separação
        if (j < col) {
            int totalPadding = maxLength[j] + 4; // Total de padding para cada coluna
            for (int p = 0; p < totalPadding; p++) {
                printf("—");
            }
        }
    }
    printf("\n");

    // Imprimir as células
    for (int i = 0; i < lin; i++) {
        printf("[%*s%d%*s] | ", 1, "", i + 1, 1, "");
        for (int j = 0; j < col; j++) {
            char buffer[20];
            char *content;
            if (celulas[i][j].isText) {
                content = celulas[i][j].formula; // Texto
            } else {
                snprintf(buffer, sizeof(buffer), "%.2lf", celulas[i][j].number); // Número formatado
                content = buffer;
            }

            int len = strlen(content);
            int padding = (maxLength[j] - len) / 2; // Centraliza com base no comprimento máximo
            printf("[%*s %s%*s]", padding + 2, "", content, maxLength[j] - padding - len + 2, ""); // +2 para o espaço adicional
        }
        printf("\n");
    }
}

void print_formulas(Vertice ** celulas,int size[]){
    int lin = size[0];
    int col = size[1];
    int maxLength[col];
    memset(maxLength, 0, sizeof(maxLength)); // Inicializa com 0

    // Primeiro, calcular os tamanhos máximos
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < lin; i++) {
            if (celulas[i][j].formula) {
                int len = strlen(celulas[i][j].formula);
                if (len > maxLength[j]) {
                    maxLength[j] = len; // Atualiza o comprimento máximo da coluna
                }
            }
        }
    }

    // Imprimir cabeçalho
    printf("[%*s%c%*s] | ", 1, "", ' ', 1, "");
    for (int i = 0; i < col; i++) {
        char columnName[10];
        int temp = i + 1;
        int index = 0;

        while (temp > 0) {
            temp -= 1;
            columnName[index++] = 'A' + ((temp) % 26);
            temp /= 26;
        }

        // Reverter a string de letras
        for (int j = 0; j < index / 2; j++) {
            char tempChar = columnName[j];
            columnName[j] = columnName[index - j - 1];
            columnName[index - j - 1] = tempChar;
        }
        columnName[index] = '\0';

        int padding = (maxLength[i] - strlen(columnName)) / 2; // Calcular o espaçamento para cada coluna
        printf("[%*s%s%*s]", padding + 2, "", columnName, maxLength[i] - padding - strlen(columnName) + 2, ""); // +2 para o espaço adicional
    }
    printf("\n");

    // Imprimir linha de separação
    printf(" ————");
    for (int j = 0; j <= col; j++) {
        printf("———");  // Adiciona linha de separação
        if (j < col) {
            int totalPadding = maxLength[j] + 4; // Total de padding para cada coluna
            for (int p = 0; p < totalPadding; p++) {
                printf("—");
            }
        }
    }
    printf("\n");

    // Imprimir as células
    for (int i = 0; i < lin; i++) {
        printf("[%*s%d%*s] | ", 1, "", i + 1, 1, "");
        for (int j = 0; j < col; j++) {
            char *content;
            if (celulas[i][j].formula) {
                content = celulas[i][j].formula;
            } else {
                content = "";
            }

            int len = strlen(content);
            int padding = (maxLength[j] - len) / 2; // Centraliza com base no comprimento máximo da coluna
            printf("[%*s%s%*s]", padding + 2, "", content, maxLength[j] - padding - len + 2, ""); // +2 para o espaço adicional
        }
        printf("\n");
    }
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
