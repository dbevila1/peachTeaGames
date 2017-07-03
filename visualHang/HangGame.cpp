#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "Animation.h"
#include "Player.h"
#include "HangGame.h"

static const float VIEW_HEIGHT = 520.0f;

void HangGame::ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int HangGame::DisplayHangGame() {
	sf::RenderWindow window(sf::VideoMode(720, 720), "Hang Man!", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	/*Background Texture*/
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("hangBckGrnd.png");
	sf::Sprite background(backgroundTexture);
	sf::Vector2f targetSize(1750.0f, 700.0f);
	background.setScale(targetSize.x / background.getLocalBounds().width, targetSize.y / background.getLocalBounds().height);
	/*End Background Texture*/

	/*Player Texture*/
	sf::Texture playerTexture;
	playerTexture.loadFromFile("hangBoat.png");
	Player player(&playerTexture, sf::Vector2u(2, 4), 0.3f, 100.0f);
	/*End Player Texture*/

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
		player.Update(deltaTime);
		view.setCenter(player.GetPosition());

		window.clear();
		window.setView(view);
		window.draw(background);
		player.Draw(window);
		window.display();
	}
	return 0;
}