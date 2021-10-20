#include "compac.h"
#define MAX 1000
/*RESUMO

a funcao arqPraBinario vai lendo o arquivo txt e a cada +- 950 bits que transforma de letra pra binario, ele chama a funcao separa a frase

ai essa funcao pega so a maior quantidade de bytes inteiros, um q seja divisivel por 8, o resto ele retorna pra arqPraBinario continuar adicionando bits ate q ela tenha a qtd de bits e etc

ai isso eh pra evitar q tenha bytes incompletos quando ta convertendo

no ultimo byte, que pode ser incompleto, ta adicionando zeros pra completar os 8, e ai a ultima coisa q salva no .compac eh a quantidade de zeros adicionados, pq quando tiver descompactando a gnt pode saber quantos foram adicionados pra descartar
*/

void arqPraBinario(TabelaBits* tabela,char* nomeArq,int qtd,Arv* arv){
	FILE* arq = fopen(nomeArq,"r");
	char* buffer = malloc(sizeof(char)*MAX);
	strcpy(buffer,"");
  
	char nome[50];
  char* temp = (char*)malloc(sizeof(char)*50);
  int i=0;

  while(1){
    temp[i] = nomeArq[i];
    if(nomeArq[i] == '.'){
			i++;
      break;
    }
		i++;
  }

  temp[i] = '\0';

	strcpy(nome,temp);
	strcat(nome,"comp");

	FILE* arqBinario = fopen(nome,"wb");

	for(int j=i;j<strlen(nomeArq);j++){
		//salva o tipo de arquivo q ta recebendo
		fprintf(arqBinario,"%c",nomeArq[j]);
	}
	
	fprintf(arqBinario,"-");
	//salva a arvore
	arvImprimeNoArqBin(arv,arqBinario);

	if(arq == NULL){
		printf("erro abrindo arq\n");
	}
	if(arqBinario == NULL){
		printf("erro abrindo o arquivo binario\n");
	}

	unsigned char *buffer2 = (unsigned char*)malloc(MAX*sizeof(unsigned char));
	
	while(fread(buffer2,sizeof(unsigned char),1,arq)){
		strcat(buffer,encontraChar(tabela,buffer2[0],qtd));
		
		if(strlen(buffer)>950){
			buffer = separaAFrase(buffer,arqBinario);
		}
		
	}
	compactaSalvaArq(buffer, arqBinario);

	free(tabela);
	free(buffer);
	free(buffer2);
	free(temp);
	fclose(arq);
	fclose(arqBinario);
}


char* separaAFrase(char* buffer,FILE* arq){
	//retorna o buffer com uma quantidade exata de bytes, o resto coloco no buffer que vai retornar para continuar adicionando
	//ex buffer = "12345678123"
	//   buffer2 = "123" pq eh o q sobra dos 8 bits
	//	 buffer3 = "12345678" os 8 bits inteiros pra formar 1 byte certinho

	char* buffer2 = malloc(MAX*sizeof(char));
	char* buffer3 = malloc(MAX* sizeof(char));
	int inteiro,j=0,i;
	inteiro = strlen(buffer)/8;

	for(int i=inteiro*8;i<strlen(buffer);i++){
		buffer2[j] = buffer[i];
		j++;
	}
	buffer2[j] = '\0';

	for(i=0;i<inteiro*8;i++){
		buffer3[i] = buffer[i];
	}
	buffer3[i] = '\0';

	compactaSalvaArq(buffer3, arq);
	free(buffer);
	free(buffer3);
	return buffer2;
}

void compactaSalvaArq(char* buffer,FILE* arq){
	bitmap* bm=bitmapInit(MAX);

	int tam;
	tam = (strlen(buffer)+7)/8;//arredonda para cima
	int adicionados = (tam*8)-strlen(buffer);

	for(int i=0;i<adicionados;i++){
		//adicionando zeros ao final pra completar a quantidade de bits
		strcat(buffer,"0");
	}

	for(int i=0;i<tam*8;i++){
		bitmapAppendLeastSignificantBit(bm, buffer[i]);
	}

	for(int i=0;i<tam;i++){
		fprintf(arq,"%c",bitmapGetContents(bm)[i]);
	}
	if(adicionados != 0){
		salvaQtdBitsExtra(adicionados,arq);
	}
	bitmapLibera(bm);
}

void salvaQtdBitsExtra(int qtd,FILE* arq){
	bitmap* bm=bitmapInit(8);

	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 0);

	if(qtd == 1){
		bitmapAppendLeastSignificantBit(bm, 0);
		bitmapAppendLeastSignificantBit(bm, 0);
		bitmapAppendLeastSignificantBit(bm, 1);
	}
	else if(qtd == 2){
		bitmapAppendLeastSignificantBit(bm, 0);
		bitmapAppendLeastSignificantBit(bm, 1);
		bitmapAppendLeastSignificantBit(bm, 0);
		
	}
	else if(qtd == 3){
		bitmapAppendLeastSignificantBit(bm, 0);
		bitmapAppendLeastSignificantBit(bm, 1);
		bitmapAppendLeastSignificantBit(bm, 1);
	}
	else if(qtd == 4){
		bitmapAppendLeastSignificantBit(bm, 1);
		bitmapAppendLeastSignificantBit(bm, 0);
		bitmapAppendLeastSignificantBit(bm, 0);
	}
	else if(qtd == 5){
		bitmapAppendLeastSignificantBit(bm, 1);
		bitmapAppendLeastSignificantBit(bm, 0);
		bitmapAppendLeastSignificantBit(bm, 1);
	}
	else if(qtd == 6){
		bitmapAppendLeastSignificantBit(bm, 1);
		bitmapAppendLeastSignificantBit(bm, 1);
		bitmapAppendLeastSignificantBit(bm, 0);
	}
	else if(qtd == 7){
		bitmapAppendLeastSignificantBit(bm, 1);
		bitmapAppendLeastSignificantBit(bm, 1);
		bitmapAppendLeastSignificantBit(bm, 1);
	}
	fprintf(arq,"%c",bitmapGetContents(bm)[0]);

	bitmapLibera(bm);
}


char* encontraChar(TabelaBits* tabela, unsigned char c,int qtd){
	int i=0;
	int teste = 0;
	
	while(i<qtd){
		if(c == RetornaCharTabela(tabela, i)){
			teste = 1;
			break;
		}
		i++;
	}
	if(teste == 0){
		i--;
		printf("%c %d\n",c,c);
		printf("char n encontrado\n");

	}

	return RetornaBitsTabela(tabela, i);
}