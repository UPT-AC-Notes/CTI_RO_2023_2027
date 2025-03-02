/*
		Fie un sistem de gestionare a unor produse într-un lanț de magazine. 
		
		Magazinul este caracterizat printr-un nume unic, iar produsele printr-un cod numeric (maxim 8 cifre).

		Se cere să se implementeze o structură multilistă adecvată pentru gestionarea acestor magazine. 
		
		Structura va avea următoarele componente:

				Fiecare magazin reprezintă o intrare separată într-o listă principală statică (număr fix de magazine).

				Fiecare magazin conține o listă secundară dinamică, ordonată după codul produselor;

				Adăugarea unui produs într-un magazin, menținând lista secundară ordonată.
				
				Eliminare produs:

				Ștergerea unui produs identificat după cod din toate magazinele.

			//ps e adaptare asta ca sa fac si celalalt tip de multilista
			// ca enuntul principal, aveti ca model primele 2 subiecte
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAGAZINE 3

typedef struct Produs{
	int cod;
	struct Produs* nextProdus;
}Produs_t;

typedef struct Magazin {
	char nume[35];
	Produs_t* listaProduse;
}Magazin_t;

typedef struct Multilista{
	Magazin_t magazine[MAX_MAGAZINE];
	int nrCurentMagazine;
}Multilista_t;

Produs_t* initProdus(int cod) {
	Produs_t* produsNou = (Produs_t*)malloc(sizeof(Produs_t));

	if (!produsNou) {
		printf("eroare alocare memorie\n");
		return NULL;
	}

	produsNou->cod = cod;
	produsNou->nextProdus = NULL;

	return produsNou;
}

Magazin_t* initMagazin(const char nume[]) {
	Magazin_t* magazinNou = (Magazin_t*)malloc(sizeof(Magazin_t));

	if (!magazinNou) {
		printf("eroare alocare memorie\n");
		return NULL;
	}

	strcpy(magazinNou->nume,nume);
	magazinNou->listaProduse = NULL;

	return magazinNou;
}

Multilista_t* initMultilista() {
	Multilista_t* multilistaNoua = (Multilista_t*)malloc(sizeof(Multilista_t));

	if (!multilistaNoua) {
		printf("eroare alocare memorie\n");
		return NULL;
	}

	multilistaNoua->nrCurentMagazine = 0;

	return multilistaNoua;
}

void adaugaProdus(Magazin_t* magazin, Produs_t* produsAdaugat) {
	//magazin gol
	if (magazin->listaProduse == NULL) {
		magazin->listaProduse = produsAdaugat;
	}
	else {
		// magazinul nu este gol
		Produs_t* produsCurent = magazin->listaProduse;

		if (produsAdaugat->cod < produsCurent->cod) {
			produsAdaugat->nextProdus = produsCurent;
			magazin->listaProduse = produsAdaugat;
			return;
		}

		Produs_t* produsAnterior = produsCurent;

		while (produsCurent != NULL && produsCurent->cod < produsAdaugat->cod) {
			produsAnterior = produsCurent;
			produsCurent = produsCurent->nextProdus;
		}

		produsAnterior->nextProdus = produsAdaugat;
		produsAdaugat->nextProdus = produsCurent;
	}
}

void afiseazaProduse(Magazin_t magazin) {
	Produs_t* produsCurent = magazin.listaProduse;
	printf("Magazinul are produsele : \n");

	while (produsCurent != NULL) {
		printf("\t Cod : %d \n", produsCurent->cod);

		produsCurent = produsCurent->nextProdus;
	}

	printf("------------------------------------\n");
}

void adaugaMagazin(Multilista_t* multilista, Magazin_t* magazinAdaugat) {
	if (multilista->nrCurentMagazine < MAX_MAGAZINE) {
		multilista->magazine[multilista->nrCurentMagazine++] = *magazinAdaugat;
	}
	else {
		printf("Nu mai este loc de magazine\n");
	}
}

void afiseazaMagazin(Multilista_t multilista) {
	for (int i = 0; i < multilista.nrCurentMagazine; i++) {
		printf("Magazinul %s \n", multilista.magazine[i].nume);
		afiseazaProduse(multilista.magazine[i]);
	}
}

void eliminaProdus(int codProdus, Multilista_t* multilista) {
	for (int i = 0; i < multilista->nrCurentMagazine; i++) {
		Produs_t* produsCurent = multilista->magazine[i].listaProduse;

		while (produsCurent != NULL) {
			if (produsCurent->cod == codProdus) {
				Produs_t* produsSters = produsCurent;
				produsCurent = produsCurent->nextProdus;
				free(produsSters);
			}
			else {
				produsCurent = produsCurent->nextProdus;
			}
		}
	}
}

int main(void) {
	Magazin_t *m1 = initMagazin("LIDL");

	for(int i = 0; i < 6; i++)
		adaugaProdus(m1, initProdus(i));

	afiseazaProduse(*m1);

	Multilista_t *multilista = initMultilista();

	adaugaMagazin(multilista, m1);

	afiseazaMagazin(*multilista);

	return 0;
}