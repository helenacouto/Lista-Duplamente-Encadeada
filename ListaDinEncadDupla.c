#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"

/* Definicao do tipo lista: oculta de quem usa a biblioteca.
   Com struct aluno de 48 bytes, sizeof(Elem) = 64 bytes em uma
   plataforma de 64 bits, contra 56 na lista encadeada simples. */
struct elemento {
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

/* --- criacao e destruicao ---------------------------------- */

Lista* cria_lista(void) {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;   /* avanca antes de liberar */
            free(no);
        }
        free(li);                /* libera o bloco do inicio */
    }
}

/* --- informacoes de estado --------------------------------- */

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;               /* parametro mantido por simetria com as demais */
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;            /* lista invalida */
    if (*li == NULL)
        return 1;            /* nenhum elemento alocado */
    return 0;
}

/* --- insercao ---------------------------------------------- */

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;    /* sem memoria: a lista esta cheia */
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if (*li != NULL)             /* lista nao vazia */
        (*li)->ant = no;         /* o antigo primeiro ganha antecessor */
    *li = no;
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->ant = NULL;
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else {
        /* O livro declara ante sem valor inicial. A inicializacao com
           NULL nao altera o comportamento e elimina o aviso
           "may be used uninitialized" do gcc com -O2. */
        Elem *ante = NULL, *atual = *li;
        while (atual != NULL &&
               atual->dados.matricula < al.matricula) {
            ante = atual;
            atual = atual->prox;
        }
        if (atual == *li) {      /* insere inicio */
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        } else {                 /* insere no meio ou no final */
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if (atual != NULL)   /* nao e o ultimo */
                atual->ant = no;
        }
        return 1;
    }
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    *li = no->prox;
    if (no->prox != NULL)          /* existe um seguinte */
        no->prox->ant = NULL;      /* ele passa a ser o primeiro */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no->prox != NULL)
        no = no->prox;
    if (no->ant == NULL)           /* primeiro e unico */
        *li = no->prox;
    else
        no->ant->prox = NULL;      /* penultimo obtido pelo proprio no */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)                /* chave ausente */
        return 0;
    if (no->ant == NULL)           /* remove o primeiro */
        *li = no->prox;
    else
        no->ant->prox = no->prox;
    if (no->prox != NULL)          /* nao e o ultimo */
        no->prox->ant = no->ant;
    free(no);
    return 1;
}

/* --- busca ------------------------------------------------- */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

/* =========== QUESTAO 1 =========== */
/*
Custo O(n). O primeiro laco chega ao ultimo elemento por prox em n-1 passos
e o segundo volta ate o primeiro por ant em mais n-1 passos. Cada elemento e
visitado duas vezes, ou seja, 2n passos, que e O(n). Memoria extra O(1).
*/
void imprime_lista_inversa(Lista* li) {
    if (li == NULL || *li == NULL) {
        printf("(lista vazia)\n");
        return;
    }

    Elem *no = *li;
    while (no->prox != NULL) no = no->prox;

    while (no != NULL) {
        printf("%d ", no->dados.matricula);
        no = no->ant;
    }
    printf("\n");
    return;
}

/* =========== QUESTAO 2 =========== */
int lista_consistente(Lista* li) {
    if (li == NULL) return 0;
    if (*li == NULL) return 1;

    Elem *no = *li;
    if (no->ant != NULL) return 0;

    while (no->prox != NULL) {
        if (no->prox->ant != no) return 0;
        no = no->prox;
    }
    return 1;
}

/* =========== QUESTAO 3 =========== */
/*
Considere o codigo:
int remove_lista(Lista* li, int mat){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL) return 0;
    no->ant->prox = no->prox;
    free(no);
    return 1;
}

a) Considerando a lista '{33, 23, 16}', ao realizar a chamada
remove_lista(li, 33) a funcao vai tentar a acessar o no anterior
ao 33, porem e NULL ja que 33 e o primeiro item da lista.

b) Considerando novamente a litsa '{33, 23, 16}', ao realizar a
chamada remove_lista(li, 23) aqui esta o panorama dos nos:
[33]->ant: NULL
[33]->prox: [16]
[16]->ant: (antigo endereco liberado de [23])
[16]->prox: NULL

A funcao tamanho_lista devolve 2 porque ele vai contar atraves dos ->prox.
Enquanto lista_consistente vai verificar o ->ant e e quando via perceber
que o ->ant do no [16] nao foi configurado corretamente ao remover [23].

Codigo corrigido ja foi implementado pela biblioteca anteriormente:
int remove_lista(Lista* li, int mat) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;
    Elem* no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)
        return 0;
    if (no->ant == NULL)
        *li = no->prox;
    else
        no->ant->prox = no->prox;
    if (no->prox != NULL)
        no->prox->ant = no->ant;
    free(no);
    return 1;
}
*/

/* =========== QUESTAO 4 =========== */
/*
Custo O(n). O tamanho_lista percorre a lista inteira (n passos) para validar
pos, e o for avanca ate pos-1 passos. Isso vale ate para pos = 1, por causa do
tamanho_lista. Depois de localizado o no, a remocao em si e O(1): o antecessor
vem de no->ant, sem segundo ponteiro de percurso.
*/
int remove_lista_pos(Lista *li, int pos) {
    if (li == NULL || *li == NULL) return 0;
    if (pos < 1 || pos > tamanho_lista(li)) return 0;

    Elem *no = *li;

    for (int i = 0; i < pos - 1; i++)
        no = no->prox;
    
    if (no->ant == NULL) {
        *li = no->prox;
    } else {
        no->ant->prox = no->prox;
    }
    if (no->prox != NULL) {
        no->prox->ant = no->ant;
    }
    free(no);
    return 1;
}

/* =========== QUESTAO 5 =========== */
/*
Elemento no meio da lista: 5 campos de ponteiro nos nos (6 escritas contando *li).
  1. no->ant->prox = no->prox   o anterior passa a pular o no
  2. no->prox->ant = no->ant    o seguinte aponta para o anterior
  3. no->prox = *li             o no aponta para o antigo primeiro
  4. no->ant = NULL             o no passa a nao ter antecessor
  5. (*li)->ant = no            o antigo primeiro aponta de volta para o no
  Alem disso, *li = no atualiza o inicio.

Elemento no final: 4 campos (5 contando *li). Como nao existe seguinte,
no->prox e NULL e o if da escrita 2 nao executa. Nenhum malloc nem free.
*/
int move_para_inicio(Lista* li, int mat) {
    if (li == NULL || *li == NULL) return 0;
    if ((*li)->dados.matricula == mat) return 1;

    Elem* no = (*li)->prox;
    while (no != NULL && no->dados.matricula != mat) {
        no = no->prox;
    }
    if (no == NULL) return 0;

    no->ant->prox = no->prox;
    if (no->prox != NULL) 
        no->prox->ant = no->ant;

    no->prox = *li;
    no->ant = NULL;
    (*li)->ant = no;
    *li = no;
    return 1;
}

/* =========== QUESTAO 6 =========== */
int remove_todos(Lista* li, int mat) {
    if (li == NULL || *li == NULL) return 0;

    Elem* no = *li, *ant = NULL;
    int cont = 0;
    while(no != NULL) {
        if (no->dados.matricula == mat) {
            if (ant != NULL) {
                ant->prox = no->prox;

                if (no->prox != NULL) no->prox->ant = ant;
                
                free(no);
                no = ant->prox;

                cont++;
            } else {
                *li = no->prox;
                if (*li != NULL) (*li)->ant = NULL;  
                free(no);
                no = *li;

                cont++;
            }
        } else {
            ant = no;
            no = no->prox;
        }
    }

    return cont;
}

/* =========== QUESTAO 7 =========== */
/*
Justificativa: na lista invertida, o sucessor de cada no e o seu antigo
antecessor, e o antecessor e o seu antigo sucessor. Trocar ant e prox em cada
no faz exatamente isso. Como os dois campos ja eram coerentes entre si, a
lista invertida tambem fica coerente: nenhuma ligacao e criada ou desfeita,
so reinterpretada. O inicio precisa ser atualizado para o antigo ultimo, pois
o antigo primeiro agora tem prox NULL e passa a ser o fim.

Custo O(n): um passo por no, com trabalho constante em cada um e sem alocacao.
*/
void inverte_lista(Lista* li) {
    if (li == NULL || *li == NULL) return;

    Elem *no = *li, *ante = NULL;

    while (no->prox != NULL) {
        no->ant = no->prox;
        no->prox = ante;
        ante = no;
        no = no->ant;
    }

    if (no->ant != NULL) {
        no->prox = ante;
        no->ant = NULL;
        *li = no;
    }
    return;
}

/* =========== QUESTAO 8 =========== */
/*
Condicao de parada: com n elementos, bastam n/2 comparacoes (divisao inteira).
Se n e par, os dois ponteiros se cruzam depois da ultima comparacao. Se n e
impar, o elemento do meio sobra e nao precisa ser comparado consigo mesmo.
Lista com 0 ou 1 elemento e palindroma sem comparar nada.

Custo: O(n). Chegar ao ultimo elemento por prox custa n passos, e as n/2
comparacoes custam mais n passos de ponteiro. A memoria extra e O(1).

Lista simples: a estrategia exige recuar a partir do final, e sem o campo ant
isso nao existe. Para recuar um no seria preciso percorrer a lista desde o
inicio, o que custaria O(n) por passo e O(n^2) no total. As alternativas seriam
um vetor auxiliar ou alterar a lista, e o enunciado proibe as duas.
*/
int eh_palindromo(Lista *li) {
    if (li == NULL) return 0;
    if (*li == NULL) return 1;

    Elem *inicio = *li, *final = *li;
    
    int n = 1;
    while(final->prox != NULL) {
        final = final->prox;
        n++;
    }
    if (n == 1) return 1;

    n = n/2;
    for (int i = 0; i < n; i++) {
        if (inicio->dados.matricula != final->dados.matricula) return 0;
        else {
            inicio = inicio->prox;
            final = final->ant;
        }
    }
    return 1;
}
