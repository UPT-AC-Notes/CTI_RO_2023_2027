/*
	Fie o suprafață caroiată, reprezentată printr-o matrice pătratică de dimensiune n × m și 4 culori.

	Se cere să se implementeze structurile de date necesare și următoarele funcționalități:

	Colorează harta - Funcția propune un mod de colorare a suprafeței, folosind cele 4 culori astfel încât vecinii pe 
	
	diagonală ai unei celule să aibă culori diferite decât cea a celulei.


	Cerințe suplimentare:

		Să se aleagă un exemplu de suprafață de cel puțin 3×3 elemente.

		Să se reprezinte grafic suprafața după apelul funcției Colorează harta.


	Notă:

		Algoritmul poate fi scris în pseudocod sau în C.

		Este obligatorie comentarea algoritmului și justificarea complexității acestuia în termeni de O(f(n)).

		Trebuie justificată alegerea structurilor de date utilizate.

		Exemplificarea efectului funcțiilor implementate este obligatorie.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINII   2
#define MAX_COLOANE 3

#define NR_CULORI 4

void citesteDate(int matrice[][MAX_COLOANE]) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			matrice[i][j] = 0;
		}
	}
}

void afiseazaMatrice(int matrice[][MAX_COLOANE]) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}
}

int esteValid(int matrice[][MAX_COLOANE], int i, int j, int k) {

	if (i > 0 && j > 0 && matrice[i - 1][j - 1] == k) {
		return 0;
	}

	if (i > 0 && j < (MAX_COLOANE - 1) && matrice[i - 1][j + 1] == k) {
		return 0;
	}

	if (i < (MAX_LINII - 1) && j > 0 && matrice[i + 1][j - 1] == k) {
		return 0;
	}

	if (i < (MAX_LINII - 1) && j < (MAX_COLOANE - 1) && matrice[i + 1][j + 1] == k) {
		return 0;
	}

	return 1;
}

// asta va folosi doar 2 culori
void coloreazaHarta(int matrice[][MAX_COLOANE]) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			if ((i + j) % 2 == 0) {
				for (int k = 1; k <= NR_CULORI; k++) {
					matrice[i][j] = k;
					if (esteValid(matrice, i, j, k)) {
						break;
					}
				}
			}
			else {
				for (int k = NR_CULORI; k >= 1; k--) {
					matrice[i][j] = k;
					if (esteValid(matrice, i, j, k)) {
						break;
					}
				}
			}
			
		}
	}
}

int main(void) {
	int matrice[MAX_LINII][MAX_COLOANE];

	citesteDate(matrice);

	printf("Matrice initiala : \n");

	afiseazaMatrice(matrice);

	printf("\n---\n");

	coloreazaHarta(matrice);

	printf("\n Matrice dupa colorare \n");

	afiseazaMatrice(matrice);

	return 0;
}
