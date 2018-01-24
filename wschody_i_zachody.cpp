// program liczacy czasy wschodu i zachodu slonca
// w danym miejscu, strefie czasowej i przedziale dni

#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

/*                          IS_INSIDE
 Funkcja sprawdzająca czy liczba x zawiera się w przedziale <l,r>.

 −−−−−−−−−−−−−−−−−−
    INFORMACJE:
 Parametry są przekazywane w późniejszej części programu.
 Funkcja jest używana przy sprawdzeniu poprawnoci strefy czasowej "zone",
 Dlaczego inline? ......

 −−−−−−−−−−−−−−−−−
 true −− x zawiera się w przedziale <l,r>
 false −− x nie zawiera się w przedziale <l,r>
 */
inline bool is_inside(double x, double l, double r) {
    return l <= x && x <= r;
}
//***************************************************************************

/*                          IS_UINT
 Funkcja sprawdzająca czy liczba s jest liczba całkowitą bez znaku
 −−−−−−−−−−−−−−−−−
    INFORMACJE:
Parametry są przekazywane (const &_parametr) gdyż
 −−−−−−−−−−−−−−−−−
 true −− s jest liczbą całkowitą bez znaku
 false −− s nie jest liczbą całkowitą bez znaku
 */

bool is_uint(const string& s) {
    /* Jezeli string s jest pusty zwaraca fałsz */
    if (s.empty()) {
        return false;
    }
    /* Sprawdza pokolej czy parametr funkcji jest liczba ,sprawdzając kazdą cyfre osobno */
    for (auto x: s) {
        if (!isdigit(x)) {
            return false;
        }
    }
    
    return s[0] != '0' || s.length() == 1;
}
//***************************************************************************

/*                          IS_INT
 Funkcja sprawdzająca czy liczba s jest liczba całkowitą
 −−−−−−−−−−−−−−−−−
 INFORMACJE:
 −−−−−−−−−−−−−−−−−
 true −− s jest liczbą całkowitą
 false −− s nie jest liczbą całkowitą
 */

inline bool is_int(const string& s) {
    return !s.empty() &&
    (is_uint(s) || ((s[0] == '-' || s[0] == '+') && is_uint(s.substr(1, s.length() - 1))));
    /* Nie jest puste i ( Jest liczbą bez znaku lub ( Na 1 miejscu ma -/+ i po odjeciu 1 znaku jest liczbą całkowita bez znaku ))*/
}
//***************************************************************************

/*                          IS_NUMBER
 Funkcja sprawdzająca czy liczba s jest liczba
 −−−−−−−−−−−−−−−−−
 INFORMACJE:
 Pętla zapamietuje iż napotkała już jeden znak '.', Kazdy kolejny spowoduje iż funkcja stwierdzi ze podany parametr nie jest liczbą
 50.300 - poprawna liczba
 50.30.1 - nie poprawna liczba

 −−−−−−−−−−−−−−−−−
 true −− s jest liczbą
 false −− s nie jest liczbą
 */

bool is_number(const string& s) {
    unsigned x = s.length();     // w zmienej x zapisuje jakas wartosc ( w tym przypadku dl s )
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '.') {
            if (x != s.length()) {
                return false;
            }
            x = i;
        } else if (i != 0 && !isdigit(s[i])) {
            return false;
        }
    }
    /* sprawdza czy string jest liczba całkowita od 1 miejsca do miejsca gdy petla napotkała '.' */
    return is_int(s.substr(0, x));
}
//***************************************************************************

/*                          IS_TIME_ZONE
 Funkcja sprawdzająca czy zone jest poprawną strefą czasowa <-12,+12>
 −−−−−−−−−−−−−−−−−
 INFORMACJE:
 −−−−−−−−−−−−−−−−−
 true −− s jest poprawna strefą czasową
 false −− s nie jest poprawną strefą czasową
 */

inline bool is_time_zone(const string& zone) {
    const int min_zone = -12, max_zone = 12;
    return is_int(zone) && min_zone <= stoi(zone) && stoi(zone) <= max_zone;
}
//***************************************************************************

/*                          TIME_ZONE_TO_STR
 Funkcja zamienia liczbę na napis odpowiadającej jej strefie czasowej

 */

inline string time_zone_to_str(int zone) {
    return (zone > 0 ? "+" : (zone < 0 ? "-" : "")) + to_string(zone) + ".00";
}

//***************************************************************************

// Klasa do przechowywania daty
// Daty są w formacie rrrr-mm-dd
// Implementowane są daty kalendarza gregoriańskiego

struct Data {
    int dzien, miesiac, rok;
};

// Sprawdza czy rok jest przestępny
bool czy_przestepny(int rok) {
    return rok % 400 == 0 || (rok % 100 != 0 && rok % 4 == 0);
}
// Sprawdza ile dni ma konkretny miesiąc
int ile_dni(int miesiac, int rok) {
    return miesiac == 2 ? (czy_przestepny(rok) ? 29 : 28) :
    ((miesiac <= 7 && miesiac % 2 == 1) || (miesiac >= 8 && miesiac % 2 == 0) ? 31 : 30);
}
    
//Zamienia liczbe na odpowiednia godzine np. 14.5 --> 14:30
string number_to_time(double n) {
    return to_string(int(floor(n))) + ":" + to_string(int(round(((n - floor(n)) * 60))));
}
    
//***************************************************************************
    
    /*                          SLONCE
     Funkcja oblicza godzine wschodu i zachodu słońca zgodnie z wzorami
     −−−−−−−−−−−−−−−−−
     INFORMACJE:
        Parametry: (długość geog, szerokość geog, strefa czasowa , wschod )
     wshod == 1 -> Oblicza wschod
     wchod == -1 -> Oblicza zachod
     −−−−−−−−−−−−−−−−−
     */
string slonce(Data dt, double dlugosc, double szerokosc, int strefa, int wschod) {
    double req = -0.833;
    double J = 367 * dt.rok - 7 * (dt.rok + ((dt.miesiac + 9) / 12)) / 4 + 275 * dt.miesiac / 9 + dt.dzien - 730531.5;
    double cent = J / 36525;
    double a = fmod(4.8949504201433 + 628.331969753199 * cent, 2 * M_PI);
    double b = fmod(6.2400408 + 628.3019501 * cent, 2 * M_PI);
    double c = 0.409093 - 0.0002269 * cent;
    double d = 0.033423 * sin(b) + 0.00034907 * sin(2 * b);
    double e = 0.0430398 * sin(2 * (a + d)) - 0.00092502 * sin(4 * (a + d)) - d;
    double f = asin(sin(c) * sin(a + d));
    double rad = M_PI / 180;
    double g = (sin(rad * req) - sin(rad * szerokosc) * sin(f)) / (cos(rad * szerokosc) * cos(f));
    return number_to_time((M_PI - (e + rad * dlugosc + wschod * acos(g))) / (15 * rad) + strefa);
}

// zamienia napis na obiekt typu Data
Data string_to_data(const string& data = "2000-01-01") {
    return {stoi(data.substr(8, 2)), stoi(data.substr(5, 2)), stoi(data.substr(0, 4))};
}

// chronologiczne porównywanie dat
bool nie_wieksza(Data d1, Data d2) {
    return d1.rok < d2.rok || (d1.rok == d2.rok && (d1.miesiac < d1.miesiac || (d1.miesiac == d2.miesiac && d1.dzien <= d2.dzien)));
}

// Sprawdza czy napis jest data kalendarza gregoriańskiego
bool is_date(const string& date) {
    /* czy napis jest przerywany odpowiednimi znakami i czy ma odp. dlugosc */
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
        
    /* czy rok, dzien, miesiac to liczby calkowite bez znaku */
    if (!(is_uint(date.substr(0, 4))
        && (is_uint(date.substr(5, 2)) || (date[5] == '0' && isdigit(date[6])))
        && (is_uint(date.substr(8, 2)) || (date[8] == '0' && isdigit(date[9]))))) {
        return false;
    }
    /* Zamieniamy stringa na inty wycinając odpowiednie części czyli: 2017-12-01 ---> rok = 2017, miesiąc = 12 , dzien = 01 */
    int rok = stoi(date.substr(0, 4)), miesiac = stoi(date.substr(5, 2)), dzien = stoi(date.substr(8, 2));
        
    /* Kalendarz Gregoriański zaczyna się od roku 1582 */
    return rok >= 1582 && is_inside(miesiac, 1, 12) && is_inside(dzien, 1, ile_dni(miesiac, rok)) && nie_wieksza(string_to_data("1582-10-01"), string_to_data(date));
}
    
// przesun date o dzien do przodu
Data nastepna(Data d) {
    if (++d.dzien > ile_dni(d.miesiac, d.rok)) {
        if (d.dzien = 1, ++d.miesiac > 12) {
            d.miesiac = 1, ++d.rok;
        }
    }
    
    return d;
}
    
// zamien date na napis
string to_string(Data d) {
    string rok = string(4 - to_string(d.rok).length(), '0') + to_string(d.rok);
    string miesiac = string(2 - to_string(d.miesiac).length(), '0') + to_string(d.miesiac);
    string dzien = string(2 - to_string(d.dzien).length(), '0') + to_string(d.dzien);
    return rok + "-" + miesiac + "-" + dzien;
}
    
//***************************************************************************
    
/*                          WSCHOD / ZACHOD
     Funkcja wywołuje funkcje Słonce która oblicza godzine wchodu i zachodu słonca
     −−−−−−−−−−−−−−−−−
     INFORMACJE:
     Parametry (wchod/zachod): (długość geog, szerokość geog, strefa czasowa)
     Parametry (słonce): (długość geog, szerokość geog, strefa czasowa , 1/-1 )
     1 -> Oblicza wschod
     -1 -> Oblicza zachod
     −−−−−−−−−−−−−−−−−
     */
string wschod(Data data, double dlugosc, double szerokosc, int strefa) {
    return slonce(data, dlugosc, szerokosc, strefa, 1);
}
    
string zachod(Data data, double dlugosc, double szerokosc, int strefa) {
    return slonce(data, dlugosc, szerokosc, strefa, -1);
}
//***************************************************************************

/*                          HELP
 Funkcja wyswietla pomoc dla uzytkownika po wpisani złych danych lub '-h'
 −−−−−−−−−−−−−−−−−
 */
void help() {
    cerr << "****************************************" << endl<< endl;
    cerr << "                 SLONCE"<< endl << endl;
    cerr << "Program do liczenia czasu wschodu i zachodu slonca w dniach [start, koniec] w miejscu <dlugosc, szerokosc>" << endl<<endl;
    cerr << "Parametry"<< endl;
    cerr << "-o nazwa pliku wyjsciowego"<< endl;
    cerr << "--lat szerokosc geograficzna "<< endl;
    cerr << "--lon długosc geograficzna"<< endl;
    cerr << "-t strefa czasowa"<< endl;
    cerr << "-s pierwszy dzien dla ktorego chcemy obliczyc wschod i zachod slonca (rrrr-mm-dd)"<< endl;
    cerr << "-k ostatni dzien dla ktorego chcemy obliczyc wschod i zachod slonca (rrrr-mm-dd)"<< endl<<endl;
    cerr << "./program -o plik_wyjsciowy --lat szerokosc --lon dlugosc  -t strefa -s start -k koniec " << endl << endl;
    cerr << "Przykład:"<< endl;
    cerr << "./program -o Gliwice --lat 50.310 --lon 18.669 -t +1 -s 2017-12-01 -k 2017-12-10  "<< endl <<endl;
}

//***************************************************************
//***************************************************************

int main(int argc, const char** argv)
{
    // liczba wymaganych argumentów przy wywołaniu to 6
    const int arguments = 6;
    
    // obsługa pomocy
    if (argc == 2 && string(argv[1]) == string("-h")) {
        help();
        return 0;
    }
    
    // sprawdzanie liczby argumentów podanych w lini plecen
    if (argc != 2 * arguments + 1) {
        help();
        cerr << "Zla liczba parametrów" << argc << endl;
        return 1;
    }
    
    // przechwycenie argumentów
    vector<pair<string, string>> params;
    for (int i = 1; i <= arguments; i++)
    {
        params.push_back({string(argv[2 * i - 1]), string(argv[2 * i])});
    }
    
    // sprawdzanie nazw argumentów
    /* Najpierw wszystko posortujmy alfabetycznie */
    sort(params.begin(), params.end());
    
    /* Vector names bedzie naszym odnisieniem */
    vector<string> names{"--lat", "--lon", "-k", "-o", "-s", "-t"};
    
    for (int i=0; i < arguments; i++)
    {
        if (params[i].first != names[i])
        {
            help();
            cerr << "Zla nazwa parametru " << params[i].first << endl;
            return 1;
        }
    }
    
    // sprawdzenie poprawnosci konkretnych argumentów
    double szerokosc, dlugosc;
    int strefa;
    string plik, param;
    Data start, koniec;
    
    // szerokosc
    param = params[0].second;
    if (!(is_number(param) && is_inside(szerokosc = stod(param), -90.0, 90.0))) {
        help();
        cerr << "Zla szerokosc geograficzna " << param << endl;
        return 1;
    } else {
        szerokosc = stod(param);
    }
    
    // dlugosc
    param = params[1].second;
    if (!(is_number(param) && (is_inside(dlugosc = stod(param), -180.0, 180.0)))) {
        help();
        cerr << "Zla dlugosc geograficzna " << param << endl;
        return 1;
    } else {
        dlugosc = stod(param);
    }
    
    // strefa
    param = params[5].second;
    if (!is_time_zone(param)) {
        help();
        cerr << "Zla strefa czasowa " << param << endl;
        return 1;
    } else {
        strefa = stoi(param);
    }
    
    // data startowa
    param = params[4].second;
    if (!is_date(param)) {
        help();
        cerr << "Zla data poczatkowa " << param << endl;
        return 1;
    } else {
        start = string_to_data(param);
    }
    
    // data koncowa
    param = params[2].second;
    if (!is_date(param)) {
        help();
        cerr << "Zla data koncowa " << param << endl;
        return 1;
    } else {
        koniec = string_to_data(param);
    }
    
    /* Wypisywanie w pliku o nazwie podanej za pomocą przełącznika -o w konsolu */
    ofstream out(params[3].second);
   
    out << fixed << setprecision(2);  //Liczba np: 12.1 ---> 12.10 (2 miejsca po przecinku, w puste miejsca dodaje 0 )

    out << "WSCHODY I ZACHODY SLONCA" << endl;
    out << "dlugosc   = " << dlugosc << " " << (dlugosc < 0 ? "W" : "E") << endl;
    out << "szerokosc = " << szerokosc << " " << (szerokosc < 0 ? "S" : "N") << endl;
    out << "strefa    = " << time_zone_to_str(strefa) << endl;
    out << endl;
    out << "data       wschod zachod" << endl;
    out << endl;
    
    for (Data data = start; nie_wieksza(data, koniec); data = nastepna(data))
    {
        out << to_string(data) << " "
        << wschod(data, dlugosc, szerokosc, strefa) << "   "
        << zachod(data, dlugosc, szerokosc, strefa) << endl;
    }
    
    out.close(); // zamykamy plik
    
    return 0;
}