#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "Animation.h"
#include "Player.h"
#include "Menu.h"
#include "HangGame.h"

static const float VIEW_HEIGHT = 520.0f;

int main(){
	sf::RenderWindow window(sf::VideoMode(720, 720), "Main Menu", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	Menu menu(window.getSize().x, window.getSize().y);
	HangGame hangGame;

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()){
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				hangGame.ResizeView(window, view);
				break;

			case sf::Event::KeyReleased:
				switch (evnt.key.code) {
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem()) {
					case 0:
						menu.SetPressedItem(-1);
						break;
					case 1:
						window.close();
						break;
					}
					break;
				}
			}
		}

		if (menu.GetPressedItem() != -1) {
			menu.draw(window);
			window.display();
		}

		else {
			window.close();
			hangGame.DisplayHangGame();
			window.clear();
			menu.SetPressedItem(-1);	
		}
	}

	return 0;
}
