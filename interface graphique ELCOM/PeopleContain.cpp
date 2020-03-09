#include "PeopleContain.h"

//fonction de creation
PeopleContain::PeopleContain(
	int _voiceCount,
	int _nbTotal,
	std::string _percent,
	int _selfPlace,
	std::string _name,
	std::shared_ptr<sf::RenderWindow> _win)
{
	win = _win;
	voiceCount = _voiceCount;
	nbTotal= _nbTotal;
	percent = _percent;
	selfPlace = _selfPlace;
	Name = _name;
	char* token = NULL;
	char* token2 = NULL;
	char* next = NULL;
	char* content = (char*)Name.c_str();

	LenMax = 0;
	token = strtok_s(content, ":", &next);
	name = new sf::Text();
	name->setString(token);
	token = strtok_s(nullptr, ":", &next);
	surname = new sf::Text();
	surname->setString(token);

	inLineMode = false;
	
	if (!urneTop.loadFromFile("TEX/urnetop.png"))
	{
		std::cerr << "Error while loading texture" << std::endl;
		return;
	}
	urneTop.setSmooth(true);

	if (!urneBottom.loadFromFile("TEX/urnebottom.png"))
	{
		std::cerr << "Error while loading texture" << std::endl;
		return;
	}
	urneBottom.setSmooth(true);

	if (!enveloppe.loadFromFile("TEX/email.png"))
	{
		std::cerr << "Error while loading texture" << std::endl;
		return;
	}
	enveloppe.setSmooth(true);
}

//fonction de destruction
PeopleContain::~PeopleContain()
{
}

//mise a jour du nom
void PeopleContain::Up_Name(bool draw)
{
	
	name->setFont(Defaultfont);
	name->setFillColor(sf::Color(0, 0, 0));
	name->setCharacterSize(50);

	surname->setFont(Defaultfont);
	surname->setFillColor(sf::Color(0, 0, 0));
	surname->setCharacterSize(50);

	sf::FloatRect WSurNameSize = surname->getGlobalBounds();
	LenMax = (WSurNameSize.width > LenMax) ? WSurNameSize.width : LenMax;

	sf::FloatRect WNameSize = name->getGlobalBounds();
	LenMax = (WNameSize.width > LenMax) ? WNameSize.width : LenMax;

	float FocusLen = Height / (nbTotal + 1);
	if (LenMax >= FocusLen)
	{
		inLineMode = true;
	}

	if (inLineMode == false)
	{
		name->setOrigin(WNameSize.width / 2.f, WNameSize.height / 2.f);
		name->setPosition(Height / (nbTotal + 1) * selfPlace, 370);
		if (draw)
			win->draw(*name);
	}
	else
	{
		name->setOrigin(WNameSize.width / 2.f, 0);
		name->setPosition(WNameSize.width / 2.f + 20, ((Width - 400) / (nbTotal + 1) * selfPlace) + 200);
		if (draw)
			win->draw(*name);
		return;
	}
	
}

// mise a jour prenom
void PeopleContain::Up_Surname(bool draw)
{
	surname->setFont(Defaultfont);
	surname->setFillColor(sf::Color(0, 0, 0));
	surname->setCharacterSize(50);

	sf::FloatRect WSurNameSize = surname->getGlobalBounds();
	LenMax = (WSurNameSize.width > LenMax) ? WSurNameSize.width : LenMax;

	if (inLineMode == false)
	{	
		surname->setOrigin(WSurNameSize.width / 2.f, WSurNameSize.height / 2.f);
		surname->setPosition(Height / (nbTotal + 1) * selfPlace, 420);
		if (draw)
			win->draw(*surname);
	}
	else
	{
		sf::FloatRect WNameSize = name->getGlobalBounds();
		surname->setOrigin(WSurNameSize.width / 2.f, 0);
		surname->setPosition(WNameSize.width + WSurNameSize.width / 2.f + 70, ((Width - 400) / (nbTotal + 1) * selfPlace) + 200);
		if (draw)
			win->draw(*surname);
	}
}

// mise a jour pourcentage
void PeopleContain::Up_percent(bool draw)
{
	W_percent = new sf::Text();
	W_percent->setFont(Defaultfont);
	W_percent->setFillColor(sf::Color(135, 16, 67));
	W_percent->setCharacterSize(60);
	
	
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << percent;
	W_percent->setString(stream.str());
	sf::FloatRect WpercentSize = W_percent->getGlobalBounds();

	if (inLineMode == false)
	{
		W_percent->setOrigin(WpercentSize.width / 2.f, WpercentSize.height / 2.f);
		W_percent->setPosition(Height / (nbTotal + 1) * selfPlace, 520);
		if (draw)
			win->draw(*W_percent);
	}
	else
	{
		sf::FloatRect WNameSize = name->getGlobalBounds();
		sf::FloatRect WSurNameSize = surname->getGlobalBounds();

		W_percent->setOrigin(WpercentSize.width / 2.f, 0);
		W_percent->setPosition(Height - 350, ((Width - 400) / (nbTotal + 1) * selfPlace) + 200);
		if (draw)
			win->draw(*W_percent);
	}
}

// mise a jour nbr de voie
void PeopleContain::Up_voiceCount(bool draw)
{
	W_voiceCount = new sf::Text();
	W_voiceCount->setFillColor(sf::Color(0, 0, 0));
	W_voiceCount->setString(std::to_string(voiceCount));
	W_voiceCount->setFont(Defaultfont);
	W_voiceCount->setCharacterSize(50);
	sf::FloatRect WVoiceSize = W_voiceCount->getGlobalBounds();
	
	if (inLineMode == false)
	{
		W_voiceCount->setOrigin(WVoiceSize.width / 2.f, WVoiceSize.height / 2.f);
		W_voiceCount->setPosition(Height / (nbTotal + 1) * selfPlace, 690);

		if (draw)
		{
			Up_Urne();
			Draw();
			win->draw(*W_voiceCount);
		}
	}
	else
	{
		sf::FloatRect WNameSize = name->getGlobalBounds();
		sf::FloatRect WSurNameSize = surname->getGlobalBounds();
		sf::FloatRect WpercentSize = W_percent->getGlobalBounds();

		W_voiceCount->setOrigin(WVoiceSize.width / 2.f, 0);
		W_voiceCount->setPosition(Height - 100, ((Width - 400) / (nbTotal + 1) * selfPlace) + 200);

		if (draw)
		{
			Up_Urne();
			win->draw(*W_voiceCount);
		}
	}

}

//mise a jour de l'image d'urne
void PeopleContain::Up_Urne()
{
	if (inLineMode == false)
	{
		sf::FloatRect S_uTopSize = S_uTop.getGlobalBounds();
		S_uTop.setOrigin(S_uTopSize.width / 2.f, S_uTopSize.height / 2.f);
		S_uTop.setScale(0.2, 0.2);
		S_uTop.setPosition(Height / (nbTotal + 1) * selfPlace - 55, 640);
		S_uTop.setTexture(urneTop);

		sf::FloatRect S_uBotSize = S_uBot.getGlobalBounds();
		S_uBot.setOrigin(S_uBotSize.width / 2.f, S_uBotSize.height / 2.f);
		S_uBot.setScale(0.2, 0.2);
		S_uBot.setPosition(Height / (nbTotal + 1) * selfPlace - 55, 640);
		S_uBot.setTexture(urneBottom);

		sf::FloatRect S_uEnvSize = S_uEnv.getGlobalBounds();
		S_uEnv.setOrigin(S_uEnvSize.width / 2.f, S_uEnvSize.height / 2.f);
		S_uEnv.setScale(0.08, 0.08);
		S_uEnv.setPosition(Height / (nbTotal + 1) * selfPlace - 20, 580);
		S_uEnv.setTexture(enveloppe);
	}
	else
	{
		sf::FloatRect S_uTopSize = S_uTop.getGlobalBounds();
		S_uTop.setOrigin(S_uTopSize.width / 2.f, 0);
		S_uTop.setScale(0.1, 0.1);
		S_uTop.setPosition(Height - 200, ((Width - 400) / (nbTotal + 1) * selfPlace) + 200);
		S_uTop.setTexture(urneTop);

		sf::FloatRect S_uBotSize = S_uBot.getGlobalBounds();
		S_uBot.setOrigin(S_uBotSize.width / 2.f, 0);
		S_uBot.setScale(0.1, 0.1);
		S_uBot.setPosition(Height - 200, ((Width - 400) / (nbTotal + 1) * selfPlace) + 200);
		S_uBot.setTexture(urneBottom);

		sf::FloatRect S_uEnvSize = S_uEnv.getGlobalBounds();
		S_uEnv.setOrigin(S_uEnvSize.width / 2.f, 0);
		S_uEnv.setScale(0.08, 0.08);
		S_uEnv.setPosition(Height - 250, ((Width - 400) / (nbTotal + 1) * selfPlace) + 200);
		S_uEnv.setTexture(enveloppe);
	}
	win->draw(S_uTop);
	//win->draw(S_uEnv);
	win->draw(S_uBot);
}

// dessin et en plus il y a des maths
void PeopleContain::Draw()
{
	if (inLineMode == false)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(Height / (nbTotal + 1) * selfPlace - 100, 470)),
			sf::Vertex(sf::Vector2f(Height / (nbTotal + 1) * selfPlace + 100, 470))
		};

		line[0].color = sf::Color(0, 0, 0);
		line[1].color = sf::Color(0, 0, 0);
		win->draw(line, 2, sf::Lines);
	}
}

//mise a jour global
void PeopleContain::update(bool draw)
{

	
	sf::Color textColor = sf::Color(0, 0, 0);

	if (!Defaultfont.loadFromFile(font))
	{
		return;
	}
	
	Up_Name(draw);
	Up_Surname(draw);
	Up_percent(draw);
	Up_voiceCount(draw);
}

//mise a jour des contenues
void PeopleContain::updateData(float _percent,
	int _voiceCount,
	int _nbTotal,
	int _selfPlace,
	std::string _name)
{
	percent = _percent;
	voiceCount = _voiceCount;
	if (_nbTotal != -1)
		nbTotal = _nbTotal;
	if (_selfPlace != -1)
		selfPlace = _selfPlace;
}

//mise a jour de la fenetre (fullscreen / windowed)
void PeopleContain::updateWin(std::shared_ptr<sf::RenderWindow> _win)
{
	win = _win;
}

// ajout des textures
void PeopleContain::setTexUrneEnv(sf::Texture _top, sf::Texture _bot, sf::Texture _env)
{
	urneTop = _top;
	urneBottom = _bot;
	enveloppe = _env;
}
