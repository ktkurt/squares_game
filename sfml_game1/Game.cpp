#include "Game.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>


Game::Game()
{
	font.loadFromFile("18536.ttf");
	Init();
}

/*int randoms(int a, int b)
{
	srand(time(NULL));
	if (a > 0) return a + rand() % (b - a);
	else return a + rand() % (abs(a) + b);
}*/

void Game::Init()
{
	int n = 16;
	std::vector<int> values = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	
	std::random_shuffle(values.begin(), values.end());

	for (int i = 0; i < ARRAY_SIZE - 1; i++) elements[i] = values[i];
	  



	free_index = ARRAY_SIZE - 1;

	elements[free_index] = 0;

	solved = true;
}

bool Game::Check()
{
	for ( int i = 0; i < ARRAY_SIZE - 1; i ++) 
	{
	if (elements[i] > 0 && elements[i] != i + 1) return false;
	}
}


void Game::ChangeDirection(Direction direction)
{
	int col = free_index % SIZE;
	int row = free_index / SIZE;

	int move_index = -1;
	if (direction == Direction::left && col < (SIZE - 1)) move_index = free_index + 1;
	if (direction == Direction::right && col > 0) move_index = free_index - 1;
	if (direction == Direction::up && row < (SIZE - 1)) move_index = free_index + SIZE;
	if (direction == Direction::down && row > 0) move_index = free_index - SIZE;

	if (free_index >= 0 && move_index >= 0)
	{
		int tmp = elements[free_index];
		elements[free_index] = elements[move_index];
		elements[move_index] = tmp;
		free_index = move_index;
	}

	solved = Check();
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	// Рисуем рамку игрового поля
	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	// Подготавливаем рамку для отрисовки всех плашек
	shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// Подготавливаем текстовую заготовку для отрисовки номеров плашек
	sf::Text text("", font, 52);

	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements[i]));
		if (solved)
		{
			// Решенную головоломку выделяем другим цветом
			shape.setOutlineColor(sf::Color::Cyan);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements[i] == i + 1)
		{
			// Номера плашек на своих местах выделяем цветом
			text.setFillColor(sf::Color::Green);
		}

		// Рисуем все плашки, кроме пустой
		if (elements[i] > 0)
		{
			// Вычисление позиции плашки для отрисовки
			sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			// Позицию текста подбирал вручную
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
			// Отрисовываем рамку плашки
			target.draw(shape, states);
			// Отрисовываем номер плашки
			target.draw(text, states);
		}
	}
}
