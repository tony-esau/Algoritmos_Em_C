#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>// Define as wide_characters.
#include <wctype.h>
#include <io.h>// Define unicode "_O_U16TEXT"
#include <fcntl.h>// _setmode


//Define uma função defensiva  que só aceita inteiros.
void leitor_inteiro(int *numero){
    int verificador = 0;
    wchar_t auxiliar[1000];
    do
    {
        fgetws(auxiliar,1000,stdin);
        //Retira o \n vindo do teclado.
        for(int i = 0; auxiliar[i] != L'\0'; i++){
            if(auxiliar[i] == L'\n'){
                auxiliar[i] = '\0'; 
            }
        }

        for(int i = 0;  auxiliar[i] != L'\0'; i++){
            if( iswdigit(auxiliar[i]) != 0){
                verificador = 1;
            }else{
                wprintf(L"Digite uma sequência numérica válida.\n");
                verificador = 0;
                break;
            }
        }  
    }while(verificador==0);
    *numero = (int) wcstol(auxiliar,NULL,10);
}



int main(){
    //Define as entradas e saídas padrão como Unicode "_O_U16TEXT".
    _setmode(_fileno(stdin),_O_U16TEXT);
    _setmode(_fileno(stdout),_O_U16TEXT);
    _setmode(_fileno(stderr),_O_U16TEXT);

    int num;
    int *ptr_num = &num;
    leitor_inteiro(ptr_num);
    wprintf(L"O número digitado foi: %d.",num);
}