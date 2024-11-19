// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Text text, vertex;
	Font font;
	font.loadFromFile("fonts/KIN668.ttf");

	// select the font
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString("Welcome to Chaos Game!! \nClick Anywhere to Start.");
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	// set the color
	text.setFillColor(sf::Color::White);
	// set the text style
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(951, 574);

	vertex.setFont(font); // font is a sf::Font

	//records mouse presses CV
	int MouseCounter = 0;


	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
					{
						///fourth click
						///push back to points vector
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			MouseCounter++;
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		// inside the main loop, between window.clear() and window.display()
		if (MouseCounter == 0)
		{
			window.draw(text);
		}
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);

			string points = "2";

			window.draw(vertex);
			vertex.setString(points);
			// set the character size
			vertex.setCharacterSize(24); // in pixels, not points!
			// set the color
			vertex.setFillColor(sf::Color::White);
			// set the text style
			//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			vertex.setPosition(vertices[i].x, vertices[i].y);
		}
		window.display();
	}
}
