#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();

	void beginDraw(); 
	void endDraw();

	void update();

	bool isDone();
	bool isFullScreen();
	sf::Vector2u getWindowSize();
	sf::RenderWindow& getRenderWindow();
	void ToggleFullScreen();

	void draw(sf::Drawable& l_drawable);

private:
	
	void setup(const std::string& l_title, const sf::Vector2u& l_size);

	void destroy();
	void create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullScreen;
};