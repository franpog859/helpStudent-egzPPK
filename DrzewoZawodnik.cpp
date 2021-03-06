// DrzewoZawodnik.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

struct wynik
{
	string miejsce;
	double czas;
	wynik * next;
};

struct zawodnik
{
	string imie;
	string nazwisko;
	wynik *wyniki;
	zawodnik * lewy;
	zawodnik * prawy;
};

zawodnik * znajdz(zawodnik * pRoot, const string &nazwisko)
{
	if (!pRoot)
	{
		return pRoot;
	}
	else
	{
		auto pHead = pRoot;
		while (true)
		{
			if (pHead->nazwisko == nazwisko)
			{
				return pHead;
			}
			if (pHead->nazwisko < nazwisko)
			{
				if (pHead->prawy)
				{
					pHead = pHead->prawy;
					continue;
				}
				return pHead;
			}
			if (pHead->nazwisko > nazwisko)
			{
				if (pHead->lewy)
				{
					pHead = pHead->lewy;
					continue;
				}
				return pHead;
			}
		}
	}
}

void dodaj(zawodnik *& pRoot, const string & imie, const string & nazwisko, const string & miejsce, double czas)
{
	zawodnik*komu=znajdz(pRoot,nazwisko);
	wynik *temp = new wynik{ miejsce, czas,nullptr };
	if (!komu)
	{
		pRoot = new zawodnik{ imie, nazwisko,temp,nullptr,nullptr };
	}
	else
	{
		if (komu->nazwisko == nazwisko)
		{
			auto pHeadW = komu->wyniki;
			if (!pHeadW)
			{
				komu->wyniki = temp;
			}
			else
			{
				while (pHeadW)
				{
					if (pHeadW->next == nullptr)
					{
						break;
					}
					pHeadW = pHeadW->next;
				}
				pHeadW->next = temp;
			}
		}
		else
		{
			if (komu->nazwisko < nazwisko)
			{
				komu->prawy = new zawodnik{ imie, nazwisko,temp,nullptr,nullptr };
			}
			else
			{
				komu->lewy = new zawodnik{ imie, nazwisko,temp,nullptr,nullptr };
			}
		}
	}
	return;
}

void usunwyniki(zawodnik*&pZawodnik)
{
	auto pHead = pZawodnik->wyniki;
	auto pHeadB = pHead;
	while (pHead)
	{
		pHead = pHead->next;
		delete pHeadB;
		pHeadB = pHead;
	}
	pZawodnik->wyniki = nullptr;
	return;
}

void usunwynikirek(wynik*&pWynik)
{
	if (pWynik)
	{
		usunwynikirek(pWynik->next);
	}
	delete pWynik;
	return;
}

enum strona
{
	lewo,
	prawo,
};

void usun(zawodnik*&pRoot)
{
	auto pHead = pRoot;
	auto pHeadB = pHead;
	int strona;
	while (pHead)
	{
		if (pHead->lewy)
		{
			pHeadB = pHead;
			pHead = pHead->lewy;
			strona = lewo;
			continue;
		}
		if (pHead->prawy)
		{
			pHeadB = pHead;
			pHead = pHead->prawy;
			strona = prawo;
			continue;
		}
		if (pHead->prawy == nullptr&&pHead->lewy == nullptr)
		{
			usunwyniki(pHead);
			cout << pHead->nazwisko;
			delete pHead;
			if (strona == lewo)
			{
				pHeadB->lewy = nullptr;
			}
			if (strona == prawo)
			{
				pHeadB->prawy = nullptr;
			}
			if (pHead == pRoot)
			{
				pRoot = nullptr;
				break;
			}
			pHead = pRoot;
		}
	}

	return;
}

void usunrek(zawodnik*&pRoot)
{
	if (pRoot)
	{
		if (pRoot->lewy)
		{
			usunrek(pRoot->lewy);
			pRoot->lewy = nullptr;
		}
		if (pRoot->prawy)
		{
			usunrek(pRoot->prawy);
			pRoot->prawy = nullptr;
		}
		if (pRoot->lewy == nullptr&&pRoot->prawy == nullptr)
		{
			cout << pRoot->nazwisko;
			usunwynikirek(pRoot->wyniki);
			delete pRoot;
		}
	}
	return;
}

int main()
{
	zawodnik*pRoot = nullptr;
	dodaj(pRoot, "Jan", "Kowalski", "Kce", 10);
	dodaj(pRoot, "Man", "Dowalski", "Kce", 10);
	dodaj(pRoot, "Aan", "Aowalski", "Kce", 10);
	dodaj(pRoot, "Dan", "Yowalski", "Kce", 10);
	dodaj(pRoot, "Jan", "Mowalski", "Kce", 10);
	dodaj(pRoot, "Jan", "Mowalski", "Kce", 10);
	dodaj(pRoot, "Aan", "Gowalski", "Kce", 10);
	dodaj(pRoot, "Zan", "Howalski", "Kce", 10);
	usunrek(pRoot);



    return 0;
}

