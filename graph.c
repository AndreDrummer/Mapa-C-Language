#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int INT_MAX = 999999;
int const QTD_VERTEX = 10;

typedef struct vertex {
    char ID[3];
    char IP[20];
    int distSrc;
} Vertex;

typedef struct aresta {
    Vertex v1;
    Vertex v2;
    int peso;
} Aresta;

struct graph {
    int numV;
    Vertex vertices[10];
    Aresta arestas[1000000];
    int numA;    
    int **tablePesos;
    int **tableAdj;
};

typedef struct graph *Graph;

// Protótipos
Graph GraphInit(int V);
static int **MATRIXint(int r, int c, int val);
void BellmanFord(Graph G, Vertex *src);
static int **Weigthint(int r, int c, int val);
int GRAPHInsertArc(Graph G, int v, int w);
void GRAPHRemoveArc(Graph G, int v, int w);
void GRAPHShow(Graph G);
void insertArcWeight(Graph G, int qtdVertices, double dens);

int main() {
    int V = QTD_VERTEX;

    Graph Grafo = GraphInit(V);
    
    insertArcWeight(Grafo, V, 0.7);

    // GRAPHShow(Grafo);

    // printf("Primeiro Vertice %s %d", Grafo->vertices[0].ID, Grafo->vertices[0].distSrc);
    BellmanFord(Grafo,&Grafo->vertices[0]);


    return 0;
}

void BellmanFord(Graph G, Vertex *src) {
    int V = G->numV;
    int E = G->numA;

    for (int i = 0; i < V; i++) {
        if(&G->vertices[i] != src) {
            G->vertices[i].distSrc = INT_MAX;
        }        
    }
    
    const int start = 0;

    &src->distSrc = start;
    

    // printf("Source %s %s\n", src.ID, G->vertices[0].ID);
    // printf("Distancias da origem a origem %s %d\n", src.ID, src.distSrc);
    printf("Distancias da origem \n");
    for (int i = 0; i < V; i++) {
        printf("%s %d\n",G->vertices[i].ID, G->vertices[i].distSrc);
    }

    printf("ID da Origem: %p, ID da posicao 0: %p\n", src, &G->vertices[0]);

    if(src == &G->vertices[0]) {
        printf("Sim..\n");
    } else {
        printf("Não..\n");
    }

    for(int i = 1; i <= V - 1; i++) {
        for(int  j = 0; j < E; j++) {            
            Vertex u = G->arestas[j].v1;
            Vertex v = G->arestas[j].v2;
            int weight = G->arestas[j].peso;

            if(u.distSrc != INT_MAX && u.distSrc + weight < v.distSrc) {
                v.distSrc = u.distSrc + weight;
            }
        }
    }

    for(int i = 0; i < E; i++) {
        Vertex u = G->arestas[i].v1;
        Vertex v = G->arestas[i].v2;
        int weight = G->arestas[i].peso;

        if(u.distSrc != INT_MAX && u.distSrc + weight < v.distSrc){
            printf("Grafo contém ciclos negativos");
        return;
        }

    }

    printf("Vertex: \t\t\t");
    for(int i = 0; i < V; i++) {
        printf("%s \t", G->vertices[i].ID);
    }
        
    printf("\nDistancia a partir da origim: ");
    for(int i = 0; i < V; i++) {
        printf("%d \t", G->vertices[i].distSrc);
    }
        
    return;
}

static int **MATRIXint(int r, int c, int val) {
    int **m = malloc(r * sizeof(int *));    
    for (int i = 0; i < r; ++i)
        m[i] = malloc(c * sizeof(int));
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            m[i][j] = val;            
    return m;
}

static int **Weigthint(int r, int c, int val)
{    
    int **weigth = malloc(r * sizeof(int *));
    for (int i = 0; i < r; ++i)
        weigth[i] = malloc(c * sizeof(int));
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            weigth[i][j] = val;            
    return weigth;
}

double randomn() {
    double numAleatorio;

    numAleatorio = rand() / (double)RAND_MAX;

    return numAleatorio;
}

Graph GraphInit(int V) {
    Graph G = malloc(sizeof *G);
    Vertex vet[QTD_VERTEX];
    
    G->numV = V;
    G->numA = 0;
    G->tableAdj = MATRIXint(V, V, 0);
    G->tablePesos = Weigthint(V, V, 0);

    for (int i = 0; i < G->numV; i++) {
        char intString[10];
        snprintf(intString, 10, "%s%d", "A", i);
        strcpy(vet[i].ID, intString);
        strcpy(vet[i].IP, "127.0.0.1");
        vet[i].distSrc = INT_MAX;
        G->vertices[i] = vet[i];
    }

    return G;
}


void GRAPHInsertWeigth(Graph G, int v, int w, int aresPos) {    
    if (G->tableAdj[v][w] = 1)
    {
        G->arestas[aresPos].peso = G->tablePesos[v][w] = (randomn() * 10240.);
    }
}

int GRAPHInsertArc(Graph G, int v, int w) {
    int actualNumArestas = G->numA;
    // printf(" %d, %d", v, w);    
    if (G->tableAdj[v][w] == 0)
    {   
        // printf("Aresta %d - [V1][V2] = [%d][%d]\n", G->numA, v ,w);
        G->arestas[G->numA].v1 = G->vertices[v];
        G->arestas[G->numA].v2 = G->vertices[w];
        G->arestas[G->numA].peso = G->tablePesos[v][w];
        G->tableAdj[v][w] = 1;
        // printf("Atribuiu: %d\n"  G->tableAdj[v][w]);
        // printf("Aresta %d - [V1][V2] = [%s][%s] | Peso = %d\n", G->numA, G->vertices[v].ID, G->vertices[w].ID, G->arestas[actualNumArestas].peso);
        G->numA++;
    }
    return actualNumArestas;
}

void GRAPHRemoveArc(Graph G, int v, int w) {
    if  (G->tableAdj[v][w] == 1)
    {
        G->tableAdj[v][w] = 0;
        G->numA++;
    }
}

void GRAPHShow(Graph G) {
    for (int v = 0; v < G->numV; ++v)
    {

        // printf("%d: ",v);
        printf("%s: ", G->vertices[v].ID);
        for (int w = 0; w < G->numV; ++w)
        {
            if  (G->tableAdj[v][w] == 1)
            {                
                // printf("%s (%d) - ", G->vertices[v].ID, G->numAp[w].peso);                
                printf("%s (%d) -  ", G->vertices[w].ID, G->tablePesos[v][w]);
                // printf("%s", G->vertices[v].IP);
            }
        }
        printf("\n\n");
    }
}

void insertArcWeight(Graph G, int qtdVertices, double dens) {

    int i, j;

    printf("\n\n Gerando Grafo Aleatório de Densidade: %f #Vertices: %d\n\n", dens, qtdVertices);
    for (i = 0; i <= qtdVertices; i++)
    {
        for (j = i; j <= qtdVertices; j++)
        {
            if (i != j)
            {
                if (randomn() < dens)
                {   
                    int actualNumArestas = GRAPHInsertArc(G, i, j);
                    // GRAPHInsertWeigth(G, i, j, actualNumArestas);                    
                }
            }
        }             
    }
}
