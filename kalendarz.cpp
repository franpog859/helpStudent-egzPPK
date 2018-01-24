#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

/*
Funkcja sprawdzajaca czy w roku kalendarzowym jest 365 czy 366 dni.
---------------
autor: Mateusz Piguła
2017-11-27
*/
bool czyRokPrzestepny(int rok)
{
    return ((rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0));
}

/*
Funkcja zwracajaca indeks dnia
dla danej daty - dzien/miesiac/rok,
wraz z ewentualnym przesunięciem jeśli pierwszym dniem tygodnia jest dzień inny niż niedziela
----------------
Index     dzien
0         Niedziela
1         Poniedzialek
2         Wtorek
3         Sroda
4         Czwartek
5         Piatek
6         Sobota
-----------------
autor: Mateusz Piguła
2017-10-22
*/
int indeksDnia(int dzien, int miesiac, int rok, int pierwszyDzienTygodnia) //Algorytm Sakamoto
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
                       4, 6, 2, 4
                     };
    rok -= miesiac < 3;
    return (rok + rok / 4 - rok / 100 +
            rok / 400 + t[miesiac - 1] + dzien - pierwszyDzienTygodnia) % 7;
}

/*
Funkcja zwracajaca nazwe miesiaca po jego indeksie

indeks Miesiaca     Nazwa
0                   Styczen
1                   Luty
2                   Marzec
3                   Kwiecien
4                   Maj
5                   Czerwiec
6                   Lipiec
7                   Sierpien
8                   Wrzesien
9                   Pazdziernik
10                  Listopad
11                  Grudzien
------------------
 autor: Mateusz Piguła
 2017−11−27
 */
string nazwaMiesiaca(int numerMiesiaca)
{
    string miesiac[] = { "Styczen", "Luty", "Marzec",
                         "Kwiecien", "Maj", "Czerwiec",
                         "Lipiec", "Sierpien", "Wrzesien",
                         "Pazdziernik", "Listopad", "Grudzien"
                       };

    return (miesiac[numerMiesiaca]);
}

/* Funkcja zwracajaca liczbe dni w danym miesiacu

Numer miesiaca   Nazwa       Liczba dni
0                Styczen     31
1                Lity        28 (nieprzestepny) / 29 (przestepny)
2                Marzec      31
3                Kwiecien    30
4                Maj         31
5                Czerwiec    30
6                Lipiec      31
7                Sierpien    31
8                Wrzesien    30
9                Pazdziernik 31
10               Listopad    30
11               Grudzien    31
-------------------
autor: Mateusz Piguła
2017-10-22
*/
int liczbaDniMiesiaca(int numerMiesiaca, int rok)
{
    // Styczen
    if (numerMiesiaca == 0)
        return (31);

    // Luty
    if (numerMiesiaca == 1)
    {
        if (czyRokPrzestepny(rok))
            return (29);
        else
            return (28);
    }

    // Marzec
    if (numerMiesiaca == 2)
        return (31);

    // Kwiecien
    if (numerMiesiaca == 3)
        return (30);

    // Maj
    if (numerMiesiaca == 4)
        return (31);

    // Czerwiec
    if (numerMiesiaca == 5)
        return (30);

    // Lipiec
    if (numerMiesiaca == 6)
        return (31);

    // Sierpien
    if (numerMiesiaca == 7)
        return (31);

    // Wrzesien
    if (numerMiesiaca == 8)
        return (30);

    // Pazdziernik
    if (numerMiesiaca == 9)
        return (31);

    // Listopad
    if (numerMiesiaca == 10)
        return (30);

    // Grudzien
    if (numerMiesiaca == 11)
        return (31);
}

/*
 Funkcja wyswietlajaca kalendarz na dany rok
------------------
 autor: Mateusz Piguła
 2017−11−27
 */
void wyswietlKalendarz(int rok, int pierwszyDzienTygodnia, const string& nazwaPliku)
{
    string const plik(nazwaPliku+".txt");
    ofstream plikWyjscia;
    plikWyjscia.open (plik.c_str());

    plikWyjscia << "	    Kalendarz " << rok;
    int dni;

    // Indeks dnia od 0 do 6
    int numerDnia = indeksDnia(1, 1, rok, pierwszyDzienTygodnia);



    // i --> Wszystkie miesiace
    // j --> Wszystkie dni miesiaca "i"
    for (int i = 0; i < 12; i++)
    {
        dni = liczbaDniMiesiaca(i, rok);

        // Wyswietl nazwe miesiaca
        if (nazwaMiesiaca(i).length() % 2 == 0)
        {
            plikWyjscia << endl << "  " << string(((34 - nazwaMiesiaca(i).length()) / 2), '-') << nazwaMiesiaca(i) << string(((33 - nazwaMiesiaca(i).length()) / 2), '-') << endl;
        }
        else
        {
            plikWyjscia << endl << "  " << string(((33 - nazwaMiesiaca(i).length()) / 2), '-') << nazwaMiesiaca(i) << string(((33 - nazwaMiesiaca(i).length()) / 2), '-') << endl;

        }


        // Wyswietl kolumny z nazwami dni
        if (pierwszyDzienTygodnia == 0) plikWyjscia << "  Nie  Pon  Wto  Sro  Czw  Pia  Sob" << endl;
        if (pierwszyDzienTygodnia == 1) plikWyjscia << "  Pon  Wto  Sro  Czw  Pia  Sob  Nie" << endl;
        if (pierwszyDzienTygodnia == 2) plikWyjscia << "  Wto  Sro  Czw  Pia  Sob  Nie  Pon" << endl;
        if (pierwszyDzienTygodnia == 3) plikWyjscia << "  Sro  Czw  Pia  Sob  Nie  Pon  Wto" << endl;
        if (pierwszyDzienTygodnia == 4) plikWyjscia << "  Czw  Pia  Sob  Nie  Pon  Wto  Sro" << endl;
        if (pierwszyDzienTygodnia == 5) plikWyjscia << "  Pia  Sob  Nie  Pon  Wto  Sro  Czw" << endl;
        if (pierwszyDzienTygodnia == 6) plikWyjscia << "  Sob  Nie  Pon  Wto  Sro  Czw  Pia" << endl;

        // Wyswietl odpowiednia ilosc miejsc
        int k;
        for (k = 0; k < numerDnia; k++)
        {
            plikWyjscia << "     ";
        }

        for (int j = 1; j <= dni; j++)
        {
            plikWyjscia << setw(5) << j;

            if (++k > 6)
            {
                k = 0;
                plikWyjscia << endl;
            }
        }

        if (k) plikWyjscia << endl;

        numerDnia = k;
    }
    return;
    plikWyjscia.close();
}

/*
 Pomoc:
 Funkcja wyswietlajaca instrukcje programu.
 ------------------
 autor: Mateusz Piguła
 2017−11−27
 */
void Pomoc()
{
    cout    << endl
            << " INSTRUKCJA" << endl
            << " Wyswietlanie kalendarza na dany rok naszej ery" << endl
            << " ---------------------przelacznik '-o'---------" << endl
            << " Po przelaczniku '-o' podajemy nazwe pliku wyjsciowego" << endl
            << " Spacja konczy nazwe pliku chyba ze zapiszemy ja w cudzyslowie" << endl
            << " ---------------------przelacznik '-d'---------" << endl
            << " Po przelaczniku '-d' podajemy pierwszy dzien " << endl << " tygodnia jako pojedynczy znak, gdzie: " << endl
            << " Poniedzialek ---- o" << endl
            << " Wtorek ---------- w" << endl
            << " Sroda ----------- s" << endl
            << " Czwartek -------- c" << endl
            << " Piatek ---------- t" << endl
            << " Sobota ---------- b" << endl
            << " Niedziela ------- n" << endl
            << " Domyslna wartosc pierwszego dnia tygodnia wskazuje poniedzialek," << endl
            << " zostanie ona wyswietlona w przypadku braku wartosci po przelaczniku '-d'" << endl
            << " ---------------------przelacznik '-r'---------" << endl
            << " Po przelaczniku '-r' podajemy rok z naszej ery" << endl
            << " Podanie roku po przelaczniku '-r' jest warunkiem niezbednym do wywolania programu" << endl << endl
            << " Przykladowe wywolanie programu to:" << endl << endl
            << " program.exe -o kal2017 -d o -r 2017" << endl
            << " WAZNE: przelaczniki i ich wartosci musza byc oddzielone znakiem spacji!" << endl
            << " -----------------------------------------------------" << endl
            << " Zycze przyjemnego korzystania z programu" << endl
            << "                            Mateusz Pigula" << endl;
}

/*
Funkcja sprawdzajaca poprawnosc wprowadzonych danych do konsoli
---------------
autor: Mateusz Piguła
2017-11-27
*/
bool poprawneDane(int rok, int pierwszyDzienTygodnia, int &argc)
{
    return !(rok < 1 || pierwszyDzienTygodnia > 6 || pierwszyDzienTygodnia < 0);
}

int main(int argc, char * argv[])
{
    int rok = 0; //Jezeli uzytkowniku nie poda roku zostaniemy poinformowanie o bledzie, gdyz rok = 0 nie spelnia warunkow
    int pierwszyDzienTygodnia = 1; // definiujemy domyslny pierwszy dzien tygodnia
    char decyzja;
    string nazwaPliku;
    string przelacznik[] = { "n", "o", "w", "s",
                           "c", "t", "b"
                         };


    for(int i = 0; i < argc; i++)
    {
        if (string(argv[i]) == "-h")
        {
            Pomoc();
            return 0;
        }
        if (string(argv[i]) == "-r")
        {
            if(argv[i] == argv[argc-1]) { break;}
            else {
            rok = atoi(argv[i+1]);
            if (nazwaPliku.empty()) nazwaPliku = "Kalendarz" + to_string(rok); // definijemy domyslna nazwa na wypadek braku deklaracji uzytkownika
            }
        }
        if (string(argv[i]) == "-d")
        {
            if(argv[i] == argv[argc-1]) { break;}
            else {
            for (int j = 0; j < 7; j++)
            {
                if (string(argv[i+1]) == przelacznik[j]) { pierwszyDzienTygodnia = j; }
            }}
        }
        if (string(argv[i]) == "-o")
        {
            if(argv[i] == argv[argc-1]) { break;}
            else nazwaPliku = argv[i+1];
        }
    }

    if (!poprawneDane(rok, pierwszyDzienTygodnia, argc))
        {
            cerr << " Podano za malo argumentow lub niepoprawne dane!" << endl;
            cout << " Wyswietlic pomoc? (t/n): ";

            do
            {
                cin >> decyzja;
            }
            while (decyzja != 't' && decyzja != 'T' && decyzja != 'n' && decyzja != 'N');

            if (decyzja == 't' || decyzja == 'T')
            {
                Pomoc();
            } else return 0;
        } else if (rok > 32768)
        {
            cout << "Hola, hola. To już dosc odlegly termin, czas juz pewnie licza troche inaczej." << endl
            << "Wpisz troche mniejsza date :-)" << endl;
        } else {
                wyswietlKalendarz(rok, pierwszyDzienTygodnia, nazwaPliku);
                cout << " Kalendarz zostal zapisany poprawnie do pliku!" << endl;
                return 0;
            }

    return 0;
}

