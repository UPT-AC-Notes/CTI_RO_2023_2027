/*
	Fie un sistem de gestionare a unor paleți din cadrul unui depozit. 
	
	Depozitul este caracterizat printr-un nume unic, iar paleții printr-un cod numeric (maxim 8 cifre).

	Structura va avea următoarea componentă:

	Fiecare depozit reprezintă o intrare separată într-o listă principală.

	Fiecare depozit conține o listă secundară ordonată după codul paleților din acel depozit 
	
	(cel puțin una din liste va fi implementată dinamic).

	Funcționalități de implementat:

	Eliminare paleți: Ștergerea unui palet identificat după cod din toate depozitele.

	Să se aleagă un exemplu de listă care să conțină cel puțin 3 depozite, fiecare cu cel puțin 5 paleți.

	Reprezentare grafică a structurii multilistei înainte și după apelul funcției de eliminare.

	Notă:

	Algoritmul poate fi scris în pseudocod (stil C).
	Se vor specifica complexitatea algoritmilor și justificarea structurii alese.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Palet {
	int cod; //cod numeric (maxim 8 cifre)
	struct Palet* nextPalet;
}Palet_t;

typedef struct Depozit {
	char nume[20]; //nume unic -> deci va trb probabil verificat
	Palet_t* listaPaleti; // ordonata dupa codul paleților din acel depozit
	struct Depozit* nextDepozit;
}Depozit_t;

typedef Depozit_t* Multilista_t;

Palet_t* initPalet(int cod) {
	Palet_t* paletNou = (Palet_t*)malloc(sizeof(Palet_t));

	if (!paletNou) {
		printf("Eroare alocare memorie \n");
		return NULL;
	}

	paletNou->cod = cod;
	paletNou->nextPalet = NULL;

	return paletNou;
}

Depozit_t* initDepozit(char nume[20]) {
	Depozit_t* depozitNou = (Depozit_t*)malloc(sizeof(Depozit_t));

	if (!depozitNou) {
		printf("Eroare alocare memorie \n");
		return NULL;
	}

	strcpy(depozitNou->nume, nume);

	depozitNou->listaPaleti = NULL;
	depozitNou->nextDepozit = NULL;

	return depozitNou;
}
/*
Multilista_t* initMultilista() {
	Multilista_t* multilista = (Multilista_t*)malloc(sizeof(Multilista_t));

	if (!multilista) {
		printf("Eroare alocare memorie \n");
		return NULL;
	}

	(*multilista)->nextDepozit = NULL; //initializare lista principala

	return multilista;
}
*/

void adaugaPalet_InDepozit(Palet_t* paletDeAdaugat, Depozit_t * depozitInCareSeAdauga) {
	//daca depozitul nu mai are alti paleti in lista
	if (depozitInCareSeAdauga->listaPaleti == NULL) {
		depozitInCareSeAdauga->listaPaleti = paletDeAdaugat;
	}
	else {
		// daca are paleti in lista
		Palet_t* paletCurent = depozitInCareSeAdauga->listaPaleti; // asta ne ajuta sa ne parcurgem lista de paleti

		if (paletDeAdaugat->cod < paletCurent->cod) {
			paletDeAdaugat->nextPalet = paletCurent;
			//paletCurent = paletDeAdaugat;
			depozitInCareSeAdauga->listaPaleti = paletDeAdaugat;
			return;
		}

		while (paletCurent->nextPalet != NULL) {
			if (paletCurent->cod > paletDeAdaugat->cod) {
				paletDeAdaugat->nextPalet = paletCurent->nextPalet;
				paletCurent->nextPalet = paletDeAdaugat;
				return;
			}
			paletCurent = paletCurent->nextPalet;
		}

		//daca paletul de adaugat este mai mare decat toate celelalte
		paletCurent->nextPalet = paletDeAdaugat;
	}
}

void afiseazaDepozit(Depozit_t* depozitDeAfisat) {
	printf("Depozitul %s contine urmatorii paleti: \n", depozitDeAfisat->nume);

	Palet_t* paletCurent = depozitDeAfisat->listaPaleti;

	while (paletCurent != NULL) {
		printf("Paletul cu codul %d \n", paletCurent->cod);
		paletCurent = paletCurent->nextPalet;
	}

	printf("--------------------\n");
}

void adaugaDepozit_InMultilista(Depozit_t* depozitDeAdaugat, Multilista_t* multilista) {
	if (*multilista == NULL) {
		*multilista = depozitDeAdaugat;
		return;
	}
	Depozit_t* depozitCurent = *multilista; // primul depozit

	while (depozitCurent->nextDepozit != NULL) {
		depozitCurent = depozitCurent->nextDepozit;
	}

	// am ajuns la final de multilista
	
	depozitCurent->nextDepozit = depozitDeAdaugat;
}

void afiseazaMultiLista(Multilista_t* multilista) {
	Depozit_t* depozitCurent = *multilista;

	while (depozitCurent != NULL) {
		afiseazaDepozit(depozitCurent);
		depozitCurent = depozitCurent->nextDepozit;
	}
}

void stergePalet_dupaCod(Multilista_t* multilista, int codPaletDeSters) {
	Depozit_t* depozitCurent = *multilista;

	while (depozitCurent != NULL) {
		Palet_t* paletCurent = depozitCurent->listaPaleti;
		Palet_t* paletAnteriorCeluiDeSters = NULL;

		while (paletCurent != NULL) {
			if (paletCurent->cod == codPaletDeSters) {
				// daca e primul palet
				if (paletAnteriorCeluiDeSters == NULL) {
					depozitCurent->listaPaleti = paletCurent->nextPalet;
				}
				else {
					paletAnteriorCeluiDeSters->nextPalet = paletCurent->nextPalet;
				}
				free(paletCurent);

				break; //asta poate disparea daca exista intr o lista de paleti mai multi paleti cu acelasi cod
			}

			paletAnteriorCeluiDeSters = paletCurent;
			paletCurent = paletCurent->nextPalet;
		}

		depozitCurent = depozitCurent->nextDepozit;
	}
}

int main(void) {

	// baga cel putin 3 depozite, fiecare cu cel putin 5 paleți

	Multilista_t multilista = NULL;

	Depozit_t* depozit1 = initDepozit("Depozit1");
	Depozit_t* depozit2 = initDepozit("Depozit2");
	Depozit_t* depozit3 = initDepozit("Depozit3");
	
	for (int i = 0; i < 5; i++) {
		Palet_t* paletNou = initPalet(i);
		adaugaPalet_InDepozit(paletNou, depozit1);
	}

	for (int i = 5; i < 10; i++) {
		Palet_t* paletNou = initPalet(i);
		adaugaPalet_InDepozit(paletNou, depozit2);
	}

	for (int i = 5; i < 10; i++) {
		Palet_t* paletNou = initPalet(i);
		adaugaPalet_InDepozit(paletNou, depozit3);
	}

	adaugaDepozit_InMultilista(depozit1, &multilista);
	adaugaDepozit_InMultilista(depozit2, &multilista);
	adaugaDepozit_InMultilista(depozit3, &multilista);

	afiseazaMultiLista(&multilista);

	printf("DUPA STERGERE \n\n");
		
	// sterge un palet 
	stergePalet_dupaCod(&multilista, 9);

	afiseazaMultiLista(&multilista);


	return 0;
}