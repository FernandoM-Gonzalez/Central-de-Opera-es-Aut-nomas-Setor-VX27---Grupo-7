#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <locale.h>

#define TAM_LISTA 100

struct Operador{
    int idOperador,qtdOperacoes;
    char nomeOperador[100],setorOperador[6],nivelOperacional[20],statusOperador[10];
};

struct Equipamento{
    int idOperadorEquipamento, nivelPrioridade;
    char idEquipamento[100], tipoEquipamento[20], setorEquipamento[6], estadoOperacional[10];
};

struct Operador listaOperadores[TAM_LISTA];
struct Equipamento listaEquipamentos[TAM_LISTA];

int qtdOperadoresCadastrados = 0;

int verificadorNomeRepetido(char nome[]){
    //Verifica se tem algum nome igual na Lista de Operadores já Cadastrados
    for(int i = 0; i < qtdOperadoresCadastrados; i++){
        if(strcmp(nome, listaOperadores[i].nomeOperador) == 0){
            return 1;
        }
    }
    return 0;
}

int verificadorPadraoSetor(char setor[]){
    //Verifica o Tamanho da String
    if(strlen(setor) != 4){
        return 0;
    }

    //Verifica se os 2 primeiros digitos são Caracteres
    if(isdigit(setor[0]) || isdigit(setor[1])){
        return 0;
    }

    //Verifica se os 2 ultimos digitos são Digitos Numéricos
    if(!isdigit(setor[2]) || !isdigit(setor[3])){
        return 0;
    }
    return 1;
}

void cadastroOperador(){
    int verificador = 0,idOperadorTemporario = 0,qtdOperacoesTemporario = 0;
    char nomeOperadorTemporario[100],setorOperadorTemporario[6], nivelOperacionalTemporario[20],statusOperadorTemporario[10];

    do{
        printf("Nome: ");
        fgets(nomeOperadorTemporario,100,stdin);

        nomeOperadorTemporario[strcspn(nomeOperadorTemporario, "\n")] = '\0';

        verificador = verificadorNomeRepetido(nomeOperadorTemporario);

        if(verificador == 1){
            printf("Esse nome já foi cadastrado. Tente Novamente.\n\n");
        }
    }while(verificador == 1);

    verificador = 0;

    do{
        printf("Um setor é composto por 2 Caracteres e 2 Números | Exemplo: TI01 \n");

        printf("Setor: ");
        fgets(setorOperadorTemporario,6,stdin);

        setorOperadorTemporario[strcspn(setorOperadorTemporario, "\n")] = '\0';

        verificador = verificadorPadraoSetor(setorOperadorTemporario);

        if(verificador == 0){
            printf("Padrão de Setor Invalido. Tente Novamente.\n\n");
        }
    }while(verificador == 0);
}

int main(){
    setlocale(LC_ALL, "Portuguese");

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
