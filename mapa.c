#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#include <time.h>

// Prototipos
void gerarGrafo(int numeroArestas, double densidade);
void printGrafo(int n);
void bellmanFord(int s);
void menorCaminho(int MatrizADJ, int inicial, int final);
double randomn();

// Variáveis Globais

int MAdj[1024][1024];
int I_arco[1024 * 1024];
int J_arco[1024 * 1024];
int Dist[1024][1024];
int M_arcos = 0;
int DistInfinita = 1;
int MaxnumAres = 1024;
int numAres;
int mapaDist[1024];

int main()
{

    float dens;

    printf("Digite o numero de vertices do grafo: ");
    scanf("%d", &numAres);

    printf("Digite a densidade do grafo: ");
    scanf("%f", &dens);

    printf("\nEi-lo ai --->\nVertices: %d, \nDensidade: %f\n\n", numAres, dens);

    gerarGrafo(numAres, dens);
    printGrafo(numAres);
    
    bellmanFord(1);
    
}

void gerarGrafo(int n, double dens)
{

    int i, j;

    printf("\n\n Gerando Grafo Aleatório de Densidade: %f #Vertices: %d\n\n", dens, n);
    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            if (i != j)
            {
                if (randomn() < dens)
                {
                    M_arcos++;
                    I_arco[M_arcos] = i;
                    J_arco[M_arcos] = j;
                    MAdj[i][j] = 1;
                    MAdj[j][i] = 1;

                    Dist[i][j] = (int)(randomn() * 10240.);
                    Dist[j][i] = Dist[i][j];

                    DistInfinita += Dist[i][j];
                }
                else
                {
                    MAdj[i][j] = 0;
                    MAdj[j][i] = 0;
                }
            }
            else
            {
                MAdj[i][j] = 0;
                MAdj[j][i] = 0;
            }
        }
    }

    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            if (MAdj[i][j] == 0)
            {
                Dist[i][j] = DistInfinita;
                Dist[j][i] = DistInfinita;
            }
        }
    }

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (MAdj[i][j] == 0)
            {
                Dist[i][j] = DistInfinita;
            }
        }
    }
}

void printGrafo(int n)
{
    int i, j, p;
    printf("\n GRAFO: Matriz de Adjacencia\n\n");

    printf("   ");
    for (i = 1; i <= n; i++)
    {
        printf("%d     ", i);
    }
    printf("\n\n");

    for (p = 1; p <= n; p++)
    {
        printf("%d", p);
        if (p < 2)
        {
            for (i = 1; i <= p; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    // printf("%d:%d %d ", i, j, MAdj[i][j]);
                    printf("  %d   ", MAdj[i][j]);
                }
                printf("\n\n");
            }
        }
        else
        {
            for (i = p; i <= p; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    // printf("%d:%d %d ", i, j, MAdj[i][j]);
                    printf("  %d   ", MAdj[i][j]);
                }
                printf("\n\n");
            }
        }
    }

    // for (i = 1; i <= n; i++)
    // {
    //     for (j = 1; j <= n; j++)
    //     {
    //         // printf("%d:%d %d ", i, j, MAdj[i][j]);
    //         printf("   %d", MAdj[i][j]);

    //     }
    //     printf("\n");
    // }

    // printf("\n");
    // for (i = 1; i <= n; i++)
    // {
    //     for (j = 1; j <= n; j++)
    //     {
    //         printf("%d:%d %d ", i, j, Dist[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("\n\n");
    printf("GRAFO: Pesos\n\n\n");

    printf("    ");
    for (i = 1; i <= n; i++)
    {
        printf("%d        ", i);
    }
    printf("\n\n");

    for (p = 1; p <= n; p++)
    {
        printf("%d", p);
        if (p < 2)
        {
            for (i = 1; i <= p; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    printf("  %d   ", Dist[i][j]);
                }
                printf("\n\n");
            }
        }
        else
        {
            for (i = p; i <= p; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    printf("  %d   ", Dist[i][j]);
                }
                printf("\n\n");
            }
        }
    }
}

void menorCaminho(int MatrizADJ, int inicial, int final)
{
    printf("Mostrar caminho minimo de cada vertice até a origem!!\n\n");
}

void bellmanFord(int s)
{
    int v, w, k, ll;
    int d_temp[MaxnumAres];
    int pred[MaxnumAres];
    int circ_neg;

    circ_neg = 0;

    // Inicializacao: Caso Base - conhece o CMC de s
    // a todos os outros vertices utilizando no minimo ZERO
    // arcos.

    for (v = 1; v <= numAres; v++)
    {
        d_temp[v] = DistInfinita;
        pred[v] = -1;
    }

    d_temp[s] = 0;
    pred[s] = 0;

    // Passo Indutivo
    // Conhece-se caminho mais curto de s a um vertice q utilizando
    // no maximo k-1 arcos.
    // Para obter o cmc de s a q utilizando no maximo k arcos,
    // testa-se para cada arco no grafo (v,w) se d_temp(v) + Dist[v][w]
    // e' menor que d_temp[w], em caso afirmativo o atual cmc de
    // s a w nao e' um cmc e portanto atualizamos d_temp[w] e pred[w]

    for (k = 1; k <= numAres - 1; k++)
    {

        for (ll = 1; ll <= M_arcos; ll++)
        {
            v = I_arco[ll];
            w = J_arco[ll];
            if (d_temp[v] + Dist[v][w] < d_temp[w])
            {
                d_temp[w] = d_temp[v] + Dist[v][w];
                pred[w] = v;
            }
        }

        // Imprime dist temps atualizadas
        /*for (v = 1; v <= numAres; v++)
        {
            printf(" %d D=%d Caminho: ", v, d_temp[v]);
            w = v;
            //    do
            //    {
            // 	  printf(" %d | %d ||", d_temp[w], pred[w]);
            // 	  w = pred[w];
            //    }
            //    while ((w != v)&&(pred[w] > 0));
            printf("\n");
        }
        getchar();*/
    }

    getchar();

    // Testa se existe circuito negativo

    for (ll = 1; ll <= M_arcos; ll++)
    {
        v = I_arco[ll];
        w = J_arco[ll];
        if (d_temp[v] + Dist[v][w] < d_temp[w])
        {
            d_temp[w] = d_temp[v] + Dist[v][w];
            pred[w] = v;
            printf(" CIRCUITO NEGATIVO DETECTADO\n");
            circ_neg = 1;
            w = v;
            do
            {
                printf("ant v=%d w=%d \n", v, w);
                printf(" %d ", w);
                w = pred[w];
                printf("dep v=%d w=%d \n", v, w);
                getchar();
            } while (w != v);
            printf(" \n\n ");
        }
    }

    // Distancias e caminhos mais curtos

    if (circ_neg == 0)
    {
        printf(" Ford Bellman -- CMC a partir de %d \n", s);
        for (v = 1; v <= numAres; v++)
        {
            if (d_temp[v] != 0 && d_temp[v] != DistInfinita)
            {
                printf(" %d D=%d Caminho: ", v, d_temp[v]);
                w = v;
                char camino[100];
                while (pred[w] > 0)
                {
                    strcat(camino, " "+pred[w]);
                    printf(" %d ", pred[w]);
                    w = pred[w];
                }
                printf("%s", camino);
                printf("\n");
            }
        }
    }
}

double randomn()
{
    double numAleatorio;

    numAleatorio = rand() / (double)RAND_MAX;

    return numAleatorio;
}