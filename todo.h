// todo.h
#define _CRT_SECURE_NO_WARNINGS
#ifndef TODO_H
#define TODO_H

#define NAZIV_DATOTEKE "zadaci.txt"

#include <stdio.h>

// Enum za prioritet zadatka
typedef enum { NIZAK = 1, SREDNJI, VISOK } Prioritet;

// Struktura za zadatak
typedef struct Zadatak {
    int id;
    char naziv[50];
    char opis[100];
    Prioritet prioritet;
    struct Zadatak* sljedeci;
} Zadatak;

// Globalni pokazivač na početak liste
extern Zadatak* glava;

// Deklaracije funkcija
void ucitajIzDatoteke();
void spremiUDatoteku();
void dodajZadatak();
void prikaziZadatke();
void azurirajZadatak();
void obrisiZadatak();
void umetniNaPoziciju();
int usporediZadatke(const void*, const void*);
void sortirajZadatke(int (*)(const void*, const void*));
void traziZadatak();
void oslobodiMemoriju();
void preimenujDatoteku();
void obrisiDatoteku();

#endif
