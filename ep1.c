#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*

#1� Exerc�cio-programa de Grafos#

#Prof. Glauber Cintra#

Integrantes do grupo:
- Elysson Gabriel Soares Sim�es
- Jo�o Marcus Maia Rocha
- Nivardo Albuquerque Leit�o de Castro
- Paulo Ricardo Bernardo Silva

*/

int numeroVertices, numeroArestas, origem, destino;
int **matrizAdjacenciaDirecialComCustos;
int *verticesOrigem, *verticesDestino, *custosArestas;
int i = 0;
char nome_do_arquivo[300];
FILE *arquivo;

void mostraResultado(
    double min,
    double custoAteVertice[numeroVertices],
    int origemDoVertice[numeroVertices])
{
    if (min == HUGE_VAL)
        printf("\nNão existe caminho entre os vértices %d e %d\n", origem, destino);
    else
    {
        printf("\nO caminho de custo mínimo entre os vértices %d e %d é:\n",
               origem, destino);
        i = destino;
        int buffer[numeroVertices];
        int index = 0;
        buffer[index++] = i;
        i = origemDoVertice[i - 1];
        while (i != -1)
        {
            buffer[index++] = i + 1;
            i = origemDoVertice[i];
        }

        for (i = index - 1; i >= 0; i--)
        {
            if (i)
                printf("%d --\'%d\'--> ", buffer[i], matrizAdjacenciaDirecialComCustos[buffer[i] - 1][buffer[i - 1] - 1]);
            else
                printf("%d", buffer[i]);
        }
        printf("\nO custo deste caminho é: %d\n", (int)custoAteVertice[destino - 1]);
    }
}

void dijkstra()
{
    int i, verticeAuxiliar, origemDoVertice[numeroVertices], visitados[numeroVertices];
    double valorMinimo, custoAteVertice[numeroVertices];

    // Inicializa o vetor de custoAteVertice e o vetor de origemDoVertice
    for (i = 0; i < numeroVertices; i++)
    {
        if (matrizAdjacenciaDirecialComCustos[origem - 1][i] != -1)
        {
            origemDoVertice[i] = origem - 1;
            custoAteVertice[i] = matrizAdjacenciaDirecialComCustos[origem - 1][i];
        }
        else
        {
            origemDoVertice[i] = -1;
            custoAteVertice[i] = HUGE_VAL;
        }
        visitados[i] = 0;
    }
    visitados[origem - 1] = 1;
    custoAteVertice[origem - 1] = 0;

    while (verticeAuxiliar != destino - 1 && valorMinimo != HUGE_VAL)
    {
        valorMinimo = HUGE_VAL;
        for (i = 0; i < numeroVertices; i++)
            if (!visitados[i])
                if (custoAteVertice[i] >= 0 && custoAteVertice[i] < valorMinimo)
                {
                    valorMinimo = custoAteVertice[i];
                    verticeAuxiliar = i;
                }

        if (valorMinimo != HUGE_VAL && verticeAuxiliar != destino - 1)
        {
            visitados[verticeAuxiliar] = 1;
            for (i = 0; i < numeroVertices; i++)
                if (!visitados[i])
                {
                    if (
                        matrizAdjacenciaDirecialComCustos[verticeAuxiliar][i] != -1 &&
                        (custoAteVertice[verticeAuxiliar] + matrizAdjacenciaDirecialComCustos[verticeAuxiliar][i]) < custoAteVertice[i])
                    {
                        custoAteVertice[i] = custoAteVertice[verticeAuxiliar] + matrizAdjacenciaDirecialComCustos[verticeAuxiliar][i];
                        origemDoVertice[i] = verticeAuxiliar;
                    }
                }
        }
    }

    mostraResultado(valorMinimo, custoAteVertice, origemDoVertice);
}

void inicializaVetoresAuxiliares()
{
    verticesOrigem = malloc(sizeof(int) * numeroArestas);
    verticesDestino = malloc(sizeof(int) * numeroArestas);
    custosArestas = malloc(sizeof(int) * numeroArestas);
}

void leCabecalhoDoArquivo()
{
    printf("Valores lidos no arquivo:\n");
    fscanf(arquivo, "%d %d %d %d\n", &numeroVertices, &numeroArestas, &origem, &destino);
    printf("%d %d %d %d\n", numeroVertices, numeroArestas, origem, destino);
}

void criaMatrizAdjacenciaDirecionalComCusto()
{
    matrizAdjacenciaDirecialComCustos = (int **)malloc(sizeof(int *) * numeroVertices);
    for (i = 0; i < numeroVertices; i++)
    {
        matrizAdjacenciaDirecialComCustos[i] = malloc(sizeof(int) * numeroVertices);
    }
    for (i = 0; i < numeroVertices; i++)
    {
        for (int j = 0; j < numeroVertices; j++)
        {
            matrizAdjacenciaDirecialComCustos[i][j] = -1;
        }
    }
}

void leCadaArestaDoArquivo()
{
    while ((fscanf(arquivo, "%d %d %d\n", &verticesOrigem[i], &verticesDestino[i], &custosArestas[i])) != EOF)
    {
        printf("%d %d %d\n", verticesOrigem[i], verticesDestino[i], custosArestas[i]);
        matrizAdjacenciaDirecialComCustos[verticesOrigem[i] - 1][verticesDestino[i] - 1] = custosArestas[i];
    }
}

void leArquivo(char *argv[])
{
    strcpy(nome_do_arquivo, argv[1]);
    arquivo = fopen(nome_do_arquivo, "r");

    if (arquivo != NULL)
    {
        leCabecalhoDoArquivo();
        inicializaVetoresAuxiliares();
        criaMatrizAdjacenciaDirecionalComCusto();
        leCadaArestaDoArquivo();
    }
    else
    {
        printf("Erro na leitura do arquivo!\n");
    }
    fclose(arquivo);
    return;
}

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        leArquivo(argv);
        dijkstra();
        return 0;
    }
    else
    {
        printf("Você precisa digitar o nome do arquivo ao executar!\n");
        return 1;
    }
}
