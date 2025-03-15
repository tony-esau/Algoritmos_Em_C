//Autor: Tony Esaú de Oliveira© CC
//15/03/2025
/*
Implementa um algoritmo simples que calcula recursivamente
o n-ésimo termo da sequência de fibonacci. A complexidade é
O(2^n) devido a árvore de recursão redundante.
*/
#include <stdio.h>

int fibonacci(int n){
    if(n == 0 || n == 1){
        return n;
    }
    
    return fibonacci(n-1)+fibonacci(n-2);
}

int main()
{
    printf("%d",fibonacci(8));

    return 0;
}
