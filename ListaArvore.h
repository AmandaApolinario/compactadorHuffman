#ifndef LISTAARVORE_H
#define LISTAARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct lista Lista;

/*
Funcao que inicia a lista de arvores como NULL
input:nenhum
output:A lista inicializada
pre-condicao: nenhuma
pos-condicao: a lista alocada e inicializada com NULL
*/
Lista* InicLista();

/*
Funcao que insere as arvores ao fim da lista,assim criando uma lista de arvores
input:A lista de arvores e uma arvore
output:atualiza a lista
pre-condicao: lista inicializada e alocada, arvore alocada e preenchida
pos-condicao:a arvore adicionada a lista
*/
void InsereLista(Lista* lista, Arv* arv);

/*
Insere a arvore que recebe ordenando-as pela frequencia, de menor para a maior
input:lista de arvores alocada, arvore para ser adicionada
output:a arvore adicionada na posicao crescente
pre-condicao: lista e arvore inicializadas e alocadas
pos-condicao: arvore adicionada
*/
void InsereListaGenerico(Lista *lista,Arv* arv);

/*
Libera a memoria da lista
input: a lista de arvores alocada
output: libera a memoria de toda a lista passada
pre-condicao: lista alocada e valida
pos-condicao: nenhuma
*/
void DestroiLista(Lista* lista);

/*
Funcao que cria a lista de folhas a partir do vetor ord
input: Vetor ord com todos os caracteres do arquivo lido e suas frequencias
output: uma lista de folhas de arvore, todos ordenados pela frequencia
pre-condicao: vetor OrdV valido e alocado, contendo os caracteres corretamente ordenados pela frequencia
pos-condicao: lista e folhas alocadas e adicionadas
*/
Lista* CriaListaFolhas(OrdV* ord);

/*
Funcao que retira o primeiro elemento de uma lista
input: uma lista alocada e preenchida com ao menos uma arvore
output: primeiro elemento da lista removido
pre-condicao: lista alocada e valida
pos-condicao: lista com o primeiro elemento removido e a posicao na lista liberada
*/
void RetiraLista(Lista *lista);

/*
Transforma uma lista de folhas em uma arvore de huffman, terminando apenas com uma raiz
input:lista de arvores
output: retorna a raiz da arvore de Huffman
pre-condicao: lista alocada e ordenada de forma crescente
pos-condicao: libera a memoria da lista e retorna a raiz da arvore
*/
Arv* CriaArvoreHuff(Lista* lista);

/*
Funcao para TESTES, imprime a lista de arvores
input: a lista de arvores
output: imprime no terminal a lista
pre-condicao: lista alocada e preenchida
pos-condicao: nenhuma
*/
void ImprimeLista(Lista* lista);

/*
Funcao para TESTES, imprime a primeira arvore da lista passada
input: lista de arvores alocada e preenchida com ao menos um elemento
output: imprime no terminal a arvore da primeira posicao
pre-condicao: lista alocada e preenchida
pos-condicao: nenhuma
*/
void ArvImprimeDaLista(Lista* l);

#endif