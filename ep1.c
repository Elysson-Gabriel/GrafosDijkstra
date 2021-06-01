#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*

#1º Exercício-programa de Grafos#

#Prof. Glauber Cintra#

Integrantes do grupo:
- Elysson Gabriel Soares Simões
- João Marcus Maia Rocha
- Nivardo Albuquerque Leitão de Castro
- Paulo Ricardo Bernardo Silva

*/

// Globais
int numeroVertices, numeroArestas, origem, destino;
int **matrizAdjacenciaDirecionalComCustos;
int *verticesOrigem, *verticesDestino, *custosArestas;
int i = 0;
char nome_do_arquivo[300];
FILE *arquivo;

// Protótipos
void mostraResultado(double min,double custoAteVertice[numeroVertices],int origemDoVertice[numeroVertices]);
void dijkstra();
void inicializaVetoresAuxiliares();
void leCabecalhoDoArquivo();
void criaMatrizAdjacenciaDirecionalComCusto();
void leCadaArestaDoArquivo();
void desalocarMatriz();
int main(int argc, char *argv[]);


void mostraResultado(
    double min,
    double custoAteVertice[numeroVertices],
    int origemDoVertice[numeroVertices])
{
    if (min == HUGE_VAL)
        printf("\nInexiste um caminho entre os vertices %d e %d\n", origem, destino);
    else
    {
        printf("Caminho minimo do vertice %d para o vertice %d:",
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

        for (i = index - 1; i > 0; i--)
        {
            printf(" (%d,  %d)", buffer[i], buffer[i-1]);
        }
        printf("\nCusto: %d\n", (int)custoAteVertice[destino - 1]);
    }
} /* fim mostraResultado */

void dijkstra()
{
    int i, verticeAuxiliar, origemDoVertice[numeroVertices], visitados[numeroVertices];
    double valorMinimo, custoAteVertice[numeroVertices];

    // Inicializa o vetor de custoAteVertice e o vetor de origemDoVertice
    for (i = 0; i < numeroVertices; i++)
    {
        if (matrizAdjacenciaDirecionalComCustos[origem - 1][i] != -1)
        {
            origemDoVertice[i] = origem - 1;
            custoAteVertice[i] = matrizAdjacenciaDirecionalComCustos[origem - 1][i];
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
                        matrizAdjacenciaDirecionalComCustos[verticeAuxiliar][i] != -1 &&
                        (custoAteVertice[verticeAuxiliar] + matrizAdjacenciaDirecionalComCustos[verticeAuxiliar][i]) < custoAteVertice[i])
                    {
                        custoAteVertice[i] = custoAteVertice[verticeAuxiliar] + matrizAdjacenciaDirecionalComCustos[verticeAuxiliar][i];
                        origemDoVertice[i] = verticeAuxiliar;
                    }
                }
        }
    }

    mostraResultado(valorMinimo, custoAteVertice, origemDoVertice);
} /* fim Dijkstra */

void inicializaVetoresAuxiliares()
{
    verticesOrigem = malloc(sizeof(int) * numeroArestas);
    verticesDestino = malloc(sizeof(int) * numeroArestas);
    custosArestas = malloc(sizeof(int) * numeroArestas);
} /* fim inicializaVetoresAuxiliares */

void leCabecalhoDoArquivo()
{
    fscanf(arquivo, "%d %d %d %d\n", &numeroVertices, &numeroArestas, &origem, &destino);
} /* fim leCabecalhoDoArquivo */

void criaMatrizAdjacenciaDirecionalComCusto()
{
    matrizAdjacenciaDirecionalComCustos = (int **)malloc(sizeof(int *) * numeroVertices);
    for (i = 0; i < numeroVertices; i++)
    {
        matrizAdjacenciaDirecionalComCustos[i] = malloc(sizeof(int) * numeroVertices);
    }
    for (i = 0; i < numeroVertices; i++)
    {
        for (int j = 0; j < numeroVertices; j++)
        {
            matrizAdjacenciaDirecionalComCustos[i][j] = -1;
        }
    }
} /* fim criaMatrizAdjacenciaDirecionalComCusto */

void leCadaArestaDoArquivo()
{
    while ((fscanf(arquivo, "%d %d %d\n", &verticesOrigem[i], &verticesDestino[i], &custosArestas[i])) != EOF)
    {
        matrizAdjacenciaDirecionalComCustos[verticesOrigem[i] - 1][verticesDestino[i] - 1] = custosArestas[i];
    }
} /* fim leCadaArestaDoArquivo */

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
    { /* Mostra mensagem para o usuário caso ocorra algum
        problema durante a leitura do arquivo */
        printf("Erro na leitura do arquivo!\n");
    }
    fclose(arquivo);
    return;
} /* fim leArquivo */


void desalocarMatriz(){
	for (i = 0; i < numeroVertices; i++)
	{
		free(matrizAdjacenciaDirecionalComCustos[i]);
	}
	free(matrizAdjacenciaDirecionalComCustos);

}/* fim desalocarMatriz */

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        leArquivo(argv);
        dijkstra();
        desalocarMatriz();
        return 0;
    }
    else
    { /* Mostra mensagem para o usuário se o programa por executado
        sem o arquivo contendo o digrafo */
        printf("Digite o nome do arquivo ao executar!\n");
        return 1;
    }
} /* fim main */
