#include <stdio.h>
#include "stdbool.h"
#include "calculadora.h"
#include "expressao.h"
#include "grafo.h"

void limparterminal(){
	#ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Linux e macOS
    #endif
}

char ** varias_celulas(char * intervalo,int size[],int *tamanho,int tipo){
        int col = size[1];
        char *token = strtok(intervalo, ":"); 
        char *inicio = strdup(token); 
        token = strtok(NULL, ":"); 
        char *fim = strdup(token);

        int id_inicio = from_A1_to_Id(inicio, size[1],0);
        int id_fim = from_A1_to_Id(fim, size[1],0);
        if(id_inicio%size[1] != id_fim%size[1]) {
            printf("Só é permitido células com a mesma coluna");
            return NULL;
        }
        int columnNumber = id_inicio % size[1]; 
        int temp = columnNumber + 1;
        char columnName[10];
        int index = 0;

        while (temp > 0) {
            temp -= 1;
            columnName[index++] = ('A') + (temp % 26);
            temp /= 26;
        }

        for (int j = 0; j < index / 2; j++) {
            char tempChar = columnName[j];
            columnName[j] = columnName[index - j - 1];
            columnName[index - j - 1] = tempChar;
        }

        columnName[index] = '\0'; 
        if (id_inicio == -1 || id_fim == -1 || id_inicio > id_fim) {
            printf("Intervalo inválido!\n");
            free(inicio);
            free(fim);
            free(intervalo);
            return NULL;
        }

        *tamanho = atoi(&fim[1]) - atoi(&inicio[1]) + 1;

        char ** A1 = (char **) malloc((*tamanho) * sizeof(char*));
        for (int i = 0; i < *tamanho; i++) {
            A1[i] = (char *) malloc(3 * sizeof(char)); 
            sprintf(A1[i], "%s%d",columnName, atoi(&inicio[1]) + i);
        }

        free(inicio);
        free(fim);
        return A1;
    
}

char ** scan_celulas(int tipo,int * tamanho,int size[]){
    if(tipo == 0){
        *tamanho = 1;
        char * aux = (char*) malloc(10000* sizeof(char));

        printf("\nDigite a celula que deseja mudar: ");
        scanf("%[^\n]%*c",aux);
        
        char ** A1 = (char **) malloc((*tamanho) * sizeof(char*));
        A1[0] = (char*) malloc((strlen(aux)+1) * sizeof(char));

        strcpy(A1[0],aux);
        free(aux);

        return A1;
    }

    if(tipo == 1 || tipo == 2){
        char *intervalo = (char *) malloc(10000 * sizeof(char)); // Aloca espaço para o intervalo

        printf("\nDigite o intervalo de células (ex: A1:A5): ");
        scanf("%[^\n]%*c", intervalo); // Lê o intervalo

        char ** A1 = varias_celulas(intervalo,size,tamanho,tipo);

        free(intervalo);

        return A1;
    }

    if(tipo == 3){

        char *intervalo = (char *) malloc(10000 * sizeof(char)); // Aloca espaço para o intervalo

        printf("\nDigite as células que serão comparadas (ex: A1:A5): ");
        scanf("%[^\n]%*c", intervalo); 
        // Lê o intervalo

        char ** A1 = varias_celulas(intervalo,size,tamanho,tipo);

        free(intervalo);

        return A1;
        
    }

    return NULL;    
}

bool numero(Vertice ** planilha,int size[], int tipo){
    double * number;
    bool erro;
    int tamanho;
    char ** A1 = scan_celulas(tipo,&tamanho,size);
     if (A1 == NULL) {
            printf("Erro ao realizar operação: \n");
            return false;
    }

    if(tipo) printf("\nDigite o numero para elas: \n");
    else printf("\nDigite o numero para ela: \n");

    if(tipo != 1){
        number = (double*) malloc(tamanho * sizeof(double));
        for(int i = 0; i<tamanho;i++){
            printf("\nDigite o valor para %s: ",A1[i]);
            scanf("%lf%*c",&number[i]);
        } 
    }else{
        number = (double*) malloc(tamanho * sizeof(double));
        printf("\nDigite o valor para %s ate %s: ",A1[0],A1[tamanho-1]);
        scanf("%lf%*c",&number[0]);
        for(int i = 1; i<tamanho;i++){
            number[i] = number[0];
        } 
    }    

    for(int i = 0;i<tamanho;i++){
        Vertice * atual = get_from_id(planilha,size,from_A1_to_Id(A1[i],size[1],0));
         if (atual == NULL) {
            printf("Célula não encontrada com id: %d\n",A1[i]);
            
            return false;
        }

        erro = mudar_valor(planilha,atual,size,number[i]);
        
        if(!erro) printf("Não foi possivel adicionar esse valor, verifique ele");
    }

    for (int i = 0; i < tamanho; i++) {
        free(A1[i]);
    }
    free(A1); 

    return true;

}

bool texto(Vertice ** planilha,int size[], int tipo,char comparacao){
    int tamanho;

    char ** A1 = scan_celulas(tipo,&tamanho,size);
     if (A1 == NULL) {
            printf("Erro ao realizar operação: \n");
            return false;
    }
    if(tipo == 3){
        double numero;
        printf("\nDigite o numero a ser comparado: ");
        scanf("%lf%*c", &numero);
        printf("\nDigite o texto para por quando verdadeiro: ");
        char * aux = (char*) malloc(10000* sizeof(char));
    
        scanf("%[^\n]%*c",aux);
            
        char * verdadeiro = (char *) malloc((strlen(aux)+1) * sizeof(char));

        strcpy(verdadeiro,aux);
        free(aux);
        printf("\nDigite o texto para por quando falso: ");
        aux = (char*) malloc(10000* sizeof(char));
    
        scanf("%[^\n]%*c",aux);
            
        char * falso = (char *) malloc((strlen(aux)+1) * sizeof(char));

        strcpy(falso,aux);
        free(aux);

        for(int i = 0;i<tamanho;i++){
            Vertice * atual = get_from_id(planilha,size,from_A1_to_Id(A1[i],size[1],0));
            if (atual == NULL) {
                printf("Célula não encontrada com id: %d\n",A1[i]);
                free(A1); 
                return false;
            }
            if(comparacao == '='){
                if(atual->number == numero){
                    atual->formula = (char*) malloc((strlen(verdadeiro) + 1)* sizeof(char));  // Aloca espaço para a fórmula
                    strcpy(atual->formula, verdadeiro);
                } 
                else{
                    atual->formula = (char*) malloc((strlen(falso) + 1)* sizeof(char));
                    strcpy(atual->formula, falso);
                } 
            }
            if(comparacao == '<'){
                    if(atual->number < numero){
                    atual->formula = (char*) malloc((strlen(verdadeiro) + 1)* sizeof(char));  // Aloca espaço para a fórmula
                    strcpy(atual->formula, verdadeiro);
                } 
                else{
                    atual->formula = (char*) malloc((strlen(falso) + 1)* sizeof(char));
                    strcpy(atual->formula, falso);
                } 
            }
            if(comparacao == '>'){
                    if(atual->number <= numero){
                    atual->formula = (char*) malloc((strlen(verdadeiro) + 1)* sizeof(char));  // Aloca espaço para a fórmula
                    strcpy(atual->formula, verdadeiro);
                } 
                else{
                    atual->formula = (char*) malloc((strlen(falso) + 1)* sizeof(char));
                    strcpy(atual->formula, falso);
                } 
            }

            atual->isText = true;
            
        }

        free(verdadeiro);
        free(falso);

    }else{

        if(tipo == 1) printf("\nDigite o texto para elas: ");
        else printf("\nDigite o texto para ela: ");

        char * aux = (char*) malloc(10000* sizeof(char));
        
        scanf("%[^\n]%*c",aux);
            
        char * texto = (char *) malloc((strlen(aux)+1) * sizeof(char));

        strcpy(texto,aux);
        free(aux);

        for(int i = 0;i<tamanho;i++){
            Vertice * atual = get_from_id(planilha,size,from_A1_to_Id(A1[i],size[1],0));
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

    }


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
    if(tipo) printf("\nDigite a formula para elas: ");
    else printf("\nDigite a formula para ela: ");

    char * aux = (char*) malloc(10000* sizeof(char));
    
    scanf("%[^\n]%*c",aux);
        
    char * formula = (char *) malloc((strlen(aux)+1) * sizeof(char));

    strcpy(formula,aux);
    free(aux);

    for(int i = 0;i<tamanho;i++){
        int id_atual = from_A1_to_Id(A1[i],size[1],0);
        add_formula(planilha,id_atual,formula,size,i);
        
        if(!erro) printf("Não foi possivel adicionar esse valor, verifique ele");
    }

    for (int i = 0; i < tamanho; i++) {
        free(A1[i]);
    }
    free(A1); 

    return true;
}