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
	const char* _Ssteps[15] = {"", "ÉLECTION DU PRÉSIDENT",
							"ÉLECTION DU 1er VICE-PRÉSIDENT",
							"ÉLECTION DU 2e VICE-PRÉSIDENT",
							"ÉLECTION DU 3e VICE-PRÉSIDENT",
							"ÉLECTION DU 4e VICE-PRÉSIDENT",
							"ÉLECTION DU 5e VICE-PRÉSIDENT",
							"ÉLECTION DU 6e VICE-PRÉSIDENT",
							"ÉLECTION DU 7e VICE-PRÉSIDENT",
							"ÉLECTION DU 8e VICE-PRÉSIDENT",
							"ÉLECTION DU 9e VICE-PRÉSIDENT",
							"ÉLECTION DU 10e VICE-PRÉSIDENT",
							"ÉLECTION DU 11e VICE-PRÉSIDENT",
							"ÉLECTION DU 12e VICE-PRÉSIDENT",
							"ÉLECTION DU 13e VICE-PRÉSIDENT"};
	 
	const char* _Srounds[4] = { "", "1er TOUR", "2e TOUR", "3e TOUR" };

	std::shared_ptr<sf::RenderWindow> win;

	sf::Font Defaultfont;
	
	/* Texts */
	sf::Text W_Steps;
	sf::Text W_Rounds;
	sf::Text W_NbEnveloppe;
	sf::Text W_nbNullblanc;
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
	int data[7];
	std::vector<pplData> datappl;

public :
	Graph(std::shared_ptr<sf::RenderWindow>);
	Graph();
	~Graph();

	bool setDefaultFont(std::string);
	bool setupSR(); // setup steps | rounds
	void setupBackGround();
	void update();
	bool setupLogo();
	void addppl(); // update ppl
	void UpdateWin(std::shared_ptr<sf::RenderWindow> _win);

};

