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
std::string Protocole::readFile(const char* filePath) {
	
	std::ifstream fileStream(filePath, std::ios::in);

	std::string content;

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return content;
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content += line + "\n";
	}

	fileStream.close();
	return content;
}

// mise a jour des informations
void Protocole::update()
{
	content = readFile("c:/temp/IPC.ipc");
	
	char* token = NULL;
	char* next = NULL;
	int i = 0;
	
	int nextdata = 0;
	token = strtok_s((char*)content.c_str(), ";", &next);

	graph->datappl.clear();
	static bool first = true;

	while (token != NULL) {
		if (i < 3 && first)
		{
			auto tmp = readFile(token);
			if (tmp.empty())
				files.push_back("NONE");
			else
				files.push_back(tmp);
		}
		if (i >= 3 && i < 5)
		{
			if (files.at(i - 3).empty())
				graph->data[i - 2] = 1;
			else
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
	files;
	graph->data;
	first = false;
}

