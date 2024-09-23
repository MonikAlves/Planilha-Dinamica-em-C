# Sistema de Planilha Dinâmica

[Descrição](#descrição) | [Substituição de Valores por Texto](#substituição-de-valores-por-texto) | [Fórmulas Dinâmicas](#fórmulas-dinâmicas) | [Suporte a Notação Normal e Pós-Fixada](#suporte-a-notação-normal-e-pós-fixada) | [Exemplo de Planilha](#exemplo-de-planilha-notatxt) | [Atualização de Valores](#atualização-de-valores) | [Limitações](#limitações) | [Instruções para Uso](#instruções-para-uso) | [Como Compilar](#como-compilar) | [Como Executar](#como-executar)


## Descrição
Este sistema de planilha permite trabalhar com células contendo valores numéricos e textos, além de suportar a manipulação dinâmica de fórmulas. Ele foi desenvolvido para facilitar a organização de dados e o cálculo automático, com suporte para [notação polonesa reversa](https://github.com/MonikAlves/Calculadora-Pos-Fixada) (RPN) e notação normal, que é convertida internamente.

## Funcionalidades

### Substituição de Valores por Texto
O sistema permite substituir certos valores numéricos por textos personalizados, facilitando a interpretação dos dados na planilha. Isso é útil em contextos onde uma célula pode conter informações mais descritivas, como status de aprovação ou reprovação.

### Fórmulas Dinâmicas
As fórmulas são atualizadas automaticamente sempre que uma célula envolvida tem seu valor alterado. Isso elimina a necessidade de recalcular manualmente as fórmulas e garante que as planilhas estejam sempre atualizadas com as últimas informações.

### Suporte a Notação Normal e Pós-Fixada
As fórmulas podem ser inseridas tanto em notação polonesa reversa (RPN) quanto em notação normal. O sistema faz a conversão interna, aceitando ambas as formas de inserção para maior flexibilidade.

### Exemplo de Planilha: `nota.txt`
O arquivo `nota.txt` é fornecido como um exemplo prático. Ao colá-lo no terminal, ele mostra um protótipo de planilha contendo valores de notas de alunos. Esta planilha demonstra o uso das fórmulas e a manipulação de dados dentro do sistema, ajudando a entender como ele funciona.

## Atualização de Valores

Quando um valor é alterado:
1. **Identificação da Célula**: O usuário especifica qual célula deseja alterar.
2. **Verificação de Dependências**: Se a célula contém uma fórmula, a função `atualizar_formulas` é chamada.
3. **Recalculo**: As fórmulas associadas são recalculadas automaticamente.

## Limitações

- Textos não acionam a reavaliação de fórmulas quando são alterados. Se um texto é modificado por um valor, as fórmulas relacionadas a essa célula não são afetadas.
- Somente valores numéricos podem ser utilizados em cálculos.

## Instruções para Uso

1. **Compilação**: Compile o código-fonte usando um compilador C padrão.
2. **Execução**: Execute o programa e siga as instruções no console para inserir e alterar valores nas células.
3. **Inserção de Fórmulas**: Insira fórmulas em células que se referenciam a outras células. Exemplo: `(A1 + B1)/2` para a media dos valores das células A1 e B1.


## Como Compilar

Para compilar o programa, utilize o comando abaixo:

```bash
gcc main.c bibliotecas/*.c -I"bibliotecas" -o Planilha
```
## Como Executar
Após a compilação, o arquivo executável será gerado com o nome Planilha. Para rodar o programa, execute o comando abaixo:

```bash
./Planilha
```
