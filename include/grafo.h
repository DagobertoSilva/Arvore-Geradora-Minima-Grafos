#ifndef GRAFO_H
#define  GRAFO_H

// aresta
typedef struct{
    int origem;
    int destino;
    double peso;
} Aresta;

//no da lista de adjacencia
typedef struct No{
    int destino;
    double peso;
    struct No* prox;
} No;

// grafo representado por lista de adjacencia
typedef struct{
    int num_vertices;
    int num_arestas_atual;
    int max_arestas;
    Aresta* array_arestas;
    No** lista_adj;

} Grafo;

//alocando memoria para o grafo
Grafo* criar_grafo(int num_vertices, int max_arestas);

//adicionando aresta ao grafo
void adicionar_aresta(Grafo* g, int origem, int destino, double peso);

//libernado memoria alocada
void liberar_grafo(Grafo* g);

#endif