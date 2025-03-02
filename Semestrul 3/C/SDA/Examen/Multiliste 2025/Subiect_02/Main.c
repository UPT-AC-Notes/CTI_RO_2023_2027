/*
	Fie un sistem de gestionare a unor GPS-uri instalate pe camioane în cadrul unor firme de transport. 

	Firma de transport este caracterizată printr-un nume unic, iar GPS-urile printr-un cod numeric (maxim 8 cifre).

	Se cere să se implementeze o structură multilistă adecvată pentru gestionarea acestor GPS-uri. 

	Structura va avea următoarea componentă:

			Fiecare firmă de transport reprezintă o intrare separată într-o listă principală.

			Fiecare firmă de transport conține o listă secundară ordonată după codul GPS-urilor (corespunzătoare camioanelor fiecărei firme).

			Cel puțin una din liste va fi implementată dinamic.

	Funcționalități de implementat:
			Eliminare GPS: Se șterge un GPS identificat după cod din toate firmele.

			Să se aleagă un exemplu de listă care să cuprindă cel puțin 3 firme, fiecare cu cel puțin 5 GPS-uri.

			Să se reprezinte grafic structura multilistei pentru acest exemplu, înainte și după apelul funcției de eliminare GPS.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GPS {
	int cod; // maxim 8 cifre
	struct GPS* nextGPS; 
}GPS_t;

typedef struct Firma {
	char nume[20];
	GPS_t* listaGPS;
	struct Firma* nextFirma;
}Firma_t;

typedef Firma_t* Multilista_t;

GPS_t* initGPS(int cod) {
	GPS_t* gpsNou = (GPS_t*)malloc(sizeof(GPS_t));

	if (!gpsNou) {
		printf("Eroare alocare memorie\n");
		return NULL;
	}

	gpsNou->cod = cod;
	gpsNou->nextGPS = NULL;

	return gpsNou;
}

Firma_t* initFirma(char nume[20]) {
	Firma_t* firmaNoua = (Firma_t*)malloc(sizeof(Firma_t));

	if (!firmaNoua) {
		printf("Eroare alocare memorie\n");
		return NULL;
	}

	strcpy(firmaNoua->nume, nume);
	firmaNoua->listaGPS = NULL;
	firmaNoua->nextFirma = NULL;

	return firmaNoua;
}

void adaugaGPS_inFirma(GPS_t* gpsDeAdaugat, Firma_t* firmaInCareSeAdauga) {
	//vom trata doua cazuri, daca firma este goala sau are un element sau nu
	if (firmaInCareSeAdauga->listaGPS == NULL) {
		firmaInCareSeAdauga->listaGPS = gpsDeAdaugat;
	}
	else {
		GPS_t* gpsCurent = firmaInCareSeAdauga->listaGPS;

		if (gpsDeAdaugat->cod < gpsCurent->cod) {
			gpsDeAdaugat->nextGPS = gpsCurent;
			firmaInCareSeAdauga->listaGPS = gpsDeAdaugat;
			return;
		}

		while (gpsCurent->nextGPS != NULL) {
			if (gpsCurent->cod > gpsDeAdaugat->cod) {
				gpsDeAdaugat->nextGPS = gpsCurent->nextGPS;
				gpsCurent->nextGPS = gpsDeAdaugat;
				return;
			}
			gpsCurent = gpsCurent->nextGPS;
		}

		gpsCurent->nextGPS = gpsDeAdaugat;
	}
}

Firma_t* cautaFirma(Multilista_t multilista, char nume[20]) {
	Firma_t* firmaCurenta = multilista;

	while (firmaCurenta != NULL) {
		if (strcmp(firmaCurenta->nume, nume) == 0) {
			return firmaCurenta;
		}

		firmaCurenta = firmaCurenta->nextFirma;
	}

	return NULL;
}

void adaugaFirma_inMultilista(Multilista_t* multilista, Firma_t* firmaDeAdaugat) {
	if (*multilista == NULL) {
		*multilista = firmaDeAdaugat;
		return;
	}

	Firma_t* firmaCurenta = multilista;

	while (firmaCurenta->nextFirma != NULL) {
		firmaCurenta = firmaCurenta->nextFirma;
	}

	firmaCurenta->nextFirma = firmaDeAdaugat;
}

void afiseazaFirma(Firma_t* firmaDeAfisat) {
	printf("Firma: %s contine urm camioane cu cod GPS\n", firmaDeAfisat->nume);

	GPS_t* gpsCurent = firmaDeAfisat->listaGPS;

	while (gpsCurent != NULL) {
		printf("GPS: %d\n", gpsCurent->cod);
		gpsCurent = gpsCurent->nextGPS;
	}

	printf("--------------------\n");
}

void afiseazaMultilista(Multilista_t *multilista) {
	Firma_t* firmaCurenta = *multilista;

	while (firmaCurenta != NULL) {
		afiseazaFirma(firmaCurenta);
		firmaCurenta = firmaCurenta->nextFirma;
	}
}

void stergeGPS_dupaCod(Multilista_t* multilista, int codGpsDeSters) {
	Firma_t* firmaCurenta = *multilista;

	while (firmaCurenta != NULL) {
		GPS_t* gpsCurent = firmaCurenta->listaGPS;
		GPS_t* gpsAnteriorCeluiDeSters = NULL;

		while (gpsCurent != NULL) {
			if (gpsCurent->cod == codGpsDeSters) {
				
				if (gpsAnteriorCeluiDeSters == NULL) {
					firmaCurenta->listaGPS = gpsCurent->nextGPS;
				}
				else {
					gpsAnteriorCeluiDeSters->nextGPS = gpsCurent->nextGPS;
				}

				free(gpsCurent);
				gpsCurent = NULL;

				break;
			}
			gpsAnteriorCeluiDeSters = gpsCurent;
			gpsCurent = gpsCurent->nextGPS;
		}

		firmaCurenta = firmaCurenta->nextFirma;
	}
}




int main(void) {
	Multilista_t multilista = NULL;

	Firma_t* firma1 = initFirma("Firma1");
	Firma_t* firma2 = initFirma("Firma2");
	Firma_t* firma3 = initFirma("Firma3");

	for (int i = 1; i <= 5; i++) {
		adaugaGPS_inFirma(initGPS(i * 100), firma1);
	}
	for (int i = 6; i <= 10; i++) {
		adaugaGPS_inFirma(initGPS(i * 100), firma2);
	}
	for (int i = 11; i <= 15; i++) {
		adaugaGPS_inFirma(initGPS(i * 100), firma3);
	}

	adaugaFirma_inMultilista(&multilista, firma1);
	adaugaFirma_inMultilista(&multilista, firma2);
	adaugaFirma_inMultilista(&multilista, firma3);

	afiseazaMultilista(&multilista);

	stergeGPS_dupaCod(&multilista, 500);

	afiseazaMultilista(&multilista);

	return 0;
}