#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

// Pokazivač na početak liste
Zadatak* glava = NULL;
int zadnjiID = 0;

// Dodaje novi zadatak
void dodajZadatak() {
    Zadatak* novi = malloc(sizeof(Zadatak));
    if (!novi) {
        printf("Greska u alokaciji memorije.\n");
        return;
    }

    novi->id = ++zadnjiID;

    printf("Unesi naziv zadatka: ");
    fgets(novi->naziv, MAX_NAZIV, stdin);
    novi->naziv[strcspn(novi->naziv, "\n")] = '\0';

    printf("Unesi opis zadatka: ");
    fgets(novi->opis, MAX_OPIS, stdin);
    novi->opis[strcspn(novi->opis, "\n")] = '\0';

    printf("Prioritet (1-Nizak, 2-Srednji, 3-Visok): ");
    int p; scanf("%d", &p); getchar();
    novi->prioritet = (Prioritet)p;

    // Novi ide na početak
    novi->sljedeci = glava;
    glava = novi;

    printf("Zadatak dodan.\n");
}

// Prikazuje sve zadatke
void prikaziZadatke() {
    Zadatak* t = glava;
    if (!t) {
        printf("Nema zadataka.\n");
        return;
    }

    while (t) {
        printf("\nID: %d\nNaziv: %s\nOpis: %s\nPrioritet: %d\n",
            t->id, t->naziv, t->opis, t->prioritet);
        t = t->sljedeci;
    }
}

// Pomoćna funkcija za pronalazak zadatka
Zadatak* nadjiZadatak(int id) {
    Zadatak* t = glava;
    while (t) {
        if (t->id == id) return t;
        t = t->sljedeci;
    }
    return NULL;
}

// Ažurira zadatak
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
    fgets(z->naziv, MAX_NAZIV, stdin);
    z->naziv[strcspn(z->naziv, "\n")] = '\0';

    printf("Novi opis: ");
    fgets(z->opis, MAX_OPIS, stdin);
    z->opis[strcspn(z->opis, "\n")] = '\0';

    printf("Novi prioritet: ");
    int p; scanf("%d", &p); getchar();
    z->prioritet = (Prioritet)p;

    printf("Zadatak azuriran.\n");
}

// Briše zadatak po ID-u
void obrisiZadatak() {
    int id;
    printf("Unesi ID za brisanje: ");
    scanf("%d", &id); getchar();

    Zadatak* tren = glava;
    Zadatak* prev = NULL;

    while (tren && tren->id != id) {
        prev = tren;
        tren = tren->sljedeci;
    }

    if (!tren) {
        printf("Zadatak nije pronadjen.\n");
        return;
    }

    if (!prev)
        glava = tren->sljedeci;
    else
        prev->sljedeci = tren->sljedeci;

    free(tren);
    printf("Zadatak obrisan.\n");
}

// Umeće zadatak na određenu poziciju
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

    novi->id = ++zadnjiID;

    printf("Unesi naziv: ");
    fgets(novi->naziv, MAX_NAZIV, stdin);
    novi->naziv[strcspn(novi->naziv, "\n")] = '\0';

    printf("Unesi opis: ");
    fgets(novi->opis, MAX_OPIS, stdin);
    novi->opis[strcspn(novi->opis, "\n")] = '\0';

    printf("Prioritet: ");
    int p; scanf("%d", &p); getchar();
    novi->prioritet = (Prioritet)p;

    if (poz == 1) {
        novi->sljedeci = glava;
        glava = novi;
    }
    else {
        Zadatak* tren = glava;
        for (int i = 1; tren && i < poz - 1; i++) {
            tren = tren->sljedeci;
        }

        if (!tren) {
            printf("Pozicija ne postoji.\n");
            free(novi);
            return;
        }

        novi->sljedeci = tren->sljedeci;
        tren->sljedeci = novi;
    }

    printf("Zadatak umetnut.\n");
}

// Sortira zadatke po prioritetu
void sortirajZadatke() {
    if (!glava || !glava->sljedeci) return;

    int n = 0;
    Zadatak* t = glava;
    while (t) { n++; t = t->sljedeci; }

    Zadatak** polje = malloc(n * sizeof(Zadatak*));
    t = glava;
    for (int i = 0; i < n; i++) {
        polje[i] = t;
        t = t->sljedeci;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (polje[i]->prioritet > polje[j]->prioritet) {
                Zadatak* temp = polje[i];
                polje[i] = polje[j];
                polje[j] = temp;
            }
        }
    }

    for (int i = 0; i < n - 1; i++) {
        polje[i]->sljedeci = polje[i + 1];
    }
    polje[n - 1]->sljedeci = NULL;
    glava = polje[0];

    free(polje);
    printf("Zadaci sortirani.\n");
}

// Traži zadatak
void traziZadatak() {
    int id;
    printf("Unesi ID za pretragu: ");
    scanf("%d", &id); getchar();

    Zadatak* z = nadjiZadatak(id);
    if (z)
        printf("Naziv: %s\nOpis: %s\nPrioritet: %d\n", z->naziv, z->opis, z->prioritet);
    else
        printf("Zadatak nije pronadjen.\n");
}

// Učitava zadatke iz datoteke
void ucitajIzDatoteke() {
    FILE* f = fopen(NAZIV_DATOTEKE, "r");

    // Ako datoteka ne postoji, kreiramo praznu
    if (!f) {
        f = fopen(NAZIV_DATOTEKE, "w");
        if (f) fclose(f);
        return;
    }

    while (!feof(f)) {
        Zadatak* novi = malloc(sizeof(Zadatak));
        if (fscanf(f, "%d;%99[^;];%199[^;];%d\n", &novi->id, novi->naziv, novi->opis, (int*)&novi->prioritet) == 4) {
            novi->sljedeci = glava;
            glava = novi;
            if (novi->id > zadnjiID)
                zadnjiID = novi->id;
        }
        else {
            free(novi);
            break;
        }
    }

    fclose(f);
}

// Sprema zadatke u datoteku
void spremiUDatoteku() {
    FILE* f = fopen(NAZIV_DATOTEKE, "w");
    if (!f) {
        printf("Ne mogu otvoriti datoteku za pisanje.\n");
        return;
    }

    Zadatak* t = glava;
    while (t) {
        fprintf(f, "%d;%s;%s;%d\n", t->id, t->naziv, t->opis, t->prioritet);
        t = t->sljedeci;
    }

    fclose(f);
}

// Briše sve iz memorije
void oslobodiMemoriju() {
    Zadatak* t = glava;
    while (t) {
        Zadatak* zaBrisanje = t;
        t = t->sljedeci;
        free(zaBrisanje);
    }
}