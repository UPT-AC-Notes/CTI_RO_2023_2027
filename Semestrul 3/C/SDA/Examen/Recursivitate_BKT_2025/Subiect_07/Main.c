/*
Enunț:
	Se dau următoarele 6 culori: alb, galben, roșu, verde, albastru și negru.

	Să se implementeze structurile de date necesare și următoarele funcționalități:

		Construiți toate steagurile formate din 3 culori care îndeplinesc următoarele condiții:

			Orice steag trebuie să conțină culoarea verde sau culoarea galben la mijloc.

			Culorile din fiecare steag trebuie să fie distincte.

		Să se aleagă cel puțin 3 exemple de steaguri și să se reprezinte grafic.

Notă:

	Algoritmul poate fi scris în pseudocod (C-like).

	Este obligatorie comentarea algoritmului și specificarea complexității în termeni de

	O(f(n)), comentarea structurilor de date alese, precum și justificarea alegerii acestora.

	Este obligatorie exemplificarea efectului apelului funcțiilor implementate pe un exemplu ales.
*/

#include <stdio.h>

#define NR_STEAGURI 3

const char* culori[] = {"alb", "galben", "rosu", "verde", "albastru", "negru"};

#define NR_CULORI 6

char* steag[3];

int acceptabil(int pos, int k) {
	for (int i = 0; i < k; i++) {
		if (strcmp(steag[i], culori[pos]) == 0) {
			return 0;
		}
	}

	if (k == 1 && (strcmp(culori[pos], "galben") != 0) && (strcmp(culori[pos], "verde") != 0)) {
		return 0;
	}

	return 1;
}

int eSolutie(int k) {
	return k == NR_STEAGURI;
}

void afiseazaSolutie() {
	for (int i = 0; i < NR_STEAGURI; i++) {
		printf("%s\t", steag[i]);
	}

	printf("\n");
}

void permuta(int k) {
	int i;

	if (eSolutie(k)) {
		afiseazaSolutie();
	}
	else {
		for (int i = 0; i < NR_CULORI; i++) {
			if (acceptabil(i, k)) {
				steag[k] = culori[i];
				permuta(k + 1);
			}
		}
	}
}

int main(void) {
	permuta(0);
	return 0;
}