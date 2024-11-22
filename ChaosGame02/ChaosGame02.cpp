// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

//Finding the height of the triangle that was made with the 3 verticies 
float heightCalc(vector<Vector2f> vertices)
{
	float x1 = vertices[0].x, y1 = vertices[0].y, x2 = vertices[1].x, y2 = vertices[1].y, x3 = vertices[2].x, y3 = vertices[2].y, a, b, c, s, area, base = 0, h;

	a = sqrt(pow(x2 - x1, 2.0) + (pow(y2 - y1, 2.0)));
	b = sqrt(pow(x3 - x2, 2.0) + (pow(y3 - y2, 2.0)));
	c = sqrt(pow(x3 - x1, 2.0) + (pow(y3 - y1, 2.0)));

	s = (a + b + c) / 2.0;

	area = sqrt(s * (s - a) * (s - b) * (s - c));

	if ((a > b && a > c) || (a == b && a > c))
	{
		base = a;
	}
	else if ((b > a && b > c) || (b == c && b > a))
	{
		base = b;
	}
	else if ((c > a && c > b) || (c == a && c > b))
	{
		base = c;
	}
	else
	{
		base = a;
	}

	h = (2 * area) / base;

	return h;
}
int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Sierpinski's Christimas Tree (Chaos Game!!)", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Font font;
	if (!font.loadFromFile("fonts/KIN668.ttf");)
	{
		return -1;
	}

	//Instruction text
	Text text;
	text.setFont(font);
	text.setString("Welcome to Chaos Game!!\n\nTo form a Sierpinski Triangle, \nclick 3 times within the circle to form \nthe triangle and another time to \nstart generating a Sierpinski form.");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(150, 150);

	//Star image
	Texture textureStar;
	textureStar.loadFromFile("graphics/star2.png");
	Sprite spriteStar;
	spriteStar.setTexture(textureStar);
	spriteStar.setScale(0.075, 0.075);

	//Circle outline
	CircleShape circ(200, 30);
	circ.setPosition(760, 340);
	circ.setFillColor(Color::Transparent);
	circ.setOutlineColor(Color::White);
	circ.setOutlineThickness(10);

	//Base Rectangle
	RectangleShape rect(Vector2f(10, 10));
	
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
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					ClickCounter++;

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
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
			int random = rand() % 3;
			float NewX = 0, NewY = 0; 
			//cout << "ChosenPoint.x is " << vertices[random].x << " ChosenPoint.y is " << vertices[random].y << endl;
			NewX = (((vertices[random].x - points.back().x) /2) + points.back().x);
			NewY = (((vertices[random].y - points.back().y) / 2) + points.back().y);
			//cout << "New verticie is " << Newx << " " << Newy << endl;
			points.push_back(Vector2f(NewX, NewY));

		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		if (ClickCounter < 3) 
		{
			window.draw(text);
			window.draw(circ);
		}
		if (ClickCounter == 3)
		{
			text.setString("Click again to start\nforming the Sierpinski Triangle");
			window.draw(text);
			
		}

		for (int i = 0; i < vertices.size(); i++)
		{
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Cyan);
			if (ClickCounter < 4)
			{
				window.draw(rect);
			}
		}
		
		//middle triangle
		for (int i = 5; i < points.size(); i++)
		{
			rect.setPosition(Vector2f(points[i].x, points[i].y));
			//rect.setFillColor(Color::Green);
			if (i % 15 == 0)
			{
				rect.setFillColor(Color::Red);
			}
			else
			{
				rect.setFillColor(Color::Green);
			}
			window.draw(rect);
		}

		//bottom triangle
		for (int i = 5; i < points.size(); i++)
		{
			rect.setPosition(Vector2f(points[i].x, points[i].y + heightCalc(vertices)));
			//rect.setFillColor(Color::Green);
			if (i % 15 == 0)
			{
				rect.setFillColor(Color::Yellow);
			}
			else
			{
				rect.setFillColor(Color::Green);
			}
			window.draw(rect);
		}

		//top triangle
		for (int i = 5; i < points.size(); i++)
		{
			rect.setPosition(Vector2f(points[i].x, points[i].y - heightCalc(vertices)));
			//rect.setFillColor(Color::Green);
			if (i % 15 == 0)
			{
				rect.setFillColor(Color::Blue);
			}
			else
			{
				rect.setFillColor(Color::Green);
			}
			window.draw(rect);
		}

		//Next instruction
		if (ClickCounter == 4) 
		{
			text.setString("Click again to put a star on the tree!!!");
			window.draw(text);

		}

		//Placing the star and funny text
		if (ClickCounter > 4)
		{
			text.setString("Happy \nThanksgiving!!!!!\n!!!!!!!");
			text.setOutlineColor(Color::Red);
			text.setOutlineThickness(5);
			text.setScale(2, 2);
			text.setFillColor(Color::Green);
			window.draw(text);

			Vector2f peak;
			if (vertices[0].y < vertices[1].y && vertices[0].y < vertices[2].y)
			{
				peak = vertices[0];
			}
			else if (vertices[1].y < vertices[0].y && vertices[1].y < vertices[2].y)
			{
				peak = vertices[1];
			}
			else if (vertices[2].y < vertices[0].y && vertices[2].y < vertices[1].y)
			{
				peak = vertices[2];
			}

			spriteStar.setOrigin(peak);
			spriteStar.setPosition(peak.x + 30, (peak.y - heightCalc(vertices)) - 20);
			window.draw(spriteStar);
		}
		window.display();
	}
	return 0;
}
