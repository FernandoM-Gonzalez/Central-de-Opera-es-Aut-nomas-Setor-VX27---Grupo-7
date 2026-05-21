#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LISTA 100

struct Operador{
    int idOperador,qtdOperacoes;
    char nomeOperador[100],setorOperador[4],nivelOperacional[20],statusOperador[10];
};

struct Equipamento{
    int idOperadorEquipamento, nivelPrioridade;
    char idEquipamento[100], tipoEquipamento[20], setorEquipamento[4], estadoOperacional[10]
};

struct Operador listaOperadores[TAM_LISTA];
struct Equipamento listaEquipamentos[TAM_LISTA];

int qtdOperadoresCadastrados = 0;

int verificadorNomeRepetido(char nome[]){
    if(qtdOperadoresCadastrados != 0){
        for(int i = 0; i < qtdOperadoresCadastrados; i++){
            if(strcmp(nome, listaOperadores[i].nomeOperador) == 0){
                return 1;
            }
        }
    }
    return 0;
}

void cadastroOperador(){
    int verificador = 0;
    int idOperadorTemporario,qtdOperacoesTemporario;
    char nomeOperadorTemporario[100],setorOperadorTemporario[4],nivelOperacionalTemporario[20],statusOperadorTemporario[10];

    do{
        printf("Nome: ");
        fgets("%s",100,&nomeOperadorTemporario);

        verificador = verificadorNomeRepetido(nomeOperadorTemporario);
    }while(verificador == 0);
}

int main(){




    return 0;
}
