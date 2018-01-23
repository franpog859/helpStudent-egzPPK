// Projekt1.cpp : Defines the entry point for the console application.
//
/* 
Temat: LU
Autor: Paulina Urbas
Data oddania: 2017-12-01

Uwagi:
Przygotowano kilka plikow testujacych:
- MacierzA1.txt					- plik wypelniona losowymi liczbami z zakresu od -100 do 100 
- MacierzA2.txt					- plik wypelniona losowymi liczbami z zakresu od -1000 do 1000
- MacierzA3.txt					- plik o niepoprawnym formacie, posiada znaki M 
- MacierzA4.txt					- plik wypelniony liczbami losowymi posiadajacy zbyt wiele elementow 
- MacierzA5.txt					- plik wypelniony liczbami losowymi posiadajacy zbyt malo elementow 
- MacierzA6.txt					- plik pusty

*/
#include "stdafx.h"
#include <iostream>
#include <fstream> 
#include <stdio.h>
#include <string>
#include <string.h>
#include <iomanip>
#include <cmath>

using namespace std;
const int ROZMIAR = 10; //okresla rozmiar macierzy, ktore sa uzyte w programie
const int W = 10; // szerokosc pola

/*
Funkcja odczytujaca zawartosc pliku.

parametry funkcji:

- nazwa								- nazwa pliku wejsciowego
- MacierzA[ROZMIAR][ROZMIAR]		- parametr wyjsciowy, do ktorego zostanie zapisana odczytana z pliku macierze wejsiowa
  
wartosc zwracana:
 - brak

uwagi:
 - brak

 */

void OdczytzPliku(const string & nazwa, double MacierzA[ROZMIAR][ROZMIAR])
{
	ifstream plik;
	plik.open("..\\..\\dat\\"+nazwa); //otwieranie pliku 
	try
	{
		if (plik.good() == false) //sprawdzenie czy plik moze byc otwarty 
		{
			throw ("nie znalezionio pliku<"+nazwa + ">!");
			plik.close();
		}
		else
		{
			for (int i = 0; i < ROZMIAR; i++)
			{
				for (int j = 0; j < ROZMIAR; j++)
				{
					if (plik >> MacierzA[i][j]) //sprawdzenie czy format pliku jest odpowiednie 
					{

					}
					else
					{
						plik.close(); //zamykanie pliku
						throw ("Blad wczytania pliku <" + nazwa + ">!");
					}
				}
			}
			plik.close(); //zamykanie pliku 
		}
	}
		catch (...)
		{
			throw("Plik<" + nazwa + "> nie zostal znaleziony!");
		}
		
	}
/*

Funkcja zwraca macierz jednostkowa (tj. macierz kwadratowa z wartosciami 1 na glownej przekatnej) o rozmiarze podanym w stalej ROZMIAR

parametry funkcji:

- MacierzL[ROZMIAR][ROZMIAR]		- parametr wyjsciowy, do ktorego zostanie zapisana stworzona macierz jednostkowa

wartosc zwracana:
- 0									- stworzono macierz jednostkowa
uwagi:

- brak

*/

int TworzenieJednostkowejMacierzy(double MacierzL[ROZMIAR][ROZMIAR])
{
	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = 0; j < ROZMIAR; j++)
		{
			if (i == j)
			{
				MacierzL[i][i] = 1; //jedynki na glownej  przekatnej 
			}
			
			else
			{
				MacierzL[i][j] = 0; //wypelnienie pozostalych elementow macierzy wartosciami 0 
			}
		}
	}
	return 0;
}

/*

Funkcja zwraca macierz zerowa (tj. macierz kwadratowa z wartosciami 0) o rozmiarze podanym w stalej ROZMIAR

parametry funkcji:
- MacierzU[ROZMIAR][ROZMIAR]		- parametr wyjsciowy, do ktorego zostanie zapisana stworzona macierz zerowa

wartosc zwracana:
- 0									- stworzono macierz zerowa

uwagi:
- brak

*/

int TworzenieMacierzyZerowej(double MacierzU[ROZMIAR][ROZMIAR])
{
	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = 0; j < ROZMIAR; j++)
		{
			MacierzU[i][j] = 0; //wypelnienie elementow macierzy 0 
		}
	}
	return 0;
}

/*
Funkcja wykonuje dekompozycje LU macierzy podanej w argumencie A

parametry funkcji:

- A[ROZMIAR][ROZMIAR]		-parametr wejsciowy, macierz podana w tym argumencie ulega dekompozycji
- L[ROZMIAR][ROZMIAR]		-parametr wyjsciowy, do ktorego, po dekompozycji, zostanie zapisana Macierz L
- U[ROZMIAR][ROZMIAR]		-parametr wyjsciowy, do ktorego, po dekompozycji, zostanie zapisana Macierz U

wartosc zwracana:
- 0							-macierz zostala rozlozona na macierz L i macierz U

uwagi:
- brak
*/

int Demkopresja(double A[ROZMIAR][ROZMIAR], double L[ROZMIAR][ROZMIAR], double U[ROZMIAR][ROZMIAR])
{
	const double EPSILON = 1e-15;
	int pomocdozapamietania = 0;
	double suma = 0; //zmienna pomocnicza do zapamietania suma L[i][k]*U[k][j]
	double suma2 = 0;  //zmienna pomocnicza do zapamietania suma L[j][k]*U[k][i]
	double tabdozapamietania[ROZMIAR]; //pomocniczy wektor sluzacy do zapamietania kazdej ze zmian w przypadku, gdy u[i][i] = 0
	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = 0; j < ROZMIAR; j++)
		{
			L[i][i] = 1;
			suma = 0; //zerowanie sumy 
			if (i <= j) //sprawdzenie warunku zgodnie ze wzorem 
			{
				for (int k = 0; k <= i; k++)
				{
					suma += L[i][k] * U[k][j];
				}
				U[i][j] = A[i][j] - suma; //wyliczenie elementu U[i][j] zgodnie ze wzorem 
			}
			suma2 = 0; //zerowanie sumy2 
			if (i < j) //sprawdzenie warunku zgodnie ze wzorem 
			{
				for (int k = 0; k <= i; k++)
				{
					suma2 += L[j][k] * U[k][i];
				}
				if (fabs(U[i][i]) > EPSILON)
				{
					L[j][i] = (A[j][i] - suma2) / U[i][i];  //wyliczenie elementu L[j][i] zgodnie ze wzorem 
				}
				else if (U[i][i] == 0)
				{
					for (int k = 0; k < ROZMIAR; k++)
					{
						U[i][i] = tabdozapamietania[i]; //zapamietywanie w wektorze pomocniczym zmian

						tabdozapamietania[i] = U[i - 1][j - 1];

						U[i - 1][j - 1] = tabdozapamietania[i];

					}
				}
			}
		}
	}
	return 0;
}

/*

Funkcja odczytujaca zawartosc pliku.
parametry funkcji:

- nazwa										-nazwa pliku wyjsciowego
- MacierzDoZapisania[ROZMIAR][ROZMIAR] 		-parametr wyjsciowy, do ktorego zostanie zapisana odczytana Macierz

wartosc zwracana:
- brak

uwagi:
- brak

*/

void ZapisdoPlikuMacierzy(string & nazwa, double MacierzDoZapisania[ROZMIAR][ROZMIAR])  // const string & nazwa
{
	fstream plik;
	plik.open(nazwa, ios::out); //otworzenie pliku 
	if (plik.is_open() == false)
	{
		return;
	}
	plik << endl;
	plik << "to jest macierz L" << endl;
	for (int i = 0; i < ROZMIAR; i++)
	{
		plik << endl;
		for (int j = 0; j < ROZMIAR; j++)
		{
			plik << setw(W) << MacierzDoZapisania[i][j]; //zapis do pliku, gdy dane do wpisania do pliku sa podane w prawidlowy sposob 
		}
	}
	plik.close();
}

/*

Funkcja wykonuje mnozenie macierzy L i U podanych jako argumenty w celu sprawdzenia poprawnosci wykonanej dekompozycji LU
parametry funkcji :
- MacierzL[ROZMIAR][ROZMIAR]			- parametr wejsciowy, macierz podana w tym argumencie zostaje mnozona
- MacierzU[ROZMIAR][ROZMIAR]			- parametr wejsciowy, macierz podana w tym argumencie zostaje mnozona
- MacierzA[ROZMIAR][ROZMIAR]			- parametr wyjsciowy, do ktorego, po mnozeniu, zostanie zapisana Macierz A

wartosc zwracana :
- 0										- macierz zostala rozlozona na macierz L i macierz U

uwagi :
- brak

*/

int Mnozenie(double MacierzL[ROZMIAR][ROZMIAR], double MacierzU[ROZMIAR][ROZMIAR], double MacierzA[ROZMIAR][ROZMIAR])

{

	for (int i = 0; i < ROZMIAR; i++)

	{

		for (int k = 0; k < ROZMIAR; k++)

		{

			MacierzA[i][k] = 0; //zerowanie elementu

			for (int j = 0; j <ROZMIAR; j++)

			{

				MacierzA[i][k] += MacierzL[i][j] * MacierzU[j][k]; //wyliczenie wartosci macierzy zgodnie ze wzorem 

			}

		}

	}

	return 0;

}

/*

Funkcja porownujaca Macierz A z macierza powstalaja przez wymnozenie macierz L i U

parametry funkcji:

- MacierzA[ROZMIAR][ROZMIAR]			- nazwa pliku wejsciowego
- MacierzA1[ROZMIAR][ROZMIAR]			- parametr wyjsciowy, do ktorego zostanie zapisana odczytana z pliku macierze wejsciowa

wartosc zwracana:

- true									- gdy macierze sa takie same
- false									- gdy macierze nie sa takie same

uwagi:
- brak

*/

bool PorownianiaMacierzy(double MacierzA[ROZMIAR][ROZMIAR], double MacierzA1[ROZMIAR][ROZMIAR])
{
	const double EPSILON = 1e-10;
	for (int i = 0; i <ROZMIAR; i++)
	{
		for (int j = 0; j <ROZMIAR; j++)
		{
			if (fabs(MacierzA[i][j] - MacierzA1[i][j]) < EPSILON)
			{
				return true; //gdy macierze sa rowne zwracana jest wartosc true
			}
			else
			{
				return false; //gdy macierze nie sa rowne zwracana jest wartosc false 
			}
		}
	}
}

/*

Funkcja wyswietlajaca macierz podana jako argument funckji

parametry funkcji:

- Macierz[ROZMIAR][ROZMIAR]			- macierz do wyswietlenia

wartosc zwracana:
- brak

uwagi:
- brak

*/

void Wyswietl(double Macierz[ROZMIAR][ROZMIAR]) //funkcja wyswietla macierz
{
	for (int i = 0; i < ROZMIAR; i++) 
	{
		cout << endl;
		for (int j = 0; j < ROZMIAR; j++)
		{
			cout << setw(W) << Macierz[i][j] << " ";
		}

	}

}

/*

Funkcja odczytujca parametry wywolania programu. Sa one podane w postaci przelacznikow:

- i							- nazwa pliku wejsciowego
- l							- nazwa pliku wyjsciowego dla macierzy L
- u							- nazwa pliku wyjsciowego dla macierzy U

parametry funkcji :
- argc						- liczba parametrow przy uruchomieniu programu
- argv						- tablica wskaznikow na lancuchy uzytyc przy uruchomieniu programu
- nazwaplikuwejsciowego		- parametr wyjsciowy, do ktorego zostanie zapisana odczytana nazwa pliku wejsciowego
- nazwazikuwyjsciowegoL		-parametr wyjsciowy, do ktorego zostanie zapisana odczytana nazwa pliku wyjsciowego
- nazwaplikuwejsciowegoU	- parametr wyjsciowy, do ktorego zostanie zapisana odczytana nazwa pliku wyjsciowego

wartosc zwracana :
- 0 - podano poprawne parametry wywolania programu, zostaly odczytane i zapisane do nazwaplikuwejsciowego
- 1 - nie udalo sie odczytac wartosci parametrow wywolania progarmu, wartosci zmiennych nazwaplikuwejciowego oraz pliku wyjsciowego

uwagi :
-brak

*/

int SprawdzWywolanie(int argc, char *argv[], string & nazwaplikuwejsciowego, string & nazwaplikuwyjsciowegoL, string & nazwaplikuwyjsciowegoU)
{
	int ok = 0;
	if (argc <= 7) // sprawdzenie czy przy wywolaniu z listy polecen zostala podana dobra liczba argumnetow 
	{
		for (int i = 1; i < argc; i++)
		{
			if (string(argv[i]) == string("-h"))
			{
				return 1;
			}
			if (string(argv[i]) == string("-i"))
			{
				nazwaplikuwejsciowego = string(argv[i + 1]);
				ok++;
			}
			if (string(argv[i]) == string("-l"))
			{
				nazwaplikuwyjsciowegoL = string(argv[i + 1]);
				ok++;
			}
			if (string(argv[i]) == string("-u"))
			{
				nazwaplikuwyjsciowegoU = string(argv[i + 1]);
				ok++;
			}
		}
		if (ok == 3)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 2;
	}

}

int main(int argc, char *argv[])
{
	try
	{
		string nazwaplikuwejsciowego;
		string nazwaplikuwyjsciowegoL;
		string nazwaplikuwyjsciowegoU;
		int blad = SprawdzWywolanie(argc, argv, nazwaplikuwejsciowego, nazwaplikuwyjsciowegoL, nazwaplikuwyjsciowegoU);
		switch (blad)
		{
		case 0:
			double MacierzU[ROZMIAR][ROZMIAR];
			double MacierzL[ROZMIAR][ROZMIAR];
			double MacierzA[ROZMIAR][ROZMIAR];
			double MacierzA1[ROZMIAR][ROZMIAR];
			cout << "Macierz A" << endl;
			try
			{
				OdczytzPliku(nazwaplikuwejsciowego, MacierzA);
			}
			catch (std::string & wyjatek)
			{
				cerr << wyjatek << endl;
				throw;
			}
			catch (std::exception & wyjatek)
			{
				cerr << "Plik<" << nazwaplikuwejsciowego << "> nie zostal znaleziony!" << endl;
				throw;
			}
			catch (...)
			{
				cerr << "Plik<" << nazwaplikuwejsciowego << "> nie zostal znaleziony!" << endl;
				throw;
			}
			Wyswietl(MacierzA);
			TworzenieJednostkowejMacierzy(MacierzL);//wypelnienie MacierzyL wartosciami takimi jak w macierzy jednostkowej, poniewaz L jest macierza jednostkowa
			TworzenieMacierzyZerowej(MacierzU);
			cout << endl;
			cout << endl;
			cout << endl;
			Demkopresja(MacierzA, MacierzL, MacierzU);
			cout << "Macierz U po dekompresji" << endl;
			Wyswietl(MacierzU);
			cout << endl;
			cout << endl;
			cout << "Macierz L po dekompresji" << endl;
			Wyswietl(MacierzL);
			try
			{
				ZapisdoPlikuMacierzy(nazwaplikuwyjsciowegoL, MacierzL);
				ZapisdoPlikuMacierzy(nazwaplikuwyjsciowegoU, MacierzU);
			}
			catch (string & wyjatek)
			{
				cerr << "Zle podane dane do zapisu" << endl;
				throw;
			}
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "Sprawdzenie dzialania dekompresji macierzy" << endl;
			Mnozenie(MacierzL, MacierzU, MacierzA1);
			cout << endl;
			cout << endl;
			cout << endl;
			Wyswietl(MacierzA1);
			cout << endl;
			cout << endl;
			cout << endl;
			PorownianiaMacierzy(MacierzA, MacierzA1);
			if (PorownianiaMacierzy(MacierzA, MacierzA1) == true)
			{
				cout << "Macierze sa takie same, dekompozycja przebiegla w sposob poprawny" << endl;
			}
			else
			{
				cout << "Macierze nie sa takie same, dekompozycja przebiegla w sposob niepoprawny" << endl;
			}
			getchar();
			getchar();
			return 0;
			break;
		case 1:
			cout << "Nieprawidlowe parametry!" << endl;
			cout << "POMOC" << endl;
			cout << "Aby podac nazwe pliku wejsciowego nalezy uzyc komendy -i, a nastepnie podac nazwe pliku wejsciowego" << endl;
			cout << "Aby podac nazwe pliku wyjsciowego dla macierzy L nalezy uzyc komendy -l, a nastepnie podac nazwe pliku wyjsciowego" << endl;
			cout << "Aby podac nazwe pliku wyjsciowego dla macierzy U nalezy uzyc komendy -u, a nastepnie podac nazwe pliku wyjsciowego" << endl;
			getchar(); 
			getchar();
			return 0;
			break;
		case 2:
			cout << "Podano za malo argumentow" << endl;
			cout << "POMOC" << endl;
			cout << "Aby podac nazwe pliku wejsciowego nalezy uzyc komendy -i, a nastepnie podac nazwe pliku wejsciowego" << endl;
			cout << "Aby podac nazwe pliku wyjsciowego dla macierzy L nalezy uzyc komendy -l, a nastepnie podac nazwe pliku wyjsciowego" << endl;
			cout << "Aby podac nazwe pliku wyjsciowego dla macierzy U nalezy uzyc komendy -u, a nastepnie podac nazwe pliku wyjsciowego" << endl;
			getchar(); 
			getchar();
			return 0;
			break;
		}
	}
	catch (...)
	{
		getchar();
		getchar();
	}
}
