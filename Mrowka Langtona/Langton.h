#pragma once

#include "Mrowka.h"

#include <SFGUI\Widgets.hpp>
#include <SFML\Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <memory>
#include <vector>
#include <list>
#include <random>
#include <ctime>


namespace langton{

	enum pole { CZARNE, BIALE };


	class Macierz
	{
	public:
		Macierz(int k, int w);

		pole & poz(const mrowka::pozycja & wspolrzedne);

		const int	_kol;
		const int	_wier;

	private:
		std::vector<pole>	_v;

	};


	class Langton
	{
	public:
		/*dl_pola - wielkosc boku ka¿dego pola w pikselach
		okres - czas w ms odœwie¿ania ekranu*/
		Langton(float	dl_pola = 10, 
				int		okres = 100);

		void	uruchom();
		void	dodaj_mrowke(const float & poz_x, const float & poz_y, const mrowka::kierunek & kier);
		void	losuj_mrowki(const int & ile);

		const unsigned int	_WYSOKOSC;
		const unsigned int	_SZEROKOSC;
		const float			_BOK;

	private:
		void				petla();
		void				rysuj();
		void				wykonaj_ruch(mrowka::Mrowka & m_mrowka);
		mrowka::pozycja		oblicz_pozycje_mrowki(const float & poz_x, const float & poz_y);

		std::unique_ptr<sf::RenderWindow>	m_render;
		std::list<mrowka::Mrowka>			m_lista_mrowek;

		sfg::SFGUI				m_SFGUI;
		sfg::Desktop			m_pulpit;
		Macierz					m_plansza;
		sf::Time				m_okres;
		sf::Time				m_sleep;
		sf::RectangleShape		m_kwadrat;

	};

}