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
    char idEquipamento[100], tipoEquipamento[20], setorEquipamento[4], estadoOperacional[10];
};

struct Operador listaOperadores[TAM_LISTA];
struct Equipamento listaEquipamentos[TAM_LISTA];

int qtdOperadoresCadastrados = 0;

int verificadorNomeRepetido(char nome[]){
    for(int i = 0; i < qtdOperadoresCadastrados; i++){
        if(strcmp(nome, listaOperadores[i].nomeOperador) == 0){
            return 1;
        }
    }
    return 0;
}

void cadastroOperador(){
    int verificador = 0,idOperadorTemporario = 0,qtdOperacoesTemporario = 0;
    char nomeOperadorTemporario[100],setorOperadorTemporario[4],nivelOperacionalTemporario[20],statusOperadorTemporario[10];

    // Verificação de nome repetido
    do{
        printf("Nome: ");
        fgets(nomeOperadorTemporario,100,stdin);

        nomeOperadorTemporario[strcspn(nomeOperadorTemporario, "\n")] = '\0';

        verificador = verificadorNomeRepetido(nomeOperadorTemporario);

        if(verificador == 1){
            printf("Esse nome ja foi cadastrado. Tente Novamente.\n\n");
        }
    }while(verificador == 1);

}

int main(){
    struct Operador opOriginal = {
        101,
        42,
        "Carlos Silva",
        "TI",
        "Pleno",
        "Ativo"
    };

    listaOperadores[0] = opOriginal;
    qtdOperadoresCadastrados = 1;

    cadastroOperador();

    return 0;
}
