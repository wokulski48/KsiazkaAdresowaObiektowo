#ifndef PLIKZADRESATAMI_H
#define PLIKZADRESATAMI_H

#include <iostream>
#include <vector>

#include "Adresat.h"
#include "UzytkownikMenadzer.h"

using namespace std;

class PlikZAdresatami
{
    const string nazwaPlikuZAdresatami = "bazaDanychAdresatow.txt";

    int idOstatniegoAdresata = 0;

    int pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami);
    int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami);
    Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami);
    string zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat);
    bool czyPlikJestPusty(fstream &plikTekstowy);
    int podajPozycjeZnakuRozdzialuIdAdresata(string pobranaLiniaTekstuZBazyDanych);

public:
    vector <Adresat> wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika);
    int pobierzIdOstatniegoAdresata();
    void dopiszAdresataDoPliku(Adresat adresat);
    void ustawIdOstatniegoAdresata(int noweIdOstatniegoAdresata);
    void zapiszBazeDanychAdresatow(int idEdytowanegoAdresata, int typOperacji, vector <Adresat> adresaci);
};

#endif
