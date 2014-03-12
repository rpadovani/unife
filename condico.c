#include <stdio.h>
#include <string.h>

int join();

int main(int argc, char *argv[]) {

	if (join() == 1) {
		printf("L' unione dei file si è completata con successo...\n\n");
	}
	
	return 0;
}

int join() {

	FILE *fp_o;
	FILE *fp_l;
	char riga_online[200];
	char riga_locale[200];
	char lettera;
	char changes[100];
	char difference_message[] = "\nMODIFICA\n";
	int i = 1, j = 0 , t = 0, n_char = 0, pos_punt = 0;

	fp_o = fopen("file_online.tmp", "r");
	fp_l = fopen("file_locale.txt", "r");

	while (fgets(riga_online, sizeof(riga_online), fp_o) != NULL && fgets(riga_locale, sizeof(riga_locale), fp_l) != NULL ) {
		if (strcmp(riga_online, riga_locale) != 0) {
			changes[j] = i;
			j++;
		}
		i++;
	}
	fclose(fp_o);
	fclose(fp_l);
	

	for (i = 0; i < j; i++) {
		printf("[!] Some differences in line number %d\n", changes[i]);
	}

	i = 0;

	fp_l = fopen("file_locale.txt", "r");
	
	while (fgets(riga_locale, sizeof(riga_locale), fp_l) != NULL ) {
		i++;
		for ( t = 0; t < j; t++) {
			if (i == changes[t] - 1) {
				pos_punt = ftell(fp_l);
				fclose(fp_l);
				fp_l = fopen("file_locale.txt", "r+");
				fseek( fp_l, pos_punt, SEEK_SET );
				fprintf(fp_l,"%s", difference_message );
				fclose(fp_l);
				fp_l = fopen("file_locale.txt", "r");
				fseek( fp_l, pos_punt+sizeof(difference_message), SEEK_SET );
			}
		}
	}
	
	fclose(fp_l);
	
}

