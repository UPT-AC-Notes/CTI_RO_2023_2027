#include <stdio.h>
#include <stdlib.h>
typedef int tip_info;
typedef struct {
	int cheie;
	tip_info info;
	struct tip_nod* urm;
} tip_nod;
typedef tip_nod* tip_lista;
tip_lista prim = NULL;
tip_lista ultim = NULL;
tip_lista insertie_fata(int cheie, tip_info info)
{
	tip_nod* q; //noul nod
	q = (tip_nod*)malloc(sizeof(tip_nod)); // aloc spatiu pentru noul nod
	if (q) //daca s-a alocat spatiu cu succes
	{
		q->cheie = cheie;
		q->info = info; //asignez valorile primite ca parametru
		q->urm = prim;  //facem legatura catre inceputul listei
		if (prim == NULL)
			ultim = q;
		prim = q;       //noul nod devine primul nod;
	}
	return prim;
}
tip_lista insertie_final(int cheie, tip_info info)
{
	tip_nod* q; //noul nod
	q = (tip_nod*)malloc(sizeof(tip_nod)); // aloc spatiu pentru noul nod
	if (q) //daca s-a alocat spatiu cu succes
	{
		q->cheie = cheie;
		q->info = info; //asignez valorile primite ca parametru
		q->urm = NULL;
		if (ultim == NULL) //daca lista a fost vida
			prim = q;
		else ultim->urm = q;       //ultim indica spre q;
		ultim = q;			 //q devine ultimul nod	
	}
	return prim;
}

tip_lista insertie_final2(int cheie, tip_info info)
{
	tip_nod* q; //noul nod
	q = (tip_nod*)malloc(sizeof(tip_nod)); // aloc spatiu pentru noul nod
	if (q) //daca s-a alocat spatiu cu succes
	{
		q->cheie = cheie;
		q->info = info; //asignez valorile primite ca parametru
		q->urm = NULL;
	}
	tip_nod* p;
	if (prim == NULL)	//daca lista era vida
		prim = q;
	else {
		for (p = prim; p->urm != NULL; p = p->urm); //parcurg lista pana la ultimul element
		p->urm = q;
	}
	return prim;
}

tip_nod* cauta(int cheie)
{
	tip_nod* p;
	//cat timp nu am gasit cheia si nu am ajuns la capatul listei avansez in lista
	for (p = prim; (p != NULL) && (p->cheie != cheie); p = p->urm);
	//atentie: conteaza ordinea celor doua contitii, deoarece in C expresiile logice se evalueaza in scurtcircuit
	return p; //functia returneaza NULL in caz ca nu a gasit cheia
}

tip_lista insertie_dupa(int cheie, tip_info info, tip_nod* p)
{
	tip_nod* q; //noul nod
	if (p == NULL) //daca se doreste de fapt insertie in fata listei
		prim = insertie_fata(cheie, info);
	else if (p == ultim)	//daca se doreste de fapt adaugare la sfarsit
		prim = insertie_final(cheie, info);
	else
	{
		q = (tip_nod*)malloc(sizeof(tip_nod)); // aloc spatiu pentru noul nod
		if (q) //daca s-a alocat spatiu cu succes
		{
			q->cheie = cheie;
			q->info = info; //asignez valorile primite ca parametru
			q->urm = p->urm; //fac legatura de la noul nod la succesorul sau  
		}
		p->urm = q;          //fac legatura catre noul nod
	}
	return prim;
}

int main()
{
	prim = insertie_fata(1, 1);
	prim = insertie_fata(2, 2);
	prim = insertie_fata(3, 3);
	prim = insertie_final(4, 4);
	prim = insertie_final(5, 5);
	prim = insertie_dupa(6, 6, cauta(3));
	prim = insertie_dupa(7, 7, cauta(5));
	prim = insertie_dupa(8, 8, cauta(9));
	return 0;

}