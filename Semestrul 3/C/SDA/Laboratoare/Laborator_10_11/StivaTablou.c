#include <stdio.h>
#include <stdlib.h>
typedef unsigned boolean;
#define true (1)
#define false (0)
#define lungime_maxima 5
typedef int tip_element;
typedef struct {
	tip_element elemente[lungime_maxima];
	int varf;
}tip_stiva;
//varianta implementare stiva care porneste de la lungime maxima si adauga elemente spre 0

void initializeaza(tip_stiva* s)
{
	s->varf = lungime_maxima;
} /*initializeaza*/

boolean stivid(tip_stiva s)
{
	boolean stivid_result;
	if (s.varf >= lungime_maxima)
		stivid_result = true;
	else stivid_result = false;
	return stivid_result;
} /*stivid*/

tip_element varfst(tip_stiva* s)
{
	boolean er;
	tip_element varfst_result;
	if (stivid(*s)) {
		er = true;
		printf("stiva este vida");
	}
	else
		varfst_result = s->elemente[s->varf];
	return varfst_result;
}

void pop(tip_stiva* s, tip_element* x)
{
	boolean er;
	if (stivid(*s)) {
		er = true;
		printf("stiva este vida");
	}
	else {
		*x = s->elemente[s->varf];
		s->varf = s->varf + 1;
	}
} /*pop*/

void push(tip_element x, tip_stiva* s)
{
	boolean er;
	if (s->varf == 0) {
		er = true;
		printf("stiva este plina");
	}
	else {
		s->varf = s->varf - 1;
		s->elemente[s->varf] = x;
	}
}/*push*/

int main(void)
{
	tip_stiva s;
	initializeaza(&s);
	push(1, &s);
	push(2, &s);
	push(3, &s);
	push(4, &s);
	push(5, &s);
	push(6, &s);
	int i, j;
	for (i = 0; i <= lungime_maxima; i++)
	{
		pop(&s, &j);
		printf("\n %d", j);
	}
	return 0;
}