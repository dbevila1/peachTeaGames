#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class HangGame {
public:
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	int DisplayHangGame();
	sf::Text Intro(const sf::RenderWindow& window);
	void LetterGuess();
	int Match();
	bool keepPlaying();

private:
	std::string permHangWord;
	std::string hangWord;
	sf::Font font;
	int imgAn = 0;
	char guess;
	int hangImg = 6;
	int flip = 1;
	char playAgain;
	int STOP = -1;
};