#pragma once

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

#define Height 1920
#define Width 1080

#define font "FONT/Quicksand-Bold.ttf"
//#define font "FONT/Dosis-Bold.otf"

class PeopleContain
{
public:
	int nbTotal;
	int selfPlace;

	std::string percent;
	int voiceCount;
	bool inLineMode;

private:
	sf::Text *W_percent;
	sf::Text *W_voiceCount;
	sf::Text *name;
	sf::Text *surname;

	std::string Name;
	sf::Font Defaultfont;
	std::shared_ptr<sf::RenderWindow> win;

	sf::Texture urneTop;
	sf::Texture urneBottom;
	sf::Texture enveloppe;

	sf::Sprite S_uTop;
	sf::Sprite S_uBot;
	sf::Sprite S_uEnv;

	int LenMax;


public :
	PeopleContain(int, int, std::string, int, std::string, std::shared_ptr<sf::RenderWindow>);
	~PeopleContain();

	void update(bool draw);
	void updateData(float, int, int = -1, int = -1, std::string = NULL);
	void updateWin(std::shared_ptr<sf::RenderWindow> _win);

	void setTexUrneEnv(sf::Texture , sf::Texture , sf::Texture );

	void Up_Name(bool draw = false);
	void Up_Surname(bool draw = false);
	void Up_percent(bool draw = false);
	void Up_voiceCount(bool draw = false);
	void Up_Urne();

	void Draw();
};

