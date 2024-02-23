#ifndef INCLUDE_MATRIZES
#define INCLUDE_MATRIZES

#define TAMANHO 3

typedef struct matriz{
    //Como o tamanho é fixo, usar-se-á uma matriz estática.
    int matriz[3][3];
}Matriz;

Matriz criar_matriz();
Matriz preencher_matriz(Matriz matriz);
void printar_matriz(Matriz matriz);

#endif