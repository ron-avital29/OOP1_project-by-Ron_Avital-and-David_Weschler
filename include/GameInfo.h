#pragma once

#include <SFML/Graphics.hpp>
#include "SingleTon.h"

class GameInfo
{
public:
	GameInfo();

	int getPlayerPoints() const;
	int getPlayerLife() const;
	bool getTimeOut() const;

	void setPlayerPoints(int amount);
	void setPlayerLife(int amount);
	void setTimeOut(bool state);
    
	void displayInfo(sf::RenderWindow& window, float time, int life, int cheese, int points, int keys, int level);
	void youLoseWin(sf::RenderWindow& window, bool win);
	
private:
	sf::Text m_text;
	sf::Text m_scoreText;
	sf::RectangleShape m_win;
	sf::RectangleShape m_lose;

	int m_playerPoints;
	int m_Playerlife;
	bool m_timeOut;
};