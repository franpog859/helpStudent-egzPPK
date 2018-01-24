#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#define debug(x)   std::cerr << "(" << __LINE__ << ") " << #x << " == " << (x) << std::endl;

using namespace std;

/*
 Pomoc:
 Funkcja wyswietlajaca instrukcje programu.
 ------------------
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Pomoc()
{
    cout
    << endl << " WYZNACZANIE ILOSCI MANDATOW UZYSKANYCH W WYBORACH PARLAMENTARNYCH ( METODA D'HONDT)" << endl
    << endl << " Program uruchamiamy z wiersza linii poleceń." << endl
    << endl << " Wywołując program można dodatkowo zastosować parametry -o -i -h."
    << endl << " Kolejność parametrów nie ma znaczenia."
    << endl << " Po parametrze -i należy wpisać nazwe pliku wejścia, z którego pobrane będą dane."
    << endl << " Po parametrze -o należy wpisać nazwe pliku wyjścia, gdzie zostanie zapisany wynik."
    << endl << " Parametr -h wyświetla instrukcje korzystania z programu."
    << endl << " Nie wykorzystanie przełączników -i lub -o spowoduje pobór/wyświetlanie danych w standartowym wejściu/wyściu." << endl
    << endl << "  Warunki poprawności danych:" << endl
    << endl << "- Pierwsza wartoscia wymagana jest ilosc mandatow."
    << endl << "- Nastepne wartosci są glosami na poszczegolne partie. "
    << endl << "- Wszystkie wartosci powinny byc oddzielone."
    << endl << "- Wszystkie wartosci powinny byc liczbami naturalnymi."
    << endl << "- Ilosc partii nie powinna przekraczac 100." << endl;
}

/*
 Wyzerowanie_mandatow:
 Funkcja ustawiajaca wartosci tablicy mandatów dla kazdej partii na 0
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 mandaty -- tablica mandatow ktora zostanie wyzerowana
 liczbapartii -- liczba partii bioracych udzial w wyborach parlamentarnych
 ------------------
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Wyzerowanie_mandatow(unsigned int mandaty[ ], unsigned int liczbapartii)
{
    for (int i = 0; i < liczbapartii; i++)
        mandaty[i] = 0;
}

/*
 Odczytaj_argumenty:
 Funkcja odczytujaca parametry wywolania programu. Sa one podane w postaci przelacznikow.
 nazwa pliku wejsciowego (-i input)
 nazwa pliku wyjsciowego (-o output)
 wyswielenie pomocy (-h)
 Przelaczniki moga byc podane w dowolnej kolejnosci .
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 ile −− liczba parametrow przy uruchomieniu programu
 argumenty −− tablica wskaznikow na lancuchy uzytych przy uruchomienieu programu
 szInput −− parametr wyjsciowy , do ktorego zostanie zapisana odczytana nazwa pliku
 wejsciowego
 szOutput −− parameter wyjsciowy , do ktorego zostanie zapisana odczytana nazwa pliku
 wyjsciowego
 ------------------
 autor : Mateusz Piwowarski
 2017−11−27
 */

bool Odczytaj_argumenty(int ile , char ** argumenty , string & szInput , string & szOutput)
{
	bool poprawneetykiety = true;    
	const string ETYKIETAINPUT ("-i");
    	const string ETYKIETAOUTPUT ("-o");
    	const string ETYKIETAHELP ("-h");

	// ile razy zostala wykorzystana etykieta. jezeli wiecej niz raz -> blad
    	int uzytoo = 0;
	int uzytoh = 0;
	int uzytoi = 0;

    for(int i = 0; i < ile - 1; i++)
    {
        string arg (argumenty[i]);
        
        if (argumenty[i+1] == ETYKIETAHELP) // -h
		{	
			uzytoh++;
            Pomoc();
		}
        
        if (arg == ETYKIETAINPUT) // -i
		{
			uzytoi++;
            szInput = argumenty[i + 1];
        }
        if (arg == ETYKIETAOUTPUT) // -o
		{
            szOutput = argumenty [i + 1];
			uzytoo++;
		}
		if(arg[0] == '-' && arg[1] != 'o' && arg[1] != 'h' && arg[1] != 'i')
			poprawneetykiety = false;
    }

	if(uzytoi > 1 || uzytoo > 1 || uzytoh > 1)
		poprawneetykiety = false;

return poprawneetykiety;
}

/*
 Sprawdzdane:
 Funkcja sprawdza czy dane wpisane w standardowym wejsciu sa poprawne
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 poprawnedane -- wartosc ktora przechowuje informacje czy dane podane przez uzytkownika sa poprawne.
 linia -- wiersz polecen w ktorym uzytkownik podal dane
 pusty -- wartosc ktora przechowuje informacje czy linia nie jest pusta

 autor : Mateusz Piwowarski
 2017−11−27
 */

void Sprawdzdane(const string & linia, bool & poprawnedane)
{
	// czy text nie zawiera innych znakow niz biale znaki lub cyfry
	for(int i = 0; i < linia.length() && poprawnedane; i++)
		if((linia[i] < '0' || linia[i] > '9') && linia[i] != ' ' && linia[i] != '	')
			poprawnedane = false;

	bool pusty = true;

	// czy text nie jest pusty
	for(int i = 0; i < linia.length() && poprawnedane; i++)
		if(linia[i] != ' ' && linia[i] != '	')
			pusty = false;
	
	if(pusty)
		poprawnedane = false;
}

/*
 SprawdzIloscPartii:
	Funkcja ktora liczy ilosc zapisanych wartosci na wejsciu standardowym
 iloscdanych -- zmienna ktora przechowuje informacje ile jest jest wartosci na wejsciu standardowym
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 linia -- wiersz polecen w ktorym uzytkownik podal dane
 ------------------
 wartosc zwracana:
 ------------------
 liczba partii podana w wejsciu standardowym ( iloscdanych - 1)
 
 autor : Mateusz Piwowarski
 2017−12−19
 */
int SprawdzIloscPartii(const string & linia)
{

	int iloscdanych = 0;
	for(int i = 0; i < linia.length(); i++)
		if(linia[i] != ' ' && linia[i] != '	')
			if(linia[i+1] == ' ' || linia[i+1] == '	' || linia[i+1] < '0' || linia[i] > '9')
				iloscdanych++;	 

	return iloscdanych - 1;
} 

/*
 Usunwartosc:
 Funkcja usuwa z tekstu wartosci zapisane do zmiennych oraz biale znaki przed wartosciami
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 linia -- wiersz polecen w ktorym uzytkownik podal dane

 autor : Mateusz Piwowarski
 2017−11−27
 */

void Usunwartosc(string & linia)
{
	while(linia[0] == ' ' || linia[0] == '	')	// usuwanie bialych znakow az do pierszej wartosci
			linia.erase(0,1);	
		
	while(linia[0] != ' ' && linia[0] != '	') // usuwanie danych ktore zostaly zapisane do zmiennej 
			linia.erase(0,1);	
}

/*
 Wartosci_z_konsoli:
 Funkcja przypisuje dane ktore podaje uzytkownik z standardowego wejscia. Pobiera liczbe partii bioracych udzial w wyborach, liczbe wszystkich mandatow ktore zostana rozdane w wyborach oraz ilosc glosow oddanych na poszczegolne partie.
 Po pobraniu kazdej wartości uruchamia funkcje Poprawnosc_danych sprawdzajaca czy podane przez uzytkownika wartosci sa popranwe.
 poprawnedane -- wartosc ktora przechowuje informacje czy dane podane przez uzytkownika sa poprawne.
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 glosy -- tablica w ktorej beda przechowywane liczby oddanych glosow na poszczegolne partie
 liczbapartii -- liczba partii ktora bedzie, ktora bedzie podana przez uzytkownika
 iloscmandatow -- liczba mandatow, ktora bedzie podana przez uzytkownika
 MAKS -- maksymalna liczba partii
 ------------------
 wartosc zwracana:
 ------------------
 true -- wartosci ktore podal uzytkownik sa poprawne
 false -- wartosci ktore podal uzytkownik sa niepoprawne
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

bool Wartosci_z_konsoli(unsigned int glosy[ ], unsigned int &liczbapartii, unsigned int &iloscmandatow, const int MAKS)
{
   	bool poprawnedane = true;
	int j = 0;	// dla ktorej partii przypisujemy glosy
	string linia;
	int rozmiar = 0;

	getline( cin, linia); // pobieranie linii z wejscia standardowego

	Sprawdzdane(linia, poprawnedane);

	if(poprawnedane)
		liczbapartii = (SprawdzIloscPartii(linia));

	if(liczbapartii > MAKS)
		return false;
	
	if(liczbapartii > 0)
	{
		if(iloscmandatow = atoi(linia.c_str()))	// pobieranie iloscimandatow (atoi .c_str -- zamiana string na int)	
			Usunwartosc(linia);
	
		// przypisywanie zdobytych glosow

		for(; j < liczbapartii - 1; j++)
			if(glosy[j] = atoi(linia.c_str()))
				Usunwartosc(linia);

		if(glosy[j] = atoi(linia.c_str()));
	}
	return poprawnedane;
}

/*
 SprawdzPoprawnosc:
 Funkcja sprawdza czy dane zapisane w pliku są poprawne
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 poprawnedane -- wartosc ktora przechowuje informacje czy dane w pliku sa poprawne
 glosy -- tablica glosow przechowujaca liczbe oddanych glosow na partie
 liczbapartii -- ilosc partii bioracych udzial w wyborach parlamentarnych
 iloscmandatow -- ilosc mandatow ktore sa do podzialu w wyborach parlamentarnych
 plikwejscia -- strumien pliku wejscia 
 ------------------
 wartosc zwracana:
 ------------------
 true -- dane w pliku sa poprawne
 false -- dane w pliku sa niepoprawne
 
 autor : Mateusz Piwowarski
 2017−12−10
 */

bool SprawdzPoprawnosc(bool & poprawnedane, unsigned int glosy[ ], unsigned int & liczbapartii, unsigned int &iloscmandatow, ifstream & plikwejscia)
{
	string linia;
	bool pustyplik = true;
	
	while(!plikwejscia.eof() && poprawnedane) // sprawdzamy rowniez poprawnedane aby nie wypisywal bledu dla kazdej linii 
	{
		getline(plikwejscia, linia);
		for(int i = 0; i < linia.length(); i++)
		{
			if((linia[i] < '0' || linia[i] > '9') && linia[i] != ' ' && linia[i] != '	')
			{	
				poprawnedane = false;
				pustyplik = false;			
				break;
			}
			if(linia[i] != ' ')
				pustyplik = false;
		}
	
		if(pustyplik)
			poprawnedane = false;
	}
		
	plikwejscia.close(); // niepotrzebne zamykanie pliku jezeli daloby sie ustawic na poczatek pliku i wczytac dane 
	return poprawnedane;
}

/*
 Brakpliku:
 Funkcja jest wywolywana kiedy plik podany przez uzytkownika nie istnieje
 Funkcja sprawdza wartosc zwracana funkcji Wartosc_z_konsoli
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 poprawnedane -- wartosc ktora przechowuje informacje czy dane w pliku sa poprawne
 glosy -- tablica glosow przechowujaca liczbe oddanych glosow na partie
 liczbapartii -- ilosc partii bioracych udzial w wyborach parlamentarnych
 iloscmandatow -- ilosc mandatow ktore sa do podzialu w wyborach parlamentarnych
 plikwejscia -- strumien pliku wejscia 
 MAKS -- maksymalna liczba partii
 ------------------
 wartosc zwracana:
 ------------------
 true -- dane w pliku sa poprawne
 false -- dane w pliku sa niepoprawne
 
 autor : Mateusz Piwowarski
 2017−12−10
 */

void Brakpliku(unsigned int glosy[ ], unsigned int &liczbapartii, unsigned int &iloscmandatow, bool &poprawnedane, const int MAKS)
{
	if(!Wartosci_z_konsoli(glosy, liczbapartii, iloscmandatow, MAKS))
		poprawnedane = false;
}

/*
 Pobieranie_danych:
 Funkcja przypisuje dane z pliku lub z standardowego wejscia.
 Tworzy strumień ifstream (plikwejscia) do pliku o nazwie wejscie ktora znajduje sie w katalogu zewnetrznym dat
 Funkcja wyswietla komunikat jezeli plik wejscia nie zostal podany w wierszu linii polecen lub pliku nie znaleziono
 Funkcja wyswietla komunikat jezeli dane w pliku wejscia sa niepoprawne
 plikwejscia -- strumien ifstream na plik tekstowy wejscie ktore znajduje sie w katalogu zewnetrzym dat
 poprawne_dane -- wartosc ktora przechowuje informacje czy dane w pliku lub dane podane przez uzytkownika sa poprawne
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 wejscie -- nazwa pliku z ktorego pobieramy dane
 MAKS -- maksymalna ilosc partii
 glosy -- tablica glosow przechowujaca liczbe oddanych glosow na partie
 liczbapartii -- ilosc partii bioracych udzial w wyborach parlamentarnych
 iloscmandatow -- ilosc mandatow ktore sa do podzialu w wyborach parlamentarnych
 ------------------
 wartosc zwracana:
 ------------------
 true -- wartosci w pliku lub ktore podal uzytkownik sa poprawne
 false -- wartosci w pliku lub ktore podal uzytkownik sa niepoprawne
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

bool Pobieranie_danych(string wejscie,const int MAKS, unsigned int glosy[ ], unsigned int &liczbapartii, unsigned int &iloscmandatow)
{
    bool poprawnedane = true;
    	if(!wejscie.empty())
	{
		ifstream plikwejscia(wejscie);
		if( plikwejscia)
		{
			if(SprawdzPoprawnosc(poprawnedane, glosy, liczbapartii, iloscmandatow, plikwejscia))
			{
				ifstream plikwejscia(wejscie); 
				plikwejscia >> iloscmandatow;
	   			// pobieranie z pliku ilosc glosow na kazda partie
    	    
				int i = 0;
		   		while (plikwejscia >> glosy[i++])
				{
		    		liczbapartii++;
					if(liczbapartii > MAKS)
					{
						poprawnedane = false;
						break; // przerywa program gdy licznik przekroczy 100
					}
				}
			}
	        plikwejscia.close();
		}
		else
    		Brakpliku(glosy, liczbapartii, iloscmandatow, poprawnedane, MAKS);
    	
	}
    else
	    Brakpliku(glosy, liczbapartii, iloscmandatow, poprawnedane, MAKS);
   	
    return poprawnedane;
}


/*
 Iloraz wyborczy:
 Funkcja zwraca wartosc ilorazu wyborczego po otrzymaniu mandatu przez partie: ( ilosc glosow otrzymanych w glosowaniu / ilosc uzyskanych mandatow w danym momencie + 1)
 Wartosc zwracana jest brana pod uwage przy przydzielaniu kolejnego mandatu
 Funkcja zostaje wywolywana po otrzymaniu mandatu przez partie
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 glosy -- ilosc glosow oddanych na partie
 mandaty -- ilosc mandatow uzyskanych przez partie
 ------------------
 wartosc zwracana:
 ------------------
 ilosc glosow po otrzymaniu mandatu przez partie
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

double Iloraz_wyborczy(double glosy, double mandaty)
{
    return (glosy) / (mandaty + 1);
}

/*
 Podzial_mandatow:
 Funkcja ktora przydziela mandaty partiom bioracych udzial w wyborach parlamentarnych
 baza_glosow -- tablica ktora na poczatku funkcji przechowuje poczatkowy stan glosow na poszczegolne partie. Wraz z kazdym przyznaniem mandatu wartosci głosów stają się ilorazem wyborczym. Po przyznaniu mandatu dla partii, dana partia otrzymuje nowa wartosc ilorazu wyborczego poprzez funkcje Iloraz_wyborczy
 max -- zmienna w ktorej przechowujemy wartosc najwiekszego ilorazu wyborczego z wszystkich partii
 miejscemax -- zmienna ktora przechowuje informacje w ktorym miejscu tablicy baza_glosow znajduje sie najwiekszy iloraz wyborczy
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 MAKS -- maksymalna ilosc partii bioracych udzial w wyborach parlamentarnych
 mandaty -- tablica mandatow przydzielonych partiom bioracych udzial w wyborach parlamentarnych
 glosy -- tablica glosow oddanych na partie bioracych udzial w wyborach parlamentarnych
 liczbapartii -- ilosc partii ktore biora udzial w wyborach parlamentarnych
 iloscmandatow -- ilosc mandatow ktore sa do podzialu w wyborach parlamentarnych
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Podzial_mandatow(const int MAKS, unsigned int mandaty [ ], unsigned int glosy [ ], unsigned int liczbapartii, unsigned int iloscmandatow)
{

    double baza_glosow[100];
    int miejscemax = 0;
    // kopia tablicy glosow
    for (int i = 0; i < liczbapartii; i++)
        baza_glosow[i] = glosy[i];
    
    for (int i = 0 ; i < iloscmandatow; i++)
    {
        // szukanie najwiekszej wartosci
        double max = -1;
        for (int j = 0 ; j< liczbapartii; j++)
            if (max < baza_glosow[j])
            {
                max = baza_glosow[j];
                miejscemax = j;
            }
        
        // partia z najwieksza wartoscia dostaje mandat
        mandaty[miejscemax]++;
        baza_glosow[miejscemax] = Iloraz_wyborczy(glosy[miejscemax], mandaty[miejscemax]);
    }
}

/*
 Wynik_konsola:
 Funkcja wyswietlajace wynik przypisania mandatow na standardowe wyjscie:
 // partia (kolejno numer partii): ilosc mandatow //
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 mandaty -- tablica mandatow przydzielonych partiom bioracych udzial w wyborach parlamentarnych
 liczbapartii -- liczba partii ktore biora udzial w wyborach parlamentarnych
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Wynik_konsola(unsigned int mandaty[ ], unsigned int liczbapartii)
{
    cout << " Podzial mandatow:" << endl;
    for (int i = 0; i < liczbapartii; i++)
        cout << " partia " << i + 1 << ": " << mandaty[i] << endl;
}

/*
 Wynik:
 Funkcja wyswietlajace wynik przypisania mandatow do pliku lub na standardowe wyjscie
 Jezeli string wyjscie jest pusty zostaje uruchomiona funkcja Wynik_konsola ktora wyswietli wynik wyborow na standardowe wyjscie.
 Jezeli string wyjscie zawiera nazwe pliku w ktorym chcemy zapisac wynik wyborow funkcja tworzy strumien ofstream plikwyjscia pliku tekstowego wyjscie w katalogu zewnetrznym dat
 W pliku tekstowym zostaje zapisany wynik wyborow: // partia (kolejno numer partii): ilosc mandatow //
 ------------------
 parametry funkcji :
 −−−−−−−−−−−−−−−−−−
 wyjscie -- nazwa pliku do ktorego zostanie zapisany wynik
 liczbapartii -- liczba partii ktore biora udzial w wyborach parlamentarnych
 mandaty -- tablica mandatow przydzielonych partiom bioracych udzial w wyborach parlamentarnych
 
 autor : Mateusz Piwowarski
 2017−11−27
 */

void Wynik(string wyjscie, unsigned int liczbapartii, unsigned int mandaty[ ])
{
    
    if(wyjscie.empty())
        Wynik_konsola( mandaty, liczbapartii);
    else
    {
        ofstream plikwyjscia(wyjscie);
        if(plikwyjscia)
        {
            plikwyjscia << " Podzial mandatow:" << endl;
            for (int i = 0; i < liczbapartii; i++)
                plikwyjscia << " partia " << i + 1 << ": " << mandaty[i] << endl;
            
       	plikwyjscia.close();
        }
    }
    
}

int main(int ile, char ** argumenty)
{
	//wszystkie zmienne 'wyzerowałem'
    const int MAKS = 100;  // maksymalna liczba partii ktora moze wziac udzial w wyborach parlamentarnych
    unsigned int mandaty[MAKS]; // tablica ktora przechowuje ilosc mandatow otrzymanych przez poszczegolne partie
    unsigned int glosy[MAKS]; // tablica ktora przechowuje ilosc glosow oddanych na poszczegolne partie
    unsigned int liczbapartii = 0; // liczba partii ktora bierze udzial w wyborach
    unsigned int iloscmandatow = 0; // ilosc mandatow do podzialu w wyborach
    
    string nazwa_pliku_wejscia; // nazwa pliku z ktorego beda pobierane dane
    string nazwa_pliku_wyjsca; // nazwa pliku w ktorym beda zapisywane wyniki wyborow
    
    if(Odczytaj_argumenty(ile, argumenty, nazwa_pliku_wejscia, nazwa_pliku_wyjsca))
    {   
    	if(Pobieranie_danych(nazwa_pliku_wejscia, MAKS, glosy, liczbapartii, iloscmandatow))
    	{
       		Wyzerowanie_mandatow( mandaty, liczbapartii); 
       		Podzial_mandatow(MAKS, mandaty, glosy, liczbapartii, iloscmandatow);
			Wynik(nazwa_pliku_wyjsca, liczbapartii, mandaty);
    	}
		else
		{
			cout << endl << " Niepoprawne dane." << endl;
			Pomoc();
		}
	}
	else
	{
		cout << endl << " Niepoprawne wywolanie programu." << endl;
		Pomoc();
	}
    return 0;
}

