#include "Graph.h"

#define MAXAMOUNT 10 


//fonction de trie
bool sorting_func(pplData i, pplData j) { 
	if (i.vote == 0 && j.vote == 0)
		return (0);
	if (i.vote == j.vote)
		return (i.name < j.name);
	return (i.vote > j.vote); 
}

//fonction de creation
Graph::Graph(std::shared_ptr<sf::RenderWindow> window)
{
	win = window;

	if (!setDefaultFont(font)) {
		std::cerr << "Error while loading font !" << std::endl;
	}
	if (!setupSR()) {
		std::cerr << "Error while setuping Steps or Rounds!" << std::endl;
	}
	setupBackGround();
	if (!setupLogo()) {
		std::cerr << "Error while setuping lOGO!" << std::endl;
	}
}

Graph::Graph()
{
	

}

Graph::~Graph()
{
}

void Graph::getfiles(std::string Steps, std::string Round)
{
	//need to work on it

	{
		char* next = NULL;
		auto token = strtok_s((char*)Steps.c_str(), "\n", &next);
		while (token != NULL) {
			_Ssteps.push_back(token);
			token = strtok_s(NULL, "\n", &next);
		}
	}
	{
		char* next = NULL;
		auto token = strtok_s((char*)Round.c_str(), "\n", &next);
		while (token != NULL) {
			_Srounds.push_back(token);
			token = strtok_s(NULL, "\n", &next);
		}
	}
}

//chargement de la police d'ecriture
bool Graph::setDefaultFont(std::string fontName)
{
	if (!Defaultfont.loadFromFile(fontName))
	{
		return false;
	}
	return true;
}

// mise en place du STEP et ROUND  /  resources
bool Graph::setupSR()
{
	W_Steps.setFont(Defaultfont);
	W_Steps.setString(" ");
	W_Steps.setCharacterSize(75);
	W_Steps.setFillColor(sf::Color::White);
	W_Steps.setPosition(800, 90);

	W_Rounds.setFont(Defaultfont);
	W_Rounds.setString(" ");
	W_Rounds.setCharacterSize(75);
	W_Rounds.setFillColor(sf::Color::White);
	W_Rounds.setPosition(Height - Height / 8.f, 75);

	W_NbEnveloppe.setFont(Defaultfont);
	W_NbEnveloppe.setString("Nombre d'enveloppes dans l'urne 00");
	W_NbEnveloppe.setCharacterSize(45);
	W_NbEnveloppe.setFillColor(sf::Color(135, 16, 67));
	sf::FloatRect WenveloppeSize = W_NbEnveloppe.getGlobalBounds();
	W_NbEnveloppe.setOrigin(WenveloppeSize.width, 0);
	W_NbEnveloppe.setPosition(Height - 75, Width - (Width / 4.f) + 70);

	W_nbNull.setFont(Defaultfont);
	W_nbNull.setString("Nombre de bulletins blancs 00");
	W_nbNull.setCharacterSize(45);
	W_nbNull.setFillColor(sf::Color(135, 16, 67));
	sf::FloatRect WnullSize = W_nbNull.getGlobalBounds();
	W_nbNull.setOrigin(WnullSize.width, 0);
	W_nbNull.setPosition(Height - 20, Width - (Width / 4.f) + 120);

	W_nbBlank.setFont(Defaultfont);
	W_nbBlank.setString("Nombre de bulletins nuls 00");
	W_nbBlank.setCharacterSize(45);
	W_nbBlank.setFillColor(sf::Color(135, 16, 67));
	sf::FloatRect WBlankSize = W_nbBlank.getGlobalBounds();
	W_nbBlank.setOrigin(WBlankSize.width, 0);
	W_nbBlank.setPosition(Height - 125, Width - (Width / 4.f) + 170);


	W_suffrage.setFont(Defaultfont);
	W_suffrage.setString("Suffrages exprimés 00");
	W_suffrage.setCharacterSize(45);
	W_suffrage.setFillColor(sf::Color(135, 16, 67));
	sf::FloatRect WsuffrageSize = W_suffrage.getGlobalBounds();
	W_suffrage.setOrigin(WsuffrageSize.width, 0);
	W_suffrage.setPosition(Height - Height / 2 - 300, Width - (Width / 4.f) + 70);

	W_Majo.setFont(Defaultfont);
	W_Majo.setString("Majorité absolue 00");
	W_Majo.setCharacterSize(45);
	W_Majo.setFillColor(sf::Color(135, 16, 67));
	sf::FloatRect WMajoSize = W_Majo.getGlobalBounds();
	W_Majo.setOrigin(WMajoSize.width, 0);
	W_Majo.setPosition(Height - Height / 2 - 300, Width - (Width / 4.f) + 120);

	return true;
}

// mise en place du carrer moche de font
void Graph::setupBackGround()
{
	R_Round = sf::RectangleShape(sf::Vector2f(Height - Height / 4.f, 200.f));
	R_Round.setPosition(sf::Vector2f(0.f, 0.f));
	R_Round.setFillColor(sf::Color(165, 18, 76));

	R_Step = sf::RectangleShape(sf::Vector2f(Height / 4.f, 200.f));
	R_Step.setPosition(sf::Vector2f(Height - Height / 4.f, 0.f));
	R_Step.setFillColor(sf::Color(135, 16, 67));
	
}


// mise a jour des elements
void Graph::update()
{
	//draw rect
	win->draw(R_Round);
	win->draw(R_Step);
	
	//draw word
	sf::FloatRect WstepSize = W_Steps.getGlobalBounds();
	W_Steps.setOrigin(WstepSize.width / 2.f, WstepSize.height / 2.f);
	if (data[0] - 1 > _Ssteps.size())
		W_Steps.setString(_Ssteps.at(_Ssteps.size()- 1));
	else
		W_Steps.setString(data[0] - 1 >= 0 ? _Ssteps.at(data[0] - 1) : " ");
	win->draw(W_Steps);

	sf::FloatRect WRoundSize = W_Rounds.getGlobalBounds();
	W_Rounds.setOrigin(WRoundSize.width / 2.f, WRoundSize.height / 2.f);
	if (data[1] - 1 > _Srounds.size())
		W_Steps.setString(_Srounds.at(_Srounds.size() - 1));
	else
		W_Rounds.setString(data[1] - 1 >= 0 ? _Srounds.at(data[1] - 1) : " ");
	win->draw(W_Rounds);

	W_NbEnveloppe.setString("Nombre d'enveloppes dans l'urne " + std::to_string(data[2]));
	win->draw(W_NbEnveloppe);
	W_nbNull.setString("Nombre de bulletins nuls " + std::to_string(data[4]));
	win->draw(W_nbNull);
	W_nbBlank.setString("Nombre de bulletins blancs " + std::to_string(data[3]));
	win->draw(W_nbBlank);
	W_suffrage.setString("Suffrages exprimés " + std::to_string(data[5]));
	win->draw(W_suffrage);

	if (data[1] != 3)
		W_Majo.setString("Majorité absolue " + std::to_string(data[6]));
	else
		W_Majo.setString(" ");
	win->draw(W_Majo);

	// sprite
	if (logoLoaded)
		win->draw(logo);

	bool DisplayMode = false;
	//metre Display mode a true pour afficher en ligne
	for (auto i : pplList)
	{
		i.update(false);
		i.inLineMode == true ? DisplayMode = true : i.inLineMode = false;
	}

	for (auto i : pplList)
	{
		i.inLineMode = DisplayMode;
		i.update(true);
	}
}

// chargement du logo
bool Graph::setupLogo()
{
	if (!texture.loadFromFile("TEX/logo.png"))
	{
		std::cerr << "Error while loading Logo texture please place a picture like this : TEX/logo.png" << std::endl;
		return false;
	}
	texture.setSmooth(true);
	if (logoLoaded)
	{
		logo.setTexture(texture);
		logo.setPosition(30, 30);
		logo.setScale(0.20, 0.20);
	}
	return true;
}


// ajout de personne 
void Graph::addppl()
{
	//change to update ppl
	pplList.clear();
	int i = 1;

	std::sort(datappl.begin(), datappl.end(), sorting_func);
	while (datappl.size() > MAXAMOUNT)
		datappl.pop_back();

	for (auto tmp : datappl)
	{
		pplList.push_back(PeopleContain(tmp.vote, datappl.size(), tmp.percent, i, tmp.name, win));
		i++;
	}
}

// mise a jour de la fenetre
void Graph::UpdateWin(std::shared_ptr<sf::RenderWindow> _win)
{
	win = _win;
	for (auto tmp : pplList)
		tmp.updateWin(_win);
}
