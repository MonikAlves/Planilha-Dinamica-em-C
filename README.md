# Planilha - Projeto de Manipulação de Dados

## Descrição

Este projeto implementa uma planilha simples em C, permitindo que os usuários armazenem e manipulem dados em células, incluindo números e textos. A planilha suporta operações básicas como a atualização de valores em células e a reavaliação automática de fórmulas quando uma célula é alterada.

## Funcionalidades

- **Armazenamento de Dados**: Cada célula pode conter um número (double) ou texto.
- **Atualização de Valores**: Os usuários podem alterar o valor de uma célula, o que pode afetar outras células que dependem desse valor.
- **Reavaliação de Fórmulas**: Sempre que uma célula com uma fórmula é atualizada, as células que utilizam essa fórmula são automaticamente recalculadas.
- **Manipulação de Textos**: A planilha permite que os usuários insiram textos, mas alterações em textos não acionam a reavaliação de fórmulas.

## Estrutura do Projeto

- **main.c**: Arquivo principal do programa que gerencia a interação do usuário e a manipulação de dados na planilha.
- **bibliotecas/**: Diretório contendo funções auxiliares para manipulação das células e fórmulas.
- **Vertice.h**: Cabeçalho que define a estrutura das células e as funções utilizadas para manipulação.

## Como Compilar

Para compilar o programa, utilize o comando abaixo:

```bash
gcc main.c bibliotecas/*.c -I"bibliotecas" -o Planilha
```
## Como Executar
Após a compilação, o arquivo executável será gerado com o nome Planilha. Para rodar o programa, execute o comando abaixo:

```bash
./Estenografia
```
