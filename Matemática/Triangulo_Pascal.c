//Autor: Tony Esaú de Oliveira© CC
//10/10/2024
//Implementa um algoritmo que printa até a n-ésima linha do triângulo de pascal com o cabeçalho de precisão numérica gmp.
#include <gmp.h>

void fatorial(mpz_t n, mpz_t resultado){
    mpz_set_ui(resultado,1);
    mpz_t i;
    mpz_init_set_ui(i,1);
    
    for(;mpz_cmp(i,n)<=0;mpz_add_ui(i,i,1)){
        mpz_mul(resultado,resultado,i);
    }
    
    mpz_clear(i);
}

void coeficiente_binomial(mpz_t n, mpz_t k, mpz_t resultado){
    mpz_t fat_n, fat_k, nk, fat_nk, auxiliar;
    mpz_inits(fat_n,fat_k, nk, fat_nk, auxiliar, NULL);
    
    mpz_sub(nk, n, k);
    
    fatorial(n, fat_n);
    fatorial(k,fat_k);
    fatorial(nk,fat_nk);
    
    mpz_mul(auxiliar,fat_k,fat_nk);
    
    mpz_div(resultado,fat_n,auxiliar);
    
    mpz_clears(fat_n, fat_k, nk, fat_nk, auxiliar, NULL);
}

void imprime_pascal(int n_linhas){
    
    mpz_t n, k, binomio;
    mpz_inits(n, k, binomio, NULL);
    
    for(int i = 0; i <= n_linhas; i++){
        mpz_set_ui(n,i);
        for(int j = 0; j <= i; j++){
            mpz_set_ui(k,j);
            coeficiente_binomial(n,k,binomio);
            gmp_printf("%Zd ",binomio);
        }
        gmp_printf("\n");
    }
    
}

int main(){
    
    int n = 20;

    //A primeira linha é a linha 0.
    imprime_pascal(n);
    
    return 0;
}
