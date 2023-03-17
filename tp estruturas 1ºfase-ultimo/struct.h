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

struct meios{

    char meios[50]; // meios de mobilizacao

    int bateria;

    float preco;

    int autonomia;
    
    char localizacao[25];

    char estado[10];

    struct meios* seguinte;
};