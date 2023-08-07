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
 * Class that acts as the game engine.
 * This is a wrapper class for the game functionality.
 */
class Game {
private:
    // Constants and Configuration Variables
    float pi;                      // The value of pi.
    float gameWidth;               // Width of the game window.
    float gameHeight;              // Height of the game window.
    sf::Vector2f paddleSize;       // Size of the paddles.
    float ballRadius;              // Radius of the ball.
    sf::Clock AITimer;             // Timer for controlling AI behavior.
    sf::Time AITime;               // Time interval for AI updates.
    float paddleSpeed;             // Speed of the player's paddle.
    float basePaddleSpeed;         // Base speed of the paddles.
    float rightPaddleSpeed;        // Speed of the AI's paddle on the right side.
    float baseBallSpeed;           // Base speed of the ball.
    float ballSpeed;               // Current speed of the ball.
    float ballAngle;               // Angle at which the ball moves.
    float dannyAngle;              // Angle for AI player's movement.
    sf::Clock clock;               // Clock for tracking game time.
    sf::Clock dannyClock;          // Clock for controlling AI's movement.
    int dannySpeed;                // Speed of the AI player's movement.

    // Window Setup
    sf::RenderWindow* window;      // Pointer to the game window.
    sf::Sprite loadscreen;         // Sprite for the loading screen.
    sf::Texture dannyTexture;      // Texture for AI player's sprite.
    sf::IntRect dannySprite;       // IntRect for AI player's sprite.
    sf::Sprite sprite;             // General purpose sprite.

    // Loading Screen
    sf::Texture loadscreenTexture; // Texture for the loading screen.

    // Paddle Objects
    sf::RectangleShape leftPaddle;     // Player's left paddle.
    sf::Texture leftPaddleTexture;     // Texture for player's left paddle.
    sf::RectangleShape rightPaddle;    // AI player's right paddle.
    sf::Texture rightPaddleTexture;    // Texture for AI player's right paddle.
    sf::RectangleShape middleLine;     // Center line of the game.

    // Ball Object
    sf::CircleShape ball;             // Ball object.
    sf::Texture balltexture;          // Texture for the ball.

    // Font and Text Objects
    sf::Font font;                    // Font for text rendering.
    sf::Text pauseMessage;            // Text for displaying pause message.
    sf::Text scoreCard;               // Text for displaying the score.

    // Running Events
    sf::Event event;                  // Event object for handling events.
    bool isPlaying;                   // Flag indicating if the game is currently playing.

    // Game Points
    int userPoint;                    // Player's current points.
    int cpuPoint;                     // AI player's current points.

    // Private methods
    void initVariables();
    void initWindow();
    void initPaddles();
    void initBall();
    void initFonts();
    void initMessages();
    void countScore();
    void danny();
    void moveDanny();
    void checkDanny();

public:
    // Constructors / Destructors
    Game();

    // Accessors
    const bool running() const;

    // Functions
    void movePaddles();
    void checkCollisions();
    void pollEvents();
    void point();
    void rungame();
};
