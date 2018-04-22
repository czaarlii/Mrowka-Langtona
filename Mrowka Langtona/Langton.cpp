#include "Langton.h"


langton::Macierz::Macierz(int k, int w) 
	: _kol	(k)
	, _wier	(w)
	, _v	(k * w, CZARNE)
{}


langton::pole & langton::Macierz::poz(const mrowka::pozycja &wspolrzedne)
{
	return _v[wspolrzedne.second * _kol + wspolrzedne.first];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

langton::Langton::Langton(float	dl_pola, 
						int		okres)	
	: _WYSOKOSC		(600)
	, _SZEROKOSC	(800)
	, _BOK			(dl_pola)
	, m_okres		(sf::milliseconds(okres))
	, m_sleep		(sf::milliseconds(50))
	, m_render		(nullptr)
	, m_plansza		(_SZEROKOSC / (unsigned int)_BOK, 
					_WYSOKOSC / (unsigned int)_BOK)
{
	mrowka::Mrowka::Init(m_plansza._kol, m_plansza._wier, _BOK);

	if (m_okres < m_sleep){
		m_sleep = sf::Time(sf::milliseconds(0));
	}

	m_kwadrat.setSize(sf::Vector2f(_BOK, _BOK));
	m_kwadrat.setFillColor(sf::Color(250, 250, 250));
}


void langton::Langton::uruchom()
{
	if (m_lista_mrowek.empty())
		return;

	m_render = std::make_unique<sf::RenderWindow>(sf::VideoMode(_SZEROKOSC, _WYSOKOSC), "Mrowka Langtona");
	petla();
}


void langton::Langton::dodaj_mrowke(const float & poz_x, const float & poz_y, const mrowka::kierunek & kier)
{
	m_lista_mrowek.push_back(mrowka::Mrowka(oblicz_pozycje_mrowki(poz_x, poz_y), kier));
}


void langton::Langton::losuj_mrowki(const int & ile)
{
	std::mt19937 m_rnd;
	m_rnd.seed(std::clock());
	std::uniform_real_distribution<float> dystr(0, 1);

	mrowka::kierunek k;
	for (int i = 0; i < ile; i++)
	{
		switch ((int)(dystr(m_rnd)*4.f))
		{
		case 0: k = mrowka::PRZOD; break;
		case 1: k = mrowka::PRAWY; break;
		case 2: k = mrowka::TYL; break;
		case 3: k = mrowka::LEWY; break;
		}

		dodaj_mrowke(dystr(m_rnd), dystr(m_rnd), k);
	}
}


void langton::Langton::wykonaj_ruch(mrowka::Mrowka & m_mrowka)
{
	if (m_plansza.poz(m_mrowka.poz()) == CZARNE) {
		m_mrowka.wykonaj_obrot(mrowka::PRAWO);
		m_plansza.poz(m_mrowka.poz()) = BIALE;
	} else {
		m_mrowka.wykonaj_obrot(mrowka::LEWO);
		m_plansza.poz(m_mrowka.poz()) = CZARNE;
	}

	m_mrowka.wykonaj_krok_naprzod();
}


void langton::Langton::rysuj()
{
	for (int y = 0; y < m_plansza._wier;y++) {
		for (int x = 0; x < m_plansza._kol; x++) 
		{
			if (m_plansza.poz({ x, y }) == BIALE) {
				m_kwadrat.setPosition(_BOK * (x + 0.5f), _BOK * (y + 0.5f));
				m_render->draw(m_kwadrat);
			}
		}
	}

	for (auto & m_mrowka : m_lista_mrowek)
	{
		auto pos = m_mrowka.poz();
		m_mrowka._wyglad.setPosition(_BOK * ((float)pos.first + 0.5f), _BOK * ((float)pos.second + 0.5f));
		m_render->draw(m_mrowka._wyglad);
	}
}


void langton::Langton::petla()
{
	sf::Event event;
	sf::Clock clock, zegar;

	rysuj();
	m_render->display();

	while (m_render->isOpen()) //pêtla programu
	{
		while (m_render->pollEvent(event)) //pêtla obs³uguj¹ca zdarzenia 
		{
			m_pulpit.HandleEvent(event);

			if (event.type == sf::Event::Closed) // tu nast¹pi koniec programu
				m_render->close();

		}

		sf::sleep(m_sleep);
		m_pulpit.Update(clock.restart().asSeconds()); // odœwie¿anie programu

		if (zegar.getElapsedTime() >= m_okres)
		{
			for (auto & m_mrowka : m_lista_mrowek)
				wykonaj_ruch(m_mrowka);

			zegar.restart();

			//rysowanie aplikacji
			m_render->clear();
			rysuj();
			m_SFGUI.Display(*m_render);
			m_render->display();
		}
	}
}


mrowka::pozycja	langton::Langton::oblicz_pozycje_mrowki(const float & poz_x, const float & poz_y)
{
	return mrowka::pozycja((int)(_SZEROKOSC / (int)_BOK * poz_x), (int)(_WYSOKOSC / (int)_BOK * poz_y));
}