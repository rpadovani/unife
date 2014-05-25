#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1048576         // 2^20
#define RANGE_RANDOM 1000   // Range per i valori da inserire nelle liste e negli array

typedef struct lista lista;

struct lista {
	int numero;
	lista *next;
};

void inizializza_lista_fondo(lista *testa);



void crea_seconda_lista( lista **testa ) {
	int i, val = 0;
	lista *p, *nuovo;
	srand(time(NULL)); 

	for (i=0; i<MAX; i++) {
		nuovo = (lista*) malloc (sizeof (lista));
		
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


void stampa_lista( lista **testa ) {
	int i, val;
	lista *p;
	p = *testa;

	while (p->next != NULL) {
		printf("%d --> ", p->numero);
		p = p->next;
	}
	printf("%d \n\n", p->numero);
}

void append (lista **testa) {
	int val = 0;
	lista *p, *nuovo;

	p = *testa;

	while (p->next != NULL) {
		p = p->next;
	}

	printf("Inserisci il nuovo numero da inserire in coda alla prima_lista: ");
	scanf("%d", &val);

	nuovo = (lista*) malloc ( sizeof (lista));

	nuovo->numero = val;
	nuovo->next = NULL;

	p->next = nuovo;
	
}

void cancella (lista **testa) {


	/* PROBLEMINO: SE CANCELLO
	IL PRIMO NUMERO, va in SEG FAULT */

	int val = 0;
	struct lista *p, *precedente;

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

		val = rand() % RANGE_RANDOM;
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

void riempi_seconda_lista (lista **testa) {

	int i, j = 0, val = 0;
	lista *p, *nuovo;
	srand(time(NULL)); 

	p = *testa;

	for (i=1; i<=MAX; i++) {
		nuovo = (lista*) malloc (sizeof (lista));

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

int main(void) {

	lista *testa,*testa2, *nuovo;

	int array[MAX];
	int array2[MAX];

	testa = NULL;
	testa2 = NULL;

	printf("Questi sono la prima lista ed il primo array: \n\n");

	inizializza_lista_fondo (testa);
	crea_primo_array(array);
	stampa_lista (&testa);
	stampa_primo_array(array);

	printf("\n\n\n\n");

	printf("Questi sono la seconda lista ed il secondo array: \n\n");

	crea_seconda_lista (&testa2);
	crea_secondo_array(array2);
	riempi_seconda_lista(&testa2);
	stampa_lista (&testa2);
	stampa_primo_array(array2);


	return 0;
}

void inizializza_lista_fondo(lista *testa) {
    int i, val;
    // *p fornisce il puntatore per creare la lista
    // *nuovo è una variabile temporanea per inserire i valori
    lista *p, *nuovo;
    srand(time(NULL)); 

    for (i=0; i<MAX; i++) {
        nuovo = (lista *) malloc (sizeof (lista));

        val = rand() % RANGE_RANDOM;

        nuovo->numero = val;
        nuovo->next = NULL;

        if (testa == NULL) {
            testa = nuovo;
            p = testa;
        } else {
            p->next = nuovo;
            p = p->next;
        }
    }
}
