// KOD VIGENERE'A Mateusz Walasz grupa 3 sekcja 7

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

/*
Funkcja zmieniajaca male litery klucza na duze.
parametry funkcji:
__________________
klucz - jest to tekst typu string, ktory jest przekazywany do funkcji w celu zmiany wielkosci liter
wartosc zwracana:
_________________
duzyKlucz - jest to klucz ze zmienionym rozmiarem liter
*/
string zmianaWielkosciLiterKlucza(string & klucz)
{
	string duzyKlucz; //zmienna typu string przechowujaca klucz zapisanymi wielkimi literami
	string x; //zmienna pomocnicza
	for (int i = 0; i < klucz.length(); i++)
	{
		if (klucz[i] > 96 && klucz[i] < 123) //jesli litera klucza jest mala litera to jest zmieniana na duze
		{
			x = toupper(klucz[i]);
		}
		else if (klucz[i] > 64 && klucz[i] < 91) // litera klucza jest wielka
		{
			x = klucz[i];
		}
		duzyKlucz = duzyKlucz + x; //skladanie klucza zlozonego z duzych liter, litera po literze
	}
	return duzyKlucz;
}

/*
Funkcja sprawdzajaca czy w przekazanym do niej tekscie znajduja sie niedozwolone znaki specjalne lub cyfry.
parametry funkcji. Funkcja pomija znaki takie jak: , . ? 

__________________
wejscie - jest to tekst typu string, ktory jest przekazywany do funkcji w celu sprawdzenia obecnosci znakow niedozwolonych.
wartosc zwracana:
_________________
true  - gdy nie wykryto znakow niedozwolonych
false - gdy wykryto chociaz jeden znak niedozwolony
*/
bool sprawdzenieZnakowSpecjalnychOrazLiczb(string & wejscie)
{
	int j = 0; //naliczanie wystapien znakow niedozwolonych
	for (int i = 0; i < wejscie.size(); i++)
	{
		if ((wejscie[i] > 35 && wejscie[i] < 65 && wejscie[i] != 44 && wejscie[i] != 46) || (wejscie[i] > 90 && wejscie[i] < 97) || (wejscie[i] > 122 && wejscie[i] < 255)) //jesli jeden ze znakow tekstu jest znakiem specjalnym lub cyfra			
			j++; 	}
	if (j > 0)
		return false; //sa znaki
	else return true; //brak znakow
}

/*
Funkcja zmieniajaca male litery na duze tekstu przekazywanego za pomoca zmiennej wejscie .
parametry funkcji:
__________________
wejscie - jest to tekst typu string, ktory jest przekazywany do funkcji w celu zmiany wielkosci liter
wartosc zwracana:
_________________
wyjscie - jest to tekst typu string w ktorym zostala zmieniona wielkosc liter na wielkie
*/
string zmianaWielkosciLiterTekstu(string wejscie)
{
	char x; //zmienna pomocnicza przechowujaca pojedyncze litery w trakcie zmiany wielkosci
	string wyjscie; //zwracany string ze zmieniona wielkoscia liter

	for (int i = 0; i < wejscie.size(); i++)
	{
		if (wejscie[i] > 96 && wejscie[i] < 123) //jesli litera tekstu jest zapisana mala litera to jest zmieniana na wielka litere
		{
			x = toupper(wejscie[i]);
		}
		else if (wejscie[i] > 64 && wejscie[i] < 91) // jesli jest zapisana wielka litera , to jest pozostawiana bez zmian
			x = wejscie[i];
		else if (wejscie[i] == 44) //znak przecinka, pozostawiany bez zmian
			x = 44;
		else if (wejscie[i] == 46) //znak kropki, pozostawiany bez zmian
			x = 46;
		else if (wejscie[i] == 32) //znak spacji, pozostawiany bez zmian
			x = 32;

		wyjscie += x;//skladanie tekstu
	}
	return wyjscie;
}

/*
Funkcja deszyfrujaca przekazany do niej tekst, na podstawie klucza, ktory rowniez zostal przekazany do funkcji.
parametry funkcji:
__________________
tekstZaszyfrowany  - parametr, ktory przekazuje do funkcji tekst przeznaczony do deszyfrowania
klucz              - parametr, ktory przekazuje do funkcji slowo kluczowe na podstawie ktorego odbedzie sie deszyfrowanie

wartosc zwracana:
_________________
tekstOdszyfrowany  - tekst typu string, ktory zostal pomyslnie odszyfrowany na podstawie klucza
*/
string deszyfrowanie(const string & tekstZaszyfrowany, string & klucz)
{
	klucz = zmianaWielkosciLiterKlucza(klucz);

	string tekstOdszyfrowany; //zmienna do ktorej zapisywany jest deszyfrowany tekst
	int i, j; //zmienne używane w pętli for, która analizuje kazda litere z osobna (i - odnosnie tekstu, j - odnosnie klucza)
	int znak; //zmienna do ktorej przypisywana jest wartosc ascii litery tekstu odszyfrowanego

	for (i = 0, j = 0; i < tekstZaszyfrowany.length(); i++, j++)
	{
		if (j >= klucz.length()) //porownywanie dlugosci wprowadzonego tekstu oraz klucza, jesli tekst jest dluzszy niz klucz, to jest on wielokrotnie powielany
			j = 0;

		if (tekstZaszyfrowany[i] >= 'A' && tekstZaszyfrowany[i] <= 'Z')	//sprawdzenie czy i-ta litera zawiera sie w zbiorze liter od "A" do "Z"
			znak = ((tekstZaszyfrowany[i] - 'A') - (klucz[j] - 'A') + 26) % 26; //pojedynczy znak 
		else //pozostale litery
			znak = tekstZaszyfrowany[i] - 'A';  

		tekstOdszyfrowany += (char)(znak + 'A'); //sumowanie wszystkich wygenerowanych liter, typ jest zmieniany na char metoda rzutowania
	}
	return tekstOdszyfrowany;
}

/*
Funkcja szyfrujaca przekazany do niej tekst, na podstawie klucza, ktory rowniez zostal przekazany do funkcji.
parametry funkcji:
__________________
tekstOdszyfrowany  - parametr, ktory przekazuje do funkcji tekst przeznaczony do szyfrowania
klucz              - parametr, ktory przekazuje do funkcji slowo kluczowe na podstawie ktorego odbedzie sie szyfrowanie
wartosc zwracana:
_________________
tekstZaszyfrowany  - tekst typu string, ktory zostal pomyslnie zaszyfrowany na podstawie klucza
*/
string szyfrowanie(const string & tekstOdszyfrowany, string & klucz)
{
	klucz = zmianaWielkosciLiterKlucza(klucz);

	string tekstZaszyfrowany; //zmienna do ktorej zapisywany jest szyfrowany tekst
	int i, j; //zmienne używane w pętli for, która analizuje kazda litere z osobna (i - odnosnie tekstu, j - odnosnie klucza)
	int znak; //zmienna do ktorej przypisywana jest wartosc ascii litery tekstu zaszyfrowanego

	for (i = 0, j = 0; i < tekstOdszyfrowany.length(); i++, j++)
	{
		if (j >= klucz.length()) //porownywanie dlugosci wprowadzonego tekstu oraz klucza, jesli tekst jest dluzszy niz klucz, to jest on wielokrotnie powielany
			j = 0;

		if (tekstOdszyfrowany[i] >= 'A' && tekstOdszyfrowany[i] <= 'Z') //sprawdzenie czy i-ta litera zawiera sie w zbiorze liter od "A" do "Z"
			znak = ((tekstOdszyfrowany[i] - 'A') + (klucz[j] - 'A')) % 26;
		else
			znak = tekstOdszyfrowany[i] - 'A';
		tekstZaszyfrowany += (char)(znak + 'A'); //sumowanie wszystkich wygenerowanych liter, typ jest zmieniany na char metoda rzutowania
	}
	return tekstZaszyfrowany;
}

/*
Funkcja odczytujaca tekst typu string z pliku, a nastepnie zapisujaca go do zmiennej wejscie.
parametry funkcji:
__________________
nazwaPliku - jest to nazwa pliku z ktorego maja zostac odczytane dane
wartosc zwracana:
_________________
ERROR            - zwraca string "ERROR" w przypadku gdy nie powiodlo sie otwarcie pliku 
polaczoneLinijki - zmienna przechowujaca wszystkie linijki odczytanego z pliku tekstu
*/
string odczytZPliku(const string & nazwaPliku)
{
	string wejscie; //tekst typu string, ktory zawiera dane odczytane z pliku o podanej nazwie
	string polaczoneLinijki; //zmienna przechowujaca kolejne odczytane z pliku linijki
	ifstream plik(nazwaPliku);

	if (plik.good())
	{
			while (plik >> wejscie)
				polaczoneLinijki = polaczoneLinijki + wejscie + " ";

			plik.close();
			return polaczoneLinijki;
	}
	else
	{
		return "ERROR";
	}
}

/*
Funkcja zapisujaca tekst typu string do pliku o wybranej nazwie.
parametry funkcji:
__________________
nazwaPliku     - jest to nazwa pliku do ktorego maja zostac zapisane dane
daneDoZapisu   - jest to tekst typu string, ktory zostaje przekazany do funkcji w celu zapisania go w pliku
wartosc zwracana:
_________________
Funkcja nie zwraca wartosci, poniewaz jest typu void.
*/
void zapisDoPliku(const string & nazwaPliku, const string & daneDoZapisu)
{
	ofstream plik(nazwaPliku); //otwarcie pliku

	if (plik.good())
	{
		plik << daneDoZapisu;

		plik.close();
	}
	else cout << "Blad w trakcie otwierania podanego pliku wejsciowego!";
}

/*
Funkcja wyswietlajaca pomocne informacje dotyczace uzytkowania programu.
parametry funkcji:
__________________
brak
wartosc zwracana:
_________________
Funkcja nie zwraca wartosci, poniewaz jest typu void.
*/
void wyswietlPomoc()
{
	cout << "Pomoc:" << endl;
	cout << "Program obsluguje nastepujace przelaczniki:\n   -i - odczytanie z linii polecen nazwy pliku wejsciowego,\n   -o - odczytanie z linii polecen nazwy pliku wynikowego,\n   -k - wprowadzenie klucza,\n   -s - szyfrowanie tekstu,\n   -d - deszyfrowanie tekstu." << endl;
	cout << endl << "Aby poprawnie uruchomic program nalezy:\n wybrac -s (szyfrowanie) lub -d (deszyfrowanie),\n wprowadzic klucz po przelaczniku -k,\n wprowadzic nazwe pliku wejsciowego po przelaczniku -i,\n wprowadzic nazwe pliku wyjsciowego po przelaczniku -o. " << endl;
}

/*
Funkcja odczytujaca parametry przekazywane w trakcie uruchamiania programu pod postacia nastepujacych przelacznikow:
-i nazwa - nazwa pliku wejsciowego
-o nazwa - nazwa pliku wyjsciowego
-k klucz - wczytywanie klucza do szyfrowania lub deszyfrowania tekstow
-h       - wyswietlenie pomocy
-s       - wybranie trybu szyfrowania
-d       - wybranie trybu deszyfrowania

Moga byc one podawane w dowolnej kolejnosci. Nie podanie zadnego parametru, spowoduje wyswietlenie pomocy. Prawidlowa ilosc parametrow wynosi 7.
parametry funkcji:
__________________
argc				  - liczba parametrow przy uruchamianiu programu
argv			      - tablica zawierajaca wskazniki przy uruchamianiu programu
klucz				  - parametr do ktorego zostanie zapisany klucz do szyfrowania lub deszyfrowania tekstow
nazwaPlikuWejsciowego - parametr do ktorego zostanie zapisana nazwa pliku wejsciowego
nazwaPlikuWyjsciowego - parametr do ktorego zostanie zapisana nazwa pliku wyjsciowego

wartosc zwracana:
_________________
1 - wywolanie pomocy
3 - wprowadzono bledna ilosc parametrow, wyswietlany jest komunikat o bledzie
4 - wybrano szyfrowanie
5 - wybrano deszyfrowanie
*/
int wywolanie(int argc, char* argv[], string & nazwaPlikuWejsciowego, string & nazwaPlikuWyjsciowego, string & klucz)
{
	if (argc == 8)
	{
		for (int i = 1; i < argc; i++)
		{
			if (string(argv[i]) == string("-h")) //wywolanie pomocy
				return 1;

			if (string(argv[i]) == string("-i")) //wczytanie nazwy pliku wejsciowego
			{
				nazwaPlikuWejsciowego = string(argv[i + 1]);
			}

			if (string(argv[i]) == string("-o")) //wczytanie nazwy pliku wyjsciowego
			{
				nazwaPlikuWyjsciowego = string(argv[i + 1]);
			}

			if (string(argv[i]) == string("-k")) //pobranie klucza wedlug ktorego nastapia operacje szyfrowania/deszyfrowania
			{
				klucz = string(argv[i + 1]);
			}

			if (string(argv[i]) == string("-s")) //jesli wprowadzono -s oznacza to ze wybrano szyfrowanie
			{
				return 4;
			}

			if (string(argv[i]) == string("-d")) //jesli wprowadzono -d oznacza to ze wybrano deszyfrowanie
			{
				return 5;
			}
		}
	}
	else if (argc == 2) //gdy wpisano tylko h to wywola sie pomoc
	{
		for (int i = 1; i < argc; i++)
		{
			if (string(argv[i]) == string("-h")) //wywolanie pomocy
				return 1;
		}
	}
	else if (argc == 1) //gdy nie wprowadzono zadnego parametru wyswietlana jest pomoc
		return 1;
	else return 3; //gdy wprowadzono bledna ilosc parametrow wyswietlany jest komunikat o bledzie
}

int main(int argc, char* argv[])
{
	string plikWejsciowy; //nazwa pliku z ktorego zostana pobrane dane
	string plikWyjsciowy; //nazwa pliku do ktorego zostana zapisane dane
	string klucz; //klucz wedlug ktorego nastapi szyfrowanie lub deszyfrowanie tekstu

	string odczytanyTekstZPliku; //tekst pobrany z pliku wejsciowego
	string zmienionaWielkosc; //zmienna pomocnicza przechowujaca tekst odczytany z pliku po zmianie wielkosci

	string zaszyfrowanyTekst; //tekst bedacy wynikiem funkcji szyfrujacej
	string odszyfrowanyTekst; //tekst bedacy wynikiem funkcji deszyfrujacej

	int parametryWywolaniaProgramu = wywolanie(argc, argv, plikWejsciowy, plikWyjsciowy, klucz); //zmienna, ktora przyjmuje wartosci funkcji wywolanie

	switch (parametryWywolaniaProgramu)
	{
	case 0://blad otwarcia pliku wejsciowego
		cout << endl << "Wystapil blad w trakcie otwierania pliku wejsciowego." << endl << endl;
		wyswietlPomoc();
		break;

	case 1: //wyswietlanie pomocy
		wyswietlPomoc();
		break;

	case 3: //niepoprawna ilosc parametrow
		cout << endl << "Wprowadzono nieprawidlowa liczbe parametrow!" << endl << endl;
		wyswietlPomoc();
		break;

	case 4: // szyfrowanie
		
		odczytanyTekstZPliku = odczytZPliku(plikWejsciowy);
		if (sprawdzenieZnakowSpecjalnychOrazLiczb(odczytanyTekstZPliku) != true) //sprawdzenie zawartosci pliku pod wzgledem znakow niedozwolonych
			cout << "Wykryto niedozwolone znaki!";
		else
		{
			zmienionaWielkosc = zmianaWielkosciLiterTekstu(odczytanyTekstZPliku);
			odczytanyTekstZPliku = zmienionaWielkosc;

			if (odczytanyTekstZPliku == "ERROR") //sprawdzenie czy plik zostal poprawnie otwarty
				cout << "Blad podczas otwierania pliku wejsciowego!";
			else if (odczytanyTekstZPliku.empty()) //sprawdzenie czy plik wejsciowy jest pusty
				{
					cout << "Plik wejsciowy jest pusty!";
				}
				else
				{
					if (odczytanyTekstZPliku.size() == 1) //sprawdzenie wielkosci zawartosci pliku
						cout << "Dane w pliku wejsciowym sa za krotkie!";
					else
					{
						zaszyfrowanyTekst = szyfrowanie(odczytanyTekstZPliku, klucz);
						zapisDoPliku(plikWyjsciowy, zaszyfrowanyTekst);

						cout << "Wybrano szyfrowanie: " << endl << endl;
						cout << "Z pliku pobrano nastepujacy tekst: \n" << odczytanyTekstZPliku << "." << endl;
						cout << endl << "Tekst zaszyfrowany to: \n" << zaszyfrowanyTekst << "." << endl;
					}
				}
			
		}
		break;

	case 5: // deszyfrowanie
		
			odczytanyTekstZPliku = odczytZPliku(plikWejsciowy);
			if (sprawdzenieZnakowSpecjalnychOrazLiczb(odczytanyTekstZPliku) != true) //sprawdzenie zawartosci pliku pod wzgledem znakow niedozwolonych
				cout << "Wykryto niedozwolone znaki!";
			else
			{
				zmienionaWielkosc = zmianaWielkosciLiterTekstu(odczytanyTekstZPliku);
				odczytanyTekstZPliku = zmienionaWielkosc;

				if (odczytanyTekstZPliku == "ERROR") //sprawdzenie czy plik zostal poprawnie otwarty
					cout << "Blad podczas otwierania pliku wejsciowego!";
				else if (odczytanyTekstZPliku.empty()) //sprawdzenie czy plik wejsciowy jest pusty
					{
						cout << "Plik wejsciowy jest pusty!";
					}
					else
					{
						if (odczytanyTekstZPliku.size() == 1) //sprawdzenie czy w pliku wejsciowym nie znajduje sie tylko jeden znak
							cout << "Dane w pliku wejsciowym sa za krotkie!";
						else
						{
							odszyfrowanyTekst = deszyfrowanie(odczytanyTekstZPliku, klucz);
							zapisDoPliku(plikWyjsciowy, odszyfrowanyTekst);
							cout << "Wybrano deszyfrowanie: " << endl << endl;
							cout << "Z pliku pobrano nastepujacy tekst: \n" << odczytanyTekstZPliku << endl;
							cout << endl << "Tekst odszyfrowany to: \n" << odszyfrowanyTekst << endl;
						}
					}
			}
		break;

	default:
		wyswietlPomoc();
		break;
	}
	return 0;
}
