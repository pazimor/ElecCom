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
	const char* _Ssteps[15] = {"", "�LECTION DU PR�SIDENT",
							"�LECTION DU 1er VICE-PR�SIDENT",
							"�LECTION DU 2e VICE-PR�SIDENT",
							"�LECTION DU 3e VICE-PR�SIDENT",
							"�LECTION DU 4e VICE-PR�SIDENT",
							"�LECTION DU 5e VICE-PR�SIDENT",
							"�LECTION DU 6e VICE-PR�SIDENT",
							"�LECTION DU 7e VICE-PR�SIDENT",
							"�LECTION DU 8e VICE-PR�SIDENT",
							"�LECTION DU 9e VICE-PR�SIDENT",
							"�LECTION DU 10e VICE-PR�SIDENT",
							"�LECTION DU 11e VICE-PR�SIDENT",
							"�LECTION DU 12e VICE-PR�SIDENT",
							"�LECTION DU 13e VICE-PR�SIDENT"};
	 
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

