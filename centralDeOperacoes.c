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
    char idEquipamento[10], tipoEquipamento[20], setorEquipamento[6], estadoOperacional[10];
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
        if(strcasecmp(nome, info->listaOperadores[i].nomeOperador) == 0){
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
        if(info->listaOperadores[i].idOperador == 0){
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

    do{
        printf("Um setor é composto por 2 Caracteres e 2 Números | Exemplo: TI01\nSetor do Operador: ");
        fgets(setorOperadorTemporario,10,stdin);

        setorOperadorTemporario[strcspn(setorOperadorTemporario, "\n")] = '\0';

        verificador = verificadorPadraoSetor(setorOperadorTemporario);

        if(verificador == 0){
            printf("Padrão de Setor Invalido. Tente Novamente.\n\n");
        }
    }while(verificador == 0);

    verificador = 0;

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

int verificadorPadraoIdEquipamento(char id[]){
    if(strlen(id) != 4){
        return 0;
    }

    if(isdigit(id[0])){
        return 0;
    }

    if(!isdigit(id[1]) || !isdigit(id[2])){
        return 0;
    }
    return 1;
}

int verificadorSetorExistente(char setor[], struct Informacoes *info){
    for(int i = 0; i < TAM_LISTA_OPERADORES; i++){
        if(strcasecmp(setor, info->listaOperadores[i].setorOperador) == 0){
            return 1;
        }
    }
    return 0;
}

int verificadorIdExistente(int id, struct Informacoes *info){
    for(int i = 0; i < TAM_LISTA_OPERADORES; i++){
        if(info->listaOperadores[i].idOperador != 0){
            if(id == info->listaOperadores[i].idOperador){
                return 1;
            }
        }
    }
    return 0;
}

void inserirEquipamentoNaLista(struct Equipamento eq, struct Informacoes *info){
    for (int i = 0; i < TAM_LISTA_EQUIPAMENTOS; i++){
        if(info->listaEquipamentos[i].idEquipamento[0] == '\0'){
            info->listaEquipamentos[i] = eq;
            break;
        }
    }
}

void cadastroEquipamento(struct Informacoes *info){
    int verificador = 0, leitorNum = 0, nivelPrioridadeTemporario, idOperadorEquipamentoTemporario;
    char leitorStr[50],idEquipamentoTemporario[10], tipoEquipamentoTemporario[20], setorEquipamentoTemporario[6], estadoOperacionalTemporario[10];

    printf("[* Cadastro de Equipamento * ]\n");

    do{
        printf("Um ID é composto por 1 Caracter e 2 Números | Exemplo: A02\nID do Equipamento: ");
        fgets(idEquipamentoTemporario,10,stdin);

        verificador = verificadorPadraoIdEquipamento(idEquipamentoTemporario);

        if(verificador == 0){
            printf("Valor Inválido.\nTente Novamente.\n\n");
        }
    }while(verificador == 0);

    idEquipamentoTemporario[strcspn(idEquipamentoTemporario, "\n")] = '\0';

    verificador = 0;

    do{
        printf("[ 1 - Drone | 2 - Sensor | 3 - Scanner | 4 - Braço Robótico ]\nCategoria Operacional: ");
        scanf("%d", &leitorNum);

        switch (leitorNum){
            case 1:
                strcpy(tipoEquipamentoTemporario, "Drone");
                verificador = 1;
                break;
            case 2:
                strcpy(tipoEquipamentoTemporario, "Sensor");
                verificador = 1;
                break;
            case 3:
                strcpy(tipoEquipamentoTemporario, "Scanner");
                verificador = 1;
                break;
            case 4:
                strcpy(tipoEquipamentoTemporario, "Braco Robotico");
                verificador = 1;
                break;
            default:
                printf("Opção Inválida. Tente novamente.\n\n");
                verificador = 0;
                limpaBuffer();
                break;
        }
    }while(verificador == 0);

    limpaBuffer();
    verificador = 0;

    do{
        printf("Setor Associado do Equipamento: ");
        fgets(setorEquipamentoTemporario,50,stdin);

        setorEquipamentoTemporario[strcspn(setorEquipamentoTemporario, "\n")] = '\0';

        verificador = verificadorSetorExistente(setorEquipamentoTemporario, info);

        if(verificador == 0){
            printf("Valor Inválido.\nTente Novamente.\n\n");
            limpaBuffer();
        }
    }while(verificador == 0);

    verificador = 0;

    do{
        printf("[ 1 - Ativo | 2 - Inativo | 3 - Manutenção ]\nEstado Operacional: ");
        scanf("%d", &leitorNum);

        switch (leitorNum){
            case 1:
                strcpy(estadoOperacionalTemporario, "Ativo");
                verificador = 1;
                break;
            case 2:
                strcpy(estadoOperacionalTemporario, "Inativo");
                verificador = 1;
                break;
            case 3:
                strcpy(estadoOperacionalTemporario, "Manutencao");
                verificador = 1;
                break;
            default:
                printf("Opção Inválida. Tente novamente.\n\n");
                verificador = 0;
                limpaBuffer();
                break;
        }
    }while(verificador == 0);

    limpaBuffer();
    verificador = 0;

    do{
        printf("ID do Operador responsável (Número de 1 a 50): ");
        fgets(leitorStr, 50, stdin);

        leitorStr[strcspn(leitorStr, "\n")] = '\0';

        verificador = verificadorNumero(leitorStr);

        if(verificador == 0){
            printf("Opção Inválida. Tente novamente.\n\n");
            limpaBuffer();
        }else{
            idOperadorEquipamentoTemporario = atoi(leitorStr);

            verificador = verificadorIdExistente(idOperadorEquipamentoTemporario, info);

            if(verificador == 0){
                printf("Operador não encontrado ou inválido.\nTente Novamente.\n\n");
                limpaBuffer();
            }
        }
    }while(verificador == 0);

    verificador = 0;
    limpaBuffer();

    do{
        printf("[ 1 - Baixa | 2 - Média | 3 - Alta ]\nNivel de Prioridade do Equipamento: ");
        fgets(leitorStr, 50, stdin);

        leitorStr[strcspn(leitorStr, "\n")] = '\0';

        verificador = verificadorNumero(leitorStr);

        if(verificador == 0){
            printf("Opção Inválida. Tente novamente.\n\n");
        }else{
            leitorNum = atoi(leitorStr);
        }

        switch (leitorNum){
            case 1:
                nivelPrioridadeTemporario = 1;
                verificador = 1;
                break;
            case 2:
                nivelPrioridadeTemporario = 2;
                verificador = 1;
                break;
            case 3:
                nivelPrioridadeTemporario = 3;
                verificador = 1;
                break;
            default:
                printf("Opção Inválida. Tente novamente.\n\n");
                verificador = 0;
                limpaBuffer();
                break;
        }
    }while(verificador == 0);

    struct Equipamento equipamentoTemporario;

    equipamentoTemporario.idOperadorEquipamento = idOperadorEquipamentoTemporario;
    equipamentoTemporario.nivelPrioridade = nivelPrioridadeTemporario;
    strcpy(equipamentoTemporario.idEquipamento, idEquipamentoTemporario);
    strcpy(equipamentoTemporario.tipoEquipamento, tipoEquipamentoTemporario);
    strcpy(equipamentoTemporario.setorEquipamento, setorEquipamentoTemporario);
    strcpy(equipamentoTemporario.estadoOperacional, estadoOperacionalTemporario);

    inserirEquipamentoNaLista(equipamentoTemporario, info);
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    struct Informacoes bancoDeDados = criarBancoDeDados();

    cadastroOperador(&bancoDeDados);

    printf("\n=== DEBUG: DADOS NA LISTA [0] ===\n");
    printf("ID: %d\n", bancoDeDados.listaOperadores[0].idOperador);
    printf("Nome: %s\n", bancoDeDados.listaOperadores[0].nomeOperador);
    printf("Setor: %s\n", bancoDeDados.listaOperadores[0].setorOperador);
    printf("Nivel: %s\n", bancoDeDados.listaOperadores[0].nivelOperacional);
    printf("Status: %s\n", bancoDeDados.listaOperadores[0].statusOperador);
    printf("Qtd Operacoes: %d\n", bancoDeDados.listaOperadores[0].qtdOperacoes);
    printf("========================================\n\n");

    cadastroEquipamento(&bancoDeDados);

    printf("\n=== DEBUG: EQUIPAMENTO NA LISTA [0] ===\n");
    printf("ID Equipamento: %s\n", bancoDeDados.listaEquipamentos[0].idEquipamento);
    printf("Tipo: %s\n", bancoDeDados.listaEquipamentos[0].tipoEquipamento);
    printf("Setor: %s\n", bancoDeDados.listaEquipamentos[0].setorEquipamento);
    printf("Estado Operacional: %s\n", bancoDeDados.listaEquipamentos[0].estadoOperacional);
    printf("Prioridade: %d\n", bancoDeDados.listaEquipamentos[0].nivelPrioridade);
    printf("ID Operador Responsavel: %d\n", bancoDeDados.listaEquipamentos[0].idOperadorEquipamento);
    printf("========================================\n\n");

    return 0;
}
