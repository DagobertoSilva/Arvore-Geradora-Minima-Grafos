#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../include/estruturas.h"
#include "../include/grafo.h"

Grafo* executar_prim(Grafo* g, double* peso_total){
    *peso_total=0.0;
    int V = g->num_vertices;
    
    //arrays de controle
    //quem conectou
    int pai[V];
    //menor custo descoberto ate o momento
    double chave[V];


    MinHeap* min_heap = criar_min_heap(V);

    for(int v = 0; v< V; v++){
        pai[v] = -1;
        chave[v] = DBL_MAX;

       // alocando no para cada vertice e inserindo no minheap
        min_heap->array[v] = (MinHeapNode*)malloc(sizeof(MinHeapNode));
        min_heap->array[v]->vertice=v;
        min_heap->array[v]->chave=chave[v];
        min_heap->posicoes[v]=v;
    }
    //escolhebndo o verice zero para iniciar os trabalhos
    chave[0]=0.0;
    min_heap->array[0]->chave=chave[0];
    min_heap->tamanho_atual=V;

    while(!heap_vazio(min_heap)){
        //catando vertices de conexao mais barata
        MinHeapNode* min_no = extrair_minimo(min_heap);
        int u = min_no -> vertice;

        min_heap->array[min_heap->tamanho_atual] = min_no;


        if(pai[u]!=-1){
            *peso_total+=chave[u];
        }

        //lista de vizinhos
        No* vizinho_atual = g->lista_adj[u];

        while (vizinho_atual != NULL) {
            int v = vizinho_atual->destino;
            double peso_aresta = vizinho_atual->peso;

            if(esta_no_min_heap(min_heap, v) && peso_aresta < chave[v]){
                chave[v] = peso_aresta;
                pai[v] = u;
                diminuir_chave(min_heap, v, chave[v]);
            }
            vizinho_atual = vizinho_atual->prox;
        }   
    }
    //montando grafo de saida
    Grafo* agm = criar_grafo(V, V-1);
    for(int i = 1; i< V; i++){
        if(pai[i] != -1){
            adicionar_aresta(agm, pai[i], i, chave[i]);
        }
    }
    liberar_min_heap(min_heap);
    return agm;

}