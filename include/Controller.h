#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Singleton.h>
#include "Button.h"
#include "GameInfo.h"
#include "StaticObj.h"
#include "Animal.h"
#include "Wall.h"
#include "Cheese.h"
#include "Mouse.h"
#include "Cat.h"
#include "Door.h"
#include "Key.h"
#include "Present.h"
#include "Heart.h"
#include "Clock.h"

class Controller
{
public:
	Controller(const std::vector<std::string>& file, int level, GameInfo& myInfo);

	void run(sf::RenderWindow& window);

private:
	void prepLevel(const std::vector<std::string>& file);
	void assignObj(const char objSymbol, int row, int col);
	void assignPresent(int presentKind);
	void handleKeyPressed(sf::Keyboard::Key keyCode, sf::Time deltaTime);
	void handleCollisions();
	void handleBoard();
	void moveCats();

	void checkBoundies(Base& obj) const;
	void returnTheAnimals();
	
	bool findErase(int index) const;
	

	void handleKillCat();
	void handleFreezeCats();
	void handleFasterMouse();
	void handleBomb();

	void updateInfo();
	void checkLevelConditions(sf::RenderWindow& window);
	void drawAll(sf::RenderWindow& window);

	Mouse* m_player;

	GameInfo* m_gameInfo;

	int m_width;
	int m_height;
	int m_numRows;
	int m_numCols;
	int m_level;
	int m_cheeseCount;
	int m_catCount;
	bool m_wonLevel;
	bool m_lostLevel;
	bool m_runOutOfTime;

	std::vector<sf::Texture> m_textures;
	std::vector<std::unique_ptr<Base>> m_movables;
	std::vector< std::unique_ptr<Base>> m_static;

	sf::Time m_deltaTime;
	sf::Time m_freezTime;
	sf::Time m_fasterTime;
	sf::Time m_hurtTime;	

	sf::Clock m_clock;
	sf::Clock m_freezeClock;
	sf::Clock m_fasterClock;
	sf::Clock m_bombClock;

	sf::RectangleShape m_background;
	sf::Sound m_sound;
};