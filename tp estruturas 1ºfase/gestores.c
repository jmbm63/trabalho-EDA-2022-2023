#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "gestores.h"

void readFile(struct gestor* Gestores){

    FILE* file;
    file=fopen("dados Gestores.txt","r");

    struct gestor* nodo = malloc(sizeof(struct gestor)); // inicio da lista    

    char linha[20];
    char *token;

    if (file==NULL){
        printf("Erro na abertura do ficheiro");
        exit(1);
    }


    while(!feof(file)){
    
        
        // nome de utilizador
        fscanf(file,"%s",linha);
        token=strtok(linha,";\n");
        strcpy(nodo->nomeGestor, token);
        printf("utilizador: %s\n",nodo->nomeGestor);

        // password
        fscanf(file,"%s",linha);
        token=strtok(NULL,";\n");
        nodo->passGestor=atoi(token);
        printf("Password: %d",nodo->passGestor); 

        nodo = nodo->seguinte;

    }
    //printf("%s",nodo->nomeGestor); // da nulo porque estou no fim da lista
    
    fclose(file);
}

void atualizarFicheiro(struct gestor** Gestores,int passTemp,char nomeTemp[50]){

    FILE* file;
    file=fopen("dados Gestores.txt","a");// a, acrescenta no fim do ficheiro

    char *token;
    char linha[20];


    // escrever no ficheiro

    struct gestor*nodo=*Gestores; // inicio da lista

    if(file==EOF){
        fprintf(file,"\n%s;%d\n",nodo->nomeGestor,nodo->passGestor);
    }

    fprintf(file, "%s;%d\n", nomeTemp, passTemp);

    fclose(file);
}

void criarGestor(struct gestor** Gestores){

    struct gestor* nodo = malloc(sizeof(struct gestor));

    char nomeTemp[50]; // nome do utilizador a criar
    int passTemp;  // password do utilizador a criar

    printf("Qual é o nome do novo gestor: ");
    scanf("%s",nomeTemp);
    printf("Indique a sua password: ");
    scanf("%d",&passTemp);

    strcpy(nodo->nomeGestor,nomeTemp);
    nodo->passGestor = passTemp;
    printf("%d",nodo->passGestor);
    nodo->seguinte = *Gestores;
    
    *Gestores = nodo;

    atualizarFicheiro(&Gestores,passTemp,nomeTemp);

}



