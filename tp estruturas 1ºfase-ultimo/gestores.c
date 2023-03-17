#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinUser.h>
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
    file = fopen("dados Gestores.txt", "rb");

    struct gestor *anterior=NULL;

    char linha[100];
    char *token;

    if (file == NULL) {
        printf("Erro na abertura do ficheiro");
        exit(1);
    }
    while (fgets(linha,sizeof(linha),file)!=NULL){

        struct gestor *nodo = malloc(sizeof(struct gestor)); // inicio da lista

        // Nome
        token=strtok(linha,";");
        strcpy(nodo->nomeGestor, token);
        
        // Password
        token=strtok(NULL,";");
        nodo->passGestor=atoi(token);
        
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
    file=fopen("dados Gestores.txt","wb");// w, para escrever no ficheiro

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
 *        Apenas um gestor pode remover um gestor
 * 
 * @param Gestores 
 */
void removerGestor(struct gestor** Gestores){

    char nomeRemover[50]; // nome a remover

    printf("\nQual e o gestor que pretende remover? ");
    getchar();
    gets(nomeRemover);

    struct gestor* Temp;

    if(strcmp((*Gestores)->nomeGestor,nomeRemover)==0){ // se estiver no primeiro nodo
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
    system("cls");

    switch (operacao){ // nao e boa pratica

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
        break;

        // alterar a Password
        case 2:

            printf("Qual e a password do gestor que prentede alterar:");
            getchar();
            gets(nomeRemover);
            printf("Qual e a nova pass:");
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
    system("cls");

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
 * Quando um meio de mobilidade é criado, é assumido que o mesmo tenha 100% de bataria
 * 
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
    char est[10]={"livre"};
       
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
    strcpy(nodo->estado,est);

    // colocar o nodo seguinte como ref
    nodo->seguinte=*Meios;

    // move o nodo inicial para o acabado de acrescentar
    *Meios=nodo;
            
    ordemDecrescente(Meios); // Para voltar a ordenar a lista ligada por ordem decrescente de autonomia
    atualizarFicheiroMeios(Meios);
}


/**
 * @brief Percorre a lista ligada, se encontrar o meio pretendido entao retorna a informacao da localizacao
 * é dada a opcao de ver a localizacao do mesmo no browser
 * 
 * @param Meios 
 */
void localizarMeio(struct meios* Meios){

    struct meios* nodo=Meios;

    char meio_a_Localizar[70];
    int abrirFicheiro;

    printf("Qual e o Meio que pretende Localizar:");
    scanf("%s",meio_a_Localizar);

    while(nodo!=NULL){
 
        if(strcmp(meio_a_Localizar,nodo->meios)==0){
            printf("A localizacao da/o %s e %s\n",nodo->meios,nodo->localizacao);
            break;
        }
        nodo=nodo->seguinte;
    }
    if(nodo==NULL){
        printf("O Meio nao existe!");
        return;
    }
    

    int meioBrowser=0;// variavel para o loop 
    while(meioBrowser!=1){

        // abre o browser com a localizacao do meio de mobilizacao
        printf("Pretende abrir no Browser a localizcao?\n1->Sim:\n2->Nao: ");
        scanf("%d",&abrirFicheiro);

        if(abrirFicheiro==1){
            char url[1000];
            meioBrowser=0;
            sprintf(url, "START https://what3words.com/%s", nodo->localizacao);
            system(url);
            break;
        }
        else if(abrirFicheiro==2){
            return;
        }else{
            printf("Numero invalido!\nEscolha novamente\n");
            meioBrowser=0;
        }
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

    switch (alteracao){
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