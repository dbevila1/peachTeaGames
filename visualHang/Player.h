#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Player {
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	//void Update(float deltaTime);
	void PosUpdate(int row, int column, float deltaTime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition();
	

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
};