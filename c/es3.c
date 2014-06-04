#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10       	// 2^20
#define RANGE_RANDOM 10   // Range per i valori da inserire nelle liste e negli array

typedef struct lista lista;

struct lista {
	int numero;
	lista *next;
};

void inizializza_lista_fondo(lista **testa);
void crea_seconda_lista( lista **testa );
void stampa_lista( lista **testa );
void append (lista **testa);
void cancella (lista **testa);
int *crea_primo_array(int *array);
int *crea_secondo_array(int *array);
void stampa_array(int *array);

int main(void) {

	srand(time(NULL));

	lista *testa,*testa2, *nuovo;				// creo i puntatori necessari alla lista

	int *array;									// creo i puntatori ad array
	int *array2;

	testa = NULL;								// inizializzo le testa
	testa2 = NULL;

	printf("Questi sono la prima lista ed il primo array: \n\n");

	inizializza_lista_fondo (&testa);
	array = crea_primo_array(array);
	stampa_lista (&testa);
	stampa_array(array);

	printf("\n\n\n\n");

	printf("Questi sono la seconda lista ed il secondo array: \n\n");

	crea_seconda_lista (&testa2);
	stampa_lista(&testa2);
	array2 = crea_secondo_array(array2);
	stampa_array(array2);


	return 0;
}

void inizializza_lista_fondo(lista **testa) {
    int i, val;
    // *p fornisce il puntatore per creare la lista
    // *nuovo è una variabile temporanea per inserire i valori
    lista *p, *nuovo; 

    for (i=0; i<MAX; i++) {
        nuovo = (lista *) malloc (sizeof (lista));		// alloco il nuovo puntatore

        val = rand() % RANGE_RANDOM;					// creo un valore random compreso tra
        												// 0 e RANGE_RANDOM
        nuovo->numero = val;							// assegno a nuovo il numero val
        nuovo->next = NULL;								// il puntatore al successivo è NULL

        if (*testa == NULL) {
            *testa = nuovo;		
            p = *testa;
        } else {
            p->next = nuovo;
            p = p->next;
        }
    }
}

void crea_seconda_lista( lista **testa ) {
    clock_t start = clock();

    int i,j = 0, val = 0, pos;
    lista *p, *nuovo;

    for (i=0; i<MAX; i++) {
        nuovo = (lista*) malloc (MAX * sizeof (lista));

        nuovo->numero = rand() % RANGE_RANDOM;
        nuovo->next = NULL;

        if (*testa == NULL) {								// se stiamo inserendo il primo numero
            *testa = nuovo;									// testa è uguale al nuovo puntatore
            p = *testa;
        } else {
            j = 1;											// altrimenti utilizzo un contatore
            p = *testa;										// per scorrere la lista
            pos = rand() % i + 1;							// creo un numero tra 0 e il numero di elementi
            if (pos == 0) {									// se pos == 0
                nuovo->next = *testa;						// inserisco il nuovo numero
                *testa = nuovo;								// in testa
            } else {
                while (j<pos) {								// altrimenti scorro finchè non arrivo alla posizione ineressata
                    p = p->next;							
                    j++;									// incremento il contatore
                }
                nuovo->next = p->next;						// il nuovo numero punterà al successivo del vecchio numero
                p->next = nuovo;							// ed il vecchio numero punterà a quello numero
            }
        }
    }
    int cpu_time_spent = clock() - start;
    printf("Time spent in creation of second list: %i\n", cpu_time_spent);

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

int *crea_primo_array(int *array) {
 
	int val, i;

	array = (int *) malloc ( MAX * sizeof(int));

	for (i=0; i<MAX; i++) {

		val = rand() % RANGE_RANDOM;
		array[i] = val;
	}

	return array;

}

int *crea_secondo_array(int *array) {
	clock_t start = clock();
	int i, pos, num_el_corr = 1;

	array = (int *) malloc ( MAX * sizeof(int));

	while (num_el_corr <= MAX) {		// finchè non ho riempito tutto l'array
		pos = rand() % num_el_corr;		// creo un numero random compreso tra 0 ed il numero di elementi già inseiri
		if (pos!=num_el_corr) {			// se la posizione random è diversa dall' ultimo elemento
			for (i=num_el_corr; i>=pos; i--) {	
				array[i+1] = array[i];	// sposto tutti gli elementi successivi alla posizione
			}							// creando spazion per il nuovo elemento
		}
		array[pos] = rand() % MAX;		// scrivo in array[pos] il numero tra 0 e la dimensione MAX
		num_el_corr++;					// aumento il contatore di numeri inseriti fin'ora
	}

	int cpu_time_spent = clock() - start;
    printf("Time spent in creation of second array: %i\n", cpu_time_spent);

	return array;

}

void stampa_array(int *array) {

	int i;

	for (i=0; i<MAX; i++) {
		printf("[%d] %d\n", i+1, array[i]);
	}
}

