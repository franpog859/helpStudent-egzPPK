//W 84 i 85 linijce możliwa jest łatwa zmiana znaku (*) i ( )

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
Funkcja łącząca poszczególne części znaku Braille'a i zwracająca je w formie stringa.
Dla odpowiedniego rzędu jaki jest wypisywany, funkcja zwróci odpowiedni rząd ze znaku.

parametry funkcji:
----------------------------------------------------------------------------------------------------
ktory_rzad_znaku_braille -- Cyfra reprezentująca numer obecnie przerabianej linjki pojedynczego wiersza znaków np.( pierwsza z trzech )
wyglad_znaku_braille     -- Tabela reprezentująca wygląd pojedynczego znaku Braille'a

wartosc zwracana:
----------------------------------------------------------------------------------------------------
jedna_trzecia_znaku  -- Jedna trzecia znaku Braille'a + biały znak

uwagi:
----------
brak

autor: Roman Zemeła
2017-11-30
*/

string wypisz_rzad_ze_znaku_braille(int ktory_rzad_znaku_braille, char wyglad_znaku_braille[3][2]) 
{
	string jedna_trzecia_znaku="__ "; // 2 części znaku i następująca po nich spacja
	switch (ktory_rzad_znaku_braille)
	{
		case 1:
			{
			jedna_trzecia_znaku[0] = wyglad_znaku_braille[0][0];
			jedna_trzecia_znaku[1] = wyglad_znaku_braille[0][1];
			break;
			}
		case 2:
			{
			jedna_trzecia_znaku[0] = wyglad_znaku_braille[1][0];
			jedna_trzecia_znaku[1] = wyglad_znaku_braille[1][1];
			break;
			}
		case 3:
			{
			jedna_trzecia_znaku[0] = wyglad_znaku_braille[2][0];
			jedna_trzecia_znaku[1] = wyglad_znaku_braille[2][1];
			break;
			}
	}
	return jedna_trzecia_znaku;
}

/*
Funkcja przekazująca funkcji wypisz_rzad_ze_znaku_braille tabelę z reprezentacją potrzebnego symbolu.
Dodatkowo w przypadku napotkania niedozolonego symbolu, wypisze stosowne powiadomienie.

parametry funkcji:
----------------------------------------------------------------------------------------------------
znak_z_pliku		     -- Znak z pliku jaki program ma obecnie przerobić na Braille'a
ktory_rzad_znaku_braille -- Cyfra reprezentująca numer obecnie przerabianej linjki pojedynczego wiersza znaków np.( pierwsza z trzech )

wartosc zwracana:
----------------------------------------------------------------------------------------------------

wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille) -- zwracany jest odpowiedni string zawierający reprezentację jednej trzeciej znaku Braille'a, wraz z następującym
po nim odstępem

uwagi:
----------
W 84 i 85 linii kodu możliwa prosta zmiana znaku (*) i ( )
W przypadku napotkania niedozwolonego symbolu funkcja zwróci stringa "?? ", umożliwiając dalsze tłumaczenie pliku wejściowego

autor: Roman Zemeła
2017-11-30
*/

string znaki_na_braille(char znak_z_pliku, int ktory_rzad_znaku_braille)
{
	const char X = '*';  //łatwa zmiana znaku  *
	const char _ = ' ';  //łatwa zmiana znaku " "

	switch (znak_z_pliku)
	{
	case 'a':
	case 'A':
	case '1':
	{
		char wyglad_znaku_braille[3][2]{ X,_,_,_,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ą':
	case 'Ą':
	{
		char wyglad_znaku_braille[3][2]{ X,_,_,_,_,X };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'b':
	case 'B':
	case '2':
	{
		char wyglad_znaku_braille[3][2]{ X,_,X,_,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'c':
	case 'C':
	case '3':
	{
		char wyglad_znaku_braille[3][2]{ X,X,_,_,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ć':
	case 'Ć':
	{
		char wyglad_znaku_braille[3][2]{ X,X,_,_,_,X };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'd':
	case 'D':
	case '4':
	{
		char wyglad_znaku_braille[3][2]{ X,X,_,X,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'e':
	case 'E':
	case '5':
	{
		char wyglad_znaku_braille[3][2]{ X,_,_,X,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ę':
	case 'Ę':
	{
		char wyglad_znaku_braille[3][2]{ X,_,_,X,_,X };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'f':
	case 'F':
	case '6':
	{
		char wyglad_znaku_braille[3][2]{ X,X,X,_,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'g':
	case 'G':
	case '7':
	{
		char wyglad_znaku_braille[3][2]{ X,X,X,X,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'h':
	case 'H':
	case '8':
	{
		char wyglad_znaku_braille[3][2]{ X,_,X,X,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'i':
	case 'I':
	case '9':
	{
		char wyglad_znaku_braille[3][2]{ _,X,X,_,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'j':
	case 'J':
	case '0':
	{
		char wyglad_znaku_braille[3][2]{ _,X,X,X,_,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'k':
	case 'K':
	{
		char wyglad_znaku_braille[3][2]{ X,_,_,_,X,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'l':
	case 'L':
	{
		char wyglad_znaku_braille[3][2]{ X,_,X,_,X,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ł':
	case 'Ł':
	{
		char wyglad_znaku_braille[3][2]{ X,_,X,_,_,X };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'm':
	case 'M':
	{
		char wyglad_znaku_braille[3][2]{ X,X,_,_,X,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'n':
	case 'N':
	{
		char wyglad_znaku_braille[3][2]{ X,X,_,X,X,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ń':
	case 'Ń':
	{
		char wyglad_znaku_braille[3][2]{ X,X,_,X,_,X };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'o':
	case 'O':
	{
		char wyglad_znaku_braille[3][2]{ X,_,_,X,X,_ };
		return wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'p':
	case 'P':
	{
		char wyglad_znaku_braille[3][2]{ X,X,X,_,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'q':
	case 'Q':
	{
		char wyglad_znaku_braille[3][2]{ X,X,X,X,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'r':
	case 'R':
	{
		char wyglad_znaku_braille[3][2]{ X,_,X,X,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 's':
	case 'S':
	{
		char wyglad_znaku_braille[3][2]{ _,X,X,_,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ś':
	case 'Ś':
	{
		char wyglad_znaku_braille[3][2]{ _,X,X,_,_,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 't':
	case 'T':
	{
		char wyglad_znaku_braille[3][2]{ _,X,X,X,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'u':
	case 'U':
	{
		char wyglad_znaku_braille[3][2]{ X,_,_,_,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ó':
	case 'Ó':
	{
		char wyglad_znaku_braille[3][2]{ _,X,_,_,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'v':
	case 'V':
	{
		char wyglad_znaku_braille[3][2]{ X,_,X,_,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'w':
	case 'W':
	{
		char wyglad_znaku_braille[3][2]{ _,X,X,X,_,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'x':
	case 'X':
	{
		char wyglad_znaku_braille[3][2]{ X,X,_,_,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'y':
	case 'Y':
	{
		char wyglad_znaku_braille[3][2]{ X,X,_,X,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ż':
	case 'Ż':
	{
		char wyglad_znaku_braille[3][2]{ X,X,X,_,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'z':
	case 'Z':
	{
		char wyglad_znaku_braille[3][2]{ X,_,_,X,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 'ź':
	case 'Ź':
	{
		char wyglad_znaku_braille[3][2]{ _,X,X,_,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case '$': //znak $ sygnalizuje zapis cyfry	
	{
		char wyglad_znaku_braille[3][2]{ _,X,_,X,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case ',': 
	{
		char wyglad_znaku_braille[3][2]{ _,_,X,_,_,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case ';': 
	{
		char wyglad_znaku_braille[3][2]{ _,_,X,_,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case ':':
	{
		char wyglad_znaku_braille[3][2]{ _,_,X,X,_,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case '-':
	{
		char wyglad_znaku_braille[3][2]{ _,_,_,_,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case '.':
	{
		char wyglad_znaku_braille[3][2]{ _,_,X,X,_,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case '!':
	{
		char wyglad_znaku_braille[3][2]{ _,_,X,X,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case '?':
	case '@': // @ służy jako oznaczenie otwarcia cudzysłowia
	{
		char wyglad_znaku_braille[3][2]{ _,_,X,_,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case '"': // " zostanie użyty tylko w przypadku zamykającego cudzysłowia
	{
		char wyglad_znaku_braille[3][2]{ _,_,_,X,X,X };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case '(':
	case ')':
	case '{':
	case '}':
	case '[':
	case ']':
	case '<':
	case '>':
	{
		char wyglad_znaku_braille[3][2]{ _,_,X,X,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case '/':
	{
		char wyglad_znaku_braille[3][2]{ _,X,_,_,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case ' ':
	{
		char wyglad_znaku_braille[3][2]{ _,_,_,_,_,_ };
		return 		wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	case 39: // dla znaku '
	{
		char wyglad_znaku_braille[3][2]{ _,_,_,_,X,_ };
		return 	wypisz_rzad_ze_znaku_braille(ktory_rzad_znaku_braille, wyglad_znaku_braille);
		break;
	}
	default: //wypisze na kosnoli "Wystąpił niedozwolony znak" i pliku tekstowym tabelę[3][2]{?,?,?,?,?,?}
	{
		switch (ktory_rzad_znaku_braille)
		{
			case 1:
				{
				break;
				}
			case 2:
				{
				break;
				}
			case 3:
				{
				cout << "Wystapil niedozwolony znak uzyj parametru -h by dowiedziec sie wiecej" << endl;
				break;
				}		
		}
		return  "?? ";
		break;
	}
	}
}
/*
Funkcja pobierająca linię znaków z pliku wejściowego, zapisująca ją jako string,a następnie odczytująca z niego następujące po sobie znaki.
Dokonuje ona odpowiednich porównań, by zawartość pliku tekstowego była poprawna wzgzlędem zasad dotyczących alfabetu Braille'a.
Dodatkowo scala ona ze sobą kolejno zwracane stringi jedna_trzecia_znaku tworząc gotową linijkę do zapisania w pliku.


parametry funkcji:
----------------------------------------------------------------------------------------------------
plik_wejsciowy -- plik wejsciowy z którego pobierane będą kolejne wiersze znaków
plik_wyjsciowy -- plik wyjsciowy do którego zapisane zostaną kolejne wiersze znaków
czy_cudzyslow_jest_zamykajacy_czy_poczatkowy -- zmienna zapamiętująca funkcję ostatniego cudzysłowia (otwierający/zamykający)

wartosc zwracana:
----------------------------------------------------------------------------------------------------
brak

uwagi:
----------
Przed każdą cyfrą pojawia się specjalny znak Braille'a
Cudzysłów otwierający i zamykający mają różne reprezentację w alfabecie Braille'a

autor: Roman Zemeła
2017-11-30
*/
void funkcja_czytajaca_i_zapisujaca_do_pliku(ifstream& plik_wejsciowy, ofstream& plik_wyjsciowy,bool& czy_cudzyslow_jest_zamykajacy_czy_poczatkowy)
{
	string linjka_znakow_z_pliku_wejsciowego;
	getline(plik_wejsciowy, linjka_znakow_z_pliku_wejsciowego);  //pobranie jednej linijki z pliku wejściowego
	int ktory_znak_z_linijki_znakow_z_pliku_wejsciowego = 0; 
	do
	{
		for (int ktory_rzad_znaku_braille = 1; ktory_rzad_znaku_braille <= 3; ktory_rzad_znaku_braille++) //pętla która wypisze 3 stringi, które jeden na drugim stworzą jedną linijkę znaków Braille'a
		{
			string jedna_trzecia_linijki; 
			int i = 0;
			for (i; i < 30; i++)
			{
				if (ktory_znak_z_linijki_znakow_z_pliku_wejsciowego >= linjka_znakow_z_pliku_wejsciowego.size())
				{
					break;
				}
/*czy cyfra */			if (linjka_znakow_z_pliku_wejsciowego[ktory_znak_z_linijki_znakow_z_pliku_wejsciowego] > 47 && linjka_znakow_z_pliku_wejsciowego[ktory_znak_z_linijki_znakow_z_pliku_wejsciowego] < 58)
				{
					if (i == 29) // Cyfra która miała być 30 znakiem zostanie przeniesiona do kolejnej linii
					{
						break;
					}					
					jedna_trzecia_linijki = jedna_trzecia_linijki + znaki_na_braille('$', ktory_rzad_znaku_braille)+ znaki_na_braille(linjka_znakow_z_pliku_wejsciowego[ktory_znak_z_linijki_znakow_z_pliku_wejsciowego], ktory_rzad_znaku_braille);
					ktory_znak_z_linijki_znakow_z_pliku_wejsciowego++;
					continue;
				}
				if (linjka_znakow_z_pliku_wejsciowego[ktory_znak_z_linijki_znakow_z_pliku_wejsciowego] == '"')
				{
					if (ktory_rzad_znaku_braille == 2)
					{
						if (czy_cudzyslow_jest_zamykajacy_czy_poczatkowy == 0) //0 oznacza otwarcie cudzysłowia | 1 oznacza zamknięcie
						{
							czy_cudzyslow_jest_zamykajacy_czy_poczatkowy = 1;
							jedna_trzecia_linijki = jedna_trzecia_linijki + znaki_na_braille('@', ktory_rzad_znaku_braille);
							ktory_znak_z_linijki_znakow_z_pliku_wejsciowego++;
							continue;
						}
						else
						{
							czy_cudzyslow_jest_zamykajacy_czy_poczatkowy = 0;
						}
					}
				}				
				jedna_trzecia_linijki = jedna_trzecia_linijki + znaki_na_braille(linjka_znakow_z_pliku_wejsciowego[ktory_znak_z_linijki_znakow_z_pliku_wejsciowego], ktory_rzad_znaku_braille);
				ktory_znak_z_linijki_znakow_z_pliku_wejsciowego++;
			}
			plik_wyjsciowy << jedna_trzecia_linijki << endl;
			ktory_znak_z_linijki_znakow_z_pliku_wejsciowego = ktory_znak_z_linijki_znakow_z_pliku_wejsciowego - i;
		}
		plik_wyjsciowy << endl;
		ktory_znak_z_linijki_znakow_z_pliku_wejsciowego = ktory_znak_z_linijki_znakow_z_pliku_wejsciowego + 30;
	} while (ktory_znak_z_linijki_znakow_z_pliku_wejsciowego <= linjka_znakow_z_pliku_wejsciowego.size());
	return;
}
/*
Funkcja wypisująca okno pomocy na konsoli

parametry funkcji:
----------------------------------------------------------------------------------------------------
brak

wartosc zwracana:
----------------------------------------------------------------------------------------------------
brak

uwagi:
----------
brak

autor: Roman Zemeła
2017-11-30
*/
void help()
{
	cout << "Przetlumaczenie pliku  tekstowego na plik zapisany znakami z alfabetu Braille'a" << endl;
	cout << "Prosze o podanie dwoch parametrow"<< endl;
	cout << "-i nazwa pliku wejsciowego" << endl;
	cout << "-o nazwa pliku wyjsciowego" << endl;
	cout << "-h dla wyswietlenia pomocy (to co jest obecnie wyswietlane, to wlasnie ta pomoc" << endl;
	cout << "-i oraz -o nie moga byc tymi samymi plikami" << endl;
	cout << "W pliku wejsciowym dopuszczalnymi znakami sa:" << endl;
	cout << "Wszystkie litery alfabetu polskiego i angielskiego" << endl;
	cout << "cyfry od 0 do 9" << endl;
	cout << "Symbole takie jak ! ( ) , ; : . < > ? / [ ] { } - oraz apostrof i cudzyslow" << endl;
	cout << "W przypadku znalezniena innego symbolu program bedzie dzialal dalej, znak Braille'a w tamtym miejscu zostanie zastapiony ??????" << endl;
	return;
}
/*
Funkcja odczytująca parametry wywołania programu. Są one podane w postaci przełączników
-i input        nazwa pliku wejściowego
-o output       nazwa pliku wyjściowego
-h              wyświetlenie pomocy

Przełączniki mogą być podane w dowolnej kolejności.

parametry funkcji:
----------------------------------------------------------------------------------------------------
ile       --liczba parametrów przy uruchomieniu programu
argumenty --tablica wskażników na łańcuchy użytych przy uruchomieniu programu
Input     --parametr wyjściowy, do którego zostanie zapisana odczytana nazwa pliku
wejściowego
Output    --parametr wyjściowy, do którego zostanie zapisana odczytana nazwa pliku
wyjściowego

wartosc zwracana:
----------------------------------------------------------------------------------------------------
brak

uwagi:
----------
W przypadku niepodania nazwy pliku wyjściowego plik zostanie zapisany w domyślnej nazwie pliku
W przypadku niepodania nazwy pliku wejściowego program wypisze "Plik wejsciowy nie otwarl sie poprawnie"
Bez pliku wejściowego nie ma na czym przeprowadzić opeacji translacji, a domyślny plik wejściowy byłby bezcelowy
W przypadku wystąpienia parametru -h, program przeprowadzi normalne przejście aby umożliwić użycie np. (-h -i -o), (-h -i) lub (-h -o)
W przypadku nie podaniu parametrów program wyświetli ekran pomocy i komunikat o nieotwarciu się pliku wejściowego, gdyż żaden plik wejściowy nie został podany

autor: Roman Zemeła
2017-11-30
*/

void funkcja_sprawdzajaca_argumenty(int ile, char ** argumenty, string & Input, string & Output)
{
	const string Przelacznik_Input("-i");
	const string Przelacznik_Output("-o");
	const string Przelacznik_Help("-h");
	bool czy_podano_parametr = 0;
	Output = "plik_wyjscia.pas";//Domyślny plik wyjścia jeżeli user nic nie poda
	for (int i = 1; i < ile; i++)
	{
		string arg(argumenty[i]);
		if (arg == Przelacznik_Help)
		{
			help();
			czy_podano_parametr = 1;
		}
		if (arg == Przelacznik_Input)
		{
			if (i != ile)
			{					
				Input = argumenty[i + 1];
				czy_podano_parametr = 1;
			}
		}
		if (arg == Przelacznik_Output)
		{
			if (i != ile)
			{
				Output = argumenty[i + 1];
				czy_podano_parametr = 1;
			}
		}	
	}
	if (czy_podano_parametr == 0)
	{
		help();
	}
	if (Input == Output) // If zapewniający nie nadpisanie pliku wejściowego
	{
		if (Output == "nie_wolno_mi_nadpisac_pliku_wejsciowego!.pas")
		{
			Output = "plik_wyjscia.pas";
			cout << "Plik wyjsciowy zostal nazwany plik_wyjscia.pas, poniewaz plik wejsciowy nie moze sie nazywac tak samo jak wyjsciowy";
		}
		else
		{
			Output = "nie_wolno_mi_nadpisac_pliku_wejsciowego!.pas";
			cout << "Plik wyjsciowy zostal nazwany nie_wolno_mi_nadpisac_pliku_wejsciowego!.pas, poniewaz plik wejsciowy nie moze sie nazywac tak samo jak wyjsciowy";
		}
	}
	return;
}
/*
Główna funkcja otwierająca i zamykająca plik wejściowy i wyjściowy. Dokonuje ona głównego sprawdzenia, czy plik wejściowy jeszcze się nie zakończył.
Wywołuje ona funkcje wymagane do poprawnego przejścia programu.

parametry funkcji:
----------------------------------------------------------------------------------------------------
ile       --liczba parametrów przy uruchomieniu programu
argumenty --tablica wskażników na łańcuchy użytych przy uruchomieniu programu

wartosc zwracana:
----------------------------------------------------------------------------------------------------
0 -- dla poprawnego przejścia programu

uwagi:
----------
Autor uważa wypisanie komunikatu błędu za poprawne przejście programu.

autor: Roman Zemeła
2017-11-30
*/
int main(int ile, char ** argumenty)
{	
	string nazwa_pliku_wejsciowego;
	string nazwa_pliku_wyjsciowego;
	funkcja_sprawdzajaca_argumenty(ile, argumenty, nazwa_pliku_wejsciowego, nazwa_pliku_wyjsciowego);
	ifstream plik_wejsciowy;
	plik_wejsciowy.open(nazwa_pliku_wejsciowego);
	if (!plik_wejsciowy.is_open())
	{
		cout << "Plik wejsciowy nie otwarl sie poprawnie, upewnij sie ze podales poprawna nazwe";
		return 0;
	}
	ofstream plik_wyjsciowy;
	plik_wyjsciowy.open(nazwa_pliku_wyjsciowego);
	if (!plik_wyjsciowy.is_open())
	{
		cout << "Plik wyjsciowy nie otwarl sie poprawnie";
		return 0; 		
	}
	bool czy_cudzyslow_jest_zamykajacy_czy_poczatkowy = 0; //zmienna pomocnicza dla sprawdzenia czy cudzyslow jest zamykajacy czy początkowy
		while (!plik_wejsciowy.eof())
	{
		funkcja_czytajaca_i_zapisujaca_do_pliku(plik_wejsciowy,plik_wyjsciowy, czy_cudzyslow_jest_zamykajacy_czy_poczatkowy);
	}
	plik_wyjsciowy.close();
	plik_wejsciowy.close();
    return 0;
}



