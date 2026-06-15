#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <math.h>  
#include "../include/grafo.h"
#define NUM_EXECUCOES 10

double calcular_tempo_ms(struct timeval inicio, struct timeval fim);
Grafo* carregar_grafo_do_arquivo(const char* nome_arquivo);
double calcular_desvio_padrao(double tempos[], double media);

int main(int argc, char* argv[]){

    if(argc != 2){
       printf("Uso correto: %s <caminho_para_instancia.txt>\n", argv[0]);
        return 1;
    }

    struct timeval inicio_leitura, fim_leitura;
    struct timeval inicio_algo, fim_algo;

    //lendo e construindo o grafito

    gettimeofday(&inicio_leitura, NULL);
    Grafo* grafo_original = carregar_grafo_do_arquivo(argv[1]);
    gettimeofday(&fim_leitura, NULL);

    double tempo_leitura_ms = calcular_tempo_ms(inicio_leitura, fim_leitura);
    printf("Tempo de leitura e construcao do grafo: %.3f ms\n\n", tempo_leitura_ms);

    //guardando metricas 
    double tempos_kruskal[NUM_EXECUCOES];
    double tempos_prim[NUM_EXECUCOES];
    double soma_kruskal = 0.0, soma_prim = 0.0;
    double peso_final_kruskal = 0.0, peso_final_prim = 0.0;

    //executando o kruskal ate dar uma dor
    printf("Iniciando execucoes do Kruskall\n");
    for (int i = 0; i < NUM_EXECUCOES; i++) {
        gettimeofday(&inicio_algo, NULL);
        Grafo* mst_kruskal = exec_Kruskal(grafo_original, &peso_final_kruskal);
        gettimeofday(&fim_algo, NULL);

        tempos_kruskal[i] = calcular_tempo_ms(inicio_algo, fim_algo);
        soma_kruskal += tempos_kruskal[i];
        
        liberar_grafo(mst_kruskal); 
    }

    //executando o prim ate dar uma dor
    printf("Iniciando execucoes do Prim\n");
    for (int i = 0; i < NUM_EXECUCOES; i++) {
        gettimeofday(&inicio_algo, NULL);
        Grafo* mst_prim = executar_prim(grafo_original, &peso_final_prim);
        gettimeofday(&fim_algo, NULL);

        tempos_prim[i] = calcular_tempo_ms(inicio_algo, fim_algo);
        soma_prim += tempos_prim[i];
        
        liberar_grafo(mst_prim);
    }

    //calculando metricas de avlaicao
    double media_kruskal = soma_kruskal / NUM_EXECUCOES;
    double dp_kruskal = calcular_desvio_padrao(tempos_kruskal, media_kruskal);

    double media_prim = soma_prim / NUM_EXECUCOES;
    double dp_prim = calcular_desvio_padrao(tempos_prim, media_prim);

    printf("Custo total da AGM (Kruskal): %.2f\n", peso_final_kruskal);
    printf("Custo total da AGM (Prim):    %.2f\n", peso_final_prim);
    if (fabs(peso_final_kruskal - peso_final_prim) < 0.01) {
        printf("Ambos os algoritmos encontraram o mesmo custo minimo!\n");
    } else {
        printf("Os custos sao diferentes :(\n");
    }

    printf("KRUSKAL - Tempo Medio: %.3f ms | Desvio Padrao: %.3f ms\n", media_kruskal, dp_kruskal);
    printf("PRIM  -  Tempo Medio: %.3f ms | Desvio Padrao: %.3f ms\n", media_prim, dp_prim);

    liberar_grafo(grafo_original);

    return 0;
}

//tempo em milisegundos
double calcular_tempo_ms(struct timeval inicio, struct timeval fim)
{
    long segundos =fim.tv_sec - inicio.tv_sec;
    long microsegundos = fim.tv_usec - inicio.tv_usec;
    return (segundos * 1000.0) + (microsegundos/1000.0);
}

//lendo arquivos gerados e construindo o grafo in memory
Grafo* carregar_grafo_do_arquivo(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nome_arquivo);
        exit(1);
    }

    int V, E;
    if (fscanf(arquivo, "%d %d", &V, &E) != 2) {
        printf("Erro ao ler cabecalho do arquivo.\n");
        exit(1);
    }

    Grafo* g = criar_grafo(V, E);

    int origem, destino;
    double peso;
    for (int i = 0; i < E; i++) {
        fscanf(arquivo, "%d %d %lf", &origem, &destino, &peso);
        adicionar_aresta(g, origem, destino, peso);
    }

    fclose(arquivo);
    return g;
}

//calc desvio padrao
double calcular_desvio_padrao(double tempos[], double media) {
    double soma_variancia = 0.0;
    for (int i = 0; i < NUM_EXECUCOES; i++) {
        soma_variancia += pow(tempos[i] - media, 2);
    }
    return sqrt(soma_variancia / NUM_EXECUCOES);
}