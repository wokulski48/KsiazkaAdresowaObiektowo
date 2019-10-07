#ifndef PLIKZADRESATAMI_H
#define PLIKZADRESATAMI_H

#include <iostream>
#include <vector>

#include "Adresat.h"
#include "UzytkownikMenadzer.h"

using namespace std;

class PlikZAdresatami
{
    const string nazwaPlikuZAdresatami;

    int pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami);
    Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami);

public:
    PlikZAdresatami(string NAZWAPLIKUZUZADRESATAMI) : nazwaPlikuZAdresatami(NAZWAPLIKUZUZADRESATAMI) {};
    vector <Adresat> wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika);
};

#endif
