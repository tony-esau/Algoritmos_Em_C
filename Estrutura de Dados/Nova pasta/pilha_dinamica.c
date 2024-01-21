#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Dados_de_No{
    char nome[50];
    int chave;
}Dados;

typedef struct No_de_pilha{
    Dados *dados;
    struct No_de_pilha *ptr_abaixo;
}No;

No* cria_pilha(){
    No *auxiliar = NULL;
    return auxiliar;
}

No* ler_dados(No *topo){
    topo = (No*) malloc(sizeof(No));
    if(topo == NULL){
        printf("N�o foi possivel alocar mem�ria para o n�.");
        return NULL;
    }
    topo->dados = (Dados*) malloc(sizeof(Dados));
     if(topo == NULL){
        printf("N�o foi possivel alocar mem�ria para os dados do n�.");
        return NULL;
    }

    printf("Digite o nome:");
    fgets(topo->dados->nome,50,stdin);
    for(int i = 0; (topo->dados->nome[i]) != '\0'; i++){
        if(topo->dados->nome[i] == '\n'){
            topo->dados->nome[i] = '\0';
            break;
        } 
    }

    printf("Digite uma chave:");
    scanf("%d",&(topo->dados->chave));

    return topo;
}

void push(No **ptr_topo){
    No* auxiliar = ler_dados(*ptr_topo);
    if(auxiliar == NULL){
        exit(1);
    }else{
        auxiliar->ptr_abaixo = *ptr_topo;
        *ptr_topo = auxiliar;
    }
}

void pop(No **ptr_topo){
    if(*ptr_topo != NULL){
        No *auxiliar = *ptr_topo;
        *ptr_topo = auxiliar->ptr_abaixo;
        free(auxiliar);
    }else{
        printf("Ainda n�o h� n�s na pilha.\n");
    }
}

void imprime_pilha(No *topo){
    if(topo == NULL){
        printf("Ainda n�o h� n�s na pilha.\n");
    }else{
        int i = 0;
        while(topo != NULL){
            if(i == 0 && ((topo->ptr_abaixo) != NULL)){
                printf("[Nome:%s. <-- Topo\n",topo->dados->nome);
                printf("Chave:%d.]\n",topo->dados->chave);
                printf("   |   \n");
                printf("   v   \n");
            }else if(i == 0 && ((topo->ptr_abaixo) == NULL)){
                printf("[Nome:%s. <-- Topo\n",topo->dados->nome);
                printf("Chave:%d.]\n",topo->dados->chave);
            }else if((topo->ptr_abaixo) == NULL){
                printf("[Nome:%s.\n",topo->dados->nome);
                printf("Chave:%d.]\n",topo->dados->chave);
            }else{
                printf("[Nome:%s.\n",topo->dados->nome);
                printf("Chave:%d.]\n",topo->dados->chave);
                printf("   |   \n");
                printf("   v   \n");
            }
            i++;
            topo = topo->ptr_abaixo;
        }   
    }
}

void imprime_menu(){
    printf("----------Op��es----------\n");
    printf("1-Empilhar................\n");
    printf("2-Desempilhar.............\n");
    printf("3-Imprimir Pilha..........\n");
    printf("4-Limpar Tela.............\n");
    printf("5-Sair do Programa........\n");
}

int main(){
    setlocale(LC_ALL,"Portuguese");

    No *topo = NULL;
    No **ptr_topo = &topo;

    int verificador;
    printf("Deseja criar uma pilha? (1:Sim|0 ou outro:N�o)\n");
    scanf("%d",&verificador);
    if(verificador == 1){
        topo = cria_pilha();
    }else{
        printf("Obrigado por utilizar...");
        exit(1);
    }

    do{
        imprime_menu();
        printf("Digite a op��oo:\n");
        scanf("%d",&verificador);
        fflush(stdin);

        if(verificador == 1){
            push(ptr_topo);
        }else if(verificador == 2){
            pop(ptr_topo);
        }else if(verificador == 3){
            imprime_pilha(topo);
        }else if(verificador == 4){
            system("cls"); //"clear" em ambientes Linux
        }else if(verificador == 5){
            printf("Obrigado por utilizar...");
            exit(1);
        }else{
            printf("Op��o inv�lida\n");
        }

    }while(verificador != 5);

    return 0;
}