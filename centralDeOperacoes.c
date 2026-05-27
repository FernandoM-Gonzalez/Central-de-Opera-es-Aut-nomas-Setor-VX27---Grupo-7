#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <locale.h>

#define TAM_LISTA_OPERADORES 50
#define TAM_LISTA_EQUIPAMENTOS 150

struct Operador{
    int idOperador,qtdOperacoes;
    char nomeOperador[70],setorOperador[10],nivelOperacional[20],statusOperador[10];
};

struct Equipamento{
    int idOperadorEquipamento, nivelPrioridade;
    char idEquipamento[100], tipoEquipamento[20], setorEquipamento[6], estadoOperacional[10];
};

struct Informacoes{
    int qtdOperadoresCadastrados;
    struct Operador listaOperadores[TAM_LISTA_OPERADORES];
    struct Equipamento listaEquipamentos[TAM_LISTA_EQUIPAMENTOS];
};

void limpaBuffer(void){
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

struct Informacoes criarBancoDeDados(){
    struct Informacoes info = {0};
    return info;
}

int verificadorNomeRepetido(char nome[], struct Informacoes *info){
    //Verifica Tamanho da String
    if(strlen(nome) == 0 || strlen(nome) > 70){
            return 1;
    }

    //Verifica se tem algum nome igual na Lista de Operadores já Cadastrados
    for(int i = 0; i < TAM_LISTA_OPERADORES; i++){
        if(strcmp(strlwr(nome), strlwr(info->listaOperadores[i].nomeOperador)) == 0 || strcmp(strupr(nome), strupr(info->listaOperadores[i].nomeOperador)) == 0 ){
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

    //Verifica se os 2 primeiros digitos não são Caracteres
    if(isdigit(setor[0]) || isdigit(setor[1])){
        return 0;
    }

    //Verifica se os 2 ultimos digitos não são Digitos Numéricos
    if(!isdigit(setor[2]) || !isdigit(setor[3])){
        return 0;
    }
    return 1;
}

int verificadorNumero(char num[]){
    //Verifica Tamanho da String
    if(strlen(num) == 0 || strlen(num) > 10){
        return 0;
    }

    //Verifica se não são Digitos Numéricos
    for(int i = 0; i < strlen(num); i++){
        if(!isdigit(num[i])){
            return 0;
        }
    }
    return 1;
}

void inserirOperadorNaLista(struct Operador op, struct Informacoes *info){
    for (int i = 0; i < TAM_LISTA_OPERADORES; i++){
        if(info->listaOperadores[i].idOperador == 0){'
            info->listaOperadores[i] = op;
            info->qtdOperadoresCadastrados++;
            break;
        }
    }
}

void cadastroOperador(struct Informacoes *info){
    int verificador = 0,leitorNum = 0,idOperadorTemporario = 0,qtdOperacoesTemporario = 0;
    char leitorStr[50],nomeOperadorTemporario[70],setorOperadorTemporario[6], nivelOperacionalTemporario[20],statusOperadorTemporario[10];

    printf("[* Cadastro de Operadores * ]\n");

    //limpaBuffer();

    do{
        printf("Nome do Operador: ");
        fgets(nomeOperadorTemporario,70,stdin);

        nomeOperadorTemporario[strcspn(nomeOperadorTemporario, "\n")] = '\0';

        verificador = verificadorNomeRepetido(nomeOperadorTemporario, info);

        if(verificador == 1){
            printf("Esse nome já foi cadastrado ou Valor Inválido.\nTente Novamente.\n\n");
        }
    }while(verificador == 1);

    verificador = 0;
    //limpaBuffer();

    do{
        printf("Um setor é composto por 2 Caracteres e 2 Números | Exemplo: TI01 \nSetor do Operador: ");
        fgets(setorOperadorTemporario,10,stdin);

        setorOperadorTemporario[strcspn(setorOperadorTemporario, "\n")] = '\0';

        verificador = verificadorPadraoSetor(setorOperadorTemporario);

        if(verificador == 0){
            printf("Padrão de Setor Invalido. Tente Novamente.\n\n");
        }
    }while(verificador == 0);

    verificador = 0;
    //limpaBuffer();

    do{
        printf("[ 1 - Básico | 2 - Intermediário | 3 - Supervisor Técnico ]\n Nivel do Operador: ");
        scanf("%d", &leitorNum);

        switch (leitorNum){
            case 1:
                strcpy(nivelOperacionalTemporario, "Basico");
                verificador = 1;
                break;
            case 2:
                strcpy(nivelOperacionalTemporario, "Intermediario");
                verificador = 1;
                break;
            case 3:
                strcpy(nivelOperacionalTemporario, "Supervisor Tecnico");
                verificador = 1;
                break;
            default:
                printf("Opção Inválida. Tente novamente.\n\n");
                limpaBuffer();
                verificador = 0;
                break;
        }
    }while(verificador == 0);

    verificador = 0;
    limpaBuffer();

    do{
        printf("[ 1 - Disponível | 2 - Ocupado | 3 - Inativo | 4 - Bloqueado ]\n Status do Operador: ");
        scanf("%d", &leitorNum);

        switch (leitorNum){
            case 1:
                strcpy(statusOperadorTemporario, "Disponivel");
                verificador = 1;
                break;
            case 2:
                strcpy(statusOperadorTemporario, "Ocupado");
                verificador = 1;
                break;
            case 3:
                strcpy(statusOperadorTemporario, "Inativo");
                verificador = 1;
                break;
            case 4:
                strcpy(statusOperadorTemporario, "Bloqueado");
                verificador = 1;
                break;
            default:
                printf("Opcão Inválida. Tente novamente.\n\n");
                limpaBuffer();
                verificador = 0;
                break;
        }
    }while(verificador == 0);

    verificador = 0;
    limpaBuffer();

    do{
        printf("Quantidade de Operações Efetuadas pelo Operador: ");
        fgets(leitorStr,50,stdin);

        leitorStr[strcspn(leitorStr, "\n")] = '\0';

        verificador = verificadorNumero(leitorStr);

        if(verificador == 0){
            printf("Opcão Inválida. Tente novamente.\n\n");
        }
    }while(verificador == 0);

    qtdOperacoesTemporario = atoi(leitorStr);
    idOperadorTemporario = info->qtdOperadoresCadastrados + 1;

    struct Operador operadorTemporario;

    operadorTemporario.idOperador = idOperadorTemporario;
    operadorTemporario.qtdOperacoes = qtdOperacoesTemporario;
    strcpy(operadorTemporario.nomeOperador, nomeOperadorTemporario);
    strcpy(operadorTemporario.setorOperador, setorOperadorTemporario);
    strcpy(operadorTemporario.nivelOperacional, nivelOperacionalTemporario);
    strcpy(operadorTemporario.statusOperador, statusOperadorTemporario);

    inserirOperadorNaLista(operadorTemporario, info);
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    struct Informacoes bancoDeDados = criarBancoDeDados();

    cadastroOperador(&bancoDeDados);
    cadastroOperador(&bancoDeDados);

    printf("\n=== DEBUG: DADOS NA LISTA [0] ===\n");
    printf("ID: %d\n", bancoDeDados.listaOperadores[0].idOperador);
    printf("Nome: %s\n", bancoDeDados.listaOperadores[0].nomeOperador);
    printf("Setor: %s\n", bancoDeDados.listaOperadores[0].setorOperador);
    printf("Nivel: %s\n", bancoDeDados.listaOperadores[0].nivelOperacional);
    printf("Status: %s\n", bancoDeDados.listaOperadores[0].statusOperador);
    printf("Qtd Operacoes: %d\n", bancoDeDados.listaOperadores[0].qtdOperacoes);
    printf("========================================\n\n");

    printf("\n=== DEBUG: DADOS NA LISTA [1] ===\n");
    printf("ID: %d\n", bancoDeDados.listaOperadores[1].idOperador);
    printf("Nome: %s\n", bancoDeDados.listaOperadores[1].nomeOperador);
    printf("Setor: %s\n", bancoDeDados.listaOperadores[1].setorOperador);
    printf("Nivel: %s\n", bancoDeDados.listaOperadores[1].nivelOperacional);
    printf("Status: %s\n", bancoDeDados.listaOperadores[1].statusOperador);
    printf("Qtd Operacoes: %d\n", bancoDeDados.listaOperadores[1].qtdOperacoes);
    printf("========================================\n\n");

    return 0;
}
