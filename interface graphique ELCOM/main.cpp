#include <SFML/Graphics.hpp>
#include <memory>
#include "Graph.h"
#include "Protocole.h"
#include "PeopleContain.h"




int main()
{
	bool fullscreen = false;
	// personalise VideoMode (args)
	sf::Image icon;
	if (!icon.loadFromFile("trophy.png")) {
		return 1;
	}

	std::shared_ptr<sf::RenderWindow> window;
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Height, Width), "ElCom", fullscreen ? sf::Style::None : sf::Style::Default);
	window->setIcon(512, 512, icon.getPixelsPtr());
	fullscreen = !fullscreen;

	sf::Event event;

	auto graph = std::make_shared<Graph>(window);
	auto proto = Protocole(graph);

	while (window->isOpen())
	{
		while (window->pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window->close();
			}
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space))
			{
				window->close();
				window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Height, Width), "ElCom", fullscreen ? sf::Style::None : sf::Style::Default);
				graph->UpdateWin(window);
				fullscreen = !fullscreen;
			}
		}
		window->clear(sf::Color(255, 255, 255, 255));
		proto.update();

		graph->addppl();
		
		// sort and cut max ppl number

		graph->update();

		window->display();
	}

	return 0;
}

