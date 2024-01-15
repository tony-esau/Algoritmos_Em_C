#include <stdio.h>
#include <stdlib.h>

//Função para printar vetores formatado
void printa_vetor(int *vetor, int tamanho){
    printf("[");
    for(int i = 0; i < tamanho; i++){
        if (i != tamanho-1){
            printf("%d, ",vetor[i]); 
        }else{
            printf("%d",vetor[i]);
        }
    }
    printf("]\n");
}

//Faz uma troca simples com uso de um auxiliar
void troca(int *vetor, int indice){
    int auxiliar = vetor[indice];
    vetor[indice] = vetor [indice+1];
    vetor[indice+1] = auxiliar;
}

/*
Algoritmo BubbleSort 
Complexidade: n^2-n, da ordem de O(n^2).
*/
void BubbleSort(int *vetor, int tamanho){
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho-1; j++){
            if(vetor[j]>vetor[j+1]){
                troca(vetor,j);
            } 
        }
    }
}


int main(){
    int tamanho;

    printf("Digite o tamanho do Vetor:\n");
    scanf("%d",&tamanho);

    int *vetor = (int*)(malloc(tamanho*sizeof(int)));   

    //Programação defensiva
    if(vetor == NULL){
        printf("Erro de Memória...");
        exit(1);
    }

    printf("Digite os valores:\n");
    for (int i = 0; i < tamanho; i++){
       scanf("%d",&vetor[i]); 
    }

    system("cls");

    printf("Vetor digitado:\n");
    printa_vetor(vetor,tamanho);

    BubbleSort(vetor,tamanho);

    printf("Vetor ordenado:\n");
    printa_vetor(vetor,tamanho);

    return 0;
}