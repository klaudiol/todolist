#define _CRT_SECURE_NO_WARNINGS

#ifndef TODO_H
#define TODO_H

#define MAX_NAZIV 100
#define MAX_OPIS 200
#define NAZIV_DATOTEKE "zadaci.txt"

typedef enum {
    NIZAK = 1,
    SREDNJI,
    VISOK
} Prioritet;

typedef struct Zadatak {
    int id;
    char naziv[MAX_NAZIV];
    char opis[MAX_OPIS];
    Prioritet prioritet;
    struct Zadatak* sljedeci;
} Zadatak;

// Pokazivač na funkciju za usporedbu
typedef int (*usporedbaFunkcija)(Zadatak*, Zadatak*);

void dodajZadatak();
void prikaziZadatke();
void ispisiRekurzivno(Zadatak* z);
Zadatak* nadjiZadatak(int id);
void azurirajZadatak();
void obrisiZadatak();
void umetniNaPoziciju();
void sortirajZadatke(usporedbaFunkcija f);
int usporediPoPrioritetu(Zadatak* a, Zadatak* b);
void traziZadatak();
void spremiUDatoteku();
void ucitajIzDatoteke();
void oslobodiMemoriju();

#endif