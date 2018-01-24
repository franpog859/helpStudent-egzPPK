//Euklidesv4-vector.cpp : Defines the entry point for the console application.
//COPYRIGHT XDDDD https://github.com/V4nish 
//#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <exception>

using namespace std;


/*Funkcja void printhelp() ->Wypisuje na ekranie zabudowna zawartosc krotkiej pomocy
-----------------------------
Przyjmowane parametry:
BRAK
-----------------------------
Zmienne:
BRAK
-----------------------------
Wartosc zwracana:
Nie zwraca zadnej wartosci
-----------------------------
Uwagi:
BRAK
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
void printhelp()
{
	cout << "Menu krotkiej pomocy!" << endl;
	cout << "1. aby wywolac menu pomocy uruchom program z przelacznikiem -h" << endl;
	cout << "2. aby wywolac poprawnie program podaj z przelacznikiem -i plik wejsciowy oraz z przelacznikiem -o plik wejsciowy" << endl;
	cout << "brakujacy przelacznik zostanie zastapiony standardowym wejsciem/wyjsciem" << endl;
	cout << "na przyklad Ruklidexv5.exe -i zlozone.txt -o pierwsze.txt" << endl;
	cout << "3. jesli chcesz uzyc pliku pomocniczego z liczbami pierwszymi lub dokonac zapisu wygenerowanych przez program liczb pierwszych dodaj taki plik po przelaczniku -p" << endl;
	cout << "4. wykrywane bledy w pliku wejsciowym zostana wpisane w pliku wejsciowym w odpowiednich liniach, ktore nie byly poprawne" << endl;
	cout << "5. program obsluguje tylko liczby naturalne" << endl;
	cout << "6. jesli uzywasz standardowego wejscia, wpisz exit by zakonczyc prace programu" << endl;
	cout << "Wykonal: Tomasz Skowron INF sem1 gr3// 2017/2018" << endl;
	return;
}


/*Funkcja isdigital() ->Sprawdza czy podany parametr sklada sie wylacznie z cyfr, spacji, null
-----------------------------
Przyjmuje parametry:
-input -> typ string, parametr ten jest sprawdzany pod wzglÄ™dem poprawnosci
-----------------------------
Zmienne:
BRAK
-----------------------------
Wartosc zwracana:
-true -> gdy nie znaleziono zadncyh znakow roznych od spacji, null i cyfr
-false -> gdy napis zawiera conajmniej 1 znak rozny od spacji, null, cyfr
-----------------------------
Uwagi:
Funkcja nie narusza podanego parametru
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
bool isdigital(const string &input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if ((0< input[i] && input[i] < 32/*]null;spacja[*/) || (32 < input[i] && input[i] < 48/*]spacja;0[*/) || (57<input[i])/*]9;+inf[*/)
		{
			return false;
		}
	}
	return true;
}



/*Funkcja iszeroonly() -> sprawdza, czy napis jest napisem zlozonym z zer i ewentualnie spacji i null
-----------------------------
Przyjmuje parametry:
-input ->typ string, parametre ten jest sprawdzany pod wzglÄ™dem poprawnosci
-----------------------------
Zmienne:
-bool waszero ->odpowiada na pytanie czy w wejsciu zero pojawilo sie conajmniej raz, zaklada sie ze jest falszem
-----------------------------
Zwraca wartosci:
-true -> podany parametr zawieral 0 i nie zawieral znakow roznych od zero, spacja, null
-false -> podany parametr zawieral znaki rozne od zero, spacja, null
-----------------------------
Uwagi:
Funkcja nie narusza podanego parametru
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
bool iszeroonly(const string &input)
{

	bool waszero = false;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == 48/*0*/)
		{
			waszero = true;
			break;
		}

	}
	if (waszero == false)
	{
		return false;
	}
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != 48/*0*/ && input[i] != 0/*null*/ && input[i] != 32/*spacja*/)
		{
			return false;
		}
	}
	if (waszero == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*Funkcja leavedigitsonly() -> na podstawie podanego parametru zwraca string pozbawiony znakow nie bedacym cyframi, funkcja ignoruje zera na poczatku inputu i nie dodaje ich do zwracanej wartosci
-----------------------------
Przyjmuje parametry:
-input ->typ string, na jego podstawie zostanie utworzony nowy string bez znakow roznych od cyfr
-----------------------------
Zmienne:
-tempinputinternal -> typ string, deklarowany jako pusty, zostanie zwrocony jako wynik dzialania funkcji, do niego dokladane sa dozwolone znaki
-firstnotzero -> typ int, indeks pierwszej cyfry nie bedacej zerem, od niej p
-----------------------------
Zwraca wartosci:
-tempinputinternal -> typ sting, input pozbawiony znakow roznych od cyfr
-----------------------------
Uwagi:
Funkcja nie narusza podanego parametru
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
string leavedigitsonly(const string &input)
{
	string tempinputinternal = "";
	int firstnotzero = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (48 < input[i] && input[i] < 58/*[1;9]*/)
		{
			firstnotzero = i;
			break;
		}
		firstnotzero++;
	}
	for (int i = firstnotzero; i < input.length(); i++)
	{
		if (47<input[i] && input[i]<58/*[0;9]*/)
		{
			tempinputinternal += input[i];
		}
	}

	return tempinputinternal;

}

/*Funkcja fillzeros() -> na podstawie podanego parametru zwraca string, ktorego rozmiar wynosi 20 znakow, brakujace znaki uzupelnia dodajac brakujaca ilosc zer na poczatku
-----------------------------
Przyjmuje parametry:
-input ->typ string, na jego podstawie zostanie utworzony nowy string o rozmiarze 20
-----------------------------
Zmienne:
-tempinputinternal -> typ string, zostanie zwrocony jako skladnik wyniku dzialania funkcji
-tempinputinternal1 -> typ string, zostanie zwrocony jako skladnik wyniku dzialania funkcji, zawiera brakujaca ilosc zer
-----------------------------
Zwraca wartosci:
-tempinputinternal1+tempinputinternal -> typ sting, 20 znakowy string, ktory jesli jako input nie mial 20 znakow to zostaly mu dodane zera na poczatku
-----------------------------
Uwagi:
Funkcja nie narusza podanego parametru
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
string fillzeros(const string &input)
{
	string tempinputinternal = input;
	string tempinputinternal1 = "";
	for (int i = 0; i < 20 - tempinputinternal.size(); i++)
	{
		tempinputinternal1 += "0";
	}
	return tempinputinternal1 + tempinputinternal;
}


/*Funkcja conditionleavedigitsonly() -> na podstawie podanego parametru rozwaza czy parametr zawiera dane o formacie "xx  xx", gdzie x to cyfra
-----------------------------
Przyjmuje parametry:
-input -> typ string, na jego podstawie decyduje sie o wartosci zwracanej przez funkcje
-----------------------------
Zmienne:
-index -> typ int, okesla do ktorego momentu w podanym parametrze dokonano sprawdzenia warunkow
-condition991 -> typ bool, staje sie falszem, gdy w podanym parametrze odnaleziono liczbe
-conditionspace -> typ bool, staje sie falszem, gdy w podanym parametrze spacje po wystapieniu liczby
-condition 992 -> typ bool, staje sie falszem, gdy w podanym parametrze odnaleziono liczbe po uprzednim wystapieniu liczby i spacji
-----------------------------
Zwraca wartosci:
-true -> gdy napis jest poprawny i nie zawiera dwoch liczb oddzielonych spacaja lub spacjami
-false -> gdy potwierdzono wystepowanie dwoch liczb oddzielonych spacja lub spacjami
-----------------------------
Uwagi:
Funkcja nie narusza podanego parametru
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
bool conditionleavedigitsonly(const string &input)
{
	int index = 0;
	bool condition991 = true;
	bool conditionspace = true;
	bool condition992 = true;

	for (; index < input.length(); index++)
	{
		if (47<input[index] && input[index]<58/*[0;9]*/)
		{
			condition991 = false;
			break;
		}
	}
	for (; index < input.length(); index++)
	{
		if (input[index] == 32/*==SPACE*/)
		{
			conditionspace = false;
			break;
		}
	}
	for (; index < input.length(); index++)
	{
		if (47<input[index] && input[index]<58/*[0;9]*/)
		{
			condition992 = false;;
			break;
		}
	}
	if (condition991 == false && condition992 == false && conditionspace == false)
	{
		return false;
	}
	return true;

}


/*Funkcja isvalid() -> na podstawie podanego parametru input rozstrzyga czy parametr nadaje sie do rozkladu na czynniki, a jesli nie to jaki wystepuje w nim blad, co zapisuje w parametrze errorname
patrz UWAGI: WAZNE
-----------------------------
Wykrywane typy bledow:
"rozmiar przekroczony" -> gdy zawartosc podanego parametru input pozbawionego znakow niepoprawnych przez funkcje leavedigitsonly()
"nie jest liczba naturalna" -> gdy zawartosc podanego parametru input zawiera znaki niedozwolone, czyli jakiekolwiek znaki nie bedace cyfra, spacja, null
"zero nie jest poprawne" -> gdy podany parametr to jedno zero lub wiecej i opcjonalnie spacje null
"brak zawartosci" -> gdy input jest pusty, nie zawiera zadnych znakow
"bledny format zawartosci linii" -> gdy linia zawiera "xx xx", gdzie "x" to liczba, ten warunek sprawdzany jest wywolaniem dodatkowej funkcji conditionleavedigitsonly()
-----------------------------
Przyjmuje parametry:
-input -> typ string, na jego podstawie decyduje sie o wartosci zwracanej przez funkcje, i ewentualnym typie bledow
-errorname -> typ string, w nim zostana zapisane komunikaty o typie bledu lub bledow
-----------------------------
Zmienne:
-tempinput -> typ string, dodatkowa kopia input-u, ktorej zostanie przypisana wartosc input pozbawiona czesci znakow przez funkcje leavedigitsonly()
-tempinput2 -> typ string, dodatkowa kopia input-u, ktorej zostanie przypisana wartosc tempinput uzupelniona do 20 znakow przez zera na poczatku za pomoca funkcji fillzeros()
-ui64input -> typ uint64_t, zawiera zawartosc podanego parametru input przetworzona do typu uin64_t
-bool validity -> typ bool, zawiera informacje o poprawnosci napisu, co jest rownowazne z wartoscia zwracana przez funkcje
-----------------------------
Zwraca wartosci:
-validity==true -> gdy napis jest poprawny i nie spelnil zadnego z warunkow niepoprawnosci zawartych w funkcji
-validity==false -> gdy ktorys z warunkow nie zostal spelniony, co jest rownoznaczne z istnieniem komunikatu o bledzie w parametrze errorname
-----------------------------
Uwagi:
Funkcja nie narusza parametru:
-input
Funkcja narusza:
-errorname (dodajac do niego odpowiednie komunikaty o niepoprawnosci input-u)
WAZNE: podajac exit przerywasz prace programu
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
bool isvalid(const string &input, string &errorname)//sprawdzanie poprawnosci inputu
{
	string tempinput;
	string tempinput2;
	tempinput = leavedigitsonly(input);
	tempinput2 = "";
	uint64_t ui64input = 0;
	bool validity = true;
	if (input == "exit")
	{
		cout << "podajac exit przerywasz prace programu" << endl;
		throw 1;
	}
	if (tempinput.size() > 20)
	{

		errorname = errorname + "rozmiar przekroczony! ";
		validity = false;

	}
	if (tempinput.size() <= 20)
	{
		tempinput2 = fillzeros(tempinput);
		if (tempinput2 > "18446744073709551615")
		{

			errorname = errorname + "rozmiar przekroczony! ";
			validity = false;

		}
	}
	if (isdigital(input) == false)
	{
		errorname = errorname + "nie jest liczba naturalna! ";
		validity = false;
	}
	if (input == "0" || iszeroonly(input))
	{
		validity = false;
		errorname = errorname + "zero nie jest poprawne! ";
	}
	if (input == "")
	{
		validity = false;
		errorname = errorname + "brak zawartosci! ";
	}
	if (conditionleavedigitsonly(input) == false)
	{
		validity = false;
		errorname = errorname + "bledny format zawartosci linii! ";

	}
	return validity;
}


/*Funkcja isvalidprime() -> na podstawie podanego parametru input rozstrzyga czy parametr jest poprawna liczba pierwsza, a jesli nie to jaki wystepuje w nim blad, co wypisuje na ekranie,
w raz z numerem linii, gdzie blad wystapil; Jesli zostanie znaleziony jakikolwiek blad, funkcja wypisuje odpowiedni komunikat i przerywa dzialanie programu
patrz UWAGI:WAZNE!!!
-----------------------------
Wykrywane typy bledow:
"przekroczono ilosc liczb pierwszych" -> gdy ilosc wczytanych liczb przekracza mozliwosci wielkosci wektora PrimesV
"zawartosc pliku z liczbami pierwszymi przekracza maksymalny rozmiar zmiennej!" -> gdy rozmiar liczby w pliku jest wiekszy niz dopuszczalny
"zawartosc pliku z liczbami pierwszymi nie sklada sie z liczb naturalnych!" -> gdy zawartosc podanego parametru input zawiera znaki niedozwolone, czyli jakiekolwiek znaki nie bedace cyfra, spacja, null
"zawartosc pliku z liczbami pierwszymi zawiera samo(e) zero(a) w linii!" -> gdy podany parametr to jedno zero lub wiecej i opcjonalnie spacje null
"zawartosc pliku z liczbami pierwszymi ma niepoprawny format! " -> gdy linia zawiera "xx xx", gdzie "x" to liczba, ten warunek sprawdzany jest wywolaniem dodatkowej funkcji conditionleavedigitsonly()
-----------------------------
Przyjmuje parametry:
-input -> typ string, na jego podstawie decyduje sie o wartosci zwracanej przez funkcje, i ewentualnym typie bledow
-errorname -> typ string, w nim zostana zapisane komunikaty o typie bledu lub bledow
-maxvector -> typ uint64_t, zawiera limit ilosci liczb pierwszych
-----------------------------
Zmienne:
-tempinput -> typ string, dodatkowa kopia input-u, ktorej zostanie przypisana wartosc input pozbawiona czesci znakow przez funkcje leavedigitsonly
-tempinput2 -> typ string, dodatkowa kopia input-u, ktorej zostanie przypisana wartosc tempinput uzupelniona do 20 znakow przez zera na poczatku za pomoca funkcji fillzeros()
-bool validity -> typ bool, zawiera informacje o poprawnosci napisu, co jest rownowazne z wartoscia zwracana przez funkcje
-----------------------------
Zwraca wartosci:
-validity==true -> gdy napis jest poprawny i nie spelnil zadnego z warunkow niepoprawnosci zawartych w funkcji
-validity==false ->  gdy ktorys z warunkow nie zostal spelniony i zawartosc input-u nie nadaje sie do wykorzystania w programie
-----------------------------
Uwagi:
Funkcja nie narusza parametrow
WAZNE:!!!Funkcja, jeĹ›li natrafi na niepoprawna dana wejsciowa, moze wypisac stosowny komunikat i zatrzymac wykonywanie calego programu (throw 1), celem zabezpieczenia przed nieprawidlowymi dzielnikami!!!
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
bool isvalidprime(const string &input, const uint64_t lineix, uint64_t maxvector)
{
	string tempinput;
	string tempinput2;
	tempinput = input;
	tempinput = leavedigitsonly(tempinput);
	tempinput2 = fillzeros(tempinput);
	bool validity = true;
	if (lineix == maxvector-1)
	{
		cout << "przekroczono ilosc liczb pierwszych: "<<maxvector<<endl;
		validity = false;
	}
	if (tempinput.size() > 20 || tempinput2 > "18446744073709551615")
	{
		cout << "zawartosc pliku z liczbami pierwszymi przekracza maksymalny rozmiar zmiennej! ";
		validity = false;
	}
	if (isdigital(input) == false)
	{
		cout << "zawartosc pliku z liczbami pierwszymi nie sklada sie z liczb naturalnych! ";
		validity = false;
	}
	if (input == "0" || iszeroonly(input) == true)
	{
		cout << "zawartosc pliku z liczbami pierwszymi zawiera samo(e) zero(a) w linii! ";
		validity = false;
	}
	if (conditionleavedigitsonly(input) == false)
	{
		cout << "zawartosc pliku z liczbami pierwszymi ma niepoprawny format! ";
		validity = false;
	}
	if (validity == false)
	{
		cout << "blad w linii: " << lineix << endl;
		throw 1;
	}
	return validity;
}


/*Funkcja findnextprime() -> odnajduje nastepna liczbe pierwsza po maksymalnej znajdujacej sie w wektorze PrimeV
-----------------------------
Przyjmuje parametry:
-PrimeV -> typ vector <uint64_t>, wektor zawierajacy liczby pierwsze znane programowi
-----------------------------
Zmienne:
-multi -> typ uint64_t, jest informacja o odleglosci kandydata na liczbe pierwsza od najwiekszej znanej juz liczby pierwszej,
na jego podstawie tworzony jest nowy kandydat na liczbe pierwsza ze wzoru maksymalnaznanapierwsza+2*multi, czyli kolejna liczba nieparzysta, mnoznik jest zwiekszany o 1 jesli kandydat okazal sie niepierwszy
-divisorix -> typ uint64_t, indeks liczby z wektora PrimeV na podstawie ktorego obliczana jest reszta z dzielenia z kandydata przez PrimeV[divisorix], zwiekszany o 1 przy niepowodzeniu operacji modulo,
resetowany do 1 po zakonczeniu sprawdzania pierwszenstwa kandydata niezaleznie od wyniku operacji
-candidate -> typ uint64_t, zawiera liczbe bedaca potencjalnym kandydatem na liczbe pierwsza, tworzony jest ze wzoru maksymalnaznanapierwsza+2*multi
przy wywplywaniu funkcji lub niepowodzeniu pierwszenstwa poprzedniego kandydata
-----------------------------
Nie zwraca wartosci, a jedynie dokonuje zmian w wektorze PrimeV dokladajac do niego kolejna liczbe pierwsza
-----------------------------
Uwagi:
Funkcja narusza parametry:
-PrimeV
Funkcja dziala do skutku
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
void findnextprime(vector <uint64_t> &PrimeV)
{
	uint64_t multi = 1;
	uint64_t divisorix = 1;
	uint64_t candidate = PrimeV[PrimeV.size() - 1] + 2 * multi;
	bool primarity = true;
	while (true)
	{
		while (divisorix + 1 <= PrimeV.size())
		{
			if (candidate%PrimeV[divisorix] == 0)
			{
				primarity = false;
				break;
			}
			else
			{
				primarity = true;
				divisorix = divisorix + 1;
			}
		}
		if (primarity == true)
		{
			PrimeV.push_back(candidate);
			break;
		}
		if (primarity == false)
		{
			primarity = true;
			multi = multi + 1;
			candidate = PrimeV[PrimeV.size() - 1] + 2 * multi;
			divisorix = 1;
		}

	}
	return;
}


/*Funkcja decomposition() -> dokonuje rozkladu zadanej liczby naturalnej na czynniki, ktore zapisuje w wektorze DecompoV
-----------------------------
Przyjmuje parametry:
-PrimeV -> typ vector <uint64_t>, wektor zawierajacy liczby pierwsze znane programowi
-DecompoV -> typ vector <uint64_t>, wektor w wyniku dzialania funkcji decomposition() otrzyma czynniki podanej do funkcji liczby, czyli parametru number
-number -> typ uint64_t, liczba ktora funkcja decompositon() ma rozlozyc
-----------------------------
Zmienne:
-dixisorix -> typ uint64_t, indeks liczby z wektora PrimeV przez ktora funkcja proboje dzielic liczbe
-----------------------------
Zwracane wartosci:
0 -> typ int, gdy  podana liczba okazala sie 0 lub 1
-----------------------------
Uwagi:
Funkcja narusza parametry:
-PrimeV
-DecompoV
Funkcja dziala do znalezienia wszystkich czynnikow liczby
Funkcja nie sprawdza poprawnosci podanych danych, poza eliminacja 0 i 1
Funkcja dba o posiadanie potencjalnego dzielnika wywolujac w odpowiedznich momentach funkcje findnextprime() uzupelaniajac tym samym wektor PrimeV o dodatkowy potencjalny czynnik
Podawany wektor PrimeV musi zawierac co najmniej {2,3}
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
int decomposition(vector <uint64_t> &PrimeV, vector <uint64_t> &DecompoV, uint64_t	number)
{
	uint64_t divisorix = 0;
	while (PrimeV[divisorix] <= number)
	{
		if (number == 0 || number == 1)
		{
			return 0;
		}
		if (divisorix == PrimeV.size() - 1)
		{
			findnextprime(PrimeV);
		}
		if (number%PrimeV[divisorix] == 0)
		{
			DecompoV.push_back(PrimeV[divisorix]);

			decomposition(PrimeV, DecompoV, number / PrimeV[divisorix]);
			break;
		}
		else
		{
			divisorix = divisorix + 1;
		}
	}
	return 0;
}


/*Funkcja droptofile() -> zapisuje dane z podanego wektora DecompoV do pliku wyjsciowego o ile te istnieja, jesli nie do strumienia zostanie przeslana pusta linia
-----------------------------
Przyjmuje parametry:
-DecompoV -> typ vector<uint64_t>, wektor z liczbami do zapisu do strumienia
-output ->typ ostream, strumien wyjsciowy do ktorego zostanie przeslana zawartosc wektora DecompoV
-----------------------------
Zmienne:
BRAK
-----------------------------
Zwracane wartosci:
BRAK
-----------------------------
Uwagi:
Funkcja nie narusza parametrow
Funkcja dodaje znak '*' pomiedzy czynniki w strumieniu wyjsciowym
Funkcja zaczyna od przeslania pierwszego, o ile istnieje, elementu wektora bez '*', dopiero kolejne az do ostatniego wypisza sie ze znakeim '*' przed nimi
Funkcja przesyla do strumienia pusta linie jesli wektor DecompoV jest pusty
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
void droptofile(const vector <uint64_t> DecompoV, ostream &output)
{
	if (DecompoV.size() >= 1)
	{
		output << DecompoV[0];
		for (int i = 1; i < DecompoV.size(); i++)
		{
			output << "*" << DecompoV[i];
		}
		output << endl;
	}
	else
	{
		output << endl;
	}
	return;
}



/*Funkcja loadprimes() -> obsluguje zaladowanie liczb pierwszych z danego pliku do wektora PrimesV
-----------------------------
Przyjmuje parametry:
-primesfile ->typ fstream, plik z ktorego czytane sa liczby pierwsze
-primesfilepath -> typ string, sciezka do pliku z liczbami pierwszymi
-PrimeV -> typ, vector<uint64_t>, zawiera liczby pierwsze, do tego wektora zostanie dodana zawartosc pliku z liczbami pierwszymi
-useprimesfromfile -> bool, w zaleznosci od wartosci tego parametru liczby zostana zaladowane (dla true), albo nie (dla false),
funkcja jezeli natrafi na nieprawidlowosc podczas wykonywania zwiazana z poprawnascia pliku lub jego zawartosci zamienia wartosc tej zmiennej zatrzymujac tym samym wszelakie dzialania z zadanym plikiem
-maxvector -> typ uint64_t, zawiera limit ilosci liczb pierwszych, do przeslania do loadprimes
-----------------------------
Zmienne:
-prime -> typ string, zawiera zawartosc liniii z zadanego pliku z liczbami pierwszymi
-lineix ->typ uint64_t, przechowuje indeks linii, ktory przesylany jest do funkcji isvalidprime(), by ta mogla go wypisac jesli dojdzie w niej do bledu
-ui64prime -> typ uint64_t, po konwersji ze string-a prime przechowuje liczbe pierwsza, ktora zostanie dodana do wektora PrimeV
-----------------------------
Zwracane wartosci:
BRAK
-----------------------------
Uwagi:
Funkcja wywoluje, celem sprawdzenia zawartosci ladowanych do wektora liczb, funkcje isvalidprime(), moze zatrzymac wykonywanie programu (throw 1), jesli natrafi na niepoprawna liczbe pierwsza
Funkcja nie laduje "2", ani "3" do wektora, gdyz one juz tam sa z deklaracji
Funkcja narusza parametry:
-PrimeV
Funkcja moze naruszac parametry, w zaleznosci od stanu zadanego pliku, lub jego zawartosci:
useprimesfromfile
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
void loadprimes(fstream &primesfile, const string &primesfilepath, vector<uint64_t> &PrimeV, bool &useprimesfromfile,uint64_t maxvector)
{
	primesfile.open(primesfilepath, ios::in);
	if (primesfile.good() == false)
	{
		printhelp();
		cout << "blad pliku z liczbami pierwszymi! " << endl;
		return;
	}
	if (useprimesfromfile == true)
	{
		string prime;
		uint64_t lineix = 0;
		while (getline(primesfile, prime))
		{
			try
			{
				if (isvalidprime(prime, lineix, maxvector))
				{
					uint64_t ui64prime = 0;

					istringstream(prime) >> ui64prime;

					if (ui64prime == 2 || ui64prime == 3)
					{
						continue;
					}
					PrimeV.push_back(ui64prime);
				}
				else
				{
					PrimeV.erase(PrimeV.begin() + 2, PrimeV.end());
					useprimesfromfile = false;
					//cout << "plik z liczbami pierwszymi zawieral bledy program zostal przerwany" << endl;
					printhelp();
					throw 1;
					break;

				}
				lineix++;
			}
			catch (int x)
			{
				throw 1;
			}
		}
	}
	primesfile.close();
	return;
}


/*Funkcja dropprimes() -> obsluguje zapisanie liczb pierwszych do zadanego pliku
patrz UWAGA WAZNE!!!
-----------------------------
Przyjmuje parametry:
-primesfile -> typ fstream, plik do ktorego zostana zapisane liczby pierwsze z wektora PrimesV
-PrimeV -> vector <uint46_t>, wektor zawierajacy liczby pierwsze, ktore zostana zapisane do pliku primesfile
-primesfilepath -> typ string, zawiera sciezke do pliku z liczbami pierwszymi, gdzie zostana zapisane liczby z wektora PrimesV
-useprimesfromfile -> typ bool, decyduje o wykonaniu funkcji
-----------------------------
Zmienne:
BRAK
-----------------------------
Zwracane wartosci:
BRAK
-----------------------------
Uwagi:
Funkcja narusza parametry:
-PrimesV
Funkcja zapisuje wszystkie elementy z wektora PrimesV do pliku, pomimo, ze funkcja loadprimes() ignoruje "2" i "3"
WAZNE:!!!Funkcja czysci elementy wektora PrimesV od indeksu 2 do konca!!!!
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
void dropprimes(fstream &primesfile, const string &primesfilepath, vector<uint64_t> &PrimeV, bool &useprimesfromfile)
{
	primesfile.open(primesfilepath, ios::out);
	if (primesfile.good() == false)
	{
		printhelp();
		cout << "blad pliku z liczbami pierwszymi! " << endl;
	}
	if (useprimesfromfile == true)
	{
		for (int i = 0; i < PrimeV.size(); i++)
		{
			primesfile << PrimeV[i] << endl;
		}
		primesfile.close();
		PrimeV.erase(PrimeV.begin() + 2, PrimeV.end());
	}
	return;
}


/*Funkcja doparameters() -> odpowiada za przypisanie parametrow podanych funkcji main do odpowiednich zmiennych oraz wywolanie loadprimes(), jezeli podano "-p", celem zaladowania liczb pierwszych do wektotra PrimesV,
jesli pokawilo sie -i albo -o funkcja zmieni wartosc zmiennych isinput oraz isoutput adekwatnie do zawartosci tabeli *params
patrz UWAGI:WAZNE!!!!
-----------------------------
Przyjmuje parametry:
-paramixmax ->typ  int, zawiera informacje o ilosci parametrow podanych do funkcji main
-params -> typ char*, zawiera parametry podane do funkcji main
-inputfilepath -> typ string, temu parametrowi zostanie przypisana sciezka do pliku wejsciowego, o ile zostala podana do funkcji main
-outputfilepath -> typ string, temu parametrowi zostanie przypisana sciezka do pliku wyjsciowego, o ile zostala podana od funkcji main
-primesfile -> typ fstream, strumien plikowy do pliku z liczbami pierwszymi
-primesfilepath -> typ string, temu parametrowi zostanie przypisana sciezka do pliku z liczbami pierwszymi, o ile zostala podana do funkcji main
-useprimesfromfile -> typ bool, jesli podano parametr "-p" do main, to funkcja przypisze temu parametrowi wartosc true i dokona proby wczytania liczb pierwszych, czego niepowodzenie poskutkuje przywroceniem wartosci false dla tego parametru
-PrimeV -> typ vector <uint64_t>, wektor z liczbami pierwszymi, jesli podano parametr "-p" do funkcji main oraz poprawna sciezke do pliku z liczbami pierwszymi, to wektor zostanie dalej przekazany do funkcji loadprimes(),
a nastepnie uzupelniony o liczby z pliku
-isinput -> typ bool, informacja o podaniu sciezki do pliku wejsciowego, modyfikowany adekwatnie do podanych parametrow w tabeli *params[]
-isinput -> typ bool, informacja o podaniu sciezki do pliku wyjsciowego, modyfikowany adekwatnie do podanych parametrow w tabeli *params[]
-maxvector -> typ uint64_t, zawiera limit ilosci liczb pierwszych, do przeslania do loadprimes
-----------------------------
Zmienne:
-tempparam -> typ string, tymczasowo przechowuje kolejne parametry zadane do funkcji przez tabele *params[]
-----------------------------
Zwracane wartosci:
BRAK
-----------------------------
Uwagi:
Funkcja narusza parametry:
-inputfilepath
-outputfilepath
-primesfilepath
-useprimesfromfile
-PrimeV
-isinput
-isoutput
Funkcja nie narusza:
-paramixmax
-*params[]
Funkcja moze wywolywac funkcje loadprimesfromfile();
WAZNE:!!!Funkcja moĹĽe przerwac wykonywanie programu (throw 1) jesli podany plik z liczbami pierwszymi okazal sie niepoprawny!!!
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
void doparameters(int paramixmax, char*params[], string &inputfilepath, string &outputfilepath, fstream &primesfile, string &primesfilepath, bool &useprimesfromfile, vector<uint64_t> &PrimeV, bool &isinput, bool &isoutput,uint64_t maxvector)
{
	for (int i = 0; i < paramixmax; i++)
	{

		string tempparam = params[i];
		//cout << tempparam << endl;
		if (tempparam == "-h" || tempparam == "--h")
		{
			printhelp();
		}
		if (tempparam == "-i" || tempparam == "--i")
		{
			inputfilepath = params[i + 1];
			isinput = true;

		}
		if (tempparam == "-o" || tempparam == "--o")
		{
			outputfilepath = params[i + 1];
			isoutput = true;
		}
		if (tempparam == "-p" || tempparam == "--p")
		{
			useprimesfromfile = true;
			primesfilepath = params[i + 1];
			if (primesfile.good() == true)
			{
				try
				{
					loadprimes(primesfile, primesfilepath, PrimeV, useprimesfromfile,maxvector);
				}
				catch (int x)
				{
					throw 2;
				}
			}
			else
			{
				//cout << "niepoprawny plik z liczbami pierwszymi" << endl;
				useprimesfromfile = false;
				throw 1;
			}
		}
	}
	return;
}


/*Funkcja streamfunction() -> pobiera linie z pliku, obsluguje wywolanie ich przetworzenia (sprawdzenie i rozlozenie na czynniki), moze wywolywac decomposition(), droptofile(), isvalid()
patrz UWAGA WAZNE!!!
-----------------------------
Przyjmuje parametry:
-input -> typ istream, strumien wejscia, z ktorego beda czytane kolejne linie
-onput -> typ ostream, strumien wyjscia, do ktorego beda zapisywane kolejne linie
-errorname -> typ string, pusty z deklaracji i czyszczony po kazdej kolejnej linii, po wykonaniu sprawdzenie poprawnosci przez funkcje isvalid() bedzie zawieral komunikat o typie lub typach bledow
-PrimeV -> typ vector<uint64_t>, zawiera liczby pierwsze potrzebne funkcji decomposition() do rozlozenia liczby
-DecompoV  -> typ vector<uint64_t>, pusty z deklaracji, bedzie zawieral czynniki zadanej w linii liczby o ile ta bedzie poprawna , po kazdym zapisie do pliku jest caĹ‚kowicie czyszczony
-----------------------------
Zmienne:
-line -> typ string, poprzez wykonanie funkcji bedzie zawieral komunikaty o bledach we wprowadzonej linii, po wykonaniu funkcji bedzie pusty
-ui64input -> typ ui64_4, do niego zostanie zapisana liczba z linii, o ile funkcja isvalid() zwrocila prawde, stwierdzajac tym samym poprawnosc zawartosci linii
-----------------------------
Zwracane wartosci:
BRAK
-----------------------------
Uwagi:
Funkcja narusza parametry:
-PrimeV
-DecompoV
-errorname
WAZNE:!!!Funkcja pozostawia zawsze wektor DecompoV oraz string erroname puste!!!
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
void streamfunction(istream & input, ostream & output, string &errorname, vector<uint64_t> &PrimeV, vector<uint64_t> &DecompoV)
{
	string line = "";
	while (getline(input, line))
	{
		try
		{
			if (isvalid(line, errorname))
			{
				uint64_t ui64input = 0;
				istringstream(line) >> ui64input;
				decomposition(PrimeV, DecompoV, ui64input);
				droptofile(DecompoV, output);
				DecompoV.erase(DecompoV.begin(), DecompoV.end());
			}
			else
			{
				output << errorname << endl;
			}
		}
		catch (int x)
		{
			throw 1;
		}
		errorname = "";
	}
	return;
}


/*Funkcja main() ->
-----------------------------
Przyjmuje parametry:
-paramixmax -> typ int, ilosc parametrow podanych z linii polecen
-params -> typ char[], tablica z parametrami
-----------------------------
Zmienne:
-inputfilepath -> typ string,
-outputfilepath -> typ string,
-errorname -> typ string, baza dla ewentualnych komunikatow o bledach w strumieniu wejscia
-inputfile -> typ fstream, deklaracja strumienia plikowego wejsciowego
-outputfile -> typ fstream, deklaracja strumienia plikowego wyjsciowego
-primesfile -> typ fstream, deklaracja strumienia plikowego dla liczb pierwszych
-primeV -> typ vector<uint64_t>, zawiera liczby pierwsze, zadeklarowano z gory "2" i "3", ktroe sa warunkiem poprawnego dzialania programu, gdyz na ich podstawie beda znajdowane kolejne liczby pierwsze, o ile beda potrzebne
-DecompoV -> typ vector <uint64_t>, pusty z deklaracji, zostanie uzupelniony o czynniki pierwsze zadanej w strumieniu liczby
-useprimesfromfile -> typ bool, zawiera infromacje o przyzwoleniu na uzycie pliku z liczbami pierwszymi, zadeklarowane jako false, moze stac sie true w wyniku dzialania funkcji doparameters()
-isinput -> typ bool, zawiera informacje o tym czy zostal podany parametr -i do funkcji, co rozstrzyga funkcja doparameters()
-isoutput -> typ bool, zawiera informacje o tym czy zostal podany parametr -o do funkcji, co rozstrzyga funkcja doparameters()
-maxvector -> typ uint64_t, zawiera limit ilosci liczb pierwszych
-----------------------------
Zwracane wartosci:
-0 -> typ int, konczy wykonywanie programu
-----------------------------
Uwagi:
Funkcja kluczowa programu
Funkcja na podstawie wywolania funkcji doparameters() decduje o sposobie wywolania funkcji streamfunction(), odpowiedzialnej za przeprowadzenie rozkladu na czynniki liczb ze strumienia wejscowego
Funkcja zabezpiecza zapis liczb pierwszych do pliku, o podano parametr "-p"
Parametry podane do funkcji main sa interpretowane przez funkcje doparameters
-----------------------------
Autor:
Tomasz Skowron 2017-11-30
*/
int main(int paramixmax, char*params[])
{
	string inputfilepath = "";
	string outputfilepath = "";
	string errorname = "";
	string primesfilepath = "";
	fstream inputfile;
	fstream outputfile;
	fstream primesfile;
	vector <uint64_t> PrimeV = { 2,3 };
	vector <uint64_t> DecompoV;
	uint64_t maxvector=PrimeV.max_size();
	bool useprimesfromfile = false;
	bool isinput = false;
	bool isoutput = false;
	try
	{
		doparameters(paramixmax, params, inputfilepath, outputfilepath, primesfile, primesfilepath, useprimesfromfile, PrimeV, isinput, isoutput, maxvector);
	}
	catch (int x)
	{
        switch (x)
        {
            case 1:  cerr << "niepoprawny plik z liczbami pierwszymi" << endl;
		    return 0;
            case 2: cerr << "plik z liczbami pierwszymi zawieral bledy, program zostal przerwany" << endl;
            return 0;
        }
	}
	try
	{
		if (isinput == false && isoutput == false)
		{
			streamfunction(cin, cout, errorname, PrimeV, DecompoV);
		}
		if (isinput == true && isoutput == false)
		{
			inputfile.open(inputfilepath, ios::in);
			if (inputfile)
			{
				streamfunction(inputfile, cout, errorname, PrimeV, DecompoV);
				inputfile.close();
			}
			else
			{
				cout << "niepoprawny plik wejsciowy" << endl;
				useprimesfromfile = false;
				printhelp();
			}
		}
		if (isinput == false && isoutput == true)
		{
			outputfile.open(outputfilepath, ios::out);
			if (outputfile)
			{
				streamfunction(cin, outputfile, errorname, PrimeV, DecompoV);
				outputfile.close();
			}
			else
			{
				cout << "niepoprawny plik wyjsciowy" << endl;
				useprimesfromfile = false;
				printhelp();
			}
		}

		if (isinput == true && isoutput == true)
		{
			inputfile.open(inputfilepath, ios::in);
			outputfile.open(outputfilepath, ios::out);
			if (inputfile)
			{
				if (outputfile)
				{
					streamfunction(inputfile, outputfile, errorname, PrimeV, DecompoV);
					inputfile.close();
					outputfile.close();
				}
				else
				{
					cout << "niepoprawny plik wyjsciowy" << endl;
					useprimesfromfile = false;
					printhelp();
				}
			}
			else
			{
				cout << "niepoprawny plik wejsciowy" << endl;
				useprimesfromfile = false;
				printhelp();
			}

		}
		if (useprimesfromfile == true)
		{
			dropprimes(primesfile, primesfilepath, PrimeV, useprimesfromfile);
		}
	}
	catch (int x)
	{
        
		return 1;
	}

	return 0;
}
