/*
			Prima problemă
	Se cere implementarea unei structuri de date care să permită gestionarea unor evenimente, 
	
	fiecare fiind caracterizat de un ID, un moment de activare și o prioritate(intre 1 si 8). Este necesar să:

			Se sorteze evenimentele după prioritate și moment de activare.

			Se utilizeze o coadă FIFO pentru a gestiona evenimentele cu prioritate egală.

			Să se afișeze rezultatele gestionării evenimentelor.

			Algoritmul trebuie să aibă complexitatea O(nlogn).
	

			A doua problemă

	Se cere implementarea unei funcții recursive pentru a parcurge și afișa o structură de date aleasă anterior.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P 8

typedef struct Eveniment {
	char id[10];
	int prioritate;
	long momentActivare;
	struct Eveniment* nextEveniment;
} Eveniment_t;

typedef struct LP {
	char prioritate[3];
	struct Eveniment* eveniment;
}LP_t;

typedef struct Multilist {
	LP_t listaPrincipala[P];	// putem face lista principala un vector, pt ca stim deja ca avem doar 8 prioritati
} Multilist_t;

typedef struct Coada {
	struct Eveniment* primEveniment;
	struct Eveniment* ultimEveniment;
} Coada_t;

Coada_t* initCoada() {
	Coada_t* coadaNoua = (Coada_t*)malloc(sizeof(Coada_t));

	if (coadaNoua == NULL) {
		printf("Eroare la alocarea memoriei pentru coada\n");
		return NULL;
	}

	coadaNoua->primEveniment = NULL;
	coadaNoua->ultimEveniment = NULL;

	return coadaNoua;
}

void enqueue(Coada_t *coada, Eveniment_t* ev) {
	if (coada->primEveniment == NULL) {
		coada->primEveniment = ev;
		coada->ultimEveniment = ev;
	}
	else {
		coada->ultimEveniment->nextEveniment = ev;
		coada->ultimEveniment = ev;
	}
}

Eveniment_t* initEveniment(char id[10], int prioritate, long momentActivare) {
	Eveniment_t* evNou = (Eveniment_t*)malloc(sizeof(Eveniment_t));

	if (evNou == NULL) {
		printf("Eroare la alocarea memoriei pentru evenimentul %s\n", id);
		return NULL;
	}

	strcpy(evNou->id, id);
	evNou->prioritate = prioritate;
	evNou->momentActivare = momentActivare;
	evNou->nextEveniment = NULL;

	return evNou;
}

Multilist_t initMultilist() {
	Multilist_t ml;

	for (int i = 0; i < P; i++) {
		sprintf(ml.listaPrincipala[i].prioritate, "P%d", i + 1);
		ml.listaPrincipala[i].eveniment = NULL;
	}

	return ml;
}

void printEveniment(LP_t* listaPrincipala) {
	Eveniment_t* evCurent = listaPrincipala->eveniment;

	while (evCurent != NULL) {
		printf("%s %ld, ", evCurent->id, evCurent->momentActivare);
		evCurent = evCurent->nextEveniment;
	}
}

void printCoada (Coada_t coada) {
	Eveniment_t* curent = coada.primEveniment;

	while (curent != NULL) {
		printf("FIFO - ");
		printf("%s %ld, ", curent->id, curent->momentActivare);
		curent = curent->nextEveniment;
	}

	putchar('\n');
}

void printMultilista(Multilist_t ml) {
	for (int i = 0; i < 8; i++) {
		printf("%s - ", ml.listaPrincipala[i].prioritate);

		if (ml.listaPrincipala[i].eveniment != NULL)
			printEveniment(&ml.listaPrincipala[i]);

		printf("\n");
	}
}

void adaugaEveniment(Multilist_t* ml, Eveniment_t* ev) {
	LP_t* lpCurent = &ml->listaPrincipala[ev->prioritate - 1];

	if (!lpCurent->eveniment) {
		lpCurent->eveniment = ev;
	}
	else if(!lpCurent->eveniment->nextEveniment){
		if (lpCurent->eveniment->momentActivare < ev->momentActivare) {
			lpCurent->eveniment->nextEveniment = ev;
		}
		else {
			ev->nextEveniment = lpCurent->eveniment;
			lpCurent->eveniment = ev;
		}
	}
	else {
		Eveniment_t* evCurent = lpCurent->eveniment;
		Eveniment_t* evAnterior = NULL;

		while (evCurent != NULL && evCurent->momentActivare < ev->momentActivare) {
			evAnterior = evCurent;
			evCurent = evCurent->nextEveniment;
		}

		evAnterior->nextEveniment = ev;
		ev->nextEveniment = evCurent;
	}
}


void deservesteEveniment(Multilist_t* ml, Coada_t *coada) {
	for (int i = P - 1; i >= 0; i--) {
		if (ml->listaPrincipala[i].eveniment != NULL) {
			Eveniment_t* evScos = ml->listaPrincipala[i].eveniment;
			ml->listaPrincipala[i].eveniment = ml->listaPrincipala[i].eveniment->nextEveniment; // am scos practic evenimentul din lista
			enqueue(coada, evScos);
			break;
		}
	}
}

// problema 2 -> functie recursiva de afisare a structurii de date

void afiseazaEvenimente(Eveniment_t* ev) {
	if (ev == NULL) {
		return;
	}

	printf("%s %ld, ", ev->id, ev->momentActivare);

	afiseazaEvenimente(ev->nextEveniment);
	//complexitate algoritmului este O(n) pentru ca avem n apeluri 
}


int main(int argc, char* argv[]) {
	Multilist_t ml = initMultilist();

	Eveniment_t* e1 = initEveniment("e1", 1, 100);

	Eveniment_t* e2 = initEveniment("e2", 2, 20);
	Eveniment_t* e3 = initEveniment("e3", 1, 30);
	Eveniment_t* e4 = initEveniment("e4", 4, 40);
	Eveniment_t* e7 = initEveniment("e7", 7, 700);



	adaugaEveniment(&ml, e1);
	adaugaEveniment(&ml, e2);
	adaugaEveniment(&ml, e3);
	adaugaEveniment(&ml, e4);
	adaugaEveniment(&ml, e7);

	printf("Initial: \n");
	printMultilista(ml);

	Coada_t* coada = initCoada();

	deservesteEveniment(&ml, coada);

	printf("Dupa scos\n");
	printMultilista(ml);
	printf("\n Coada :\n");
	printCoada(*coada);


	printf("AFISARE EVENIMENTE RECURSIV: \n");
	afiseazaEvenimente(e3);

	return 0;
}
