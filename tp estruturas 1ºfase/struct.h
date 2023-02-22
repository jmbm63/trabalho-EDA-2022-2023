#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct cliente{

    float saldo;

    int pass[10];
    
    char nome;

    char morada[50];

    char nif[9];// talves int?

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
    
    char localizacao[25];

    struct maquinas* seguinte;
};






