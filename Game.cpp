#include "Game.h"

void Game::initVariables(){
    this->pi = 3.14159f;
    this->gameWidth = 800;
    this->gameHeight = 600;
    this->paddleSize = sf::Vector2f(50, 100);
    this->ballRadius = 40.f;
    this->AITime = sf::seconds(0.1f);
    this->paddleSpeed = 400.f;
    this->rightPaddleSpeed = 0.f;
    this->ballSpeed = 400.f;
    this->ballAngle = 0.f; // TODO

}

void Game::initWindow(){
	this->window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(gameWidth), static_cast<unsigned int>(gameHeight), 32), "SFML Tennis",
                            sf::Style::Titlebar | sf::Style::Close);
    this->window->setVerticalSyncEnabled(true);

    if(!this->loadscreenTexture.loadFromFile("resources/rumham.png"))
        exit(0);
    this->loadscreen.setTexture(loadscreenTexture);
    this->loadscreen.setPosition(170, 50);
}

void Game::initPaddles(){
      // Create the left paddle
    this->leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    this->leftPaddle.setOutlineThickness(3);
    this->leftPaddle.setOutlineColor(sf::Color::Black);
    this->leftPaddle.setFillColor(sf::Color(100, 100, 200));
    this->leftPaddle.setOrigin(paddleSize / 2.f);
    if(!this->leftPaddleTexture.loadFromFile("resources/leftpaddle.png"))
        return exit(0);
    this->leftPaddle.setTexture(&leftPaddleTexture);

    // Create the right paddle
    this->rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    this->rightPaddle.setOutlineThickness(3);
    this->rightPaddle.setOutlineColor(sf::Color::Black);
    this->rightPaddle.setFillColor(sf::Color(200, 100, 100));
    this->rightPaddle.setOrigin(paddleSize / 2.f);
    if(!this->rightPaddleTexture.loadFromFile("resources/rightpaddle.png"))
        return exit(0);
    rightPaddle.setTexture(&rightPaddleTexture);

}
void Game::initBall(){
    // Create the rum ball
    this->ball.setRadius(ballRadius - 3);
    //this->ball.setOutlineThickness(2);
    this->ball.setOutlineColor(sf::Color::Black);
    this->ball.setFillColor(sf::Color::White);
    this->ball.setOrigin(ballRadius / 1, ballRadius / 1);
    if (!this->balltexture.loadFromFile("resources/rumball.png"))
        return exit(0);
    this->ball.setTexture(&balltexture);
}

void Game::initFonts(){
    if (!this->font.loadFromFile("resources/tuffy.ttf"))
        return exit(0);
}

void Game::initMessages(){
    this->pauseMessage.setFont(font);
    this->pauseMessage.setCharacterSize(40);
    this->pauseMessage.setPosition(170.f, 200.f);
    this->pauseMessage.setFillColor(sf::Color::White);
    this->pauseMessage.setString("Welcome to Danny Pong!\n\nPress space to start the game.");
}

const bool Game::running() const{
	return this->window->isOpen();
}

void Game::rungame(){
    this->window->display();  //Start working on this
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initPaddles();
    this->initBall();
	this->initFonts();
	this->initMessages();
}