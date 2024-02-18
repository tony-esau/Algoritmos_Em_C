#include <stdio.h>
#include <stdlib.h>

//Estrutura de Dados.
typedef struct Dados_de_No{
    int chave;
}Dados;

//Estrutura que define um n�.
typedef struct No_de_pilha{
    Dados *dados;
    struct No_de_pilha *ptr_abaixo;
}No;

//Cria a pilha, inicialmente um ponteiro para NULL.
No* cria_pilha(){
    No *auxiliar = NULL;
    return auxiliar;
}

//Função de Empilhar um nó.
No* empilhar(No *topo, int a){
    No* novo = (No*)malloc(sizeof(Dados));
    if(novo != NULL){
        novo->ptr_abaixo = topo;
        novo->dados->chave = a;
        return novo;
    }else{
        printf("Falha na alocação de memória!");
        retrn 
    }
}

//Função de desempilhar um nó.
No* desempilhar(No **ptr_topo){
    No* remover = NULL; 

    if(*ptr_topo != NULL){
        No *remover = *ptr_topo;
        *ptr_topo = remover->ptr_abaixo;
    }else{
        printf("\nAinda nao ha nos na pilha.\n");
    }
}


int main(){

    No *topo;
    No **ptr_topo = &topo;

    return 0;
}