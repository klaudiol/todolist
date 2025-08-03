// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "todo.h"

int main() {
    int izbor;
    ucitajIzDatoteke();

    do {
        printf("\n--- TO-DO LIST IZBORNIK ---\n");
        printf("1. Dodaj zadatak\n");
        printf("2. Prikazi zadatke\n");
        printf("3. Azuriraj zadatak\n");
        printf("4. Obrisi zadatak\n");
        printf("5. Umetni zadatak na poziciju\n");
        printf("6. Sortiraj zadatke po prioritetu\n");
        printf("7. Pretrazi zadatke po ID-u\n");
        printf("8. Preimenuj datoteku\n");
        printf("9. Obrisi datoteku\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1: dodajZadatak(); break;
            case 2: prikaziZadatke(); break;
            case 3: azurirajZadatak(); break;
            case 4: obrisiZadatak(); break;
            case 5: umetniNaPoziciju(); break;
            case 6: sortirajZadatke(usporediZadatke); break;
            case 7: traziZadatak(); break;
            case 8: preimenujDatoteku(); break;
            case 9: obrisiDatoteku(); break;
            case 0: oslobodiMemoriju(); break;
            default: printf("Nepoznata opcija.\n");
        }

    } while (izbor != 0);

    return 0;
}
