#include <stdio.h>
#include "stdbool.h"
#include "calculadora.h"
#include "expressao.h"
#include "grafo.h"
#include "planilha.h"


// Funções placeholders para cada operação
void adicionar_valor_1_celula(Vertice ** planilha,int * size,int tipo) {
    printf("Adicionando um valor a uma única célula...\n");
    numero(planilha,size,tipo);
    print_celulas(planilha,size);

}

void adicionar_valor_varias_celulas(Vertice ** planilha,int * size,int tipo) {
    printf("Adicionando um valor a várias células...\n");
    numero(planilha,size,tipo);
    print_celulas(planilha,size);
}

void adicionar_formula_1_celula(Vertice ** planilha,int * size,int tipo) {
    printf("Adicionando uma fórmula a uma única célula...\n");
    formula(planilha,size,tipo);
    print_celulas(planilha,size);
}

void adicionar_formula_varias_celulas(Vertice ** planilha,int * size,int tipo) {
    printf("Adicionando uma fórmula a várias células...\n");
    formula(planilha,size,tipo);
    print_celulas(planilha,size);
}

void adicionar_formula_dinamica_varias_celulas(Vertice ** planilha,int * size,int tipo) {
    printf("Adicionando uma fórmula dinâmica a várias células...\n");
    formula(planilha,size,tipo);
    print_celulas(planilha,size);
}

void adicionar_texto_1_celula(Vertice ** planilha,int * size,int tipo) {
    printf("Adicionando um texto a uma única célula...\n");
    texto(planilha,size,tipo,' ');
    print_celulas(planilha,size);
}

void adicionar_texto_varias_celulas(Vertice ** planilha,int * size,int tipo) {
    printf("Adicionando um texto a várias células...\n");
    texto(planilha,size,tipo,' ');
    print_celulas(planilha,size);
}

void adicionar_texto_no_lugar_de_valores(Vertice ** planilha,int * size,int tipo) {
    char comparação;
    if(tipo == 1) comparação = '=';
    if(tipo == 2) comparação = '<';
    if(tipo == 3) comparação = '>';
    printf("Substituindo valores específicos por texto...\n");
    texto(planilha,size,3,comparação);
    print_celulas(planilha,size);
}

void exibirMenu() {
    printf("====================================\n");
    printf("=         Menu Principal           =\n");
    printf("====================================\n");
    printf("= 1 - Adicionar um Valor           =\n");
    printf("= 2 - Adicionar uma Fórmula        =\n");
    printf("= 3 - Adicionar um Texto           =\n");
    printf("= 4 - Ver as Fórmulas              =\n");
    printf("= 5 - Encerrar                     =\n");
    printf("====================================\n");
}

void exibirSubMenuValores() {
    printf("==================================================\n");
    printf("=                 Adicionar Valor                =\n");
    printf("==================================================\n");
    printf("= 1 - Inserir um valor a uma única célula        =\n");
    printf("= 2 - Inserir um valor a várias células          =\n");
    printf("= 3 - Inserir vários diferentes a várias células =\n");
    printf("==================================================\n");
}

void exibirSubMenuFormulas() {
    printf("=====================================================\n");
    printf("=                 Adicionar Fórmula                 =\n");
    printf("=====================================================\n");
    printf("= 1 - Inserir uma fórmula a uma única célula        =\n");
    printf("= 2 - Inserir uma fórmula a várias células          =\n");
    printf("= 3 - Inserir uma fórmula dinâmica a várias células =\n");
    printf("=======================================================\n");
}

void exibirSubMenuTextos() {
    printf("================================================\n");
    printf("=                Adicionar Texto               =\n");
    printf("================================================\n");
    printf("= 1 - Inserir um texto a uma única célula      =\n");
    printf("= 2 - Inserir um texto a várias células        =\n");
    printf("= 3 - Substituir valores específicos por texto =\n");
    printf("================================================\n");
}

void exibirSubSubstituir() {
    printf("=========================================================\n");
    printf("=                  Substituir por Texto                  =\n");
    printf("==========================================================\n");
    printf("= 1 - Substituir valores iguais (ex: A1 = 1)             =\n");
    printf("= 2 - Substituir valores menores (ex: A1 < 1)            =\n");
    printf("= 3 - Substituir valores menores ou igual (ex: A1 <= 1)  =\n");
    printf("==========================================================\n");
}

int main() {
    int opcao1, opcao2,opcao3;
    bool encerrado = false;
    Vertice ** planilha;
    int size[2];
    bool erro;
    printf("Para começar diga as dimensões da sua planilha (ex 5 5):\n>> ");
    scanf("%d %d%*c",&size[0],&size[1]);

    planilha = (Vertice**) malloc(size[0]*sizeof(Vertice*));
    for(int i =0;i<size[0];i++){
        planilha[i] = (Vertice*) malloc(size[1]*sizeof(Vertice));
    }

    for(int i =0;i<size[0];i++){
        for(int j=0;j<size[1];j++){
            planilha[i][j].id =  coordenada_para_id(i,j,size[1]);
            planilha[i][j].adj = NULL;
            planilha[i][j].numeroAdj = 0; 
            planilha[i][j].isText = false;
            planilha[i][j].formula = NULL;
        }
    }

    while (!encerrado) {
        //limparterminal();
        exibirMenu();
        print_celulas(planilha,size);
        printf("Escolha uma opção: ");
        scanf("%d%*c", &opcao1);
        
        switch (opcao1) {
            case 1:
                //VALORES
                //limparterminal();
                exibirSubMenuValores();
                print_celulas(planilha,size);
                printf("Escolha uma opção: ");
                scanf("%d%*c", &opcao2);
                if (opcao2 == 1)adicionar_valor_1_celula(planilha,size,0);
                else if (opcao2 == 2) adicionar_valor_1_celula(planilha,size,1);
                else if (opcao2 == 3) adicionar_valor_varias_celulas(planilha,size,2);
                else printf("Opção inválida! Tente novamente.\n");
                break;

            case 2:
                // FORMULA
                //limparterminal();
                exibirSubMenuFormulas();
                print_celulas(planilha,size);
                printf("Escolha uma opção: ");
                scanf("%d%*c", &opcao2);
                if (opcao2 == 1) adicionar_formula_1_celula(planilha,size,(opcao2-1));
                else if (opcao2 == 2) adicionar_formula_varias_celulas(planilha,size,(opcao2-1));
                else if (opcao2 == 3) adicionar_formula_dinamica_varias_celulas(planilha,size,(opcao2-1));
                else printf("Opção inválida! Tente novamente.\n");
                break;

            case 3:
                // TEXTO
                //limparterminal();
                exibirSubMenuTextos();
                print_celulas(planilha,size);
                printf("Escolha uma opção: ");
                scanf("%d%*c", &opcao2);
                if (opcao2 == 1) adicionar_texto_1_celula(planilha,size,(opcao2-1));
                else if (opcao2 == 2) adicionar_texto_varias_celulas(planilha,size,(opcao2-1));
                else if (opcao2 == 3){
                    //limparterminal();
                    exibirSubSubstituir();
                    print_celulas(planilha,size);
                    printf("Escolha uma opção: ");
                    scanf("%d%*c", &opcao3);
                    adicionar_texto_no_lugar_de_valores(planilha,size,opcao3);
                } 
                else printf("Opção inválida! Tente novamente.\n");
                break;

            case 4:
                //limparterminal();
                exibirSubMenuTextos();
                print_formulas(planilha,size);
                printf("Digite qualquer numero para voltar ao menu: ");
                scanf("%d%*c", &opcao2);
                if (opcao2) break;
                else break;
                break;

            case 5:
                printf("Encerrando o programa. Até logo!\n");
                encerrado = true;
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    for (int i = 0; i < size[0]; i++) {
        free(planilha[i]);
    }
    free(planilha);
    return 0;
}
