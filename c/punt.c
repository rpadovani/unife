#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 15

struct prima_lista {
	int numero;
	struct prima_lista *next;
};

struct seconda_lista {
	int numero;
	struct seconda_lista *next;
};

void creaprima_lista( struct prima_lista **testa ) {
	int i, val = 0;
	struct prima_lista *p, *nuovo;
	srand(time(NULL)); 

	for (i=0; i<MAX; i++) {
		nuovo = (struct prima_lista*) malloc (sizeof (struct prima_lista));
		
		val = rand() % MAX;

		nuovo->numero = val;
		nuovo->next = NULL;

		if (*testa == NULL) {
			*testa = nuovo;
			p = *testa;
		} else {
			p->next = nuovo;
			p = p->next;
		}
	}

}


void creaseconda_lista( struct seconda_lista **testa ) {
	int i, val = 0;
	struct seconda_lista *p, *nuovo;
	srand(time(NULL)); 

	for (i=0; i<MAX; i++) {
		nuovo = (struct seconda_lista*) malloc (sizeof (struct seconda_lista));
		
		nuovo->numero = 0;
		nuovo->next = NULL;

		if (*testa == NULL) {
			*testa = nuovo;
			p = *testa;
		} else {
			p->next = nuovo;
			p = p->next;	
		}
	}

}

void stampaseconda_lista( struct seconda_lista **testa ) {
	int i, val;
	struct seconda_lista *p;
	p = *testa;

	while (p->next != NULL) {
		printf("%d --> ", p->numero);
		p = p->next;
	}
	printf("%d \n\n", p->numero);
}

void stampaprima_lista( struct prima_lista **testa ) {
	int i, val;
	struct prima_lista *p;
	p = *testa;

	while (p->next != NULL) {
		printf("%d --> ", p->numero);
		p = p->next;
	}
	printf("%d \n\n", p->numero);
}

void append (struct prima_lista **testa) {
	int val = 0;
	struct prima_lista *p, *nuovo;

	p = *testa;

	while (p->next != NULL) {
		p = p->next;
	}

	printf("Inserisci il nuovo numero da inserire in coda alla prima_lista: ");
	scanf("%d", &val);

	nuovo = (struct prima_lista*) malloc ( sizeof (struct prima_lista));

	nuovo->numero = val;
	nuovo->next = NULL;

	p->next = nuovo;
	
}

void cancella (struct prima_lista **testa) {


	/* PROBLEMINO: SE CANCELLO
	IL PRIMO NUMERO, va in SEG FAULT */

	int val = 0;
	struct prima_lista *p, *precedente;

	p = *testa;
	precedente = p;

	printf("Inserisci il numero da cancellare: ");
	scanf("%d", &val);

	while (p != NULL) {
		if (p->numero != val) {
			precedente = p;
			p = p->next;
		} else {
			precedente->next = p->next;
			free(p);
			p = precedente->next;
		}
	}
}

int *crea_primo_array(int array[MAX]) {

	srand(time(NULL)); 
	int val, i;

	for (i=0; i<MAX; i++) {

		val = rand() % MAX;
		array[i] = val;
	}

	return array;

}

int *crea_secondo_array(int array[MAX]) {

	int val, i;

	srand(time(NULL)); 

	for (i=1; i<=MAX; i++) {

		val = rand() % i;
		if (i == 1) {
			val = 0;
			array[i-1] = val;
		}
		array[i] = val;
	}

	return array;

}

void stampa_primo_array(int array[MAX]) {

	int i;

	for (i=0; i<MAX; i++) {
		printf("[%d] %d\n", i+1, array[i]);
	}
}

void riempi_seconda_lista (struct seconda_lista **testa) {

	int i, j = 0, val = 0;
	struct seconda_lista *p, *nuovo;
	srand(time(NULL)); 

	p = *testa;

	for (i=1; i<=MAX; i++) {
		nuovo = (struct seconda_lista*) malloc (sizeof (struct seconda_lista));

		val = rand() % i;

		nuovo->numero = val;
		nuovo->next = NULL;

		if (i == 1) {
			val = 0;
		}

		if (*testa == NULL) {
			*testa = nuovo;
			p = *testa;
		} else {
			p->next = nuovo;
			p = p->next;	
		}
	}

}

int main() {

	struct prima_lista *testa, *nuovo;
	struct seconda_lista *testa2, *nuovo2;

	int array[MAX];
	int array2[MAX];

	testa = NULL;
	testa2 = NULL;

	printf("Questi sono la prima lista ed il primo array: \n\n");

	creaprima_lista (&testa);
	crea_primo_array(array);
	stampaprima_lista (&testa);
	stampa_primo_array(array);

	printf("\n\n\n\n");

	printf("Questi sono la seconda lista ed il secondo array: \n\n");

	creaseconda_lista (&testa2);
	crea_secondo_array(array2);
	riempi_seconda_lista(&testa2);
	stampaseconda_lista (&testa2);
	stampa_primo_array(array2);


	return 0;
}