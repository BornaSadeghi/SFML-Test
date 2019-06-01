#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>

sf::Font loadFont (std::string fontName) {
	sf::Font font;
	if (!font.loadFromFile("C://Windows//Fonts//" + fontName + ".ttf"))
		throw ("Font not found");
	return font;
}

float lerp (float from, float to, float smooth){
	return from + (to-from)/smooth;
}

sf::RenderWindow window(sf::VideoMode(400,400), "Hello World", sf::Style::Close | sf::Style::Titlebar);
sf::Font arialFont = loadFont("Arial");

class Player {
public:
	sf::RectangleShape rect;
	sf::Text infoText;

	int x,y, dX=0,dY=0;
	int sizeX=100, sizeY=100;

	float vX=0, vY=0;

	float moveSmoothing = 12;
	float speed = 10;

	Player(int x, int y){
		this->x = x;
		this->y = y;
		this->rect = sf::RectangleShape(sf::Vector2f(100,100));
		this->rect.setFillColor(sf::Color::Red);

		this->infoText = sf::Text("Bruh", arialFont);
	}

	void update (){
		this->vX = lerp(this->vX, this->dX*speed, this->moveSmoothing);
		this->vY = lerp(this->vY, this->dY*speed, this->moveSmoothing);

		this->x += this->vX;
		this->y += this->vY;

		this->rect.setPosition(x, y);
		this->infoText.setPosition(x, y);

		this->infoText.setString("x: " + std::to_string(this->x) + "\n" + "y: " + std::to_string(this->y));
	}

	void draw(){
		window.draw(this->rect);
		window.draw(this->infoText);
	}
};


int main()
{
	// sf is the namespace for sfml
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	Player player(0,0);

	sf::Font fontArial = loadFont("Arial");

	// while running
	while (window.isOpen()) {
		sf::Event e;

		// similar to Pygame's "for e in event.get()"
		while (window.pollEvent(e)) {
			switch (e.type){
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch(e.key.code){
				case sf::Keyboard::Key::W:
					player.dY -= 1;
					break;
				case sf::Keyboard::Key::A:
					player.dX -= 1;
					break;
				case sf::Keyboard::Key::S:
					player.dY += 1;
					break;
				case sf::Keyboard::Key::D:
					player.dX += 1;
					break;
				}
				break;
				case sf::Event::KeyReleased:
					switch(e.key.code){
					case sf::Keyboard::Key::W:
						player.dY += 1;
						break;
					case sf::Keyboard::Key::A:
						player.dX += 1;
						break;
					case sf::Keyboard::Key::S:
						player.dY -= 1;
						break;
					case sf::Keyboard::Key::D:
						player.dX -= 1;
						break;
					}
					break;
			}
		}

		printf("%f %f\n", player.vX, player.vY);
		fflush(stdout);

		player.update();

		window.clear();

		player.draw();

		window.display();
	}

	return 0;
}
