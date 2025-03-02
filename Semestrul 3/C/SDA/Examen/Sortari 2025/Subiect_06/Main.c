/*
	Se consideră un tablou de structuri de forma:


	Fiind dat tabloul cu dimensiunea N, se cere implementarea a câte o funcție pentru:

	a) Mutarea pe primele poziții din vector a echipelor cu punctaj mai mare decât 45 și, pe ultimele poziții, a celor cu punctaj mai mic 
	
	decât 20. Algoritmul va avea o complexitate de O(n) și nu va folosi un alt tablou auxiliar.

	b) Sortarea cât mai eficientă a echipelor cu un buget mai mare decât 100.000 (celelalte echipe nu vor fi sortate) descrescător în 

	funcție de punctaj.

	Se consideră un exemplu de tablou cu minimum 5 astfel de echipe și se va exemplifica cum va arăta tabloul după apelul fiecărei funcții.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

typedef struct {
	char nume[25];
	int puncte;
	int buget;
	char oras[25];
} Echipa_T;


void citireDateDinFisier(Echipa_T* echipe, FILE* fin) {
	for (int i = 0; i < N; i++) {
		fscanf(fin, "%s %d %d %s", echipe[i].nume, &echipe[i].puncte, &echipe[i].buget, echipe[i].oras);
	}
}

void afisareDate(Echipa_T* echipe) {
	for (int i = 0; i < N; i++) {
		printf("Nume: %s -> Puncte: %d -> Buget: %d -> Oras: %s\n",
			echipe[i].nume, echipe[i].puncte, echipe[i].buget, echipe[i].oras);
	}
	printf("---------------------------------\n");
}

void swap(Echipa_T* a, Echipa_T* b) {
	Echipa_T tmp = *a;
	*a = *b;
	*b = tmp;
}

void cerintaA_mutareEchipe(Echipa_T* echipe) {
	int inceput = 0;
	int sfarsit = N - 1;

	for (int i = 0; i <= sfarsit;) {
		if (echipe[i].puncte > 45) {
			if (i != inceput) {
				swap(&echipe[i], &echipe[inceput]);
			}
			inceput++;
			i++;
		}
		else if (echipe[i].puncte < 20) {
			if (i != sfarsit) {
				swap(&echipe[i], &echipe[sfarsit]);
			}
			sfarsit--;
			//i++;
		}
		else {
			i++;
		}
	}
}

void cerintaB_sortareEchipe(Echipa_T* echipe) {
	int i, j, min;

	for (i = 0; i < N - 1; i++) {
		if (echipe[i].buget > 100000) {
			min = i;
		}
		else {
			continue;
		}

		for (j = i + 1; j < N; j++) {
			if (echipe[j].buget > 100000 && echipe[j].puncte > echipe[min].puncte) {
				min = j;
			}
		}

		swap(&echipe[min], &echipe[i]);
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Nu s-au dat corect argumentele in linie de comanda \n");
		return 1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (fin == NULL) {
		printf("Eroare la deschiderea fisierului\n");
		return 2;
	}

	Echipa_T echipe[N];

	printf("Date initiale : \n");
	citireDateDinFisier(echipe, fin);
	afisareDate(echipe);

	cerintaA_mutareEchipe(echipe);
	printf("Date dupa cerinta A : \n");
	afisareDate(echipe);

	cerintaB_sortareEchipe(echipe);
	printf("Date dupa cerinta B : \n");
	afisareDate(echipe);

	fclose(fin);

	return 0;
}