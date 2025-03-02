0##include <stdio.h>
#include <stdlib.h>
#define Datein "date3.txt"
typedef struct angajat {
	char nume[35];
	int salariu;
	int bonus;
}angajat;
void citire(angajat* s, int n,FILE *f)
{
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%s %d %d", s[i].nume, &s[i].salariu, &s[i].bonus);
	}
}//O(n)
void afisare(angajat* s, int n )
{
	for (int i = 0; i < n; i++)
	{
		printf( "%s %d %d\n", s[i].nume, s[i].salariu, s[i].bonus);
	}
	printf("\n");
}//O(n)
void mutare(angajat* s, int n)
{
	int j = n-1,i=0;
	while (i < j)
	{
		if (s[i].bonus == 1)
		{
			if (s[j].bonus == 0)
			{
				angajat aux;
				aux = s[j];
				s[j] = s[i];
				s[i] = aux;
			}
			else
			{
				j--;
			}
		}
		else
		{
			i++;
		}
	}
}//O(n)
void quick(angajat* p, int s, int d)
{
	int i = s, j = d;
	angajat x = p[(s + d) / 2];
	do {
		while (p[i].salariu < x.salariu) i++;
		while (p[j].salariu > x.salariu) j--;
		if (i <= j)
		{
			angajat temp = p[i];
			p[i] = p[j];
			p[j] = temp;
			i++;
			j--;
			
		}
	} while (i <= j);
	if (s < j) quick(p, s, j);
	if (d > i) quick(p, i, d);
}//O(n*log(n)) uzual O(n^2) cel mai defavorabil caz
void sortare(angajat* s, int n)
{
	int m = 0;
	while (s[m].bonus == 0)
	{
			m++;
	}
	quick(s, m, n - 1);
}
int main(void)
{
	FILE* ff;
	if ((ff = fopen(Datein, "r")) == NULL)
	{
		exit(-2);
	}
	angajat s[20];
	int n;
	fscanf(ff, "%d", &n);
	citire(s, n, ff);
	afisare(s, n);
	mutare(s, n);
	afisare(s, n);
	sortare(s, n);
	afisare(s, n);
	return 0;
}