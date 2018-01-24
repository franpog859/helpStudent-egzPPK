// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>

using namespace std;

struct Wynik {			// lista
	string miejsce;
	double czas;
	Wynik* next;
};
struct Zawodnik {		// drzewo
	string imie, nazwisko;
	Wynik * wynik;
	Zawodnik * lewy;
	Zawodnik * prawy;
};
//znajdz zawodnika
//jezeli nie ma to dodaj
//dodaj zawodnikowi czas w porzadku

Zawodnik* znajdzZawodnika(Zawodnik * &pRoot, string nazwisko, string imie)
{
	if (!pRoot)
	{
		pRoot = new Zawodnik{ imie,nazwisko,NULL,NULL,NULL };
		return pRoot;
	}
	else
	{
		if (nazwisko == pRoot->nazwisko)	return pRoot;
		else if (nazwisko < pRoot->nazwisko) 
			return znajdzZawodnika(pRoot->lewy, nazwisko, imie); // idz w lewo
		else
			return znajdzZawodnika(pRoot->prawy, nazwisko, imie); // idz w prawo		
	}
}
Wynik* znajdzRodzica(Wynik *pHead, Wynik *szukany)
{
	auto p = pHead;
	while (p)
	{
		if (p->next == szukany)	return p;
		p = p->next;
	}
}
void dodajWynik(Zawodnik * competitor, string miejsce, double czas)
{
	if (!competitor->wynik)	// jesli lista biegow pusta, dodaj jako glowe listy
		competitor->wynik = new Wynik{ miejsce, czas, NULL };
	else
	{
  // TODO sortowenie wynikow na liscie, zamiast dodawania na poczatek
		competitor->wynik = new Wynik{ miejsce, czas, competitor->wynik };
		
	//znajdzRodzica(competitor->wynik,p)->next = p;
	}
}
void dodaj(Zawodnik * &pRoot, string imie, string nazwisko, string miejsce, double czas)
{
	Zawodnik* competitor = znajdzZawodnika(pRoot, nazwisko, imie);
	dodajWynik(competitor, miejsce, czas);
}
void wypiszBiegi(Wynik * pHead)
{
	auto p = pHead;
	while (p)
	{
		cout << p->miejsce << "\t" << p->czas << endl;
		p = p->next;
	}
}
void wypisz(Zawodnik *& pRoot)
{
	if (pRoot)
	{
		wypisz(pRoot->lewy);
		cout << pRoot->imie << "   " << pRoot->nazwisko << endl;
		wypiszBiegi(pRoot->wynik);
		wypisz(pRoot->prawy);
	}
}

int main()
{
	Zawodnik * Korzen = NULL;	// Korzen drzewa
	dodaj(Korzen, "pawel", "tomaszewski", "tarnowskie gory", 21323);
	dodaj(Korzen, "szymon", "adamczyk", "boston", 13453);
	dodaj(Korzen, "szymon", "adamczyk", "rpa maraton", 23453);
	dodaj(Korzen, "szymon", "adamczyk", "orlen", 23233);
	dodaj(Korzen, "pawel", "tomaszewski", "boston", 13453);
	//znajdzZawodnika(Korzen, "korzewniowski", "szymon");
	wypisz(Korzen);
	return 0;
}

