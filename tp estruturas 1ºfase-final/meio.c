#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "meio.h"

/**
 * @brief funcao referente a leitura e insercao dos meios na lista ligada
 * 
 * @param Meios 
 */
void lerFicheiro(struct meios** Meios){

    FILE* file;
    file=fopen("dados Meios.txt","r");

    struct meios* anterior=NULL;

    char linha[100];
    char *token;

    if(file==NULL){
        printf("Erro a abrir o ficheiro");
    }

    while(fgets(linha,sizeof(linha),file)!=NULL){

        struct meios *nodo = malloc(sizeof(struct meios));
        
        // meio
        token=strtok(linha,";");
        strcpy(nodo->meios, token);
        
        // bateria
        token=strtok(NULL,";");
        nodo->bateria=atoi(token);
        
        // preco
        token=strtok(NULL,";");
        nodo->preco = atof(token);
        
        // autonomia
        token=strtok(NULL,";");
        nodo->autonomia=atoi(token);
        
        // Localizacao
        token=strtok(NULL,";");
        strcpy(nodo->localizacao, token);
        
        // Estado
        token=strtok(NULL,";");
        strcpy(nodo->estado, token);
        
        nodo->seguinte=NULL;

        if(anterior==NULL){
            *Meios=nodo; // coloca o primeiro nodo 
        }else{
            anterior->seguinte=nodo;// liga o nodo anterior ao atual
        }
        anterior=nodo;// atualiza o elemento anterior
    }
    
    fclose(file);
}

/**
 * @brief Apos uma alteracao feita na lista ligada irá ser feita uma atulizacao do ficheiro de dados
 * 
 * @param Meios 
 */
void atualizarFicheiroMeios(struct meios** Meios){

    FILE* file;
    file=fopen("dados Meios.txt","w");

    char *token;
    char linha[20];

    // escrever no ficheiro

    struct meios* novo=*Meios; // inicio da lista

    while(novo!=NULL){
        fprintf(file,"%s;%d;%.2f;%d;%s;%s;\n",novo->meios,novo->bateria,novo->preco,novo->autonomia,novo->localizacao,novo->estado);
        novo=novo->seguinte;
    }
    fclose(file);
}

/**
 * @brief Ordenacao da lista ligada por ordem descrescente de autonomia
 * A lista é percorrida e compara os valores de autonomia do nodo atual com o seguinte, 
 * caso seja maior entao é feia a troca de nodos
 * 
 * @param Meios 
 */
void ordemDecrescente(struct meios **Meios) {

    struct meios* nodo = *Meios;
    struct meios*temp;

    int i,j;

    // bubble sort
    /**
     * @brief https://pt.stackoverflow.com/questions/330286/ordenar-lista-ligada-em-c
     * 
    */
    while(nodo!=NULL){ // percorre a lista de inicio a fim

        temp=nodo->seguinte;

        while(temp!=NULL){ // precorre a lista do nodo seguinte

            if(nodo->autonomia<temp->autonomia){ // se a autonomia for maior entao trocamos o conteudo do nodo

                // meios de mobilidade
                char f[100];
                strcpy(f,nodo->meios);
                strcpy(nodo->meios,temp->meios);
                strcpy(temp->meios,f);

                // bateria
                int b=nodo->bateria;
                nodo->bateria=temp->bateria;
                temp->bateria=b;

                // Preco do meio
                float pf;
                pf=nodo->preco;
                nodo->preco=temp->preco;
                temp->preco=pf;
                
                // Autonomia do meio
                int auto2;
                auto2=nodo->autonomia;
                nodo->autonomia=temp->autonomia;
                temp->autonomia=auto2;

                // Localizacao do meio
                char l[100];
                strcpy(l,nodo->localizacao);
                strcpy(nodo->localizacao,temp->localizacao);
                strcpy(temp->localizacao,l);

                // Estado do meio
                char est[100];
                strcpy(est,nodo->estado);
                strcpy(nodo->estado,nodo->estado);
                strcpy(nodo->estado,est);

            }
            temp=temp->seguinte;
        }
        nodo=nodo->seguinte;
    }
}