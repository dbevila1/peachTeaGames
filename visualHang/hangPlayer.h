#pragma once

//Daniel Bevilacqua

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class hangPlayer {
public:
	void setPlayer(int, int);

private:
	int xAxis = 1, yAxis = 2;
};