#include "PlikZAdresatami.h"

vector <Adresat> PlikZAdresatami::wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    vector <Adresat> adresaci;

    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstaniegoAdresataWPliku = "";
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZAdresatami.c_str(), ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        daneOstaniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    plikTekstowy.close();

    if (daneOstaniegoAdresataWPliku != "")
    {
        idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstaniegoAdresataWPliku);
    }
    else
    {
        idOstatniegoAdresata = 0;
    }

    return adresaci;
}

int PlikZAdresatami::pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika));

    return idUzytkownika;
}

Adresat PlikZAdresatami::pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.ustawId(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 2:
                adresat.ustawIdUzytkownika(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 3:
                adresat.ustawImie(pojedynczaDanaAdresata);
                break;
            case 4:
                adresat.ustawNazwisko(pojedynczaDanaAdresata);
                break;
            case 5:
                adresat.ustawNumerTelefonu(pojedynczaDanaAdresata);
                break;
            case 6:
                adresat.ustawEmail(pojedynczaDanaAdresata);
                break;
            case 7:
                adresat.ustawAdres(pojedynczaDanaAdresata);
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

int PlikZAdresatami::pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdAdresata));
    return idAdresata;
}

int PlikZAdresatami::pobierzIdOstatniegoAdresata()
{
    return idOstatniegoAdresata;
}

void PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
{
    string liniaZDanymiAdresata = "";
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZAdresatami.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (czyPlikJestPusty(plikTekstowy) == true)
        {
            plikTekstowy << liniaZDanymiAdresata;
        }
        else
        {
            plikTekstowy << endl << liniaZDanymiAdresata;
        }
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
    }
    plikTekstowy.close();
    system("pause");
}

string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.pobierzImie() + '|';
    liniaZDanymiAdresata += adresat.pobierzNazwisko() + '|';
    liniaZDanymiAdresata += adresat.pobierzNumerTelefonu() + '|';
    liniaZDanymiAdresata += adresat.pobierzEmail() + '|';
    liniaZDanymiAdresata += adresat.pobierzAdres() + '|';

    return liniaZDanymiAdresata;
}

bool PlikZAdresatami::czyPlikJestPusty(fstream &plikTekstowy)
{
    plikTekstowy.seekg(0, ios::end);
    if (plikTekstowy.tellg() == 0)
        return true;
    else
        return false;
}

void PlikZAdresatami::ustawIdOstatniegoAdresata(int noweIdOstatniegoAdresata)
{
    idOstatniegoAdresata = noweIdOstatniegoAdresata;
}

void PlikZAdresatami::zapiszBazeDanychAdresatow(int idEdytowanegoAdresata, int typOperacji, vector <Adresat> adresaci)
{
    //typOperacji == 0 -> usuwanie adresata
    //typOperacji == 1 -> edycja adresata

    int numerWierszaWBazieDanychAdresatow = 1;

    string pobranaLiniaTekstuZBazyDanych = "";

    fstream bazaDanychAdresatow;
    //Odczyt z pliku
    bazaDanychAdresatow.open("bazaDanychAdresatow.txt", ios::in);

    fstream tymczasowaBazaDanychAdresatow;
    //Zapis do pliku
    tymczasowaBazaDanychAdresatow.open("tymczasowaBazaDanychAdresatow.txt", ios::out);

    if(bazaDanychAdresatow.good() == true)
    {
        if(typOperacji == 0)
        {
            while(getline(bazaDanychAdresatow, pobranaLiniaTekstuZBazyDanych))
            {
                if (numerWierszaWBazieDanychAdresatow != 1)
                {
                    tymczasowaBazaDanychAdresatow << endl;
                }

                if(atoi(pobranaLiniaTekstuZBazyDanych.substr(0, podajPozycjeZnakuRozdzialuIdAdresata(pobranaLiniaTekstuZBazyDanych)).c_str()) != idEdytowanegoAdresata)
                {
                    tymczasowaBazaDanychAdresatow << pobranaLiniaTekstuZBazyDanych;

                    numerWierszaWBazieDanychAdresatow++;
                }
            }
        }
        else
        {
            while(getline(bazaDanychAdresatow, pobranaLiniaTekstuZBazyDanych))
            {
                if (numerWierszaWBazieDanychAdresatow != 1)
                {
                    tymczasowaBazaDanychAdresatow << endl;
                }

                if(atoi(pobranaLiniaTekstuZBazyDanych.substr(0, podajPozycjeZnakuRozdzialuIdAdresata(pobranaLiniaTekstuZBazyDanych)).c_str()) == idEdytowanegoAdresata)
                {
                    int indeksEdytowanegoAdresata=0;

                    for(indeksEdytowanegoAdresata=0; indeksEdytowanegoAdresata<adresaci.size(); indeksEdytowanegoAdresata++)
                    {
                        if(adresaci[indeksEdytowanegoAdresata].pobierzId() == idEdytowanegoAdresata)
                        {
                            break;
                        }
                    }

                    tymczasowaBazaDanychAdresatow << adresaci[indeksEdytowanegoAdresata].pobierzId() << '|';
                    tymczasowaBazaDanychAdresatow << adresaci[indeksEdytowanegoAdresata].pobierzIdUzytkownika() << '|';
                    tymczasowaBazaDanychAdresatow << adresaci[indeksEdytowanegoAdresata].pobierzImie() << '|';
                    tymczasowaBazaDanychAdresatow << adresaci[indeksEdytowanegoAdresata].pobierzNazwisko() << '|';
                    tymczasowaBazaDanychAdresatow << adresaci[indeksEdytowanegoAdresata].pobierzNumerTelefonu() << '|';
                    tymczasowaBazaDanychAdresatow << adresaci[indeksEdytowanegoAdresata].pobierzEmail() << '|';
                    tymczasowaBazaDanychAdresatow << adresaci[indeksEdytowanegoAdresata].pobierzAdres() << '|';
                }
                else
                {
                    tymczasowaBazaDanychAdresatow << pobranaLiniaTekstuZBazyDanych;
                }

                numerWierszaWBazieDanychAdresatow++;
            }
        }
    }

    bazaDanychAdresatow.close();
//Koniec odczytu pliku

    tymczasowaBazaDanychAdresatow.close();
//Koniec zapisu do pliku

    remove("bazaDanychAdresatow.txt");

    rename("tymczasowaBazaDanychAdresatow.txt", "bazaDanychAdresatow.txt");
}

int PlikZAdresatami::podajPozycjeZnakuRozdzialuIdAdresata(string pobranaLiniaTekstuZBazyDanych)
{
    int pozycjaZnakuRozdzialuIdAdresata = 0;

    char znakuRozdzialuIdAdresata = '|';

    while(znakuRozdzialuIdAdresata != pobranaLiniaTekstuZBazyDanych[pozycjaZnakuRozdzialuIdAdresata])
    {
        pozycjaZnakuRozdzialuIdAdresata++;
    }

    return pozycjaZnakuRozdzialuIdAdresata;
}
