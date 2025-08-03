// todo.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "todo.h"

// Glava povezane liste
Zadatak* glava = NULL;

// Funkcija koja automatski generira sljedeći ID
static int dajSljedeciID() {
    int maxID = 0;
    Zadatak* p = glava;
    while (p) {
        if (p->id > maxID)
            maxID = p->id;
        p = p->sljedeci;
    }
    return maxID + 1;
}

// Učitavanje zadataka iz .txt datoteke
void ucitajIzDatoteke() {
    FILE* dat = fopen(NAZIV_DATOTEKE, "r");
    if (!dat) return;

    char linija[200];
    while (fgets(linija, sizeof(linija), dat)) {
        Zadatak* novi = (Zadatak*)malloc(sizeof(Zadatak));
        if (!novi) {
            perror("malloc");
            fclose(dat);
            return;
        }

        // Parsiramo redak iz datoteke
        if (sscanf(linija, "%d | %49[^|]| %99[^|]| %d", &novi->id, novi->naziv, novi->opis, (int*)&novi->prioritet) == 4) {
            novi->sljedeci = glava;
            glava = novi;
        } else {
            free(novi);
        }
    }

    if (ferror(dat)) perror("Greska pri citanju datoteke");

    fclose(dat);
}

// Spremanje liste zadataka u .txt datoteku
void spremiUDatoteku() {
    FILE* dat = fopen(NAZIV_DATOTEKE, "w");
    if (!dat) {
        perror("fopen");
        return;
    }

    Zadatak* tren = glava;
    while (tren) {
        fseek(dat, 0, SEEK_CUR); // pozicioniranje
        fprintf(dat, "%d | %s| %s| %d\n", tren->id, tren->naziv, tren->opis, tren->prioritet);
        tren = tren->sljedeci;
    }

    if (ferror(dat)) perror("Greska pri pisanju u datoteku");

    fclose(dat);
}

// Dodavanje novog zadatka
void dodajZadatak() {
    Zadatak* novi = (Zadatak*)malloc(sizeof(Zadatak));
    if (!novi) return;

    novi->id = dajSljedeciID();

    printf("Unesite naziv: ");
    scanf(" %49[^\n]", novi->naziv);
    printf("Unesite opis: ");
    scanf(" %99[^\n]", novi->opis);
    printf("Unesite prioritet (1-nizak, 2-srednji, 3-visok): ");
    scanf("%d", (int*)&novi->prioritet);

    novi->sljedeci = glava;
    glava = novi;

    spremiUDatoteku(); // automatsko spremanje
}

// Prikaz svih zadataka
void prikaziZadatke() {
    Zadatak* tren = glava;
    while (tren) {
        printf("ID: %d | Naziv: %s | Opis: %s | Prioritet: %d\n", tren->id, tren->naziv, tren->opis, tren->prioritet);
        tren = tren->sljedeci;
    }
}

// Ažuriranje zadatka po ID-u
void azurirajZadatak() {
    int id;
    printf("Unesite ID za azuriranje: ");
    scanf("%d", &id);
    Zadatak* tren = glava;
    while (tren) {
        if (tren->id == id) {
            printf("Novi naziv: "); scanf(" %49[^\n]", tren->naziv);
            printf("Novi opis: "); scanf(" %99[^\n]", tren->opis);
            printf("Novi prioritet: "); scanf("%d", (int*)&tren->prioritet);
            spremiUDatoteku();
            return;
        }
        tren = tren->sljedeci;
    }
}

// Brisanje zadatka po ID-u
void obrisiZadatak() {
    int id;
    printf("Unesite ID za brisanje: ");
    scanf("%d", &id);
    Zadatak* tren = glava;
    Zadatak* prev = NULL;
    while (tren) {
        if (tren->id == id) {
            if (prev) prev->sljedeci = tren->sljedeci;
            else glava = tren->sljedeci;
            free(tren);
            spremiUDatoteku();
            return;
        }
        prev = tren;
        tren = tren->sljedeci;
    }
}

// Umetanje zadatka na određenu poziciju
void umetniNaPoziciju() {
    int poz;
    printf("Na koju poziciju zelite umetnuti: ");
    scanf("%d", &poz);
    Zadatak* novi = (Zadatak*)malloc(sizeof(Zadatak));
    if (!novi) return;

    novi->id = dajSljedeciID();
    printf("Unesite naziv: ");
    scanf(" %49[^\n]", novi->naziv);
    printf("Unesite opis: ");
    scanf(" %99[^\n]", novi->opis);
    printf("Unesite prioritet: ");
    scanf("%d", (int*)&novi->prioritet);

    if (poz == 0 || !glava) {
        novi->sljedeci = glava;
        glava = novi;
    } else {
        Zadatak* tren = glava;
        for (int i = 0; i < poz - 1 && tren->sljedeci; i++) tren = tren->sljedeci;
        novi->sljedeci = tren->sljedeci;
        tren->sljedeci = novi;
    }
    spremiUDatoteku();
}

// Funkcija za usporedbu zadataka po prioritetu (za sortiranje)
int usporediZadatke(const void* a, const void* b) {
    Zadatak* z1 = *(Zadatak**)a;
    Zadatak* z2 = *(Zadatak**)b;
    return z1->prioritet - z2->prioritet;
}

// Sortiranje zadataka pomoću qsort
void sortirajZadatke(int (*usporedi)(const void*, const void*)) {
    int n = 0;
    Zadatak* tren = glava;
    while (tren) { n++; tren = tren->sljedeci; }

    if (n < 2) return;

    Zadatak** niz = calloc(n, sizeof(Zadatak*));
    if (!niz) return;

    tren = glava;
    for (int i = 0; i < n; i++) {
        niz[i] = tren;
        tren = tren->sljedeci;
    }

    qsort(niz, n, sizeof(Zadatak*), usporedi);

    for (int i = 0; i < n - 1; i++) niz[i]->sljedeci = niz[i + 1];
    niz[n - 1]->sljedeci = NULL;
    glava = niz[0];

    free(niz);
    spremiUDatoteku();
}

// Pretraga zadatka po ID-u
void traziZadatak() {
    int id;
    printf("Unesite ID za pretragu: ");
    scanf("%d", &id);

    Zadatak* tren = glava;
    while (tren) {
        if (tren->id == id) {
            printf("Pronadjen: %s - %s\n", tren->naziv, tren->opis);
            return;
        }
        tren = tren->sljedeci;
    }
    printf("Zadatak nije pronadjen.\n");
}

// Oslobađanje dinamički alocirane memorije
void oslobodiMemoriju() {
    Zadatak* tren = glava;
    while (tren) {
        Zadatak* zaBrisanje = tren;
        tren = tren->sljedeci;
        free(zaBrisanje);
    }
    glava = NULL;
}

// Preimenovanje datoteke pomoću rename()
void preimenujDatoteku() {
    char novoIme[100];
    printf("Unesite novo ime za datoteku: ");
    scanf(" %99[^\n]", novoIme);
    if (rename(NAZIV_DATOTEKE, novoIme) != 0) perror("rename");
    else printf("Datoteka preimenovana.\n");
}

// Brisanje datoteke pomoću remove()
void obrisiDatoteku() {
    if (remove(NAZIV_DATOTEKE) != 0) perror("remove");
    else printf("Datoteka obrisana.\n");
}
