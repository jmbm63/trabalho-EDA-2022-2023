#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"
#include "clientes.h"

// leitura do ficheiro e insercao na lista ligada
void readFile(struct gestor** Gestores){
    FILE *file;
    file = fopen("dados Gestores.txt", "r");

    struct gestor *nodo = malloc(sizeof(struct gestor)); // inicio da lista    
    *Gestores = nodo; // atribuicao do primeiro nodo

    char linha[20];
    char *token;

    if (file == NULL) {
        printf("Erro na abertura do ficheiro");
        exit(1);
    }
    while (!feof(file)){

        fscanf(file,"%s",linha);
        token=strtok(linha,";");
        strcpy(nodo->nomeGestor, token);
        printf("%s;",nodo->nomeGestor);

        fscanf(file,"%s",linha);
        token=strtok(linha,";");
        nodo->passGestor=atoi(token);
        printf("%d\n",nodo->passGestor);

        nodo->seguinte = malloc(sizeof(struct gestor));
        nodo = nodo->seguinte;        
    }
    nodo->seguinte = NULL;
    fclose(file);
}

// atualizaçao do ficheiro de texto
void atualizarFicheiro(struct gestor** Gestores){

    FILE* file;
    file=fopen("dados Gestores.txt","w");// a, acrescenta no fim do ficheiro

    char *token;
    char linha[20];

    // escrever no ficheiro

    struct gestor*nodo=*Gestores; // inicio da lista

    while(!feof(file) && nodo!=NULL){
        fprintf(file,"%s;\n%d;\n",nodo->nomeGestor,nodo->passGestor);
        nodo=nodo->seguinte;
    }

    fclose(file);
}

// criar um novo gestor
void criarGestor(struct gestor** Gestores){

   
    struct gestor* nodo = malloc(sizeof(struct gestor));
    //struct gestor*novo=*Gestores; // inicio da lista

    char nomeTemp[50]; // nome do utilizador a criar
    int passTemp;  // password do utilizador a criar

    printf("Qual é o nome do novo gestor: ");
    scanf("%s",nomeTemp);
    printf("Indique a sua password: ");
    scanf("%d",&passTemp);

    strcpy(nodo->nomeGestor,nomeTemp);
    nodo->passGestor = passTemp;
    nodo->seguinte = *Gestores;
    
    *Gestores = nodo;

    atualizarFicheiro(Gestores);
}

// Remover gestor
void removerGestor(struct gestor** Gestores){

    char nomeRemover[50]; // nome a remover

    printf("\nQual é o gestor que pretende remover? ");
    scanf("%s", nomeRemover);

    /* struct gestor* temp = *Gestores;// leva me para o inicio da lista
    while(temp!=NULL){// percorre a lista -> confirmação que os dados estao sendo inseridos

        printf("Este PRINT%s;%d;\n",temp->nomeGestor,temp->passGestor);
        temp=temp->seguinte;

    }  
     // percorre a lista e procura pelo gestor a ser removido
    while(nodo!=NULL){
        printf("1::::::%s\n",nodo->nomeGestor);
        // se o nodo atual ja for o gestor a ser eliminado
        if(strcmp(nodo->nomeGestor,nomeRemover)==0){
            printf("2::::::%s\n",nodo->nomeGestor);
            *Gestores=nodo->seguinte;
            free(nodo);
            return;
           
        }
        printf("3::::::%s\n",nodo->nomeGestor);
        //anterior=nodo;
        nodo=nodo->seguinte;
    }*/

    
    struct gestor* Temp;

    if(strcmp((*Gestores)->nomeGestor,nomeRemover)==0){
        Temp=*Gestores;
        *Gestores=(*Gestores)->seguinte;
        free(Temp);
    }else{

        struct gestor* nodo = *Gestores;

        while(nodo->seguinte!=NULL){

            if(strcmp(nodo->seguinte->nomeGestor,nomeRemover)==0){

                Temp=nodo->seguinte;
                nodo->seguinte=nodo->seguinte->seguinte;
                free(Temp);
                break;
            }else{
                nodo=nodo->seguinte;
            }
        }
    }      
    // Atualiza o ficheiro de gestores
    atualizarFicheiro(Gestores);
}


// alterar informacao de um gestor
void alterarGestor(struct gestor** Gestores){

    struct gestor*nodo=*Gestores;

    int operacao; 
    char novoNome[50];
    char nomeRemover[50];
    int novaPass;

    printf("O que pretende fazer:\n1->alterar nome:\n2->alterar password:");
    scanf("%d",&operacao);

    switch (operacao){

        // Alterar nome do gestor
        case 1:

            printf("Qual é o nome do gestor que prentede alterar:");
            scanf("%s",nomeRemover);
            printf("Qual é o novo nome:");
            scanf("%s",novoNome);

            while(strcmp(nomeRemover, nodo->nomeGestor) != 0){ // se forem diferentes retorna um valor !0
                nodo=nodo->seguinte;
            }
            
            strcpy(nodo->nomeGestor, novoNome);

            struct gestor* temp = *Gestores;// leva me para o inicio da lista
            while(temp!=NULL){// percorre a lista -> confirmação que os dados estao sendo inseridos

            printf("\n%s;%d;",temp->nomeGestor,temp->passGestor);
            temp=temp->seguinte;
            }

            //atualizarFicheiro(); //CONFIRMAR DEPOIS
        break;

        // alterar a Password
        case 2:
            printf("Qual é a password do gestor que prentede alterar:");
            scanf("%s",nomeRemover);
            printf("Qual é a nova pass:");
            scanf("%d",&novaPass);

            while(strcmp(nodo->nomeGestor, nomeRemover) != 0){ // se forem diferentes retorna um valor !0
                nodo=nodo->seguinte;
            }
            nodo->passGestor=novaPass;
             
        break;
        }
    atualizarFicheiro(Gestores);
}  
    
// remover um clientes
void removerCliente(struct cliente** Clientes){

    char clienteRemover[50];

    printf("\nCliente a remover:");
    scanf("%s",clienteRemover);

    struct cliente* temp;
    
    if(strcmp((*Clientes)->nomeCliente,clienteRemover)==0){
        temp=*Clientes;
        *Clientes=(*Clientes)->seguinte;
        free(temp);
    }else{
        struct cliente* nodo=*Clientes;

        while(nodo->seguinte!=NULL){

            if(strcmp(nodo->seguinte->nomeCliente,clienteRemover)==0){

                temp=nodo->seguinte;
                nodo->seguinte=nodo->seguinte->seguinte;
                free(temp);
            }
            nodo=nodo->seguinte;
        }
    }

    // Imprimir a lista atualizada
/*      struct cliente* ala = *Clientes;
    while(ala!=NULL){
        printf("\n%s;\n%d;\n%.2f;\n%d;\n%s;",ala->nomeCliente,ala->passCliente,ala->saldo,ala->nif,ala->morada);
        ala=ala->seguinte;
    }  */
     
    atualizarFicheiroCliente(Clientes);
} 
    


