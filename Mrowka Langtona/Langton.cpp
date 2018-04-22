#include "Langton.h"


langton::Macierz::Macierz(int k, int w) :
	_kol	(k),
	_wier	(w),
	_v		(k * w, CZARNE)
{}


langton::pole & langton::Macierz::poz(const mrowka::pozycja &wspolrzedne)
{
	return _v[wspolrzedne.second * _kol + wspolrzedne.first];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

langton::Langton::Langton(
	float			dl_pola, 
	int				okres,
	float			poz_x,
	float			poz_y
) :
	_WYSOKOSC		(600),
	_SZEROKOSC		(800),
	_BOK			(dl_pola),
	_stop			(false),
	m_okres			(sf::milliseconds(okres)),
	m_sleep			(sf::milliseconds(50)),
	m_render		(nullptr),
	m_plansza(
		_SZEROKOSC / (unsigned int)_BOK, 
		_WYSOKOSC / (unsigned int)_BOK
	),
	m_mrowka(
		mrowka::pozycja(
			(int)(_SZEROKOSC / (int)_BOK * poz_x),
			(int)(_WYSOKOSC / (int)_BOK * poz_y)
		),
		m_plansza._kol, 
		m_plansza._wier
	)

{
	if (m_okres < m_sleep){
		//m_sleep = m_okres;
		m_sleep = sf::Time(sf::milliseconds(0));
	}

	m_kwadrat.setSize(sf::Vector2f(_BOK, _BOK));
	m_kwadrat.setFillColor(sf::Color(250, 250, 250));
	
	m_mrowka._wyglad.setSize(sf::Vector2f(_BOK, _BOK));
	m_mrowka._wyglad.setFillColor(sf::Color( 250, 0, 0 ));

	auto pos = m_mrowka.poz();
	m_mrowka._wyglad.setPosition(_BOK * ((float)pos.first + 0.5f), _BOK * ((float)pos.second + 0.5f));
}


langton::Langton::~Langton()
{
	/*if (m_render != nullptr)
		delete m_render;*/
}


void langton::Langton::uruchom()
{
	m_render = std::make_unique<sf::RenderWindow>(sf::VideoMode(_SZEROKOSC, _WYSOKOSC), "Mrowka Langtona");
	petla();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void langton::Langton::wykonaj_ruch()
{
	if (m_plansza.poz(m_mrowka.poz()) == CZARNE) {
		m_mrowka.wykonaj_obrot(mrowka::PRAWO);
		m_plansza.poz(m_mrowka.poz()) = BIALE;
	} else {
		m_mrowka.wykonaj_obrot(mrowka::LEWO);
		m_plansza.poz(m_mrowka.poz()) = CZARNE;
	}

	if (!m_mrowka.wykonaj_krok_naprzod())
		_stop = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	auto pos = m_mrowka.poz();
	m_mrowka._wyglad.setPosition(_BOK * ((float)pos.first + 0.5f), _BOK * ((float)pos.second + 0.5f));
	m_render->draw(m_mrowka._wyglad);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

		if (zegar.getElapsedTime() >= m_okres && !_stop)
		{
			wykonaj_ruch();
			zegar.restart();

			//rysowanie aplikacji
			m_render->clear();
			rysuj();
			m_SFGUI.Display(*m_render);
			m_render->display();
		}
	}
}
