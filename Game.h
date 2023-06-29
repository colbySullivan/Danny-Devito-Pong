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

class Game{
private:
    // Variables
    float pi;
    float gameWidth;
    float gameHeight;
    sf::Vector2f paddleSize;
    float ballRadius;
    sf::Clock AITimer;
    sf::Time AITime;
    float paddleSpeed;
    float basePaddleSpeed;
    float rightPaddleSpeed;
    float baseBallSpeed;
    float ballSpeed;
    float ballAngle;
    sf::Clock clock;

    //Window setup
    sf::RenderWindow* window;
    sf::Sprite loadscreen;

    // Create the loading screen texture:
    sf::Texture loadscreenTexture;

    // Create paddles
    sf::RectangleShape leftPaddle;
    sf::Texture leftPaddleTexture;
    sf::RectangleShape rightPaddle;
    sf::Texture rightPaddleTexture;
    sf::RectangleShape middleLine;

    // Create ball
    sf::CircleShape ball;
    sf::Texture balltexture;

    // Set font
    sf::Font font;

    // Create text
    sf::Text pauseMessage;
    sf::Text scoreCard;

    //Running events
    sf::Event event;
    bool isPlaying;

    //Game points
    int userPoint;
    int cpuPoint;

    void initVariables();
    void initWindow();
    void initPaddles();
    void initBall();
    void initFonts();
	void initMessages();
    void countScore();
public:
	//Constructors / Destructors
	Game();

	//Accessors
	const bool running() const;

    //Functions
    void movePaddles();
    void checkCollisions();
    void pollEvents();
    void point();
    void rungame();
};