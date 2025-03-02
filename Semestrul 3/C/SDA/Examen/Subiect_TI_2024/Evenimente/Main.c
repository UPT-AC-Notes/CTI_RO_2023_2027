/*
	Fie un sistem capabil să deservească doar un eveniment la un moment dat. 
	
	Se consideră n evenimente, caracterizate printr-un ID, momentul de start și momentul de finalizare. 
	
	Momentele de timp sunt considerate ca având valori întregi (ex. momentele: 1, 2, ..., 200).

	Se cere să se implementeze structurile de date necesare și următoarele funcționalități:

		Să se aleagă un criteriu relevant pentru a sorta evenimentele.

		Să se sorteze aceste evenimente, astfel încât:

				să se determine o planificare care să includă cât mai multe evenimente posibile.


	Pentru sortarea evenimentelor se va lua în considerare faptul că algoritmul va rula pe un sistem încorporat care:

					nu permite execuția de funcții recursive,
					nu trebuie să aibă complexitatea mai mare sau egală cu O(n²).

	Exemplu: Pentru cazul de mai jos, prima planificare este soluția, deoarece include 2 evenimente.


	n = 3
	ID1 0 5
	ID2 3 11
	ID3 6 10
	Răspuns: ID1, ID3

	n = 3
	ID1 0 5
	ID2 6 9
	ID3 4 10
	Răspuns: ID1, ID2


*/

#include <stdio.h>
#include <stdlib.h>


typedef struct Eveniment {
	char id[5];
	int momentStart;				// 1, 2, 200 etc
	int momentFinalizare;
}Eveniment_t;



/*
				void deplasare(tip_element a[], int stanga, int dreapta)
				{
					int fiu = 2 * stanga + 1;
					while (fiu <= dreapta)
					{
						if (fiu < dreapta && a[fiu].cheie < a[fiu + 1].cheie)
							//daca al doilea fiu are cheia cea mai mare
							fiu++;								//retinem al doilea fiu
						if (a[stanga].cheie < a[fiu].cheie)  //daca este necesar
						{										 //schimba parinte cu fiu
							swap(&a[stanga], &a[fiu]);			 //si deplaseaza in jos
							stanga = fiu;
							fiu = 2 * stanga + 1;
						}
						else
							fiu = dreapta + 1;
					}
				}
*/

void swap(Eveniment_t* a, Eveniment_t* b) {
	Eveniment_t tmp = *a;
	*a = *b;
	*b = tmp;
}

int cmpFinalizare(Eveniment_t* a, Eveniment_t* b) {
	return a->momentFinalizare < b->momentFinalizare;
}

void deplasare(Eveniment_t a[], int stanga, int dreapta) {
	int fiu = 2 * stanga + 1;

	while (fiu <= dreapta) {
		if (fiu < dreapta && cmpFinalizare(&a[fiu], &a[fiu + 1])) {
			fiu++;
		} // retinem al doilea fiu

		if (cmpFinalizare(&a[stanga], &a[fiu])) {
			swap(&a[stanga], &a[fiu]);
			stanga = fiu;
			fiu = 2 * stanga + 1;
		}
		else {
			fiu = dreapta + 1;
		}
	}
}

void heapsort(Eveniment_t a[], int n)
{
	int i;
	//algoritmul lui Floyd 
	for (i = n / 2 - 1; i >= 0; i--) //se creaza ansamblul
		deplasare(a, i, n - 1);
	//extragerea maximului si refacerea ansamblului
	for (i = n - 1; i >= 1; i--)
	{
		swap(&a[0], &a[i]);			//mutare element maxim pe pozitia a[i]
		deplasare(a, 0, i - 1);		//se reface proprietatea de ansamblu
	}
}

void afiseazaEveniment(Eveniment_t ev) {
	printf("ID : %s \t Moment start : %d \t Moment finalizare: %d\n", ev.id, ev.momentStart, ev.momentFinalizare);
}

void afiseazaEvenimente(Eveniment_t a[], int n) {
	printf("\n-------------afisare -> start-----------\n");

	for (int i = 0; i < n; i++) {
		afiseazaEveniment(a[i]);
	}

	printf("\n-------------afisare -> done-----------\n\n");
}

void citesteEvenimente(Eveniment_t a[], int *n, FILE *fin) {
	fscanf(fin, "%d", n);
	
	for (int i = 0; i < *n; i++) {
		fscanf(fin, "%s %d %d", a[i].id, &a[i].momentStart, &a[i].momentFinalizare);
		
	}
}

void planificaEvenimente(Eveniment_t a[], int n) {
	printf("\nPlanificare maxima : \n\n");

	printf("%s", a[0].id);

	int ultimMomentFinalizare = a[0].momentFinalizare;

	for (int i = 1; i < n; i++) {
		if (a[i].momentStart >= ultimMomentFinalizare) {
			printf(", %s", a[i].id);
			ultimMomentFinalizare = a[i].momentFinalizare;
		}
	}

	printf("\n");
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("eroare argumente\n");
		return -1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (fin == NULL) {
		printf("eroare deschidere fisier\n");
		return -2;
	}

	Eveniment_t a[10];

	int n = 0;;

	citesteEvenimente(a, &n, fin);

	printf("Evenimente initiale \n");
	afiseazaEvenimente(a, n);

	printf("Evenimente dupa sortare \n");
	heapsort(a, n);
	afiseazaEvenimente(a, n);

	planificaEvenimente(a, n);

	fclose(fin);

	return 0;
}