// PPKprojekt1macierz.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

//stala sizeOfMatrix oznacza wielkosc kwadratowych macierzy wejsciowych i macierzy wyjsciowej
const int sizeOfMatrix = 10;

/*
	Funkcja readArguments odczytuje parametry podane podczas wywolania programu i zapisuje je w zmiennych nazw plikow. Sa one podane w postaci przelacznikow:
	-i input	nazwy dwoch plikow wejsciowych
	-o output	nazwa pliku wyjsciowego
	-h help		wyswietlenie pomocy
	Przelaczniki moga byc podane w dowolnej kolejnosci.

	Parametry funkcji:
	------------------
	argNumber		- liczba parametrow przy wywolaniu programu
	arguments		- tablica wskaznikow na lancuchy uzytych przy uruchomieniu programu
	inputDataName1	- nazwa pierwszego pliku wejsciowego
	inputDataName2	- nazwa drugiego pliku wejsciowego
	outputDataName	- nazwa pliku wyjsciowego

	Zmienne lokalne:
	------------------
	INPUT_LABEL		- ciag znakow odpowiadajacy przelacznikowi dla plikow wejsciowych
	OUTPUT_LABEL	- ciag znakow odpowiadajacy przelacznikowi dla pliku wyjsciowego
	HELP_LABEL		- ciag znakow odpowiadajacy przelacznikowi dla wyswietlenia pomocy
	INPUT_FLAG_1	- oznaczenie miejsca jedynki przy sprawdzaniu poprawnosci wykonania funkcji dla pierwszego pliku wejsciowego
	INPUT_FLAG_2	- oznaczenie miejsca jedynki przy sprawdzaniu poprawnosci wykonania funkcji dla drugiego pliku wejsciowego
	OUTPUT_FLAG		- oznaczenie miejsca jedynki przy sprawdzaniu poprawnosci wykonania funkcji dla pliku wyjsciowego
	CORRECT_RESULT	- wartosc zmiennej result w przypadku poprawdnego przypisania wartosci parametrom 
	result			- zapisywane sa w niej poprawnie wkonane operacje zapisow wartosci do parametrow w postaci zmiany zer na jedynki w postaci binarnej jej wartosci
	error			- ciag znakow zawierajacy komentarz zwiazany z wytapieniem bledu
	end				- ciag znakow zawierajacy komentarz zwiazany z wyswietleniem pomocy

	Brak wartosci zwracanej.
	Zrwacane sa nazwy plikow wejsciowych i pliku wyjsciowego.

	Poprawny zapis argumentu do zmiennej nazwy pliku jest dokumentowany zamiana zera na jedynke na odpowiedniej pozycji w zmiennej result.
	Jezeli podczas wywolania funkcji brakuje ktoregos z argumentow, sygnalizowane jest to przez rzucenie wyjatku typu string z odpowiednim komentarzem.
	Jezeli jednym z argumentow jest przelacznik -h, rzucany jest odpowiedni wyjatek do funkcji main.
	Jezeli nie zostal wywolany przelacznik -h, a ilosc argumentow sie nie zgadza (nie wynosci 6), rzucany jest odpowiedni wyjatek do funkcji main.
	Jezeli pod koniec wykonywania funkcji z jakiegos powodu zmienna result nie rowna sie binarnie 111, rzucany jest odpowieni wyjatek do funkcji main sygnalizujacy blad.
	
	autor: Franciszek Pogodzinski
	2017-11-24
*/
void readArguments(int argNumber, char ** arguments, string & inputDataName1, string & inputDataName2, string & outputDataName) 
{
	const string INPUT_LABEL = "-i";
	const string OUTPUT_LABEL = "-o";
	const string HELP_LABEL = "-h";
	const int INPUT_FLAG_1 = 1;
	const int INPUT_FLAG_2 = INPUT_FLAG_1 << 1;
	const int OUTPUT_FLAG = INPUT_FLAG_1 << 2;

	const int CORRECT_RESULT = INPUT_FLAG_1 | INPUT_FLAG_2 | OUTPUT_FLAG;
	int result = 0;

	for (int i = 1; i < argNumber - 1; i++) 
	{
		if (arguments[i] == OUTPUT_LABEL) 
		{
			outputDataName = arguments[i + 1];
			result |= OUTPUT_FLAG;
		}
		if (arguments[i] == INPUT_LABEL) 
		{
			inputDataName1 = arguments[i + 1];
			result |= INPUT_FLAG_1;
			i++;
			if (i < argNumber - 1) 
			{
				inputDataName2 = arguments[i + 1];
				result |= INPUT_FLAG_2;
			}
			else 
			{
				string error = "Brakuje drugiego pliku zrodlowego.";
				throw error;
			}
		}
		if (arguments[i] == HELP_LABEL) 
		{
			string end = "Pomoc dla uzytkownika:";
			throw end;
		}
	}

	if (arguments[argNumber - 1] == HELP_LABEL) 
	{
		string end = "Pomoc dla uzytkownika:";
		throw end;
	}

	if (argNumber != 6)
	{
		string error = "Zla liczba argumentow.";
		throw error;
	}
	else
	{
		if (result == CORRECT_RESULT)
		{
			return;
		}
		else
		{
			string error = "Wystapil blad podczas czytania argumentow.";
			throw error;
		}
	}
}

/*
Funkcja helpUser wyswietla w konsoli opis programu i przykladowe jego wywolanie. Przyjmuje parametr typu string.

Parametry funkcji:
------------------
argument		- pierwszy argument wywolania programu, czyli nazwa programu

Brak wartosci zwracanej.

autor: Franciszek Pogodzinski
2017-11-24
*/
void helpUser(const string & argument) 
{
	cout << "Program mnozacy macierze kwadratowe o rozmiarze 10 x 10." << endl;
	cout << "Macierze podaje sie w dwoch plikach wejsciowych." << endl;
	cout << "Wynik mnozenia zapisywany jest do pliku wyjsciowego." << endl;
	cout << "Nazwy plikow podawane sa w lini polecen po przelacznikach:" << endl;
	cout << "-i		pliki wejsciowe" << endl;
	cout << "-o		plik wyjsciowy" << endl;
	cout << "Przkladowe wywolanie programu:" << endl;
	cout << argument << " -o wyjscie -i pierwsza druga" << endl;
}

/*
Funkcja fillMatrixFromFile wypelnia macierz danymi zawartymi w pliku wejsciowym. Przyjmuje parametry w postaci macierzy odwuwymiarowej oraz nazwy pliku ejsciowego.

Parametry funkcji:
------------------
Matrix			- tablica dwuwymiarowa, do ktorej zostana wpisane dane zamieszczone w pliku wejsciowym
dataName		- nazwa pliku wejsciowego

Zmienne lokalne:
------------------
inputData		- obiekt, z ktorym zwiazany jest plik wejsciowy
line			- ciag znakow, do ktorego wpisywana jest linia danych z pliku wejsciowego
row				- licznik wierszy w pliku wejsciowym
col				- licznik kolumn w linii danych pliku wejsciowego
data			- zmienna pomocnicza wypelniana pojedyncza skladowa macierzy z pliku wejsciowego
sstream			- strumien, do ktorego wpisywana jest linia znakow z ciagu znakow w zmiennej line
error			- ciag znakow zawierajacy komentarz zwiazany z wytapieniem bledu

Brak wartosci zwracanej.
Zrwacana jest macierz w tablicy Matrix.

Jezeli licznik wierszy uzyskal juz pozadana wartosc, a do zmiennej line ponownie zostal wpisany wiersz z pliku wejsciowego, rzucany jest wyjatek typu string z odpowiednim komentarzem.
Jezeli liczba kolumn w wierszu jest nieodpowiednia, rzucany jest wyjatek z odpowiednim komentarzem.
Jezeli licznik wierszy nie uzyskal pozadanej wartosci, rzucany jest wyjatek z odpowiednim komentarzem.
Jezeli nie udalo sie otwrzyc pliku, rzucany jest wyjatek z odpowiednim komentarzem.
Jezeli w bloku try wystapil nieprzewidziany blad, rzucany jest wyjatek z odpowiednim komentarzem.

autor: Franciszek Pogodzinski
2017-11-24
*/
void fillMatrixFromFile(double Matrix[][sizeOfMatrix], const string & dataName) 
{
	ifstream inputData(dataName);
	try 
	{ 
		if (inputData)
		{
			string line;
			int row = 0;
			int col = 0;
			double data;
			while (getline(inputData, line))
			{
				if (row == sizeOfMatrix) 
				{
					string error = "Problem z danymi w pliku " + dataName + " - Za duzo wierszy w macierzy.";
					throw error;
				}

				stringstream sstream;
				sstream << line;
				while (sstream >> data)
				{
					Matrix[row][col] = data;
					col++;
				}
				if (col != sizeOfMatrix)
				{
					string error = "Problem z danymi w pliku " + dataName + " - Zla liczba wierszy lub zly typ.";
					throw error;
				}

				row++;
				col = 0;
			}
			if (row != sizeOfMatrix)
			{
				string error = "Problem z danymi w pliku " + dataName + " - Za malo wierszy w macierzy.";
				throw error;
			}
		}
		else
		{
			string error = "Nie udalo sie otworzyc pliku " + dataName;
			throw error;
		}
		inputData.close();
	}
	catch (exception & e) 
	{
		string error = "Wystapil nieznany blad zwiazany z plikiem " + dataName;
		throw error;
	}
}

/*
Funkcja fillFilewithMatrix zapisuje wynikowa macierz w pliku z dokladnoscia do szesnastu miejsc po przecinku. Przyjmuje parametry w postaci wynikowej macierzy i nazwy pliku wyjsciowego.

Parametry funkcji:
------------------
multipliedMatrix	- wynikowa macierz dwuwymiarowa, ktora zostanie wpisana do pliku
dataName			- nazwa pliku wyjsciowego

Zmienne lokalne:
------------------
outputData		- obiekt, z ktorym zwiazany jest plik wyjsciowy
i, j			- liczniki w petlach for odpowiadajace za wiersze i kolumny w macierzy
error			- ciag znakow zawierajacy komentarz zwiazany z wytapieniem bledu

Brak wartosci zwracanej.

Jezeli nie udalo sie otworzyc pliku, rzucany jest wyjatek z odpowiednim komentarzem.
Jesli wystapil nieprzewidziany blad, rzucany jest wyjatek z odpowiednim komentarzem.

autor: Franciszek Pogodzinski
2017-11-24
*/
void fillFileWithMatrix(double multipliedMatrix[][sizeOfMatrix], const string & dataName) 
{
	ofstream outputData(dataName);
	try
	{
		if (outputData)
		{
			outputData.precision(16);
			for (int i = 0; i < sizeOfMatrix; i++) {
				for (int j = 0; j < sizeOfMatrix; j++) {
					outputData << setw(25) << fixed << multipliedMatrix[i][j] << " ";
				}
				outputData << endl;
			}
		}
		else
		{
			string error = "Wystapil problem podczas zapisu macierzy do pliku " + dataName;
			throw error;
		}
		outputData.close();
	}
	catch (exception & e)
	{
		string error = "Wystapil problem podczas zapisu macierzy do pliku " + dataName;
		throw error;
	}
}

/*
Funkcja multiplyMatrixes mnozy dwie macierze uzyskane z plikow wejsciowych i zapisuje wynik w macierzy wynikowej. Przyjmuje paramentry w postaci trzech dwuwymiarowych macierzy - dwoch wejsciowych i jednej wyjsciowej.

Parametry funkcji:
------------------
firstMatrix			- pierwsza macierz uzyskana z pliku wejsciowego
secondMatrix		- druga macierz uzyskana z pliku wejsciowego
multipliedMatrix	- macierz z wnikiem mnozenia 

Zmienne lokalne:
------------------
sum				- zmienna pomocnicza wykorzystywana podczas operacji mnozenia macierzy
i, j, k			- liczniki w petlach for odpowiadajace za numery kolumn i wierszy w mnozonych macierzach

Brak wartosci zwracanej.
Zwracana macierz z wynikiem mnozenia.

autor: Franciszek Pogodzinski
2017-11-24
*/
void multiplyMatrixes(double firstMatrix[][sizeOfMatrix], double secondMatrix[][sizeOfMatrix], double multipliedMatrix[][sizeOfMatrix]) 
{
	double sum = 0;
	for (int i = 0; i < sizeOfMatrix; i++) 
	{
		for (int j = 0; j < sizeOfMatrix; j++) 
		{

			for (int k = 0; k < sizeOfMatrix; k++) 
			{
				sum += firstMatrix[i][k] * secondMatrix[k][j];
			}

			multipliedMatrix[i][j] = sum;
			sum = 0;
		}
	}
}

/*
Funkcja main odczytuje parametry podane podczas wywolywania programu, odczytuje macierze podane w dwoch plikach wejsciowych i zapisuje w pliku wyjsciowym wynik ich mnozenia. Sygnalizuje blad, jezeli taki wystapi.

Parametry funkcji:
------------------
argNumber		- liczba parametrow przy wywolaniu programu
arguments		- tablica wskaznikow na lancuchy uzytych przy uruchomieniu programu

Zmienne lokalne:
------------------
firstMatrix			- pierwsza macierz uzyskana z pliku wejsciowego
secondMatrix		- druga macierz uzyskana z pliku wejsciowego
multipliedMatrix	- macierz z wnikiem mnozenia
inputDataName1		- nazwa pierwszego pliku wejsciowego
inputDataName2		- nazwa drugiego pliku wejsciowego
outputDataName		- nazwa pliku wyjsciowego
e					- ciag znakow zawierajacy komentarz zwiazany z wytapieniem bledu

Brak wartosci zwracanej.
Zrwacane sa nazwy plikow wejsciowych i pliku wyjsciowego.

Jezeli wszystkie operacje sie powioda sygnalisowane jest do wypisanym komentarzem w konsoli.
Jezeli ktorakolwiek z funkcji rzuci wyjatek z komentarzem o bledzie lub prosba o pomoc, zostanie to wyswietlone w konsoli wraz z zawartoscia funkcji helpUser.  
Program sam zakonczy dzialanie.

autor: Franciszek Pogodzinski
2017-11-24
*/
int main(int argNumber, char ** arguments)
{
	double firstMatrix[sizeOfMatrix][sizeOfMatrix] = { 0 };
	double secondMatrix[sizeOfMatrix][sizeOfMatrix] = { 0 };

	string inputDataName1, inputDataName2, outputDataName;

	try
	{
		readArguments(argNumber, arguments, inputDataName1, inputDataName2, outputDataName);
		fillMatrixFromFile(firstMatrix, inputDataName1);
		fillMatrixFromFile(secondMatrix, inputDataName2);

		double multipliedMatrix[sizeOfMatrix][sizeOfMatrix] = { 0 };
		multiplyMatrixes(firstMatrix, secondMatrix, multipliedMatrix);

		fillFileWithMatrix(multipliedMatrix, outputDataName);
		cout << "Wynik zapisano pomyslnie.";
		return 0;
	}
	catch (string & e)
	{
		cerr << e << endl;
		helpUser(arguments[0]);
	}
	return 0;
}

