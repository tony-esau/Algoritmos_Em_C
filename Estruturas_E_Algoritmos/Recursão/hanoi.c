//Autor: Tony Esaú de Oliveira© CC
//26/02/2024
/*
  Implementa um algoritmo simples que resolve o problema da Torre de Hanoi 
  com n discos, com base no livro Estruturas de Dados e Seus Algoritmos de 
  Szwarcfiter. A complexidade do algortitmo recursivo é de O(2^n), ou seja,
  para valores de n enormes, o tempo é horrível.
*/

#include <stdio.h>
#include <stdlib.h>

int passos = 0;

typedef struct disco{
    int tamanho;
    struct disco *ptr_disco;
}Disco;

typedef struct tabuleiro{
    Disco *topo_disco;
}Tabuleiro;

void empilhar(Disco **topo_disco, int tamanho) {
    Disco *novo_disco = (Disco*)malloc(sizeof(Disco));
    novo_disco->tamanho = tamanho;
    novo_disco->ptr_disco = *topo_disco;
    *topo_disco = novo_disco;
}

void inicializa_jogo(Disco **topo_disco, int n){
    for(int i = n; i > 0; i--){
        empilhar(topo_disco,i);
    }
}

void printar(Tabuleiro *tabuleiro, int n) {
    // Determinar a largura máxima necessária para impressão.
    int largura_maxima = n * 2 + 1;  // Largura do maior disco (n) * 2 + espaço para caracteres.
    int largura_total = (largura_maxima * 3) + 6;  // 3 torres + espaços entre elas.
    
    // Linha superior.
    for (int i = 0; i < largura_total; i++) {
        printf("=");
    }
    printf("\n");
    
    // Para cada linha, de cima para baixo.
    for (int i = 0; i < n; i++) {
        // Para cada uma das torres.
        for (int j = 0; j < 3; j++) {
            Disco *atual = tabuleiro[j].topo_disco;
            
            // Contar discos na torre j.
            int num_discos = 0;
            Disco *auxiliar = atual;
            while (auxiliar != NULL) {
                num_discos++;
                auxiliar = auxiliar->ptr_disco;
            }
            
            // Verificar se esta linha deve mostrar um disco ou apenas o poste.
            if (i < (n - num_discos)) {
                // Mostrar apenas o poste.
                int espacos_laterais = largura_maxima / 2;
                for (int k = 0; k < espacos_laterais; k++) {
                    printf(" ");
                }
                printf("|");
                for (int k = 0; k < espacos_laterais; k++) {
                    printf(" ");
                }
            } else {
                // Mostrar um disco.
                int pos_na_pilha = i - (n - num_discos);
                
                auxiliar = atual;
                for (int k = 0; k < pos_na_pilha; k++) {
                    if (auxiliar != NULL) {
                        auxiliar = auxiliar->ptr_disco;
                    }
                }
                
                if (auxiliar != NULL) {
                    int tamanho_disco = auxiliar->tamanho * 2 - 1; // Para manter proporção.
                    int espacos = (largura_maxima - tamanho_disco) / 2;
                    
                    // Espaços à esquerda.
                    for (int k = 0; k < espacos; k++) {
                        printf(" ");
                    }
                    
                    // Disco.
                    for (int k = 0; k < tamanho_disco; k++) {
                        printf("-");
                    }
                    
                    // Espaços à direita.
                    for (int k = 0; k < espacos; k++) {
                        printf(" ");
                    }
                } else {
                    // Nunca deveria chegar aqui, mas por segurança...
                    int espacos_laterais = largura_maxima / 2;
                    for (int k = 0; k < espacos_laterais; k++) {
                        printf(" ");
                    }
                    printf("|");
                    for (int k = 0; k < espacos_laterais; k++) {
                        printf(" ");
                    }
                }
            }
            printf("  ");
        }
        printf("\n");
    }
    
    for (int i = 0; i < largura_total; i++) {
        printf("=");
    }
    printf("\n");
    
    int espacos_base = (largura_maxima - 1) / 2;
    printf("%*sA%*s", espacos_base, "", espacos_base, "");
    printf("  ");
    printf("%*sB%*s", espacos_base, "", espacos_base, "");
    printf("  ");
    printf("%*sC%*s", espacos_base, "", espacos_base, "");
    printf("\n\n");
}

//Move um disco para outro poste, trocando os ponteiros.
void mover(Tabuleiro *tabuleiro, int A, int B){
    Disco *auxiliar = tabuleiro[A].topo_disco;
    tabuleiro[A].topo_disco = tabuleiro[A].topo_disco->ptr_disco;

    auxiliar->ptr_disco = tabuleiro[B].topo_disco;
    tabuleiro[B].topo_disco = auxiliar;
}

/*
	Rescolve recursivamente o problema das torres, utilizando um poste 
	auxilixar. Resolve o problema para n e depois para n-1 e assim
	sucessivamente.
*/
void hanoi(Tabuleiro *tabuleiro, int n, int A, int B, int C, int total_discos){
    if (n > 0) {
        hanoi(tabuleiro, n - 1, A, C, B, total_discos); 
        mover(tabuleiro, A, C);
        passos++;
        printf("Move disco %d de %c para %c\n", tabuleiro[C].topo_disco->tamanho, 'A' + A, 'A' + C);
        printar(tabuleiro, total_discos);
        hanoi(tabuleiro, n - 1, B, A, C, total_discos); 
    }
}

void resolver_hanoi(int n, Tabuleiro *tabuleiro){
    hanoi(tabuleiro, n, 0, 1, 2, n);
}

void inicializar(){
    int n;
    Tabuleiro *tabuleiro = (Tabuleiro*) malloc(3*sizeof(Tabuleiro));
    for(int i = 0; i < 3; i++){
        tabuleiro[i].topo_disco = NULL;
    }
    printf("Digite o número de peças:\n");
    scanf("%d",&n);
    inicializa_jogo(&(tabuleiro[0].topo_disco), n);

    printf("Tabuleiro inicialmente:\n");
    printar(tabuleiro,n);

    resolver_hanoi(n,tabuleiro);

    printf("Número de Passos: %d.\n",passos);
}

int main(){
    inicializar();
    return 0;
}
