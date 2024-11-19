// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

/*
	****************************************
	TODO:
		find a way to populate points faster 
		fix the problem of 2 outlier points 

	****************************************
*/

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

	Font font;
	font.loadFromFile("fonts/KIN668.ttf");

	//intro text
	Text text;
	text.setFont(font);
	text.setString("Welcome to Chaos Game!! \nClick Anywhere to Start.\n\nTo form a Sierpinski Triangle, \nclick 3 times anywhere to form \nthe trianlge and another time to \nstart generating a Sierpinski form.");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(150, 150);
	text.setFont(font);

	//records mouse clicks 
	int ClickCounter = 0;


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
			//Reads Mouse input
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					ClickCounter++;
					std::cout << ClickCounter << std::endl;
					
					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
					{
						///fourth click
						///push back to points vector
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			//code of populating the triangle to form the Sierpinski look 
			int random = rand() % 3, random2 = 0;
			float newx = 0, newy = 0;
			cout << "ChosenPoint.x is " << vertices[random].x << " ChosenPoint.y is " << vertices[random].y << endl;
			newx = (((vertices[random].x - points.back().x) / 2) + points.back().x); 
			newy = (((vertices[random].y - points.back().y) / 2) + points.back().y); 
			cout << "New verticie is " << newx << " " << newy << endl;
			points.push_back(Vector2f(newx, newy));

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
		
		//intro text
		if (ClickCounter < 3)
		{
			window.draw(text);
		}

		if (ClickCounter == 3)
		{
			text.setString("Click again to start \nforming the Sierpinski Triangle");
			text.setPosition(150, 150);
			window.draw(text);
		}
		//Draws the starting vertices
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);


		}
		//Draws the popluated points for Sierpinski Triangle
		for (int i = 1; i < points.size(); i++)
		{
			RectangleShape rect2(Vector2f(10, 10));
			rect2.setPosition(Vector2f(points[i].x, points[i].y));
			rect2.setFillColor(Color::Red);
			window.draw(rect2);
		}


		window.display();
	}
}
