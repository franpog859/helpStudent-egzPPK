// PODCIĄG.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool Sprawdzpodciag(const string & podslowo, const string & slowo)
{
	for (int i = 0; i < slowo.size() - podslowo.size() +1 ; i++)
	{
		int zgodnaLiterka = 0;
		for (int j = 0; j < podslowo.size(); j++)
		{
			if (podslowo[j] == slowo[i+j])
			{
				zgodnaLiterka++;
			}
			if (zgodnaLiterka == podslowo.size())
			{
				return true;
			}
		}
	}
	return false;
}

void zapiszWynik(ofstream & plikwyjscia, bool wynik)
{
	if (wynik == true)
	{
		plikwyjscia << "true" << endl;
	}
	else
	{
		plikwyjscia << "false" << endl;
	}
}

void Sprawdz(const string & wejscie, const string & wyjscie)
{
	ifstream plikwejscia(wejscie);
	ofstream plikwyjscia;
	plikwyjscia.open(wyjscie, ios_base::app);

	if (plikwejscia.good() == true)
	{
		while (!plikwejscia.eof())
		{
			string podslowo;
			string slowo;
			plikwejscia >> podslowo;
			plikwejscia >> slowo;
			bool wynik = Sprawdzpodciag(podslowo, slowo);
			zapiszWynik(plikwyjscia, wynik);
		}
		plikwejscia.close();
		plikwyjscia.close();

	}

}


int main()
{
	string wejscie = "test.txt";
	string wyjscie = "wynik.txt";
	Sprawdz(wejscie, wyjscie);

    return 0;
}

