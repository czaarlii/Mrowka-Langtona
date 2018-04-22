#include "Mrowka.h"


int	mrowka::Mrowka::mr_max_x;
int	mrowka::Mrowka::mr_max_y;


mrowka::Mrowka::Mrowka(
	const pozycja		&poz_poczatkowa,
	int					x_max, 
	int					y_max
) :
	mr_poz			(poz_poczatkowa),
	mr_kierunek		(PRZOD)

{
	mr_max_x = x_max - 1;
	mr_max_y = y_max - 1;
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


bool mrowka::Mrowka::wykonaj_krok_naprzod()
{
	switch (mr_kierunek)
	{
	case PRZOD: 
		if (mr_poz.second == 0) //return false;
			mr_poz.second = mr_max_y;
		else mr_poz.second--;
		break;

	case TYL:	
		if (mr_poz.second >= mr_max_y) //return false;
			mr_poz.second = 0;
		else mr_poz.second++;
		break;

	case LEWY:	
		if (mr_poz.first == 0) //return false;
			mr_poz.first = mr_max_x;
		else mr_poz.first--;
		break;

	case PRAWY: 
		if (mr_poz.first >= mr_max_x) //return false;
			mr_poz.first = 0;
		else mr_poz.first++;
		break;
	}

	return true;
}
