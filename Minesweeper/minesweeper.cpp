#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <ctime>

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(320, 320), "Minesweeper", sf::Style::Close);

	int width = 32;
	int grid[12][12];
	int sgrid[12][12];

	sf::Texture texture;
	texture.loadFromFile("Textures/tiles.jpg");

	sf::Sprite tile;
	tile.setTexture(texture);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			sgrid[i][j] = 10;
			if (rand() % 5 == 0)
				grid[i][j] = 9;
			else
				grid[i][j] = 0;
		}
	}

	for (size_t i = 1; i < 11; i++)
	{
		for (size_t j = 1; j < 11; j++)
		{
			int n = 0;
			if (grid[i][j] == 9)			continue;
			if (grid[i + 1][j] == 9)		n++;
			if (grid[i][j + 1] == 9)		n++;
			if (grid[i - 1][j] == 9)		n++;
			if (grid[i][j - 1] == 9)		n++;
			if (grid[i + 1][j + 1] == 9)	n++;
			if (grid[i - 1][j - 1] == 9)	n++;
			if (grid[i - 1][j + 1] == 9)	n++;
			if (grid[i + 1][j - 1] == 9)	n++;
			grid[i][j] = n;
		}
	}

	while (window.isOpen())
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			sgrid[sf::Mouse::getPosition(window).x / width][sf::Mouse::getPosition(window).y / width] = grid[sf::Mouse::getPosition(window).x / width][sf::Mouse::getPosition(window).y / width];

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			sgrid[sf::Mouse::getPosition(window).x / width][sf::Mouse::getPosition(window).y / width] = 11;

		window.clear(sf::Color::White);

		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				if (sgrid[sf::Mouse::getPosition(window).x/width][sf::Mouse::getPosition(window).y / width] == 9)
					sgrid[i][j] = grid[i][j];
				tile.setTextureRect(sf::IntRect(sgrid[i][j] * width, 0, width, width));
				tile.setPosition(i * width, j * width);
				window.draw(tile);
			}
		}
		window.display();
	}

}