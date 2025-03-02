#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define lung_max 3

typedef int tip_indice;
typedef struct {
	int info;
} tipnod;

typedef struct {
	tipnod noduri[lung_max];
	tip_indice ultim;
} tiplista;
typedef tip_indice tip_pozitie;
typedef unsigned boolean;
#define true (1)
#define false (0)
boolean reccmp(tipnod x, tipnod y);/*comparare conţinut  noduri*/


void insereaza(tiplista* l, tipnod x,
	tip_pozitie p, boolean* er)	/*plasează pe x în poziţia p a listei; performanţa O(n)*/
{
	tip_pozitie q;
	*er = false;
	if (l->ultim >= (lung_max - 1)) {
		*er = true;
		printf("lista este plina");
	}
	else
		if ((p > l->ultim + 1) || (p < 0)) {
			*er = true;
			printf("pozitie invalida");
		}
		else {
			for (q = l->ultim + 1; q > p; q--)
				l->noduri[q] = l->noduri[q - 1];//se face loc pentru noul element
			l->noduri[p] = x;					//se insereaza elementul
			l->ultim++;							//se incrementeaza numarul de elemente
		}
} /*insereaza*/
void suprima(tiplista* l, tip_pozitie p, boolean* er)
/*extrage elementul din poziţia p a listei*/
{
	tip_pozitie q; /*performanţa O(n)*/
	*er = false;
	if ((p > l->ultim + 1) || (p < 0)) {
		*er = true;
		printf("pozitie invalida");
	}
	else {
		for (q = p; q <= l->ultim; q++)
			l->noduri[q] = l->noduri[q + 1];
		l->ultim = l->ultim - 1;
	}
} /*suprima*/
tip_pozitie cauta(tipnod x, tiplista l)
{
	/*returnează poziţia lui x în listă*/
	tip_pozitie q;
	boolean gasit;
	tip_pozitie cauta_result;
	q = 0; gasit = false; /*performanţa O(n)*/
	do {
		if (reccmp(l.noduri[q], x) != 0) {
			cauta_result = q;
			gasit = true;
		}
		q = q + 1;
	} while (!(gasit || (q == l.ultim + 1)));
	if (!gasit) cauta_result = -1;
	return cauta_result;
}
/*cauta*/
boolean reccmp(tipnod x, tipnod y)
/*comparare conţinut noduri*/
{
	if (x.info == y.info)
		return true;
	else
		return false;
}

int main(void)
{
	tiplista l;
	int er;
	l.ultim = -1;
	tipnod a = { 1 };
	insereaza(&l, a, 0, &er);
	a.info = 2;
	insereaza(&l, a, 1, &er);
	a.info = 3;
	insereaza(&l, a, 2, &er);
	a.info = 4;
	insereaza(&l, a, 3, &er);
	a.info = 4;
	printf("\n-%d-\n", cauta(a, l));
	suprima(&l, 1, &er);
	suprima(&l, 1, &er);
	suprima(&l, 0, &er);
	suprima(&l, 1, &er);
	return 0;
}