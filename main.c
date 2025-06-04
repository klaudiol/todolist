#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "todo.h"

int main() {
    int izbor;

    // Ucitaj zadatke iz datoteke
    ucitajIzDatoteke();

    do {
        // Glavni izbornik
        printf("\n==== To-Do Lista ====\n");
        printf("1. Dodaj zadatak\n");
        printf("2. Prikazi zadatke\n");
        printf("3. Azuriraj zadatak\n");
        printf("4. Obrisi zadatak\n");
        printf("5. Umetni zadatak na poziciju\n");
        printf("6. Sortiraj po prioritetu\n");
        printf("7. Pretrazi po ID\n");
        printf("8. Spremi u datoteku\n");
        printf("0. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor); getchar();

        switch (izbor) {
        case 1: dodajZadatak(); break;
        case 2: prikaziZadatke(); break;
        case 3: azurirajZadatak(); break;
        case 4: obrisiZadatak(); break;
        case 5: umetniNaPoziciju(); break;
        case 6: sortirajZadatke(usporediPoPrioritetu); break;
        case 7: traziZadatak(); break;
        case 8: spremiUDatoteku(); break;
        case 0: spremiUDatoteku(); oslobodiMemoriju(); printf("Izlaz.\n"); break;
        default: printf("Neispravan unos.\n");
        }

    } while (izbor != 0);

    return 0;
}
