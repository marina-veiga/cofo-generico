#ifndef _COFO_H
#define _COFO_H

#ifdef _COFO_C

//Estrutura do cofo genérico
typedef struct _gCofo_{
    int numItens;         //Número de itens que estão guardados no cofo
    int maxItens;         //Número máximo de itens que o cofo pode guardar
    int cur;              //Marcador que indica qual elemento do cofo está sendo acessado no momento
    void **item;          //Vetor que guarda os elementos do cofo
}gCofo;

//Funções de implementação do cofo genérico 


// Função que cria o cofo com o número máximo de itens informado. Retorna o cofo ou NULL se falhar.
gCofo *gCofoCreate(int max_itens);                                         

// Função que insere um elemento no cofo. Retorna true se sucesso, false se estiver cheio.
int gCofoInsert(gCofo *c, void *item);

// Função que destroi o cofo. Retorna true se sucesso, false se ainda houver elementos.
int gCofoDestroy(gCofo *c);

// Função que remove e retorna o elemento encontrado pela chave, ou NULL se não encontrar.
void *gCofoRemove(gCofo *c, void *key, int (*cmp)(void* a, void* b));

// Função que busca e retorna o elemento encontrado pela chave, ou NULL se não encontrar.
void *gCofQuery(gCofo *c, void *key, int (*cmp)(void* a, void *b));

// Função que retorna o primeiro elemento do cofo ou NULL se estiver vazio.
void *gCofGetFirst(gCofo *c);

// Função que retorna o próximo elemento do cofo ou NULL se chegou ao fim.
void *gCofGetNext(gCofo *c);

//Função que esvazia o cofo 
int gCofoEsvazia(gCofo *c);

#else

typedef struct _gCofo_ gCofo;
extern gCofo *gCofoCreate(int max_itens);
extern int gCofoInsert(gCofo *c, void *item);
extern int gCofoDestroy(gCofo *c);
extern void *gCofoRemove(gCofo *c, void *key, int (*cmp)(void* a, void* b));
extern void *gCofQuery(gCofo *c, void *key, int (*cmp)(void* a, void *b));
extern void *gCofGetFirst(gCofo *c);
extern void *gCofGetNext(gCofo *c);
extern int gCofoEsvazia(gCofo *c);

#endif
#endif

