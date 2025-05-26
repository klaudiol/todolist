#define _CRT_SECURE_NO_WARNINGS

#ifndef TODO_H
#define TODO_H

// Maksimalne duljine stringova
#define MAX_NAZIV 100
#define MAX_OPIS 200

// Naziv datoteke u koju spremamo zadatke
#define NAZIV_DATOTEKE "zadaci.txt"

// Nabrajanje prioriteta
typedef enum {
    NIZAK = 1,
    SREDNJI,
    VISOK
} Prioritet;

// Struktura za jedan zadatak
typedef struct Zadatak {
    int id;
    char naziv[MAX_NAZIV];
    char opis[MAX_OPIS];
    Prioritet prioritet;
    struct Zadatak* sljedeci;
} Zadatak;

// Deklaracije funkcija
void dodajZadatak();
void prikaziZadatke();
void azurirajZadatak();
void obrisiZadatak();
void umetniNaPoziciju();
void sortirajZadatke();
void traziZadatak();
void spremiUDatoteku();
void ucitajIzDatoteke();
void oslobodiMemoriju();

#endif
