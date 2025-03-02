/*
	O fotografie alb-negru este prezentată sub forma unei matrice binare. 
	
	Fiecare element din matrice reprezintă un pixel. 
	
	În fotografie pot exista unul sau mai multe obiecte. 
	
	Porțiunile corespunzătoare obiectului (sau obiectelor) în matrice au valoarea 1, iar restul au valoarea 0.

	Se cere să se proiecteze un algoritm care determină câte obiecte sunt prezente în fotografie.

	Cerințe:
		Algoritmul trebuie scris în pseudocod sau în limbaj C.

		Este obligatorie comentarea algoritmului și justificarea complexității acestuia în termeni de O(f(n)).

		Este obligatorie exemplificarea efectului algoritmului pe un exemplu ales.
*/

// o solutie ar putea fi implementata cu flood fill

/*
	1 1 0 0 0
	1 1 0 0 0
	0 0 0 1 1
	0 0 1 0 0
	0 0 1 1 1

	-> 3 obiecte 
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINII   5
#define MAX_COLOANE 5

int vizitat[MAX_LINII][MAX_COLOANE];


// directii stanga - dreapta - sus - jos
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};


void citesteDate(int matrice[][MAX_COLOANE], FILE* fin) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			fscanf(fin, "%d", &matrice[i][j]);
		}
	}
}

void fill(int matrice[][MAX_COLOANE], int x, int y) {
	matrice[x][y] = 3;

	if (y > 0 && matrice[x][y - 1] == 1) {
		fill(matrice, x, y - 1); // stanga sau vest
	}

	if (y < (MAX_COLOANE - 1) && matrice[x][y + 1] == 1) {
		fill(matrice, x, y + 1); // dreapta sau est
	}

	if (x > 0 && matrice[x - 1][y] == 1) {
		fill(matrice, x - 1, y); // sus sau nord
	}

	if (x < (MAX_LINII - 1) && matrice[x + 1][y] == 1) {
		fill(matrice, x + 1, y); // jos sau sud
	}

}

int esteValid(int x, int y, int matrice[][MAX_COLOANE]) {
	return (x >= 0 && x < MAX_LINII && y >= 0 && y < MAX_COLOANE && matrice[x][y] == 1);
}

void fillDeplasamente(int matrice[][MAX_COLOANE], int x, int y) {
	matrice[x][y] = 3;

	for (int d = 0; d < 4; d++) {
		//noile pozitii
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (esteValid(nx, ny, matrice)) {
			fillDeplasamente(matrice, nx, ny);
		}
	}
}

int numaraObiecte(int matrice[][MAX_COLOANE]) {
	int nrObiecte = 0;

	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			if (matrice[i][j] == 1) {
				nrObiecte++;
				//fill(matrice, i, j);
				fillDeplasamente(matrice, i, j);
			}
		}
	}

	return nrObiecte;
}

void afiseazaMatrice(int matrice[][MAX_COLOANE]) {
	for (int i = 0; i < MAX_LINII; i++) {
		for (int j = 0; j < MAX_COLOANE; j++) {
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
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

	int matrice[MAX_LINII][MAX_COLOANE];

	citesteDate(matrice, fin);

	printf("Matrice initiala : \n");

	afiseazaMatrice(matrice);

	printf("\n---\n");

	int nrObiecte = numaraObiecte(matrice);

	printf("Numarul de obiecte este : %d\n", nrObiecte);
	return 0;
}