#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika = 0;
    string nazwa ="", haslo = "";
};

struct Adresat
{
    int idAdresata = 0;
    int idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};


void dodajUzytkownikaDoPliku(int id, string nazwa, string haslo)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if(plik.good()==false)
    {
        cout<<"Nie mozna otworzyc pliku!";
    }
    plik << id << "|" << nazwa << "|" << haslo << endl;

    plik.close();
}

int rejestracja(vector<Uzytkownik> &uzytkownicy, int liczbaUzytkownikow)
{
    string nazwa, haslo;
    Uzytkownik nowyUzytkownik;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while (i < liczbaUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wybierz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
        else
            i++;
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    nowyUzytkownik.nazwa = nazwa;
    nowyUzytkownik.haslo = haslo ;
    nowyUzytkownik.idUzytkownika = liczbaUzytkownikow +1;

    uzytkownicy.push_back(nowyUzytkownik);

    dodajUzytkownikaDoPliku(liczbaUzytkownikow+1, nazwa, haslo);


    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return liczbaUzytkownikow+1;
}

int logowanie(vector<Uzytkownik> &uzytkownicy, int liczbaUzytkownikow)
{
    string nazwa, haslo;
    cout << "Podaj nazwe: ";
    cin >> nazwa;
    int i = 0;
    while (i < liczbaUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for (int proby = 0 ; proby < 3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob" << 3-proby << " : ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo";
            Sleep(2000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}



int wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy)
{
    string idUzytkownika, nazwa, haslo;
    string linia;
    int iloscUzytkownikow = 0;
    int nrDanej=1;

    Uzytkownik uzytkownik;
    int id;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good()==false)
    {
        cout<<"Nie mozna otworzyc pliku!";
        return 0;
    }


    while(getline(plik,linia))
    {

        string temp="";
        int i=0;


        while (i<linia.length())
        {
            while ((linia[i]!='|') && (i<linia.length()) )
            {
                temp+=linia[i];
                i++;
            }


            switch(nrDanej)
            {
            case 1:
                uzytkownik.idUzytkownika = atoi(temp.c_str());;
                break;
            case 2:
                uzytkownik.nazwa = temp;
                break;
            case 3:
                uzytkownik.haslo = temp;
                break;
            }

            temp = "";
            i++;

            if (nrDanej == 3)
            {
                nrDanej=0;
                iloscUzytkownikow++;
            }
            nrDanej++;
        }

        uzytkownicy.push_back(uzytkownik);

    }

    plik.close();

    return iloscUzytkownikow;
}

int wczytajAdresatowdlaDanegoUzytkownika(vector<Adresat> &adresaci,int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, numerTelefonu, email, adres;
    string linia;
    int iloscOsob = 0;
    int nrDanej=1;

    Adresat adresat;
    int idAdresata;
    int idUzytkownika;
    int liczbaAdresatow = 0;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if(plik.good()==false)
        cout<<"Nie mozna otworzyc pliku!";


    while(getline(plik,linia))
    {
        string temp="";
        int i=0;

        while ((linia[i]!='|') && (i<linia.length()) )
        {
            while (linia[i]!='|')
            {
                temp+=linia[i];
                i++;
            }


            switch(nrDanej)
            {
            case 1:
                adresat.idAdresata = atoi(temp.c_str());
                break;
            case 2:
                adresat.idUzytkownika= atoi(temp.c_str());
                break;
            case 3:
                adresat.imie = temp;
                break;
            case 4:
                adresat.nazwisko = temp;
                break;
            case 5:
                adresat.numerTelefonu = temp;
                break;
            case 6:
                adresat.email = temp;
                break;
            case 7:
                adresat.adres = temp;
                break;
            }

            temp = "";
            i++;

            if (nrDanej==7)
            {
                nrDanej=0;
            }
            nrDanej++;

        }

        if (adresat.idUzytkownika == idZalogowanegoUzytkownika)
        {
            adresaci.push_back(adresat);
            liczbaAdresatow++;
        }

    }

    plik.close();


    return liczbaAdresatow;
}


void wyswietlWszystkichAdresatow(vector<Adresat> &adresaci, int liczbaAdresatow)
{

    system("cls");

    if (liczbaAdresatow == 0)
        cout << "Brak adresatow dla podanego uzytkownika" << endl;

    for (int i=0; i<liczbaAdresatow; i++)
    {
        cout << adresaci[i].idAdresata <<endl;
        cout << adresaci[i].imie <<endl;
        cout << adresaci[i].nazwisko <<endl;
        cout << adresaci[i].numerTelefonu <<endl;
        cout << adresaci[i].email <<endl;
        cout << adresaci[i].adres <<endl;
    }

    getch();

}

void wyswietlOsobyOTymSamymImieniu(vector<Adresat> &adresaci, int liczbaAdresatow)
{
    string imie;
    system("cls");
    cout << "Podaj imie : " << endl;
    cin >> imie;
    cout << endl;

    for (int i=0; i<liczbaAdresatow; i++)
        if (adresaci[i].imie == imie)
        {
            cout << adresaci[i].idAdresata<<endl;
            cout << adresaci[i].imie <<endl;
            cout << adresaci[i].nazwisko <<endl;
            cout << adresaci[i].numerTelefonu <<endl;
            cout << adresaci[i].email <<endl;
            cout << adresaci[i].adres <<endl <<endl;
        }

    getch();

}


void wyswietlOsobyOTymSamymNazwisku(vector<Adresat> &adresaci, int liczbaAdresatow)
{
    string nazwisko;
    system("cls");
    cout << "Podaj nazwisko : " << endl;
    cin >> nazwisko;
    cout << endl;

    for (int i=0; i<liczbaAdresatow; i++)
        if (adresaci[i].nazwisko == nazwisko)
        {
            cout << adresaci[i].idAdresata <<endl;
            cout << adresaci[i].imie <<endl;
            cout << adresaci[i].nazwisko <<endl;
            cout << adresaci[i].numerTelefonu <<endl;
            cout << adresaci[i].email <<endl;
            cout << adresaci[i].adres <<endl <<endl;
        }

    getch();
}

int ustalMAxId()
{
    string linia,linia2;

    int maxId=0;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if(plik.good()==false)
    {
        cout<<"Nie mozna otworzyc pliku!";
        return 0;
    }

    while(getline(plik,linia))
    {
        linia2=linia;
    }

    linia=linia2;

    string temp="";
    int i=0;

    while (linia[i]!='|' )
    {
        temp+=linia[i];
        i++;
    }

    maxId = atoi(temp.c_str());


    plik.close();
    return maxId;

}

void dodajAdresataDoPliku(const char *file_name, Adresat adresat)
{

    ifstream fin(file_name);
    ofstream fout;
    fout.open("temp.txt", ios::out);
    string linia;

    while (getline(fin,linia))
        fout<<linia<<endl;

    fout << adresat.idAdresata<< "|" ;
    fout << adresat.idUzytkownika<< "|" ;
    fout << adresat.imie << "|" ;
    fout << adresat.nazwisko << "|";
    fout << adresat.numerTelefonu << "|";
    fout << adresat.email << "|";
    fout << adresat.adres << "|" <<endl;
    fout.close();
    fin.close();
    remove(file_name);
    rename("temp.txt", file_name);
}

int dodajAdresata(vector<Adresat> &adresaci, int liczbaOsob, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, numerTelefonu, email, adres;

    Adresat adresat;

    int idAdresata = 0;
    idAdresata = ustalMAxId()+1;

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> adresat.imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> adresat.nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync();
    getline(cin, adresat.numerTelefonu);
    cout << "Podaj email uzytkownika: ";
    cin >> adresat.email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adresat.adres);

    adresat.idAdresata = idAdresata;
    adresat.idUzytkownika = idZalogowanegoUzytkownika;
    adresaci.push_back(adresat);

    dodajAdresataDoPliku("Adresaci.txt",adresat);

    cout << "Osoba zostala dodana." << endl;
    Sleep(1000);

    liczbaOsob++;
    return liczbaOsob;
}


void del_line(const char *file_name, int id)
{
    ifstream fin(file_name);
    ofstream fout;
    fout.open("temp.txt", ios::out);
    int idLini;

    string linia;

    while(getline(fin,linia))
    {

        string idStr="";
        int i=0;

        while (linia[i]!='|' )
        {
            idStr+=linia[i];
            i++;
        }

        idLini = atoi(idStr.c_str());

            fout<<linia<<endl;
    }
        if(idLini != id)
    fout.close();
    fin.close();
    remove(file_name);
    rename("temp.txt", file_name);
}



int usunAdresata(vector<Adresat> &adresaci, int iloscOsob)
{
    char wybor;
    int id;
    int nrLini = 0;
    system("cls");
    cout << "Podaj id osoby do usuniecia : " << endl;
    cin >> id;
    cout << endl;

    vector<Adresat>::iterator it;
    for (it = adresaci.begin(); it != adresaci.end(); ++it)
        if ((*it).idAdresata == id)
        {
            cout << "Czy na pewno usunac osobe (t/n)?" << endl;
            cin >> wybor;
            if (wybor == 't')
            {
                adresaci.erase(it);
                it--;
                cout << "Osoba zostala usunieta." << endl;
                Sleep(1000);
            }
        }
    del_line("Adresaci.txt",id);


    return --iloscOsob;
}

void aktualizacjaPliku(const char *file_name,int id,Adresat edytowanyAdresat, int iloscOsob)
{
    ifstream fin(file_name);
    ofstream fout;
    fout.open("temp.txt", ios::out);
    int idLini;

    string linia;

    while(getline(fin,linia))
    {
        string idStr="";
        int i=0;

        while (linia[i]!='|' )
        {
            idStr+=linia[i];
            i++;
        }

        idLini = atoi(idStr.c_str());
        if (id == idLini)
        {

            fout << edytowanyAdresat.idAdresata<< "|" ;
            fout << edytowanyAdresat.idUzytkownika<< "|" ;
            fout << edytowanyAdresat.imie << "|" ;
            fout << edytowanyAdresat.nazwisko << "|";
            fout << edytowanyAdresat.numerTelefonu << "|";
            fout << edytowanyAdresat.email << "|";
            fout << edytowanyAdresat.adres << "|" <<endl;

        }

        else

            fout<<linia<<endl;
    }
    fout.close();
    fin.close();
    remove(file_name);
    rename("temp.txt", file_name);
}



void edytujAdresata(vector<Adresat> &adresaci,int iloscOsob)
{
    int wybor;
    int id;
    Adresat edytowanyAdresat;
    string imie, nazwisko, numerTelefonu, email, adres;

    system("cls");
    cout << "Podaj id adresata ktorego chcesz eydotwac " << endl;
    cin >> id;

    system("cls");


    vector<Adresat>::iterator it;
    edytowanyAdresat.idAdresata = id;



    for (it = adresaci.begin(); it != adresaci.end(); ++it)
        if ((*it).idAdresata == id)
        {
            cout << "Wybierz ktora dana adresata chesz edytowac" << endl;
            cout << " 1 - imie " << endl;
            cout << " 2 - nazwisko " << endl;
            cout << " 3 - numer telefonu " << endl;
            cout << " 4 - email " << endl;
            cout << " 5 - adres " << endl;
            cout << " 6 - powrot do menu " << endl;
            cin >> wybor;

            switch(wybor)
            {
            case 1:
                cout << "Podaj nowe imie" << endl;
                cin >> imie;
                (*it).imie = imie;
                edytowanyAdresat.idUzytkownika = (*it).idUzytkownika;
                edytowanyAdresat. imie = imie;
                edytowanyAdresat.nazwisko = (*it).nazwisko;
                edytowanyAdresat.email = (*it).email;
                edytowanyAdresat.adres = (*it).adres;
                edytowanyAdresat.numerTelefonu = (*it).numerTelefonu;
                break;
            case 2:
                cout << "Podaj nowe nazwisko" << endl;
                cin >> nazwisko;
                (*it).nazwisko = nazwisko;
                edytowanyAdresat.idUzytkownika = (*it).idUzytkownika;
                edytowanyAdresat. imie = (*it).imie;
                edytowanyAdresat.nazwisko = nazwisko;
                edytowanyAdresat.email = (*it).email;
                edytowanyAdresat.adres = (*it).adres;
                edytowanyAdresat.numerTelefonu = (*it).numerTelefonu;
                break;
            case 3:
                cout << "Podaj nowy numer telefonu" << endl;
                cin >> numerTelefonu;
                (*it).numerTelefonu = numerTelefonu;
                edytowanyAdresat.idUzytkownika = (*it).idUzytkownika;
                edytowanyAdresat. imie = (*it).imie;
                edytowanyAdresat.nazwisko = (*it).nazwisko;
                edytowanyAdresat.email = (*it).email;
                edytowanyAdresat.adres = (*it).adres;
                edytowanyAdresat.numerTelefonu = numerTelefonu;
                break;
            case 4:
                cout << "Podaj nowy email" << endl;
                cin >> email;
                (*it).email = email;
                edytowanyAdresat.idUzytkownika = (*it).idUzytkownika;
                edytowanyAdresat. imie= (*it).imie;
                edytowanyAdresat.nazwisko = (*it).nazwisko;
                edytowanyAdresat.email = email;
                edytowanyAdresat.adres = (*it).adres;
                edytowanyAdresat.numerTelefonu = (*it).numerTelefonu;
                break;
            case 5:
                cout << "Podaj nowy adres" << endl;
                cin >> adres;
                (*it).adres = adres;
                edytowanyAdresat. imie = (*it).imie;
                edytowanyAdresat.idUzytkownika = (*it).idUzytkownika;
                edytowanyAdresat.nazwisko = (*it).nazwisko;
                edytowanyAdresat.email = (*it).email;
                edytowanyAdresat.adres = adres;
                edytowanyAdresat.numerTelefonu = (*it).numerTelefonu;
                break;
            }

            aktualizacjaPliku("Adresaci.txt",id,edytowanyAdresat,iloscOsob);

            cout << "Osoba zostala edytowana." << endl;
            Sleep(1000);
        }

}

void aktualizacjaPlikuPoZmianieHasla(const char *file_name,int idZalogowanegoUzytkownika,Uzytkownik uzytkownikZnowymHaslem)
{
    ifstream fin(file_name);
    ofstream fout;
    fout.open("temp.txt", ios::out);
    int idLini;

    string linia;

    while(getline(fin,linia))
    {
        string idStr="";
        int i=0;

        while (linia[i]!='|' )
        {
            idStr+=linia[i];
            i++;
        }

        idLini = atoi(idStr.c_str());
        if (idZalogowanegoUzytkownika == idLini)
        {

            fout << uzytkownikZnowymHaslem.idUzytkownika<< "|" ;
            fout << uzytkownikZnowymHaslem.nazwa<< "|" ;
            fout << uzytkownikZnowymHaslem.haslo << "|" <<endl;

        }

        else

            fout<<linia<<endl;
    }
    fout.close();
    fin.close();
    remove(file_name);
    rename("temp.txt", file_name);

}



void zmianaHasla(vector<Uzytkownik> &uzytkownicy,int liczbaUzytkownikow, int idZalogowanegoUzytkownika)
{
    string haslo;
    Uzytkownik uzytkownik;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (int i=0; i < liczbaUzytkownikow; i++)

        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            uzytkownik = uzytkownicy[i];
            cout << "Haslo zostalo zmienione" << endl;
            aktualizacjaPlikuPoZmianieHasla("Uzytkownicy.txt",idZalogowanegoUzytkownika,uzytkownik);
            Sleep(2000);
        }
}


int main()
{
    vector<Uzytkownik> uzytkownicy;
    vector<Adresat> adresaci;


    int idZalogowanegoUzytkownika = 0;
    int liczbaUzytkownikow = 0;
    int liczbaAdresatow = 0;

    char wybor;

    liczbaUzytkownikow = wczytajUzytkownikowZPliku(uzytkownicy);

    while (1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                liczbaUzytkownikow = rejestracja(uzytkownicy, liczbaUzytkownikow);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, liczbaUzytkownikow);
                adresaci.clear();
                liczbaAdresatow = wczytajAdresatowdlaDanegoUzytkownika(adresaci,idZalogowanegoUzytkownika);
            }
            else if (wybor == '9')
            {
                exit(0);
            }

        }
        else
        {

            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj adresatow o podanym imieniu" << endl;
            cout << "3. Wyszukaj adresatow o podanym nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                liczbaAdresatow = dodajAdresata(adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);
            }
            if (wybor == '2')
            {
                wyswietlOsobyOTymSamymImieniu(adresaci,liczbaAdresatow);
            }
            if (wybor == '3')
            {
                wyswietlOsobyOTymSamymNazwisku(adresaci,liczbaAdresatow);
            }
            if (wybor == '4')
            {
                wyswietlWszystkichAdresatow(adresaci,liczbaAdresatow);
            }
            if (wybor == '5')
            {
                liczbaAdresatow = usunAdresata(adresaci,liczbaAdresatow);
            }
            if (wybor == '6')
            {
                edytujAdresata(adresaci,liczbaAdresatow);
            }
            if (wybor == '7')
            {
                zmianaHasla(uzytkownicy, liczbaUzytkownikow, idZalogowanegoUzytkownika);
            }
            else if (wybor == '9')
            {
                idZalogowanegoUzytkownika = 0;
            }

        }

    }
    return 0;
}
