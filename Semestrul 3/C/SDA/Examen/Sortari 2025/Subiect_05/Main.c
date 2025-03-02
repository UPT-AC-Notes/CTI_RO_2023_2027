/*
		Se consideră un tablou de structuri de forma:
				struct film {
                char nume[35];
                int an;
                int premii; // 1 dacă filmul a fost premiat, 0 dacă nu
            };

		Fiind dat tabloul cu dimensiunea N, se cere implementarea a câte o funcție pentru:

        a) Mutarea, într-un mod cât mai eficient, pe primele poziții din vector a filmelor care au primit premii.

        b) Sortarea în ordine invers alfabetică după nume, a filmelor premiate (doar filmele premiate vor fi sortate).

        Se consideră un exemplu de tablou cu minimum 5 astfel de filme și se va exemplifica cum va arăta tabloul după apelul fiecărei funcții.

*/

#include <stdio.h>
#include <string.h>

typedef struct film {
    char nume[35];
    int an;
    int premii; // 1 dacă filmul a fost premiat, 0 dacă nu
} Film_T;

#define N 5 


void citireDateDinFisier(Film_T* filme, FILE* fin) {
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%s %d %d", filme[i].nume, &filme[i].an, &filme[i].premii);
    }
}

void afisareDate(Film_T* filme) {
    for (int i = 0; i < N; i++) {
        printf("Nume: %s -> An: %d -> Premii: %d\n", filme[i].nume, filme[i].an, filme[i].premii);
    }
    printf("---------------------------------\n");
}

void swap(Film_T* a, Film_T* b) {
    Film_T tmp = *a;
    *a = *b;
    *b = tmp;
}

int cerintaA_mutareFilmePremiate(Film_T* filme) {
    int index = 0;

    for (int i = 0; i < N; i++) {
        if (filme[i].premii == 1) {
            if (index != i) {
                swap(&filme[index], &filme[i]);
            }
            index++;
        }
    }

    return index; 
}

void cerintaB_sortareFilmePremiate(Film_T* filme, int prim, int ultim) {
    int stanga = prim + 1;
    int dreapta = ultim;

    swap(&filme[prim], &filme[(prim + ultim) / 2]); 

    Film_T pivot = filme[prim];

    while (stanga <= dreapta) {
       
        while (stanga <= ultim && strcmp(filme[stanga].nume, pivot.nume) > 0) {
            stanga++;
        }

        while (dreapta >= prim && strcmp(filme[dreapta].nume, pivot.nume) < 0) {
            dreapta--;
        }

        if (stanga <= dreapta) {
            swap(&filme[stanga], &filme[dreapta]);
            stanga++;
            dreapta--;
        }
        else {
            stanga++;
        }
    }

    swap(&filme[prim], &filme[dreapta]);

    
    if (prim < dreapta - 1) {
        cerintaB_sortareFilmePremiate(filme, prim, dreapta - 1);
    }

    if (dreapta + 1 < ultim) {
        cerintaB_sortareFilmePremiate(filme, dreapta + 1, ultim);
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect ussage!\n");
        return 1;
    }

    Film_T filme[N]; 

    FILE* fin = fopen(argv[1], "r");

    if (fin == NULL) {
        printf("Fisierul nu a putut fi deschis!\n");
        return 1;
    }

    citireDateDinFisier(filme, fin);
    printf("Datele initiale:\n");
    afisareDate(filme);

    int nrFilmePremiate = cerintaA_mutareFilmePremiate(filme);
    printf("Cerinta A:\n");
    afisareDate(filme);

    cerintaB_sortareFilmePremiate(filme, 0, nrFilmePremiate - 1);
    printf("Cerinta B:\n");
    afisareDate(filme);

    fclose(fin);

    return 0;
}
