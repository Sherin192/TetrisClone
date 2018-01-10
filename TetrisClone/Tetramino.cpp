#include "Tetramino.h"
#include <iostream>


sf::Texture Tetramino::texture[];
bool Tetramino::loaded = false;
int tetraminos[7][4][4][2]
{
	//I
	{
		{
			{ -2, 0 },
			{ -1, 0 },
			{ 0, 0 },
			{ 1, 0 }
		},
		{
			{ 0,-2 },
			{ 0,-1 },
			{ 0,0 },
			{ 0,1 }
		},
		{
			{ -1,0 },
			{ 0,0 },
			{ 1,0 },
			{ 2,0 }
		},
		{
			{ 0,-1 },
			{ 0,0 },
			{ 0,1 },
			{ 0,2 }
		}
	},
	{
		//J
		{
			{ 0, -1 },
			{ 1, -1 },
			{ 0, 0 },
			{ 0, 1 }
		},
		{
			{ 1, 1},
			{ 1, 0 },
			{ 0,0 },
			{ -1, 0 }
		},
		{
			{ -1, 1 },
			{ 0, 1 },
			{ 0, 0 },
			{ 0, -1 }
		},
		{
			{ -1, -1 },
			{ -1, 0 },
			{ 0, 0 },
			{ 1, 0 }
		}
	},
	{
		//L
		{
			{ 0, -1 },
			{ 0, 0 },
			{ 0, 1 },
			{ 1, 1 }
		},
		{
			{ -1, 0 },
			{ 0, 0 },
			{ 1, 0 },
			{ -1, 1 }
		},
		{
			{ -1, -1 },
			{ 0, -1 },
			{ 0, 0 },
			{ 0, 1 }
		},
		{
			{ 1,-1 },
			{ 1, 0 },
			{ 0, 0 },
			{ -1, 0 }
		}
	},
	{
		//O
		{
			{ 0, 0 },
			{ 1, 0 },
			{ 0, 1 },
			{ 1, 1 }
		},
		{
			{ 0, 0 },
			{ 1, 0 },
			{ 0, 1 },
			{ 1, 1 }
		},
		{
			{ 0, 0 },
			{ 1, 0 },
			{ 0, 1 },
			{ 1, 1 }
		},
		{
			{ 0, 0 },
			{ 1, 0 },
			{ 0, 1 },
			{ 1, 1 }
		}
	},
	{
		//S
		{//ok
			{ -1, 0 },
			{ 0, 0 },
			{ 0, -1 },
			{ 1, -1 }
		},
		{//ok
			{ 0, -1 },
			{ 0, 0 },
			{ 1, 0 },
			{ 1, 1 }
		},
		{//ok was wrong
			{ -1, 1 },
			{ 0, 0 },
			{ 0, 1 },
			{ 1, 0 }
		},
		{
			{ 0, -1 },
			{ 0, 0 },
			{ 1, 0 },
			{ 1, 1 }
		}
	},
	{
		//T
		{
			{ 0, -1 },
			{ -1, 0 },
			{ 0, 0 },
			{ 1, 0 }
		},
		{
			{ 0, -1 },
			{ 0, 0 },
			{ 1, 0 },
			{ 0, 1 }
		},
		{
			{ -1, 0 },
			{ 0, 0 },
			{ 1, 0 },
			{ 0, 1 }
		},
		{
			{ 0, -1 },
			{ 0, 0 },
			{ 0, 1 },
			{ -1, 0 }
		}
	},
	{
		//Z
		{
			{ -1, -1 },
			{ 0, -1 },
			{ 0, 0 },
			{ 1, 0 }
		},
		{
			{ 1, -1 },
			{ 1, 0 },
			{ 0, 0 },
			{ 0, 1 }
		},
		{
			{ -1, 0 },
			{ 0, 0 },
			{ 0, 1 },
			{ 1, 1 }
		},
		{
			{ 0, -1 },
			{ 0, 0 },
			{ -1, 0 },
			{ -1, 1 }
		}
	}
};
Tetramino::Tetramino():m_fixed(false), m_readyToBeFixed(false)
{
	srand(time(NULL));
	createTetramino();
}

Tetramino::~Tetramino()
{
}
void Tetramino::createTetramino()
{
	m_positionInTiles = sf::Vector2f(4, 2);
	m_previewInTiles = sf::Vector2f(13, 3);
	m_rotation = rand() % 4;
	m_type = Type(rand() % 7);

	if (!loaded)
	{
		texture[0].loadFromFile("Images/element_blue_square.png");
		texture[1].loadFromFile("Images/element_yellow_square.png");
		texture[2].loadFromFile("Images/element_purple_square.png");
		texture[3].loadFromFile("Images/element_red_square.png");
	}
	
	int index = rand() % 4;
	sprite[0].setTexture(texture[index]);
	sprite[1].setTexture(texture[index]);
	sprite[2].setTexture(texture[index]);
	sprite[3].setTexture(texture[index]);

}
void Tetramino::update()
{
	setPositionInPixel();
	sprite[0].setPosition(m_positionInPixels[0]);
	sprite[1].setPosition(m_positionInPixels[1]);
	sprite[2].setPosition(m_positionInPixels[2]);
	sprite[3].setPosition(m_positionInPixels[3]);
}
void Tetramino::draw(Window& l_window)
{
	l_window.draw(sprite[0]);
	l_window.draw(sprite[1]);
	l_window.draw(sprite[2]);
	l_window.draw(sprite[3]);
}
void Tetramino::preview(Window& l_window)
{
	setPositionInPixel(m_previewInTiles);
	sprite[0].setPosition(m_previewPosition[0]);
	sprite[1].setPosition(m_previewPosition[1]);
	sprite[2].setPosition(m_previewPosition[2]);
	sprite[3].setPosition(m_previewPosition[3]);
	l_window.draw(sprite[0]);
	l_window.draw(sprite[1]);
	l_window.draw(sprite[2]);
	l_window.draw(sprite[3]);
}
void Tetramino::setPosition(float x, float y) {
	m_positionInTiles.x = x;
	m_positionInTiles.y = y;
}
sf::Vector2i Tetramino::pixelsToTiles(sf::Vector2f pos)
{ 
	sf::Vector2i posTiles;
	posTiles.x = (pos.x / 32) - 1;
	posTiles.y = (pos.y / 32) - 1;
	return posTiles; 
}
bool Tetramino::canMove()
{

	if (m_fixed)
		return !m_fixed;
	for (int i = 0; i < 4; ++i)
	{
		if (((m_positionInTiles.y) + tetraminos[m_type][m_rotation][i][1]) == 19)
		{
			return false;
		}
	}
}
void Tetramino::setPositionInPixel(sf::Vector2f pos)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				m_previewPosition[i].x = ((pos.x + 1) + tetraminos[m_type][m_rotation][i][j]) * 32;

			}
			else
			{
				m_previewPosition[i].y = ((pos.y + 1) + tetraminos[m_type][m_rotation][i][j]) * 32;

			}
		}
	}
}
void Tetramino::setPositionInPixel()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				m_positionInPixels[i].x = ((m_positionInTiles.x + 1) + tetraminos[m_type][m_rotation][i][j]) * 32;
				
			}
			else
			{
				m_positionInPixels[i].y = ((m_positionInTiles.y + 1) + tetraminos[m_type][m_rotation][i][j]) * 32;
				
			}
		}		
	}
}
void Tetramino::move(Direction l_direction)
{
	if (m_fixed)
		return;
	if (l_direction == LEFT)
		m_positionInTiles.x -= 1;

	if (l_direction == RIGHT)
		m_positionInTiles.x += 1;

	if (l_direction == DOWN)
		m_positionInTiles.y += 1;
}
void Tetramino::onTick()
{
	if (!m_fixed)
		m_positionInTiles.y += 1;
}
void Tetramino::rotate() {
	m_rotation = (m_rotation + 1) % 4;
}