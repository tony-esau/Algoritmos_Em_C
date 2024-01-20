#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

void printa_cpf(char *cpf){
    printf("O CPF foi validado:\n");
    int i, j = 0;
    for(i = 0; i < 14 ; i++){
        if((i == 3) || (i == 7)){
            printf("%c",'.');
        }else if(i == 11){
            printf("%c",'-');
        }else{
            printf("%c",cpf[j]);
            j++;
        }
    }
    printf("\n");
}

int valida_cpf(char *cpf){
    int auxiliar[11];
    for(int i = 0; i < 11; i++){
        if(isdigit(cpf[i])){
            auxiliar[i] = (cpf[i] - 48);
        }
    }

    int digitos_iguais = 1;
    for(int i = 0; i < 10; i++){
        if(auxiliar[i] == auxiliar[i+1]){
            digitos_iguais = 1;
        }else{
            digitos_iguais = 0;
        } 
    }

    if(digitos_iguais == 1){
        printf("CPF inválido.\n");
        return 0;
    }

    int soma = 0, navegador1= 10, resto;

    for(int i = 0; i < 9; i++){
        soma += (auxiliar[i] * navegador1);
        navegador1--;
    }

    resto = soma % 11;

    if((resto == 0) || (resto == 1)){
        if(auxiliar[9] != 0){
            printf("CPF inválido.\n");
            return 0;
        }
    }else{
        if(auxiliar[9] != (11-resto)){
            printf("CPF inválido.\n");
            return 0;
        }
    }

    soma = 0;
    int navegador2 = 11;

    for(int i = 0; i < 10; i++){
        soma += (auxiliar[i] * navegador2);
        navegador2--;
    }

    resto = soma % 11;

    if((resto == 0) || (resto == 1)){
        if(auxiliar[10] != 0){
            printf("CPF inválido\n");
            return 0;
        }
    }else{
        if(auxiliar[10] != (11-resto)){
            printf("CPF inválido\n");
            return 0;
        }
    }

    return 1;
}

void leitor_cpf(){
    char cpf[11];
    fgets(cpf,12,stdin);
    int situacao = valida_cpf(cpf);
    if(situacao == 1){
        printa_cpf(cpf);
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    int verificador = 1;

    do{
        printf("Digite seu CPF (apenas números):\n");
        leitor_cpf();

        printf("Deseja continuar? (1: Sim | 0 ou outro: Não)");
        scanf("%d",&verificador);
        fflush(stdin);
    }while(verificador == 1);
    
    return 0;
}