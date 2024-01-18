#ifndef TREE_AVL_H
#define TREE_AVL_H

typedef struct no {
    int valor;
    int fb;
    struct no *esq;
    struct no *dir;
} no;

typedef no* arvore;

arvore inserir (arvore raiz, int valor, int *cresceu);
arvore rotacao (arvore pivo);
arvore rotacao_simples_esquerda(arvore pivo);
arvore rotacao_simples_direita(arvore pivo);
arvore rotacao_dupla_esquerda(arvore pivo);
arvore rotacao_dupla_direita(arvore pivo);

void preorder(arvore raiz);
void inorder(arvore raiz);
void posorder(arvore raiz);
void reverso(arvore raiz);

int qtde_par(arvore raiz);
int antecessor(arvore raiz, int n);
int pai(arvore raiz, int n);
int soma_par(arvore raiz);
void dobro(arvore raiz);
int busca(arvore raiz, int valor);
void descendentes(arvore raiz, int valor);
int altura(arvore raiz);
arvore remover(arvore raiz, int valor, int *caiu);
int maior_elemento(arvore raiz);
int menor_elemento(arvore raiz);

int somatorio(arvore raiz);
void mesclar (arvore raiz1, arvore raiz2);
void ascendentes(arvore raiz, int valor);

#endif
