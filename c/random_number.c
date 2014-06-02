#include <stdio.h>
#include <time.h>

int main(void) {
	int i;
	srand ( time(NULL) );
	
	for (i=0;i<10;i++) {
		printf("%i\n", rand() % 100);
	}
}
