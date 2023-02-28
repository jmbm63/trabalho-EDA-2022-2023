#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"

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
        printf("%s",nodo->nomeGestor);

        fscanf(file,"%s",linha);
        token=strtok(NULL,";\n");
        nodo->passGestor=atoi(token);
        printf("%d",nodo->passGestor);

        nodo->seguinte = malloc(sizeof(struct gestor));
        nodo = nodo->seguinte;        
    }
    //nodo->seguinte = NULL;
    fclose(file);
}

void atualizarFicheiro(struct gestor** Gestores,int passTemp,char nomeTemp[50]){

    FILE* file;
    file=fopen("dados Gestores.txt","a");// a, acrescenta no fim do ficheiro

    char *token;
    char linha[20];

    // escrever no ficheiro

    struct gestor*nodo=*Gestores; // inicio da lista

    if(!feof(file)){
        fprintf(file,"%s;%d",nodo->nomeGestor,nodo->passGestor);
    }

    fprintf(file, "\n%s;%d;", nomeTemp, passTemp);

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

    atualizarFicheiro(&Gestores,passTemp,nomeTemp);
}

// Remover gestor
void removerGestor(struct gestor** Gestores){

    struct gestor* nodo = *Gestores,*anterior; // gestores é a referencia 
    //struct gestor* nodoAnterior = NULL; // inicializa o nó anterior a NULL

    
    char nomeRemover[50]; // nome a remover

    printf("Qual é o cliente que pretende remover? ");
    scanf("%s", nomeRemover);
   
   // se o nodo atual ja for o gestor a ser eliminado
    if(nodo!=NULL && strcmp(nodo->nomeGestor,nomeRemover)==0){//strcmp retorna 0 se as duas strings forem iguais

        *Gestores=nodo->seguinte;
        free(nodo);
        return;
    }

    // percorre a lista e procura pelo gestor a ser removido
    while(nodo!=NULL && strcmp(nodo->nomeGestor,nomeRemover)!=0){
        printf("%s",nodo->nomeGestor);
        anterior=nodo;
        nodo=nodo->seguinte;
    }

    // se o gestor nao estiver presente na lista de gestores
    if(nodo==NULL){
        printf("Esse gestor nao existe!");
        return;
    }

    anterior->seguinte=nodo->seguinte;

    free(nodo); // liberta a memória alocada pelo nó removido
    // Atualiza o ficheiro de gestores
    // atualizarFicheiro(Gestores);
}

void alterarGestor(struct gestor** Gestores){

    struct gestor*nodo=*Gestores;

    int operacao; 
    char novoNome[50];
    char nomeRemover[50];
    int oldPass;
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

            //atualizarFicheiro(); //CONFIRMAR DEPOIS
        break;

        // alterar a Password
        case 2:
            printf("Qual é a password do gestor que prentede alterar:");
            scanf("%d",oldPass);
            printf("Qual é a nova pass:");
            scanf("%d",novaPass);

            while(oldPass!=nodo->passGestor){ // se forem diferentes retorna um valor !0
                nodo=nodo->seguinte;
            }
            
            nodo->passGestor=novaPass;

            //atualizarFicheiro(); // CONFIRMAR DEPOIS

        break;
    }
}