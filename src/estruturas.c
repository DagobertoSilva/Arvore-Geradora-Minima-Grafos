#include <stdio.h>
#include <stdlib.h>
#include "../include/estruturas.h"

//função para criar um novo Union-Find
UnionFind* criar_uf(int n) {
 UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    if (uf == NULL) {
        printf("Erro ao alocar memoria para UnionFind.\n");
        exit(1);
    }
    uf ->pai=(int*)malloc(n*sizeof(int));
    uf ->rank=(int*)malloc(n*sizeof(int));
    if (uf->pai == NULL || uf->rank == NULL) {
        printf("Erro ao alocar memoria para UnionFind.\n");
        free(uf);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        uf->pai[i] = i;
        uf->rank[i] = 0;
    }
    return uf;
}

//função para encontrar o representante do conjunto de um elemento
int encontrar_uf(UnionFind* uf, int i){
    if(uf->pai[i] != i){
        uf->pai[i] = encontrar_uf(uf, uf->pai[i]);
    }
    return uf->pai[i];
}

//função para unir dois conjuntos
void unir_uf(UnionFind* uf, int i, int j){
    //encontrando as raízes dos conjuntos de i e j
    int raiz_i = encontrar_uf(uf,i);
    int raiz_j = encontrar_uf(uf,j);

    //unindo os conjuntos se as raízes forem diferentes
    if(raiz_i != raiz_j) {
        if (uf->rank[raiz_i] < uf->rank[raiz_j]) {
            uf->pai[raiz_i] = raiz_j;
        } else if (uf->rank[raiz_i] > uf->rank[raiz_j]) {
            uf->pai[raiz_j] = raiz_i;
        } 
        // Se os ranks são iguais, escolhemos uma raiz arbitrariamente e incrementamos seu rank
        else {
            uf->pai[raiz_j] = raiz_i;
            uf->rank[raiz_i]++;
        }
    }
}

void liberar_uf(UnionFind* uf) {
    if (uf != NULL) {
        free(uf->pai);
        free(uf->rank);
        free(uf);
    }
}

MinHeap* criar_min_heap(int capacidade) {
    MinHeap* min_heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (min_heap == NULL) {
        printf("Erro ao alocar memoria para MinHeap.\n");
        exit(1);
    }
    min_heap->tamanho_atual = 0;
    min_heap->capacidade = capacidade;
    min_heap->posicoes = (int*)malloc(capacidade * sizeof(int));
    if (min_heap->posicoes == NULL) {
        printf("Erro ao alocar memoria para MinHeap.\n");
        free(min_heap);
        exit(1);
    }
    min_heap->array = (MinHeapNode**)malloc(capacidade * sizeof(MinHeapNode*));
    if (min_heap->array == NULL) {
        printf("Erro ao alocar memoria para MinHeap.\n");
        free(min_heap->posicoes);
        free(min_heap);
        exit(1);
    }
    return min_heap;
}

//trocando dois nós na min-heap
void trocar_nos_min_heap(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

////mantendo o menor no no topo da min-heap
void min_heapify(MinHeap* min_heap, int idx) {
    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;

    if (esquerda < min_heap->tamanho_atual && 
        min_heap->array[esquerda]->chave < min_heap->array[menor]->chave)
        menor = esquerda;

    if (direita < min_heap->tamanho_atual && 
        min_heap->array[direita]->chave < min_heap->array[menor]->chave)
        menor = direita;

    if (menor != idx) {
        //atualiza o mapa de posicoes antes de trocar
        MinHeapNode* no_menor = min_heap->array[menor];
        MinHeapNode* no_idx = min_heap->array[idx];
        min_heap->posicoes[no_menor->vertice] = idx;
        min_heap->posicoes[no_idx->vertice] = menor;

        trocar_nos_min_heap(&min_heap->array[menor], &min_heap->array[idx]);
        min_heapify(min_heap, menor);
    }
}

int heap_vazio(MinHeap* min_heap) {
    return min_heap->tamanho_atual == 0;
}

//retirando e devolvendo o vertice de menor valoer
MinHeapNode* extrair_minimo(MinHeap* min_heap){
    if (heap_vazio(min_heap)){
        return NULL;
    }

    MinHeapNode* raiz = min_heap->array[0];
    MinHeapNode* ultimo_no = min_heap-> array[min_heap->tamanho_atual - 1];
    //substitui a raiz pleo utlmo no e reorganiza fila
    min_heap->array[0]=ultimo_no;
    min_heap->posicoes[raiz->vertice] = min_heap->tamanho_atual-1;
    min_heap->posicoes[ultimo_no->vertice] = 0;

    min_heap->tamanho_atual--;
    min_heapify(min_heap, 0);

    return raiz;
}

//atualizando o custo de um vertice
void diminuir_chave(MinHeap* min_heap, int vertice, double nova_chave){
    int i = min_heap ->posicoes[vertice];
    min_heap-> array[i]-> chave = nova_chave;
while (i && min_heap->array[i]->chave < min_heap->array[(i - 1) / 2]->chave) {
        min_heap->posicoes[min_heap->array[i]->vertice] = (i - 1) / 2;
        min_heap->posicoes[min_heap->array[(i - 1) / 2]->vertice] = i;
        
        trocar_nos_min_heap(&min_heap->array[i], &min_heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// verificando se ainda ha vertices na fila
int esta_no_min_heap(MinHeap* minHeap, int vertice) {
    return minHeap->posicoes[vertice] < minHeap->tamanho_atual;
}

void liberar_min_heap(MinHeap* minHeap) {
    if (minHeap != NULL) {
        for (int i = 0; i < minHeap->capacidade; i++) {
            if (minHeap->array[i] != NULL) free(minHeap->array[i]);
        }
        free(minHeap->array);
        free(minHeap->posicoes);
        free(minHeap);
    }
}