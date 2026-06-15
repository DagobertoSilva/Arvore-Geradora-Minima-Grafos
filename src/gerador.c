#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//gerando pesos aleatórios para as arestas do grafo
double gerar_peso(double min, double max){
    double escala = rand() / (double) RAND_MAX; 
    return min + escala * (max - min);
}

int main (int argc, char* argv[]){
    if(argc!=4){
        printf("Uso: %s <num_vertices> <num_arestas> <peso_maximo>\n", argv[0]);
        return 1;
    }

    int V = atoi(argv[1]);
    int E = atoi(argv[2]);
    char* nome_arquivo = argv[3];

    if(E < V -1){
        printf("O numero de arestas deve ser pelo menos V-1 para garantir a conectividade do grafo.\n");
        return 1;
    }

    FILE* arquivo = fopen(nome_arquivo, "w");

    if(arquivo == NULL){
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }
    srand(time(NULL));
    fprintf(arquivo, "%d %d\n", V, E);

    int arestas_geradas = 0;

    for(int i = 1; i < V; i++){

        int j = rand() % i;
        double peso = gerar_peso(1.0, 100.0);
        fprintf(arquivo, "%d %d %.2f\n", j, i, peso);
        arestas_geradas++;
    }

    while(arestas_geradas < E){
        int u = rand() % V;
        int v = rand() % V;

        if(u != v){
            double peso = gerar_peso(1.0, 100.0);
            fprintf(arquivo, "%d %d %.2f\n", u, v, peso);
            arestas_geradas++;
        }
    }
    fclose(arquivo);
    printf("Grafo gerado no arquivo %s\n", nome_arquivo);

    return 0;
}