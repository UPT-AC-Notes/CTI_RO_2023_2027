/*
    Se consideră un tablou de structuri de forma:

            struct student {
                char nume[35];
                int varsta;
                int premii; // 1 dacă studentul a fost premiat, 0 dacă nu
            };

    Fiind dat tabloul cu dimensiunea N, se cere implementarea a câte o funcție pentru:

    a) Mutarea, într-un mod cât mai eficient, pe primele poziții din vector a studenților care au primit premii.

    b) Sortarea în ordine invers alfabetică după nume, a studenților premiați (doar studenții premiați vor fi sortați).

    Se consideră un exemplu de tablou cu minimum 5 astfel de studenți și se va exemplifica cum va arăta tabloul după apelul fiecărei funcții.
*/

#include <stdio.h>
#include <string.h>

typedef struct student {
	char nume[35];
	int varsta;
	int premii; // 1 dacă studentul a fost premiat, 0 dacă nu
} Student_T;

#define N 5

void citireDateDinFisier(Student_T* studenti, FILE *fin) {
    for (int i = 0; i < N; i++) {
		fscanf(fin, "%s %d %d", studenti[i].nume, &studenti[i].varsta, &studenti[i].premii);
    }
}

void afisareDate(Student_T* studenti) {
	for (int i = 0; i < N; i++) {
		printf("Nume : %s -> Varsta : %d -> Premii : %d\n", studenti[i].nume, studenti[i].varsta, studenti[i].premii);
	}

	printf("---------------------------------\n");
}

void swap(Student_T* a, Student_T* b) {
    Student_T tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int cerintaA_mutareStudentiPremiati(Student_T* studenti) {
    int index = 0;

    for (int i = 0; i < N; i++) {
        if (studenti[i].premii == 1) {
            if (index != i) {
                swap(&studenti[index], &studenti[i]);
            }

            index++;
        }
    }

    return index;
}

void cerintaB_sortareStudentiPremiati(Student_T* studenti, int prim, int ultim) {
    int stanga = prim + 1;
    int dreapta = ultim;

    swap(&studenti[prim], &studenti[(prim + ultim) / 2]);

    Student_T pivot = studenti[prim];

    while (stanga <= dreapta) {

        while (stanga <= ultim && strcmp(studenti[stanga].nume, pivot.nume) > 0) {
            stanga++;
        }

        while (dreapta > prim && strcmp(studenti[dreapta].nume, pivot.nume) < 0) {
            dreapta--;
        }

        if (stanga <= dreapta) {
            swap(&studenti[stanga], &studenti[dreapta]);
            stanga++;
            dreapta--;
        }
        else {
            stanga++;
        }
    }

	swap(&studenti[prim], &studenti[dreapta]);

    if (prim < dreapta - 1) {
		cerintaB_sortareStudentiPremiati(studenti, prim, dreapta - 1);
    }

	if (dreapta + 1 < ultim) {
		cerintaB_sortareStudentiPremiati(studenti, dreapta + 1, ultim);
	}

}



int main(int argc, char *argv[]) {
    if (argc != 2) {
		printf("Introduceti numele fisierului de intrare ca argument in linia de comanda!\n");
		return 1;
    }

    Student_T studenti[N];

    FILE* fin = fopen(argv[1], "r");

    if (fin == NULL) {
        printf("Fisierul nu a putut fi deschis!\n");
        return 1;
    }

	citireDateDinFisier(studenti, fin);
	printf("Datele citite din fisier sunt : \n");
	afisareDate(studenti);

	int nrStudentiPremiati = cerintaA_mutareStudentiPremiati(studenti);
	printf("Cerinta A : \n");
	afisareDate(studenti);

	cerintaB_sortareStudentiPremiati(studenti, 0, nrStudentiPremiati - 1);

	printf("Cerinta B : \n");
	afisareDate(studenti);


	fclose(fin);

    return 0;
}