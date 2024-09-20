#include <stdio.h>
#include <stdlib.h>
#define memoria 5

typedef struct No_cabeca{
    int vetor[memoria];
    int frente;
    int retaguarda;
}Sentinela;

void cria_fila(Sentinela *No_cabeca){
    No_cabeca->frente = -1;
    No_cabeca->retaguarda = -1;
}

int fila_vazia(Sentinela *No_cabeca){
    if((No_cabeca->frente == -1) && (No_cabeca->retaguarda == -1)){
        return 1;
    }else{
        return 0;
    } 
}

int fila_cheia(Sentinela *No_cabeca){
    if(((No_cabeca->retaguarda + 1) % memoria) == (No_cabeca->frente)){
        return 1;
    }else{
        return 0;
    }
}

void inserir_fila(Sentinela *No_cabeca){
    if(fila_cheia(No_cabeca) == 1){
        printf("A fila est� cheia");
    }else{
        if(No_cabeca->frente == -1){
            No_cabeca->frente+=2;
        }
        if(No_cabeca->retaguarda == -1){
            No_cabeca->retaguarda++;
        }
        No_cabeca->retaguarda = (No_cabeca->retaguarda + 1) % memoria;
        int auxiliar;
        printf("Digite a chave:");
        scanf("%d",&auxiliar);
        fflush(stdin);
        No_cabeca->vetor[No_cabeca->retaguarda] = auxiliar;
    }
}

void remover_fila(Sentinela *No_cabeca){
    if(fila_vazia(No_cabeca) == 1){
        printf("A fila ainda n�o tem elementos");
    }else{
        if(No_cabeca->frente == No_cabeca->retaguarda){
            No_cabeca->frente = -1;
            No_cabeca->retaguarda = No_cabeca->frente;
        }else{
            No_cabeca->frente = (No_cabeca->frente + 1) % memoria;
        }
    }
}

void imprime_fila(Sentinela No_cabeca){
    Sentinela *ptr_auxiliar = &No_cabeca;
    if(fila_vazia(ptr_auxiliar) == 0){
        printf("\nA lista se encontra na seguinte configura��o:\n");
        if(No_cabeca.frente ==  No_cabeca.retaguarda){
            printf("\n[%d]\n",No_cabeca.vetor[No_cabeca.frente]);
        }else{
            printf("[");
            while(No_cabeca.frente != No_cabeca.retaguarda){
                printf("%d,",No_cabeca.vetor[No_cabeca.frente]);
                No_cabeca.frente = ((No_cabeca.frente + 1) % memoria);
            }
            printf("%d]\n",No_cabeca.vetor[No_cabeca.retaguarda]);
        }
    }else{
        printf("Ainda n�o h� elementos na fila.");
    }
}

void imprime_menu(){
    printf("\n----------Op��es----------\n");
    printf("1-Inserir...................\n");
    printf("2-Remover...................\n");
    printf("3-Imprimir..................\n");
    printf("4-Limpar Tela...............\n");
    printf("5-Sair......................\n");
}

int main(){
    Sentinela fila;
    Sentinela *ptr_fila = &fila;
    cria_fila(ptr_fila);
    int verificador;

    while(verificador != 5){
        imprime_menu();
        scanf("%d",&verificador);
        fflush(stdin);

        if(verificador == 1){
            inserir_fila(ptr_fila);
        }else if(verificador == 2){
            remover_fila(ptr_fila);
        }else if(verificador == 3){
            system("cls");
            imprime_fila(fila);
        }else if(verificador == 4){
            system("cls");
        }else if(verificador == 5){
            exit(1);
        }else{
           printf("Comando inexistente."); 
        }
    }
   return 0; 
}
