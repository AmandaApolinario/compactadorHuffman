#ifndef COMPAC_H
#define COMPAC_H

#include "arvore.h"

/*
Funcao que salva a arvore no arquivo binario e le o arquivo para ser compactado, chamando a funcao de compactar a cada 1000 caracteres mais o menos, para nao sobrecarregar o buffer
input: tabela de bits para transformar o que eh lido em binario, o nome do arquivo que sera lido, a quantidade de char na tabela, e a arvore que sera salva
output: criado o arquivo .comp e salva o texto codificado
pre-condicao: tabela e arvore alocadas e validas, nome do arquivo para ser lido existente 
pos-condicao: arquivos fechados e memoria alocada liberada
*/
void arqPraBinario(TabelaBits* tabela,char* nomeArq,int qtd,Arv* arv);

/*
Funcao que encontra na tabela a posicao que o char esta salvo
input: tabela com os bits representantes dos char salvos, o char que esta sendo procurado, o tamanho da tabela
output: o vetor de bits em binario que representa o char
pre-condicao: tabela de bits alocada e inicializada
pos-condicao: vetor de char dos bits
*/
char* encontraChar(TabelaBits* tabela, unsigned char c,int qtd);

/*
Funcao que, utilizando o bitmap, compacta os bits em seus representantes em binario e salva no arquivo passado por parametro
input: vetor de char com os bits 0 e 1, arquivo .compac
output: binario salvo no arquivo 
pre-condicao: vetor de char alocado e valido, arquivo aberto e em modo de escrita
pos-condicao: memoria do vetor de char liberada e binario salvo no arquivo
*/
void compactaSalvaArq(char* buffer,FILE* arq);

/*
Funcao que salva no ultimo bit do arquivo a quantidade de zeros que foram adicionados no bit anterior, para evitar salvar lixo
input: quantidade de bits que foram adicionados, o arquivo para salvar aberto
output: salva um numero de 1 a 7 no arquivo,em binario
pre-condicao: arquivo aberto e qtd maior que 0 e menor que 8
pos-condicao: nenhuma
*/
void salvaQtdBitsExtra(int qtd,FILE* arq);

/*
Para evitar de ter uma string muito grande lida para converter a binario, a funcao separa a maior quantidade de char divisivel por 8 e salva no arquivo passado, o resto eh retornado para a funcao lendo o arquivo
input: vetor de char com 0s e 1s, e o arquivo .comp que esta sendo escrito
output: vetor de char com os que nao foram salvos no arquivo
pre-condicao: vetor de char alocado e preenchido, arquivo aberto em modo de escrita 
pos-condicao: libera a memoria do que foi salvo ao arquivo
*/
char* separaAFrase(char* buffer,FILE* arq);

#endif