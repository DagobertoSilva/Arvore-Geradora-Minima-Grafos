#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct{
    double x,y;
}Ponto;

int main(int argc, char* argv[]){

    if(argc !=4){
        return 1;
    }
    
    int V = atoi(argv[1]);
    int E = atoi(argv[2]);

    FILE * arq = fopen(argv[3], "w");

    Ponto* pontos = malloc(V* sizeof(Ponto));
    if (pontos == NULL)
    {
        printf("Erro ao alocar memoria!");
        exit(1);
    }
    srand(time(NULL));

    for (int i = 0; i < V; i++){
        pontos[i].x = rand() % 1000;
        pontos[i].y = rand()%1000;
    }
    fprintf(arq, "%d %d\n", V, E);

    for(int i = 0; i < E; i++){
        int u = rand() % V;
        int v = rand() % V;

        if(u!=v){
            double dist = sqrt(pow(pontos[u].x - pontos[v].x, 2) +
                                pow(pontos[u].y - pontos[v].y, 2));
            fprintf(arq, "%d %d %.2f\n", u, v, dist);
        }
    }

    fclose(arq);
    free(pontos);
    return 0;
}