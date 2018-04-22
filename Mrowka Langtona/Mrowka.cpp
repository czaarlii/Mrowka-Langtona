#include "Mrowka.h"

int		mrowka::Mrowka::mr_max_x;
int		mrowka::Mrowka::mr_max_y;
float	mrowka::Mrowka::_BOK;


void mrowka::Mrowka::Init(int x_max, int y_max, float BOK)
{
	mr_max_x = x_max - 1;
	mr_max_y = y_max - 1;
	_BOK = BOK;
}


mrowka::Mrowka::Mrowka(const pozycja &poz_poczatkowa, const kierunek & kier_poczatkowy)
	: mr_poz		(poz_poczatkowa)
	, mr_kierunek	(kier_poczatkowy)
{
	_wyglad.setSize(sf::Vector2f(_BOK, _BOK));
	_wyglad.setFillColor(sf::Color(250, 0, 0));
	_wyglad.setPosition(_BOK * ((float)mr_poz.first + 0.5f), _BOK * ((float)mr_poz.second + 0.5f));
}


mrowka::pozycja mrowka::Mrowka::poz()
{
	return mr_poz;
}


void mrowka::Mrowka::wykonaj_obrot(const obrot & ob)
{
	switch (ob)
	{
	case LEWO:
		switch (mr_kierunek)
		{
			case PRZOD:	mr_kierunek = LEWY; break;
			case LEWY:	mr_kierunek = TYL; break;
			case TYL:	mr_kierunek = PRAWY; break;
			case PRAWY:	mr_kierunek = PRZOD; break;
		}
		break;

	case PRAWO:
		switch (mr_kierunek)
		{
			case PRZOD:	mr_kierunek = PRAWY; break;
			case LEWY:	mr_kierunek = PRZOD; break;
			case TYL:	mr_kierunek = LEWY; break;
			case PRAWY:	mr_kierunek = TYL; break;
		}
		break;
	}
}


void mrowka::Mrowka::wykonaj_krok_naprzod()
{
	switch (mr_kierunek)
	{
	case PRZOD: 
		if (mr_poz.second == 0)
			mr_poz.second = mr_max_y;
		else mr_poz.second--;
		break;

	case TYL:	
		if (mr_poz.second >= mr_max_y)
			mr_poz.second = 0;
		else mr_poz.second++;
		break;

	case LEWY:	
		if (mr_poz.first == 0)
			mr_poz.first = mr_max_x;
		else mr_poz.first--;
		break;

	case PRAWY: 
		if (mr_poz.first >= mr_max_x)
			mr_poz.first = 0;
		else mr_poz.first++;
		break;
	}
}
