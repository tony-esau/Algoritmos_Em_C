#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cabecalho.h"

void limpa_tela(){
    #ifdef _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

void Merge(Dados *dados, int inicio, int meio, int fim){
    int *vetor_auxiliar, inicio_1, inicio_2,tamanho,i,j,k;
    int fim_1 = 0, fim_2 = 0;
    tamanho = fim-inicio+1;
    inicio_1 = inicio;
    inicio_2 = meio+1;
    vetor_auxiliar = (int*) (malloc(tamanho*sizeof(int)));
    
    if(vetor_auxiliar == NULL){
        printf("Erro de Memória...");
        exit(1);
    }else{
        for(i = 0; i < tamanho; i++){
            if(!fim_1 && !fim_2){
                if(dados->vetor[inicio_1] < dados->vetor[inicio_2]){
                    vetor_auxiliar[i] = dados->vetor[inicio_1];
                    inicio_1++;
                }else{
                    vetor_auxiliar[i] = dados->vetor[inicio_2];
                    inicio_2++;
                }
                if(inicio_1 > meio) fim_1 = 1;
                if(inicio_2 > fim) fim_2 = 1;

            }else{
                if(!fim_1){
                    vetor_auxiliar[i] = dados->vetor[inicio_1];
                    inicio_1++;
                }else{
                    vetor_auxiliar[i] = dados->vetor[inicio_2];
                    inicio_2++;
                }      
            }
        }
    }
    for(i = 0; i < tamanho; i++){
        dados->vetor[inicio + i] = vetor_auxiliar[i];
    }
    free(vetor_auxiliar);
}

void MergeRecursive(Dados *dados, int inicio, int fim){
    int meio;

    if(inicio < fim){
        meio = (int)((inicio+fim)/2);
        MergeRecursive(dados,inicio,meio);
        MergeRecursive(dados,meio+1,fim);
        Merge(dados,inicio,meio,fim);
    }
}


void MergeSort(Dados *dados){
    int fim = (dados->tamanho)-1;
    int inicio = 0;
    MergeRecursive(dados,inicio,fim);
}

float moda(Dados *dados){
    if(dados->tamanho == 1){
        return (float)dados->vetor[0];
    }
    int acumulador = 0;
    int maior_repeticao = 0;
    int moda = dados->vetor[0];
    if(dados->tamanho > 1){
        for(int i = 0; i < dados->tamanho;i++){
            acumulador = 0;
            for(int j = 0; j < dados->tamanho;j++){
                if(dados->vetor[j] == dados->vetor[i]){
                    acumulador++;
                }
            }
            if(acumulador > maior_repeticao){
                maior_repeticao = acumulador;
                moda = dados->vetor[i];
            }
        }
    }
    
    if(maior_repeticao == 1){
        return 0.0;
    }else{
        return (float) moda;
    }
}

float media(Dados *dados){
    float soma = 0;
    for(int i = 0; i < dados->tamanho;i++){
        soma += dados->vetor[i];
    }
    
    return soma/(float)dados->tamanho;
}

float mediana(Dados *dados){
    MergeSort(dados);
    if((dados->tamanho%2) != 0){
        return (float)dados->vetor[(dados->tamanho/2)];
    }
    
    return (dados->vetor[(dados->tamanho/2)-1] + dados->vetor[(dados->tamanho/2)])/2.0;
}

void preencher_dados(Dados *dados){
    for(int i = 0; i < dados->tamanho;i++){
        scanf("%d",&dados->vetor[i]);
    }
}

Dados* inicializa_dados(Dados *dados, int tamanho){
    dados = (Dados*) malloc(sizeof(Dados));
    if(dados == NULL){
        printf("Erro de alocação...");
    }
    dados->ponto = (Ponto*) malloc(sizeof(Ponto));
    dados->vetor = (int*) malloc(tamanho*sizeof(int));
    if(dados->vetor == NULL){
        printf("Erro de alocação...");
    }
    dados->tamanho = tamanho;
    
    preencher_dados(dados);
    dados->ponto->x = media(dados);
    dados->ponto->y = moda(dados);
    dados->ponto->z = mediana(dados);
    
    return dados;
}


float distancia(Ponto *ponto1, Ponto *ponto2){
    return sqrt(pow((ponto1->x-ponto2->x),2)+pow(ponto1->y-ponto2->y,2)+pow(ponto1->z-ponto2->z,2));
}


void printa_dados(Dados *dados){
    printf("[");
    for(int i = 0; i < dados->tamanho; i++){
        if (i != dados->tamanho-1){
            printf("%d, ",dados->vetor[i]); 
        }else{
            printf("%d",dados->vetor[i]);
        }
    }
    printf("]\n");
}
