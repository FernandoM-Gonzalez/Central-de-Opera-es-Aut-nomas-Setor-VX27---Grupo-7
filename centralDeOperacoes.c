#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAM_LISTA_OPERADORES 50
#define TAM_LISTA_EQUIPAMENTOS 150
#define TAM_NOME 70
#define TAM_SETOR 10
#define TAM_TEXTO 500

struct Operador {
    int idOperador, qtdOperacoes;
    char nomeOperador[TAM_NOME], setorOperador[TAM_SETOR], nivelOperacional[30], statusOperador[30];
};
struct Equipamento {
    int idOperadorEquipamento, nivelPrioridade;
    char idEquipamento[10], tipoEquipamento[30], setorEquipamento[TAM_SETOR], estadoOperacional[30];
};
struct Registros {
    int status, id;
    char registroTexto[TAM_TEXTO];
};
struct Informacoes {
    int qtdOperadoresCadastrados, qtdEquipamentosCadastrados, qtdRegistrosCriados;
    struct Operador listaOperadores[TAM_LISTA_OPERADORES];
    struct Equipamento listaEquipamentos[TAM_LISTA_EQUIPAMENTOS];
    struct Registros registrosGerais[TAM_LISTA_EQUIPAMENTOS];
};
void limpaBuffer(void) {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
void tirarEnter(char texto[]) {
    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            texto[i] = '\0';
            return;
        }
        i++;
    }
}
int ehDigito(char c) {
    return c >= '0' && c <= '9';
}
int ehLetra(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
char paraMaiuscula(char c) {
    if (c >= 'a' && c <= 'z') return c - 32;
    return c;
}
char paraMinuscula(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}
void deixarMaiusculo(char texto[]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        texto[i] = paraMaiuscula(texto[i]);
    }
}
int compararTexto(char texto1[], char texto2[]) {
    int i = 0;
    while (texto1[i] != '\0' && texto2[i] != '\0') {
        if (paraMinuscula(texto1[i]) != paraMinuscula(texto2[i])) return 0;
        i++;
    }
    if (texto1[i] == '\0' && texto2[i] == '\0') return 1;
    return 0;
}
void linha(void) {
    printf("\n+------------------------------------------------------------+\n");
}
void titulo(char texto[]) {
    linha();
    printf("| %-58s |\n", texto);
    linha();
}
void lerTexto(char mensagem[], char destino[], int tamanho) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    tirarEnter(destino);
}
int lerInteiro(char mensagem[]) {
    int valor, certo;
    do {
        printf("%s", mensagem);
        certo = scanf("%d", &valor);
        limpaBuffer();
        if (certo != 1) {
            printf("Valor invalido. Digite apenas numeros.\n");
        }
    } while (certo != 1);
    return valor;
}
struct Informacoes criarBancoDeDados(void) {
    struct Informacoes info = {0};
    return info;
}
int verificadorNumero(char num[]) {
    int i;
    if (strlen(num) == 0 || strlen(num) > 10) return 0;
    for (i = 0; num[i] != '\0'; i++) {
        if (!ehDigito(num[i])) return 0;
    }
    return 1;
}
int verificadorIdOperadorTexto(char id[]) {
    if (strlen(id) != 4) return 0;
    return verificadorNumero(id);
}
int verificadorPadraoSetor(char setor[]) {
    if (strlen(setor) != 4) return 0;
    if (!ehLetra(setor[0]) || !ehLetra(setor[1])) return 0;
    if (!ehDigito(setor[2]) || !ehDigito(setor[3])) return 0;
    return 1;
}
int verificadorPadraoIdEquipamento(char id[]) {
    if (strlen(id) != 3) return 0;
    if (!ehLetra(id[0])) return 0;
    if (!ehDigito(id[1]) || !ehDigito(id[2])) return 0;
    return 1;
}
int buscarIndiceOperadorPorId(struct Informacoes *info, int id) {
    int i;
    for (i = 0; i < info->qtdOperadoresCadastrados; i++) {
        if (info->listaOperadores[i].idOperador == id) return i;
    }
    return -1;
}
int buscarIndiceOperadorPorNome(struct Informacoes *info, char nome[]) {
    int i;
    for (i = 0; i < info->qtdOperadoresCadastrados; i++) {
        if (compararTexto(info->listaOperadores[i].nomeOperador, nome) == 1) return i;
    }
    return -1;
}
int buscarIndiceEquipamento(struct Informacoes *info, char id[]) {
    int i;
    for (i = 0; i < info->qtdEquipamentosCadastrados; i++) {
        if (compararTexto(info->listaEquipamentos[i].idEquipamento, id) == 1) return i;
    }
    return -1;
}
int buscarIndiceRegistro(struct Informacoes *info, int id) {
    int i;
    for (i = 0; i < info->qtdRegistrosCriados; i++) {
        if (info->registrosGerais[i].id == id) return i;
    }
    return -1;
}
int verificadorNomeRepetido(char nome[], struct Informacoes *info) {
    if (strlen(nome) == 0 || strlen(nome) >= TAM_NOME) return 1;
    if (buscarIndiceOperadorPorNome(info, nome) != -1) return 1;
    return 0;
}
int verificadorSetorExistente(char setor[], struct Informacoes *info) {
    int i;
    for (i = 0; i < info->qtdOperadoresCadastrados; i++) {
        if (compararTexto(setor, info->listaOperadores[i].setorOperador) == 1) return 1;
    }
    return 0;
}
int operadorPodeControlar(struct Operador op) {
    if (compararTexto(op.statusOperador, "Inativo") == 1) return 0;
    if (compararTexto(op.statusOperador, "Bloqueado") == 1) return 0;
    return 1;
}
int operadorEstaLivre(struct Operador op) {
    if (compararTexto(op.statusOperador, "Disponivel") == 1) return 1;
    return 0;
}
char *prioridadeEmTexto(int nivel) {
    if (nivel == 1) return "Baixa";
    if (nivel == 2) return "Media";
    return "Alta";
}
int gerarIdOperador(struct Informacoes *info) {
    return 1001 + info->qtdOperadoresCadastrados;
}
void inserirOperadorNaLista(struct Operador op, struct Informacoes *info) {
    if (info->qtdOperadoresCadastrados < TAM_LISTA_OPERADORES) {
        info->listaOperadores[info->qtdOperadoresCadastrados] = op;
        info->qtdOperadoresCadastrados++;
    }
}
void escolherNivelOperador(char nivelOperacionalTemporario[]) {
    int leitorNum;
    int verificador = 0;
    do {
        printf("[ 1 - Basico | 2 - Intermediario | 3 - Supervisor Tecnico ]\n");
        leitorNum = lerInteiro("Nivel do Operador: ");
        switch (leitorNum) {
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
                printf("Opcao invalida. Tente novamente.\n\n");
                break;
        }
    } while (verificador == 0);
}
void escolherStatusOperador(char statusOperadorTemporario[]) {
    int leitorNum;
    int verificador = 0;
    do {
        printf("[ 1 - Disponivel | 2 - Ocupado | 3 - Inativo | 4 - Bloqueado ]\n");
        leitorNum = lerInteiro("Status do Operador: ");
        switch (leitorNum) {
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
                printf("Opcao invalida. Tente novamente.\n\n");
                break;
        }
    } while (verificador == 0);
}
void cadastroOperador(struct Informacoes *info) {
    int verificador;
    char leitorStr[50], nomeOperadorTemporario[TAM_NOME], setorOperadorTemporario[TAM_SETOR], nivelOperacionalTemporario[30], statusOperadorTemporario[30];
    struct Operador operadorTemporario;
    titulo("CADASTRO DE OPERADOR");
    if (info->qtdOperadoresCadastrados >= TAM_LISTA_OPERADORES) {
        printf("Limite de operadores atingido.\n");
        return;
    }
    do {
        lerTexto("Nome do Operador: ", nomeOperadorTemporario, TAM_NOME);
        verificador = verificadorNomeRepetido(nomeOperadorTemporario, info);
        if (verificador == 1) {
            printf("Esse nome ja foi cadastrado ou esta invalido. Tente novamente.\n\n");
        }
    } while (verificador == 1);
    do {
        printf("Um setor possui 2 letras e 2 numeros. Exemplo: TI01\n");
        lerTexto("Setor do Operador: ", setorOperadorTemporario, TAM_SETOR);
        deixarMaiusculo(setorOperadorTemporario);
        verificador = verificadorPadraoSetor(setorOperadorTemporario);
        if (verificador == 0) {
            printf("Padrao de setor invalido. Tente novamente.\n\n");
        }
    } while (verificador == 0);
    escolherNivelOperador(nivelOperacionalTemporario);
    escolherStatusOperador(statusOperadorTemporario);
    do {
        lerTexto("Quantidade de operacoes efetuadas pelo operador: ", leitorStr, 50);
        verificador = verificadorNumero(leitorStr);
        if (verificador == 0) {
            printf("Valor invalido. Tente novamente.\n\n");
        }
    } while (verificador == 0);
    operadorTemporario.idOperador = gerarIdOperador(info);
    operadorTemporario.qtdOperacoes = atoi(leitorStr);
    strcpy(operadorTemporario.nomeOperador, nomeOperadorTemporario);
    strcpy(operadorTemporario.setorOperador, setorOperadorTemporario);
    strcpy(operadorTemporario.nivelOperacional, nivelOperacionalTemporario);
    strcpy(operadorTemporario.statusOperador, statusOperadorTemporario);
    inserirOperadorNaLista(operadorTemporario, info);
    printf("\nOperador cadastrado com sucesso! ID gerado: %04d\n", operadorTemporario.idOperador);
}
void inserirEquipamentoNaLista(struct Equipamento eq, struct Informacoes *info) {
    if (info->qtdEquipamentosCadastrados < TAM_LISTA_EQUIPAMENTOS) {
        info->listaEquipamentos[info->qtdEquipamentosCadastrados] = eq;
        info->qtdEquipamentosCadastrados++;
    }
}
void escolherTipoEquipamento(char tipoEquipamentoTemporario[]) {
    int leitorNum;
    int verificador = 0;
    do {
        printf("[ 1 - Drone | 2 - Sensor | 3 - Scanner | 4 - Braco Robotico ]\n");
        leitorNum = lerInteiro("Categoria Operacional: ");
        switch (leitorNum) {
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
                printf("Opcao invalida. Tente novamente.\n\n");
                break;
        }
    } while (verificador == 0);
}
void escolherEstadoOperacional(char estadoOperacionalTemporario[]) {
    int leitorNum;
    int verificador = 0;
    do {
        printf("[ 1 - Ativo | 2 - Inativo | 3 - Manutencao ]\n");
        leitorNum = lerInteiro("Estado Operacional: ");
        switch (leitorNum) {
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
                printf("Opcao invalida. Tente novamente.\n\n");
                break;
        }
    } while (verificador == 0);
}
int escolherPrioridadeEquipamento(void) {
    int leitorNum;
    int verificador = 0;
    do {
        printf("[ 1 - Baixa | 2 - Media | 3 - Alta ]\n");
        leitorNum = lerInteiro("Nivel de Prioridade do Equipamento: ");
        if (leitorNum >= 1 && leitorNum <= 3) {
            verificador = 1;
        } else {
            printf("Opcao invalida. Tente novamente.\n\n");
        }
    } while (verificador == 0);
    return leitorNum;
}
int lerIdOperadorExistente(struct Informacoes *info, char setorEquipamento[]) {
    int idOperador, indiceOperador;
    char leitorStr[50];
    int verificador;
    do {
        printf("O mesmo operador pode controlar mais de um equipamento.\n");
        lerTexto("ID do Operador responsavel (4 digitos): ", leitorStr, 50);
        verificador = verificadorIdOperadorTexto(leitorStr);
        if (verificador == 0) {
            printf("ID invalido. Use 4 digitos.\n\n");
        } else {
            idOperador = atoi(leitorStr);
            indiceOperador = buscarIndiceOperadorPorId(info, idOperador);
            if (indiceOperador == -1) {
                printf("Operador nao encontrado.\n\n");
                verificador = 0;
            } else if (compararTexto(info->listaOperadores[indiceOperador].setorOperador, setorEquipamento) == 0) {
                printf("O operador informado nao pertence ao setor do equipamento.\n\n");
                verificador = 0;
            } else if (operadorPodeControlar(info->listaOperadores[indiceOperador]) == 0) {
                printf("Operador inativo ou bloqueado nao pode receber equipamento.\n\n");
                verificador = 0;
            }
        }
    } while (verificador == 0);
    return idOperador;
}
void cadastroEquipamento(struct Informacoes *info) {
    int verificador;
    char idEquipamentoTemporario[10], tipoEquipamentoTemporario[30], setorEquipamentoTemporario[TAM_SETOR], estadoOperacionalTemporario[30];
    struct Equipamento equipamentoTemporario;
    titulo("CADASTRO DE EQUIPAMENTO / MODULO");
    if (info->qtdEquipamentosCadastrados >= TAM_LISTA_EQUIPAMENTOS) {
        printf("Limite de equipamentos atingido.\n");
        return;
    }
    if (info->qtdOperadoresCadastrados == 0) {
        printf("Cadastre pelo menos um operador antes de cadastrar equipamentos.\n");
        return;
    }
    do {
        printf("Um ID possui 1 letra e 2 numeros. Exemplo: A02\n");
        lerTexto("ID do Equipamento: ", idEquipamentoTemporario, 10);
        deixarMaiusculo(idEquipamentoTemporario);
        verificador = verificadorPadraoIdEquipamento(idEquipamentoTemporario);
        if (verificador == 0) {
            printf("Valor invalido. Tente novamente.\n\n");
        } else if (buscarIndiceEquipamento(info, idEquipamentoTemporario) != -1) {
            printf("Esse ID de equipamento ja foi cadastrado.\n\n");
            verificador = 0;
        }
    } while (verificador == 0);
    escolherTipoEquipamento(tipoEquipamentoTemporario);
    do {
        printf("Um setor possui 2 letras e 2 numeros. Exemplo: VX27\n");
        lerTexto("Setor Associado do Equipamento: ", setorEquipamentoTemporario, TAM_SETOR);
        deixarMaiusculo(setorEquipamentoTemporario);
        verificador = verificadorPadraoSetor(setorEquipamentoTemporario);
        if (verificador == 0) {
            printf("Padrao de setor invalido.\n\n");
        } else if (verificadorSetorExistente(setorEquipamentoTemporario, info) == 0) {
            printf("Nenhum operador cadastrado nesse setor.\n\n");
            verificador = 0;
        }
    } while (verificador == 0);
    escolherEstadoOperacional(estadoOperacionalTemporario);
    equipamentoTemporario.idOperadorEquipamento = lerIdOperadorExistente(info, setorEquipamentoTemporario);
    equipamentoTemporario.nivelPrioridade = escolherPrioridadeEquipamento();
    strcpy(equipamentoTemporario.idEquipamento, idEquipamentoTemporario);
    strcpy(equipamentoTemporario.tipoEquipamento, tipoEquipamentoTemporario);
    strcpy(equipamentoTemporario.setorEquipamento, setorEquipamentoTemporario);
    strcpy(equipamentoTemporario.estadoOperacional, estadoOperacionalTemporario);
    inserirEquipamentoNaLista(equipamentoTemporario, info);
    printf("\nEquipamento cadastrado com sucesso!\n");
}
void atualizarEstadoOperacional(struct Informacoes *bancoDeDados) {
    char id[10];
    int indice;
    titulo("ALTERAR ESTADO OPERACIONAL");
    if (bancoDeDados->qtdEquipamentosCadastrados == 0) {
        printf("Nenhum equipamento cadastrado.\n");
        return;
    }
    do {
        lerTexto("ID do Equipamento: ", id, 10);
        deixarMaiusculo(id);
        if (verificadorPadraoIdEquipamento(id) == 0) {
            printf("ID invalido. Use 1 letra e 2 numeros.\n\n");
        }
    } while (verificadorPadraoIdEquipamento(id) == 0);
    indice = buscarIndiceEquipamento(bancoDeDados, id);
    if (indice == -1) {
        printf("Equipamento nao encontrado.\n");
        return;
    }
    escolherEstadoOperacional(bancoDeDados->listaEquipamentos[indice].estadoOperacional);
    printf("Estado atualizado com sucesso.\n");
}
void atualizarDisponibilidadeOperador(struct Informacoes *bancoDeDados) {
    int idInformado, indice;
    titulo("ATUALIZAR DISPONIBILIDADE DO OPERADOR");
    if (bancoDeDados->qtdOperadoresCadastrados == 0) {
        printf("Nenhum operador cadastrado.\n");
        return;
    }
    idInformado = lerInteiro("Digite o ID do Operador: ");
    indice = buscarIndiceOperadorPorId(bancoDeDados, idInformado);
    if (indice == -1) {
        printf("Operador nao encontrado.\n");
        return;
    }
    escolherStatusOperador(bancoDeDados->listaOperadores[indice].statusOperador);
    printf("Status atualizado com sucesso.\n");
}
void trocarOperadorResponsavel(struct Informacoes *bancoDeDados) {
    char id[10];
    int indiceEquipamento, novoId;
    titulo("TROCAR OPERADOR RESPONSAVEL");
    if (bancoDeDados->qtdEquipamentosCadastrados == 0) {
        printf("Nenhum equipamento cadastrado.\n");
        return;
    }
    lerTexto("ID do Equipamento: ", id, 10);
    deixarMaiusculo(id);
    indiceEquipamento = buscarIndiceEquipamento(bancoDeDados, id);
    if (indiceEquipamento == -1) {
        printf("Equipamento nao encontrado.\n");
        return;
    }
    printf("Setor atual do equipamento: %s\n", bancoDeDados->listaEquipamentos[indiceEquipamento].setorEquipamento);
    novoId = lerIdOperadorExistente(bancoDeDados, bancoDeDados->listaEquipamentos[indiceEquipamento].setorEquipamento);
    bancoDeDados->listaEquipamentos[indiceEquipamento].idOperadorEquipamento = novoId;
    printf("Operador responsavel atualizado com sucesso.\n");
}
void moverEquipamento(struct Informacoes *bancoDeDados) {
    char id[10], novoSetor[TAM_SETOR];
    int indiceEquipamento, verificador;
    titulo("MOVER EQUIPAMENTO ENTRE SETORES");
    if (bancoDeDados->qtdEquipamentosCadastrados == 0) {
        printf("Nenhum equipamento cadastrado.\n");
        return;
    }
    lerTexto("ID do Equipamento: ", id, 10);
    deixarMaiusculo(id);
    indiceEquipamento = buscarIndiceEquipamento(bancoDeDados, id);
    if (indiceEquipamento == -1) {
        printf("Equipamento nao encontrado.\n");
        return;
    }
    do {
        lerTexto("Digite o novo setor associado do equipamento: ", novoSetor, TAM_SETOR);
        deixarMaiusculo(novoSetor);
        verificador = verificadorPadraoSetor(novoSetor);
        if (verificador == 0) {
            printf("Padrao de setor invalido.\n\n");
        } else if (verificadorSetorExistente(novoSetor, bancoDeDados) == 0) {
            printf("Nenhum operador cadastrado nesse setor.\n\n");
            verificador = 0;
        }
    } while (verificador == 0);
    strcpy(bancoDeDados->listaEquipamentos[indiceEquipamento].setorEquipamento, novoSetor);
    printf("Agora escolha um operador do novo setor para evitar cadastro incorreto.\n");
    bancoDeDados->listaEquipamentos[indiceEquipamento].idOperadorEquipamento = lerIdOperadorExistente(bancoDeDados, novoSetor);
    printf("Equipamento movido com sucesso.\n");
}
void criarRegistro(struct Informacoes *bancoDeDados) {
    char texto[TAM_TEXTO];
    titulo("REGISTRAR OCORRENCIA");
    if (bancoDeDados->qtdRegistrosCriados >= TAM_LISTA_EQUIPAMENTOS) {
        printf("Limite de registros atingido.\n");
        return;
    }
    lerTexto("Digite o registro: ", texto, TAM_TEXTO);
    bancoDeDados->registrosGerais[bancoDeDados->qtdRegistrosCriados].id = bancoDeDados->qtdRegistrosCriados + 1;
    bancoDeDados->registrosGerais[bancoDeDados->qtdRegistrosCriados].status = 1;
    strcpy(bancoDeDados->registrosGerais[bancoDeDados->qtdRegistrosCriados].registroTexto, texto);
    bancoDeDados->qtdRegistrosCriados++;
    printf("Ocorrencia registrada com sucesso.\n");
}
void apagarOcorrencia(struct Informacoes *bancoDeDados) {
    int id, indice, i;
    struct Registros vazio = {0};
    titulo("APAGAR OCORRENCIA");
    if (bancoDeDados->qtdRegistrosCriados == 0) {
        printf("Nenhuma ocorrencia registrada.\n");
        return;
    }
    id = lerInteiro("Digite o ID da ocorrencia que sera apagada: ");
    indice = buscarIndiceRegistro(bancoDeDados, id);
    if (indice == -1) {
        printf("Registro nao encontrado.\n");
        return;
    }
    for (i = indice; i < bancoDeDados->qtdRegistrosCriados - 1; i++) {
        bancoDeDados->registrosGerais[i] = bancoDeDados->registrosGerais[i + 1];
        bancoDeDados->registrosGerais[i].id = i + 1;
    }
    bancoDeDados->qtdRegistrosCriados--;
    bancoDeDados->registrosGerais[bancoDeDados->qtdRegistrosCriados] = vazio;
    printf("Ocorrencia apagada. Os registros posteriores assumiram a posicao anterior.\n");
}
void atualizarIdsOperadoresDepoisDeApagar(struct Informacoes *bancoDeDados) {
    int i, j, idAntigo, idNovo;
    for (i = 0; i < bancoDeDados->qtdOperadoresCadastrados; i++) {
        idAntigo = bancoDeDados->listaOperadores[i].idOperador;
        idNovo = 1001 + i;
        if (idAntigo != idNovo) {
            for (j = 0; j < bancoDeDados->qtdEquipamentosCadastrados; j++) {
                if (bancoDeDados->listaEquipamentos[j].idOperadorEquipamento == idAntigo) {
                    bancoDeDados->listaEquipamentos[j].idOperadorEquipamento = idNovo;
                }
            }
            bancoDeDados->listaOperadores[i].idOperador = idNovo;
        }
    }
}
void apagarOperador(struct Informacoes *bancoDeDados) {
    int id, indice, i;
    struct Operador vazio = {0};
    titulo("APAGAR OPERADOR");
    if (bancoDeDados->qtdOperadoresCadastrados == 0) {
        printf("Nenhum operador cadastrado.\n");
        return;
    }
    id = lerInteiro("Digite o ID do operador que sera apagado: ");
    indice = buscarIndiceOperadorPorId(bancoDeDados, id);
    if (indice == -1) {
        printf("Operador nao encontrado.\n");
        return;
    }
    for (i = 0; i < bancoDeDados->qtdEquipamentosCadastrados; i++) {
        if (bancoDeDados->listaEquipamentos[i].idOperadorEquipamento == id) {
            bancoDeDados->listaEquipamentos[i].idOperadorEquipamento = 0;
        }
    }
    for (i = indice; i < bancoDeDados->qtdOperadoresCadastrados - 1; i++) {
        bancoDeDados->listaOperadores[i] = bancoDeDados->listaOperadores[i + 1];
    }
    bancoDeDados->qtdOperadoresCadastrados--;
    bancoDeDados->listaOperadores[bancoDeDados->qtdOperadoresCadastrados] = vazio;
    atualizarIdsOperadoresDepoisDeApagar(bancoDeDados);
    printf("Operador apagado. Os operadores posteriores assumiram a posicao anterior.\n");
    printf("Equipamentos desse operador ficaram sem responsavel ate nova atualizacao.\n");
}
void apagarEquipamento(struct Informacoes *bancoDeDados) {
    char id[10];
    int indice, i;
    struct Equipamento vazio = {0};
    titulo("APAGAR EQUIPAMENTO");
    if (bancoDeDados->qtdEquipamentosCadastrados == 0) {
        printf("Nenhum equipamento cadastrado.\n");
        return;
    }
    lerTexto("Digite o ID do equipamento que sera apagado: ", id, 10);
    deixarMaiusculo(id);
    indice = buscarIndiceEquipamento(bancoDeDados, id);
    if (indice == -1) {
        printf("Equipamento nao encontrado.\n");
        return;
    }
    for (i = indice; i < bancoDeDados->qtdEquipamentosCadastrados - 1; i++) {
        bancoDeDados->listaEquipamentos[i] = bancoDeDados->listaEquipamentos[i + 1];
    }
    bancoDeDados->qtdEquipamentosCadastrados--;
    bancoDeDados->listaEquipamentos[bancoDeDados->qtdEquipamentosCadastrados] = vazio;
    printf("Equipamento apagado. Os equipamentos posteriores assumiram a posicao anterior.\n");
}
void apagarRegistros(struct Informacoes *bancoDeDados) {
    int opcao;
    while (1) {
        titulo("APAGAR REGISTROS DO SISTEMA");
        printf("| 1 | Apagar operador                                      |\n");
        printf("| 2 | Apagar equipamento                                   |\n");
        printf("| 3 | Apagar ocorrencia                                    |\n");
        printf("| 4 | Voltar                                               |\n");
        linha();
        opcao = lerInteiro("Selecione a opcao: ");
        system("cls");
        switch (opcao) {
            case 1:
                apagarOperador(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 2:
                apagarEquipamento(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 3:
                apagarOcorrencia(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 4:
                return;

            default:
                printf("Opcao invalida.\n");
                system("pause");
                system("cls");
                break;
        }
    }
}
void atualizar(struct Informacoes *bancoDeDados) {
    int opcao;
    while (1) {
        titulo("ATUALIZACAO DO SISTEMA");
        printf("| 1 | Alterar estado operacional do equipamento             |\n");
        printf("| 2 | Atualizar disponibilidade dos operadores              |\n");
        printf("| 3 | Mover equipamentos entre setores                      |\n");
        printf("| 4 | Registrar ocorrencias                                 |\n");
        printf("| 5 | Apagar registros                                      |\n");
        printf("| 6 | Trocar operador responsavel de equipamento            |\n");
        printf("| 7 | Sair                                                  |\n");
        linha();
        opcao = lerInteiro("Selecione a opcao: ");
        system("cls");
        switch (opcao) {
            case 1:
                atualizarEstadoOperacional(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 2:
                atualizarDisponibilidadeOperador(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 3:
                moverEquipamento(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 4:
                criarRegistro(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 5:
                apagarRegistros(bancoDeDados);
                system("cls");
                break;

            case 6:
                trocarOperadorResponsavel(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 7:
                return;

            default:
                printf("Opcao invalida.\n");
                system("pause");
                system("cls");
                break;
        }
    }
}
void mostrarOperador(struct Operador op) {
    printf("ID: %04d\n", op.idOperador);
    printf("Nome: %s\n", op.nomeOperador);
    printf("Setor: %s\n", op.setorOperador);
    printf("Nivel: %s\n", op.nivelOperacional);
    printf("Status: %s\n", op.statusOperador);
    printf("Operacoes realizadas: %d\n", op.qtdOperacoes);
}
void mostrarEquipamento(struct Equipamento eq, struct Informacoes *info) {
    int indiceOperador;
    printf("ID Equipamento: %s\n", eq.idEquipamento);
    printf("Tipo: %s\n", eq.tipoEquipamento);
    printf("Setor: %s\n", eq.setorEquipamento);
    printf("Estado: %s\n", eq.estadoOperacional);
    printf("Prioridade: %s\n", prioridadeEmTexto(eq.nivelPrioridade));
    if (eq.idOperadorEquipamento == 0) {
        printf("Operador responsavel: Sem operador\n");
    } else {
        indiceOperador = buscarIndiceOperadorPorId(info, eq.idOperadorEquipamento);
        if (indiceOperador == -1) {
            printf("Operador responsavel: ID %04d nao encontrado\n", eq.idOperadorEquipamento);
        } else {
            printf("Operador responsavel: %04d - %s\n", eq.idOperadorEquipamento, info->listaOperadores[indiceOperador].nomeOperador);
        }
    }
}
void consultarOperadorLivre(struct Informacoes *bancoDeDados) {
    int opcao, id;
    int indice = -1;
    char nome[TAM_NOME];
    titulo("CONSULTAR OPERADOR LIVRE");
    if (bancoDeDados->qtdOperadoresCadastrados == 0) {
        printf("Nenhum operador cadastrado.\n");
        return;
    }
    printf("1 - Pesquisar por ID\n");
    printf("2 - Pesquisar por nome\n");
    opcao = lerInteiro("Selecione a opcao: ");
    if (opcao == 1) {
        id = lerInteiro("Digite o ID do operador: ");
        indice = buscarIndiceOperadorPorId(bancoDeDados, id);
    } else if (opcao == 2) {
        lerTexto("Digite o nome do operador: ", nome, TAM_NOME);
        indice = buscarIndiceOperadorPorNome(bancoDeDados, nome);
    } else {
        printf("Opcao invalida.\n");
        return;
    }
    if (indice == -1) {
        printf("Operador nao encontrado.\n");
        return;
    }
    mostrarOperador(bancoDeDados->listaOperadores[indice]);
    if (operadorEstaLivre(bancoDeDados->listaOperadores[indice]) == 1) {
        printf("Resultado: operador LIVRE para operar.\n");
    } else {
        printf("Resultado: operador NAO esta livre no momento.\n");
    }
}
void consultarEstadoEquipamento(struct Informacoes *bancoDeDados) {
    char id[10];
    int indice;
    titulo("CONSULTAR ESTADO DO EQUIPAMENTO");
    if (bancoDeDados->qtdEquipamentosCadastrados == 0) {
        printf("Nenhum equipamento cadastrado.\n");
        return;
    }
    lerTexto("ID do equipamento: ", id, 10);
    deixarMaiusculo(id);
    indice = buscarIndiceEquipamento(bancoDeDados, id);
    if (indice == -1) {
        printf("Equipamento nao encontrado.\n");
        return;
    }
    printf("Equipamento %s esta com estado: %s\n",
           bancoDeDados->listaEquipamentos[indice].idEquipamento,
           bancoDeDados->listaEquipamentos[indice].estadoOperacional);
}
void consultarOperadoresLivresParaEquipamento(struct Informacoes *bancoDeDados) {
    char id[10], setor[TAM_SETOR];
    int indiceEquipamento, i;
    int achou = 0;
    titulo("OPERADORES LIVRES PARA EQUIPAMENTO E SETOR");
    if (bancoDeDados->qtdEquipamentosCadastrados == 0 || bancoDeDados->qtdOperadoresCadastrados == 0) {
        printf("Cadastre operadores e equipamentos antes da consulta.\n");
        return;
    }
    lerTexto("ID do equipamento: ", id, 10);
    deixarMaiusculo(id);
    indiceEquipamento = buscarIndiceEquipamento(bancoDeDados, id);
    if (indiceEquipamento == -1) {
        printf("Equipamento nao encontrado.\n");
        return;
    }
    lerTexto("Setor desejado: ", setor, TAM_SETOR);
    deixarMaiusculo(setor);
    if (compararTexto(bancoDeDados->listaEquipamentos[indiceEquipamento].setorEquipamento, setor) == 0) {
        printf("Esse equipamento nao esta cadastrado no setor informado.\n");
        return;
    }
    printf("\nOperadores disponiveis no setor %s:\n", setor);
    for (i = 0; i < bancoDeDados->qtdOperadoresCadastrados; i++) {
        if (compararTexto(bancoDeDados->listaOperadores[i].setorOperador, setor) == 1 &&
            operadorEstaLivre(bancoDeDados->listaOperadores[i]) == 1) {
            printf("%04d - %s\n", bancoDeDados->listaOperadores[i].idOperador, bancoDeDados->listaOperadores[i].nomeOperador);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Nenhum operador livre encontrado nesse setor.\n");
    }
}
void listarOcorrencias(struct Informacoes *bancoDeDados) {
    int i;
    titulo("OCORRENCIAS REGISTRADAS");
    if (bancoDeDados->qtdRegistrosCriados == 0) {
        printf("Nenhuma ocorrencia registrada.\n");
        return;
    }
    for (i = 0; i < bancoDeDados->qtdRegistrosCriados; i++) {
        printf("ID %d - %s\n", bancoDeDados->registrosGerais[i].id, bancoDeDados->registrosGerais[i].registroTexto);
    }
}
void consultarRegistro(struct Informacoes *bancoDeDados) {
    int opcao;
    while (1) {
        titulo("CONSULTAS");
        printf("| 1 | Pesquisar se operador esta livre pelo nome ou ID       |\n");
        printf("| 2 | Pesquisar estado operacional de um equipamento         |\n");
        printf("| 3 | Pesquisar operadores livres por equipamento e setor    |\n");
        printf("| 4 | Listar ocorrencias registradas                         |\n");
        printf("| 5 | Voltar                                                |\n");
        linha();
        opcao = lerInteiro("Selecione a opcao: ");
        system("cls");
        switch (opcao) {
            case 1:
                consultarOperadorLivre(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 2:
                consultarEstadoEquipamento(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 3:
                consultarOperadoresLivresParaEquipamento(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 4:
                listarOcorrencias(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 5:
                return;

            default:
                printf("Opcao invalida.\n");
                system("pause");
                system("cls");
                break;
        }
    }
}
void relatorioTodosOperadores(struct Informacoes *bancoDeDados) {
    int i;
    titulo("RELATORIO - TODOS OS OPERADORES");
    if (bancoDeDados->qtdOperadoresCadastrados == 0) {
        printf("Nenhum operador cadastrado.\n");
        return;
    }
    for (i = 0; i < bancoDeDados->qtdOperadoresCadastrados; i++) {
        printf("\n+---------------- OPERADOR %d ----------------+\n", i + 1);
        mostrarOperador(bancoDeDados->listaOperadores[i]);
    }
}
void relatorioOperadoresPorSetor(struct Informacoes *bancoDeDados) {
    char setor[TAM_SETOR];
    int i;
    int achou = 0;
    titulo("RELATORIO - OPERADORES POR SETOR");
    lerTexto("Digite o setor: ", setor, TAM_SETOR);
    deixarMaiusculo(setor);
    printf("\n+------+------------------------------+--------------------+\n");
    printf("| ID   | Nome                         | Status             |\n");
    printf("+------+------------------------------+--------------------+\n");
    for (i = 0; i < bancoDeDados->qtdOperadoresCadastrados; i++) {
        if (compararTexto(bancoDeDados->listaOperadores[i].setorOperador, setor) == 1) {
            printf("| %04d | %-28s | %-18s |\n", bancoDeDados->listaOperadores[i].idOperador, bancoDeDados->listaOperadores[i].nomeOperador, bancoDeDados->listaOperadores[i].statusOperador);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Nenhum operador encontrado nesse setor.\n");
    }
}
void relatorioEquipamentosPorSetor(struct Informacoes *bancoDeDados) {
    char setor[TAM_SETOR];
    int i;
    int achou = 0;
    titulo("RELATORIO - EQUIPAMENTOS POR SETOR");
    lerTexto("Digite o setor: ", setor, TAM_SETOR);
    deixarMaiusculo(setor);
    printf("\n+------+----------------------+----------------------+\n");
    printf("| ID   | Tipo                 | Estado Operacional  |\n");
    printf("+------+----------------------+----------------------+\n");
    for (i = 0; i < bancoDeDados->qtdEquipamentosCadastrados; i++) {
        if (compararTexto(bancoDeDados->listaEquipamentos[i].setorEquipamento, setor) == 1) {
            printf("| %-4s | %-20s | %-20s |\n", bancoDeDados->listaEquipamentos[i].idEquipamento, bancoDeDados->listaEquipamentos[i].tipoEquipamento, bancoDeDados->listaEquipamentos[i].estadoOperacional);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Nenhum equipamento encontrado nesse setor.\n");
    }
}
void relatorioOperadoresEquipamentosPorSetor(struct Informacoes *bancoDeDados) {
    char setor[TAM_SETOR];
    int i, indiceOperador;
    int achou = 0;
    titulo("RELATORIO - OPERADOR E EQUIPAMENTO POR SETOR");
    lerTexto("Digite o setor: ", setor, TAM_SETOR);
    deixarMaiusculo(setor);
    printf("\n+-------------+------------------------------+----------------+----------------------+\n");
    printf("| ID Operador | Nome Operador                | ID Equipamento | Tipo                 |\n");
    printf("+-------------+------------------------------+----------------+----------------------+\n");
    for (i = 0; i < bancoDeDados->qtdEquipamentosCadastrados; i++) {
        if (compararTexto(bancoDeDados->listaEquipamentos[i].setorEquipamento, setor) == 1) {
            indiceOperador = buscarIndiceOperadorPorId(bancoDeDados, bancoDeDados->listaEquipamentos[i].idOperadorEquipamento);
            if (indiceOperador == -1) {
                printf("| %-11s | %-28s | %-14s | %-20s |\n", "Sem operador", "Sem operador", bancoDeDados->listaEquipamentos[i].idEquipamento, bancoDeDados->listaEquipamentos[i].tipoEquipamento);
            } else {
                printf("| %04d        | %-28s | %-14s | %-20s |\n", bancoDeDados->listaOperadores[indiceOperador].idOperador, bancoDeDados->listaOperadores[indiceOperador].nomeOperador, bancoDeDados->listaEquipamentos[i].idEquipamento, bancoDeDados->listaEquipamentos[i].tipoEquipamento);
            }
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Nenhum relacionamento encontrado nesse setor.\n");
    }
}
int setorJaFoiMostrado(char setores[][TAM_SETOR], int qtdSetores, char setor[]) {
    int i;
    for (i = 0; i < qtdSetores; i++) {
        if (compararTexto(setores[i], setor) == 1) return 1;
    }
    return 0;
}
void relatorioMaiorOperadorPorSetor(struct Informacoes *bancoDeDados) {
    char setores[TAM_LISTA_OPERADORES][TAM_SETOR];
    int qtdSetores = 0;
    int i, j, indiceMaior;
    titulo("RELATORIO - MAIOR NUMERO DE OPERACOES POR SETOR");
    if (bancoDeDados->qtdOperadoresCadastrados == 0) {
        printf("Nenhum operador cadastrado.\n");
        return;
    }
    for (i = 0; i < bancoDeDados->qtdOperadoresCadastrados; i++) {
        if (setorJaFoiMostrado(setores, qtdSetores, bancoDeDados->listaOperadores[i].setorOperador) == 0) {
            strcpy(setores[qtdSetores], bancoDeDados->listaOperadores[i].setorOperador);
            qtdSetores++;
            indiceMaior = i;
            for (j = 0; j < bancoDeDados->qtdOperadoresCadastrados; j++) {
                if (compararTexto(bancoDeDados->listaOperadores[j].setorOperador, bancoDeDados->listaOperadores[i].setorOperador) == 1 &&
                    bancoDeDados->listaOperadores[j].qtdOperacoes > bancoDeDados->listaOperadores[indiceMaior].qtdOperacoes) {
                    indiceMaior = j;
                }
            }
            printf("Setor %s -> %04d - %s (%d operacoes)\n",
                   bancoDeDados->listaOperadores[indiceMaior].setorOperador,
                   bancoDeDados->listaOperadores[indiceMaior].idOperador,
                   bancoDeDados->listaOperadores[indiceMaior].nomeOperador,
                   bancoDeDados->listaOperadores[indiceMaior].qtdOperacoes);
        }
    }
}
void relatorioEquipamentosPorOperador(struct Informacoes *bancoDeDados) {
    int id, indiceOperador, i;
    int achou = 0;
    titulo("RELATORIO - EQUIPAMENTOS CONTROLADOS POR OPERADOR");
    if (bancoDeDados->qtdOperadoresCadastrados == 0 || bancoDeDados->qtdEquipamentosCadastrados == 0) {
        printf("Cadastre operadores e equipamentos antes de gerar esse relatorio.\n");
        return;
    }
    id = lerInteiro("Digite o ID do operador: ");
    indiceOperador = buscarIndiceOperadorPorId(bancoDeDados, id);
    if (indiceOperador == -1) {
        printf("Operador nao encontrado.\n");
        return;
    }
    printf("\nOperador: %04d - %s\n", bancoDeDados->listaOperadores[indiceOperador].idOperador, bancoDeDados->listaOperadores[indiceOperador].nomeOperador);
    printf("Equipamentos vinculados:\n");
    for (i = 0; i < bancoDeDados->qtdEquipamentosCadastrados; i++) {
        if (bancoDeDados->listaEquipamentos[i].idOperadorEquipamento == id) {
            printf("%s | %s | %s | prioridade %s\n",
                   bancoDeDados->listaEquipamentos[i].idEquipamento,
                   bancoDeDados->listaEquipamentos[i].tipoEquipamento,
                   bancoDeDados->listaEquipamentos[i].estadoOperacional,
                   prioridadeEmTexto(bancoDeDados->listaEquipamentos[i].nivelPrioridade));
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Esse operador nao controla nenhum equipamento no momento.\n");
    }
}
void relatorio(struct Informacoes *bancoDeDados) {
    int opcao;
    system("cls");
    while (1) {
        titulo("RELATORIOS OPERACIONAIS");
        printf("| 1 | Listar todos os operadores                            |\n");
        printf("| 2 | Listar ID, nome e status dos operadores de um setor    |\n");
        printf("| 3 | Listar equipamentos de um setor                        |\n");
        printf("| 4 | Listar operadores e equipamentos de um setor           |\n");
        printf("| 5 | Operador com maior numero de operacoes por setor       |\n");
        printf("| 6 | Equipamentos controlados por um operador               |\n");
        printf("| 7 | Voltar                                                |\n");
        linha();
        opcao = lerInteiro("Selecione a opcao: ");
        system("cls");
        switch (opcao) {
            case 1:
                relatorioTodosOperadores(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 2:
                relatorioOperadoresPorSetor(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 3:
                relatorioEquipamentosPorSetor(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 4:
                relatorioOperadoresEquipamentosPorSetor(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 5:
                relatorioMaiorOperadorPorSetor(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 6:
                relatorioEquipamentosPorOperador(bancoDeDados);
                system("pause");
                system("cls");
                break;

            case 7:
                return;

            default:
                printf("Opcao invalida.\n");
                system("pause");
                system("cls");
                break;
        }
    }
}
int pesoNivelOperador(struct Operador op) {
    if (compararTexto(op.nivelOperacional, "Supervisor Tecnico") == 1) return 3;
    if (compararTexto(op.nivelOperacional, "Intermediario") == 1) return 2;
    return 1;
}
int escolherEquipamentoBaixaParaRealocacao(struct Informacoes *bancoDeDados, int indiceEquipamentoAlta) {
    int i;
    int indiceMelhor = -1;
    int indiceOperadorAtual, indiceOperadorMelhor, idOperadorAlta, pesoAtual, pesoMelhor;
    idOperadorAlta = bancoDeDados->listaEquipamentos[indiceEquipamentoAlta].idOperadorEquipamento;
    for (i = 0; i < bancoDeDados->qtdEquipamentosCadastrados; i++) {
        if (i != indiceEquipamentoAlta && bancoDeDados->listaEquipamentos[i].nivelPrioridade == 1 &&
            compararTexto(bancoDeDados->listaEquipamentos[i].setorEquipamento,
                          bancoDeDados->listaEquipamentos[indiceEquipamentoAlta].setorEquipamento) == 1 &&
            bancoDeDados->listaEquipamentos[i].idOperadorEquipamento != 0 &&
            bancoDeDados->listaEquipamentos[i].idOperadorEquipamento != idOperadorAlta) {
            indiceOperadorAtual = buscarIndiceOperadorPorId(bancoDeDados,
                                                            bancoDeDados->listaEquipamentos[i].idOperadorEquipamento);
            if (indiceOperadorAtual != -1 && operadorPodeControlar(bancoDeDados->listaOperadores[indiceOperadorAtual]) == 1) {
                if (indiceMelhor == -1) {
                    indiceMelhor = i;
                } else {
                    indiceOperadorMelhor = buscarIndiceOperadorPorId(bancoDeDados,
                                                                     bancoDeDados->listaEquipamentos[indiceMelhor].idOperadorEquipamento);
                    pesoAtual = pesoNivelOperador(bancoDeDados->listaOperadores[indiceOperadorAtual]);
                    pesoMelhor = pesoNivelOperador(bancoDeDados->listaOperadores[indiceOperadorMelhor]);
                    if (pesoAtual > pesoMelhor) {
                        indiceMelhor = i;
                    } else if (pesoAtual == pesoMelhor &&
                               bancoDeDados->listaOperadores[indiceOperadorAtual].qtdOperacoes >
                               bancoDeDados->listaOperadores[indiceOperadorMelhor].qtdOperacoes) {
                        indiceMelhor = i;
                    }
                }
            }
        }
    }
    return indiceMelhor;
}

void mostrarOperadorTroca(struct Informacoes *bancoDeDados, int idOperador) {
    int indiceOperador;
    if (idOperador == 0) {
        printf("Sem operador");
        return;
    }
    indiceOperador = buscarIndiceOperadorPorId(bancoDeDados, idOperador);
    if (indiceOperador == -1) {
        printf("ID %04d nao encontrado", idOperador);
    } else {
        printf("%04d - %s", idOperador, bancoDeDados->listaOperadores[indiceOperador].nomeOperador);
    }
}
void mostrarEquipamentoTroca(struct Equipamento eq) {
    printf("%s | %s | Setor: %s | Prioridade: %s",
           eq.idEquipamento,
           eq.tipoEquipamento,
           eq.setorEquipamento,
           prioridadeEmTexto(eq.nivelPrioridade));
}
void trocarOperadorAutomaticoPrioridadeAlta(struct Informacoes *bancoDeDados) {
    char id[10];
    int indiceEquipamentoAlta, indiceEquipamentoBaixa, idOperadorSaiuDaBaixa, idOperadorAntigoDaAlta;
    titulo("REALOCAR OPERADOR DE PRIORIDADE BAIXA PARA ALTA");
    if (bancoDeDados->qtdEquipamentosCadastrados == 0) {
        printf("Nenhum equipamento cadastrado.\n");
        return;
    }
    if (bancoDeDados->qtdOperadoresCadastrados == 0) {
        printf("Nenhum operador cadastrado.\n");
        return;
    }
    lerTexto("ID da maquina/equipamento de prioridade alta: ", id, 10);
    deixarMaiusculo(id);
    indiceEquipamentoAlta = buscarIndiceEquipamento(bancoDeDados, id);
    if (indiceEquipamentoAlta == -1) {
        printf("Equipamento nao encontrado.\n");
        printf("Troca realizada: NAO\n");
        return;
    }
    printf("Maquina de destino informada: ");
    mostrarEquipamentoTroca(bancoDeDados->listaEquipamentos[indiceEquipamentoAlta]);
    printf("\n");
    if (bancoDeDados->listaEquipamentos[indiceEquipamentoAlta].nivelPrioridade != 3) {
        printf("Troca realizada: NAO\n");
        printf("Motivo: a maquina de destino nao possui prioridade alta.\n");
        return;
    }
    indiceEquipamentoBaixa = escolherEquipamentoBaixaParaRealocacao(bancoDeDados, indiceEquipamentoAlta);
    if (indiceEquipamentoBaixa == -1) {
        printf("Troca realizada: NAO\n");
        printf("Motivo: nao existe maquina de prioridade baixa no setor %s com operador valido para realocacao.\n",
               bancoDeDados->listaEquipamentos[indiceEquipamentoAlta].setorEquipamento);
        return;
    }
    idOperadorSaiuDaBaixa = bancoDeDados->listaEquipamentos[indiceEquipamentoBaixa].idOperadorEquipamento;
    idOperadorAntigoDaAlta = bancoDeDados->listaEquipamentos[indiceEquipamentoAlta].idOperadorEquipamento;
    bancoDeDados->listaEquipamentos[indiceEquipamentoAlta].idOperadorEquipamento = idOperadorSaiuDaBaixa;
    bancoDeDados->listaEquipamentos[indiceEquipamentoBaixa].idOperadorEquipamento = idOperadorAntigoDaAlta;
    printf("Troca realizada: SIM\n");
    printf("Operador realocado: ");
    mostrarOperadorTroca(bancoDeDados, idOperadorSaiuDaBaixa);
    printf("\n");
    printf("Saiu da maquina: ");
    mostrarEquipamentoTroca(bancoDeDados->listaEquipamentos[indiceEquipamentoBaixa]);
    printf("\n");
    printf("Foi para a maquina: ");
    mostrarEquipamentoTroca(bancoDeDados->listaEquipamentos[indiceEquipamentoAlta]);
    printf("\n");
    if (idOperadorAntigoDaAlta == 0) {
        printf("A maquina de prioridade baixa ficou sem operador responsavel.\n");
    } else {
        printf("Operador que estava na maquina alta foi movido para a maquina baixa: ");
        mostrarOperadorTroca(bancoDeDados, idOperadorAntigoDaAlta);
        printf("\n");
    }
}
void menu(struct Informacoes *bancoDeDados) {
    int opcao;
    while (1) {
        titulo("CENTRAL DE OPERACOES AUTONOMAS - SETOR VX27");
        printf("| 1 | Cadastrar Operador                                    |\n");
        printf("| 2 | Cadastrar Equipamento / Modulo                        |\n");
        printf("| 3 | Atualizar Cadastro                                    |\n");
        printf("| 4 | Consultar Registros                                   |\n");
        printf("| 5 | Relatorios Operacionais                               |\n");
        printf("| 6 | Realocar operador de baixa para alta                 |\n");
        printf("| 7 | Sair                                                  |\n");
        linha();
        opcao = lerInteiro("Selecione a opcao: ");
        system("cls");
        switch (opcao) {
    case 1:
        cadastroOperador(bancoDeDados);
        system("pause");
        system("cls");
        break;

    case 2:
        cadastroEquipamento(bancoDeDados);
        system("pause");
        system("cls");
        break;

    case 3:
        atualizar(bancoDeDados);
        system("cls");
        break;

    case 4:
        consultarRegistro(bancoDeDados);
        system("cls");
        break;

    case 5:
        relatorio(bancoDeDados);
        system("cls");
        break;

    case 6:
        trocarOperadorAutomaticoPrioridadeAlta(bancoDeDados);
        system("pause");
        system("cls");
        break;

    case 7:
        printf("Encerrando o sistema...\n");
        return;

    default:
        printf("Opcao invalida.\n");
        system("pause");
        system("cls");
        break;
}
    }
}
int main(void) {
    setlocale(LC_ALL, "");
    struct Informacoes bancoDeDados = criarBancoDeDados();
    system("cls");
    menu(&bancoDeDados);
    return 0;
}
