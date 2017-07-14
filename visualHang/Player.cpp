#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) : animation(texture, imageCount, switchTime) {
	this->speed = speed;
	row = 0;
	body.setSize(sf::Vector2f(200.0f, 200.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(500.0f, 380.0f);
	body.setTexture(texture);
}
/*
void Player::Update(float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);
	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}
*/
void Player::PosUpdate(int _row, int _column,float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);
	animation.PosUpdate(_row, _column, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(body, sf::BlendMultiply);
}

sf::Vector2f Player::GetPosition() {
	return body.getPosition();
}