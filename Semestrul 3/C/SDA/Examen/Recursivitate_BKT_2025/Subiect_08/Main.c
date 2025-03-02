/*
	Fie un sistem care generează numere de telefon.

	Să se implementeze structurile de date necesare și funcțiile valid și soluție pentru un algoritm de tip 
	
	backtracking care oferă următoarele soluții:

				Generează număr: Funcția afișează toate numerele de telefon de 10 cifre care:

						Încep cu 0799,

						Au ultima cifră 0,

						Nu au două cifre pare una lângă cealaltă.

Să se scrie cel puțin una dintre soluțiile problemei.
*/
#include <stdio.h>

#define MAX_CIFRE 10

int numar[MAX_CIFRE];


int acceptabil(int valoare, int k) {
	if (k < 5) {
		for (int i = 0; i < k; i++) {
			if (i == 0 && numar[i] != 0) {
				return 0;
			}

			if (i == 1 && numar[i] != 7) {
				return 0;
			}

			if ((i == 2 || i == 3) && numar[i] != 9) {
				return 0;
			}
		}
	}

	if (k > 0 && (numar[k - 1] % 2 == 0 && valoare % 2 == 0)) {
		return 0;
	}

	if (k == (MAX_CIFRE - 1) && valoare != 0) {
		return 0;
	}
	
	return 1;
}

int eSolutie(int k){
	return k == MAX_CIFRE;
}

void afiseazaSolutie() {
	for (int i = 0; i < MAX_CIFRE; i++) {
		printf("%d", numar[i]);
	}

	printf("\n");
}

void permuta(int k) {
	int i, aux;

	if (eSolutie(k)) {
		afiseazaSolutie();
	}
	else {
		for (int i = 0; i < MAX_CIFRE; i++) {
			aux = i;

			if (acceptabil(aux, k)) {
				numar[k] = i;
				permuta(k + 1);
			}
		}
	}
}

int main(void) {
	permuta(0);
	return 0;
}