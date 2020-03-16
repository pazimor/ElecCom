#include "Protocole.h"

// creation du protocole
Protocole::Protocole()
{
}

// creation du protocole
Protocole::Protocole(std::shared_ptr<Graph> _graph)
{
	graph = _graph;
}

// destruction du protocole
Protocole::~Protocole()
{
}

// lecture
void Protocole::readFile(const char* filePath) {
	
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return ;
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content = line;
	}

	fileStream.close();
}

// mise a jour des informations
void Protocole::update()
{
	readFile("c:/temp/IPC.ipc");
	
	char* token = NULL;
	char* next = NULL;
	int i = 0;
	
	int nextdata = 0;
	token = strtok_s((char*)content.c_str(), ";", &next);

	graph->datappl.clear();
	while (token != NULL) {
		if (i < 3)
		{
			//path
		}
		if (i >= 3 && i < 5)
		{
			//step Round
			graph->data[i - 3] = std::stoi(token);
		}
		else if (i == 5)
		{
			// compute end O_o`
			nextdata = (3 * std::stoi(token)) + 5;
		}
		else if (i >= 5 && i < 11)
		{
			graph->data[i - 4] = std::stoi(token);
		}
		else if (i >= 11)
		{
			// for ppl
			if (token != "")
			{
				pplData tmp;
				tmp.name = token;
				token = strtok_s(NULL, ";", &next);
				tmp.percent = token;
				token = strtok_s(NULL, ";", &next);
				tmp.vote = std::stoi(token);
				graph->datappl.push_back(tmp);
				i++; i++;
			}
		}
		i++;
		token = strtok_s(NULL, ";", &next);

		// update graphics (set values)
	}
}

