#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>// Define as wide_characters.
#include <wctype.h>
#include <io.h>// Define unicode "_O_U16TEXT"
#include <fcntl.h>// _setmode

//Define uma função defensiva  que só aceita espaços ou caracteres alfabéticos (acentuadas ou não).
void leitor_caractere(wchar_t *string, int tamanho){
    int verificador = 0;
    do
    {
        fgetws(string,tamanho,stdin);
        //Retira o \n vindo do teclado.
        for(int i = 0; string[i] != L'\0'; i++){
            if(string[i] == L'\n'){
                string[i] = '\0'; 
            }
        }

        for(int i = 0;  string[i] != L'\0'; i++){
            if( (iswalpha(string[i]) != 0) || (iswspace(string[i]) != 0) ){
                verificador = 1;
            }else{
                wprintf(L"Digite somente letras ou espaços.\n");
                verificador = 0;
                break;
            }
        }  
    }while(verificador==0);
}



int main(){
    //Define as entradas e saídas padrão como Unicode "_O_U16TEXT".
    _setmode(_fileno(stdin),_O_U16TEXT);
    _setmode(_fileno(stdout),_O_U16TEXT);
    _setmode(_fileno(stderr),_O_U16TEXT);

    wchar_t frase[100];
    leitor_caractere(frase,100);
    wprintf(L"A string digitada é: %ls.",frase);
}