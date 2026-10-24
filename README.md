# Lista de exercícios: Lista dinâmica duplamente encadeada

Resolução da lista de exercícios da **Aula 08** da disciplina **Estrutura de Dados**
(Departamento de Informática, UFPB), sobre a lista dinâmica duplamente encadeada, em C.

## Sobre a atividade

Uma atividade da disciplina é uma **lista de exercícios** construída sobre uma biblioteca
que o professor apresenta em aula. Em vez de escrever um programa do zero, o trabalho é
**estender a biblioteca**: cada questão pede uma nova função, e todas seguem as mesmas regras.

1. A função é escrita dentro do arquivo `.c` da biblioteca.
2. O protótipo é acrescentado ao arquivo `.h`.
3. A função é testada a partir do `main.c`.
4. Toda função trata a lista inválida (`li == NULL`), a lista vazia e a lista com um único elemento.

As funções precisam ficar dentro do `.c` porque o tipo da lista é **opaco**: a `struct elemento`
só existe no `.c`, e por isso nenhuma função que percorre os nós (usando `prox` e `ant`)
compila fora dele.

### Questões

| Questão | Função | O que faz |
|---|---|---|
| 1 | `imprime_lista_inversa` | Imprime as matrículas do último para o primeiro, chegando ao fim por `prox` e voltando só por `ant` |
| 2 | `lista_consistente` | Verifica se os dois encadeamentos estão corretos (`ant` do primeiro é `NULL` e `no->prox->ant == no`) |
| 3 | `remove_lista` | Análise de uma versão com defeito e a versão corrigida (resposta escrita em comentário no `.c`) |
| 4 | `remove_lista_pos` | Remove o elemento de uma posição, usando um único ponteiro de percurso |
| 5 | `move_para_inicio` | Move um elemento para o início apenas religando ponteiros, como em um cache LRU |
| 6 | `remove_todos` | Remove todas as ocorrências de uma matrícula e devolve quantas foram removidas |
| 7 | `inverte_lista` | Inverte a lista no lugar, sem alocar nem liberar nós |
| 8 | `eh_palindromo` | Informa se a sequência de matrículas é a mesma nos dois sentidos, com dois ponteiros em sentidos opostos |

As respostas escritas pedidas no enunciado (por exemplo, o custo de cada função) estão em
comentários no `ListaDinEncadDupla.c`, junto de cada questão.

## Biblioteca base

A biblioteca de partida (`ListaDinEncadDupla.h` e `ListaDinEncadDupla.c`) é do
**Prof. Daniel Faustino Lacerda de Souza** e foi copiada, sem alterações, da pasta
`04-lista-dinamica-duplamente-encadeada` do repositório da disciplina:
[github.com/Ensino-UFPB/exemplosed1](https://github.com/Ensino-UFPB/exemplosed1).

Ela traz criação e destruição da lista, inserção (início, final e ordenada), remoção
(início, final e por matrícula) e busca (por posição e por matrícula). O que foi
acrescentado por mim está marcado nos arquivos:

- no `.h`, pela seção `ATIVIDADE`;
- no `.c`, pelos comentários `QUESTÃO N`, no final do arquivo.

## Organização do repositório

```
.
├── ListaDinEncadDupla.h    interface: tipo opaco e protótipos (base do professor + atividade)
├── ListaDinEncadDupla.c    implementação: base do professor + funções das questões
├── main.c                  programa de testes das questões
├── Makefile                compilação separada dos módulos
└── README.md
```

## Como compilar e executar

```bash
make        # gera o executável ./teste
./teste     # executa os testes
make clean  # remove os .o e o executável
```

Sem o `make`, a compilação manual é:

```bash
gcc -Wall -Wextra -std=c11 -o teste ListaDinEncadDupla.c main.c
```

O único requisito é um compilador C com suporte a C11 (`gcc` ou `clang`). Para procurar
vazamentos de memória nas funções que alocam ou liberam nós:

```bash
valgrind --leak-check=full ./teste
```

## Como os testes funcionam

O `main.c` tem um bloco por questão. Cada bloco monta uma lista, imprime o estado dela
antes e depois da operação, no formato `NULL <- [33] <-> [23] -> NULL`, e confere casos
de borda (lista vazia, `NULL`, elemento único, primeiro e último). Depois das operações
que alteram a lista, o programa chama `lista_consistente` para confirmar que `prox` e
`ant` continuam coerentes.

O `main.c` usa apenas o que está declarado no `.h`: em nenhum ponto ele acessa os campos
`ant`, `dados` ou `prox`.

## Convenções

- **Tipo opaco:** a `struct` interna é definida apenas no `.c`.
- **Compilação limpa:** o código compila com `gcc -Wall -Wextra -std=c11` sem avisos.
- **Retorno:** inserção e remoção devolvem `1` em caso de sucesso e `0` caso contrário.
- **Comentários sem acentuação** nos arquivos `.c` e `.h`, para evitar problemas de
  codificação em editores com outra página de código. Os arquivos `README.md` usam
  acentuação normal.
- **Nomes em português**, iguais aos dos slides e das listas de exercícios.

## Referências

- BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*. Rio de Janeiro: LTC, 2023.
- TENENBAUM, A. M.; LANGSAM, Y.; AUGENSTEIN, M. J. *Estruturas de dados usando C*. São Paulo: Makron Books, 1995.
- CORMEN, T. H. et al. *Algoritmos: teoria e prática*. 3. ed. Rio de Janeiro: Elsevier, 2012.

## Autoria

Atividade resolvida por Helena Couto, estudante de Ciência de Dados e Inteligência Artificial na UFPB. A biblioteca base e o enunciado da lista são do Prof. Daniel Faustino Lacerda de Souza.