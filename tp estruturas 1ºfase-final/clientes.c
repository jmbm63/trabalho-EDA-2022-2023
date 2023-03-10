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
        
        // password
        token=strtok(NULL,";");
        nodo->passCliente=atoi(token);
        
        // saldo da conta
        token=strtok(NULL,";");
        nodo->saldo=atof(token);
        
        // NIF
        token=strtok(NULL,";");
        nodo->nif=atoi(token);
        
        // morada
        token=strtok(NULL,";");
        strcpy(nodo->morada, token);
        
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
 * A lista ligada é percorrida e ao mesmo tempo é feita a impressao da informacao da lista no ficheiro
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
 * @brief Esta funcao é utilizada Quando o utilizador quer colocar dinheiro na sua conta,
 * ou apenas consultar o seu saldo
 * 
 * 
 * @param Clientes 
 * @param login 
 */
void acrescentarSaldo(struct cliente ** Clientes,char* login){


    int saldoAcrescentado;
    int escolha;
    int loop=0;
    
    struct cliente* temp;

    while (loop!=1){
        printf("Para consultar saldo prima 1\nPara adicionar saldo prima 2:");
        scanf("%d",&escolha);

        switch (escolha){

            case 1:
                // caso o cliente queira apenas verificar o seu saldo
                temp=*Clientes;
                while(strcmp(login,temp->nomeCliente)!=0){
                    temp=temp->seguinte;
                }

                int sa;
                printf("O seu saldo e: %.2f",temp->saldo);
                printf("\nDeseja acrescentar saldo?\n0->Sim\n1->Nao");
                scanf("%d",&sa);
                system("cls");

                if(sa==1) {
                    loop=1;
                }else if(sa==0){
                    loop=0;
                }

            break;

            // caso o cliente queira adicionar uma quantia ao seu saldo
            case 2:

                printf("Coloque a quantia: ");
                scanf("%d",&saldoAcrescentado);
                system("cls"); // para eliminar os prints anteriores
    
                struct cliente* nodo=*Clientes;
                while(strcmp(login,nodo->nomeCliente)!=0){
                    nodo=nodo->seguinte;
                }
                nodo->saldo+=saldoAcrescentado;
                loop=1;
            break;
        }
    }
    atualizarFicheiroCliente(Clientes);
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

    // Variaveis utilizadas
    char nomeNovo_Cliente[50]; // nome do utilizador a criar
    int passNova_Cliente;  // password do utilizador a criar
    int nif_Novo;
    char moradaNova[50];
    int saldo = 0; // inicializado a zero, depois tera uma nova função para acrescentar saldo

    // Contacto com o utiliador
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
    
    // copia da unformacao para a lista
    // inserido no inicio

    strcpy(nodo->nomeCliente,nomeNovo_Cliente);
    nodo->passCliente = passNova_Cliente;
    strcpy(nodo->morada,moradaNova);
    nodo->nif = nif_Novo;
    nodo->saldo = saldo;

    nodo->seguinte = *Clientes;
    
    *Clientes = nodo;

    int saldoConta;
    printf("Quer acrescentar saldo a sua conta?");
    scanf("%d",&saldoConta);

    if(saldoConta==1){ // caso queira adicionar saldo entra na funcao acrescentarSaldo()
        acrescentarSaldo(Clientes,nodo->nomeCliente);
    }else{
        atualizarFicheiroCliente(Clientes);
    }  
}

//Apagar Conta
/**
 * @brief O utilizador se quiser deletar a conta, irá para esta funcao
 * 
 * No login encontrar o nodo, passar-lo com argumento e de seguida eliminar esse mesmo nodo
 * 
 * @param Clientes 
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

// ALTERAR CLIENTE
/**
 * @brief Nesta funcao é utilizada para que todos os alugueres sejam guardados no ficheiro txt
 * 
 * @param Meios 
 * @param Clientes 
 * @param alugado 
 * @param login 
 */
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
 * 
 * 
 * @param Meios 
 * @param Clientes 
 * @param login 
 */
void alugarMeio(struct meios* Meios,struct cliente** Clientes, char* login){

    struct cliente* temp=*Clientes;
    struct meios* nodo=Meios;

    char meio_para_alugar[70];
    int loop=0;
    int opcao;

    while(loop!=1){ // loop iniciado para que caso o cliente nao queira alugar o meio devido a localizacao

        while(nodo!=NULL){
            if(strcmp(nodo->estado,"livre")==0 && nodo->bateria>=10){ // informar o cliente todos os meios livres

                printf("Meio: %s; Bateria: %d; Preco: %.2f; Autonomia: %d; localizacao: %s\n",nodo->meios,
                nodo->bateria,nodo->preco,nodo->autonomia,nodo->localizacao);
            }
            nodo=nodo->seguinte;
        }
        
        // iteracao com o utilizador
        printf("Qual é o meio que pretende alugar?");
        scanf("%s", meio_para_alugar);
 
        printf("Deseja abrir a localizacao do mesmo?");
        scanf("%d",&opcao);

        // abrir a localizacao do meio de mobilizacao
        struct meios* Local=Meios;
        while(Local!=NULL){
        
            if(opcao==1 && strcmp(meio_para_alugar,Local->meios)==0){
                char url[1000];
                sprintf(url, "START https://what3words.com/%s", Local->localizacao);
                system(url);
                break;
            }
            else if(opcao==2){
            }
            Local=Local->seguinte;
        }
    
        // Proceder com o aluguer do meio
        printf("Se Deseja Proceder com o Aluguer do Meio digite 1:");
        scanf("%d",&opcao);
        
        if(opcao==1){
           
            while(temp!=NULL){
                nodo = Meios;
                if(strcmp(login,temp->nomeCliente)==0){
                    while(nodo!=NULL){
                        if(strcmp(meio_para_alugar,nodo->meios)==0){
                            loop=1;
                            temp->saldo-=nodo->preco;
                            strcpy(nodo->estado,"ocupado");
                            nodo->bateria=nodo->bateria-10;

                            break;
                        }
                        nodo=nodo->seguinte;
                    } 
                }
                temp=temp->seguinte;
            } 
        }
    }
   escreverFicheiroHistorico(Meios,Clientes,meio_para_alugar,login);
   atualizarFicheiroCliente(Clientes);
   atualizarFicheiroMeios(&Meios);
}



