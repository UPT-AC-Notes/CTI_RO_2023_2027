/*
		Fie o aplicație care gestionează o rețea de profesioniști din întreaga lume, de tip LinkedIn. Pentru o persoană se memorează:

						un ID (număr întreg),
						un nume (maxim 35 caractere),
						o ocupație (maxim 35 caractere),
						o listă de recomandări.

		O recomandare trebuie să conțină:

					text (maxim 100 caractere fiecare),
					ID-ul persoanei care a făcut recomandarea.

		Structura trebuie să fie implementată utilizând lista simplu înlănțuită, 
		
		iar fiecare persoană va conține un tablou static cu recomandările primite.

		Cerințe:
					Căutare profesioniști IT:

					Se cere crearea unei liste (statică sau dinamică) care să conțină 
					
					3 profesioniști IT cu mai mult de 10 recomandări.

		Se va reprezenta grafic structura multilistei înainte și după apelul funcției de căutare.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECOMANDARI 16

typedef struct Recomandare {
    char text[100];
    int idPersoanaCareAFacutRecomandarea;
} Recomandare_t;

typedef struct Persoana {
    int id;
    char nume[35];
    char ocupatie[35];
    Recomandare_t recomandari[MAX_RECOMANDARI];
    int nrCurentRecomandari;
    struct Persoana* nextPersoana;
} Persoana_t;

typedef Persoana_t* Multilista_t;

Persoana_t* initPersoana(int id, const char* nume, const char* ocupatie) {
    Persoana_t* persoanaNoua = (Persoana_t*)malloc(sizeof(Persoana_t));

    if (!persoanaNoua) {
        printf("Eroare alocare memorie\n");
        return NULL;
    }

    persoanaNoua->id = id;

    strcpy(persoanaNoua->nume, nume);
    strcpy(persoanaNoua->ocupatie, ocupatie);
    persoanaNoua->nrCurentRecomandari = 0;
    persoanaNoua->nextPersoana = NULL;
    return persoanaNoua;
}

void adaugaRecomandare(Persoana_t* persoana, const char* text, int id) {
    if (!persoana) {
        printf("Persoana invalida\n");
        return;
    }
    if (persoana->nrCurentRecomandari < MAX_RECOMANDARI) {
        Recomandare_t* recomandare = &persoana->recomandari[persoana->nrCurentRecomandari++];

        strcpy(recomandare->text, text);
        recomandare->idPersoanaCareAFacutRecomandarea = id;
    }
    else {
        printf("Persoana %s a atins limita de recomandari\n", persoana->nume);
    }
}

void adaugaPersoana(Persoana_t* persoanaDeAdaugat, Multilista_t* multilista) {
    if (*multilista == NULL) {
        *multilista = persoanaDeAdaugat;
    }
    else {
        Persoana_t* persoanaCurenta = *multilista;

        while (persoanaCurenta->nextPersoana != NULL) {
            persoanaCurenta = persoanaCurenta->nextPersoana;
        }

        persoanaCurenta->nextPersoana = persoanaDeAdaugat;
    }
}

void afiseazaRecomandari(Persoana_t* persoana) {
    printf("  Recomandari:\n");
    for (int i = 0; i < persoana->nrCurentRecomandari; i++) {
        printf("    ID: %d, Text: %s\n",
            persoana->recomandari[i].idPersoanaCareAFacutRecomandarea,
            persoana->recomandari[i].text);
    }
    printf("----------------------------------------\n");
}

void afiseazaMultilista(Multilista_t multilista) {
    Persoana_t* persoanaCurenta = multilista;
    while (persoanaCurenta != NULL) {
        printf("Persoana: ID: %d, Nume: %s, Ocupatie: %s\n",
            persoanaCurenta->id, persoanaCurenta->nume, persoanaCurenta->ocupatie);
        afiseazaRecomandari(persoanaCurenta);
        persoanaCurenta = persoanaCurenta->nextPersoana;
    }
}

Multilista_t cautaProfesionistiIT(Multilista_t multilista) {
    Multilista_t listaProfesionisti = NULL;

    Persoana_t* persoanaCurenta = multilista;

    while (persoanaCurenta != NULL) {
        if (strcmp(persoanaCurenta->ocupatie, "IT") == 0 && persoanaCurenta->nrCurentRecomandari > 10) {

            Persoana_t* copiePersoana = initPersoana(persoanaCurenta->id, persoanaCurenta->nume, persoanaCurenta->ocupatie);

            copiePersoana->nrCurentRecomandari = persoanaCurenta->nrCurentRecomandari;

            memcpy(copiePersoana->recomandari, persoanaCurenta->recomandari, sizeof(persoanaCurenta->recomandari));

            adaugaPersoana(copiePersoana, &listaProfesionisti);
        }
        persoanaCurenta = persoanaCurenta->nextPersoana;
    }
    return listaProfesionisti;
}

int main(void) {
    Multilista_t multilista = NULL;

    Persoana_t* persoana1 = initPersoana(1, "Alice", "IT");
    Persoana_t* persoana2 = initPersoana(2, "Bob", "Marketing");
    Persoana_t* persoana3 = initPersoana(3, "Charlie", "IT");
    Persoana_t* persoana4 = initPersoana(4, "David", "IT");
    Persoana_t* persoana5 = initPersoana(5, "Eve", "HR");


    adaugaPersoana(persoana1, &multilista);
    adaugaPersoana(persoana2, &multilista);
    adaugaPersoana(persoana3, &multilista);
    adaugaPersoana(persoana4, &multilista);
    adaugaPersoana(persoana5, &multilista);

    for (int i = 1; i <= 12; i++) {
        adaugaRecomandare(persoana1, "Recomandare IT pentru Alice", i);
    }
    for (int i = 1; i <= 8; i++) {
        adaugaRecomandare(persoana2, "Recomandare generala", i);
    }
    for (int i = 1; i <= 11; i++) {
        adaugaRecomandare(persoana3, "Recomandare IT pentru Charlie", i);
    }
    for (int i = 1; i <= 15; i++) {
        adaugaRecomandare(persoana4, "Recomandare IT pentru David", i);
    }

    printf("Structura multilista initiala:\n");
    afiseazaMultilista(multilista);


    printf("\nProfesionisti IT cu peste 10 recomandari:\n");
    Multilista_t listaProfesionisti = cautaProfesionistiIT(multilista);
    afiseazaMultilista(listaProfesionisti);

    return 0;
}
