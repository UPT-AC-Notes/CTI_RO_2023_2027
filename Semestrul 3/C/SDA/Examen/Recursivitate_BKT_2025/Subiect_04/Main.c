/*
	Un labirint este reprezentat sub forma unei matrice A cu m linii și n coloane.

	Elementele A[i][j] reprezintă informația legată de acea celulă:

								−1: perete,

								0: celulă liberă,

								>0: puncte de energie.

	Se presupune că un roboțel se găsește inițial într-o celulă A(a,b), având P puncte de energie.

	Știind că roboțelul consumă un punct de energie la fiecare pas și că acesta se poate deplasa atâta vreme cât

	mai are energie disponibilă, să se implementeze structurile de date necesare și funcțiile valid și soluție pentru

	un algoritm de tip backtracking care:

		Calculează toate traseele ce pot fi urmate de roboțel pentru ca el să iasă din labirint

		(să ajungă în oricare din celulele libere de la marginea labirintului).

	Roboțelul se poate deplasa în oricare din cele 4 celule învecinate (sus, jos, stânga, dreapta),

	cu condiția ca acestea să nu fie un perete, iar dacă celula conține puncte de energie atunci le va culege,

	încărcându-și bateriile.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Coordonata {
	int x;
	int y;
}Coordonata_t;


typedef struct Robot {
	Coordonata_t coordonataCurenta;
	int energie;
}Robot_t;

Coordonata_t deplasari[4];

Robot_t robot;

#define MAX_LINII 4
#define MAX_COLOANE 4

int labirint[MAX_LINII][MAX_COLOANE];

int vizitat[MAX_LINII][MAX_COLOANE];

Coordonata_t traseu[100];
int lungimeTraseu = 0;

void initializare() {
	//stanga
	deplasari[0].x = 0;
	deplasari[0].y = -1;

	// dreapta
	deplasari[1].x = 0;
	deplasari[1].y = 1;

	//sus 
	deplasari[2].x = -1;
	deplasari[2].y = 0;

	//jos
	deplasari[3].x = 1;
	deplasari[3].y = 0;
}

void citesteDate(int matrice[][MAX_COLOANE], FILE* fin) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			fscanf(fin, "%d", &matrice[i][j]);
		}
	}
}

void afiseazaMatrice(int matrice[][MAX_COLOANE]) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

int eSolutie(Coordonata_t c) {
	if (c.x == 0 || c.y == 0 || c.x == MAX_LINII - 1 || c.y == MAX_COLOANE - 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int acceptabil(Coordonata_t c) { //coordonata viitoare

	if (c.x >= 0 && c.y >= 0 && c.x < MAX_LINII && c.y < MAX_COLOANE && labirint[c.x][c.y] != -1 && vizitat[c.x][c.y] == 0 && robot.energie>0)
		return 1;
	return 0;
}

void afiseazaTraseu() {
	printf("\n traseu\n");
	for (int i = 0; i < lungimeTraseu; i++) {
		printf("(%d, %d) -> ", traseu[i].x, traseu[i].y);
	}
	printf("end \n\n ----------------------------------------------\n");
}

void back() {
	int i;
	Coordonata_t aux;
	traseu[lungimeTraseu++] = robot.coordonataCurenta;

	//printf("%d %d\n", robot.coordonataCurenta.x, robot.coordonataCurenta.y);

	if (eSolutie(robot.coordonataCurenta)) {
		afiseazaMatrice(vizitat);
		afiseazaTraseu();
		//lungimeTraseu--;
		return;
	}
	else {
		for (int i = 0; i < 4; i++) {
			aux.x = robot.coordonataCurenta.x + deplasari[i].x;
			aux.y = robot.coordonataCurenta.y + deplasari[i].y;

			if (acceptabil(aux)) {
				int energieCurent = robot.energie;
				robot.coordonataCurenta = aux;
				robot.energie += labirint[robot.coordonataCurenta.x][robot.coordonataCurenta.y] - 1;
				vizitat[robot.coordonataCurenta.x][robot.coordonataCurenta.y] = 1;

				back();
				vizitat[robot.coordonataCurenta.x][robot.coordonataCurenta.y] = 0;

				robot.coordonataCurenta.x -= deplasari[i].x;
				robot.coordonataCurenta.y -= deplasari[i].y;
				robot.energie = energieCurent;
				lungimeTraseu--;
			}
		}

	}
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Utilizare incorecta argumente \n");
		return -1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (fin == NULL) {
		printf("Eroare deschidere fisier\n");
		return -2;
	}

	initializare();

	citesteDate(labirint, fin);

	robot.coordonataCurenta.x = 2;
	robot.coordonataCurenta.y = 2;
	robot.energie = 13;

	vizitat[robot.coordonataCurenta.x][robot.coordonataCurenta.y] = 1;

	back();

	fclose(fin);

	return 0;
}