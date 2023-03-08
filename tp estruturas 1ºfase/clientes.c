#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"
#include "meio.h"

/**
 * @brief Funcao de abertura do ficheiro de texto referente aos Clientes
 * Depois da abertura os valores são introduzidos na lista ligada
 * 
 * @param Clientes 
 */

void abrirFicheiro(struct cliente** Clientes){

    FILE* file;
    file=fopen("dados Cliente.txt","r");

    
    struct cliente* anterior=NULL;

    char linha[100];
    char *token;

    if (file==NULL){
        printf("Erro na abertura do ficheiro");
        exit(1);
    }

    while(fgets(linha,sizeof(linha),file)!=NULL){
    
        struct cliente* nodo = malloc(sizeof(struct cliente)); // alocar dinamicamente um novo nodo na memoria    

        // nome de utilizador

        token=strtok(linha,";");
        strcpy(nodo->nomeCliente, token);
        printf("\nutilizador: %s\n",nodo->nomeCliente);

        // password
        
        token=strtok(NULL,";");
        nodo->passCliente=atoi(token);
        printf("pass: %d\n",nodo->passCliente);

        // saldo da conta
        
        token=strtok(NULL,";");
        nodo->saldo=atof(token);
        printf("saldo: %.2f\n",nodo->saldo);

        // NIF
        
        token=strtok(NULL,";");
        nodo->nif=atoi(token);
        printf("nif: %d\n",nodo->nif);

        // morada
        
        token=strtok(NULL,";");
        strcpy(nodo->morada, token);
        printf("morada: %s\n",nodo->morada);

        nodo->seguinte = NULL;

        if(anterior==NULL){
            *Clientes=nodo; // coloca o primeiro nodo 
        }else{
            anterior->seguinte=nodo;// liga o nodo anterior ao atual
        }
        anterior=nodo;// atualiza o elemento anterior     
    }
    
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

    // escrever no ficheiro

    struct cliente* novo=*Clientes; // inicio da lista

    while(novo!=NULL){
        fprintf(file,"%s;%d;%.2f;%d;%s;\n",novo->nomeCliente,novo->passCliente,novo->saldo,novo->nif,novo->morada);
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
    getchar();
    gets(nomeNovo_Cliente);
    printf("Indique a sua password: ");
    scanf("%d",&passNova_Cliente);
    printf("Qual é o sua morada: ");
    getchar();
    gets(moradaNova);
    printf("NIF: ");
    scanf("%d",&nif_Novo);
    system("cls"); // para eliminar os prints anteriores
    

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
    system("cls"); // para eliminar os prints anteriores
    

    struct cliente* nodo=*Clientes;

   
    while(strcmp(login,nodo->nomeCliente)!=0){
        nodo=nodo->seguinte;
    }
    
    nodo->saldo+=saldoAcrescentado;

  
    atualizarFicheiroCliente(Clientes);
}

// ALTERAR CLIENTE
void escreverFicheiroHistorico(struct meios* Meios,struct cliente** Clientes, char* alugado,char *login){
   
    
    FILE* file;
    file=fopen("historico.txt","a");

    // escrever no ficheiro

    struct cliente* novo= *Clientes; // inicio da lista
    struct meios* nodo= Meios;

    while(nodo!=NULL){
        if(strcmp(alugado,nodo->meios)==0 ){
            while(novo!=NULL){
                if(strcmp(login,novo->nomeCliente) ==0){
                    fprintf(file,"%s;%d;%s;\n",novo->nomeCliente,novo->nif,nodo->meios);
                }
                novo=novo->seguinte;
            }
        }
        nodo=nodo->seguinte;
    }
    fclose(file);
}


/**
 * @brief funcao utilizada para o cliente alugar um meio
 * ele inicialmente irá mostrar todos os 
 * 
 * @param Meios 
 * @param Clientes 
 * @param login 
 */
void alugarMeio(struct meios* Meios,struct cliente** Clientes, char* login){

    struct cliente* temp=*Clientes;
    struct meios* nodo=Meios;
    char meio_para_alugar[70];


    while(nodo!=NULL){
        if(strcmp(nodo->estado,"livre")==0){
    
            printf("Meio: %s; Bateria: %d; Preco: %.2f; Autonomia: %d; localizacao: %s\n",nodo->meios,
            nodo->bateria,nodo->preco,nodo->autonomia,nodo->localizacao);
            
        }
        nodo=nodo->seguinte;
    }
    

    printf("Qual é o meio que pretende alugar?");
    scanf("%s", meio_para_alugar);

    while(temp!=NULL){
        nodo = Meios;
        if(strcmp(login,temp->nomeCliente)==0){
            while(nodo!=NULL){
                if(strcmp(meio_para_alugar,nodo->meios)==0){
                    temp->saldo-=nodo->preco;
                    strcpy(nodo->estado,"ocupado");
                    break;
                }
                nodo=nodo->seguinte;
            } 
        }
        temp=temp->seguinte;
    }
   escreverFicheiroHistorico(Meios,Clientes,meio_para_alugar,login);
   atualizarFicheiroCliente(Clientes);
   atualizarFicheiroMeios(&Meios);
}