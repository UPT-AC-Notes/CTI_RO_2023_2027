/*
Enunț:
	Fie un sistem care generează numere binare.

	Să se implementeze structurile de date necesare și funcțiile valid și soluție pentru un algoritm de tip 
	
	backtracking care oferă următoarele soluții:

	Generează număr binar: Funcția afișează toate numerele binare de 6 cifre care au:

	exact 2 cifre de '0',
	exact 4 cifre de '1'.

Suplimentar:

	Numerele nu trebuie să înceapă cu două cifre de '1'.
	Numerele nu trebuie să se termine cu cifra '0'.
	

	Să se scrie cel puțin trei dintre soluțiile problemei.

*/

#include <stdio.h>

#define MAX_CIFRE 6

int numar[MAX_CIFRE];
int pos[] = { 0, 1 };

int acceptabil(int pos, int k) {
	int nr_zero = 0;
	int nr_unu = 0;

	for (int i = 0; i < k; i++) {
		if (numar[i] == 0) {
			nr_zero++;
		}
		if (numar[i] == 1) {
			nr_unu++;
		}
		if (i == 1 && nr_unu == 2) {
			return 0;
		}
	}

	if (pos == 0 && k == (MAX_CIFRE - 1)) {
		return 0;
	}

	if (pos == 0 && nr_zero < 2) {
		return 1;
	}

	if (pos == 1 && nr_unu < 4) {
		return 1;
	}


	return 0;
}


int eSolutie(int k) {
	return k == MAX_CIFRE;
}

int solutiiAfisate = 0;

void afiseazaSolutie() {
	for (int i = 0; i < MAX_CIFRE; i++) {
		printf("%d", numar[i]);
	}

	printf("\n");

	solutiiAfisate++;
}

void permuta(int k) {
	int i;
	int aux;

	if (eSolutie(k)) {
		afiseazaSolutie();
	}
	else {
		for (int i = 0; i < 2; i++) {
			aux = pos[i];
			if (acceptabil(aux, k)) {
				numar[k] = pos[i];
				permuta(k + 1);
			}
		}
	}
}

int main(void) {
	permuta(0);

	printf("\n Solutii: %d", solutiiAfisate);
	return 0;
}