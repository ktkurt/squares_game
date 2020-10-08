#pragma once
#include <SFML/Graphics.hpp>

const int SIZE = 4;
const int ARRAY_SIZE = SIZE * SIZE;
const int FIELD_SIZE = 480;
const int CELL_SIZE = 120;

enum class Direction
{
	left = 0,
	right = 1,
	up = 3,
	down = 4
};

class Game : public sf::Drawable, public sf::Transformable
{
private:
	int elements[ARRAY_SIZE];
	int free_index;
	sf::Font font;
	bool solved;
public:
	Game();
	void Init();
	void ChangeDirection(Direction direction);
	//int randoms(int a, int b);
	bool Check();
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

