#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

class Protocole
{
public :
	std::string content;
	std::vector<std::string> files;
	std::shared_ptr<Graph> graph;

public :
	Protocole();
	Protocole(std::shared_ptr<Graph>);
	~Protocole();

	std::string readFile(const char* filePath);
	void update();
};

