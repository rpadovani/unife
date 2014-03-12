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
#include <string.h>

#define MAX_LENGTH_ARRAY 150

unsigned int string_to_int(char *string, unsigned int base);
void int_to_string(int integer, char *string, unsigned int base);
int opposite(int number);
int unit_test(void);
int string_to_int_test(char *string, int base, int result);
int int_to_string_test(int integer, unsigned int base, char *result);
int controllo_numero_base(char *numero, int base, int arrivo);
int controllo_input(char *numero);
void usage(void);

int debug = 0;																// Viene impostato a 1 se siamo in debug mode

int main(int argc, char *argv[]) {	
	char number_array[MAX_LENGTH_ARRAY]; 									// Array che verrà passato alla funzione int_to_string
	unsigned int result;													// Il risultato è dove verrà salvato il risultato di string_to_int

	if (argc == 2) {														// Se gli argomenti passati sono due 
		if (( strcmp(argv[1], "-unit") == 0)) {								// ed il secondo è '-unit'
			debug = 1;
			unit_test() == 0 ? printf("[+] Unit test Riuscito\n") : printf("[!] Unit test Fallito\n");  // Avvia gli unit test		
		} else {
			printf("[!] Argomento sconosciuto\n");							// se il secondo argomento non è '-unit'
			usage();														// richiama la funzione 'usage'
			return 1;
		}													
	} else if ( argc != 4) {												// se gli argomenti passati non sono due e non sono neanche 4
		usage();															// richiama la funzione 'usage'
	} else {

		char* numero_da_convertire = argv[1];
		char* base_di_partenza = argv[2];
		char* base_di_arrivo = argv[3];

		int partenza = string_to_int(base_di_partenza, 10);						// Base di partenza convertita in int per passarla alle funzioni
		int arrivo = string_to_int(base_di_arrivo, 10);							// Base di arrivo convertita in int per passarla alle funzioni

		if (controllo_numero_base(numero_da_convertire, partenza, arrivo) == 1) {
			if(controllo_input(numero_da_convertire) == 1) {

				if (arrivo == 10) {												// Se la base di arrivo è 10 usiamo string_to_int
					result = string_to_int(numero_da_convertire, partenza);
					printf("%i\n", result);										// Stampiamo a schermo il risultato
				}
				else {															// Se abbiamo un numero in base 10 da convertire a un'altra base usiamo int_to_string
					int convertire = string_to_int(numero_da_convertire, partenza); // Il numero da convertire deve essere un int per into_to_string
					int_to_string(convertire, number_array, arrivo);			// Non stampiamo il risultato perché viene stampato dalla funzione stessa
				}
			} else {
				printf("La stringa inserita contiene dei caratteri non ammessi\n\n");
				return 1;
			}
		} else if (controllo_numero_base(numero_da_convertire, partenza, arrivo) == -1)  {
			printf("Il numero inserito non può far parte della base %d\n\n", partenza);
			return 1;
		} else {
			printf("Il numero inserito non può essere convertito nella base %d\n", arrivo);
		}
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
				tmp = tmp * base;									// Formula di conversione di un numero da base x a numero matematico
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

void int_to_string(int integer, char *string, unsigned int base) {
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

	if (string[0] == '-' && debug == 0) {
		printf("-");
	}

	i--;															// Dobbiamo diminuire di una unità i perché viene aumentata una volta inserito l'ultimo carattere per come è costruito il while
	
	if (debug == 0) {												// Se non siamo in debug mode stampa i risultati
		while (i+1 != 0) {											// Partiamo dall'ultimo carattere inserito stampiamo la stringa
			if (string[i] != '-') {
				printf("%c", string[i]);
			}
			i--;
		}

		printf("\n");
	}
}

int opposite(int number) {
	return ~number + 1;												// Funzione per calcolare l'opposto con il NOT, aggiungiamo 1 come da formula
}


int controllo_numero_base(char *numero, int base, int arrivo) {
	int i, length = 0;

	while (numero[length] != '\0') {								// Calcolo la lunghezza della stringa 'numero' 
		length++;													
	}

 
	if (base > 0 && base < 63) {									// Entra nel ciclo solo se la base di partenza è positiva e minore di 63
		if (arrivo > 0 && arrivo < 63) {							// Entra nel ciclo solo se la base di arrivo è positiva e minore di 63
			if (base < 11) {									
				for (i=0; i < length; i++) {
					if (numero[i] - 48 >= base) {					// se la stringa contiene un numero maggiore o uguale alla base ( minore di 11 )
						return -1;									// fallisce uscendo dal ciclo di controllo
					}
				}
			}
			if (base > 10 && base < 36) {
				for (i=0; i< length; i++) {
					if (numero[i] - 55 >= base) {					// se la stringa contiene un numero ( o lettera ) maggiore o uguale alla base ( maggiore di 10 ma minore di 36 )
						return -1;									// fallisce uscendo dal ciclo di controllo
					}
				}
			}

			if (base > 36) {
				for (i=0; i< length; i++) {
					if (numero[i] - 61 >= base) {					// se la stringa contiene un numero ( o lettera ) maggiore o uguale alla base
						return -1;									// fallisce uscendo dal ciclo di controllo
					}
				}
			}
		} else {
			return -2;
		}

	} else {
		return -1;
	}

	return 1;
}

int controllo_input(char *numero) {

	int i, flag = 0, length = 0;

	while (numero[length] != '\0') {								// controllo la lunghezza della stringa
		length++;													
	}

	for (i=0; i<length; i++) {
		if (numero[i] > 42 && numero[i] < 44 ||						// se ogni numero/lettera della stringa fa parte dei caratteri consentiti
			numero[i] > 44 && numero[i] < 46 ||
			numero[i] > 46 && numero[i] < 58 || 					
			numero[i] > 64 && numero[i] < 91 || 
			numero[i] > 96 && numero[i] < 123) { 
					flag++;											// aumento la variabile 'flag' di uno
		}
	}

	if (flag == length) {											// se 'flag' è effettivamente uguale alla lunghezza della stringa
		return 1;													// vuol dire che tutti i numeri/lettere sono stati accettati dal controllo precedente
	} else {
		return -1;
	}

}

int unit_test(void) {
	if (string_to_int_test("456", 8, 302) 		!= 0 ||
		string_to_int_test("-456", 8, -302) 	!= 0 ||
		string_to_int_test("FA9", 16, 4009) 	!= 0 ||
		string_to_int_test("-FA9", 16, -4009) 	!= 0 ||
		string_to_int_test("1011", 2, 11) 		!= 0 ||
		string_to_int_test("-1011", 2, -11) 	!= 0 ||
		string_to_int_test("1011", 5, 131) 		!= 0 ||
		string_to_int_test("-1011", 5, -131) 	!= 0 ||
		string_to_int_test("22", 22, 46) 		!= 0 ||
		int_to_string_test(10, 2, "1010\0") 	!= 0 ||
		int_to_string_test(302, 8, "456\0") 	!= 0 ||
		int_to_string_test(-302, 8, "-456\0") 	!= 0 ||
		int_to_string_test(4009, 16, "FA9\0") 	!= 0 ||
		int_to_string_test(-4009, 16, "-FA9\0") != 0 ||
		int_to_string_test(11, 2, "1011\0") 	!= 0 ||
		int_to_string_test(-11, 2, "-1011\0") 	!= 0 ||
		int_to_string_test(131, 5, "1011\0") 	!= 0 ||
		int_to_string_test(-131, 5, "-1011\0") 	!= 0 ||
		int_to_string_test(46, 22, "22\0") 		!= 0  )
	{
		return -1;	// Se anche solo uno dei test fallisce restituiamo un fallimento nell'unit test
	}
	return 0;
}

int string_to_int_test(char *string, int base, int result) {
	if (string_to_int(string, base) != result)						// se il test non da i risultati esatti
	{
		printf("Test fallito, %s in base %d dovrebbe diventare %d in base 10, invece risulta %d\n", string, base, result, string_to_int(string, base));
		return -1;													// scrive un messaggio di errore ed esce dal ciclo
	}

	return 0;
}

int int_to_string_test(int integer, unsigned int base, char *result) {
	int length = 0, i, k;
	char number_array[MAX_LENGTH_ARRAY];

	int_to_string(integer, number_array, base);

	while (result[length] != '\0') {										// Calcolo la lunghezza della stringa
		length++;													
	}

	k = length - 1;											

	for (i = 0; i < length; ++i)
	{
		if (result[0] == '-' && number_array[length-i-1] != result[i+1] && number_array[length-i-1] != '-') { 	// se il numero è negativo ed il risultato della conversione è sbagliato
			printf("Test fallito, %i in base %i dovrebbe essere %s, invece risulta ", integer, base, result);	// stampo un messaggio di errore
			printf("-");
			while (k+1 != 0) {												// Partiamo dall'ultimo carattere inserito stampiamo la stringa
				if (number_array[k] != '-') {
					printf("%c", number_array[k]);
				}
				k--;
			}
			printf("\n");
			return -1;
		}
		else if (result[0] != '-' && number_array[length-i-1] != result[i]) {	// se il numero non è negativo ed il risultato della conversione è sbagliato
			printf("%c %c \n", number_array[length-i-1], result[i] );
			printf("Test fallito, %i in base %i dovrebbe essere %s, invece risulta ", integer, base, result);
			while (k+1 != 0) {												// Partiamo dall'ultimo carattere inserito stampiamo la stringa
				printf("%c", number_array[k]);
				k--;
			}
			printf("\n");
			return -1;
		}
	}

	return 0;
}

void usage() {
	printf("Errore.\nUsage:\t./script <numero> <base-di-partenza> <base-di-arrivo> ( per eseguire lo script normalmente )\n");
	printf("\t./script -unit ( per eseguire gli unit test )\n\n");
																	// semplice funzione che stampa un messaggio di errore se il programma non viene eseguito con i parametri giusti
}
