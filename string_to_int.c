/*
 * Esercitazione numero 1
 *
 * Giovanni Bucci <giovanni01.bucci@student.unife.it>
 * Lorenzo Gardenghi <lorenzo.gardenghi@student.unife.it>
 * Riccardo Padovani <riccardo.padovani@student.unife.it>
 *
 */

#include <stdio.h>
#include <assert.h>

#define MAX_LENGTH_ARRAY 150

unsigned int string_to_int(char *string, unsigned int base);
void int_to_string(unsigned int integer, char *string, unsigned int base);
int opposite(int number);
int unit_test(void);

int main(int argc, char *argv[]) {
	char number_array[MAX_LENGTH_ARRAY]; 							// Array che verrà passato alla funzione int_to_string
	unsigned int result;											// Il risultato è dove verrà salvato il risultato di string_to_int

	char* numero_da_convertire = argv[1];
	char* base_di_partenza = argv[2];
	char* base_di_arrivo = argv[3];

	if (unit_test()) {
		printf("Unit test fallito. Uscita...\n");
		return 1;													// Se non passa tutti gli unit test usciamo 
	}

	int partenza = string_to_int(base_di_partenza, 10);				// Base di partenza convertita in int per passarla alle funzioni
	int arrivo = string_to_int(base_di_arrivo, 10);					// Base di arrivo convertita in int per passarla alle funzioni

	if (arrivo == 10) {												// Se la base di arrivo è 10 usiamo string_to_int
		result = string_to_int(numero_da_convertire, partenza);
		printf("%i\n", result);										// Stampiamo a schermo il risultato
	}
	else {															// Se abbiamo un numero in base 10 da convertire a un'altra base usiamo int_to_string
		int convertire = string_to_int(numero_da_convertire, partenza); // Il numero da convertire deve essere un int per into_to_string
		int_to_string(convertire, number_array, arrivo);			// Non stampiamo il risultato perché viene stampato dalla funzione stessa
	}

	return 0;														// Terminiamo il programma
} 

unsigned int string_to_int(char *string, unsigned int base) {
	int i, j, length = 0, tmp = 1, opposite_done = 0;				// opposite_done è una flag per controllare se il numero è negativo
	unsigned int result = 0;
	
	while (string[length] != '\0') {
		length++;													// Calcoliamo la lunghezza della stringa usando il suo terminatore
	}

	for (i = length - 1; i >= 0; i--) {								// Iniziamo a lavorare sula stringa
		if (i == 0 && (string[i] == '-' || string[i] == '+')) {		// Se c'è un più o un meno all'inizio della stringa lo ignoriamo
			if (string[i] == '-') {
				opposite_done = 1;									// Però se è un meno impostiamo la flag
			}
		}
		else {
			tmp = string[i] - 48;									// Per convertire il char di un numero in un int togliamo 48
			if (string[i] >= 65 && string[i] <= 90) {				// Lettere dalla A alla Z (maiuscole). Rappresentano nelle basi > 10 quello che in base 10 è da 10 a 36
				tmp -= 7;											// Oltre al 48 tolto prima vanno tolto altri 7 perché ci sono dei caratteri
			}
			else if (string[i] >= 97 && string[i] <= 122) {			// Lettere dalla a alla z (minuscole). Rappresentanto nella basei > 36 quello che in base 10 è da 37 a 62
				tmp -= 13;											// Oltre al 48 tolto prima  vanno tolti altri 13 perché ci sono dei caratteri che non ci interessano
			}
			for (j = 0; j < length-i-1; ++j) {
				tmp = tmp * base;									// Formula di conversione di un numero da base x a numero matematico (ulteriori spiegazioni nel file)
			} 
			result += tmp;
			tmp = 1;												// Reimpostiamo il tmp a 1;
		}
	}

	if (opposite_done == 1) {										// Se era un numero negativo di cui abbiamo calcolato il modulo...
		result = opposite(result);									// ... applichiamo la funziona opposite
	}

	return result;													// Ritorniamo il risultato
}

void int_to_string(unsigned int integer, char *string, unsigned int base) {
	int i = 0, tmp;
	if (integer < 0) {												// Se è un numero negativo...
		integer = opposite(integer);								// ... ne calcoliamo l'opposto
		string[i] = '-';											// ... il primo carattere della stringa è -
		i++;														// ... aumentiamo il contatore della posizione nella stringa perché il primo carattere della stringa è dedicato al -
	}

	while (integer != 0) {											// Formula di conversione di un numero a una base b
		tmp = integer % base;

		// Per passare da un int a un char dobbiamo aggiungere 48, ma lo facciamo dopo il controllo sul resto, in modo da verificare la base

		if (tmp >= 10 && tmp < 36) {								// Se il resto è maggiore di 10 ma minore di 36, la base è > 10, quindi dobbiamo usare le lettere maiuscole
			tmp += 7;												// ... quindi aggiungiamo 7
		} 
		else if (tmp >= 36) {										// ... ma se il resto è maggiore di 36, la base è > 36, quindi dobbiamo usare le lettere minuscole
			tmp += 13;												// ... quindi aggiungiamo 13
		}

		tmp += 48;													// Per passare da un int a un char dobbiamo aggiungere 48

		string[i] = tmp;											// Salviamo il char nella stringa
		integer /= base;

		i++;														// Aumentiamo il contatore per passare al carattere successivo della stringa
	}

	i--;															// Dobbiamo diminuire di una unità i perché viene aumentata una volta inserito l'ultimo carattere per come è costruito il while

	while (i+1 != 0) {												// Partiamo dall'ultimo carattere inserito stampiamo la stringa
		printf("%c", string[i]);
		i--;
	}

	printf("\n");
}

int opposite(int number) {
	return ~number + 1;												// Funzione per calcolare l'opposto con il NOT, aggiungiamo 1 come da formula
}

int unit_test(void) {
	char string[] = "456";
	if (string_to_int(string, 8) != 302) {
		printf("Test fallito, 456 in base 8 dovrebbe diventare 302 in base 10, invece risulta %i\n", string_to_int(string, 8));
		return -1;
	}

	char string1[] = "-456";
	if (string_to_int(string1, 8) != -302) {
		printf("Test fallito, -456 in base 8 dovrebbe diventare -302 in base 10, invece risulta %i\n", string_to_int(string1, 8));
		return -1;
	}

	char string2[] = "FA9";
	if (string_to_int(string2, 16) != 4009) {
		printf("Test fallito, FA9 in base 16 dovrebbe diventare 4009 in base 10, invece risulta %i\n", string_to_int(string2, 16));
		return -1;
	}

	char string3[] = "-FA9";
	if (string_to_int(string3, 16) != -4009) {
		printf("Test fallito, -FA9 in base 16 dovrebbe diventare -4009 in base 10, invece risulta %i\n", string_to_int(string3, 16));
		return -1;
	}

	char string4[] = "1011";
	if (string_to_int(string4, 2) != 11) {
		printf("Test fallito, 1011 in base 2 dovrebbe diventare 11 in base 10, invece risulta %i\n", string_to_int(string4, 2));
		return -1;
	}

	char string5[] = "-1011";
	if (string_to_int(string5, 2) != -11) {
		printf("Test fallito, -1011 in base 2 dovrebbe diventare -11 in base 10, invece risulta %i\n", string_to_int(string5, 2));
		return -1;
	}

	if (string_to_int(string4, 5) != 131) {
		printf("Test fallito, 1011 in base 5 dovrebbe diventare 131 in base 10, invece risulta %i\n", string_to_int(string4, 5));
		return -1;
	}

	if (string_to_int(string5, 5) != -131) {
		printf("Test fallito, -1011 in base 5 dovrebbe diventare -131 in base 10, invece risulta %i\n", string_to_int(string5, 5));
		return -1;
	}


	return 0;
}