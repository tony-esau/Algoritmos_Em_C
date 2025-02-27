/******************************************************************************
Implemente um simulador de ambiente de medição de desempenho para o mundo de aspirador de
pó representado na Figura 2.2 e especificado na página 38. Sua implementação deve ser modular, de
forma que os sensores, os atuadores e as características do ambiente (tamanho, forma, localização da
sujeira etc.) possam ser alterados com facilidade. (Inteligência Artificial, Russel).
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void limpa_tela(){
    #ifdef _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

//uma posição pode ser aspiravel = poeira/m^2, naspiravel = -1 
typedef struct ambiente{
    int **matriz;
    int linhas;
    int colunas;
}Ambiente;

Ambiente* aloca_ambiente(int linhas, int colunas){
    
    //Aloca ambiente.
    Ambiente *ambiente = (Ambiente*) malloc(sizeof(Ambiente));  
    
    //Aloca matriz de ambiente.
    ambiente->matriz = (int **)(malloc(sizeof(int *) * linhas));
    for (int i = 0; i < linhas; i++) {
        ambiente->matriz[i] = (int *)(malloc(sizeof(int) * colunas));
    }
    
    ambiente->linhas = linhas;
    ambiente->colunas = colunas;
    
    return ambiente;
}

void printar_ambiente(Ambiente *ambiente){
    for(int i = 0; i<ambiente->linhas;i++){
        for(int j = 0; j<ambiente->colunas;j++){
            if(ambiente->matriz[i][j] == -1){
                printf("*");
            }else{
                printf("[ ]");
            }
        }
        printf("\n");
    }
}

/*
    Se o usuário deseja que a matriz represente melhor o ambiente
    ou porque existe um obstáculo em dada posição.
*/
void determinar_invalidas(Ambiente *ambiente){
    int verificador = 1;
    int linha;
    int coluna;
    
    while(verificador != 0){
        printf("Estado atual:\n");
        printar_ambiente(ambiente);
        printf("Deseja dizer alguma posição não acessível no ambiente?(1:sim/0:não)\n");
        scanf("%d",&verificador);
        
        if(verificador == 0){
            break;
        }
        
        printf("Digite a linha:\n");
        scanf("%d",&linha);
        printf("Digite a coluna:\n");
        scanf("%d",&coluna);
        
        ambiente->matriz[linha][coluna] = -1;
        
        limpa_tela();
    }
}

void define_sujeira(Ambiente *ambiente){
    int contador = 0;
    int numero_aleatorio = rand() % (ambiente->linhas * ambiente->colunas);
    int linha;
    int coluna;
    
    while(contador < numero_aleatorio){
        linha = rand() % ambiente->linhas;
        coluna = rand() % ambiente->colunas;
        if(ambiente->matriz[linha][coluna] == 0){
            ambiente->matriz[linha][coluna] = (rand() % 3 + 1);
             contador++;
        }
    }
}

void inicializa_ambiente(Ambiente *ambiente){
    int linhas;
    int colunas;
    
    for(int i = 0; i<ambiente->linhas;i++){
        for(int j = 0; j<ambiente->colunas;j++){
            ambiente->matriz[i][j] = 0;
        }
    }
    
    determinar_invalidas(ambiente);
    
    define_sujeira(ambiente);
    
}

int main(){
    return 0;
}
