#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"
#include "clientes.h"

int main(){

    
    struct gestor* Gestores=malloc(sizeof(struct gestor));
    struct cliente* Clientes=malloc(sizeof(struct cliente));
    //struct maquina* Meios=malloc(sizeof(struct maquina));

   
    
    
    

    int confirmar;
    int gest; // para os gestores
    int opCliente;// para os clientes

    printf("Iniciar sessão como: \n");
    printf("1 Gestor: \n2 Cliente:\n ");
    scanf("%d",&confirmar);
   
    switch (confirmar) {
        case 1:

            printf("Escolha a operacao:\n1 Criar Gestor: \n2 Remover Gestor:\n3 Alterar Gestor: "); 
            scanf("%d",&gest);
            //abrirFicheiro(Clientes);
            readFile(Gestores);
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
                  //  removerCliente(&Gestores,&Clientes);
                  break;

            }
        break;

        case 2: // para os clientes
            printf("Escolha a operacao:\n1->Criar Cliente: \n2->Apagar Conta:\n3->Alugar Meio de Mobilizacao:\n4->Consultar saldo:");
            scanf("%d",&opCliente);

            switch(opCliente){
                
                // Criar Conta
                case 1:

                    criarCliente(&Clientes);

                break;
                
                // Apagar Conta
                case 2:


                break;    

                // Alugar meio
                case 3:

                break;

                // Consultar Saldo
                case 4:

                break;

            }




        break;
    }
    return 0;

}