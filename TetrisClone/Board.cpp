#include "Board.h"
#include <iostream>
Board::Board() : m_tileSize(32), m_boardSizeInTiles(10, 20)
{
	initialize();
}
void Board::initialize()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_board[i][j].fixed = false;
		}
	}
	
	score = 0;
	if (!font.loadFromFile("BungeeInline-Regular.ttf"))
	{
		std::cout << "error" << std::endl;
	}
	scoreText.setFont(font);
	scoreText.setColor(sf::Color::Red);
	scoreString = "Score: " + std::to_string(score);
	scoreText.setString(scoreString);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(sf::Vector2f(440, 40));
	loseString = "You Lost.";
	loseText.setFont(font);
	loseText.setColor(sf::Color::Red);
	loseText.setString(loseString);
	loseText.setCharacterSize(24);
	loseText.setPosition(420, 400);

	m_boardBackground.setSize(sf::Vector2f(m_tileSize * m_boardSizeInTiles.x, m_tileSize * m_boardSizeInTiles.y));
	m_boardBackground.setPosition(m_tileSize, m_tileSize);
	m_boardBackground.setFillColor(sf::Color(255, 0, 0, 128));
	m_boardBackground.setOutlineColor(sf::Color::White);
	m_boardBackground.setOutlineThickness(2.0f);

	m_currentTetramino.setPosition(sf::Vector2f(6, 8));
}
Board::~Board()
{
}
void Board::update(sf::Event event, float& dt)
{
	bool cantMoveRight = false;
	bool cantMoveLeft = false;
	sf::Vector2f pos;
	sf::Vector2i posTiles;
	if (dt > 0.8f)
	{
		dt -= 0.8f;
		if (!m_currentTetramino.getReadyToBeFixed())
			getCurrentTetramino().onTick();
	}
	if (m_currentTetramino.getFixed())
		swepTetramino();
	
	
	bool canMoveDown = true;
	for (int i = 0; i < 4; ++i)
	{
		pos = m_currentTetramino.getPositionInPixelsOfaTile(i);
		posTiles = m_currentTetramino.pixelsToTiles(pos);
		std::cout << "pos: " << posTiles.y << std::endl;
		if (posTiles.x == 0)
			cantMoveLeft = true;
		if (posTiles.x == 9)
			cantMoveRight = true;
		if (posTiles.x < 10 && m_board[posTiles.y][posTiles.x + 1].fixed == true)
			cantMoveRight = true;
		if (m_board[posTiles.y][posTiles.x - 1].fixed == true)
			cantMoveLeft = true;
		if (posTiles.y <= 19 && posTiles.y + 1 == 20 || m_board[posTiles.y + 1][posTiles.x].fixed == true)
		{
			canMoveDown = false;
			if (m_currentTetramino.getReadyToBeFixed() || posTiles.y == 19)
			{
				if (dt > 0.4f)
				{
					dt -= 0.4f;
					m_currentTetramino.setFixed();
					std::cout << "setFixed" << std::endl;
				}
			}
			else
			{
				std::cout << "setReadyFixed" << std::endl;

				m_currentTetramino.setReadyToBeFixed();
			}
		}
	}
	if (canMoveDown && m_currentTetramino.getReadyToBeFixed())
	{
		std::cout << "reset" << std::endl;
		m_currentTetramino.resetReadyToBeFixed();
	}
	if (!m_currentTetramino.getFixed())
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left && !cantMoveLeft)
			{
				m_currentTetramino.move(LEFT);
			}
			if (event.key.code == sf::Keyboard::Right && !cantMoveRight)
				m_currentTetramino.move(RIGHT);
			if (!m_currentTetramino.getReadyToBeFixed())
			{
				if (event.key.code == sf::Keyboard::Down)
					m_currentTetramino.move(DOWN);
				if (event.key.code == sf::Keyboard::Space)
				{
					m_currentTetramino.rotate();
				}
			}	
		}
		for (int i = 0; i < 4; ++i)
		{
			pos = m_currentTetramino.getPositionInPixelsOfaTile(i);
			posTiles = m_currentTetramino.pixelsToTiles(pos);
			if (posTiles.x  < 0)
			{
				m_currentTetramino.setPosition(m_currentTetramino.getPosition().x + 1, m_currentTetramino.getPosition().y);
			}
			if (posTiles.x  > 9)
			{
				m_currentTetramino.setPosition(m_currentTetramino.getPosition().x - 1, m_currentTetramino.getPosition().y);
			}
		}
		m_currentTetramino.update();
	}

	if (!m_currentTetramino.canMove())
	{
		m_currentTetramino.setReadyToBeFixed();
	}
	cancellFullLine();
}

void Board::draw(Window& l_window)
{
	int c = 0;
	l_window.draw(m_boardBackground);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_board[i][j].fixed)
			{
				c++;
				l_window.draw(m_board[i][j].sprite);
			}	
		}
	}
	m_nextTetramino.preview(l_window);
	m_currentTetramino.draw(l_window);
	
	scoreText.setString(scoreString);
	l_window.draw(scoreText);
	if (lost)
	l_window.draw(loseText);
}
void Board::swepTetramino()
{
	sf::Vector2f pos;
	sf::Vector2i posTiles;
	for (int i = 0; i < 4; ++i)
	{
		pos = m_currentTetramino.getPositionInPixelsOfaTile(i);
		posTiles = m_currentTetramino.pixelsToTiles(pos);

		m_board[posTiles.y][posTiles.x].fixed = true;
		m_board[posTiles.y][posTiles.x].sprite = m_currentTetramino.getSprite(i);
	}
	m_currentTetramino = m_nextTetramino;
	m_nextTetramino.createTetramino();
}

void Board::cancellFullLine() {
	int count = 0;
	bool d = false;
	for (int i = 19; i >= 0; i--)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_board[i][j].fixed)
			{
				count++;
			}
			if (count == 10)
			{
				score += 10;
				scoreString = "Score: " + std::to_string(score);
				for (i; i > 0; i--)
				{
					for (j = 0; j < 10; j++)
					{
						m_board[i][j].fixed = m_board[i - 1][j].fixed;
						d = true;
					}
				}
			}
		}
		if (d)
		{
			for (int i = 0; i < 20; i++)
			{
				std::cout << i << " ";
				for (int j = 0; j < 10; j++)
				{
					std::cout << "["<< i <<"]" <<"["<<j <<"]"<<m_board[i][j].fixed;
				}
				std::cout << std::endl;
			}
		}
		
		count = 0;
	}
}

bool Board::checkBoardState()
{
	for (int i = 0; i < 10; ++i)
	{
		if (m_board[3][i].fixed)
			return true;
	}
	return false;
}
void Board::setLost(bool)
{
	lost = true;
}
