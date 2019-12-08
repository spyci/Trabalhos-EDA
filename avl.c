#include "avl.h"
arvAvl *criarArvAvl(){
    arvAvl *retArvAvl = (arvAvl*)malloc(sizeof(arvAvl));
    if(retArvAvl==NULL)
        return NULL;
    retArvAvl->raiz = NULL;
    retArvAvl->tam = 0;
    return retArvAvl;
}

noArv *Rot_esq(arvAvl *A, noArv* n){
    //printf("Rot_esq\n");
    noArv *y = n->dir;
    n->dir = y->esq;
    if(A->raiz == n){
        A->raiz = y;
        y->pai = NULL;
    }
    else{
        if (n==n->pai->esq)
            n->pai->esq=y;
        else
            n->pai->dir=y;
    }
    y->esq = n;
    n->pai = y;
    atualizar_altura(n);
    atualizar_altura(y);
    return y;
}

noArv *Rot_dir(arvAvl *A, noArv *n){
    noArv *y = n->esq;
    n->esq = y->dir;
    if(A->raiz == n){
        A->raiz = y;
        y->pai = NULL;
    }
    else{
        if(n == n->pai->esq){
//            printf("%lld pai de %lld recebe filho esq = %lld\n", n->pai->chave, n->chave, y->chave);
            n->pai->esq = y;
        }
        else{
//            printf("%lld pai de %lld recebe filho dir = %lld\n", n->pai->chave, n->chave, y->chave);
            n->pai->dir = y;
  //          //printf("agr e: %lld\n", n->pai->dir->chave);
        }
    }
    y->dir = n;
    n->pai = y;
    atualizar_altura(n);
    atualizar_altura(y);
    //printf("Rot_dir %lld %lld\n", n->chave, y->chave);
    return y;
}

noArv *Rot_dup_esq(arvAvl *A, noArv *n){
    //printf("Rot_dup_esq\n");
    noArv *y = n->dir;
    y = Rot_dir(A, y);
    n = Rot_esq(A, n);
}

noArv *Rot_dup_dir(arvAvl *A, noArv *n){
    //printf("Rot_dup_dir\n");
    noArv *y = n->esq;
    y = Rot_esq(A, y);
    n = Rot_dir(A, n);
}

noArv *Copia(noArv *n){
    noArv *retNoArv = createNoArv(n->chave, n->valor);
    if (retNoArv == NULL)
        return NULL;
    retNoArv->esq = n->esq;
    retNoArv->dir = n->dir;
    retNoArv->pai = n->pai;
    retNoArv->altura = n->altura;
    return retNoArv;
}

noArv *Transplante(arvAvl *A, noArv *n, noArv *m){
    if (n->pai==NULL)
        A->raiz = m;
    else if (n==n->pai->esq)
        n->pai->esq = m;
    else
        n->pai->dir = m;
    if (m!=NULL)
        m->pai = n->pai;
    return m;
}

llint balanco(noArv *n){
    if(n == NULL)
        return 0;
    else
        return no_alt(n->esq) - no_alt(n->dir);
}

noArv *Avl_minimo(noArv *n){
    noArv *aux = n;
    while (aux->esq!=NULL)
        aux = aux->esq;
    return aux;
}

void Balanceamento(arvAvl *A, noArv *n){
    if(balanco(n)==-2){
        noArv *m = n->dir;
        if(balanco(m)==1){
            //printf("rot dup esquerda balanco");
            Rot_dup_esq(A, n);
          }
        else{
            //printf("rot esquerda balanco");
            Rot_esq(A, n);
          }
    }
    else if (balanco(n)==2){
        noArv *m= n->esq;
        if(balanco(m)==-1){
            //printf("rot dup direita balanco");
            Rot_dup_dir(A, n);
          }
        else{
            //printf("rot direita balanco");
            Rot_dir(A, n);
          }
    }
}

noArv *Inserir_AVL(arvAvl *A, noArv *n, noArv *m){
    if (A->raiz == NULL){
        A->raiz = m;
        m->pai = NULL;
        return m;
    }
    else{
      if (m->chave < n->chave){
          if (n->esq == NULL){
              n->esq = m;
              m->pai = n;
            }
          else
            n->esq = Inserir_AVL(A, n->esq, m);
          }
          if (m->chave > n->chave){
            if (n->dir == NULL){
              n->dir = m;
              m->pai = n;
            }
            else
              n->dir = Inserir_AVL(A, n->dir, m);
          }
    atualizar_altura(n);
    if(balanco(n)==2||balanco(n)==-2){
        Balanceamento(A,n);
    }
    return n;
  }
}

noArv *Remover_AVL(arvAvl *A, noArv *n, llint m){
    if (n == NULL)
        return NULL;
    if (m < n->chave)
        n->esq = Remover_AVL(A, n->esq, m);
    else if (m > n->chave)
            n->dir = Remover_AVL(A, n->dir, m);
    else{
          if (n->esq == NULL){
            noArv *aux = Transplante(A, n, n->dir);
            free(n);
            n = aux;
          }
          else if (n->dir == NULL){
              Transplante(A, n, n->esq);
              noArv *aux = Transplante(A, n, n->dir);
              free(n);
              n = aux;
          }
          else{
              noArv *y = Avl_minimo(n->dir);
              noArv *z = Copia(y);
              Transplante(A, n, z);
              z->dir = n->dir;
              z->esq = n->esq;
              n->dir->pai = z;
              n->esq->pai = z;
              free(n);
              n = z;
              Remover_AVL(A, z->dir, y->chave);
            }
    }
    if (n == NULL)
        return NULL;
    atualizar_altura(n);
    if (balanco(n)==2||balanco(n)==-2){
        Balanceamento(A,n);
    }
    return n;
}

noArv *Procurar_AVL(noArv *n, llint chave){
    if(n == NULL || chave == n->chave)
        return n;
    if(chave < n->chave)
        return Procurar_AVL(n->esq, chave);
    if(chave > n->chave)
        return Procurar_AVL(n->dir, chave);
}

llint Altura_AVL(arvAvl *A){
  if(A->raiz)
    return A->raiz->altura;
  return 0;
}

void InOrder(noArv *node){
    if (node == NULL)
        return;
    InOrder(node->esq);
    printf("%lld %lld %lld\n", node->chave, node->opr, node->valor);
    InOrder(node->dir);
}

void InOrder_rev(noArv *node){
    if (node == NULL)
      return;
    InOrder_rev(node->dir);
    printf("%lld %lld %lld\n", node->chave, node->opr, node->valor);
    InOrder_rev(node->esq);
}
void InOrder_debug(noArv *node){
  if (node == NULL)
      return;
  printf("no:%lld ponteiro:%p esq: %p dir: %p pai: %p\n", node->chave, node, node->esq, node->dir, node->pai);
  InOrder_debug(node->esq);
  InOrder_debug(node->dir);

}
