#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"
#include "clientes.h"
#include "meio.h"

/**
 * @brief Leitura do ficheiro e insercao dos dados na lista
 * 
 * @param Gestores 
 * @return * leitura 
 */
void readFile(struct gestor** Gestores){
    FILE *file;
    file = fopen("dados Gestores.txt", "r");

    struct gestor *anterior=NULL;

    char linha[100];
    char *token;

    if (file == NULL) {
        printf("Erro na abertura do ficheiro");
        exit(1);
    }
    while (fgets(linha,sizeof(linha),file)!=NULL){

        struct gestor *nodo = malloc(sizeof(struct gestor)); // inicio da lista

        token=strtok(linha,";");
        strcpy(nodo->nomeGestor, token);
        printf("%s;",nodo->nomeGestor);


        token=strtok(NULL,";");
        nodo->passGestor=atoi(token);
        printf("%d\n",nodo->passGestor);

        nodo->seguinte = NULL;

        if(anterior==NULL){
            *Gestores=nodo; // coloca o primeiro nodo 
        }else{
            anterior->seguinte=nodo;// liga o nodo anterior ao atual
        }
        anterior=nodo;// atualiza o elemento anterior        
    }
    
    fclose(file);
}

/**
 * @brief atualizaçao do ficheiro de texto quando há uma alteracao na lista 
 * 
 * @param Gestores 
 */
void atualizarFicheiro(struct gestor** Gestores){

    FILE* file;
    file=fopen("dados Gestores.txt","w");// a, acrescenta no fim do ficheiro

    char *token;
    char linha[20];

    // escrever no ficheiro

    struct gestor*nodo=*Gestores; // inicio da lista

    while(!feof(file) && nodo!=NULL){
        fprintf(file,"%s;%d;\n",nodo->nomeGestor,nodo->passGestor);
        nodo=nodo->seguinte;
    }

    fclose(file);
}


/**
 * @brief Criacao de um novo gestor
 *        Apenas um gestor pode criar outro gestor
 * 
 * @param Gestores 
 */

void criarGestor(struct gestor** Gestores){

   
    struct gestor* nodo = malloc(sizeof(struct gestor));
    //struct gestor*novo=*Gestores; // inicio da lista

    char nomeTemp[50]; // nome do utilizador a criar
    int passTemp;  // password do utilizador a criar

    printf("Qual é o nome do novo gestor: ");
    getchar();
    gets(nomeTemp);
    printf("Indique a sua password: ");
    scanf("%d",&passTemp);

    // acrescentar a frente
    strcpy(nodo->nomeGestor,nomeTemp);
    nodo->passGestor = passTemp;

    // coloca nodo seguinte como referencia
    nodo->seguinte = *Gestores;
    
    // move nodo inicial para o acabado de incluir
    *Gestores = nodo;

    atualizarFicheiro(Gestores);
}


/**
 * @brief Remocao de um gestor
 * 
 * @param Gestores 
 */
void removerGestor(struct gestor** Gestores){

    char nomeRemover[50]; // nome a remover

    printf("\nQual é o gestor que pretende remover? ");
    getchar();
    gets(nomeRemover);

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

/**
 * @brief alteracao de um gestor
 *        Qualquer gestor pode alterar a informacao de um outro gestor
 * 
 * @param Gestores 
 */
void alterarGestor(struct gestor** Gestores){

    struct gestor*nodo=*Gestores;

    int operacao; 
    char novoNome[50];
    char nomeRemover[50];
    int novaPass;

    printf("O que pretende fazer:\n1->alterar nome:\n2->alterar password:");
    scanf("%d",&operacao);

    switch (operacao){ // nao é boa pratica

        // Alterar nome do gestor
        case 1:

            printf("Qual é o nome do gestor que prentede alterar:");
            getchar();
            gets(nomeRemover);
            
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
            getchar();
            gets(nomeRemover);
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
    

/**
 * @brief remocao de um cliente da lista
 * 
 * @param Clientes 
 */
void removerCliente(struct cliente** Clientes){

    char clienteRemover[50];

    printf("\nCliente a remover:");
    getchar();
    gets(clienteRemover);
    

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
    atualizarFicheiroCliente(Clientes);
} 
    

/**
* @brief funcao que permite aos gestores obter a informacao sobre os clientes
* 
* @param Clientes 
*/
void infoClientes(struct cliente* Clientes){

    //struct clientes* nodo=Clientes;
    int escolha;
    char clientePesquisar[70];

    printf("1->Escolher apenas 1 Cliente:\n2->Obter a lista de todos os Clientes:");
    scanf("%d",&escolha);

    switch(escolha){
        case 1:
            printf("Qual é o Cliente que pretende pesquisar: ");
            getchar();
            gets(clientePesquisar);

            while(Clientes!=NULL){
                if(strcmp(clientePesquisar,Clientes->nomeCliente)==0){
                    printf("Nome:%s\nPassWord:%d\nSaldo:%.2f\nNif:%d\nMorada:%s\n",Clientes->nomeCliente,Clientes->passCliente,Clientes->saldo,Clientes->nif,Clientes->morada);
                }
                Clientes=Clientes->seguinte;
            }
        break;

        case 2:
            while(Clientes!=NULL){
                printf("%s;%d;%.2f;%d,%s\n",Clientes->nomeCliente,Clientes->passCliente,Clientes->saldo,Clientes->nif,Clientes->morada);
                Clientes=Clientes->seguinte;
            }
        break;
    }  
}

/**
 * @brief funcao que permite ao gestor acrescentar um meio de mobilidade
 * 
 * @param Meios 
 */

void acrescentarMeio(struct meios** Meios){

    struct meios* nodo=malloc(sizeof(struct meios));

    //variaveis auxilizares
    int autonomiaNova;
    int bateria=100;
    float precoNovo;
    char localizacaoNova[70],meioNovo[70];

    //assumindo que ao acrescentar um meio de mobilizacao a sua bateria estara nos 100%
    printf("Introduza as seguintes Informacoes:\n1->Nome do meio:");
    getchar();
    gets(meioNovo);
    printf("2->Preco:");
    scanf("%f",&precoNovo);
    printf("3->autonomia:");
    scanf("%d",&autonomiaNova);
    printf("4->Localizacao do meio:");
    getchar();
    gets(localizacaoNova);
    
    system("cls");

    //atribuicao das variaveis na lista ligada
    // acrescentar a frente

    strcpy(nodo->meios,meioNovo);
    nodo->bateria=bateria;
    nodo->preco=precoNovo;
    nodo->autonomia=autonomiaNova;
    strcpy(nodo->localizacao,localizacaoNova);

    // colocar o nodo seguinte como ref
    nodo->seguinte=(*Meios);

    // move o nodo inicial para o acabado de acrescentar
    (*Meios)=nodo;


    ordemDecrescente(Meios); // Para voltar a ordenar a lista ligada por ordem decrescente de autonomia
    atualizarFicheiroMeios(Meios);
}


/**
 * @brief Percorre a lista ligada, se encontrar o meio pretendido entao retorna a informacao da localizacao
 * 
 * @param Meios 
 */
void localizarMeio(struct meios* Meios){
    struct meios* nodo=Meios;

    char meio_a_Localizar[70];

    printf("Qual e o Meio que pretende Localizar:");
    scanf("%s",meio_a_Localizar);

    while(nodo!=NULL){
 
        if(strcmp(meio_a_Localizar,nodo->meios)==0){
            printf("A localizacao da %s e %s",nodo->meios,nodo->localizacao);
        }

       // printf("A localizacao da %s e %s\n",nodo->meios,nodo->localizacao);
        nodo=nodo->seguinte;
        //printf("ola\n");
    }
}

/**
 * @brief remover meio de mobilizacao
 * 
 * @param Meios 
 */

void removerMeio(struct meios** Meios){

    struct meios* nodo=*Meios;
    struct meios* temp;
    char meioRemover[70];


    printf("Qual e o meio que pretende remover: ");
    getchar();
    gets(meioRemover);

    
    if(strcmp((*Meios)->meios,meioRemover)==0){
        temp=*Meios;
        *Meios=(*Meios)->seguinte;
        free(temp);
    }else{
        while(nodo->seguinte!=NULL){

            if(strcmp(nodo->seguinte->meios,meioRemover)==0){

                temp=nodo->seguinte;
                nodo->seguinte=nodo->seguinte->seguinte;
                free(temp);
            }
            nodo=nodo->seguinte;
        }
    }

    ordemDecrescente(Meios);// Para ordenar a lista por ordem decrescente novamente
    atualizarFicheiroMeios(Meios);
}




/**
 * @brief alterar meio de mobilizacao
 * 
 * @param Meios 
 */
void alterarMeio(struct meios** Meios){

    struct meios* nodo=*Meios;
    int alteracao,novoPreco;
    char meioAlterar[70],novoMeio[70],localizacaoNova[70];


    printf("Pretende alterar:\n1->Nome do Meio:\n2->preco:\n3->Localizacao:");
    scanf("%d",&alteracao);

    switch (alteracao)
    {
        case 1:
        
            printf("Nome do meio a alterar:");
            getchar();
            gets(meioAlterar);
            printf("Novo nome:");
            getchar();
            gets(meioAlterar);    

            while(nodo!=NULL){
                if(strcmp(nodo->meios,meioAlterar)==0){
                    strcpy(nodo->meios,meioAlterar);
                }
                nodo=nodo->seguinte;
            }
        break;
        case 2:
            printf("Nome do meio a alterar:");
            getchar();
            gets(meioAlterar);
            printf("Novo Preco:");
            scanf("%d",&novoPreco);

            while(nodo!=NULL){
                if(strcmp(nodo->meios,meioAlterar)==0){
                nodo->preco=novoPreco;
                }
                nodo=nodo->seguinte;
            }
        break;

    case 3:
            printf("Nome do meio a alterar:");
            getchar();
            gets(meioAlterar);
            printf("Localizacao Nova:");
            getchar();
            gets(localizacaoNova);

            while(nodo!=NULL){
                if(strcmp(nodo->localizacao,localizacaoNova)==0){
                strcpy(nodo->localizacao,localizacaoNova);
                }
                nodo=nodo->seguinte;
            }
        break;
    }
    atualizarFicheiroMeios(Meios);
}