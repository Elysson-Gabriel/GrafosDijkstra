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

int quantidade_de_vertices, quantidade_de_arcos, vertice_origem, vertice_destino;
int *vertice_origem_i, *vertice_destino_i, *custo_i;
int i = 0;
char nome_do_arquivo[300];
FILE *arquivo;

// Algoritmo de Dijkstra
void dijkstra(int matriz_grafo)
{
    
}

// Caminho mínimo do vértice 1 para o vértice 4: (1, 2) (2, 5) (5, 4)
// Custo: 13
int main()
{
    strcpy(nome_do_arquivo, "digrafo.txt");
    arquivo = fopen(nome_do_arquivo, "r");

    if (arquivo != NULL)
    {
        fscanf(arquivo, "%d %d %d %d\n", &quantidade_de_vertices, &quantidade_de_arcos, &vertice_origem, &vertice_destino);
        printf("%d %d %d %d\n", quantidade_de_vertices, quantidade_de_arcos, vertice_origem, vertice_destino);

        vertice_origem_i = malloc(sizeof(int) * quantidade_de_arcos);
        vertice_destino_i = malloc(sizeof(int) * quantidade_de_arcos);
        custo_i = malloc(sizeof(int) * quantidade_de_arcos);

        // Matriz de adjacência do grafo
        int matriz_grafo[quantidade_de_vertices][quantidade_de_vertices];

        // Poupulando a matriz de adjacência do grafo
        for (int i = 0; i < quantidade_de_vertices; i++)
            for (int j = 0; j < quantidade_de_vertices; j++)
                matriz_grafo[i][j] = -1;

        while ((fscanf(arquivo, "%d %d %d\n", &vertice_origem_i[i], &vertice_destino_i[i], &custo_i[i])) != EOF)
        {
            printf("%d %d %d\n", vertice_origem_i[i], vertice_destino_i[i], custo_i[i]);
            matriz_grafo[vertice_origem_i[i]][vertice_destino_i[i]] = custo_i[i];
            i++;
        }

        //Chamada do algoritmo
        dijkstra(matriz_grafo);
    }
    else
    {
        printf("Erro na leitura do arquivo!\n");
    }

    fclose(arquivo);

    return 0;
}
