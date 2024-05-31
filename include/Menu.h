#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <fstream>
#include "Singleton.h"
#include "Button.h"
#include "Controller.h"

class Menu
{
public:
	Menu();
	void run();

private:
	void setButtons();
	void handleChoice(const sf::Event::MouseButtonEvent& event);
	void setSound();
	void gamePlayGuide();
	void startNewGame();
	void loadFromFile(std::vector<std::string>& levelBoard, std::string filename);
	void drawAll();

	sf::RenderWindow m_window;
	sf::Sprite m_spBackround;
	sf::Sprite m_gamePlay;
	Singleton& m_assets = Singleton::instance();
	std::vector<Button> m_buttons;
    GameInfo m_gameInfo;
	bool m_musicIsplaying;
};