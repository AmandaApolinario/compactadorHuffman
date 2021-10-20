CC=gcc
CFLAGS=-lm -Wall

all: Compacta Descompacta

Compacta: main.c arvore.c bitmap.c compac.c ListaArvore.c descompac.c
	$(CC) -o Compacta main.c arvore.c bitmap.c compac.c ListaArvore.c descompac.c $(CFLAGS)
	
Descompacta: main.c arvore.c bitmap.c descompac.c ListaArvore.c compac.c
	$(CC) -o Descompacta main.c arvore.c bitmap.c descompac.c ListaArvore.c compac.c $(CFLAGS)
