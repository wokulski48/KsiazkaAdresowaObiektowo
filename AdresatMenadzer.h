#ifndef ADRESATMENADZER_H
#define ADRESATMENADZER_H

#include <iostream>
#include <vector>
#include <limits>

#include "Adresat.h"
#include "PlikZAdresatami.h"

using namespace std;

class AdresatMenadzer
{
    vector <Adresat> adresaci;
    vector <Adresat> *w_adresaci;

    PlikZAdresatami plikZAdresatami;

    Adresat podajDaneNowegoAdresata(int idZalogowanegoUzytkownika, int idOstatniegoAdresata);
    void wyswietlDaneAdresata(Adresat adresat);

public:
    void wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika);
    int dodajAdresata(int idZalogowanegoUzytkownika, int idOstatniegoAdresata);
    int pobierzIdOstatniegoAdresata();
    void wyswietlWszystkichAdresatow();
    vector <Adresat>* pobierzAdresaci();
    void ustawIdOstatniegoAdresata(int noweIdOstatniegoAdresata);
    void edytujAdresata();
    void usunAdresata(int idZalogowanegoUzytkownika);
    void wyszukajPoImieniu();
    void wyszukajPoNazwisku();
};

#endif
