#pragma once

#include <SFML/Graphics.hpp>

#include <Vector>
#include <iostream>
#include <memory>
#include "PeopleContain.h"

#define Height 1920
#define Width 1080

#define font "FONT/Quicksand-Bold.ttf"
//#define font "FONT/Dosis-Bold.otf"

struct pplData {
	std::string name;
	std::string percent;
	int vote;

};

class Graph
{
	std::vector<std::string> _Ssteps;
	std::vector<std::string> _Srounds;

	std::shared_ptr<sf::RenderWindow> win;

	sf::Font Defaultfont;
	
	/* Texts */
	sf::Text W_Steps;
	sf::Text W_Rounds;
	sf::Text W_NbEnveloppe;
	sf::Text W_nbNull;
	sf::Text W_nbBlank;
	sf::Text W_suffrage;
	sf::Text W_Majo;
	/* rects */
	sf::RectangleShape R_Step;
	sf::RectangleShape R_Round;

	/* Pics */
	sf::Sprite logo;
	sf::Texture texture;

	
	sf::Texture urneTop;
	sf::Texture urneBottom;
	sf::Texture enveloppe;
	/* values from protocole*/

	bool logoLoaded;
public: 
	std::vector<PeopleContain> pplList;
	int data[10];
	std::vector<pplData> datappl;

public :
	Graph(std::shared_ptr<sf::RenderWindow>);
	Graph();
	~Graph();

	void getfiles(std::string, std::string);
	bool setDefaultFont(std::string);
	bool setupSR(); // setup steps | rounds
	void setupBackGround();
	void update();
	bool setupLogo();
	void addppl(); // update ppl
	void UpdateWin(std::shared_ptr<sf::RenderWindow> _win);

};

