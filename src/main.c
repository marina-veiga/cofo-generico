#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#include "colecao.h"


//estrutura de um album de música
typedef struct musicAlbum{
    char nome[50];
    int ano;
    float fat;
}Album;


// Comparação por Nome (Chave é char*)
int cmpNome(void *key, void *item) {                                  
    char *nomeBusca = (char *)key;                                                          //cast de um ponteiro genérico para um ponteiro do tipo char
    Album *album = (Album *)item;                                                           //cast de um ponteiro genérico para um ponteiro do tipo Album
    
    if(strcmp(nomeBusca, album->nome) == FALSE){
        return TRUE;
    }
    return FALSE;
}

// Comparação por Ano (Chave é int*)
int cmpAno(void *key, void *item) {
    int *anoBusca = (int *)key;
    Album *album = (Album *)item;
    if(*anoBusca == album->ano){
        return TRUE;
    }
    return FALSE;
}

// Comparação por Faturamento (Chave é float*)
int cmpFat(void *key, void *item) {
    float *fatBusca = (float *)key;
    Album *album = (Album *)item;

    if(*fatBusca == album->fat){
        return TRUE;
    }
    return FALSE;
}

//Função que lista os itens que estão no cofo
void listElem(gCofo *c){
    if( c != NULL){
        void *resultado = gCofGetFirst(c);                                            //variável do tipo (void *) para guardar o primeiro elemento do cofo
        if(resultado == NULL){
            printf("\nColecaoo Vazia\n");
        }

        Album *lista = (Album*) resultado;                                            //cast dessa variável para ela ser do tipo Album 
        while(lista != NULL){                                                         //percorre todos os itens do cofo do primeiro até o último
            printf("Nome do Album: %s", lista->nome);                             
            printf("Ano do Album: %d\n", lista->ano);
            printf("Faturamento do Album: %.3f\n\n", lista->fat);

           lista =(Album*) gCofGetNext(c);                                                    //pega o próximo item da lista
        }
    }

}

int main(){
    gCofo* cofoAlbum = NULL;                                                           
    int opcao = -1; 

    while(opcao!= 0){
        printf("\n----MENU----");                                                     
        printf("\n1 - Criar");
        printf("\n2 - Inserir");
        printf("\n3 - Remover");
        printf("\n4 - Buscar");
        printf("\n5 - Listar");
        printf("\n6 - Esvaziar");
        printf("\n7 - Destruir");  
        printf("\n0 - Sair"); 

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
                    int opcaoRemover;
                    void *resultado = NULL;

                    printf("\nRemover por:\n 1-Nome \n 2-Ano\n 3-Faturamento\n");
                    printf("Opcao: ");
                    scanf("%d", &opcaoRemover);

                    if(opcaoRemover == 1){
                        char nome[50];
                        printf("Digite o nome: ");
                        getchar();
                        fgets(nome, 50, stdin);
                        resultado= gCofoRemove(cofoAlbum, (void*)nome, cmpNome);
                    }else if(opcaoRemover == 2){
                        int ano;
                        printf("Digite o ano: ");
                        scanf("%d", &ano);
                        resultado= gCofoRemove(cofoAlbum, (void*)&ano, cmpAno);
                    }else if(opcaoRemover == 3){
                        float fat;
                        printf("Digite o faturamento: ");
                        scanf("%f", &fat);
                        resultado= gCofoRemove(cofoAlbum, (void*)&fat, cmpFat);
                    }

                    if(resultado != NULL){
                        free(resultado);                                                            //Libera a memória do álbum removido                                                            
                        printf("\nAlbum removido com sucesso!\n");

                    }else{
                        printf("\nAlbum não encontrado!\n");
                    }
                    
               } 
            break;
            case 4: 
               if(cofoAlbum != NULL){
                    int opcaoBusca;
                    void *resultado = NULL;     

                    printf("Buscar por:\n 1-Nome \n 2-Ano\n 3-Faturamento\n");
                    printf("Opcao: ");
                    scanf("%d", &opcaoBusca);
                    
                    if(opcaoBusca==1){
                        char nome[50];
                        printf("Digite o nome: ");
                        getchar();
                        fgets(nome, 50, stdin);
                        resultado = gCofQuery(cofoAlbum, nome, cmpNome);
                    }else if(opcaoBusca == 2){
                        int ano;
                        printf("Digite o ano: ");
                        scanf("%d",&ano);
                        resultado = gCofQuery(cofoAlbum, &ano, cmpAno);

                    }else if(opcaoBusca == 3){
                        float fat;
                        printf("Digite o faturamento: ");
                        scanf("%f", &fat);
                        resultado = gCofQuery(cofoAlbum, &fat, cmpFat);

                    }

                    if(resultado != NULL){
                        Album *albumAchado = (Album*) resultado;                           //o resultado da busca agora passa ser do tipo (Album *)
                        if(albumAchado != NULL){                                           //se achou o elemento, informa os dados do álbum
                            printf("--ALBUM ENCONTRADO--\n");
                            printf("Nome: %s",albumAchado->nome);
                            printf("Ano: %d\n",albumAchado->ano);
                            printf("Faturamento: %.3f\n",albumAchado->fat);
                        }
                    } else{
                        printf("\nPoxa... Album nao encontrado!\n");
                    }

               }
            break;
            case 5:
                if(cofoAlbum != NULL){                                           
                    printf("\n---LISTA DOS ALBUMS---\n");
                    listElem(cofoAlbum);                                             //listar todos os elementos do cofo
               }
            break;

            case 6:
                if(cofoAlbum!= NULL){
                    int esvaziou= gCofoEsvazia(cofoAlbum);
                    if(esvaziou == TRUE){
                        printf("\nCofo esvaziado com sucesso!\n");
                    }else{
                        printf("\nErro ao esvaziar o cofo!\n");
                    }
                }else{
                    printf("\n\nErro: Voce precisa criar o cofo primeiro!\n");
                }
            break;

            case 7:
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

            case 0:
            if(cofoAlbum!=NULL){
                int destruiu = gCofoDestroy(cofoAlbum);
                if(destruiu == TRUE){
                    printf("\nCofo destruido. Saindo... ate a proxima!\n");                            //sair do programa
            
                }else{
                    printf("O cofo precisa esta vazio!");
                }
            
            } printf("\nsaindo... ate a proxima!");                          
            break;

        }
    }

    return 0;
}