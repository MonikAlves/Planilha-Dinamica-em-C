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
    char auxform[5];

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

    printf("Digite a celula que quer mudar: ");
    scanf("%[^\n]%*c",aux);
    printf("e o numero dela: ");
    scanf("%d%*c",&auxnum );

    get_from_id(celulas,lin,col,from_A1_to_Id(aux,col))->number = auxnum;
    
    print_celulas(celulas,lin,col);

    printf("Digite a celula que quer mudar: ");
    scanf("%[^\n]%*c",aux);
    printf("e o numero dela: ");
    scanf("%[^\n]%*c",auxform);

    bool erro;
    double valor;
    erro = add_formula(celulas,from_A1_to_Id(aux,col),auxform,col,lin,&valor);
    if(!erro) printf("Não foi possivel adicionar essa formula, verifique ela");

    get_from_id(celulas,lin,col,from_A1_to_Id(aux,col))->number = valor;

    print_celulas(celulas,lin,col);

    
    printf("Digite a celula que quer mudar: ");
    scanf("%[^\n]%*c",aux);
    printf("e o numero dela: ");
    scanf("%[^\n]%*c",auxform);

    erro = add_formula(celulas,from_A1_to_Id(aux,col),auxform,col,lin,&valor);
    if(!erro) printf("Não foi possivel adicionar essa formula, verifique ela");

    get_from_id(celulas,lin,col,from_A1_to_Id(aux,col))->number = valor;

    print_celulas(celulas,lin,col);


    // Liberação de memória (recomendado para evitar vazamento de memória)
    for (int i = 0; i < lin; i++) {
        free(celulas[i]);
    }
    free(celulas);

    return 0;
}