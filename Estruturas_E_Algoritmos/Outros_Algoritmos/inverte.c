//Autor: Tony Esaú de Oliveira© CC
//26/02/2024
/*
Implementa um algoritmo simples de inversão de vetor com
base no livro Estruturas de Dados e Seus Algoritmos de Szwarcfiter.
*/
#include <stdio.h>
#include <stdlib.h>

//Função piso.
int piso(double x) {
    int inteiro = (int)x;
    return (x < 0 && x != inteiro) ? inteiro - 1 : inteiro;
}

//Printa no terminal o vetor formatado.
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

//Implementa a inversão trocando os valores até piso(tamanho/2).
void inverte_vetor(int *vetor, int tamanho){
	int auxiliar;
	for(int i = 0; i < piso(tamanho/2);i++){
		auxiliar = vetor[i];
		vetor[i] = vetor[tamanho-i-1];
		vetor[tamanho-i-1] = auxiliar;
	}
}

int main(){
	int n;
	printf("Digite o tamanho do vetor:\n");
	scanf("%d",&n);

	int *vetor = (int*) malloc(n*sizeof(int));


	printf("Digite os valores:\n");
	for(int i = 0; i < n; i++){
		scanf("%d",&vetor[i]);
	}

	printa_vetor(vetor, n);

	inverte_vetor(vetor,n);

	printf("Vetor invertido:\n");

	printa_vetor(vetor, n);


}
