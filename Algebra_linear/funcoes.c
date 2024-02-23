#include "matrizes.h"
#include <stdio.h>

Matriz criar_matriz(){
    Matriz matriz;
    return matriz;
}

Matriz preencher_matriz(Matriz matriz){
    int auxiliar;
    for( int i = 0; i < TAMANHO; i++){
        for (int j = 0; j < TAMANHO; j++){
            printf("Digite o valor da célula a[%d][%d]:",i,j);
            scanf("%d",auxiliar);
            matriz.matriz[i][j] = auxiliar;
        } 
    }
    system("clear");
    return matriz;
}

void printar_matriz(Matriz matriz){
    for(int i = 0; i < TAMANHO; i++){
        for(int j = 0; j < TAMANHO; j++){
            printf("%d",matriz.matriz[i][j]);
        }
        printf("\n");
    }
}

