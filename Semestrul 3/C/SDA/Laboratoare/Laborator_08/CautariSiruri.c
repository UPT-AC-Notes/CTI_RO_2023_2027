#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//KMP
int d[256]; //tabloul de coeficienti k folositi in calculul deplasarilor

int KMP(char s[], char p[]) //s-sursa, p- model
{
	int i, j, k;
	j = 0; k = -1; d[0] = -1; /*precompilare model*/
	unsigned int n = strlen(s);
	unsigned int m = strlen(p);
	while (j < m - 1)
	{
		while ((k >= 0) && (p[j] != p[k]))
		{
			k = d[k];
		}
		j = j + 1;
		k = k + 1;
		if (p[j] == p[k])
			d[j] = d[k];
		else d[j] = k;
	}
	/*cât timp*/
	i = 0; j = 0; /*căutare model*/
	while ((j < m) && (i < n))
	{
		while ((j >= 0) && (s[i] != p[j]))
		{
			j = d[j];
		}
		j = j + 1;
		i = i + 1;
	}
	if (j == m)
		return i - m;
	else return -1;
	/*CautareKMP*/
}

int BM(char* s, char* p) //s - sursa, p - model
{
	int k, i, j; int n = strlen(s); int m = strlen(p);
	//construire tablou d
	for (i = 0; i < 256; i++) d[i] = m;
	for (j = 0; j <= m - 2; j++) d[p[j]] = m - j - 1;
	i = m; j = m;
	while ((j > 0) && (i <= n))
	{
		j = m;
		k = i;
		while ((j > 0) && (s[k - 1] == p[j - 1]))
		{
			k = k - 1;
			j = j - 1;
		}
		if (j > 0) i = i + d[s[i - 1]];
	}
	if (j == 0) {
		return k;
	}
	else
		return -1;
}


int main()
{
	const char txt[] = "abababaabcabacaababaca";
	const char pat[] = "ababaca";
	int result = KMP(txt, pat);
	printf("%d ", result);
	printf("\n");
	result = BM(txt, pat);
	printf("%d ", result);
	printf("\n");
	return 0;
}