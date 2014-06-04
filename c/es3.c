#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10       // 2^20
#define RANGE_RANDOM 10   // Range per i valori da inserire nelle liste e negli array

typedef struct lista lista;

struct lista {
	int numero;
	lista *next;
};

void inizializza_lista_sequenziale(lista **testa);
void inizializza_lista_casuale( lista **testa );
void accedi_lista_sequenziale(lista **testa);
void accedi_lista_casuale(lista **testa);
void stampa_lista( lista **testa );
void append (lista **testa);
void cancella (lista **testa);
int *crea_primo_array(int *array);
int *crea_secondo_array(int *array);
void stampa_array(int *array);

int main(void) {
	srand(time(NULL));

	lista *lista_sequenziale, *lista_casuale;

	int *array;
	int *array2;

	lista_sequenziale = NULL;
	lista_casuale = NULL;

	inizializza_lista_sequenziale(&lista_sequenziale);
        inizializza_lista_casuale(&lista_casuale);
	// array = crea_primo_array(array);
	// stampa_lista (&testa);
	//stampa_array(array);

        accedi_lista_sequenziale(&lista_sequenziale);
        accedi_lista_casuale(&lista_sequenziale);
	
        accedi_lista_sequenziale(&lista_casuale);
        accedi_lista_casuale(&lista_casuale);
	//array2 = crea_secondo_array(array2);
	//stampa_array(array2);


	return 0;
}

void inizializza_lista_sequenziale(lista **testa) {
    int i, val;
    // *p fornisce il puntatore per creare la lista
    // *nuovo è una variabile temporanea per inserire i valori
    lista *p, *nuovo; 

    for (i=0; i<MAX; i++) {
        nuovo = (lista *) malloc (sizeof (lista));

        val = rand() % RANGE_RANDOM;

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

void inizializza_lista_casuale( lista **testa ) {
    clock_t start = clock();

    int i,j = 0, val = 0, pos;
    lista *p, *nuovo;

    for (i=0; i<MAX; i++) {
        nuovo = (lista*) malloc (MAX * sizeof (lista));

        nuovo->numero = rand() % RANGE_RANDOM;
        nuovo->next = NULL;

        if (*testa == NULL) {
            *testa = nuovo;
            p = *testa;
        } else {
            j = 1;
            p = *testa;
            pos = rand() % i + 1;
            if (pos == 0) {
                nuovo->next = *testa;
                *testa = nuovo;
            } else {
                while (j<pos) {
                    p = p->next;
                    j++;
                }
                nuovo->next = p->next;
                p->next = nuovo;
            }
        }
    }

    int cpu_time_spent = clock() - start;
    printf("Time spent in creation of second list: %i\n", cpu_time_spent);
}

/**
 * La funzione prende in input un puntatore alla testa di una lista
 * e accede in maniera sequenziale ai valori, stampadoli uno per uno
 */
void accedi_lista_sequenziale(lista **testa) {
    lista *puntatore;
    puntatore = *testa;
    int totale = 0;     // Variabile in cui salvo la somma di tutti i valori a cui accedo

    printf("Stampa della lista in accesso sequenziale: \n");
    // Finché non arriviamo a un puntatore invalido, ne stampiamo il valore
    while (puntatore != NULL) {
        printf("%d ", puntatore->numero);
        totale += puntatore->numero;
        puntatore = puntatore->next;
    }

    printf("\nSomma totale dei valori a cui si è acceduto %d \n", totale);
}

/**
 * La funzione prende in input un puntatore alla testa di una lista
 * e accede a N valori della lista, dove N è il numero di elementi della lista
 * scegliendo a quali valori accedere in maniera completamente casuale
 */
void accedi_lista_casuale(lista **testa) {
    lista *puntatore;
    puntatore = *testa;
    int totale = 0;     // Variabile in cui salvo la somma di tutti i valori a cui accedo
    int i, pos, j;

    printf("Stampa della lista in accesso casuale: \n");

    // MAX rappresenta la grandezza massima della lista, noi accediamo a MAX
    // elementi della lista
    for (i = 0; i < MAX; i++) {
        // Decidiamo a che posizione accedere
        pos = rand() % MAX;

        // Resettiamo il contatore e riniziamo a scorrere dalla testa
        j = 0;
        puntatore = *testa;

        // Scorriamo la lista finché non arriviamo alla posizione che abbiamo
        // deciso
        while (j < pos) {
            puntatore = puntatore->next;
            j++;
        }

        printf("%d ", puntatore->numero);
        totale += puntatore->numero;
    }

    printf("\nSomma totale dei valori a cui si è acceduto %d \n", totale);
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

	int val, i, pos, num_el_corr = 1;


	array = (int *) malloc ( MAX * sizeof(int));


	while (num_el_corr <= MAX) {
		pos = rand() % num_el_corr;
		printf("-->%d\n", pos);
		if (pos != 0) {
			for (i = 0; i<pos; i++) {
				
			}
		}
		array[pos] = rand() % MAX;
		num_el_corr++;
	}

	return array;

}

void stampa_array(int *array) {

	int i;

	for (i=0; i<MAX; i++) {
		printf("[%d] %d\n", i+1, array[i]);
	}
}

