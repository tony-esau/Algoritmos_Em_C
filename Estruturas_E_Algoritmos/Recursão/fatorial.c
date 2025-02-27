//Autor: Tony Esaú de Oliveira© CC
//26/02/2024
/*
Implementa um algoritmo simples de cálculo de fatorial com 
base no livro Estruturas de Dados e Seus Algoritmos de Szwarcfiter.
*/

#include <stdio.h>

int fatorial(int n){
	if(n <= 1){
		return 1;
	}else{
		return n*fatorial(n-1);
	}
}

int main(){
	int n;
	printf("Digite qual valor n de Fibonacci deseja verificar:\n");
	scanf("%d",&n);

	int fatorial_n = fatorial(n);

	printf("O fatorial de %d é: %d.\n",n,fatorial_n);
}
