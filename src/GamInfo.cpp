#include "GameInfo.h"
#include <string>

GameInfo::GameInfo()
{	
	m_text.setFont(Singleton::instance().getFont());
	m_lose.setTexture(&(Singleton::instance().getEnd(0)));
	m_win.setTexture(&(Singleton::instance().getEnd(1)));

	m_lose.setSize(sf::Vector2f(1000, 750));
	m_win.setSize(sf::Vector2f(1000, 750));

	m_lose.setPosition(sf::Vector2f(175, 70));
	m_win.setPosition(sf::Vector2f(175, 70));

	m_scoreText.setFont(Singleton::instance().getFont());
	m_scoreText.setPosition(m_lose.getSize().x / 1.5, m_lose.getSize().y / 1.06);

	m_playerPoints = 0;
	m_Playerlife = LIFE;
	m_timeOut = false;	
}

int GameInfo::getPlayerPoints() const
{
	return m_playerPoints;
}

int GameInfo::getPlayerLife() const
{
	return m_Playerlife;
}

bool GameInfo::getTimeOut() const
{
	return m_timeOut;
}

void GameInfo::setPlayerPoints(int amount)
{
	m_playerPoints = amount;
}

void GameInfo::setPlayerLife(int amount)
{
	m_Playerlife = amount;
}

void GameInfo::setTimeOut(bool state)
{
	m_timeOut = state;
}

void GameInfo::displayInfo(sf::RenderWindow& window, float time, int life, int cheese, int points, int keys, int level)
{
	std::string infoString = "\n" + std::to_string((int)time) +
							"\n\n" + std::to_string(life) +
							"\n\n" + std::to_string(cheese) +
							"\n\n" + std::to_string(points) +
							"\n\n" + std::to_string(keys) +
							"\n\n" + std::to_string(level);

	m_text.setCharacterSize(45);
	m_text.setString(infoString);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition((window.getSize().x/1.25)+120, 4);
	window.draw(m_text);
}

void GameInfo::youLoseWin(sf::RenderWindow& window, bool win)
{
	window.draw(win ? m_win : m_lose);

	std::string infoString = std::to_string(m_playerPoints);
	m_scoreText.setString(infoString);
	m_scoreText.setCharacterSize(55);
	m_scoreText.setFillColor(sf::Color(102, 4, 204));
   
    window.draw(m_scoreText);
}