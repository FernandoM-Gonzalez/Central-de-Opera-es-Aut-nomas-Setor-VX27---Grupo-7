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

int main(){




    return 0;
}
