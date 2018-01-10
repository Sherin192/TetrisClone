#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "window.h"
#include "board.h"

enum GameState {Menu, Play, Exit};
class Game
{
	
private:
	
	Window window;
	Board board;
	GameState gameState;
	sf::Clock m_clock;
	float m_elapsed;
	float timeStep;
	float tick;
	bool m_exit;

	void initialize();
	void loop();
public:
	void exit();
	sf::Time getElapsed();
	void restartClock();
	Game();
	~Game();
};
