#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct vertex {
    char ID[3];
    char IP[20];    
};

typedef struct vertex *Vertex;

struct Grafo {
    Vertex *v1;
    Vertex *v2;
    int Peso;
};

int main() {

    

    return 0;
}