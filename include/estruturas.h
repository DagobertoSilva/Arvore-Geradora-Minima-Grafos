#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


typedef struct{
    int* pai;
    int* rank;
} UnionFind;


//criando estruturas para o algoritmo de prim
//estrutura para representar um nó na fila de prioridade
typedef struct{
    int vertice;
    double chave;
}MinHeapNode;

typedef struct{
    int tamanho_atual;
    int capacidade;
    int* posicoes;
    MinHeapNode** array;
} MinHeap;

UnionFind* criar_uf(int n);
int encontrar_uf(UnionFind* uf, int i);
void unir_uf(UnionFind* uf, int i, int j);
void liberar_uf(UnionFind* uf);

MinHeap* criar_min_heap(int capacidade);
void trocar_nos_min_heap(MinHeapNode** a, MinHeapNode** b);
void min_heapify(MinHeap* min_heap, int idx);
int heap_vazio(MinHeap* min_heap);
MinHeapNode* extrair_minimo(MinHeap* min_heap);
void diminuir_chave(MinHeap* min_heap, int vertice, double nova_chave);
int esta_no_min_heap(MinHeap* min_heap, int vertice);
void liberar_min_heap(MinHeap* min_heap);
#endif