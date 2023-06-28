#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <SFML/Main.hpp>

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
    // Constants
    float pi;
    float gameWidth;
    float gameHeight;
    sf::Vector2f paddleSize;
    float ballRadius;

    sf::RenderWindow* window;
    sf::Sprite loadscreen;

    // Create the loading screen texture:
    sf::Texture loadscreenTexture;

    // Create paddles
    sf::RectangleShape leftPaddle;
    sf::Texture leftPaddleTexture;
    sf::RectangleShape rightPaddle;
    sf::Texture rightPaddleTexture;

    void initVariables();
    void initWindow();
    void initPaddles();
    void initFonts();
	void initText();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	
};