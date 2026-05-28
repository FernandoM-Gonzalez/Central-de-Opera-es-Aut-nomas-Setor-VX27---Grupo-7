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
struct Registros{
 int status;
 int id;
 char registroTexto[500];


};

struct Informacoes{
    int qtdOperadoresCadastrados;
    int qtdRegistrosCriados;
    struct Operador listaOperadores[TAM_LISTA_OPERADORES];
    struct Equipamento listaEquipamentos[TAM_LISTA_EQUIPAMENTOS];
    struct Registros registrosGerais[TAM_LISTA_EQUIPAMENTOS];
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

void atualizarEstadoOperacional(struct Informacoes *bancoDeDados){
    char id[10];
    int leitorNum;
    int verificador;
    do{
        printf("Um ID é composto por 1 Caracter e 2 Números | Exemplo: A02\nID do Equipamento: ");
        fgets(id,10,stdin);


        verificador = verificadorPadraoIdEquipamento(id);
        id[strcspn(id, "\n")] = '\0';

        if(verificador == 0){
            printf("Valor Inválido.\nTente Novamente.\n\n");
        }
    }while(verificador == 0);

    for(int i = 0;i < TAM_LISTA_EQUIPAMENTOS; i++){
        if(strcmp(id, bancoDeDados->listaEquipamentos[i].idEquipamento)== 0){

        do{
        printf("Digite o Estado Operacional");
        printf("[ 1 - Ativo | 2 - Inativo | 3 - Manutenção ]\nEstado Operacional: ");
        scanf("%d", &leitorNum);

        switch (leitorNum){
            case 1:
                strcpy(bancoDeDados->listaEquipamentos[i].estadoOperacional, "Ativo");
                verificador = 1;
                break;
            case 2:
                strcpy(bancoDeDados->listaEquipamentos[i].estadoOperacional, "Inativo");
                verificador = 1;
                break;
            case 3:
                strcpy(bancoDeDados->listaEquipamentos[i].estadoOperacional, "Manutencao");
                verificador = 1;
                break;
            default:
                printf("Opção Inválida. Tente novamente.\n\n");
                verificador = 0;
                limpaBuffer();
                break;
        }
    }while(verificador == 0);


        }

    }

}


void atualizarDisponibilidadeOperador(struct Informacoes *bancoDeDados){
    int leitorNum;
    int verificador = 0;
    printf("Digite o ID do Operador: ");
    scanf("%d",&leitorNum);
    for(int i = 0;i < TAM_LISTA_OPERADORES; i++){
            if(i == bancoDeDados->listaOperadores[0].idOperador){
                do{
                    printf("[ 1 - Disponível | 2 - Ocupado | 3 - Inativo | 4 - Bloqueado ]\n Status do Operador: ");
                    scanf("%d", &leitorNum);

                    switch (leitorNum){
                        case 1:
                            strcpy(bancoDeDados->listaOperadores[0].statusOperador, "Disponivel");
                            verificador = 1;
                            break;
                        case 2:
                            strcpy(bancoDeDados->listaOperadores[0].statusOperador, "Ocupado");
                            verificador = 1;
                            break;
                        case 3:
                            strcpy(bancoDeDados->listaOperadores[0].statusOperador, "Inativo");
                            verificador = 1;
                            break;
                        case 4:
                            strcpy(bancoDeDados->listaOperadores[0].statusOperador, "Bloqueado");
                            verificador = 1;
                            break;
                        default:
                            printf("Opcão Inválida. Tente novamente.\n\n");
                            limpaBuffer();
                            verificador = 0;
                            break;
                    }
                }while(verificador == 0);
        }
    }
    return;





}


void moverEquipamento(struct Informacoes *bancoDeDados){
    char id[10];
    char novoSetor[50];
    int verificador;
    do{
        printf("Um ID é composto por 1 Caracter e 2 Números | Exemplo: A02\nID do Equipamento: ");
        fgets(id,10,stdin);


        verificador = verificadorPadraoIdEquipamento(id);
        id[strcspn(id, "\n")] = '\0';

        if(verificador == 0){
            printf("Valor Inválido.\nTente Novamente.\n\n");
        }
    }while(verificador == 0);

    for(int i = 0;i < TAM_LISTA_EQUIPAMENTOS; i++){
        if(strcmp(id, bancoDeDados->listaEquipamentos[i].idEquipamento)== 0){
            do{
            printf("Digite o novo setor Associado do Equipamento: ");
            fgets(novoSetor,50,stdin);

            novoSetor[strcspn(novoSetor, "\n")] = '\0';

            verificador = verificadorSetorExistente(novoSetor, bancoDeDados);;

            if(verificador == 0){
                printf("Valor Inválido.\nTente Novamente.\n\n");
                limpaBuffer();
                }
            }while(verificador == 0);

            strcpy(bancoDeDados->listaEquipamentos[i].setorEquipamento, novoSetor);

        }

    }

}

int verificadorIDRegistro(struct Informacoes *bancoDeDados, int id){
    for(int i = 0;i<TAM_LISTA_EQUIPAMENTOS;i++){
        if(bancoDeDados->registrosGerais[i].id == id){
            return 1;

        }

 }
 return 0;
}


void criarRegistro(struct Informacoes *bancoDeDados){
    char texto[500];

    printf("Digite o registro: ");
    fgets(texto, 500, stdin);

    texto[strcspn(texto, "\n")] = '\0';

    for(int i = 0; i < TAM_LISTA_EQUIPAMENTOS; i++){

        if(bancoDeDados->registrosGerais[i].id == 0){

            bancoDeDados->registrosGerais[i].id =
            bancoDeDados->qtdRegistrosCriados + 1;

            bancoDeDados->registrosGerais[i].status = 1;
            strcpy(bancoDeDados->registrosGerais[i].registroTexto,texto);
            bancoDeDados->qtdRegistrosCriados++;

            break;
        }
    }



}


void desativarRegistro(struct Informacoes *bancoDeDados){

    int a;
    int encontrado = 0;

    do{
        printf("Digite o ID da Ocorrencia a ser desabilitada: ");
        scanf("%d", &a);
        limpaBuffer();

        if(verificadorIDRegistro(bancoDeDados, a) == 0){
            printf("ID inválido. Tente novamente.\n\n");
        }

    }while(verificadorIDRegistro(bancoDeDados, a) == 0);

    for(int i = 0; i < TAM_LISTA_EQUIPAMENTOS; i++){

        if(bancoDeDados->registrosGerais[i].id == a){

            bancoDeDados->registrosGerais[i].status = 0;

            encontrado = 1;

            break;
        }
    }

}














void atualizar(struct Informacoes *bancoDeDados){
    int a;
    int op;
    for(;;){

        printf("1-Altere o Estado Operacional do Equipamento\n");
        printf("2-Atualize a disponibilidade dos Operadores\n");
        printf("3-Mover equipamentos entre Setores\n");
        printf("4-Registrar ocorrências\n");
        printf("5-Desativar Registros\n");
        printf("6-Sair");


        do
        {
            printf("\nSelecione a opção:");
            a=scanf("%d", &op);
            limpaBuffer();
        }while(!a);

       switch (op){
        case 1:
            atualizarEstadoOperacional(bancoDeDados);
        break;
        case 2:
            atualizarDisponibilidadeOperador(bancoDeDados);
        break;

        case 3:
            moverEquipamento(bancoDeDados);
        break;
        case 4:
            criarRegistro(bancoDeDados);
        break;
        case 5:
            desativarRegistro(bancoDeDados);
        break;
        case 6:
            return;
        break;





       }


}
}


void menu(struct Informacoes *bancoDeDados){
    int a;
    int opcao;
    for(;;){

        printf("1-Cadrastra Operadore\n");
        printf("2-Cadrastra Equipamento\n");
        printf("3-Atualizar Cadastro\n");
        printf("4-Consultar Registro\n");
        printf("5-Relatorio\n");


        do
        {
            printf("\nSelecione a opção:");
            a=scanf("%d", &opcao);
            limpaBuffer();
        }while(!a);

       switch (opcao){
        case 1:
            cadastroOperador(bancoDeDados);
        break;
        case 2:
            cadastroEquipamento(bancoDeDados);
        break;

        case 3:
            atualizar(bancoDeDados);

        break;
        case 4:



        break;
        case 1212:

            for(int i = 0;i<2;i++){
                printf("\n=== DEBUG: DADOS NA LISTA [%d] ===\n",i);
                printf("ID: %d\n", bancoDeDados->listaOperadores[i].idOperador);
                printf("Nome: %s\n", bancoDeDados->listaOperadores[i].nomeOperador);
                printf("Setor: %s\n", bancoDeDados->listaOperadores[i].setorOperador);
                printf("Nivel: %s\n", bancoDeDados->listaOperadores[i].nivelOperacional);
                printf("Status: %s\n", bancoDeDados->listaOperadores[i].statusOperador);
                printf("Qtd Operacoes: %d\n", bancoDeDados->listaOperadores[i].qtdOperacoes);
                printf("========================================\n\n");

            }

            for(int i = 0;i<2;i++){
                printf("\n=== DEBUG: EQUIPAMENTO NA LISTA [%d] ===\n",i);
                printf("ID Equipamento: %s\n", bancoDeDados->listaEquipamentos[i].idEquipamento);
                printf("Tipo: %s\n", bancoDeDados->listaEquipamentos[i].tipoEquipamento);
                printf("Setor: %s\n", bancoDeDados->listaEquipamentos[i].setorEquipamento);
                printf("Estado Operacional: %s\n", bancoDeDados->listaEquipamentos[i].estadoOperacional);
                printf("Prioridade: %d\n", bancoDeDados->listaEquipamentos[i].nivelPrioridade);
                printf("ID Operador Responsavel: %d\n", bancoDeDados->listaEquipamentos[i].idOperadorEquipamento);
                printf("========================================\n\n");

            }
            for(int i  = 0;i<2;i++){
                printf("Ocorencia id: %d\n",bancoDeDados->registrosGerais[i].id);
                printf("Ocorencia status: %d\n",bancoDeDados->registrosGerais[i].status);
                printf("Ocorencia: %s\n",bancoDeDados->registrosGerais[i].registroTexto);


            }
        break;




       }





    }




}

int main(){
    setlocale(LC_ALL, "Portuguese");

    struct Informacoes bancoDeDados = criarBancoDeDados();

    menu(&bancoDeDados);




    return 0;
}
