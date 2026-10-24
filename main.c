#include <stdio.h>
#include "ListaDinEncadDupla.h"

static struct aluno mk(int matricula, float n1, float n2, float n3) {
    struct aluno a;
    a.matricula = matricula;
    snprintf(a.nome, sizeof(a.nome), "Aluno %d", matricula);
    a.n1 = n1; a.n2 = n2; a.n3 = n3;
    return a;
}

/* Imprime a lista usando apenas a interface publica:
   NULL <- [33] <-> [23] -> NULL */
static void imprime(const char *rotulo, Lista *li) {
    int i, n = tamanho_lista(li);
    struct aluno a;
    printf("  %-22s tam=%d: ", rotulo, n);
    if (n == 0) {
        printf("(vazia)\n");
        return;
    }
    printf("NULL <-");
    for (i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &a);
        printf(" [%d] %s", a.matricula, i < n ? "<->" : "-> NULL");
    }
    printf("\n");
}

/* Monta uma lista com as matriculas dadas, inserindo no final. */
static Lista* monta(const int *mats, int n) {
    Lista *li = cria_lista();
    for (int i = 0; i < n; i++)
        insere_lista_final(li, mk(mats[i], 0, 0, 0));
    return li;
}

static void titulo(const char *t) {
    printf("\n%s\n", t);
}

int main(void) {
    Lista *li;

    /* ---------- Questao 1 ---------- */
    titulo("Q1 - imprime_lista_inversa em [33, 23, 16]  (esperado: 16 23 33)");
    {
        int m[] = {33, 23, 16};
        li = monta(m, 3);
        imprime("lista", li);
        printf("  inversa: ");
        imprime_lista_inversa(li);
        libera_lista(li);

        li = cria_lista();
        printf("  vazia:   ");
        imprime_lista_inversa(li);
        libera_lista(li);
        printf("  NULL:    ");
        imprime_lista_inversa(NULL);
    }

    /* ---------- Questao 2 ---------- */
    titulo("Q2 - lista_consistente");
    {
        int m[] = {33, 23, 16};
        li = monta(m, 3);
        printf("  [33, 23, 16] -> %d (esperado 1)\n", lista_consistente(li));
        libera_lista(li);
        li = cria_lista();
        printf("  vazia        -> %d (esperado 1)\n", lista_consistente(li));
        libera_lista(li);
        printf("  NULL         -> %d (esperado 0)\n", lista_consistente(NULL));
    }

    /* ---------- Questao 3 ---------- */
    titulo("Q3 - remove_lista corrigida em [33, 23, 16]");
    {
        int m[] = {33, 23, 16};
        li = monta(m, 3);
        imprime("antes", li);
        remove_lista(li, 23);
        imprime("remove do meio", li);
        remove_lista(li, 33);
        imprime("remove do inicio", li);
        remove_lista(li, 16);
        imprime("remove o unico", li);
        printf("  consistente=%d (esperado 1)\n", lista_consistente(li));
        libera_lista(li);
    }

    // /* ---------- Questao 4 ---------- */
    // titulo("Q4 - remove_lista_pos em [10, 20, 30, 40, 50]");
    // {
    //     int m[] = {10, 20, 30, 40, 50};
    //     li = monta(m, 5);
    //     imprime("antes", li);
    //     remove_lista_pos(li, 3);
    //     imprime("pos 3 (meio)", li);
    //     remove_lista_pos(li, 4);
    //     imprime("pos 4 (ultima)", li);
    //     remove_lista_pos(li, 1);
    //     imprime("pos 1 (primeira)", li);
    //     printf("  pos 9 devolve %d (esperado 0)\n", remove_lista_pos(li, 9));
    //     printf("  consistente=%d (esperado 1)\n", lista_consistente(li));
    //     libera_lista(li);
    // }

    // /* ---------- Questao 5 ---------- */
    // titulo("Q5 - move_para_inicio em [10, 20, 30, 40]");
    // {
    //     int m[] = {10, 20, 30, 40};
    //     li = monta(m, 4);
    //     imprime("antes", li);
    //     move_para_inicio(li, 30);
    //     imprime("move 30 (meio)", li);
    //     move_para_inicio(li, 40);
    //     imprime("move 40 (ultimo)", li);
    //     printf("  move 40 (ja e o primeiro) devolve %d (esperado 1)\n",
    //            move_para_inicio(li, 40));
    //     printf("  move 99 devolve %d (esperado 0)\n", move_para_inicio(li, 99));
    //     printf("  consistente=%d (esperado 1)\n", lista_consistente(li));
    //     libera_lista(li);
    // }

    // /* ---------- Questao 6 ---------- */
    // titulo("Q6 - remove_todos(7)");
    // {
    //     int m[] = {7, 3, 7, 7, 5, 7};
    //     int t[] = {7, 7, 7};
    //     li = monta(m, 6);
    //     imprime("antes", li);
    //     printf("  devolve %d (esperado 4)\n", remove_todos(li, 7));
    //     imprime("depois", li);
    //     printf("  consistente=%d (esperado 1)\n", lista_consistente(li));
    //     libera_lista(li);

    //     li = monta(t, 3);
    //     imprime("todos iguais a 7", li);
    //     printf("  devolve %d (esperado 3)\n", remove_todos(li, 7));
    //     imprime("depois", li);
    //     libera_lista(li);
    // }

    // /* ---------- Questao 7 ---------- */
    // titulo("Q7 - inverte_lista em [1, 2, 3, 4, 5]");
    // {
    //     int m[] = {1, 2, 3, 4, 5};
    //     li = monta(m, 5);
    //     imprime("antes", li);
    //     inverte_lista(li);
    //     imprime("depois", li);
    //     printf("  consistente=%d (esperado 1)\n", lista_consistente(li));
    //     libera_lista(li);

    //     li = cria_lista();
    //     inverte_lista(li);                  /* nao pode travar */
    //     inverte_lista(NULL);                /* nem esta */
    //     printf("  vazia e NULL: sem travar\n");
    //     libera_lista(li);
    // }

    // /* ---------- Questao 8 ---------- */
    // titulo("Q8 - eh_palindromo");
    // {
    //     int p1[] = {1, 2, 3, 2, 1};         /* impar: 1 */
    //     int p2[] = {4, 8, 8, 4};            /* par:   1 */
    //     int p3[] = {1, 2, 2, 3};            /* nao:   0 */
    //     int p4[] = {9};                     /* um:    1 */

    //     li = monta(p1, 5);
    //     printf("  1 2 3 2 1 -> %d (esperado 1)\n", eh_palindromo(li));
    //     libera_lista(li);
    //     li = monta(p2, 4);
    //     printf("  4 8 8 4   -> %d (esperado 1)\n", eh_palindromo(li));
    //     libera_lista(li);
    //     li = monta(p3, 4);
    //     printf("  1 2 2 3   -> %d (esperado 0)\n", eh_palindromo(li));
    //     libera_lista(li);
    //     li = monta(p4, 1);
    //     printf("  9         -> %d (esperado 1)\n", eh_palindromo(li));
    //     libera_lista(li);
    //     li = cria_lista();
    //     printf("  vazia     -> %d (esperado 1)\n", eh_palindromo(li));
    //     libera_lista(li);
    //     printf("  NULL      -> %d (esperado 0)\n", eh_palindromo(NULL));
    // }

    printf("\n");
    return 0;
}