// sfml_game1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Squares");
	
	sf::Font font;
	font.loadFromFile("18536.ttf");

	sf::Text text("F2 - New Game/ Esc - exit/ Change direction - key arrows", font, 20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(5.f, 5.f);

	Game game;
	game.setPosition(50.f, 50.f);

	sf::Event event;
	int move_couter = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::F2)
				{
					game.Init();
					move_couter = 180;
				}
				if (event.key.code == sf::Keyboard::Up) game.ChangeDirection(Direction::up);
				if (event.key.code == sf::Keyboard::Left) game.ChangeDirection(Direction::left);
				if (event.key.code == sf::Keyboard::Right) game.ChangeDirection(Direction::right);
				if (event.key.code == sf::Keyboard::Down) game.ChangeDirection(Direction::down);
				
			}
		}
		if (move_couter --> 0) game.ChangeDirection((Direction)(rand() %4 ));

		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}

	return 0;
}
