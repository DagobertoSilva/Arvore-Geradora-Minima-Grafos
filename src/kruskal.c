#include <stdio.h>
#include <stdlib.h>
#include "../include/grafo.h"
#include "../include/estruturas.h"


//comparando as arestas pelo peso
int comparar_arestas(const void* a, const void* b) {
    //convertendo os ponteiros para o tipo Aresta
    Aresta* arestaA=(Aresta*)a;
    Aresta* arestaB=(Aresta*)b;

    
    if(arestaA->peso < arestaB->peso){
        return -1;
    }
    if(arestaA->peso > arestaB->peso){
        return 1;
    }
    return 0;
}

Grafo* exec_Kruskal(Grafo *g, double* peso_total) {
    *peso_total = 0.0;
    //criando um novo grafo para armazenar a agm

    int max_arestas_agm = g->num_vertices - 1;
    Grafo* agm = criar_grafo(g->num_vertices, max_arestas_agm);

    //ordenando as arestas do grafo pelo peso
    qsort(g->array_arestas, g->num_arestas_atual, sizeof(Aresta), comparar_arestas);

    //criando um UF para gerenciar os conjuntos de vértices
    UnionFind* uf = criar_uf(g->num_vertices);

    for(int i = 0; i < g->num_arestas_atual; i++){
        Aresta aresta_atual = g->array_arestas[i];
        if(encontrar_uf(uf, aresta_atual.origem) != encontrar_uf(uf, aresta_atual.destino)){
                //adicionando a aresta atual a agm
                adicionar_aresta(agm, aresta_atual.origem, aresta_atual.destino, aresta_atual.peso);
                *peso_total += aresta_atual.peso;

                //unindo os conjuntos dos vErtices da aresta atual
                unir_uf(uf, aresta_atual.origem, aresta_atual.destino);
            if(agm->num_arestas_atual == max_arestas_agm){
                break;
            }
        } 
    }
    liberar_uf(uf);
    return agm;
}