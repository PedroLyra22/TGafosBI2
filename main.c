#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define INFINITY 9999

// LETRA A----------------------------------

typedef struct vertice {
  int qtdAdjacentes;
  int adjacentes[MAX][2];
} Vertice;

typedef struct grafo {
  int qtdVertices;
  Vertice **vertices;
} Grafo;

Vertice *leVertice() {
  printf("Insira a quantidade de adjacentes:\n");
  int qtdAdjacentes;
  scanf("%d%*c", &qtdAdjacentes);

  Vertice *v = (Vertice *)malloc(sizeof(Vertice));
  v->qtdAdjacentes = qtdAdjacentes;

  for (int i = 0; i < qtdAdjacentes; i++) {
    printf("Insira o ID e peso da adjacência\n");
    scanf("%d %d%*c", &v->adjacentes[i][0], &v->adjacentes[i][1]);
  }

  return v;
}

Grafo leVertices() {
  printf("Quantos vertices?\n");
  int qtd;
  scanf("%d%*c", &qtd);

  Grafo g;
  g.qtdVertices = qtd;
  g.vertices = (Vertice **)malloc(sizeof(Vertice *) * g.qtdVertices);

  for (int i = 0; i < qtd; i++) {
    printf("Lendo vertice %d: \n", i);
    g.vertices[i] = leVertice();
  }

  return g;
}

void liberaGrafo(Grafo g) {
  for (int i = 0; i < g.qtdVertices; i++) {
    free(g.vertices[i]);
  }
}

void imprimeGrafo(Grafo g) {
  printf("Qtd de vertices: %d\n", g.qtdVertices);

  for (int i = 0; i < g.qtdVertices; i++) {
    printf("Vertice de ID %d\n", i);
    for (int j = 0; j < g.vertices[i]->qtdAdjacentes; j++) {
      printf("Adjacente de ID %d e peso %d\n", g.vertices[i]->adjacentes[j][0],
             g.vertices[i]->adjacentes[j][1]);
    }
  }
}

// LETRA B----------------------------------

int **alocaMatriz(int lin, int col) {
  int *valores = calloc(lin * col, sizeof(int));
  int **linhas = malloc(lin * sizeof(int *));
  for (int i = 0; i < lin; ++i) {
    linhas[i] = valores + i * col;
  }
  return linhas;
}

void liberaMatriz(int **matriz) {
  free(*matriz);
  free(matriz);
}

int **criaMatrizAdjacencia(Grafo g) {

  int **matriz = alocaMatriz(g.qtdVertices, g.qtdVertices);

  for (int i = 0; i < g.qtdVertices; i++) {
    for (int j = 0; j < g.qtdVertices; j++) {
      matriz[i][j] = INFINITY;
    }
  }

  for (int i = 0; i < g.qtdVertices; i++) {
    for (int j = 0; j < g.vertices[i]->qtdAdjacentes; j++) {
      // i;                               // id do atual
      // g.vertices[i]->adjacentes[j][0]; // id do adjacente
      // g.vertices[i]->adjacentes[j][1]; // peso do adjacente

      matriz[i][g.vertices[i]->adjacentes[j][0]] =
          g.vertices[i]->adjacentes[j][1];
    }
  }

  for (int i = 0; i < g.qtdVertices; i++) {
    printf("%d: ", i);
    for (int j = 0; j < g.qtdVertices; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
  return matriz;
}

void dijkstra(int **matrizAdj, int qtdVertices, int inicio) {

  int dist[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  // initialize pred[],distance[] and visited[]
  for (i = 0; i < qtdVertices; i++) {
    dist[i] = matrizAdj[inicio][i];
    pred[i] = inicio;
    visited[i] = 0;
  }

  dist[inicio] = 0;
  visited[inicio] = 1;
  count = 1;

  while (count < qtdVertices - 1) {
    mindistance = INFINITY;

    // nextnode gives the node at minimum distance
    for (i = 0; i < qtdVertices; i++)
      if (dist[i] < mindistance && !visited[i]) {
        mindistance = dist[i];
        nextnode = i;
      }

    // check if a better path exists through nextnode
    visited[nextnode] = 1;
    for (i = 0; i < qtdVertices; i++)
      if (!visited[i])
        if (mindistance + matrizAdj[nextnode][i] < dist[i]) {
          dist[i] = mindistance + matrizAdj[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }

  // print the path and distance of each node
  for (i = 0; i < qtdVertices; i++)
    if (i != inicio) {
      printf("\nDistance of node%d=%d", i, dist[i]);
      printf("\nPath=%d", i);

      j = i;
    }
  do {
    j = pred[j];
    printf("<-%d", j);
  } while (j != inicio);
}

int main(int argc, char const *argv[]) {
  Grafo g = leVertices();

  imprimeGrafo(g);

  int **matrizAdj = criaMatrizAdjacencia(g);
  dijkstra(matrizAdj, g.qtdVertices, 1);

  liberaGrafo(g);
  return 0;
}
