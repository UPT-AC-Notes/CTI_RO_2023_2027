/*
Fie un tablou de elemente ale căror valori sunt numere întregi, pozitive sau negative.
Să se aleagă și să se modifice unul din algoritmii de sortare studiați, astfel încât:

Valorile negative vor fi aduse la începutul tabloului (rezultatul va fi un tablou cu toate elementele negative la început 

și toate elementele pozitive la sfârșit).

Valorile pozitive vor fi sortate crescător.
Algoritmul modificat trebuie să fie cât mai eficient.

Se cere:

Motivați alegerea algoritmului.
Exemplificați funcționarea algoritmului pe un tablou de 6 elemente.
Notă:

Algoritmul poate fi scris în pseudocod (C-like).
Este obligatorie comentarea algoritmului și specificarea complexității acestuia în termeni de O(f(n)), comentarea structurilor 

de date alese, precum și justificarea alegerii acestora.

Este obligatorie exemplificarea efectului apelului funcțiilor implementate pe un exemplu ales.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	int *data;
	int size;
}Tablou_t;

// cea mai eficienta metoda de sortare ar fi QuickSort, deoarece are complexitatea O(n log n) in cazul mediu si O(n^2) in cazul
// cel mai defavorabil, dar in cazul nostru, QuickSort ar fi eficient deoarece avem de sortat doar numere intregi, pozitive si
// negative, fara alte conditii speciale. Astfel, QuickSort ar fi alegerea optima pentru a rezolva problema data.

// daca ar fi sa folosim MergeSort, ar fi mai ineficient deoarece MergeSort are complexitatea O(n log n) in cazul cel mai defavorabil
// si in cazul mediu, dar MergeSort are nevoie de un vector auxiliar pentru a sorta elementele, ceea ce ar face algoritmul mai ineficient
// decat QuickSort.

void swap(int* el1, int* el2)
{
	int tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}

void quicksort(Tablou_t tablou, int primElement, int ultimElement) { // O(n * log n) in cazul mediu si O(n^2) in cazul cel mai defavorabil
	int stanga = primElement + 1;
	int dreapta = ultimElement;

	// alegere pivot
	swap(&tablou.data[primElement], &tablou.data[(primElement + ultimElement) / 2]);

	//mutare pivot pe prima pozitie 
	int pivot = tablou.data[primElement];

	// ne ocupam de partitionare

	while (stanga <= dreapta) {	

		while (stanga <= ultimElement && tablou.data[stanga] < pivot) {  //ordoneaza crescator,
			stanga++;
		}

		while (dreapta >= primElement && pivot < tablou.data[dreapta]) { // ordoneaza crescator
			dreapta--;
		}

		if (stanga < dreapta) {
			swap(&tablou.data[stanga++], &tablou.data[dreapta--]);
		}
		else {
			stanga++;
		}
	}

	//mutam pivot la locul lui sau la final
	swap(&tablou.data[dreapta], &tablou.data[primElement]);

	//apeluri recursive
	if (primElement < dreapta - 1) {
		quicksort(tablou, primElement, dreapta - 1); 
	}

	if (dreapta + 1 < ultimElement) {
		quicksort(tablou, dreapta + 1, ultimElement);
	}
}

int separareValoriNegativeDePozitive(Tablou_t tablou) {
	int index = 0;

	// avem o functie de sortare valori negative(in prima parte a vectorului
	// si valori pozitive(in a doua parte a vectorului) si returnam indexul de unde incepe partea a doua a vectorului
	// pentru a apela quicksort pe acea parte a vectorului
	// O(n) -> n - dimensiunea tabloului
	for (int i = 0; i < tablou.size; i++) { 
		if (tablou.data[i] < 0) {
			if (i != index) {
				swap(&tablou.data[i], &tablou.data[index]);
			}
			index++;
		}
	}

	return index;
}

void printTablou(Tablou_t tablou) {
	for (int i = 0; i < tablou.size; i++) {
		printf("%d ", tablou.data[i]);
	}
	printf("\n");
}


int main(void) {
	srand(time(NULL));

	Tablou_t tablou;
	
	tablou.size = rand() % 20; // 6 elemente

	tablou.data = (int*)malloc(tablou.size * sizeof(int));

	for (int i = 0; i < tablou.size; i++) {
		tablou.data[i] = rand() % 100 - 50;
	}

	printf("Tabloul initial: \n");
	printTablou(tablou);

	printf("--------------------\n");

	int index = separareValoriNegativeDePozitive(tablou);

	printf("Tabloul dupa separare: \n");
	printTablou(tablou);

	printf("--------------------\n");

	printf("Tabloul dupa sortare: \n");
	quicksort(tablou, index, tablou.size - 1);

	printTablou(tablou);

	printf("--------------------\n");

	free(tablou.data);

	return 0;
}