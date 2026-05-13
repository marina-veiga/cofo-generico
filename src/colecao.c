#define _COFO_C
#include "colecao.h"
#include <stdio.h> 
#include <stdlib.h> 
#define TRUE 1
#define FALSE 0 

gCofo *gCofoCreate(int max_itens){
    gCofo *cofo;                                                              
    if(max_itens > 0){                                                           //verifica se o número máximo de itens que o cofo guarda é maior que zero
        cofo = (gCofo*) malloc (sizeof(gCofo) * 1);                              //aloca memória para a estrutura do cofo
        if (cofo != NULL){                                                       //testa se o alocamento do cofo deu certo
            cofo ->item = (void **) malloc( sizeof(void*) * max_itens);          //alocando o vetor de itens
            if(cofo -> item != NULL){                                            //testa se o alocamento do vetor deu certo
                cofo -> numItens = 0;
                cofo -> maxItens = max_itens;
                cofo->cur = -1;                                                  //cur começa em -1 pois ainda não há elementos no cofo
                return cofo; 
            }
            free(cofo);                                                          //caso a alocação do vetor dê erro, liberamos o cofo.
        }
    }
    return NULL;
}

int gCofoInsert(gCofo *c, void *item){
    if(c != NULL){                                                               //verifica se o cofo existe
        if(c->numItens < c->maxItens){                                           //verifica se o cofo não está cheio
            c->item[c->numItens] = item;                                         //a quantidade de elementos indica a próxima posição do vetor para colocar o novo item
            c->numItens++;                                                       //atualiza a quantidade de elementos do cofo
            return TRUE;                                                         
        }
    }
    return FALSE;                                                               
}

int gCofoDestroy(gCofo *c){
    if(c!= NULL){                                                                
        if(c->numItens == 0){                                                    //condição para destruir o cofo: caso não possua nenhum elemento dentro do cofo
            free(c->item);                                                       //libera a memória do vetor de itens                           
            free(c);                                                             //libera a memória da estrutura cofo
            return TRUE;                                                         
        }
    }
    return FALSE;                                                                
}

void *gCofoRemove(gCofo *c, void *key, int (*cmp)(void* a, void* b)){
    if(c!=NULL){                                                                 
        if(c->numItens > 0){                                                     //checa se há elementos no cofo para remover
            int i= 0; int alvo= cmp(key,c->item[i]);                             
            while( i< c->numItens -1  && alvo != TRUE){                           //enquanto o índice não ultrapassar o último item E o alvo ainda não foi encontrado
                i++;       
                alvo = cmp(key, c->item[i]);                                     //chama a função que compara para o próximo elemento do vetor de itens
            }

            if(alvo == TRUE){                                                   
                void* elemento = c->item[i];                                     //se encontrou o alvo guarda ele em uma variável genérica
                for(int j = i; j < c->numItens -1; j++){                         //perorrer da posição do elemento encontrado até o final do vetor item
                    c->item[j] = c->item[j+1];                                   //a partir da posição do valor encontrado, puxar todos os valores sucessores dele pra esquerda
                }

                c->numItens --; 
                c->cur = -1;                                                 
                return elemento;                                                 //retorna o ponteiro para o elemento que foi removido
            }
        }
    }

    return NULL;                                                                 //caso o cofo não exista ou o alvo não for encontrado, retorna nulo
}

void *gCofQuery(gCofo *c, void *key, int (*cmp)(void* a, void *b)){             
    if(c!= NULL){                                                                
        if(c->numItens > 0){                                                     //checa se há elementos para buscar 
            int i= 0; int alvo = cmp(key, c->item[i]);
            while(i < c->numItens -1 && alvo != TRUE){                            //loop de condição: enquanto o índice não ultrapassar o último item E o alvo ainda não foi encontrado
                i++;
                alvo = cmp(key, c->item[i]);                                     //chama a função que compara para o próximo elemento do vetor de itens
            }

            if(alvo == TRUE){
                return c->item[i];                                               //se encontrou o alvo retorna um ponteiro para o elemento                                           
            }else{
                return NULL;
            }
        }
    }

    return NULL;                                                                 //caso o cofo não exista ou o alvo não for encontrado, retorna nulo
}

void *gCofGetFirst(gCofo *c){
    if(c !=NULL){                                                               
        if(c->numItens > 0){                                                    //checa se há elementos dentro do cofo
            c->cur=0;                                                           //atualiza o valor do marcador cur para 0
            return c->item[c->cur];                                             //retorna o primeiro elemento do cofo
        }
    }
    return NULL;                                                                //se o cofo não existir ou estiver vazio, retorna null
}

void *gCofGetNext(gCofo *c){
    if(c!= NULL){                                                               
        if(c->cur +1 < c->numItens){                                            //checa se o próximo elemento do vetor ainda está no limite de itens do cofo
            c->cur++;                                                           //avança o marcador cur para a próxima posição
            return c->item[ c->cur];                                            //retorna o elemento da nova posição do marcador
        }
    }
    return NULL;                                                                //se o cofo não existir ou não houver um próximo elemento, retorna null
}
int gCofoEsvazia(gCofo *c){
    if(c!=NULL){
        for(int i = 0; i < c->numItens;i++){
            free(c->item[i]);
        }
        c->numItens = 0;
        c->cur=-1;
        return TRUE;
    }

    return FALSE;

}
