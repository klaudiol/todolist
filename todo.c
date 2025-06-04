#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

// Glava liste zadataka
Zadatak* glava = NULL;
int zadnjiID = 0;

// Dodavanje novog zadatka
void dodajZadatak() {
    Zadatak* novi = malloc(sizeof(Zadatak));
    if (!novi) return;

    (*novi).id = ++zadnjiID;

    printf("Unesi naziv zadatka: ");
    fgets((*novi).naziv, MAX_NAZIV, stdin);
    (*novi).naziv[strcspn((*novi).naziv, "\n")] = '\0';

    printf("Unesi opis zadatka: ");
    fgets((*novi).opis, MAX_OPIS, stdin);
    (*novi).opis[strcspn((*novi).opis, "\n")] = '\0';

    printf("Prioritet (1-Nizak, 2-Srednji, 3-Visok): ");
    int p; scanf("%d", &p); getchar();
    (*novi).prioritet = (Prioritet)p;

    (*novi).sljedeci = glava;
    glava = novi;

    printf("Zadatak dodan.\n");
}

// Rekurzivni ispis zadataka
void ispisiRekurzivno(Zadatak* z) {
    if (!z) return;

    printf("\nID: %d\nNaziv: %s\nOpis: %s\nPrioritet: %d\n",
        (*z).id, (*z).naziv, (*z).opis, (*z).prioritet);

    ispisiRekurzivno((*z).sljedeci);
}

// Ispis svih zadataka
void prikaziZadatke() {
    if (!glava) {
        printf("Nema zadataka.\n");
        return;
    }

    ispisiRekurzivno(glava);
}

// Trazi zadatak po ID
Zadatak* nadjiZadatak(int id) {
    Zadatak* p = glava;
    while (p) {
        if ((*p).id == id) return p;
        p = (*p).sljedeci;
    }
    return NULL;
}

// Azuriranje zadatka
void azurirajZadatak() {
    int id;
    printf("Unesi ID zadatka: ");
    scanf("%d", &id); getchar();

    Zadatak* z = nadjiZadatak(id);
    if (!z) {
        printf("Zadatak nije pronadjen.\n");
        return;
    }

    printf("Novi naziv: ");
    fgets((*z).naziv, MAX_NAZIV, stdin);
    (*z).naziv[strcspn((*z).naziv, "\n")] = '\0';

    printf("Novi opis: ");
    fgets((*z).opis, MAX_OPIS, stdin);
    (*z).opis[strcspn((*z).opis, "\n")] = '\0';

    printf("Novi prioritet: ");
    int p; scanf("%d", &p); getchar();
    (*z).prioritet = (Prioritet)p;

    printf("Zadatak azuriran.\n");
}

// Brisanje zadatka
void obrisiZadatak() {
    int id;
    printf("Unesi ID za brisanje: ");
    scanf("%d", &id); getchar();

    Zadatak* p = glava;
    Zadatak* prethodni = NULL;

    while (p && (*p).id != id) {
        prethodni = p;
        p = (*p).sljedeci;
    }

    if (!p) {
        printf("Zadatak nije pronadjen.\n");
        return;
    }

    if (!prethodni) glava = (*p).sljedeci;
    else (*prethodni).sljedeci = (*p).sljedeci;

    free(p);
    printf("Zadatak obrisan.\n");
}

// Umetanje na odredjenu poziciju
void umetniNaPoziciju() {
    int poz;
    printf("Unesi poziciju: ");
    scanf("%d", &poz); getchar();

    if (poz < 1) {
        printf("Neispravna pozicija.\n");
        return;
    }

    Zadatak* novi = malloc(sizeof(Zadatak));
    if (!novi) return;

    (*novi).id = ++zadnjiID;

    printf("Unesi naziv: ");
    fgets((*novi).naziv, MAX_NAZIV, stdin);
    (*novi).naziv[strcspn((*novi).naziv, "\n")] = '\0';

    printf("Unesi opis: ");
    fgets((*novi).opis, MAX_OPIS, stdin);
    (*novi).opis[strcspn((*novi).opis, "\n")] = '\0';

    printf("Prioritet: ");
    int p; scanf("%d", &p); getchar();
    (*novi).prioritet = (Prioritet)p;

    if (poz == 1) {
        (*novi).sljedeci = glava;
        glava = novi;
    }
    else {
        Zadatak* t = glava;
        for (int i = 1; t && i < poz - 1; i++) t = (*t).sljedeci;

        if (!t) {
            printf("Pozicija ne postoji.\n");
            free(novi);
            return;
        }

        (*novi).sljedeci = (*t).sljedeci;
        (*t).sljedeci = novi;
    }

    printf("Zadatak umetnut.\n");
}

// Funkcija za usporedbu po prioritetu
int usporediPoPrioritetu(Zadatak* a, Zadatak* b) {
    return (*a).prioritet - (*b).prioritet;
}

// Sortiranje zadataka (okazivač na funkciju za usporedbu)
void sortirajZadatke(usporedbaFunkcija f) {
    if (!glava || !(*glava).sljedeci) return;

    int n = 0;
    Zadatak* p = glava;
    while (p) { n++; p = (*p).sljedeci; }

    Zadatak** niz = malloc(n * sizeof(Zadatak*));
    p = glava;
    for (int i = 0; i < n; i++) {
        niz[i] = p;
        p = (*p).sljedeci;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (f(niz[i], niz[j]) > 0) {
                Zadatak* temp = niz[i];
                niz[i] = niz[j];
                niz[j] = temp;
            }
        }
    }

    for (int i = 0; i < n - 1; i++)
        (*niz[i]).sljedeci = niz[i + 1];
    (*niz[n - 1]).sljedeci = NULL;
    glava = niz[0];

    free(niz);
    printf("Zadaci sortirani.\n");
}

// Pretraga po ID
void traziZadatak() {
    int id;
    printf("Unesi ID za pretragu: ");
    scanf("%d", &id); getchar();

    Zadatak* z = nadjiZadatak(id);
    if (z)
        printf("Naziv: %s\nOpis: %s\nPrioritet: %d\n", (*z).naziv, (*z).opis, (*z).prioritet);
    else
        printf("Zadatak nije pronadjen.\n");
}

// Ucitavanje iz datoteke
void ucitajIzDatoteke() {
    FILE* f = fopen(NAZIV_DATOTEKE, "r");
    if (!f) return;

    Zadatak temp;
    while (fread(&temp, sizeof(Zadatak), 1, f)) {
        Zadatak* novi = malloc(sizeof(Zadatak));
        *novi = temp;
        (*novi).sljedeci = glava;
        glava = novi;

        if ((*novi).id > zadnjiID)
            zadnjiID = (*novi).id;
    }

    fclose(f);
}

// Spremanje u tekstualnu datoteku
void spremiUDatoteku() {
    FILE* f = fopen(NAZIV_DATOTEKE, "w");
    if (!f) {
        printf("Greška pri otvaranju datoteke!\n");
        return;
    }

    Zadatak* p = glava;
    while (p) {
        fprintf(f, "ID: %d\n", (*p).id);
        fprintf(f, "Naziv: %s\n", (*p).naziv);
        fprintf(f, "Opis: %s\n", (*p).opis);
        fprintf(f, "Prioritet: %d\n", (*p).prioritet);
        fprintf(f, "-----------------------------\n");

        p = (*p).sljedeci;
    }

    fclose(f);
    printf("Zadaci spremljeni u tekstualnu datoteku.\n");
}

// Oslobodi memoriju
void oslobodiMemoriju() {
    while (glava) {
        Zadatak* zaBrisanje = glava;
        glava = (*glava).sljedeci;
        free(zaBrisanje);
    }
}
