#include "no.h"
#ifndef ARVAVL
#define ARVAVL
typedef struct ArvAvl{
    noArv *raiz;
    llint tam;
} arvAvl;
arvAvl *criarArvAvl();
noArv *Rot_esq(arvAvl *A, noArv* n);
noArv *Rot_dir(arvAvl *A, noArv* n);
noArv *Rot_dup_esq(arvAvl *A, noArv *n);
noArv *Rot_dup_dir(arvAvl *A, noArv *n);
void *Transplante(arvAvl *A, noArv *n, noArv *m);
noArv *Copia(noArv *n);
llint balanco(noArv *n);
noArv *Avl_minimo(noArv *n);
void Balacenamento(arvAvl *A, noArv *n);
noArv *Inserir_AVL(arvAvl *A, noArv *n, noArv *m);
noArv *Remover_AVL(arvAvl *A, noArv *n, llint m);
void InOrder(noArv *node);
void InOrder_rev(noArv *node);
noArv *Procurar_AVL(noArv *n, llint chave);
llint Altura_AVL(arvAvl *A);
#endif
