/*
Enunț:

	Se dă mulțimea M={a,b,c}.
	
	Să se implementeze structurile de date necesare și următoarele funcționalități:

		Generează cuvinte - Funcția determină toate cuvintele ce conțin numai litere din mulțimea M, 
		
		de lungime 10, care conțin exact 3 simboluri 'a', 4 simboluri 'b' și 3 simboluri 'c'.

		Să se noteze primele 5 cuvinte generate în ordine.
Nota:

	Algoritmul poate fi scris în pseudocod (C-like).

	Este obligatorie comentarea algoritmului și specificarea complexității acestuia în termeni de O(f(n)).

	Este obligatorie exemplificarea efectului apelului funcțiilor implementate pe un exemplu ales.
*/

#include <stdio.h>

#define nmax 10	//lungime cuv generat

char a[nmax];	
int pos[nmax];

#define nr_a 3
#define nr_b 4
#define nr_c 3


int acceptabil(char pos, int k) {
	int nrCurent_a = 0;
	int nrCurent_b = 0;
	int nrCurent_c = 0;

	for (int i = 0; i < k; i++) {
		if (a[i] == 'a') {
			nrCurent_a++;
		}
		if (a[i] == 'b') {
			nrCurent_b++;
		}
		if (a[i] == 'c') {
			nrCurent_c++;
		}
	}

	if (pos == 'a' && nrCurent_a < nr_a) {
		return 1;
	}

	if (pos == 'b' && nrCurent_b < nr_b) {
		return 1;
	}

	if (pos == 'c' && nrCurent_c < nr_c) {
		return 1;
	}

	return 0;
}

int eSolutie(int k) {
	// sa aiba lungimea 10
	return k == nmax;
}

int solutiiAfisate = 0;

void afiseazaSolutia() {
	for (int i = 0; i < nmax; i++) {
		printf("%c", a[i]);
	}
	printf("\n");
	solutiiAfisate++;
}

void permuta(int k) {
	
	int i;
	char aux;

	char pos[] = { 'a', 'b', 'c' };

	if (solutiiAfisate >= 5) {
		return;
	}

	if (eSolutie(k)) {
		afiseazaSolutia();

	}
	else {
		for (i = 0; i < 3; i++) {	// parcurgem toate posibilitatile
			aux = pos[i];

			if (acceptabil(aux, k)) {
				a[k] = pos[i];
				permuta(k + 1);
			}
		}
	}
}

void genereazaCuvinte(char res[10], int i, int a_ramas, int b_ramas, int c_ramas) {
	if (solutiiAfisate >= 5) {
		return;
	}

	if (i == 10) {
		for (int j = 0; j < 10; j++) {
			printf("%c", res[j]);
		}
		printf("\n");
		solutiiAfisate++;
		return;
	}

	if (a_ramas > 0) {
		res[i] = 'a';
		genereazaCuvinte(res, i + 1, a_ramas - 1, b_ramas, c_ramas);
	}

	if (b_ramas > 0) {
		res[i] = 'b';
		genereazaCuvinte(res, i + 1, a_ramas, b_ramas - 1, c_ramas);
	}

	if (c_ramas > 0) {
		res[i] = 'c';
		genereazaCuvinte(res, i + 1, a_ramas, b_ramas, c_ramas - 1);
	}
}

int main(void) {
	//permuta(0);

	char res[10];

	genereazaCuvinte(res, 0, 3, 4, 3);

	return 0;
}