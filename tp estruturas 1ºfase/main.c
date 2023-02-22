#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"

int main(){

    
    struct gestor* Gestores=malloc(sizeof(struct gestor));
    //struct cliente* Clientes=malloc(sizeof(struct cliente));
    //struct maquina* Meios=malloc(sizeof(struct maquina));

    int confirmar;
    int gest; // para os gestores


    printf("Iniciar sessão como: \n");
    printf("1 Gestor: \n2 Cliente:\n ");
    scanf("%d",&confirmar);
   
    switch (confirmar) {
        case 1:
            readFile(Gestores);
            printf("Escolha a operacao:\n");
            printf("1 Criar Gestor: \n2 Remover Gestor:\n3 Alterar Gestor: "); 
            scanf("%d",&gest);

            switch(gest){
                case 1:
                    criarGestor(&Gestores);
                break;

                case 2:

                break;
            }
        break;

        case 2: // para os clientes

        break;
    }
    return 0;

}