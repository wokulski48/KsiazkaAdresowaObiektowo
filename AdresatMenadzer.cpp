#include "AdresatMenadzer.h"

void AdresatMenadzer::wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika)
{
    adresaci = plikZAdresatami.wczytajAdresatowZalogowanegoUzytkownikaZPliku(idZalogowanegoUzytkownika);
}

int AdresatMenadzer::pobierzIdOstatniegoAdresata()
{
    return plikZAdresatami.pobierzIdOstatniegoAdresata();
}

int AdresatMenadzer::dodajAdresata(int idZalogowanegoUzytkownika, int idOstatniegoAdresata)
{
    Adresat adresat;

    system("cls");
    cout << " >>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;
    adresat = podajDaneNowegoAdresata(idZalogowanegoUzytkownika, idOstatniegoAdresata);

    adresaci.push_back(adresat);
    plikZAdresatami.dopiszAdresataDoPliku(adresat);

    return ++idOstatniegoAdresata;
}

Adresat AdresatMenadzer::podajDaneNowegoAdresata(int idZalogowanegoUzytkownika, int idOstatniegoAdresata)
{
    Adresat adresat;

    adresat.ustawId(++idOstatniegoAdresata);
    adresat.ustawIdUzytkownika(idZalogowanegoUzytkownika);

    cout << "Podaj imie: ";
    adresat.ustawImie(MetodyPomocnicze::wczytajLinie());
    adresat.ustawImie(MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.pobierzImie()));

    cout << "Podaj nazwisko: ";
    adresat.ustawNazwisko(MetodyPomocnicze::wczytajLinie());
    adresat.ustawNazwisko(MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.pobierzNazwisko()));

    cout << "Podaj numer telefonu: ";
    adresat.ustawNumerTelefonu(MetodyPomocnicze::wczytajLinie());

    cout << "Podaj email: ";
    adresat.ustawEmail(MetodyPomocnicze::wczytajLinie());

    cout << "Podaj adres: ";
    adresat.ustawAdres(MetodyPomocnicze::wczytajLinie());

    return adresat;
}

void AdresatMenadzer::wyswietlWszystkichAdresatow()
{
    system("cls");
    if (!adresaci.empty())
    {
        cout << "             >>> ADRESACI <<<" << endl;
        cout << "-----------------------------------------------" << endl;
        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            wyswietlDaneAdresata(*itr);
        }
        cout << endl;
    }
    else
    {
        cout << endl << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void AdresatMenadzer::wyswietlDaneAdresata(Adresat adresat)
{
    cout << endl << "Id:                 " << adresat.pobierzId() << endl;
    cout << "Imie:               " << adresat.pobierzImie() << endl;
    cout << "Nazwisko:           " << adresat.pobierzNazwisko() << endl;
    cout << "Numer telefonu:     " << adresat.pobierzNumerTelefonu() << endl;
    cout << "Email:              " << adresat.pobierzEmail() << endl;
    cout << "Adres:              " << adresat.pobierzAdres() << endl;
}

vector <Adresat>* AdresatMenadzer::pobierzAdresaci()
{
    w_adresaci = &adresaci;
    return w_adresaci;
}

void AdresatMenadzer::ustawIdOstatniegoAdresata(int noweIdOstatniegoAdresata)
{
    plikZAdresatami.ustawIdOstatniegoAdresata(noweIdOstatniegoAdresata);
}

void AdresatMenadzer::edytujAdresata()
{
    int id, indeksAdresata = 0;
    string opcjaMenu = "";

    cout << "EDYTUJ ADRESATA" << endl;
    cout << "Podaj id: ";
    cin >> id;

    for(indeksAdresata=0; indeksAdresata<adresaci.size(); indeksAdresata++)
    {
        if(adresaci[indeksAdresata].pobierzId() == id)
        {
            break;
        }
    }

    if(indeksAdresata == adresaci.size())
    {
        system( "cls" );
        cout << "Adresat o podanym ID nie istnieje!";
        Sleep(1500);
        system( "cls" );
        return;
    }

    system( "cls" );
    cout << "EDYTUJ ADRESATA O ID: " << id << endl;
    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - numer telefonu" << endl;
    cout << "4 - email" << endl;
    cout << "5 - adres" << endl;
    cout << "6 - powrot do menu" << endl;

    do
    {
        cout << "Twoj wybor:";
        cin >> opcjaMenu;
    }
    while (opcjaMenu != "1" && opcjaMenu != "2" && opcjaMenu != "3" && opcjaMenu != "4" && opcjaMenu != "5" && opcjaMenu != "6");

    if(opcjaMenu == "1")
    {
        string imie = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj imie: ";
        cin >> imie;

        adresaci[indeksAdresata].ustawImie(imie);

        plikZAdresatami.zapiszBazeDanychAdresatow(id, 1, adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else if(opcjaMenu == "2")
    {
        string nazwisko = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj nazwisko: ";
        cin >> nazwisko;

        adresaci[indeksAdresata].ustawNazwisko(nazwisko);

        plikZAdresatami.zapiszBazeDanychAdresatow(id, 1, adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else if(opcjaMenu == "3")
    {
        string numerTelefonu = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj numer telefonu: ";
        cin.ignore(numeric_limits < streamsize >::max(), '\n' );
        getline(cin, numerTelefonu);

        adresaci[indeksAdresata].ustawNumerTelefonu(numerTelefonu);

        plikZAdresatami.zapiszBazeDanychAdresatow(id, 1, adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else if(opcjaMenu == "4")
    {
        string email = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj email: ";
        cin >> email;

        adresaci[indeksAdresata].ustawEmail(email);

        plikZAdresatami.zapiszBazeDanychAdresatow(id, 1, adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else if(opcjaMenu == "5")
    {
        string adres = "";

        system( "cls" );
        cout << "EDYTUJ ADRESATA O ID: " << id << endl;
        cout << "Podaj adres: ";
        cin.ignore(numeric_limits < streamsize >::max(), '\n' );
        getline(cin, adres);

        adresaci[indeksAdresata].ustawAdres(adres);

        plikZAdresatami.zapiszBazeDanychAdresatow(id, 1, adresaci);

        cout << endl << "Dane adresata zostaly zaktualizowane!";
        Sleep(1500);
        system( "cls" );
    }
    else
    {
        system( "cls" );
        return;
    }
}
