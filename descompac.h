#ifndef DESCOMPAC_H
#define DESCOMPAC_H

#include "arvore.h"

/*
Le os primeiros caracteres do arquivo compactado ate achar um '-', retorna essa string
input: arquivo compactado
output: string com os caracteres lidos
pre-condicao: arquivo aberto em modo de leitura
pos-condicao: extensao retornada com memoria alocada
*/
char* pegaExtensao(FILE* arq);

/*
Abre o arquivo do nome passado e retorna o tamanho que ele ocupa
input: nome do arquivo que sera aberto
output: quantidade de bytes que o arquivo ocupa
pre-condicao: nome do arquivo valido
pos-condicao: arquivo que eh aberto eh fechado
*/
long int tamArquivo(char* nome);

/*
Funcao recursiva que le a arvore do arquivo e vai preenchendo
input: o arquivo aberto e o char lido, podendo ser 0, 1 ou o caractere da folha
output: arvore criada
pre-condicao: arquivo aberto em modo de leitura e c alocado
pos-condicao: arvore criada e com memoria alocada
*/
Arv* leCriaArv(FILE* arq,unsigned char* c);

/*
Abre o arquivo binario e o descompacta, utilizando a arvore de huffman
input: nome do arquivo para ser lido, arvore de huffman para descodificar o que foi salvo no arquivo
output: um novo arquivo criado e descompactado
pre-condicao: arquivo existente e arvole corretamente preenchida com as informacoes
pos-condicao: memoria liberada e arquivo descompactado
*/
void descompactaArq(char* arq,char* ext,FILE* compac,long int size);

/*
Transforma um numero inteiro em um vetor de char com seu numero binario representante
input:um numero inteiro
output:o numero em binario num vetor de char
pre-condicao:numero positivo
pos-condicao:vetor de char do binario
*/
char* decParaBin(int num);

/*
Funcao que adiciona zeros a esquerda do vetor binario, para completar os 8 bits
input:vetor de char com os bits de um numero
output: vetor completo ate que tenha 8 char 
pre-condicao: vetor num alocado e inicializado
pos-condicao: vetor com 0s adicionados a esquerda ate completar 8 caracteres
*/
char* zeroAesquerda(char* num);

#endif