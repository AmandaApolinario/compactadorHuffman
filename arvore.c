#include "bitmap.h"
#include "arvore.h"

struct arv{
  int ehfolha;
  int freq;
  unsigned char carac;
  Arv* dir;
  Arv* esq;
};

struct VetorOrdenado{
  unsigned char c;
  int frequencia;
};

struct tabelabits{
	unsigned char c;
	char bits[50];
};


Arv* cria_folha(unsigned char c, int freq){
  Arv* arv = (Arv*)malloc(sizeof(Arv));

  arv->freq = freq;
  arv->carac = c;
  arv->ehfolha = 1; //1 para sim
  arv->dir = NULL;
  arv->esq = NULL;

  return arv;
}

Arv* cria_no(Arv* dir, Arv* esq){
  Arv* arv = (Arv*)malloc(sizeof(Arv));

  arv->freq = dir->freq + esq->freq;
  arv->dir = dir;
  arv->esq = esq;
  arv->ehfolha = 0; //0 para nao

  return arv;
}

int* LeArquivo(char* NomeArquivo){
  int* Vetor = (int*)calloc(257,sizeof(int));

  FILE* arquivo = fopen(NomeArquivo,"r");

	unsigned char buffer[1];

	while(fread(buffer,sizeof(unsigned char),1,arquivo)){
		Vetor[buffer[0]]++;
	}

	fclose(arquivo);
  return Vetor;
}


unsigned char RetornaChar(Arv* arv){
  return arv->carac;
}

OrdV* OrdenaVetor(int* vetor){
  int i=0, j;
  OrdV* ord = (OrdV*)calloc(257,sizeof(OrdV));

  while(i<257){
		
    if(vetor[i] != 0){
      ord[i].c = i;
      ord[i].frequencia = vetor[i];
    }
		i++;
  }

  int aux;
  char aux2;

  for(i=0;i<256;i++){
    for(j=0;j<256-1-i;j++){
      if(ord[j].frequencia > ord[j+1].frequencia){
        aux = ord[j].frequencia;
        aux2 = ord[j].c;
        ord[j].frequencia = ord[j+1].frequencia;
        ord[j].c = ord[j+1].c;
        ord[j+1].frequencia = aux;
        ord[j+1].c = aux2;
      }
    }
  }

	free(vetor);
  return ord;
}

int ReturnFreq(OrdV* ord, int i){
  return ord[i].frequencia;
}

unsigned char ReturnChar(OrdV* ord, int i){
  return ord[i].c;
}

int qtdFolhasArv(Arv *arvore){

  if(arvore->esq == NULL && arvore->dir == NULL){
    //caso base
    return 1;
  }
  else if(arvore->esq != NULL && arvore->dir == NULL){
    return qtdFolhasArv(arvore->esq);
  }
  else if(arvore->esq == NULL && arvore->dir != NULL){
    return qtdFolhasArv(arvore->dir);
  }
  return qtdFolhasArv(arvore->esq) + qtdFolhasArv(arvore->dir);
    
}

void arvImprime(Arv *arvore){
  if(arvore != NULL){
		if(EhFolha(arvore) == 1){
      printf("1%c",RetornaChar(arvore));
		}
		else{
			printf("0");
		}
    	arvImprime(arvore->esq);
    	arvImprime(arvore->dir);   
    }
}


void arvImprimeNoArqBin(Arv *arvore,FILE* arq){
		bitmap* bm=bitmapInit(8);
		char* temp;

		if(arvore != NULL){
			if(EhFolha(arvore) == 1){
				//salva a folha
				fprintf(arq,"1");

				//salva o char utilizando o bitmap
				temp = decParaBin(RetornaChar(arvore));
				for(int i=0;i<8;i++){
					bitmapAppendLeastSignificantBit(bm, temp[i]);
				}
				fprintf(arq,"%c",bitmapGetContents(bm)[0]);
				free(temp);
			}
		else{
			//salva o no
			fprintf(arq,"0");
		}
    	arvImprimeNoArqBin(arvore->esq,arq);
    	arvImprimeNoArqBin(arvore->dir,arq);
        
    }
		bitmapLibera(bm);
}

Arv* arvLibera(Arv *arvore){
  if(arvore != NULL){
    arvLibera(arvore->esq);
    arvLibera(arvore->dir);

    free(arvore);
  }
  return NULL;
}

int EhFolha(Arv *arv){
	return arv->ehfolha;
}

int RetornaFreq(Arv* arv){
	return arv->freq;
}

TabelaBits* arvBits(Arv *arv,int qtd){

	TabelaBits* tabela = (TabelaBits*)malloc(qtd * sizeof(TabelaBits));

	for(int i=0;i<qtd;i++){
		//inicializa a tabela com string vazia
		strcpy(tabela[i].bits,"");
	}
	
	PreencheTabela(arv, tabela, 0,qtd);

	return tabela;
}

void PreencheTabela(Arv* arv,TabelaBits* tabela, int ini, int fim){
	//preenche a tabela utilizando quantas folhas tem na esquerda e na direita para calcular onde deve-se adicionar 0 e 1

	//por exemplo, adiciona 0 a todas as folhas da esquerda da raiz e 1 em todos da direita, chama recursivamente para preencher tudo
	int qtdFolhasEsq;

	if(arv->esq != NULL && arv->dir != NULL){
		qtdFolhasEsq = qtdFolhasArv(arv->esq); 

		for(int i=ini;i<qtdFolhasEsq+ini;i++){
			strcat(tabela[i].bits,"0");
		}
		for(int i=qtdFolhasEsq+ini;i<fim;i++){
			strcat(tabela[i].bits,"1");
		}

		PreencheTabela(arv->esq,tabela,ini,qtdFolhasEsq+ini);
		PreencheTabela(arv->dir,tabela,qtdFolhasEsq+ini,fim);

	}
	else if(arv->esq == NULL && arv->dir != NULL){

		for(int i=ini;i<fim;i++){
			strcat(tabela[i].bits,"1");
		}
		PreencheTabela(arv->dir,tabela,ini,fim);
	}
	else if(arv->esq != NULL && arv->dir == NULL){

		for(int i=ini;i<fim;i++){
			strcat(tabela[i].bits,"0");
		}
		PreencheTabela(arv->esq,tabela,ini,fim);
	}
	else{
		tabela[fim-1].c = arv->carac;
	}
}

void ImprimeTabela(TabelaBits* tabela,int qtd){
	printf("\n");
	for(int i=0;i<qtd;i++){
		printf("%c %s\n",tabela[i].c,tabela[i].bits);
	}
}

unsigned char RetornaCharTabela(TabelaBits* tabela,int pos){
	return tabela[pos].c;
}

char* RetornaBitsTabela(TabelaBits* tabela,int pos){
	return tabela[pos].bits;
}

TabelaBits* PoeCharNaTabela(TabelaBits* tabela, unsigned char c, int aux){
  tabela[aux].c = c;

  return tabela;
}

TabelaBits* PoeBitsNaTabela(TabelaBits* tabela,unsigned char c, int pos,int aux){
  tabela[aux].bits[pos] = c;

  return tabela;
}

Arv* ReturnArvDir(Arv* arv){
  return arv->dir;
}

Arv* ReturnArvEsq(Arv* arv){
  return arv->esq;
}

Arv* InicArv(Arv* arv){
  arv = (Arv*)malloc(sizeof(Arv));
  arv->esq = NULL;
  arv->dir = NULL;

  return arv;
}