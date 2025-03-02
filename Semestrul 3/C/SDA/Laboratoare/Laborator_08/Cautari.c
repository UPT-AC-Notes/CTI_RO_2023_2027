#include <stdio.h>
typedef struct
{
	int cheie;
}tip_element;
tip_element a[8] = { 3, 0, 1, 7, 4, 6, 5, 2 };
tip_element b[8];
int n = 8;
#define mm 8
void insertion_sort(tip_element a[], int n)
{
	int i, j;
	tip_element tmp;
	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i; (j > 0) && (tmp.cheie < a[j - 1].cheie); j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

void afisare(tip_element a[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d ", a[i].cheie);
	printf("\n");
}

int cautare_interpolare(tip_element a[], int n, int x)
{
	int stanga, dreapta, mij;
	int gasit;
	stanga = 0; dreapta = n - 1; gasit = 0;
	while ((stanga <= dreapta) && (!gasit) && (x >= a[stanga].cheie) && (x <= a[dreapta].cheie))
	{
		/* aici este modificarea*/
		mij = stanga + ((x - a[stanga].cheie)*(dreapta - stanga)) / (a[dreapta].cheie - a[stanga].cheie);
		if (a[mij].cheie<x) stanga = mij + 1;
		else if (a[mij].cheie>x) dreapta = mij - 1;
		else if (a[mij].cheie == x) gasit = 1;
	}
	if (gasit) /*avem o coincidenţă la indexul i*/
		return mij;
	else return -1;
}

int cautare_binara(tip_element a[], int n, int x)
{
	int stanga, dreapta, mij;
	int gasit;
	stanga = 0; dreapta = n - 1; gasit = 0;
	while ((stanga <= dreapta) && (!gasit))
	{
		/* aici este modificarea*/
		mij = (stanga + dreapta) / 2;
		if (a[mij].cheie<x) stanga = mij + 1;
		else if (a[mij].cheie>x) dreapta = mij - 1;
		else if (a[mij].cheie == x) gasit = 1;
	}
	if (gasit) /*avem o coincidenţă la indexul i*/
		return mij;
	else return -1;
}

int main(void)
{
	afisare(a, n);
	insertion_sort(a, n);
	printf("gasit %d\n", cautare_interpolare(a, n, 5));
	afisare(a, n);
	return 0;
}