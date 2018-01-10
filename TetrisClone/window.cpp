#include "window.h"
#include <iostream>
Window::Window()
{
	setup("Window", sf::Vector2u(640, 480));
}
Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
	setup(l_title, l_size);
}
Window::~Window()
{
	destroy();
}
sf::RenderWindow& Window::getRenderWindow()
{
	return m_window;
}

void Window::setup(const std::string& l_title, const sf::Vector2u& l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isDone = false;
	m_isFullScreen = false;
	create();
}
void Window::create()
{
	sf::Uint32 style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);

	m_window.create({ m_windowSize.x, m_windowSize.y}, m_windowTitle, style);
}
void Window::update()
{
	sf::Event event;
	m_window.pollEvent(event);
	while (m_window.pollEvent(event))
	{
	if (event.type == sf::Event::Closed)
	{
		m_isDone = true;
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
	{
		ToggleFullScreen();
	}
	}
}
void Window::ToggleFullScreen()
{
	m_isFullScreen = !m_isFullScreen;
	destroy();
	create();
}
void Window::beginDraw()
{
	m_window.clear(sf::Color::Black);
}
void Window::endDraw()
{
	m_window.display();
}
bool Window::isDone()
{
	return m_isDone;
}

bool Window::isFullScreen()
{
	return m_isFullScreen;
}
sf::Vector2u Window::getWindowSize()
{
	return m_windowSize;
}
void Window::draw(sf::Drawable& l_drawable)
{
	m_window.draw(l_drawable);
}
void Window::destroy()
{
	m_window.close();
}
