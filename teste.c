#include <stdio.h>
#include "stdbool.h"
#include "calculadora.h"
#include "expressao.h"
#include "grafo.h"

int main(){
    Vertice ** celulas;
    int size[2];
    int id =0;
    char aux[10];
    int auxnum;
    char auxform[15];
    bool erro;

    scanf("%d %d%*c",&size[0],&size[1]);

    celulas = (Vertice**) malloc(size[0]*sizeof(Vertice*));
    for(int i =0;i<size[0];i++){
        celulas[i] = (Vertice*) malloc(size[1]*sizeof(Vertice));
    }

    for(int i =0;i<size[0];i++){
        for(int j=0;j<size[1];j++){
            celulas[i][j].id =  coordenada_para_id(i,j,size[1]);
            celulas[i][j].adj = NULL;
            celulas[i][j].numeroAdj = 0; 
            celulas[i][j].isText = false;
        }
    }

    printf("Digite a celula que quer mudar: ");
    scanf("%[^\n]%*c",aux);
    printf("e o numero dela: ");
    scanf("%d%*c",&auxnum );

    erro = mudar_valor(celulas,get_from_id(celulas,size,from_A1_to_Id(aux,size[1])),size,auxnum);
    
    if(!erro) printf("Não foi possivel adicionar essa formula, verifique ela");
    
    print_celulas(celulas,size);

    printf("Digite a celula que quer mudar: ");
    scanf("%[^\n]%*c",aux);
    printf("e a formula dela: ");
    scanf("%[^\n]%*c",auxform);


    erro = add_formula(celulas,from_A1_to_Id(aux,size[1]),auxform,size);
    if(!erro) printf("Não foi possivel adicionar essa formula, verifique ela");

    print_celulas(celulas,size);

    printf("\nTESTE");
    printf("\nformula:%s",get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->formula);
    printf("\nnumero Adj:%d",get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->numeroAdj);
    printf("\nAdj:%s",get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->adj);
    printf("\nis text:%d\n",get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->isText);

    // printf("Digite a celula que quer mudar: ");
    // scanf("%[^\n]%*c",aux);
    // printf("e o texto dela: ");
    // scanf("%[^\n]%*c",auxform);
    // get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->formula = auxform;
    // get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->isText = true;
    

    // print_celulas(celulas,size);


    printf("Digite a celula que quer mudar: ");
    scanf("%[^\n]%*c",aux);
    printf("e o numero dela: ");
    scanf("%d%*c",&auxnum );

    Vertice *celula_atual = get_from_id(celulas, size, from_A1_to_Id(aux, size[1]));
    if (celula_atual == NULL) {
        printf("Erro: Célula não encontrada\n");
        return -1;
    }


    erro = mudar_valor(celulas,celula_atual,size,auxnum);
    if(!erro) printf("Não foi possivel adicionar essa formula, verifique ela");
    
    print_celulas(celulas,size);
    printf("\nTESTE");
    printf("\nformula:%s",get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->formula);
    printf("\nnumero Adj:%d",get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->numeroAdj);
    printf("\nAdj:%s",get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->adj);
    printf("\nis text:%s\n",get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->isText);


    // Liberação de memória (recomendado para evitar vazamento de memória)
    for (int i = 0; i < size[0]; i++) {
        free(celulas[i]);
    }
    free(celulas);

    return 0;
}