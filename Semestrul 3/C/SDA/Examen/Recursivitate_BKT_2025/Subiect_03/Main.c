/*
	Enunț:

	Un teren este reprezentat sub forma unei matrice A cu m linii și n coloane. 
	
	Elementele A[i][j] aparțin mulțimii numerelor reale și reprezintă cotele (înălțimea) diferitelor 
	
	porțiuni din acest teren. Se presupune că:

		O bilă se găsește pe o porțiune A[a][b] (citită de la tastatură).

		Bila se poate deplasa pe orice porțiune vecină (orizontal, vertical sau diagonal), 
		
		doar dacă cota porțiunii vecine este strict inferioară cotei curente.


	Cerințe:

	Să se precizeze toate traseele pe care bila le poate urma de la poziția de start, până când aceasta va ieși din teren.

	Să se implementeze funcționalitatea algoritmului și structurile de date necesare.

	Să se exemplifice funcționarea algoritmului pentru o matrice de dimensiune minimă 3×3.


	Notă:

	Algoritmul poate fi scris în pseudocod sau în C.

	Este obligatorie comentarea algoritmului și justificarea complexității acestuia în termeni de O(f(n)).

	Trebuie justificată alegerea structurilor de date utilizate.

	Se va exemplifica efectul funcționalităților implementate pe un exemplu ales.

*/

#include <stdio.h>

#define MAX_LINII   3
#define MAX_COLOANE 3

int dx[] = { -1, 1, 0, 0, -1, -1, 1, 1};
int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1};


void citesteDate(float matrice[][MAX_COLOANE], FILE* fin) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			fscanf(fin, "%f", &matrice[i][j]);
		}
	}
}

void afiseazaMatrice(float matrice[][MAX_COLOANE]) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			printf("%f ", matrice[i][j]);
		}
		printf("\n");
	}
	printf("\n\n-----------------------------------------------------------------------\n\n");
}



float vizitat[MAX_LINII][MAX_COLOANE];

int esteValid(float matrice[][MAX_COLOANE], int x, int y, float curent) {
	return (x >= 0 && x < MAX_LINII && y >= 0 && y < MAX_COLOANE && vizitat[x][y] == 0 && curent > matrice[x][y]);
}

void fill(float matrice[][MAX_COLOANE], int x, int y) {
	vizitat[x][y] = 1;

	if (x == 0 || x == (MAX_LINII - 1) || y == 0 || y == (MAX_COLOANE - 1)) {
		afiseazaMatrice(vizitat);
		vizitat[x][y] = 0;
		return;
	}

	for (int d = 0; d < 8; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];

		if (esteValid(matrice, nx, ny, matrice[x][y])) {
			fill(matrice, nx, ny);
		}
	}

	vizitat[x][y] = 0;
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

	int x, y;

	if (fscanf(fin, "%d %d", &x, &y) != 2) {
		printf("Nu ati introdus corect coordonatele de plecare\n");
		return -3;
	}

	float matrice[MAX_LINII][MAX_COLOANE];

	citesteDate(matrice, fin);

	printf("Matrice initiala : \n");

	afiseazaMatrice(matrice);

	printf("\n---\n");

	fill(matrice, x, y);



	return 0;
}