#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "ListaArvore.h"
#include "compac.h"
#include "descompac.h"


int main(int argc, char** argv) {
	if(argc ==2){
		if(strcmp(argv[0],"./Compacta")==0){
			int* vetor = LeArquivo(argv[1]);
			OrdV* ord = OrdenaVetor(vetor);

			Lista* lista = CriaListaFolhas(ord);
			Arv* arv = CriaArvoreHuff(lista);
			int qtd = qtdFolhasArv(arv);

			TabelaBits* tabela = arvBits(arv,qtd);
			arqPraBinario(tabela, argv[1], qtd,arv);
			
			DestroiLista(lista);
		}
		else{
			long int size = tamArquivo(argv[1]);

			FILE* compac = fopen(argv[1],"rb");
			char* ext = pegaExtensao(compac);

			descompactaArq(argv[1],ext,compac,size);

			fclose(compac);
		}
		
	}

	else{
		printf("Por favor insira o nome do arquivo\n");
	}

  return 0;
}