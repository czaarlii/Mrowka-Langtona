#pragma once

#include <SFML\Graphics.hpp>


namespace mrowka{

	using pozycja = std::pair<int, int>;

	enum kierunek	{ PRZOD, PRAWY, TYL, LEWY };
	enum obrot		{ LEWO, PRAWO };

	class Mrowka
	{
	public:
		Mrowka(const pozycja &poz_poczatkowa, const kierunek & kier_poczatkowy = PRZOD);

		static void		Init(int x_max, int y_max, float BOK);

		pozycja			poz();
		void			wykonaj_obrot(const obrot & ob);
		void			wykonaj_krok_naprzod();

		sf::RectangleShape	_wyglad;

	private:
		static int		mr_max_x;
		static int		mr_max_y;
		static float	_BOK;

		pozycja			mr_poz;
		sf::Color		mr_kolor;
		kierunek		mr_kierunek;

	};

}