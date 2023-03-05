#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"
#include "clientes.h"

int main(){

    // incializacao das lista a NULL
    struct gestor* Gestores=NULL;
    struct cliente* Clientes=NULL;
    //struct maquina* Meios=malloc(sizeof(struct maquina));


// Leitura dos ficheiros
    readFile(&Gestores);
    abrirFicheiro(&Clientes);
    
    int confirmar;
    int gest; // para os gestores
    int opCliente;// para os clientes
    char login[20];
    int passLogin;


    struct gestor* temp = Gestores;
    struct cliente* tempCliente = Clientes;


    printf("\nIniciar sessão como: \n");
    printf("1->Gestor: \n2->Cliente:\n3->Criar Conta:\n");
    scanf("%d",&confirmar);
   
    switch (confirmar) {
        case 1:

            // Codigo para o Log-in dos Gestores
            printf("Faca o seu log-in: ");
            scanf("%s",login);
            printf("Indique a pass: ");
            scanf("%d",&passLogin);
 
            // Percorrer a lista dos Gestores
            while(temp!=NULL){ 

                if(strcmp(login,temp->nomeGestor)==0 && passLogin==temp->passGestor){
            
                    printf("Login feito com sucesso\nEscolha a operacao:\n1->Criar Gestor: \n2->Remover Gestor:\n3->Alterar Gestor:\n4->Remover Cliente: "); 
                    scanf("%d",&gest);
                    break;
                }
                temp=temp->seguinte;
            }
            if(temp==NULL){// caso o Gestor nao exista
                printf("PassWord ou Nome de utilizador Invalidos!");
            }
           
 /**
 * @brief Implementacao de um Menu para os Gestores
 * 
 */
            switch(gest){
                case 1:
                    criarGestor(&Gestores);
                break;

                case 2:
                    removerGestor(&Gestores);
                break;

                case 3:
                    alterarGestor(&Gestores);
                break;

                case 4:
                    removerCliente(&Clientes);
                break;

            }
        break;

        // para os clientes
        case 2: 

            // Codigo para o Log-in dos Clientes
            printf("Faca o seu log-in: ");
            scanf("%s",login);
            printf("Indique a pass: ");
            scanf("%d",&passLogin);
 
            // percorrer a lista dos Clientes
            while(tempCliente!=NULL){
                if(strcmp(login,tempCliente->nomeCliente)==0 && passLogin==tempCliente->passCliente){

                    printf("Login feito com sucesso!\nEscolha a operacao:\n1->Apagar Conta:\n2->Alugar Meio de Mobilizacao:\n3->Consultar saldo:");
                    scanf("%d",&opCliente);
                    break; // para sair do while
                }
                tempCliente=tempCliente->seguinte;
            }  
            if(tempCliente==NULL){ // caso o cliente não exista
                printf("PassWord ou Nome de utilizador Invalidos!");
            }

/**
 * @brief Implementacao de um Menu para os clientes
 * 
*/
            switch(opCliente){
                
                // Apagar Conta
                case 1:
                    apagarConta(&Clientes,login);

                break;    

                // Alugar meio
                case 2:

                break;

                // Consultar Saldo/Acrescentar saldo
                case 3:
                    acrescentarSaldo(&Clientes,login);
                break;

            }
        break;

/**
* @brief para os utilizadores novos e dada a opcao de criar conta
* 
*/
        case 3:
        // Criar Conta para os clientes 
            criarCliente(&Clientes);
        break;
    }
    return 0;
}