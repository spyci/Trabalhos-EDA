#include "avl.h"

void insere_no(arvAvl *A, llint cdg_cliente, llint op, llint valor){
  noArv *aux = Procurar_AVL(A->raiz, cdg_cliente);
  if(aux!=NULL){
    switch(op){
      case(1):{
        aux->valor -= valor;
        aux->opr++;
        break;
      }
      case(0):{
        aux->valor += valor;
        aux->opr++;
        break;
      }
    }
  }
  else{
    aux = createNoArv(cdg_cliente, 0);
    switch(op){
      case(1):{
        aux->valor = aux->valor - valor;
        aux->opr = aux->opr+1;
        break;
      }
      case(0):{
        aux->valor = aux->valor + valor;
        aux->opr = aux->opr+1;
        break;
      }
    }
    Inserir_AVL(A, A->raiz, aux);
  }
  A->tam++;
}

void consulta_no(arvAvl *A, llint cdg_cliente){
  noArv *aux = Procurar_AVL(A->raiz, cdg_cliente);
  if(aux!=NULL)
    printf("existe no com chave: %lld\n", cdg_cliente);
  else
    printf("nao existe no com chave: %lld\n", cdg_cliente);
}

void remove_no(arvAvl *A, llint cdg_cliente){
  if(Procurar_AVL(A->raiz, cdg_cliente)!=NULL){
    Remover_AVL(A, A->raiz, cdg_cliente);
    A->tam--;
    printf("Achou o no %lld para remover\n", cdg_cliente);
    return;
  }
  printf("para remover nao achou a chave %lld\n", cdg_cliente);
}

void em_ordem(arvAvl *A, char c){
  noArv *node = A->raiz;
  switch(c){
    case('c'):
      InOrder(node);
      break;
    case('d'):
      InOrder_rev(node);
      break;
    }
}

void informa_altura(arvAvl *A){
  printf("%lld\n", Altura_AVL(A)+1);
}

void emNivel(noArv *node, llint nivel){
  if(node == NULL)
    return;
  if(nivel == 1)
    printf("%lld\n", node->chave);
  else if (nivel>1){
    emNivel(node->esq, nivel-1);
    emNivel(node->dir, nivel-1);
  }
}

void fim_entrada(arvAvl *A){
  printf("-+- Inicio relatorio -+-\n%lld\n", A->tam);
  int aux = A->tam;
  for(int i=0; i<aux; i++){
    printf("%lld %lld %lld\n", A->raiz->chave, A->raiz->opr, A->raiz->valor);
    Remover_AVL(A, A->raiz, A->raiz->chave);
  }
}



int main(){
  char c = 'a';
  arvAvl *A = criarArvAvl();
  while(c!= 'f'){
    scanf(" %c", &c);
    switch(c){
      case('i'):{
        llint cdg_cliente, op, valor;
        scanf(" %lld %lld %lld", &cdg_cliente, &op, &valor);
        insere_no(A, cdg_cliente, op, valor);
        break;
      }
      case('r'):{
        llint cdg_cliente;
        scanf(" %lld", &cdg_cliente);
        remove_no(A, cdg_cliente);
        break;
      }
      case('c'):{
        llint cdg_cliente;
        scanf(" %lld\n", &cdg_cliente);
        consulta_no(A, cdg_cliente);
        break;
      }
      case('p'):{
        char s;
        scanf(" %c\n", &s);
        em_ordem(A, s);
        break;
      }
      case('n'):{
        llint n;
        scanf(" %lld", &n);
        emNivel(A->raiz, n);
        break;
      }
      case('h'):{
        informa_altura(A);
        break;
      }
    }
  }
  fim_entrada(A);
}
