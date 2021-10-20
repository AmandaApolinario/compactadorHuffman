#include "ListaArvore.h"

typedef struct celula Celula;

struct celula{
  Arv* arv;
  Celula *prox;
	Celula *ant;
};

struct lista{
  Celula* prim;
  Celula* ult;
};

Lista* InicLista(){
  Lista *list = (Lista*)malloc(sizeof(Lista));
  list->prim = NULL;
  list->ult = NULL;

  return list;
}

void InsereLista(Lista *lista,Arv* arv){
  //insere no fim da lista
	Celula *nova = (Celula*)malloc(sizeof(Celula));

  nova->arv = arv;
  nova->ant = lista->ult;
	if(nova->ant != NULL){
		nova->ant->prox = nova;
	}
	nova->prox = NULL;

  lista->ult = nova;

  if(lista->prim == NULL){
    lista->prim = nova;
  }

}

void InsereListaGenerico(Lista *lista,Arv* arv){
	//pra colocar na primeira posição é pos = -1
	//pra colocar em segundo, ou seja depois do primeiro, é pos = 0
	int pos=0;
  Celula *nova = (Celula*)malloc(sizeof(Celula));
  nova->arv = arv;
  Celula* temp = lista->prim;

  int freqTemp, freqArv, i=-1;
  freqArv = RetornaFreq(arv);

  while(temp != NULL){
 
    freqTemp = RetornaFreq(temp->arv);
    if(freqArv < freqTemp){
      if(i==-1){
        pos = -1;
        break;
      }
			break;    
    }
		i++;
		temp = temp->prox;
  }

  if(pos == -1){
    nova->prox = lista->prim;
    lista->prim = nova;

    if(lista->ult == NULL){
      lista->ult = nova;
    }
    return;
  }

  temp=lista->prim;

  for(int j=0;j<i;j++){
    temp = temp->prox;
  }

  if(temp == NULL) {
		nova->arv = arv;
		nova->prox = NULL;
  	lista->ult = nova;
    lista->prim = nova;
  
    return;      
  }
 
  nova->prox = temp->prox;
  temp->prox = nova;
  nova->ant = temp;

  if(nova->prox != NULL){
    nova->prox->ant = nova;
  }

  if(lista->ult == NULL){
    lista->ult = nova;
  }   
}

void DestroiLista(Lista *lista){    
	Celula *temp = lista->prim;
  Celula *prox;

  while(temp != NULL){
    prox = temp->prox;
    arvLibera(temp->arv);
    free(temp);
    temp = prox;
  }
	
	free(temp);
  free(lista);
}

Lista* CriaListaFolhas(OrdV* ord){
  int i = 0;
  Lista* lista = InicLista();
	
  while(i<256){
    if(ReturnFreq(ord,i) != 0){
      InsereLista(lista, cria_folha(ReturnChar(ord,i),ReturnFreq(ord,i)));
    }
    i++;
  }

	free(ord);
  return lista;
}

void RetiraLista(Lista *lista){
  Celula *retirar;
  retirar = lista->prim;

  lista->prim = retirar->prox;
  if(lista->prim == NULL){
    free(retirar);
    return;
  }
  lista->prim->ant = NULL;

  free(retirar);
}

Arv* CriaArvoreHuff(Lista* lista){

  while(lista->prim->prox != NULL){
    Arv* arv = cria_no(lista->prim->prox->arv,lista->prim->arv);

		//retira os dois primeiros elementos, pois foram adicionados na nova arv
    RetiraLista(lista);
    RetiraLista(lista);
	  InsereListaGenerico(lista, arv);
  }

	return lista->prim->arv;
}

void ImprimeLista(Lista *lista){
	Celula *temp;
  temp = lista->prim;

  while(temp!= NULL){
		if(EhFolha(temp->arv)==1){
    	printf("c:%c\n",RetornaChar(temp->arv));
		}
		printf("f: %d\n",RetornaFreq(temp->arv));
    temp = temp->prox;
  }
	printf("\n");
}

void ArvImprimeDaLista(Lista* l){
	arvImprime(l->prim->arv);
}