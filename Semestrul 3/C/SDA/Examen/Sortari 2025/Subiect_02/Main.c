/*
Se consideră un tablou de structuri de forma:
	            struct agenda {
                    char nume[25];
                    char telefon[10];
                    int an;
                    int venit;
                };

Fiind dat tabloul cu dimensiunea N, se cere implementarea a câte o funcție pentru:

a) Mutarea pe ultimele poziții din vector a primelor două persoane cu un venit mai mic de 1000.

b) Sortarea eficientă, în ordine alfabetică a numelor, a persoanelor cu vârsta între 30 și 40 de ani.

Notă: Se consideră un exemplu de tablou cu minimum 5 astfel de structuri și se va exemplifica cum va arăta tabloul după 

apelul fiecărei funcții.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

typedef struct agenda {
	char nume[25];
	char telefon[10];
	int an;
	int venit;
}Agenda_t;

void citesteDateFisier(Agenda_t *agende, FILE *fin) {
	for (int i = 0; i < N; i++) {
		fscanf(fin, "%s", agende[i].nume);
		fscanf(fin, "%s", agende[i].telefon);
		fscanf(fin, "%d", &agende[i].an);
		fscanf(fin, "%d", &agende[i].venit);
	}
}

void afiseazaDateAgende(Agenda_t* agende) {
	for (int i = 0; i < N; i++) {
		printf("Nume : % s - Telefon %s - An %d - Venit %d\n", agende[i].nume, agende[i].telefon, agende[i].an, agende[i].venit);
	}

	printf("---------------------------------------------------------------\n");
}

void cerintaA_mutaPersoane(Agenda_t* agende) {
	int nrPersoaneMutate = 2;

	for (int i = 0; i < N && nrPersoaneMutate > 0; i++) {
		if (agende[i].venit < 1000) {
			// aici facem swap 
			Agenda_t tmp = agende[i];

			if (nrPersoaneMutate == 2) {
				agende[i] = agende[N - 1];
				agende[N - 1] = tmp;
			}
			else {
				agende[i] = agende[N - 2];
				agende[N - 2] = tmp;
			}

			nrPersoaneMutate--;
		}
	}
}

void swap(Agenda_t* a, Agenda_t* b) {
	Agenda_t tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
	pt dimensiuni mici ale lui N, folosirea Selection sort se dovedeste a fi eficienta
	complexitatea algoritmului este O(n^2)

	Intr-adevar pentru dimensiuni mari ale lui N, ar fi mai eficient sa folosim un algoritm de sortare mai eficient
	precum QuickSort, MergeSort, dar pentru dimensiuni mici, Selection sort este suficient de eficient
*/

//void cerintaB_sortareNume(Agenda_t* agende) {
//	int i, j, min;
//
//	for (i = 0; i < N - 1; i++) {
//		if (agende[i].an >= 30 && agende[i].an <= 40) {
//			min = i;
//		}
//		else {
//			continue;
//		}
//
//		for (j = i + 1; j < N; j++) {
//			if (agende[j].an >= 30 && agende[j].an <= 40) {
//				if (strcmp(agende[j].nume, agende[min].nume) < 0) {
//					min = j;
//				}
//			}
//		}
//
//		swap(&agende[i], &agende[min]);
//	}
//}

/*
void mergesort(tip_element A[], tip_element temp[], int left, int right) {
	if (left == right) return; // secventa de un element

	int mid = (left + right) / 2;

	mergesort(A, temp, left, mid);
	mergesort(A, temp, mid + 1, right);

	for (int i = left; i <= right; i++) temp[i] = A[i]; // se copiaza secventa in temp

	int i1 = left; int i2 = mid + 1; // interclasare inapoi in A

	for (int index = left; index <= right; index++) {
		if (i1 == mid + 1) A[index] = temp[i2++];  // s-a epuizat secventa din stanga
		else if (i2 > right) A[index] = temp[i1++]; // s-a epuizat secventa din dreapta
		else if (temp[i1].cheie < temp[i2].cheie) A[index] = temp[i1++];
		else A[index] = temp[i2++];
	}
}
*/

void quicksort(Agenda_t a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	Agenda_t pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && (strcmp(a[stanga].nume, pivot.nume) < 0))
			stanga++;
		while (dreapta >= prim && (strcmp(a[dreapta].nume, pivot.nume) > 0))
			dreapta--;
		if (stanga < dreapta)
			swap(&a[stanga++], &a[dreapta--]);
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
		quicksort(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);
}

void sortare(Agenda_t a[]) {
	int newSize = 0;
	Agenda_t eligibili[N];
	int indecsi[N];

	//O(N) pentru selectarea persoanelor eligibile
	for (int i = 0; i < N; i++) {
		if (a[i].an >= 30 && a[i].an <= 40) {
			eligibili[newSize] = a[i];
			indecsi[newSize] = i;
			newSize++;
		}
	}

	//O(n * logn) pentru sortarea persoanelor eligibile

	quicksort(eligibili, 0, newSize - 1);

	for (int i = 0; i < newSize; i++) {
		a[indecsi[i]] = eligibili[i];
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Numar insuficient de argumente");
		exit(1);
	}

	Agenda_t agende[N];

	FILE* fin = fopen(argv[1], "r");

	if (fin == NULL) {
		printf("Fisierul nu a putut fi deschis");
		exit(1);
	}

	citesteDateFisier(agende, fin);

	printf("Date initiale\n");
	afiseazaDateAgende(agende);

	printf("Cerinta A : \n");
	cerintaA_mutaPersoane(agende);
	afiseazaDateAgende(agende);

	printf("Cerinta B : \n");
	//cerintaB_sortareNume(agende);
	sortare(agende);
	afiseazaDateAgende(agende);

	return 0;
}