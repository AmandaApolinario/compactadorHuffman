#include "descompac.h"

char* pegaExtensao(FILE* arq){
	int i=0;
	char *a = (char*)malloc(2*sizeof(char));
	char *temp = (char*)malloc(sizeof(char)*50);
	strcpy(temp,"");
	strcpy(a,"");

	while(1){
		fread(a,sizeof(char),1,arq);
		if(memcmp(a,"-",1)==0){
			break;
		}
		temp[i] = a[0];
		i++;
	}
	temp[i] = '\0';
	free(a);
	return temp;
}

long int tamArquivo(char* nome){
	FILE* compac = fopen(nome,"rb");
	fseek(compac, 0, SEEK_END);
  long int size = ftell(compac);
  fclose(compac);

	return size;
}

Arv* leCriaArv(FILE* arq,unsigned char* c){
	fread(c,sizeof(unsigned char),1,arq);

	if(c[0] == 	'0'){
		Arv* esq = leCriaArv(arq,c);
		return cria_no(leCriaArv(arq,c),esq);
	}
	else if(c[0] == '1'){

		fread(c,sizeof(unsigned char),1,arq);
		return cria_folha(c[0],0);
	}
	printf("\n:%c:\n",c[0]);
	printf("erro");
	return NULL;
}

void descompactaArq(char* arq,char* ext,FILE* compac,long int size){
	char nome[50];
	char* temp2 = (char*)malloc(sizeof(char)*50);
  int i=0;

	while(1){
    temp2[i] = arq[i];
    if(arq[i] == '.'){
      break;
    }
		i++;
  }
	
	temp2[i] = '\0';
	strcpy(nome,temp2);
	strcat(nome,"2.");
	strcat(nome,ext);

	FILE* descompac = fopen(nome,"w");
	if(descompac == NULL){
		printf("erro ao abrir o arquivo descompac\n");
		exit(0);
	}

	unsigned char* lido = (unsigned char*)malloc(size* sizeof(unsigned char));
	unsigned char* c = (unsigned char*)malloc(sizeof(unsigned char));
	i=0;

	
	Arv* arv2 = leCriaArv(compac,c);
	
	while(fread(c,sizeof(unsigned char),1,compac)){
		lido[i] = c[0];
		i++;
	}
	lido[i] = '\0';
	int tamLido = i;
	
	char* vet;
	Arv* temp;
	temp = arv2;
	int j;
	for(j =0;j <tamLido-2; j++){

		vet = decParaBin(lido[j]);

		for(int k=0;k<8;k++){
			//vai percorrendo a arvore para achar o char correspondente
			if(vet[k] == '1'){
			temp = ReturnArvDir(temp);
			}
			else{
				temp = ReturnArvEsq(temp);
			}
			if(EhFolha(temp) == 1){
				fprintf(descompac,"%c",RetornaChar(temp));

				temp = arv2;
			}
		}
		free(vet);
	}
	

	vet = decParaBin(lido[j]);
	j++;//numero q indica quantos zeros foram adicionados no final

	for(int k=0;k<8-lido[j];k++){//faz um loop para apenas considerar os bits validos
		if(vet[k] == '1'){
			temp = ReturnArvDir(temp);
		}
		else{
			temp = ReturnArvEsq(temp);
		}
		if(EhFolha(temp) == 1){
			fprintf(descompac,"%c",RetornaChar(temp));
			temp = arv2;
		}
	}

	arvLibera(arv2);
	fclose(descompac);
	free(temp2);
	free(lido);
	free(vet);
	free(c);
	free(ext);
}

char* decParaBin(int num){
	int *vet_bin = (int*)malloc(25*sizeof(int));
	char *vetFinal = (char*)malloc(25*sizeof(char));
	// variáveis de controle de loop
	int i = 0, j,k=0;
  
	// enquanto "num" for maior que 0
	while(num > 0){
		// obtém o resto da divisão de num por 2
		vet_bin[i] = num % 2;
		i++;
		num = num / 2;
	}

	for(j = i - 1; j >= 0; j--){
		vetFinal[k] = vet_bin[j] +'0';
		k++;
	}
	vetFinal[k] = '\0';

	char* vetor;
	vetor = zeroAesquerda(vetFinal);
	free(vetFinal);
  free(vet_bin);
	return vetor;
}

char* zeroAesquerda(char* num){
	int adi;
	char* nome = (char*)malloc(9*sizeof(char));
	strcpy(nome,"");
	
	adi = 8-strlen(num);
	for(int i=0;i<adi;i++){
		strcat(nome,"0");
	}
	strcat(nome,num);

	return nome;
}