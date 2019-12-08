#include <stdlib.h>
#include <stdio.h>
#ifndef NOARV
#define NOARV
typedef long long llint;
typedef struct noArv{
    struct noArv *pai;
    struct noArv *esq;
    struct noArv *dir;
    llint valor;
    llint chave;
    llint altura;
    llint opr;
} noArv;
llint max(llint A, llint B);
llint no_alt(noArv *n);
noArv *createNoArv(llint chave, llint valor);
void atualizar_altura(noArv *n);
void deleteNoArv(noArv *node);
#endif
