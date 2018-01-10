#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "window.h"
#include <iostream>

struct Block
{
	bool fixed;
	sf::Sprite sprite;
};

enum Type  { I, J, L, O, S, T, Z};
enum Color {RED};
enum Direction {DOWN, LEFT, RIGHT};
class Tetramino
{
	static bool loaded;
	static sf::Texture texture [4];
	sf::Sprite sprite[4];
	sf::Vector2f m_positionInPixels[4];
	sf::Vector2f m_positionInTiles;
	sf::Vector2f m_previewInTiles;
	sf::Vector2f m_previewPosition[4];
	Type m_type;
	int m_rotation;
	bool m_fixed;
	bool m_readyToBeFixed;
	Color m_color;
	
	public:
		Tetramino();
		~Tetramino();
		void update();
		void draw(Window& l_window);
		void createTetramino();
		void setPositionInPixel();
		int getRotation() { return m_rotation; }
		void setFixed() { m_fixed = true; std::cout << "fixing" << std::endl; }
		bool getFixed() { return m_fixed; }
		void setReadyToBeFixed() { m_readyToBeFixed = true; }
		void resetReadyToBeFixed() { m_readyToBeFixed = false; }
		bool getReadyToBeFixed() { return m_readyToBeFixed; }
		sf::Vector2f getPositionInPixelsOfaTile(int i) { return m_positionInPixels[i]; }
		sf::Vector2i pixelsToTiles(sf::Vector2f pos); 
		void rotate();
		sf::Sprite getSprite(int i) { return sprite[i]; }
		void setPosition(sf::Vector2f pos) { m_positionInTiles = pos; }
		void setPosition(float x, float y);
		sf::Vector2f getPosition() { return m_positionInTiles; }
		bool canMove();
		void move(Direction l_direction);
		void onTick();
		void preview(Window& l_window);
		void setPositionInPixel(sf::Vector2f pos);
};