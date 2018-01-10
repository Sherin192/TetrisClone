#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "window.h"
#include "Tetramino.h"
#include <vector>
class Board
{
	Tetramino m_currentTetramino;
	Tetramino m_nextTetramino;
	std::string scoreString;
	std::string loseString;

	sf::Text scoreText;
	sf::Text loseText;
	sf::Font font;
	const float m_tileSize;
	const sf::Vector2f m_boardSizeInTiles;
	Block m_board[20][10];
	sf::RectangleShape m_boardBackground;
	int score;
	bool lost = false;
	void initialize();
	
public:
	Board();
	~Board();
	void swepTetramino();
	const float getTileSize() { return m_tileSize; }
	Tetramino& getCurrentTetramino() { return m_currentTetramino; }
	const sf::Vector2f getBoardSizeInTiles() { return m_boardSizeInTiles; }
	void update(sf::Event event, float& dt);
	bool checkBoardState();
	//void tryToFixTetramino();
	void cancellFullLine();
	void draw(Window& l_window);
	void setLost(bool);
	
};