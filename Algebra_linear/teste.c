#include <stdio.h>
#include <stdlib.h>

typedef struct matriz {
  // Como o tamanho pode escalonar, usar-se-á uma matriz dinâmica.
  int n_linhas;
  int n_colunas;
  float **matriz;
  int quadrada;
  int preenchimento;
} Matriz;

float **aloca_matriz(Matriz *matriz) {
  matriz->matriz = (float **)(malloc(sizeof(float *) * matriz->n_linhas));
  for (int i = 0; i < matriz->n_linhas; i++) {
    matriz->matriz[i] = (float *)(malloc(sizeof(float) * matriz->n_colunas));
  }
  return matriz->matriz;
}

// Cria a matriz de flutuantes dinamicamente
void criar_matriz(Matriz **matriz) {
  *matriz = (Matriz *)(malloc(sizeof(Matriz)));
  if (*matriz == NULL) {
    printf("Erro de alocação de memória! Encerrando o programa...\n");
    exit(1);
  }
  printf("Digite o número de linhas:");
  scanf("%d", &(*matriz)->n_linhas);
  printf("%d", (*matriz)->n_linhas);
  printf("Digite o número de colunas:");
  scanf("%d", &(*matriz)->n_colunas);
  printf("%d", (*matriz)->n_linhas);
  (*matriz)->matriz = aloca_matriz(*matriz);
  if ((*matriz)->n_linhas == (*matriz)->n_colunas) {
    (*matriz)->quadrada = 1;
  } else {
    (*matriz)->quadrada = 0;
  }
  (*matriz)->preenchimento = 0;
}


int main() {
  Matriz *matriz;
  criar_matriz(&matriz);
}