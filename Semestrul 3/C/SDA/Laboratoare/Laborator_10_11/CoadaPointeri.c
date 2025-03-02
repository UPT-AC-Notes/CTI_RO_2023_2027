#include <stdio.h>
#include <stdlib.h>
typedef unsigned boolean;
#define true (1)
#define false (0)
#define lungime_maxima 5
/*Exemplu de implementare a TDA Coada cu ajutorul TDA Lista (setul 1 de operatori).*/
typedef int tip_element;
typedef struct
{
	tip_element element;
	struct tip_nod* urm;
}tip_nod;

typedef struct {
	tip_nod* prim;
	tip_nod* ultim;
}tip_coada;


void initializeaza(tip_coada* c)
{
	c->prim = NULL;
	c->ultim = NULL; /*coada este vida,
					 nici prim nici ultim nu indica spre vreun element*/
}/*initializeaza*/

boolean vid(tip_coada c)
{
	if (c.prim == NULL)
		return true;
	else return false;
}/*vid*/

tip_element cap(tip_coada c)
{
	return c.prim->element;
}/*cap*/

void adauga(tip_coada* c, tip_element x)
{
	tip_nod* nou = (tip_nod*)malloc(sizeof(tip_nod));
	if (nou) /*daca s-a alocat spatiu pentru nou cu succes*/
	{
		nou->element = x;
		nou->urm = NULL;
		if (c->prim == NULL) /* daca lista este vida, noul nod este si primul si ultimul */
		{
			c->prim = nou;
			c->ultim = nou;
		}
		else {
			c->ultim->urm = nou; /*se adauga un nod nou la sfarsitul cozii*/
			c->ultim = c->ultim->urm; /*actualizam ultimul element*/
		}
	}
}/*adauga*/

void scoate(tip_coada* c, int* er)
{
	if (vid(*c))
		*er = true;// coada este vida, nu se poate face suprimarea
	else
	{
		*er = false;
		c->prim = c->prim->urm;
	}
}/*scoate*/


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