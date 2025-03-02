/*
Se consideră un tablou de structuri de forma:
				struct angajat {
					char nume[35];
					int salar;
					int bonus; // 1 dacă angajatul a primit un bonus, 0 dacă nu
				};

Fiind dat tabloul cu dimensiunea N, se cere implementarea a câte o funcție pentru:

a) Mutarea, într-un mod cât mai eficient, pe primele poziții din vector a angajaților care au primit bonus.

b) Sortarea în ordine inversă după salar, a angajaților care nu au primit bonus (doar aceștia vor fi sortați).

Se consideră un exemplu de tablou cu minimum 5 astfel de angajați și se va exemplifica cum va arăta tabloul după apelul fiecărei funcții.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

typedef struct angajat {
	char nume[35];
	int salar;
	int bonus; // 1 dacă angajatul a primit un bonus, 0 dacă nu
}Angajat_T;

void citireDateDinFisier(Angajat_T* angajati, FILE* fin) {
	// complexitate O(N)

	for (int i = 0; i < N; i++) {
		fscanf(fin, "%s", angajati[i].nume);
		fscanf(fin, "%d", &angajati[i].salar);
		fscanf(fin, "%d", &angajati[i].bonus);
	}
}

void afisareDate(Angajat_T* angajati) {
	// complexitate O(N)

	for (int i = 0; i < N; i++) {
		printf("Nume: %s, Salariu: %d, Bonus: %d\n", angajati[i].nume, angajati[i].salar, angajati[i].bonus);
	}

	printf("-----------------------------------------------------------------------------\n");	
}

int cerintaA_mutareAngajatiCuBonus(Angajat_T* angajati) {
	int index = 0;

	for (int i = 0; i < N; i++) {
		if (angajati[i].bonus == 1) {

			if (index != i) {
				Angajat_T tmp = angajati[i];

				angajati[i] = angajati[index];

				angajati[index] = tmp;
			}

			index++;
		}
	}

	return index;
}

void swap(Angajat_T* a, Angajat_T* b) {
	Angajat_T tmp = *a;
	*a = *b;
	*b = tmp;
}

void cerintaB_sortareAngajatiFaraBonus(Angajat_T* angajati, int prim, int ultim) {
	int stanga = prim + 1;
	int dreapta = ultim;

	swap(&angajati[prim], &angajati[(prim + ultim) / 2]);

	Angajat_T pivot = angajati[prim];

	while (stanga <= dreapta) {

		while (stanga <= ultim && angajati[stanga].salar > pivot.salar) {
			stanga++;
		}

		while (dreapta >= prim && angajati[dreapta].salar < pivot.salar) {
			dreapta--;
		}

		if (stanga < dreapta) {
			swap(&angajati[stanga], &angajati[dreapta]);
			stanga++;
			dreapta--;
		}
		else {
			stanga++;
		}
	}

	swap(&angajati[prim], &angajati[dreapta]);

	if (prim < dreapta - 1) {
		cerintaB_sortareAngajatiFaraBonus(angajati, prim, dreapta - 1);
	}

	if (dreapta + 1 < ultim) {
		cerintaB_sortareAngajatiFaraBonus(angajati, dreapta + 1, ultim);
	}

}


int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Nu ati introdus numele fisierului de intrare!\n");
		return 1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (fin == NULL) {
		printf("Fisierul nu a putut fi deschis!\n");
		return 1;
	}

	Angajat_T angajati[N];

	citireDateDinFisier(angajati, fin);

	printf("Datele citite din fisier sunt:\n");
	afisareDate(angajati);

	int index = cerintaA_mutareAngajatiCuBonus(angajati);

	printf("Cerinta A:\n");
	afisareDate(angajati);

	printf("Cerinta B:\n");

	cerintaB_sortareAngajatiFaraBonus(angajati, index, N - 1);

	afisareDate(angajati);

	fclose(fin);
	return 0;
}