#include <stdio.h>
#include <stdlib.h>
typedef unsigned boolean;
#define true (1)
#define false (0)
#define lungime_maxima 5
/*Exemplu de implementare a TDA Coada cu ajutorul TDA Lista (setul 1 de operatori).*/
typedef int tip_element;
typedef struct coada_c
{
	tip_element coada[lungime_maxima + 1];
	int dimensiune;
	int prim;
	int ultim;
}tip_coada;
void initializeaza(tip_coada* c)
{
	c->dimensiune = lungime_maxima + 1;
	c->prim = 1;
	c->ultim = 0;
}
tip_element cap(tip_coada c)
{
	return c.coada[c.prim];
}
boolean vid(tip_coada c)
{
	if (((c.ultim + 1) % c.dimensiune) == c.prim)
		return true;
	else return false;
}
void adauga(tip_coada* c, tip_element el)
{
	if (((c->ultim + 2) % c->dimensiune) == c->prim)
		printf("Coada este plina\n");
	else
	{
		c->ultim = (c->ultim + 1) % c->dimensiune;
		c->coada[c->ultim] = el;
	}
}
void scoate(tip_coada* c, int* er)
{
	if (vid(*c))
	{
		*er = true;
	}
	else
	{
		*er = false;
		c->prim = (c->prim + 1) % c->dimensiune;
	}
}


int main(void)
{
	tip_coada c;
	initializeaza(&c);
	tip_element x;
	int er;
	x = 5;
	adauga(&c, x);
	printf("%d", cap(c));
	x = 3;
	adauga(&c, x);
	printf("%d", cap(c));
	x = 8;
	adauga(&c, x);
	printf("%d", cap(c));
	x = 9;
	adauga(&c, x);
	printf("%d", cap(c));
	x = 10;
	adauga(&c, x);
	printf("%d", cap(c));
	x = 11;
	adauga(&c, x);
	printf("%d", cap(c));
	scoate(&c, &er);
	if (!(vid(c)))
	{
		printf("\n%d", cap(c));
	}
	scoate(&c, &er);
	if (!(vid(c)))
	{
		printf("\n%d", cap(c));
	}
	scoate(&c, &er);
	if (!(vid(c)))
	{
		printf("\n%d", cap(c));
	}


	return 0;
}