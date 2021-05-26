#include <stdio.h>
#include <stdlib.h>

/*

#1º Exercício-programa de Grafos#

#Prof. Glauber Cintra#

Integrantes do grupo:
- Elysson Gabriel Soares Simões
- João Marcus Maia Rocha
- Nivardo Albuquerque Leitão de Castro
- Paulo Ricardo Bernardo Silva

*/

int n, m, s, t;
int *u, *v, *c;
int i = 0;
char nome_do_arquivo[300];
FILE *arquivo;

int main()
{
    strcpy(nome_do_arquivo, "digrafo.txt");
    arquivo = fopen(nome_do_arquivo, "r");

    if(arquivo != NULL){

        fscanf(arquivo,"%d %d %d %d\n", &n, &m, &s, &t);
        printf("%d %d %d %d\n", n, m, s, t);

        u = malloc(sizeof(int) * m);
        v = malloc(sizeof(int) * m);
        c = malloc(sizeof(int) * m);

        while((fscanf(arquivo,"%d %d %d\n", &u[i], &v[i], &c[i])) != EOF){
            printf("%d %d %d\n", u[i], v[i], c[i]);
            i++;
        }

    }else{
        printf("Erro na leitura do arquivo!\n");
    }

    fclose(arquivo);

    return 0;
}
