#pragma once

#include <SFML\Graphics.hpp>
#include <utility>

namespace mrowka{

	using pozycja = std::pair<int, int>;

	enum kierunek	{ PRZOD, PRAWY, TYL, LEWY };
	enum obrot		{ LEWO, PRAWO };

	class Mrowka
	{
	public:
		Mrowka(
			const pozycja		&poz_poczatkowa, 
			int					x_max, 
			int					y_max
		);

		pozycja		poz();
		void		wykonaj_obrot(const obrot & ob);
		bool		wykonaj_krok_naprzod();

		sf::RectangleShape	_wyglad;

	private:
		pozycja			mr_poz;
		sf::Color		mr_kolor;
		kierunek		mr_kierunek;
		static int		mr_max_x;
		static int		mr_max_y;
	};

}