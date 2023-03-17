#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"
#include "clientes.h"
#include "meio.h"


int main(){

    // incializacao das lista a NULL
    struct gestor* Gestores=NULL;
    struct cliente* Clientes=NULL;
    struct meios* Meios=NULL;
   
    // Leitura dos ficheiros
    readFile(&Gestores);
    abrirFicheiro(&Clientes);
    lerFicheiro(&Meios);

    // variaveis auxiliares    
    int confirmar;
    int gest; // para os gestores
    int opCliente;// para os clientes
    char login[20];
    int passLogin;


    struct gestor* temp = Gestores;
    struct cliente* tempCliente = Clientes;
    

    ordemDecrescente(&Meios);//funcao que ordena a lista por ordem decrescente de autonomia

    //Impressao da lista alterada na funcao a cima
    struct meios*nodo_Atual=Meios;
    while(nodo_Atual!=NULL){
        printf("\n%s;%d;%.2f;%d;%s;%s",nodo_Atual->meios,nodo_Atual->bateria,nodo_Atual->preco,nodo_Atual->autonomia,nodo_Atual->localizacao,nodo_Atual->estado);
        nodo_Atual=nodo_Atual->seguinte;
    }


    printf("\nIniciar sessão como: \n1->Gestor: \n2->Cliente:\n3->Criar Conta:\n");
    scanf("%d",&confirmar);
    system("cls"); // para eliminar os prints anteriores

    switch (confirmar) {

        // Para os gestores
        case 1:

            // Codigo para o Log-in dos Gestores
            printf("Faca o seu log-in: ");
            scanf("%s",login);
            printf("Indique a pass: ");
            scanf("%d",&passLogin);
            system("cls"); 
    

            // Percorrer a lista dos Gestores
            while(temp!=NULL){ 
                if(strcmp(login,temp->nomeGestor)==0 && passLogin==temp->passGestor){ // caso a passWord e o nome estiverem corretos o gestor tera acesso às opcoes
            
                    printf("Login feito com sucesso\nEscolha a operacao:\n1->Criar Gestor:\n2->Remover Gestor:\n3->Alterar Gestor:""\n4->Remover Cliente:\n5->Obter Informacao dos clientes:"
                    "\n6->Adicionar Meio de Mobilizacao:\n7->Remover Meio de Mobilizacao:\n8-> Localizar Meio de Mobilizacao:\n9->Alterar Meios de Mobilizacao: "); 
                    scanf("%d",&gest);

                    system("cls"); 
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

                // criar Gestor
                case 1:
                    criarGestor(&Gestores);
                break;

                // remover Gestor
                case 2:
                    removerGestor(&Gestores);
                break;

                // alterar Gestor
                case 3:
                    alterarGestor(&Gestores);
                break;

                // Remover Cliente
                case 4:
                    removerCliente(&Clientes);
                break;

                // Informacao dos clientes
                case 5:
                    infoClientes(Clientes);
                break;

                // Adicionar meio
                case 6:
                    acrescentarMeio(&Meios);;
                break;

                // Remover meio
                case 7: 
                    removerMeio(&Meios);
                break;
            
                //Localizar meio
                case 8:
                    localizarMeio(Meios);
                break; 

                //Alterar meio
                case 9:
                    alterarMeio(&Meios);
                break; 

                default:
                    printf("Erro");
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
            system("cls"); // para eliminar os prints anteriores
    
 
            // percorrer a lista dos Clientes
            while(tempCliente!=NULL){

                if(strcmp(login,tempCliente->nomeCliente)==0 && passLogin==tempCliente->passCliente){

                    printf("Login feito com sucesso!\nEscolha a operacao:\n1->Apagar Conta:\n2->Alugar Meio de Mobilizacao:\n3->Consultar saldo:");
                    scanf("%d",&opCliente);

                    system("cls");
                    break; 

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
                    alugarMeio(Meios,&Clientes,login);
                break;

                // Consultar Saldo/Acrescentar saldo
                case 3:
                    acrescentarSaldo(&Clientes,login);
                break;

                default:
                    printf("Erro");
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

        default:
            printf("Erro");
        break;
    }

    return 0;
}