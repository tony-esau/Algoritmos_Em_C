#include <stdio.h>
#include <stdlib.h>
#include "cabecalho.h"

/*Para efeito de teste o algoritmo toma 3 conjuntos de dados, cada qual com seu
ponto correspondente (x:média, y:moda e z:mediana) e compara a distância no espaço
com a origem, o objetivo final é dizer qual dos conjuntos é o mais próximo da origem
do espaço cartesiano.*/
int main(){
    int n = 3;
    Dados *dados[n];
    int tamanho;
    
    for(int i = 0; i < n; i++){
        printf("Digite o tamanho do conjunto %d:\n",i);
        scanf("%d",&tamanho);
        limpa_tela();
        printf("Digite os valores do conjunto %d:\n",i);
        dados[i] = inicializa_dados(dados[i],tamanho);
        limpa_tela();
    }
    
    for(int i = 0; i < n; i++){
        printf("Conjunto %d:",i);
        printa_dados(dados[i]);
        printf("Coordenadas do seu ponto:\n");   
        printf("[x:%f\n",dados[i]->ponto->x);
        printf("y:%f\n",dados[i]->ponto->y);
        printf("z:%f]\n",dados[i]->ponto->z);
    }
    
    //Origem do espaço cartesiano.
    Ponto *origem = (Ponto*)malloc(sizeof(Ponto));
    origem->x = 0;
    origem->y = 0;
    origem->z = 0;
    
    float *auxiliar = (float*) malloc(n*sizeof(float));
    
    for(int i = 0; i < n; i++){
        auxiliar[i] = distancia(dados[i]->ponto,origem);
    }
    
    int menor = auxiliar[0];
    for(int i = 0; i < n-1;i++){
        if(auxiliar[i+1]<auxiliar[i]){
            menor = i+1;
        }
    }
    
    printf("O conjunto de menor distância é %d, d = %f.",menor,auxiliar[menor]);
    
    return 0;
}
