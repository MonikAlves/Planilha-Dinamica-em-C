#include <stdio.h>
#include "stdbool.h"
#include "calculadora.h"
#include "expressao.h"
#include "grafo.h"

char ** scan_celulas(int tipo,int * tamanho,int size[]){
    if(tipo == 0){
        *tamanho = 1;
        char * aux = (char*) malloc(10000* sizeof(char));

        printf("Digite a celula que deseja mudar: ");
        scanf("%[^\n]%*c",aux);
        
        char ** A1 = (char **) malloc((*tamanho) * sizeof(char*));
        A1[0] = (char*) malloc(strlen(aux) * sizeof(char));

        strcpy(A1[0],aux);
        free(aux);
        return A1;
    }
    if(tipo == 1){
        char *intervalo = (char *) malloc(10000 * sizeof(char)); // Aloca espaço para o intervalo

        printf("Digite o intervalo de células (ex: A1:A5): ");
        scanf("%[^\n]%*c", intervalo); // Lê o intervalo

        // Divide o intervalo em duas partes: início e fim
        char *token = strtok(intervalo, ":"); // Obtém a primeira parte
        char *inicio = strdup(token); // Armazena a célula inicial
        token = strtok(NULL, ":"); // Obtém a segunda parte
        char *fim = strdup(token); // Armazena a célula final

        // Converte as células inicial e final para IDs
        int id_inicio = from_A1_to_Id(inicio, size[1]);
        int id_fim = from_A1_to_Id(fim, size[1]);
        if(id_inicio%size[1] != id_fim%size[1]) {
            printf("Só é permitido células com a mesma coluna");
            return NULL;
        }
        int columnNumber = id_inicio % size[1]; // size[1] é o número de colunas
        int temp = columnNumber + 1; // Ajusta para o formato 1-base
        char columnName[10];
        int index = 0;

        // Converte o número da coluna para a letra correspondente
        while (temp > 0) {
            temp -= 1;
            columnName[index++] = ('A') + (temp % 26);
            temp /= 26;
        }

        // Reverte a string para obter a ordem correta
        for (int j = 0; j < index / 2; j++) {
            char tempChar = columnName[j];
            columnName[j] = columnName[index - j - 1];
            columnName[index - j - 1] = tempChar;
        }

        columnName[index] = '\0'; // Finaliza a string


        // Valida se os IDs estão dentro dos limites da planilha
        if (id_inicio == -1 || id_fim == -1 || id_inicio > id_fim) {
            printf("Intervalo inválido!\n");
            free(inicio);
            free(fim);
            free(intervalo);
            return NULL; // Retorna NULL em caso de erro
        }
         // Converte a parte numérica da célula final

        // Calcula a quantidade de células entre as linhas
        *tamanho = atoi(&fim[1]) - atoi(&inicio[1]) + 1;

    // Adiciona o loop para popular as células no vetor A1
        char ** A1 = (char **) malloc((*tamanho) * sizeof(char*));
        for (int i = 0; i < *tamanho; i++) {
            A1[i] = (char *) malloc(3 * sizeof(char)); // Aloca espaço para a célula (ex: "A1")
            sprintf(A1[i], "%s%d",columnName, atoi(&inicio[1]) + i); // Constrói a célula (ex: "A1", "A2", ...)
        }

        // Libera a memória alocada
        free(inicio);
        free(fim);
        free(intervalo);
        return A1;// Retorna os IDs das células
    }
    return NULL;    
}

bool numero(Vertice ** planilha,int size[], int tipo){
    double number;
    bool erro;
    int tamanho;

    char ** A1 = scan_celulas(tipo,&tamanho,size);
     if (A1 == NULL) {
            printf("Erro ao realizar operação: \n");
            return false;
        }
    if(tipo) printf("Digite o numero para elas: ");
    else printf("Digite o numero para ela: ");

    scanf("%lf%*c",&number);

    for(int i = 0;i<tamanho;i++){
        Vertice * atual = get_from_id(planilha,size,from_A1_to_Id(A1[i],size[1]));
         if (atual == NULL) {
            printf("Célula não encontrada com id: %d\n",A1[i]);
            
            return false;
        }

        erro = mudar_valor(planilha,atual,size,number);
        
        if(!erro) printf("Não foi possivel adicionar esse valor, verifique ele");
    }

    for (int i = 0; i < tamanho; i++) {
        free(A1[i]);
    }
    free(A1); 

    return true;

}

bool texto(Vertice ** planilha,int size[], int tipo){
    int tamanho;

    char ** A1 = scan_celulas(tipo,&tamanho,size);
     if (A1 == NULL) {
            printf("Erro ao realizar operação: \n");
            return false;
        }
    if(tipo) printf("Digite o texto para elas: ");
    else printf("Digite a texto para ela: ");

    char * aux = (char*) malloc(10000* sizeof(char));
    
    scanf("%[^\n]%*c",aux);
        
    char * texto = (char *) malloc((strlen(aux)+1) * sizeof(char));

    strcpy(texto,aux);
    free(aux);

    for(int i = 0;i<tamanho;i++){
        Vertice * atual = get_from_id(planilha,size,from_A1_to_Id(A1[i],size[1]));
         if (atual == NULL) {
            printf("Célula não encontrada com id: %d\n",A1[i]);
            free(A1); 
            return false;
        }

        atual->formula = (char*) malloc((strlen(texto) + 1)* sizeof(char));  // Aloca espaço para a fórmula
        strcpy(atual->formula, texto);
        atual->isText = true;
        
    }


    free(texto);
    for (int i = 0; i < tamanho; i++) {
        free(A1[i]);
    }
    free(A1); 

    return true;


}

bool formula(Vertice ** planilha,int size[], int tipo){
    bool erro;
    int tamanho;

    char ** A1 = scan_celulas(tipo,&tamanho,size);
     if (A1 == NULL) {
            printf("Erro ao realizar operação: \n");
            return false;
        }
    if(tipo) printf("Digite a formula para elas: ");
    else printf("Digite a formula para ela: ");

    char * aux = (char*) malloc(10000* sizeof(char));
    
    scanf("%[^\n]%*c",aux);
        
    char * formula = (char *) malloc(strlen(aux) * sizeof(char));

    strcpy(formula,aux);
    free(aux);

    for(int i = 0;i<tamanho;i++){
        int id_atual = from_A1_to_Id(A1[i],size[1]);

        erro = add_formula(planilha,id_atual,formula,size);
        
        if(!erro) printf("Não foi possivel adicionar esse valor, verifique ele");
    }

    for (int i = 0; i < tamanho; i++) {
        free(A1[i]);
    }
    free(A1); 

    return true;
}

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
            celulas[i][j].formula = NULL;
        }
    }

    
    numero(celulas,size,0);

    print_celulas(celulas,size);

    formula(celulas,size,1);

    print_celulas(celulas,size);

    texto(celulas,size,1);

    print_celulas(celulas,size);


    // erro = mudar_valor(celulas,get_from_id(celulas,size,from_A1_to_Id(aux,size[1])),size,auxnum);
    
    // if(!erro) printf("Não foi possivel adicionar essa formula, verifique ela");
    
    // print_celulas(celulas,size);

    // printf("Digite a celula que quer mudar: ");
    // scanf("%[^\n]%*c",aux);
    // printf("e a formula dela: ");
    // scanf("%[^\n]%*c",auxform);


    // erro = add_formula(celulas,from_A1_to_Id(aux,size[1]),auxform,size);
    // if(!erro) printf("Não foi possivel adicionar essa formula, verifique ela");

    // print_celulas(celulas,size);

    // // printf("Digite a celula que quer mudar: ");
    // // scanf("%[^\n]%*c",aux);
    // // printf("e o texto dela: ");
    // // scanf("%[^\n]%*c",auxform);
    // // get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->formula = auxform;
    // // get_from_id(celulas,size,from_A1_to_Id(aux,size[1]))->isText = true;
    

    // // print_celulas(celulas,size);


    // printf("Digite a celula que quer mudar: ");
    // scanf("%[^\n]%*c",aux);
    // printf("e o numero dela: ");
    // scanf("%d%*c",&auxnum );

    // Vertice *celula_atual = get_from_id(celulas, size, from_A1_to_Id(aux, size[1]));
    // if (celula_atual == NULL) {
    //     printf("Erro: Célula não encontrada\n");
    //     return -1;
    // }


    // erro = mudar_valor(celulas,celula_atual,size,auxnum);
    // if(!erro) printf("Não foi possivel adicionar essa formula, verifique ela");

    //    print_celulas(celulas,size);
    
    // Liberação de memória (recomendado para evitar vazamento de memória)
    for (int i = 0; i < size[0]; i++) {
        free(celulas[i]);
    }
    free(celulas);

    return 0;
}