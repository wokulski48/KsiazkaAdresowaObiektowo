#include <iostream>

#include "KsiazkaAdresowa.h"

using namespace std;

int main()
{
    KsiazkaAdresowa ksiazkaAdresowa("Uzytkownicy.txt", "Adresaci.txt");

    //ksiazkaAdresowa.rejestracjaUzytkownika();
    //ksiazkaAdresowa.rejestracjaUzytkownika();

    //ksiazkaAdresowa.wypiszWszystkichUzytkownikow();

    //ksiazkaAdresowa.logowanieUzytkownika();

    //ksiazkaAdresowa.zmianaHaslaZalogowanegoUzytkownika();

    //ksiazkaAdresowa.wylogujUzytkownika();

    ksiazkaAdresowa.wczytajAdresatowZalogowanegoUzytkownikaZPliku();

    return 0;
}
