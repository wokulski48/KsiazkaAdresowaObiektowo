#include "UzytkownikMenadzer.h"

void UzytkownikMenadzer::rejestracjaUzytkownika()
{
    Uzytkownik uzytkownik = podajDaneNowegoUzytkownika();

    uzytkownicy.push_back(uzytkownik);

    plikZUzytkownikami.dopiszUzytkownikaDoPliku(uzytkownik);

    cout << endl << "Konto zalozono pomyslnie" << endl << endl;
    system("pause");
}

Uzytkownik UzytkownikMenadzer::podajDaneNowegoUzytkownika()
{
    Uzytkownik uzytkownik;

    uzytkownik.ustawId(pobierzIdNowegoUzytkownika());

    do
    {
        cout << "Podaj login: ";
        uzytkownik.ustawLogin(MetodyPomocnicze::wczytajLinie());
    }
    while (czyIstniejeLogin(uzytkownik.pobierzLogin()) == true);

    cout << "Podaj haslo: ";
    uzytkownik.ustawHaslo(MetodyPomocnicze::wczytajLinie());

    return uzytkownik;
}

int UzytkownikMenadzer::pobierzIdNowegoUzytkownika()
{
    if (uzytkownicy.empty() == true)
        return 1;
    else
        return uzytkownicy.back().pobierzId() + 1;
}

void UzytkownikMenadzer::wypiszWszystkichUzytkownikow()
{
    for(int i=0; i<uzytkownicy.size(); i++)
    {
        cout << uzytkownicy[i].pobierzId() << endl;
        cout << uzytkownicy[i].pobierzLogin() << endl;
        cout << uzytkownicy[i].pobierzHaslo() << endl;
    }
}

bool UzytkownikMenadzer::czyIstniejeLogin(string login)
{
    for(int i=0; i<uzytkownicy.size(); i++)
    {
        if(uzytkownicy[i].pobierzLogin() == login)
        {
            cout << endl << "Istnieje uzytkownik o takim loginie." << endl;
            return true;
        }
    }
    return false;
}

void UzytkownikMenadzer::wczytajUzytkownikowZPliku()
{
    uzytkownicy = plikZUzytkownikami.wczytajUzytkownikowZPliku();
}

int UzytkownikMenadzer::logowanieUzytkownika()
{
    //Uzytkownik uzytkownik;
    string login = "", haslo = "";

    cout << "Podaj login: ";
    login = MetodyPomocnicze::wczytajLinie();

    vector <Uzytkownik>::iterator itr = uzytkownicy.begin();
    while (itr != uzytkownicy.end())
    {
        if (itr -> pobierzLogin() == login)
        {
            for (int iloscProb = 3; iloscProb > 0; iloscProb--)
            {
                cout << "Podaj haslo. Pozostalo prob: " << iloscProb << ": ";
                haslo = MetodyPomocnicze::wczytajLinie();

                if (itr -> pobierzHaslo() == haslo)
                {
                    cout << endl << "Zalogowales sie." << endl << endl;
                    system("pause");
                    return idZalogowanegoUzytkownika = itr -> pobierzId();
                }
            }
            cout << "Wprowadzono 3 razy bledne haslo." << endl;
            system("pause");
            return idZalogowanegoUzytkownika = 0;
        }
        itr++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl << endl;
    system("pause");
    return idZalogowanegoUzytkownika = 0;
}

void UzytkownikMenadzer::zmianaHaslaZalogowanegoUzytkownika()
{
    string noweHaslo = "";
    cout << "Podaj nowe haslo: ";
    noweHaslo = MetodyPomocnicze::wczytajLinie();

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if (itr -> pobierzId() == idZalogowanegoUzytkownika)
        {
            itr -> ustawHaslo(noweHaslo);
            cout << "Haslo zostalo zmienione." << endl << endl;
            system("pause");
        }
    }
    plikZUzytkownikami.zapiszWszystkichUzytkownikowDoPliku(uzytkownicy);
}

void UzytkownikMenadzer::wylogujUzytkownika()
{
    idZalogowanegoUzytkownika = 0;
    //adresaci.clear();
}

int UzytkownikMenadzer::pobierzIdZalogowanegoUzytkownika()
{
    return idZalogowanegoUzytkownika;
}

void UzytkownikMenadzer::ustawIdZalogowanegoUzytkownika(int noweIdZalogowanegoUzytkownika)
{
    idZalogowanegoUzytkownika = noweIdZalogowanegoUzytkownika;
}

void UzytkownikMenadzer::zmianaHaslaUzytkownika()
{
    system( "cls" );

    string noweHasloUzytkownika = "";
    int liczbaProbZmianHasla = 1;

    cout << "ZMIANA HASLA UZYTKOWNIKA" << endl;
    cout << "Podaj nowe haslo dla uzytkownika (" << uzytkownicy[idZalogowanegoUzytkownika-1].pobierzLogin() << "): ";

    do
    {
        if(liczbaProbZmianHasla > 1)
        {
            cout << "Podaj inne haslo!";
            Sleep(1500);
            system( "cls" );
            cout << "ZMIANA HASLA UZYTKOWNIKA" << endl;
            cout << "Podaj nowe haslo dla uzytkownika (" << uzytkownicy[idZalogowanegoUzytkownika-1].pobierzLogin() << "): ";
        }

        cin >> noweHasloUzytkownika;
        liczbaProbZmianHasla++;
    }
    while (noweHasloUzytkownika == uzytkownicy[idZalogowanegoUzytkownika-1].pobierzHaslo());

    uzytkownicy[idZalogowanegoUzytkownika-1].ustawHaslo(noweHasloUzytkownika);

    fstream bazaDanychUzytkownikow;

    //Zapis do pliku
    bazaDanychUzytkownikow.open("Uzytkownicy.txt", ios::out);

    int numerWierszaWBazieDanychUzytkownikow = 1;

    vector<Uzytkownik>::iterator koniecWektora = uzytkownicy.end();
    for(vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr !=koniecWektora; ++itr)
    {
        if (numerWierszaWBazieDanychUzytkownikow != 1)
        {
            bazaDanychUzytkownikow << endl;
        }

        bazaDanychUzytkownikow << itr->pobierzId() << '|';
        bazaDanychUzytkownikow << itr->pobierzLogin() << '|';
        bazaDanychUzytkownikow << itr->pobierzHaslo() << '|';

        numerWierszaWBazieDanychUzytkownikow++;
    }

    bazaDanychUzytkownikow.close();
    //Koniec zapisu do pliku

    cout << "Haslo zostalo zmienione!";
    Sleep(1500);
    system( "cls" );

}
