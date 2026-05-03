#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#include "cofo.h"

//estrutura de um album de música
typedef struct musicAlbum{
    char nome[50];
    int ano;
    float fat;
}Album;


//Função que compara duas string e retorna true caso seja a mesma e false caso não sejam iguais
int cmpNome(void * nome1, void* nome2){                                   
    char *nome = (char*)nome1;                                                          //cast de um ponteiro genérico para um ponteiro do tipo char
    Album *nomeAlbum = (Album*) nome2;                                                  //cast de um ponteiro genérico para um ponteiro do tipo Album
    
    if(strcmp(nome,nomeAlbum->nome) == FALSE){                                          //verifica se os nomes são iguais         
        return TRUE;                                                                    
    }
    else{
        return FALSE;
    }
}

//Função que lista os itens que estão no cofo
void listElem(gCofo *c){
    if( c != NULL){
        void *resultado = gCofGetFirst(c);                                            //variável do tipo (void *) para guardar o primeiro elemento do cofo
        Album *lista = (Album*) resultado;                                            //cast dessa variável para ela ser do tipo Album 
        while(lista != NULL){                                                         //percorre todos os itens do cofo do primeiro até o último
            printf("Nome do Album: %s", lista->nome);                             
            printf("Ano do Album: %d\n", lista->ano);
            printf("Faturamento do Album: %.3f\n\n", lista->fat);

           lista = gCofGetNext(c);                                                    //pega o próximo item da lista
        }
    }
}

int main(){
    gCofo* cofoAlbum = NULL;                                                           
    int opcao = -1; 

    while(opcao!= 0){
        printf("\n----MENU----");                                                     
        printf("\n1- Criar cofo");
        printf("\n2- Inserir no cofo");
        printf("\n3- Destruir o cofo"); 
        printf("\n4- Remover do cofo"); 
        printf("\n5- Buscar no cofo"); 
        printf("\n6- Pegar o primeiro do cofo");
        printf("\n7- Pegar o proximo do cofo"); 
        printf("\n8- Listar elementos do cofo"); 
        printf("\n0- Sair"); 

        printf("\nqual opcao do menu voce deseja: ");
        scanf("%d",&opcao);


        switch(opcao){
            case 1: 
                if(cofoAlbum == NULL){                                                 
                    int max_itens; 
                    printf("Qual o numero maximo que o cofo deve guardar: ");
                    scanf("%d",&max_itens);
                    cofoAlbum = gCofoCreate(max_itens);                                //se não existir nenhum cofo, cria um.
                    printf("\nCofo criado com sucesso!\n");
                } 
            break;

            case 2:
                if(cofoAlbum != NULL){                          
                    Album* album;                     
                    album = (Album*)malloc(sizeof(Album));
                    printf("Nome do album: ");
                    getchar();
                    fgets(album->nome,50,stdin);
                    printf("\nAno de Lancamento: ");
                    scanf("%d",&album->ano);
                    printf("\nFaturamento do album: ");
                    scanf("%f",&album->fat);

                    int flag= gCofoInsert(cofoAlbum,(void*)album);                   //variável que recebe se o album foi inserido no cofo(true) ou se deu erro (false)
                    if(flag == TRUE){
                        printf("\nAlbum inserido com sucesso!\n");
                    }else{
                        free(album);                                                 //se o cofo estiver cheio, libera a memória do álbum alocado
                        printf("\nErro ao inserir o album!\n");
                    }
                }
            break;

            case 3:
                if(cofoAlbum != NULL){
                    int flag = gCofoDestroy(cofoAlbum);                            //variável que recebe se o cofo foi destruido (true) ou se deu erro (false)
                    if(flag == TRUE){
                        printf("\nO cofo foi destruido com sucesso!\n");
                        cofoAlbum = NULL;
                    }else{
                        printf("\nO cofo precisa esta vazio para ser destruido\n");
                    }
                }else{
                    printf("\nNao existe cofo!\n");
                }
            break;

            case 4:
               if(cofoAlbum != NULL){
                    char chave[50];
                    printf("informe a chave: ");
                    getchar();
                    fgets(chave,50,stdin);
                    void *removido = gCofoRemove(cofoAlbum,(void*)chave,cmpNome);                   //remove do cofo e guarda o ponteiro para poder liberar a memória
                    
                    if(removido != NULL){
                        free(removido);                                                            //Libera a memória do álbum removido                                                            
                        printf("\nAlbum removido com sucesso!\n");

                    }else{
                        printf("\nAlbum não encontrado!\n");
                    }
                    
               } 
            break;

            case 5: 
               if(cofoAlbum != NULL){
                    char chave[50];
                    printf("informe a chave: ");
                    getchar();
                    fgets(chave,50,stdin); 

                    void *busca = gCofQuery(cofoAlbum,(void *)chave,cmpNome);      //variável do tipo (void *) que recebe o resultado da busca de item

                    Album *albumAchado = (Album*) busca;                           //o resultado da busca agora passa ser do tipo (Album *)
                    if(albumAchado != NULL){                                       //se achou o elemento, informa os dados do álbum
                        printf("--ALBUM ENCONTRADO--\n");
                        printf("Nome: %s",albumAchado->nome);
                        printf("Ano: %d\n",albumAchado->ano);
                        printf("Faturamento: %.3f\n",albumAchado->fat);

                    } else{
                        printf("\nPoxa... Album nao encontrado!\n");
                    }
               }
            break;

            case 6:
               if(cofoAlbum != NULL){
                    void *resultado = gCofGetFirst(cofoAlbum);                   
                    Album *firstAlbum = (Album*) resultado;
                    if(firstAlbum != NULL){                                        //se pegou o primeiro elemento do cofo, informa os dados desse álbum
                    printf("\n---PRIMEIRO ALBUM DO COFO---");
                    printf("\nnome do album: %s", firstAlbum->nome);
                    printf("ano de lancamento: %d", firstAlbum->ano);
                    printf("\nfaturamento do album: %.3f\n", firstAlbum->fat);
                    } else{
                        printf("\nO cofo esta vazio! Insira um album para pegar o primeiro!\n");
                    }
               }
            break;

            case 7:
               if(cofoAlbum != NULL){
                    void *resultado = gCofGetNext(cofoAlbum);
                    Album *nextAlbum = (Album*) resultado;
                    if(nextAlbum != NULL){                                        //se pegou o próximo elemento do cofo, informa os dados desse álbum
                    printf("\n---PROXIMO ALBUM DO COFO---\n");
                    printf("nome do album: %s",nextAlbum->nome);   
                    printf("ano de lancamento: %d\n",nextAlbum->ano);
                    printf("faturamento do album: %.3f\n",nextAlbum->fat);
                    } else{
                        printf("\nNao existe proximo album!\n");
                    }    
               }      
            break;

            case 8:
               if(cofoAlbum != NULL){                                           
                printf("\n---LISTA DOS ALBUMS---\n");
                listElem(cofoAlbum);                                             //listar todos os elementos do cofo
               }
            break;

            case 0:
               printf("\nsaindo... ate a proxima!");                            //sair do programa
            break;

        }
    }

    return 0;
}