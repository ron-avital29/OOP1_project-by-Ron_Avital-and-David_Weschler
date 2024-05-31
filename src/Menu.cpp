#include <iostream>
#include "Menu.h"

Menu::Menu()
	: m_musicIsplaying(true)
{
	m_spBackround.setTexture(m_assets.getMenuBackround());
	m_gamePlay.setTexture(m_assets.getGamePlay());
	setButtons();
}

void Menu::setButtons()
{
	float X[] = { 375, 825, 375, 825 };
	float Y[] = { 375, 375, 640, 640 };

	for (int i = 0; i < NUM_OF_BUTTONS; i++)
	{
		m_buttons.push_back(Button(sf::Vector2f(X[i], Y[i]), i, &m_assets.getButtonTextures(i)));
	}
}

void Menu::run()
{
	m_window.create(sf::VideoMode(1200, 900), "The best game in the werld");

	if (m_musicIsplaying)
	{
		m_assets.getMusic().setLoop(true);
		m_assets.getMusic().setVolume(VOLUME);
		m_assets.getMusic().play();
	}

	while (m_window.isOpen())
	{
		m_window.clear();
		drawAll();
		m_window.display();

		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonPressed:
				handleChoice(event.mouseButton);
				break;
			}
		}

		//Enlarge buttons
		for (int i = 0; i < NUM_OF_BUTTONS; i++)
		{
			(m_buttons[i].getGlobalBound().contains(sf::Mouse::getPosition(m_window).x, 
													sf::Mouse::getPosition(m_window).y)) ?
													m_buttons[i].setScale(1.1f, 1.1f) : 
													m_buttons[i].setScale(1.0f, 1.0f);
		}
	}
}

void Menu::handleChoice(const sf::Event::MouseButtonEvent& event)
{
	for (int i = 0; i < NUM_OF_BUTTONS; i++)
	{
		if (m_buttons[i].getGlobalBound().contains(event.x, event.y))
		{
			switch (i)
			{
			case EXIT:
				m_window.close();
				break;
			case NEWGAME:
				startNewGame();
				run();
				break;
			case SOUNDON:
				setSound();
				break;
			case HELP:
				gamePlayGuide();
				break;
			}
		}
	}
}

void Menu::gamePlayGuide()
{
	sf::RenderWindow window(sf::VideoMode(1200, 694), "How To Play");

	while (window.isOpen())
	{
        window.clear();
		window.draw(m_gamePlay);
        window.display();

        sf::Event event;
        while (window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
			}
		}
	}
}

void Menu::startNewGame()
{
	auto playlist = std::ifstream("playlist.txt");
	auto level = std::string();
	auto theLevel = 0;

	m_gameInfo.setPlayerLife(LIFE);
	m_gameInfo.setPlayerPoints(0);
	m_gameInfo.setTimeOut(false);

	if (!playlist.is_open())
	{
		std::cerr << "Error opening the file" << std::endl;
		exit(EXIT_FAILURE);
	}	

	while (std::getline(playlist, level))
	{
		std::vector<std::string> levelBoard;

		loadFromFile(levelBoard, level);

		if (levelBoard.empty())
		{
			exit(EXIT_FAILURE);
		}

		Controller newGame(levelBoard, ++theLevel, m_gameInfo);
		newGame.run(m_window);

		if (m_gameInfo.getPlayerLife() <= 0) 
		{ 
			return; 
		}

		while (m_gameInfo.getTimeOut())
		{			
			m_gameInfo.setTimeOut(false);
			Controller newGame(levelBoard, theLevel, m_gameInfo);
			newGame.run(m_window);

			if (m_gameInfo.getPlayerLife() <= 0)
			{
				return;
			}
		}		
	}	
}

void Menu::loadFromFile(std::vector<std::string> &levelBoard, std::string filename)
{
	auto line = std::string();
	auto file = std::ifstream(filename);

	if (!file.is_open())
	{
		std::cerr << "Error opening the file." << std::endl;
		exit(EXIT_FAILURE);
	}

	while (std::getline(file, line))
	{
		levelBoard.push_back(line);
	}
	
	if (levelBoard.size() <= 0)
	{
		std::cout << "level is empty\n";
		return;
	}
}

void Menu::setSound()
{
	if (m_musicIsplaying)
	{
		m_assets.getMusic().pause();
		m_buttons[2].setTexture(&m_assets.getButtonTextures(SOUNDOFF));
	}
	else
	{
		m_assets.getMusic().play();
		m_buttons[2].setTexture(&m_assets.getButtonTextures(SOUNDON));
	}
	m_musicIsplaying = !m_musicIsplaying;
}

void Menu::drawAll()
{
	m_spBackround.setScale((float)(1200) / m_assets.getMenuBackround().getSize().x,
							(float)(900) / m_assets.getMenuBackround().getSize().y);

	m_window.draw(m_spBackround);

	for (int i = 0; i < NUM_OF_BUTTONS; i++)
	{
		m_buttons[i].drawButton(m_window);
	}
}