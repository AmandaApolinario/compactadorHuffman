#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

typedef struct arv Arv;

typedef struct VetorOrdenado OrdV;

typedef struct tabelabits TabelaBits;
#include "descompac.h"

/*
Cria uma folha da Arv, com arvores direita e esquerda iguais a NULL
input: caractere e sua frequencia no arquivo lido
output: a arvore com memoria alocada e devidamente preenchida 
pre-condicao: nenhuma
pos-condicao: retorna arvore com memoria alocada
*/
Arv* cria_folha(unsigned char c, int freq);

/*
Cria um no de Arv, com as arvores esqueda e direita passadas por parametro
input: arvores da esquerda e direita
output: no preenchido com as arvores passadas por parametro
pre-condicao: arvore esquerda e direita com memoria alocada  
pos-condicao: novo no criado e preenchido com as arvores passadas
*/
Arv* cria_no(Arv* dir, Arv* esq);

/*
Funcao que le o arquivo com o nome passado e retorna um vetor com a frequencia de cada caractere
input: nome do arquivo a ser lido
output: vetor de inteiros onde o char correspondente a frequencia eh a posicao no vetor
pre-condicao: nome de arquivo valido 
pos-condicao: vetor de inteiros alocado dinamicamente
*/
int* LeArquivo(char* NomeArquivo);

/*
Funcao que retorna o char da arvore passada
input: Arvore 
output: o caractere da arvore
pre-condicao: Arvore alocada e que seja uma folha
pos-condicao: nenhuma
*/
unsigned char RetornaChar(Arv* arv);

/*
Funcao que ordena o vetor passado e retorna o resultado
input: Vetor de inteiros com as frequencias dos caracteres, representados pela posicao no vetor
output: Um vetor do struct OrdV, que contem o caractere e sua frequencia em ordem crescente
pre-condicao: vetor de inteiros alocado e valido
pos-condicao: vetor OrdV alocado dinamicamente e preenchido em ordem crescente 
*/
OrdV* OrdenaVetor(int* vetor);

/*
Funcao que retorna a frequencia de uma posicao do vetor ord
input: Vetor ord contendo caracteres e suas frequencias, inteiro da posicao que deseja ser retornada
output: frequencia da posicao desejada
pre-condicao: Vetor ordV ordenado e alocado dinamicamente, inteiro passado ser uma posicao valida
pos-condicao: nenhuma 
*/
int ReturnFreq(OrdV* ord, int i);

/*
Funcao que retorna o char da posicao i passada no vetor OrdV
input: Vetor ord com caracteres e frequencias ordenados, posicao i procurada
output: unsigned char da posicao procurada
pre-condicao: Vetor ordV ordenado e alocado dinamicamente, inteiro passado ser uma posicao valida
pos-condicao: nenhuma
*/
unsigned char ReturnChar(OrdV* ord, int i);

/*
Conta quantas folhas uma arvore tem e retorna esse valor
input: Arvore que tera as folhas contadas
output: Quantidade de folhas da arvore
pre-condicao: Arvore valida e alocada dinamicamente
pos-condicao: nenhuma 
*/
int qtdFolhasArv(Arv *arvore);

/*
FUNCAO DE TESTE para imprimir a arvore no terminal
input:arvore a ser impressa
output: representacao da arvore no terminal
pre-condicao: arvore valida e alocada dinamicamente
pos-condicao: nenhuma 
*/
void arvImprime(Arv *arvore);

/*
Funcao que salva a arvore no arquivo compactado
input: Arvore a ser salva e arquivo que sera passado
output: arvore salva no arquivo 
pre-condicao: arvore alocada dinamicamente e valida, arquivo ja aberto e em modo de escrita
pos-condicao: nenhuma
*/
void arvImprimeNoArqBin(Arv *arvore,FILE* arq);

/*
Libera a memoria de uma arvore
input: arvore a ser liberada
output: a arvore nula
pre-condicao: arvore alocada dinamicamente
pos-condicao: memoria alocada na arvore liberada
*/
Arv* arvLibera(Arv *arvore);

/*
Verifica se a arvore passada eh um no ou folha
input: arvore a ser verificada
output: 1 se a arvore for folha, 0 se for no
pre-condicao: arvore inicializada e alocada dinamicamente
pos-condicao: nenhuma 
*/
int EhFolha(Arv *arv);

/*
Funcao que retorna a frequencia de uma arvore, a frequencia eh a soma das frequencias de todas as arvores abaixo dela, caso seja folha eh a frequencia que o caractere aparece no arquivo
input: arvore a ser verificada
output: inteiro da frequencia desejada
pre-condicao: arvore alocada dinamicamente
pos-condicao: nenhuma
*/
int RetornaFreq(Arv* arv);

/*
Inicializa a tabela de bits com strings vazias, a tabela contera, quando preenchida, os bits da compactacao de huffman e o char que esta sendo compactado
input: arvore de huffman e a quantidade de folhas de uma arvore, ou seja quantos caracteres existem
output: a tabela para compactar o arquivo em binario
pre-condicao: arvore alocada e no modelo de huffman, quantidade de folhas da arvore passada
pos-condicao: tabela de bits alocada dinamicamente e corretamente preenchida 
*/
TabelaBits* arvBits(Arv *arv,int qtd);

/*
Funcao que percorre a arvore e preenche a tabela de bits com 0s para os caracteres a esquerda do no observado, e 1s para os a direita. Percorre a arvore de forma recursiva
input: Arvore percorrida, a tabela de bits para compactacao, inteiros de inicio e fim, que correspondem a arvore percorrida, para preencher apenas as posicao corretas
output: nenhuma
pre-condicao: arvore alocada e valida, tabela de bits alocada e valida, inicio e final correspondentes a recursividade da funcao
pos-condicao: tabela de bits preenchida
*/
void PreencheTabela(Arv* arv,TabelaBits* tabela, int ini, int fim);

/*
FUNCAO DE TESTE para imprimir a tabela de bits no terminal, apenas para verificacao
input: tabela de bits e a quantidade de caracteres nela
output: os caracteres e suas representacoes em binario no terminal
pre-condicao: a tabela de bits preenchida e alocada, a quantidade correta de elementos na tabela
pos-condicao: nenhuma 
*/
void ImprimeTabela(TabelaBits* tabela,int qtd);

/*
Funcao que retorna o char da posicao desejada
input:tabela de bits e a posicao que esta sendo procurada
output: o unsigned char correspondente a posicao passada
pre-condicao: tabela de bits preenchida e alocada dinamicamente,posicao valida no vetor
pos-condicao: nenhuma
*/
unsigned char RetornaCharTabela(TabelaBits* tabela,int pos);

/*
Funcao que retorna o vetor de char dos bits correspondentes ao caractere da posicao passada
input:tabela de bits e a posicao que esta sendo procurada
output: vetor de char com os bits correspondentes
pre-condicao: tabela de bits preenchida e alocada dinamicamente,posicao valida no vetor
pos-condicao: nenhuma
*/
char* RetornaBitsTabela(TabelaBits* tabela,int pos);

/*
Preenche a posicao na tabela com o caractere passado
input: tabela de bits a ser preenchida, o char que sera colocado e o auxiliar que representa a posicao na tabela
output: caractere preenchido na tabela
pre-condicao: tabela de bits alocada dinamicamente, posicoes validas 
pos-condicao: tabela preenchida
*/
TabelaBits* PoeCharNaTabela(TabelaBits* tabela,unsigned char c, int aux);

/*
Preenche a posicao na tabela com os bits correspondentes a compactacao de huffman
input: tabela de bits a ser preenchida, o char que sera colocado, a posicao no vetor de bits, e o auxiliar que representa a posicao na tabela
output: tabela preenchida com o bit passado
pre-condicao: tabela de bits alocada dinamicamente, posicoes validas 
pos-condicao: tabela preenchida
*/
TabelaBits* PoeBitsNaTabela(TabelaBits* tabela, unsigned char c, int pos, int aux);

/*
Retorna a arvore da direita
input: no de uma arvore
output: a arvore direita desta
pre-condicao: arvore alocada dinamicamente e que seja um no
pos-condicao: arvore da direita que ja estava inicializada 
*/
Arv* ReturnArvDir(Arv* arv);

/*
Retorna a arvore da esquerda
input: no de uma arvore
output: a arvore esquerda desta
pre-condicao: arvore alocada dinamicamente e que seja um no
pos-condicao: arvore da esquerda que ja estava inicializada 
*/
Arv* ReturnArvEsq(Arv* arv);

/*
Retorna uma arvore com memoria alocada e ramificação dir e esq iguais a NULL
input: uma arvore 
output: a arvore inicializada
pre-condição: arvore nao alocada dinamicamente
pos-condicao: arvore com memoria alocada e com ramificações igualadas a NULL
*/
Arv* InicArv(Arv* arv);

#endif