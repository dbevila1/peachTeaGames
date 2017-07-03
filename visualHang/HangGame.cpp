#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include<string>
#include<Windows.h>
#include "Animation.h"
#include "Player.h"
#include "HangGame.h"

using namespace std;

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

void HangGame::Intro() {
	HANDLE  hConsole;
	HangGame hangGame;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 6; i > imgAn; --i) {
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "Welcome to HangMan! V1.0, I hope your ready to play.\n";
		//hangGame.HangingMan(i);
		Sleep(1000);
		system("CLS");
	}
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "Welcome to HangMan! V1.0, I hope your ready to play.\n";
	std::cout << "Please enter the word of choosing: ";
	std::cin >> hangWord;
	permHangWord = hangWord;
	std::cout << "\n";
	system("CLS");
	std::cout << "Welcome to HangMan! V1.0, I hope your ready to play.\n";
}

void HangGame::LetterGuess() {
	if (STOP == -1) {
		std::cout << "Enter your guessed letter: ";
		std::cin >> guess;
	}
	else
		exit;
}

int HangGame::Match() {
	HANDLE  hConsole;
	HangGame hangGame;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	flip = 1;
	int leng = hangWord.length();
	int gmeOvrCntr = leng;
	for (int i = 0; i < leng; ++i) {
		if (guess == hangWord[i]) {
			system("CLS");
			std::cout << "We have a match!\nThe match was " << guess << "\n";
			//hangGame.HangingMan(hangImg + 1);
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "You have " << hangImg << " guesses left.\n";
			hangWord[i] = 0;
			flip = 0;
			if (hangWord[i + 1] != 0) {
				return 0;
			}
		}
		if (hangWord[i] == 0) {
			--gmeOvrCntr;
			if (gmeOvrCntr < 1) {
				std::cout << "You win!!!\n";
				std::cout << "The winning word was: " << permHangWord << "\n\n";
				return -1;
			}
		}
	}
	if (flip != 0) {
		system("CLS");
		std::cout << "The letter " << guess << " is not in the word. \n\n";
		//hangGame.HangingMan(hangImg);
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "You have " << hangImg - 1 << " guesses left.\n";
		if (hangImg - 1 == 0) {
			std::cout << "The winning word was: " << permHangWord << "\n";
			return -1;
		}
		--hangImg;
		return 0;
	}
	return 0;
}

bool HangGame::keepPlaying() {
	if (hangImg > 0) {
		return true;
	}
	else return false;
}
