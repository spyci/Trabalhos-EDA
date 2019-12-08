#include "no.h"
llint max(llint A, llint B){
    return (A>B)? A:B;
}

llint no_alt(noArv *n){
    if(n == NULL){
        return 0;
    }
    else{
        return n->altura;
    }
}

void atualizar_altura(noArv *n){
    if(n == NULL)
        return;
    n->altura = max(no_alt(n->esq), no_alt(n->dir))+1;
}

noArv *createNoArv(llint chave, llint valor){
    noArv *retNoArv = (noArv*)malloc(sizeof(noArv));
    if(retNoArv==NULL) return NULL;
    retNoArv->pai = NULL;
    retNoArv->esq = NULL;
    retNoArv->dir = NULL;
    retNoArv->chave = chave;
    retNoArv->valor = valor;
    retNoArv->altura = 1;
    retNoArv->opr = 0;
    return retNoArv;
}

void deleteNoArv(noArv *node){
    free(node);
}
