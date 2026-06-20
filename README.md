# Análise Experimental: Árvore Geradora Mínima (AGM)

Este projeto implementa e analisa o desempenho empírico de dois algoritmos clássicos da Teoria dos Grafos para o problema da Árvore Geradora Mínima (MST - Minimum Spanning Tree): **Algoritmo de Kruskal** e **Algoritmo de Prim**.

O trabalho foi desenvolvido em linguagem C, com foco em estruturas de dados e medição de tempo de execução.

## Estruturas de Dados Utilizadas
Para garantir a complexidade de tempo exigida na literatura, os algoritmos foram otimizados com as seguintes estruturas auxiliares:
* **Kruskal:** Utiliza a estrutura de *Union-Find* (Conjuntos Disjuntos) com as otimizações de *Compressão de Caminho* e *União por Rank* para detecção de ciclos em tempo quase $O(1)$.
* **Prim:** Utiliza uma *Fila de Prioridade* implementada como uma *Min-Heap* baseada em array, permitindo a operação *Decrease-Key* em tempo $O(\log V)$.

## Estrutura de Diretórios

O projeto está organizado na seguinte estrutura:

```text
Arvore-Geradora-Minima-Grafos/
├── bin/            # Executáveis compilados
├── docs/           # Relatório final e documentação
├── include/        # Arquivos de cabeçalho (.h)
├── instancias/     # Arquivos de texto contendo os grafos gerados (.txt)
├── src/            # Códigos-fonte (.c)
└── README.md
```
## Pré-requisitos
- Compilador GCC instalado.

## Como Compilar e Executar no Terminal
Abra o terminal na pasta raiz do projeto e siga os passos abaixo.

1. Compilar o Gerador de Instâncias

O gerador cria grafos conexos aleatórios garantindo que existe pelo menos uma Árvore Geradora Mínima válida.

```bash
gcc src/gerador.c -Wall -Wextra -o bin/gerador
```

2. Gerar um Grafo de Teste
Execute o gerador passando o número de vértices, o número de arestas e o caminho do arquivo de saída.

- Exemplo: Gerando um grafo esparso com 100 vértices e 150 arestas:
```bash
./bin/gerador 100 150 instancias/grafo_100_esparso.txt
```
3. Compilar o Orquestrador Principal

O programa principal lê o grafo e executa a bateria de testes. Como utilizamos funções matemáticas avançadas (desvio padrão), é obrigatório o uso da flag -lm.

```bash
gcc src/main.c src/grafo.c src/estruturas.c src/kruskal.c src/prim.c -Wall -Wextra -I./include -lm -o bin/main
```

4. Executar os Algoritmos
Rode o orquestrador passando o caminho do arquivo de texto gerado no Passo 2. O programa isola o tempo de I/O, roda cada algoritmo 10 vezes consecutivas e exibe a média e o desvio padrão em milissegundos.

```bash
./bin/main instancias/grafo_100_esparso.txt
```