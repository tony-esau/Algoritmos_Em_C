//Autor: Tony Esaú de Oliveira© CC
//22/09/2024
//Implementa a visualização de um calendário do mês atual no terminal.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Calcula o dia da semana atual com base no algoritmo de Zeller.
int dia_zeller(int dia, int mes, int ano) {
    if (mes == 1) {
        mes = 13;
        ano--;
    }
    if (mes == 2) {
        mes = 14;
        ano--;
    }
    int q = dia;
    int m = mes;
    int k = ano % 100;
    int j = ano / 100;
    int h = q + (13 * (m + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j);
    h = h % 7;
    return (h + 6) % 7; // Ajuste para o formato desejado
}

//Verifica quantos dias tem no mês atual.
int dias_no_mes(int mes, int ano) {
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30; // Meses com 30 dias.
    if (mes == 2) { 
        return (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) ? 29 : 28; //Verifica se o ano é bissexto.
    }
    return 31; // Meses com 31 dias.
}

void printar_calendario() {
	const char* nomes_meses[] = {
    	"Janeiro", "Fevereiro", "Março", "Abril",
    	"Maio", "Junho", "Julho", "Agosto",
    	"Setembro", "Outubro", "Novembro", "Dezembro"
	};

	const char* nomes_dias[]={
		"Domingo","Segunda", "Terça-Feira","Quarta_Feira",
		"Quinta-Feira","Sexta-Feira","Sábado"
	};

	const char* nome_dias_abrev[]={
		"Dom","Seg","Ter","Qua","Qui","Sex","Sab"
	};

    time_t tempo;
    struct tm *infotempo;//Guarda informações em formatos diversos sobre temporização.

    time(&tempo); //Recebe o tempo atual em segundos com base no marco definido em sistema.
    infotempo = localtime(&tempo);//Converte esse tempo para uma estrutura tm;

    int calendario[7][7];
    int dia_primeiro = 1;
    int mes_atual = infotempo->tm_mon + 1; // Mês atual.
    int ano_atual = infotempo->tm_year + 1900; // Ano atual, soma 1900 porque é o marco de tempo.

    // Inicializa o calendário.
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            calendario[i][j] = -1;
        }
    }

    // Preenche os dias da semana para imprimir abreviações.
    for (int j = 0; j < 7; j++){
        calendario[0][j] = j;
    }
  
    // Calcula o dia da semana do primeiro dia do mês.
    int dia_semana = dia_zeller(dia_primeiro, mes_atual, ano_atual);
    
    int dias_mes_atual = dias_no_mes(mes_atual,ano_atual);
    
    int contador = 1;

    // Preenche o calendário com os dias.
    for(int i = 1; i < 7; i++){
        for(int j = 0; j<7;j++){
            if( i == 1 && j == dia_semana){
                calendario[i][j] = contador;
                contador++;
            }else if(contador >= 2 && contador <= dias_mes_atual){
                calendario[i][j] = contador;
                contador++;
            }
        }
    }

    int dia_atual = infotempo->tm_mday;
  
    printf("%21s\n",nomes_dias[dia_semana]);
    printf("---------%s %d, %d---------\n",nomes_meses[mes_atual-1],dia_atual,ano_atual);

    // Imprime o calendário.
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (i == 0) {
                printf(" %s ",nome_dias_abrev[j]);
            } else {
                if (calendario[i][j] == -1) {
                    printf("     "); // Espaço para dias não preenchidos (= -1)
                } else {
                    if(calendario[i][j] == infotempo->tm_mday){
                        printf("\033[31m%4d\033[0m ", calendario[i][j]); //Dia de hoje com coloração de terminal.
                    }else{
                        printf("%4d ", calendario[i][j]); //Demais dias.
                    }
                }
            }
        }
        printf("\n");
    }
}

int main() {
    printar_calendario();
    return 0;
}

