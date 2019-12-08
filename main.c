#include "avl.h"
int main(){
  arvAvl *A = criarArvAvl();
  noArv *n1 = createNoArv(11, 0);
  noArv *n2 = createNoArv(2, 0);
  noArv *n3 = createNoArv(10, 0);
  noArv *n4 = createNoArv(3, 0);
  noArv *n5 = createNoArv(9, 0);
  noArv *n6 = createNoArv(1, 0);

  Inserir_AVL(A, A->raiz, n1);


  InOrder_debug(A->raiz);
  printf("\n");

  Inserir_AVL(A, A->raiz, n2);

  InOrder_debug(A->raiz);
  printf("\n");

  Inserir_AVL(A, A->raiz, n3);

  InOrder_debug(A->raiz);
  printf("\n");

  Inserir_AVL(A, A->raiz, n4);

  InOrder_debug(A->raiz);
  printf("\n");

  Inserir_AVL(A, A->raiz, n6);

  InOrder_debug(A->raiz);
  printf("\n");

  Remover_AVL(A, A->raiz, 2);

  InOrder_debug(A->raiz);
  printf("\n");

  Inserir_AVL(A, A->raiz, n5);

  InOrder_debug(A->raiz);

}
