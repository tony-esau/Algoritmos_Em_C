#include <stdio.h>
#include <stdlib.h>

typedef struct matriz{
    int n_linhas;
    int n_colunas;
    float **matriz;
    int preenchimento;
    int quadrada;
}Matriz;

float **aloca_matriz(Matriz *matriz) {
  matriz->matriz = (float **)(malloc(sizeof(float *) * matriz->n_linhas));
  for (int i = 0; i < matriz->n_linhas; i++) {
    matriz->matriz[i] = (float *)(malloc(sizeof(float) * matriz->n_colunas));
  }
  return matriz->matriz;
}

Matriz* criar_matriz(Matriz *ptr_matriz){
    
    ptr_matriz = (Matriz*)malloc(sizeof(Matriz));
    
    printf("Digite o número de linhas:");
    scanf("%d", &ptr_matriz->n_linhas);
    printf("Digite o número de colunas:");
    scanf("%d", &ptr_matriz->n_colunas);

    ptr_matriz->matriz = aloca_matriz(ptr_matriz);

    ptr_matriz->preenchimento = 0;

    if (ptr_matriz->n_colunas == ptr_matriz->n_linhas) {
        ptr_matriz->quadrada = 1;
    }else{ 
        ptr_matriz->quadrada = 0; 
    }
    return ptr_matriz;
}

void preencher_matriz(Matriz *matriz) {
  for (int i = 0; i < matriz->n_linhas;  i++) {
    for (int j = 0; j < matriz->n_colunas; j++) {
      printf("Digite o valor da célula a[%d][%d]:", i, j);
      scanf("%f", &(matriz->matriz[i][j]));
    }
  }
  matriz->preenchimento = 1;
}

int printar_matriz(Matriz *matriz) {
  if (matriz->preenchimento == 1) {
    for (int i = 0; i < matriz->n_linhas; i++) {
      for (int j = 0; j < matriz->n_colunas; j++) {
        if (j == 0) {
          // ver o caso da matriz coluna
          printf("|%.2f\t", matriz->matriz[i][j]);
        } else if (j == (matriz->n_colunas - 1)) {
          printf("%.2f|\t", matriz->matriz[i][j]);
        } else {
          printf("%.2f\t", matriz->matriz[i][j]);
        }
      }
      printf("\n");
    }
    return 1;
  } else {
    return 0;
  }
}

Matriz* adiciona_matriz(Matriz *matriz1, Matriz *matriz2) {
    Matriz *matriz_soma = (Matriz *)(malloc(sizeof(Matriz)));
    if((matriz1->preenchimento == 1) && (matriz2->preenchimento == 1) && (matriz1->n_linhas == matriz2->n_linhas) && (matriz1->n_colunas == matriz2->n_colunas)) {
        matriz_soma->n_linhas = matriz1->n_linhas;
        matriz_soma->n_colunas = matriz1->n_colunas;
        matriz_soma->quadrada = matriz1->quadrada;
        matriz_soma->matriz = aloca_matriz(matriz_soma);
        matriz_soma->preenchimento = 1;
        for (int i = 0; i < matriz1->n_linhas; i++){
            for(int j = 0; j < matriz1->n_colunas; j++){
                matriz_soma->matriz[i][j] = matriz1->matriz[i][j] + matriz2->matriz[i][j];
            } 
        }
        return matriz_soma;
  }
    free(matriz_soma);
    return NULL;
}

Matriz* multiplica_matriz(Matriz *matriz1, Matriz *matriz2) {
    Matriz *matriz_produto = (Matriz *)(malloc(sizeof(Matriz)));
    if((matriz1->preenchimento == 1) && (matriz2->preenchimento == 1) && (matriz1->n_colunas == matriz2->n_linhas)){
        matriz_produto->n_linhas = matriz1->n_linhas;
        matriz_produto->n_colunas = matriz2->n_colunas;
        matriz_produto->matriz = aloca_matriz(matriz_produto);
        matriz_produto->preenchimento = 1;

        for(int i = 0; i < matriz_produto->n_linhas; i++){
            for(int j = 0; j < matriz_produto->n_colunas; j++){
                matriz_produto->matriz[i][j] = 0;
                for(int k = 0; k < matriz1->n_colunas; k++){ 
                    matriz_produto->matriz[i][j] += matriz1->matriz[i][k] * matriz2->matriz[k][j];
                }
            }
        }
        
        if(matriz_produto->n_linhas == matriz_produto->n_colunas){
            matriz_produto->quadrada = 1;
        }else{
            matriz_produto->quadrada = 0;
        }
        return matriz_produto;
  }
    free(matriz_produto);
    return NULL;
}

Matriz *transpor_matriz(Matriz *matriz) {
  if (matriz->preenchimento == 1) {
    Matriz *transposta = (Matriz *)(malloc(sizeof(Matriz)));
    transposta->n_linhas = matriz->n_colunas;
    transposta->n_colunas = matriz->n_linhas;
    transposta->quadrada = matriz->quadrada;

    transposta->matriz = aloca_matriz(transposta);

    for (int i = 0; i < transposta->n_linhas; i++) {
      for (int j = 0; j < transposta->n_colunas; j++) {
        transposta->matriz[i][j] = matriz->matriz[j][i];
      }
    }
    transposta->preenchimento = 1;

    return transposta;
  }
  return NULL;
}

int main(){
    Matriz *matriz1 = NULL;
    matriz1 = criar_matriz(matriz1);
    Matriz *matriz2 = NULL;
    matriz2 = criar_matriz(matriz2);

    preencher_matriz(matriz1);
    preencher_matriz(matriz2);

    Matriz *matriz_produto = multiplica_matriz(matriz1, matriz2);
    if(matriz_produto == NULL){
        printf("erro");
    }else{
        printar_matriz(matriz_produto);
    } 

}
