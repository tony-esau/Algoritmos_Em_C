#include <stdio.h>
#include <stdlib.h>

//Função para printar vetores formatado
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

//Faz o ajuntameneto dos subvetores, produtos da recursão.
void Merge(int *vetor, int inicio, int meio, int fim){
    int *vetor_auxiliar, inicio_1, inicio_2,tamanho,i,j,k;
    int fim_1 = 0, fim_2 = 0;
    tamanho = fim-inicio+1;
    inicio_1 = inicio;
    inicio_2 = meio+1;
    vetor_auxiliar = (int*) (malloc(tamanho*sizeof(int)));
    
    if(vetor_auxiliar == NULL){
        printf("Erro de Memória...");
        exit(1);
    }else{
        for(i = 0; i < tamanho; i++){
            if(!fim_1 && !fim_2){
                if(vetor[inicio_1] < vetor[inicio_2]){
                    vetor_auxiliar[i] = vetor[inicio_1];
                    inicio_1++;
                }else{
                    vetor_auxiliar[i] = vetor[inicio_2];
                    inicio_2++;
                }
                //Se um dos vetores acabou.
                if(inicio_1 > meio) fim_1 = 1;
                if(inicio_2 > fim) fim_2 = 1;

            }else{
                /*Se um dos vetores acabou então basta copiar o restante do 
                vetor não finalizado, pois ele já está ordenado.*/
                if(!fim_1){
                    vetor_auxiliar[i] = vetor[inicio_1];
                    inicio_1++;
                }else{
                    vetor_auxiliar[i] = vetor[inicio_2];
                    inicio_2++;
                }      
            }
        }
    }
    /*
    Se deseja ver o juntamento dos subvetores descomente a linha abaixo.
    printa_vetor(vetor_auxiliar,tamanho);
    */
    for(j = 0, k = inicio ; j < tamanho; j++, k++){
        vetor[k] = vetor_auxiliar[j];
    }
    free(vetor_auxiliar);
}

/*
Algoritmo MergeSort
Complexidade: O(n*log(n)).
*/
void MergeRecursive(int *vetor, int inicio, int fim){
    int meio;
    /*Quebra o vetor ao meio até restar somente um elemento(caso base). 
    Primeiro sai quebrando a primeira metade, depois a segunda, por último 
    chama Merge para fazer os ajuntamentos.*/
    if(inicio < fim){
        meio = (int)((inicio+fim)/2);
        MergeRecursive(vetor,inicio,meio);
        MergeRecursive(vetor,meio+1,fim);
        Merge(vetor,inicio,meio,fim);
    }
}

//Função auxiliar para não ficar passando inicio e fim manualmente.
void MergeSort(int *vetor, int tamanho){
    int fim = tamanho-1;
    int inicio = (fim-tamanho+1);
    MergeRecursive(vetor,inicio,fim);
}

int main(){
    int tamanho;

    printf("Digite o tamanho do Vetor:\n");
    scanf("%d",&tamanho);

    int *vetor = (int*)(malloc(tamanho*sizeof(int)));

    //Programação defensiva
    if(vetor == NULL){
        printf("Erro de Memória...");
        exit(1);
    }

    printf("Digite os valores:\n");
    for (int i = 0; i < tamanho; i++){
       scanf("%d",&vetor[i]); 
    }

    system("cls");

    printf("Vetor digitado:\n");
    printa_vetor(vetor,tamanho);

    MergeSort(vetor,tamanho);

    printf("Vetor ordenado:\n");
    printa_vetor(vetor,tamanho);

    return 0;
}