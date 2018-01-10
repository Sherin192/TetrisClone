#include "game.h"
#include <iostream>
Game::Game(): window("Tetris Clone", sf::Vector2u(600, 704))
{
	
	initialize();
}
Game::~Game()
{

}
void Game::initialize()
{
	m_exit = false;
	gameState = Play;
	tick = 0.0f;
	m_clock.restart();
	m_elapsed = 0.0f;
	timeStep = 0.1f;
	window.update();
	window.beginDraw();
	board.draw(window);

	window.endDraw();
	while (!m_exit)
	{
		loop();
	}
}
sf::Time Game::getElapsed() { return m_clock.getElapsedTime(); }
void Game::restartClock() { m_elapsed += m_clock.restart().asSeconds(); }

void Game::loop()
{		

	switch (gameState)
	{
		case Play:
			sf::Event event;
			if (board.checkBoardState())
				gameState = Exit;
				//exit();
			window.getRenderWindow().pollEvent(event);

			board.update(event, m_elapsed);
			window.beginDraw();
			board.draw(window);
			window.endDraw();

			restartClock();
		break;
		case Exit:
			std::cout << "lost\n";
			board.setLost(true);
			window.beginDraw();
			board.draw(window);
			window.endDraw();
			break;
	}
		
	
}

void Game::exit()
{
	m_exit = true;
}