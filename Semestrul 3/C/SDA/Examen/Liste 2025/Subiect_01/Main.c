/*
Se dă o listă simplu înlănțuită despre care se știe că are un număr impar de elemente. 

Nu se cunoaște numărul de elemente, dar se cunoaște că este impar.

Se cere să se proiecteze un algoritm care 

			găsește și șterge elementul din mijloc al acestei liste, 
			
			printr-o singură parcurgere a listei.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// cu pointeri

typedef int Element_t;

typedef struct nod {
	int cheie;
	Element_t info;
	struct nod* urm;
}Nod_t;

typedef Nod_t* Lista_t;

Lista_t primNod = NULL;
//Lista_t ultimNod = NULL; asta e la lista circulara

Lista_t insertNod_fata(int cheie, Element_t info) {

	Nod_t* nodNou = (Nod_t*)malloc(sizeof(Nod_t));
	
	if (nodNou) {
		// daca s-a alocat spatiu cu succes
		// ne cream nod
		nodNou->cheie = cheie;
		nodNou->info = info;

		// facem legatura catre inceputul listei
		// Lista noastra este in cazul de fata declarata global

		nodNou->urm = primNod;

		// daca avem lista circulara 
		/*
			if(primNod == NULL){
				ultimNod = nodNou;
			}
		*/

		//actualizam capul listei
		primNod = nodNou;
	}

	//returnam lista noastra
	return primNod;
}

void afiseazaLista(Lista_t lista) {
	while (lista) {
		printf("Cheie : % d, Info : %d \n", lista->cheie, lista->info);
		lista = lista->urm;
	}
}

Lista_t stergeNodMijloc(Lista_t lista) {
	if (lista == NULL) {
		printf("Lista este goala \n");
		return NULL;
	}

	if (lista->urm == NULL) {
		printf("eliminam singurul element \n");

		free(lista);
		lista = NULL;

		return NULL;
	}

	Lista_t nodUrmator = lista; // asta crestem cu 1
	Lista_t nodUrmator_Plus_2 = lista; // asta crestem cu 2
	Lista_t nodAnteriorCeluiDeSters = NULL;

	while (nodUrmator_Plus_2->urm != NULL) {
		nodAnteriorCeluiDeSters = nodUrmator;

		nodUrmator = nodUrmator->urm;
		nodUrmator_Plus_2 = nodUrmator_Plus_2->urm->urm;
	}

	if (nodAnteriorCeluiDeSters) {
		nodAnteriorCeluiDeSters->urm = nodUrmator->urm;

		free(nodUrmator);
	}

	return lista;
}

int main(void) {
	srand(time(NULL));

	Lista_t lista = NULL;

	int n = rand() % 10 + 3;

	if (n % 2 == 0) {
		n++;
	}

	for (int i = 0; i < n; i++) {
		lista = insertNod_fata(i, rand() % 100);
	}

	printf("Lista initiala : \n");

	afiseazaLista(lista);

	lista = stergeNodMijloc(lista);

	printf("Lista dupa stergere : \n");

	afiseazaLista(lista);

	return 0;
}

