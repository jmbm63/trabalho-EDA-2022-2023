#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"

/**
 * @brief Funcao de abertura do ficheiro de texto referente aos Clientes
 * Depois da abertura os valores são introduzidos na lista ligada
 * 
 * @param Clientes 
 */

void abrirFicheiro(struct cliente** Clientes){

    FILE* file;
    file=fopen("dados Cliente.txt","r");

    struct cliente* nodo = malloc(sizeof(struct cliente)); // alocar dinamicamente um novo nodo na memoria    
    *Clientes = nodo;

    char linha[20];
    char *token;

    if (file==NULL){
        printf("Erro na abertura do ficheiro");
        exit(1);
    }

    while(!feof(file)){
    
        // nome de utilizador
        fscanf(file,"%s",linha);
        token=strtok(linha,";");
        strcpy(nodo->nomeCliente, token);
        printf("\nutilizador: %s\n",nodo->nomeCliente);

        // password
        fscanf(file,"%s",linha);
        token=strtok(linha,";");
        nodo->passCliente=atoi(token);
        printf("pass: %d\n",nodo->passCliente);

        // saldo da conta
        fscanf(file,"%s",linha);
        token=strtok(linha,";");
        nodo->saldo=atoi(token);
        printf("saldo: %.2f\n",nodo->saldo);

        // NIF
        fscanf(file,"%s",linha);
        token=strtok(linha,";");
        nodo->nif=atoi(token);
        printf("nif: %d\n",nodo->nif);

        // morada
        fscanf(file,"%s",linha);
        token=strtok(linha,";");
        strcpy(nodo->morada, token);
        printf("morada: %s\n",nodo->morada);

        nodo->seguinte = malloc(sizeof(struct cliente));
        nodo = nodo->seguinte;        
    }
    nodo->seguinte = NULL;
    fclose(file);
}


/**
 * @brief Funcao chamada quando é feita alguma alteracao à lista que deva constar no ficheiro de texto
 * 
 * A lista ligada é percorrida e ao mesmo tempo é feita a impressao da informacao no ficheiro
 * 
 * @param Clientes 
 */
void atualizarFicheiroCliente(struct cliente** Clientes){

    FILE* file;
    file=fopen("dados Cliente.txt","w");

    char *token;
    char linha[20];

    // escrever no ficheiro

    struct cliente* novo=*Clientes; // inicio da lista

    while(novo!=NULL){
        fprintf(file,"%s;\n%d;\n%.2f;\n%d;\n%s;\n",novo->nomeCliente,novo->passCliente,novo->saldo,novo->nif,novo->morada);
        novo=novo->seguinte;
    }

    fclose(file);
}

/**
 * @brief A funcao é utilizada para um cliente se inscrever na aplicacao
 * 
 * @param Clientes 
 */
void criarCliente(struct cliente** Clientes){

    // Para criar o cliente é necessario:
    // nome, morada,password,saldo,nif

    struct cliente *nodo = malloc(sizeof(struct cliente)); // alocar dinamicamente na memoria


    char nomeNovo_Cliente[50]; // nome do utilizador a criar
    int passNova_Cliente;  // password do utilizador a criar
    int nif_Novo;
    char moradaNova[50];

    int saldo = 0; // inicializado a zero, depois tera uma nova função para acrescentar saldo

    printf("\nQual é o seu nome: ");
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

    //printf("%d",nodo->passCliente);
    nodo->seguinte = *Clientes;
    
    *Clientes = nodo;
    
    atualizarFicheiroCliente(Clientes);
}


//Apagar Conta
/**
 * @brief O utilizador se quiser deletar a conta, irá para esta funcao
 * 
 * No login encontrar o nodo, passar-lo com argumento e de seguida eliminar esse mesmo nodo
 * 
 * @param Clientes 
 * 
 * Imprime lixo no fim
 */
void apagarConta(struct cliente** Clientes,char* login){
    
    struct cliente *nodo=*Clientes;
    struct cliente *temp; // variavel para guarda o nodo do cliente a ser removido

    if(strcmp(login,(*Clientes)->nomeCliente)==0){

        temp=*Clientes;
        *Clientes=(*Clientes)->seguinte;
        free(temp);
    }else{

        while(nodo->seguinte!=NULL){
            if(strcmp(login,(*Clientes)->nomeCliente)!=0){

                temp=nodo->seguinte;
                nodo->seguinte=nodo->seguinte->seguinte;
                free(temp);
            }
            nodo=nodo->seguinte; 
        }
    } 
    atualizarFicheiroCliente(Clientes);
}

/**
 * @brief Esta funcao é utilizada Quando o utilizador quer colocar dinheiro na sua conta
 * Imprime lixo no fim
 * @param Clientes 
 * @param login 
 */
void acrescentarSaldo(struct cliente ** Clientes,char* login){


    int saldoAcrescentado;
    
    printf("Coloque a quantia: ");
    scanf("%d",&saldoAcrescentado);

    struct cliente* nodo=*Clientes;

   
    while(strcmp(login,nodo->nomeCliente)!=0){
        nodo=nodo->seguinte;
    }
    
    nodo->saldo+=saldoAcrescentado;

  
    atualizarFicheiroCliente(Clientes);
}