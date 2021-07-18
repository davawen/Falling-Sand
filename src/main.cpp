#include <iostream>
#include <SFML/Graphics.hpp>

#include "matrix.hpp"
#include "element.hpp"

int main(int argc, char **argv)
{
	sf::RenderWindow window{sf::VideoMode(1000, 1000), "Window", sf::Style::Default};
	
	int width = 333;
	int height = 333;
	
	sf::Texture texture;
	if(!texture.create(width, height))
	{
		printf("Failed to create texture.\n");
		return -1;
	}
	
	Matrix matrix = Matrix(width, height);
	
	int textureLength = width * height * 4;
	sf::Uint8 *pixels = new sf::Uint8[textureLength];
	
	texture.update(pixels);
	
	sf::Sprite sprite{texture};
	sprite.setScale(3.f, 3.f);
	
	
	sf::Clock __deltaClock;
	float deltaTime = 0.f;
	
	float timePassed = 0.f;
	
	int mouseButtonDown = -1;
	
	unsigned int selectedElement = 1;
	
	while(window.isOpen())
	{
		deltaTime = __deltaClock.restart().asSeconds();
		
		sf::Event event;
		
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					mouseButtonDown = event.mouseButton.button;
					break;
				case sf::Event::MouseButtonReleased:
					mouseButtonDown = -1;
					break;
				case sf::Event::MouseWheelScrolled:
					if(event.mouseWheel.delta) selectedElement++;
					else selectedElement--;
					
					selectedElement = std::clamp(selectedElement, 0U, 3U);
					break;
				case sf::Event::KeyPressed:
					switch(event.key.code)
					{
						//Reload sim
						case sf::Keyboard::Key::R:
							for(int i = 0; i < matrix.len; i++)
							{
								matrix.grid[i].type = Element::Type::Empty;
								matrix.grid[i].setColor();
							}
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
		
		sf::Vector2i mousePos = sf::Mouse::getPosition(window) / 3;

		if(mouseButtonDown != -1 && mousePos.x > 1 && mousePos.x < width-1 && mousePos.y > 1 && mousePos.y < height-1)
		{
			for(int i = -1; i <= 1; i++)
			{
				for(int j = -1; j <= 1; j++)
				{
					matrix.setElementAt(mousePos.x + i, mousePos.y + j, (Element::Type)selectedElement);
				}
			}
		}

		timePassed += deltaTime;
		
		while(timePassed > 1.f/60.f)
		{
			// Step simulation
			
			matrix.step();
			matrix.draw(pixels);
			
			texture.update(pixels);
			
			// Display change
			window.clear();
			
			window.draw(sprite);

			window.display();
			
			timePassed -= 1.f / 60.f;

			printf("\x1b[2K\x1b[1000D%f FPS\n\x1b[1A", 1.f / deltaTime);
		}
	}
	
	return 0;
}