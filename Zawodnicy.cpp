#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
struct Wynik
{
	string miejsce;
	double czas;
	Wynik * pNastepny;
};
struct Zawodnik
{
	string imie;
	string nazwisko;
	Wynik * wyniki;
	Zawodnik *lewy;
	Zawodnik * prawy;
};
Zawodnik * Dodaj(Zawodnik * & pRoot, string imie, string nazwisko)
{
	if (!pRoot)
	{
		pRoot = new Zawodnik{ imie, nazwisko, nullptr, nullptr, nullptr };
		return pRoot;
	}
	else
	{
		if (pRoot->nazwisko > nazwisko)
		{
			Dodaj(pRoot->lewy, imie, nazwisko);
		}
		else
		{
			Dodaj(pRoot->prawy, imie, nazwisko);
		}
	}
}
Zawodnik * Znajdz(Zawodnik *& pRoot, string imie, string nazwisko)
{
	if (pRoot)
	{
		if (pRoot->nazwisko == nazwisko)
		{
			return pRoot;
		}
		else
		{
			if (pRoot->nazwisko > nazwisko)
			{
				Znajdz(pRoot->lewy, imie, nazwisko);
			}
			else
			{
				Znajdz(pRoot->prawy, imie, nazwisko);
			}
		}

	}
	else
	{
		return Dodaj(pRoot, imie, nazwisko);
	}
}
Wynik * DodajWynik(Zawodnik * & pHead, double czas, string miejsce)
{
	Wynik * pomoc = pHead->wyniki;
	if (pomoc == nullptr)
	{
		pomoc = new Wynik{ miejsce, czas, nullptr };
		return pomoc;
	}
	else if (czas <= pomoc->czas)
	{
		pomoc = new Wynik{ miejsce, czas, pomoc };
		return pomoc;
	}
	else
	{
		while (pomoc)
		{
			if (pomoc->pNastepny && czas > pomoc->pNastepny->czas)
			{
				pomoc = pomoc->pNastepny;
			}
			else if (pomoc->pNastepny == nullptr)					// przypadek z dodawaniem na koncu listy
			{
				pomoc->pNastepny = new Wynik{ miejsce, czas, nullptr };
			}
			else
			{
				pomoc->pNastepny = new Wynik{ miejsce, czas, pomoc->pNastepny };	// przypadek z dodawaniem w srodku listy
				
			}
		}
		return pHead->wyniki;
	}
}
void DodajZawodnikowiWynik(Zawodnik * & pRoot, string imie, string nazwisko, double czas, string miejsce)
{
	Zawodnik * G = Znajdz(pRoot, imie, nazwisko);
	G->wyniki = DodajWynik(G, czas, miejsce);
}
void UsunWyniki(Wynik * & pHead)
{
	if (pHead)
	{
		auto p = pHead;
		pHead = pHead->pNastepny;
		delete p;
	}
}
void UsunDrzewo(Zawodnik * & pRoot)
{
	if (pRoot)
	{
		UsunDrzewo(pRoot->lewy);
		UsunWyniki(pRoot->wyniki);
		UsunDrzewo(pRoot->prawy);
		delete pRoot;
		pRoot = 0;
	}
}
int main()
{
	Zawodnik * G = 0;
	DodajZawodnikowiWynik(G, "Bartek", "Goral", 24.55, "1");
	DodajZawodnikowiWynik(G, "Kacper", "Nowakowski", 24.55, "2");
	DodajZawodnikowiWynik(G, "Juliusz", "Nowak", 44.55, "2");
	DodajZawodnikowiWynik(G, "Jurek", "Nowak", 23.55, "2");
	DodajZawodnikowiWynik(G, "Michal", "Kukulski", 57.23, "2");
	DodajZawodnikowiWynik(G, "Jurek", "Nowak", 34.55, "2");
	DodajZawodnikowiWynik(G, "Jurek", "Nowak", 24.55, "2");
	DodajZawodnikowiWynik(G, "Bartek", "Goral", 24.55, "1");
	DodajZawodnikowiWynik(G, "Bartek", "Goral", 14.55, "22");
	DodajZawodnikowiWynik(G, "Bartek", "Goral", 24.55, "3");
	DodajZawodnikowiWynik(G, "Bartek", "Goral", 14.55, "4");
	DodajZawodnikowiWynik(G, "Michal", "Kukul", 77.23, "2");
	DodajZawodnikowiWynik(G, "Michal", "Kukul", 27.23, "2");
	DodajZawodnikowiWynik(G, "Michal", "Kukul", 37.23, "2");
	UsunDrzewo(G);
	UsunDrzewo(G);
	return 0;
}