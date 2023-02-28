#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"


void abrirFicheiro(struct cliente* Clientes){

    FILE* file;
    file=fopen("dados Cliente.txt","r");

    struct cliente* nodo = malloc(sizeof(struct cliente)); // inicio da lista    

    char linha[20];
    char *token;

    if (file==NULL){
        printf("Erro na abertura do ficheiro");
        exit(1);
    }


    while(!feof(file)){
    
        
        // nome de utilizador
        fscanf(file,"%s",linha);
        token=strtok(linha,"\n");
        strcpy(nodo->nomeCliente, token);
        printf("utilizador: %s\n",nodo->nomeCliente);

        // password
        fscanf(file,"%s",linha);
        token=strtok(NULL,";");
        nodo->passCliente=atoi(token);
        printf("pass: %d\n",nodo->passCliente);

        // saldo da conta
        fscanf(file,"%s",linha);
        token=strtok(NULL,";");
        nodo->saldo=atoi(token);
        printf("saldo: %f\n",nodo->saldo);

        // NIF
        fscanf(file,"%s",linha);
        token=strtok(NULL,";");
        nodo->nif=atoi(token);
        printf("nif: %d\n",nodo->nif);

        // morada
        fscanf(file,"%s",linha);
        token=strtok(NULL,";\n");
        strcpy(nodo->morada, token);
        printf("morada: %s\n",nodo->morada);

        nodo = nodo->seguinte;

    }
    //printf("%s",nodo->nomeGestor); // da nulo porque estou no fim da lista
    
    fclose(file);
}


void criarCliente(struct cliente** Clientes){

    // Para criar o cliente é necessario:
    // nome, morada,password,saldo,nif

    struct cliente *nodo = malloc(sizeof(struct cliente)); // corrigido para struct cliente
    //struct cliente *novo = *Clientes; // inicio da lista


    char nomeNovo_Cliente[50]; // nome do utilizador a criar
    int passNova_Cliente;  // password do utilizador a criar
    int nif_Novo;
    char moradaNova[50];

    int saldo = 0; // inicializado a zero, depois tera uma nova função para acrescentar saldo

    printf("Qual é o seu nome: ");
    scanf("%s",nomeNovo_Cliente);
    printf("Indique a sua password: ");
    scanf("%d",&passNova_Cliente);
    printf("Qual é o sua morada: ");
    scanf("%s",moradaNova);
    printf("NIF: ");
    scanf("%d",&nif_Novo);

    strcpy(nodo->nomeCliente,nomeNovo_Cliente);
    nodo->passCliente = passNova_Cliente;
    strcpy(nodo->morada,moradaNova);
    nodo->nif = nif_Novo;
    nodo->saldo = saldo;

    printf("%d",nodo->passCliente);
    nodo->seguinte = *Clientes;
    
    *Clientes = nodo;
}

/* void apagarConta(struct cliente** Clientes){

    struct gestor*novo=*Gestores;

    if(nodo->nomeCliente==nomeRemover){
        nodo=nodo->seguinte;
        free(nodo);
    }else{

        nodo=nodo->seguinte;
        while(nodo!=NULL&& nodo->nomeCliente!=nomeRemover){
            nodo=nodo;
            nodo=nodo->seguinte;
        }
        free(nodo);
    }
}
 */


/* void registoAluguel(){
 
} */





















