#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10000       // 2^20
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
int *inizializza_array_sequenziale(int *array);
int *inizializza_array_casuale(int *array);
void accedi_array_sequenziale(int *array);
void accedi_array_casuale(int *array);


int main(void) {
	srand(time(NULL));

	lista *lista_sequenziale, *lista_casuale;

	int *array_sequenziale;
	int *array_casuale;

	lista_sequenziale = NULL;
	lista_casuale = NULL;

	inizializza_lista_sequenziale(&lista_sequenziale);
    inizializza_lista_casuale(&lista_casuale);
	array_sequenziale = inizializza_array_sequenziale(array_sequenziale);
	array_casuale = inizializza_array_casuale(array_casuale);

    accedi_lista_sequenziale(&lista_sequenziale);
    accedi_lista_casuale(&lista_sequenziale);
    accedi_lista_sequenziale(&lista_casuale);
    accedi_lista_casuale(&lista_casuale);

	accedi_array_sequenziale(array_sequenziale);
    accedi_array_casuale(array_sequenziale);
	accedi_array_sequenziale(array_casuale);
    accedi_array_casuale(array_casuale);


	return 0;
}

void inizializza_lista_sequenziale(lista **testa) {
    clock_t start = clock();
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
    int cpu_time_spent = clock() - start;
    printf("Tempo impiegato per la creazione della lista sequenziale: %d\n", cpu_time_spent);
}

void inizializza_lista_casuale( lista **testa ) {
    clock_t start = clock();

    int i,j = 0, val = 0, pos;
    lista *p, *nuovo;

    for (i=0; i<MAX; i++) {
        nuovo = (lista*) malloc (MAX * sizeof (lista));

        nuovo->numero = rand() % RANGE_RANDOM;
        nuovo->next = NULL;

        if (*testa == NULL) {	        // se stiamo inserendo il primo numero
            *testa = nuovo;	        // testa è uguale al nuovo puntatore
            p = *testa;
        } 
        else {
            j = 1;              	// altrimenti utilizzo un contatore
            p = *testa;			// per scorrere la lista
            pos = rand() % i + 1;	// creo un numero tra 0 e il numero di elementi
            
            if (pos == 0) {		
                nuovo->next = *testa;	// inserisco il nuovo numero
                *testa = nuovo;		// in testa
            } 
            else {
                while (j<pos) {		// altrimenti scorro finchè non arrivo alla posizione ineressata
                    p = p->next;							
                    j++;		// incremento il contatore
                }
                nuovo->next = p->next;	// il nuovo numero punterà al successivo del vecchio numero
                p->next = nuovo;	// ed il vecchio numero punterà a quello numero
            }
        }
    }
    int cpu_time_spent = clock() - start;
    printf("Tempo impiegato per la creazione della lista casuale : %d\n", cpu_time_spent);
}

/**
 * La funzione prende in input un puntatore alla testa di una lista
 * e accede in maniera sequenziale ai valori, stampadoli uno per uno
 */
void accedi_lista_sequenziale(lista **testa) {
    clock_t start = clock();
    lista *puntatore;
    puntatore = *testa;
    int totale = 0;     // Variabile in cui salvo la somma di tutti i valori a cui accedo

    // Finché non arriviamo a un puntatore invalido, ne stampiamo il valore
    while (puntatore != NULL) {
        totale += puntatore->numero;
        puntatore = puntatore->next;
    }

    int cpu_time_spent = clock() - start;
    printf("Tempo impiegato per l'accesso sequenziale alla lista: %d\n", cpu_time_spent);
}

/**
 * La funzione prende in input un puntatore alla testa di una lista
 * e accede a N valori della lista, dove N è il numero di elementi della lista
 * scegliendo a quali valori accedere in maniera completamente casuale
 */
void accedi_lista_casuale(lista **testa) {
    clock_t start = clock();
    lista *puntatore;
    puntatore = *testa;
    int totale = 0;     // Variabile in cui salvo la somma di tutti i valori a cui accedo
    int i, pos, j;

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

        // Facciamo una piccola operazione per essere sicuri di evitare
        // un'eccessiva ottimizzazione da parte del compilatore
        totale += puntatore->numero;
    }

    // Stampiamo il tempo totale di accesso alla lista
    int cpu_time_spent = clock() - start;
    printf("Tempo impiegato per l'accesso casuale alla lista: %d\n", cpu_time_spent);
}

int *inizializza_array_sequenziale(int *array) {
    clock_t start = clock();
	int val, i;

	array = (int *) malloc ( MAX * sizeof(int));

	for (i=0; i<MAX; i++) {

		val = rand() % RANGE_RANDOM;
		array[i] = val;
	}

    int cpu_time_spent = clock() - start;
    printf("Tempo impiegato per l' inizializzazione dell' array in modo sequenziale: %i\n", cpu_time_spent);

	return array;

}

int *inizializza_array_casuale(int *array) {
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
    printf("Tempo impiegato per l' inizializzazione dell' array in modo casuale: %i\n", cpu_time_spent);

	return array;

}

void accedi_array_casuale( int *array ) {
    clock_t start = clock();
	int pos, somma = 0, i;

	for (i=0; i<MAX; i++) {
		pos = rand() % RANGE_RANDOM;
		pos += array[pos];
	}
    int cpu_time_spent = clock() - start;
    printf("Tempo impiegato per l' accesso all' array in modo casuale: %i\n", cpu_time_spent);
}

void accedi_array_sequenziale(int *array) {
    clock_t start = clock();
	int i, somma;

	for (i=0; i<MAX; i++) {
		somma += array[i];
	}
    int cpu_time_spent = clock() - start;
    printf("Tempo impiegato per l' accesso all' array in modo sequenziale: %i\n", cpu_time_spent);
}

