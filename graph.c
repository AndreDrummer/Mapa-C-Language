#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertex {
    char ID[3];
    char IP[20];    
} Vertex;

typedef struct aresta {
    Vertex v1;
    Vertex v2;
    int peso;
} Aresta;

struct graph {
    int numV;
    Vertex vertices[10];
    Aresta Ap[1000000];
    int A;    
    int **pesos;
    int **adj;
};

typedef struct graph *Graph;

static int **MATRIXint(int r, int c, int val)
{
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

double randomn()
{
    double numAleatorio;

    numAleatorio = rand() / (double)RAND_MAX;

    return numAleatorio;
}

Graph GraphInit(int V)
{
    Graph G = malloc(sizeof *G);
    
    G->numV = V;
    G->A = 0;
    G->adj = MATRIXint(V, V, 0);
    G->pesos = Weigthint(V, V, 0);
    // G->Ap = 

    for (int i = 0; i < G->numV; i++) {
        strcpy(G->vertices[i].ID, "A"+1);
        strcpy(G->vertices[i].IP, "127.0.0.1");        
    }

    return G;
}


void GRAPHInsertWigth(Graph G, int v, int w)
{    
    if (G->adj[v][w] = 1)
    {
        G->pesos[v][w] = (int)(randomn() * 10240.);        
    }
}

void GRAPHInsertArc(Graph G, int v, int w)
{
    // printf(" %d, %d", v, w);    
    if (G->adj[v][w] == 0)
    {           
        G->Ap[G->A].v1 = G->vertices[v];
        G->Ap[G->A].v2 = G->vertices[w];
        G->Ap[G->A].peso = G->pesos[v][w];
        G->adj[v][w] = 1;
        // printf("Atribuiu: %d\n",G->adj[v][w]);
        G->A++;
    }
}

void GRAPHRemoveArc(Graph G, int v, int w)
{
    if (G->adj[v][w] == 1)
    {
        G->adj[v][w] = 0;
        G->A++;
    }
}

void GRAPHShow(Graph G)
{
    for (int v = 0; v < G->numV; ++v)
    {

        printf("%s: ", G->vertices[v].ID);
        for (int w = 0; w < G->numV; ++w)
        {
            if (G->adj[v][w] == 1)
            {                
                printf("%s (%d) - ", G->vertices[v].ID, G->Ap[w].peso);                
                // printf("Showning: %d\n", G->adj[v][w]);
            }
        }
        printf("\n\n");
    }
}

void gerarGrafo(Graph G, int qtdVertices, double dens)
{

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
                    GRAPHInsertArc(G, i, j);
                    GRAPHInsertWigth(G, i, j);                       

                    // Dist[i][j] = (int)(randomn() * 10240.);
                    // Dist[j][i] = Dist[i][j];

                    // DistInfinita += Dist[i][j];
                }
            }
        }             
    }

    // for (i = 1; i <= qtdVertices; i++)
    // {
    //     for (j = i; j <= qtdVertices; j++)
    //     {
    //         if (MAdj[i][j] == 0)
    //         {
    //             Dist[i][j] = DistInfinita;
    //             Dist[j][i] = DistInfinita;
    //         }
    //     }
    // }

    // for (i = 1; i <= qtdVertices; i++)
    // {
    //     for (j = 1; j <= qtdVertices; j++)
    //     {
    //         if (MAdj[i][j] == 0)
    //         {
    //             Dist[i][j] = DistInfinita;
    //         }
    //     }
    // }
}

int main()
{
    int V = 10;

    // printf("Digite a quantidade de Vertices: \n");
    // scanf("%d", &V);

    Graph Grafo = GraphInit(V);

    int no;
    
    gerarGrafo(Grafo, V, 0.6);

    GRAPHShow(Grafo);

    return 0;
}