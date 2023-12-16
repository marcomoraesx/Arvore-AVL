#include "tree_avl.h"
#include <stdlib.h>
#include <stdio.h>

arvore inserir (arvore raiz, int valor, int *cresceu){
    if(raiz == NULL) {
        arvore nova = (arvore) malloc(sizeof(struct no));
        nova->valor = valor;
        nova->esq = NULL;
        nova->dir = NULL;
        nova->fb = 0;
        *cresceu = 1;
        return nova;
    } else {
        if(valor > raiz->valor) {
            raiz->dir = inserir(raiz->dir, valor, cresceu);
            if (*cresceu) {
                //Atualização dos Fatores de Balanço após a árvore à direita crescer
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        *cresceu = 0;
                        return rotacao(raiz);
                        break;
                    case -1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                }
            }
        } else {
            raiz->esq = inserir(raiz->esq, valor, cresceu);
            if (*cresceu) {
            //Atualização dos Fatores de Balanço após a árvore à esquerda crescer
                switch (raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *cresceu = 1;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case -1:
                        *cresceu = 0;
                        return rotacao(raiz);
                        break;
                }
            }
        }
        return raiz;
    }
}

arvore rotacao (arvore pivo) {
    if (pivo->fb > 0) {
        //Rotações à Esquerda
        if (pivo->dir->fb >= 0) {
            //Rotação Simples à Esquerda
            if (pivo->dir->fb == 0) {
                pivo->fb = 1;
                pivo->dir->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
            }
            return rotacao_simples_esquerda(pivo);
        } else {
            //Rotação Dupla à Esquerda
            if (pivo->dir->esq->fb < 0) {
                pivo->fb = 0;
                pivo->dir->fb = 1;
                pivo->dir->esq->fb = 0;
            } else if (pivo->dir->esq->fb > 0){
                pivo->fb = -1;
                pivo->dir->fb = 0;
                pivo->dir->esq->fb = 0;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
                pivo->dir->esq->fb = 0;
            }
            return rotacao_dupla_esquerda(pivo);
        }
    } else {
        //Rotações à Direita
        if (pivo->esq->fb <= 0) {
            //Rotação Simples à Direita
            if (pivo->esq->fb == 0) {
                pivo->fb = -1;
                pivo->esq->fb = 1;
            } else {
                pivo->fb = 0;
                pivo->esq->fb = 0;
            }
            return rotacao_simples_direita(pivo);
        } else {
            //Rotação Dupla à Direita
            if (pivo->esq->dir->fb < 0) {
                pivo->fb = 1;
                pivo->esq->fb = 0;
                pivo->esq->dir->fb = 0;
            } else if (pivo->esq->dir->fb > 0) {
                pivo->fb = 0;
                pivo->esq->fb = -1;
                pivo->esq->dir->fb = 0;
            } else {
                pivo->fb = 0;
                pivo->esq->fb = 0;
                pivo->esq->dir->fb = 0;
            }
            return rotacao_dupla_direita(pivo);
        }
    }
}

arvore rotacao_simples_esquerda(arvore pivo) {
    arvore u, t1, t2, t3;
    u = pivo->dir;
    t1 = pivo->esq;
    t2 = u->esq;
    t3 = u->dir;
    u->esq = pivo;
    pivo->dir = t2;
    return u;
}

arvore rotacao_simples_direita(arvore pivo) {
    arvore u, t1, t2, t3;
    u = pivo->esq;
    t1 = pivo->dir;
    t2 = u->esq;
    t3 = u->dir;
    u->dir = pivo;
    pivo->esq = t3;
    return u;
}

arvore rotacao_dupla_direita(arvore pivo) {
    pivo->esq = rotacao_simples_esquerda(pivo->esq);
    return rotacao_simples_direita(pivo);
}

arvore rotacao_dupla_esquerda(arvore pivo) {
    pivo->dir = rotacao_simples_direita(pivo->dir);
    return rotacao_simples_esquerda(pivo);
}

void preorder(arvore raiz){
    if(raiz != NULL) {
        printf("[%d - %d]", raiz->valor, raiz->fb);
        preorder(raiz->esq);
        preorder(raiz->dir);
    }
}

void inorder(arvore raiz){
    if(raiz != NULL) {
        inorder(raiz->esq);
        printf("[%d]", raiz->valor);
        inorder(raiz->dir);
    }
}

void posorder(arvore raiz) {
    if(raiz != NULL) {
        posorder(raiz->esq);
        posorder(raiz->dir);
        printf("[%d]", raiz->valor);
    }
}

void reverso(arvore raiz){
    if(raiz != NULL) {
        reverso(raiz->dir);
        printf("[%d]", raiz->valor);
        reverso(raiz->esq);
    }
}

int qtde_par(arvore raiz){
    int qtde = 0;
    if(raiz != NULL) {
        if (raiz->valor%2 == 0) {
            qtde += 1;
        }
        qtde += qtde_par(raiz->esq) + qtde_par(raiz->dir);
    }
    return qtde;
}

/*int antecessor(arvore raiz, int n){
    int ant = -1;
    if (raiz != NULL) {
        if (n == raiz->valor){
            ant = antecessor(raiz->esq, n);
        } else if (n < raiz->valor) {
            ant = antecessor(raiz->esq, n);
        } else {
            ant = raiz->valor;
            int result = antecessor(raiz->dir, n);
            if (result != -1) {
                ant = result;
            }
        }
    }
    return ant;
}*/

int maior_valor(arvore raiz) {
    int maior = raiz->valor ? raiz->valor : NULL;
    if (raiz != NULL && raiz->dir != NULL) {
        maior = maior_valor(raiz->dir);
    }
    return maior;
}

int antecessor(arvore raiz, int valor) {
    arvore candidato = NULL;
    arvore raiz_atual = raiz;
    while (raiz_atual != NULL) {
        if (valor < raiz_atual->valor) {
            raiz_atual = raiz_atual->esq;
        } else if (valor > raiz_atual->valor) {
            candidato = raiz_atual;
            raiz_atual = raiz_atual->dir;
        } else {
            if (raiz_atual->esq != NULL) {
                return maior_valor(raiz_atual->esq);
            } else {
                if (candidato != NULL) {
                    return candidato->valor;
                }
                break;
            }
        }
    }
    return -1;
}

int pai(arvore raiz, int n){
    int father = -1;
    if (raiz != NULL) {
        if (n < raiz->valor) {
            if (raiz->esq != NULL && raiz->esq->valor == n) {
                father = raiz->valor;
            } else {
                father = pai(raiz->esq, n);
            }
        }
        if (n > raiz->valor) {
            if (raiz->dir != NULL && raiz->dir->valor == n) {
                father = raiz->valor;
            } else  {
                father = pai(raiz->dir, n);
            }
        }
    }
    return father;
}

int soma_par(arvore raiz) {
    int soma = 0;
    if (raiz != NULL) {
        if (raiz->valor%2 == 0){
            soma += raiz->valor;
        }
        soma += soma_par(raiz->esq) + soma_par(raiz->dir);
    }
    return soma;
}

void dobro(arvore raiz) {
    if (raiz != NULL) {
        raiz->valor = raiz->valor * 2;
        dobro(raiz->esq);
        dobro(raiz->dir);
    }
}

int busca(arvore raiz, int valor) {
    int encontrado = 0;
    if (raiz != NULL) {
        if (raiz->valor == valor) {
            encontrado = 1;
        }
        if (valor < raiz->valor) {
            encontrado = busca(raiz->esq, valor);
        }
        if (valor > raiz->valor) {
            encontrado = busca(raiz->dir, valor);
        }
    }
    return encontrado;
}

void descendentes(arvore raiz, int valor) {
    if (raiz != NULL) {
        if (raiz->valor == valor) {
            if (raiz->esq != NULL) {
                inorder(raiz->esq);
                inorder(raiz->dir);
            } else {
                inorder(raiz->dir);
            }
        }
        if (raiz->valor > valor) {
            descendentes(raiz->esq, valor);
        }
        if (raiz->valor < valor) {
            descendentes(raiz->dir, valor);
        }
    }
}

int altura(arvore raiz) {
    int bigger;
    if (raiz != NULL) {
        int left = altura(raiz->esq);
        int right = altura(raiz->dir);
        if (left > right) {
            bigger = left;
        } else {
            bigger = right;
        }
        return 1 + bigger;
    }
    return 0;
}

int somatorio(arvore raiz){
    int soma = 0;
    if(raiz != NULL) {
        soma += raiz->valor + somatorio(raiz->esq) + somatorio(raiz->dir);
    }
    return soma;
}

arvore remover(arvore raiz, int valor, int *caiu) {
    if (raiz != NULL) {
        if (raiz->valor == valor) {
            if (raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                *caiu = 1;
                return NULL;
            }
            if (raiz->esq != NULL && raiz->dir == NULL) {
                arvore temp = raiz->esq;
                free(raiz);
                *caiu = 1;
                return temp;
            }
            if (raiz->dir != NULL && raiz->esq == NULL) {
                arvore temp = raiz->dir;
                free(raiz);
                *caiu = 1;
                return temp;
            }
            int menor = menor_valor(raiz->dir);
            raiz->valor = menor;
            raiz->dir = remover(raiz->dir, menor, caiu);
            if (*caiu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *caiu = 0;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *caiu = 1;
                        break;
                    case -1:
                        *caiu = 1;
                        return rotacao(raiz);
                        break;
                }
            }
            return raiz;
        } else if (valor < raiz->valor) {
            raiz->esq = remover(raiz->esq, valor, caiu);
            if (*caiu) {
                //Atualização dos Fatores de Balanço após a árvore à esquerda diminuir
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *caiu = 0;
                        break;
                    case 1:
                        *caiu = 1;
                        return rotacao(raiz);
                        break;
                    case -1:
                        raiz->fb = 0;
                        *caiu = 1;
                        break;
                }
                return raiz;
            }
        } else {
            raiz->dir = remover(raiz->dir, valor, caiu);
            if (*caiu) {
                //Atualização dos Fatores de Balanço após a árvore à direita diminuir
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *caiu = 0;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *caiu = 1;
                        break;
                    case -1:
                        *caiu = 1;
                        return rotacao(raiz);
                        break;
                }
                return raiz;
            }
        }
    }
    *caiu = 0;
    return raiz;
}

int menor_valor(arvore raiz) {
    int menor = raiz->valor ? raiz->valor : NULL;
    if (raiz->esq != NULL) {
        menor = menor_valor(raiz->esq);
    }
    return menor;
}
