#include <stdio.h>
#include "calculadora.h"
#include "expressao.h"
#include "grafo.h"

int main(){
    Vertice ** celulas;
    int col,lin;
    int id =0;
    char aux[10];
    int auxnum;

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

    print_alfabeto(col);
    
    for(int i =0;i<lin;i++){
        printf("[%*s%d%*s]", 1, "", i+1, 1, "");
        for(int j=0;j<col;j++){
            printf("[%*s%d%*s]", 2, "", celulas[i][j].id, 2, "");
        }
        printf("\n");
    }

    printf("Digite a celula que quer mudar: ");
    scanf("%[^\n]%*c",aux);
    printf("e o numero dela: ");
    scanf("%d",&auxnum );

    get_from_id(celulas,lin,col,from_A1_to_Id(aux,col))->number = auxnum;

    print_alfabeto(col);

printf("%*s", 5, "-");
printf("⊹")
    for (int j = 0; j < col; j++) {
        for (int k = 0; k < 12; k++) {
            printf("-");  // Adicionar sublinhado para cada célula de largura 'cellWidth'
        }
    }

    printf("\n");

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

    // Liberação de memória (recomendado para evitar vazamento de memória)
    for (int i = 0; i < lin; i++) {
        free(celulas[i]);
    }
    free(celulas);

    return 0;
}