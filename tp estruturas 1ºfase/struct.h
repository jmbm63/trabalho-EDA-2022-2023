#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cliente{

    char nomeCliente[50];

    int passCliente;

    float saldo;

    int nif;

    char morada[50];
    
    struct cliente* seguinte;

};


struct gestor{

    char nomeGestor[50];

    int passGestor;

    struct gestor* seguinte;
};

struct maquinas{

    char meios[10]; // meios de mobilizacao

    int bateria;

    float preco;

    int autonomia;
    
    char localizacao[25];

    struct maquinas* seguinte;
};