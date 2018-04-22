#pragma once

#include "Mrowka.h"

#include <SFGUI\Widgets.hpp>
#include <SFML\Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <memory>
#include <vector>

namespace langton{

	enum pole { CZARNE, BIALE };


	class Macierz
	{
	public:
		Macierz(int k, int w);

		pole&		poz(const mrowka::pozycja & wspolrzedne);

		const int	_kol;
		const int	_wier;

	private:
		std::vector<pole>	_v;

	};


	class Langton
	{
	public:
		Langton(
			float	dl_pola = 10, 
			int		okres = 100,
			float	poz_x = 0.5f,
			float	poz_y = 0.5f
		);
			//dl_pola - wielkosc boku ka¿dego pola w pikselach
		~Langton();

		void uruchom();

		const unsigned int	_WYSOKOSC;
		const unsigned int	_SZEROKOSC;
		const float			_BOK;

		bool				_stop;

	private:
		void	petla();
		void	rysuj();
		void	wykonaj_ruch();

		std::unique_ptr<sf::RenderWindow>	m_render;

		sfg::SFGUI				m_SFGUI;
		sfg::Desktop			m_pulpit;

		Macierz					m_plansza;
		mrowka::Mrowka			m_mrowka;
		sf::Time				m_okres;
		sf::Time				m_sleep;
		sf::RectangleShape		m_kwadrat;

	};

}