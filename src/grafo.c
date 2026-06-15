#include <stdio.h>
#include <stdlib.h>
#include "../include/grafo.h"

Grafo* criar_grafo(int num_vertices, int max_arestas){
     //alocando memoria para o grafo.
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));

    if(g == NULL){
        printf ("Erro ao alocar memoria para o grafo.\n");
        exit(1);
    }
    g->num_vertices = num_vertices;
    g->num_arestas_atual = 0;
    g->max_arestas = max_arestas;

    //alocando memoria para o array de arestas
    g->array_arestas = (Aresta*)malloc(max_arestas * sizeof(Aresta));
    //alocando memoria para a lista de adjacencia
    g->lista_adj = (No**)malloc(num_vertices * sizeof(No*));
    
    for (int i = 0; i < num_vertices; i++) {
        g->lista_adj[i] = NULL;
    }
    
    return g;
}
///adicionando aresta nao direcionada ao grafo

void adicionar_aresta(Grafo* g, int origem, int destino, double peso){
    if(g->num_arestas_atual < g->max_arestas){
        //adicionando aresta ao array de arestas
        g->array_arestas[g->num_arestas_atual].origem = origem;
        g->array_arestas[g->num_arestas_atual].destino = destino;
        g->array_arestas[g->num_arestas_atual].peso = peso;
        g->num_arestas_atual++;

        //adicionando aresta a lista de adjacencia
        No* novo_no1 = (No*)malloc(sizeof(No));
        if(novo_no1 == NULL){
            printf("Erro ao alocar memoria para o no.\n");
            exit(1);
        }
        novo_no1->destino = destino;
        novo_no1->peso = peso;
        novo_no1->prox = g->lista_adj[origem];
        g->lista_adj[origem] = novo_no1;

        // Criando o no de origem e insere na lista de destino
        No* novo_no2 = (No*)malloc(sizeof(No));
        if(novo_no2 == NULL){
            printf("Erro ao alocar memoria para o no.\n");
            exit(1);
        }
        novo_no2->destino = origem;
        novo_no2->peso = peso;
        novo_no2->prox = g->lista_adj[destino];
        g->lista_adj[destino] = novo_no2;

    } else {
        printf("Limite maximo de arestas atingido.\n");
    }
}

//liberando memoria alocada para o grafo
void liberar_grafo(Grafo* g){
    if(g!=NULL){
        for(int i = 0; i < g->num_vertices; i++){
            No* atual = g->lista_adj[i];
            while (atual != NULL) {
                No* temp = atual;
                atual = atual->prox;
                free(temp);
            }
        }

        free(g->lista_adj);
        free(g->array_arestas);
        free(g);
    }
}