#include "Controller.h"
#include <cstdlib>
#include "GameInfo.h"
#include "KillCat.h"
#include "Frozen.h"
#include "Bomb.h"
#include "Faster.h"

Controller::Controller(const std::vector<std::string>& file, int level, GameInfo& myInfo)
{
	srand(time(NULL));
	m_background.setTexture(&(Singleton::instance().getObjTexture(0)));
	m_cheeseCount = m_catCount = 0;
	prepLevel(file);
	m_level = level;
	m_wonLevel = m_lostLevel = m_runOutOfTime = false;
	m_gameInfo = &myInfo;

	m_player->setPoints(m_gameInfo->getPlayerPoints());
	m_player->setLife(m_gameInfo->getPlayerLife(), false);
}

void Controller::prepLevel(const std::vector<std::string>& file)
{
	if (!file.empty())
	{
		m_numRows = (int)file.size();
		m_numCols = (int)file[0].size();
	}
	else
	{
		exit(EXIT_FAILURE);
	}

	m_width = (DESIRED_SIZE * m_numCols);
	m_height = (DESIRED_SIZE * m_numRows);

	m_background.setSize(sf::Vector2f(1.75*m_width, m_height));
	
	m_movables.push_back(std::make_unique<Mouse>(&(Singleton::instance().getObjTexture(3))));
	for (int row = 0; row < file.size(); row++)
	{
		for (int col = 0; col < file[row].size(); col++)
		{
			assignObj(file[row][col], row, col);
		}
	}

	m_deltaTime = m_clock.restart();

	m_player->setCountDown(COUNT_DOWND, false);
}

void Controller::assignObj(const char objSymbol, int row, int col)
{
	int presentKind = (rand() % NUM_OF_PRESENTS);
	switch (objSymbol)
	{
	case WALL:
		m_static.push_back(std::make_unique<Wall>(&(Singleton::instance().getObjTexture(1))));
		m_static.back()->setDrawSettings(row, col);
		break;
	case CAT:
		m_movables.push_back(std::make_unique<Cat>(&(Singleton::instance().getObjTexture(4))));
		m_movables.back()->setDrawSettings(row, col);
		m_catCount++;
		break;
	case MOUSE:
		static_cast<Mouse*>(m_movables[0].get())->setDrawSettings(row, col);
		m_player = static_cast<Mouse*>(m_movables[0].get());
		m_player->setStartLocation();
		break;
	case PRESENT:
		assignPresent(presentKind);
		m_static.back()->setDrawSettings(row, col);
		break;
	case CHEESE:
		m_static.push_back(std::make_unique<Cheese>(&(Singleton::instance().getObjTexture(2))));
		m_static.back()->setDrawSettings(row, col);
		m_cheeseCount++;
		break;
	case KEY:
		m_static.push_back(std::make_unique<Key>(&(Singleton::instance().getObjTexture(6))));
		m_static.back()->setDrawSettings(row, col);
		break;
	case DOOR:
		m_static.push_back(std::make_unique<Door>(&(Singleton::instance().getObjTexture(5))));
		m_static.back()->setDrawSettings(row, col);
		break;
	}
}

void Controller::assignPresent(int presentKind)
{
	switch (presentKind)
	{
	case 0:
		m_static.push_back(std::make_unique<Frozen>(&(Singleton::instance().getObjTexture(presentKind + 7))));
		break;
	case 1:
		m_static.push_back(std::make_unique<KillCat>(&(Singleton::instance().getObjTexture(presentKind + 7))));
		break;
	case 2:
		m_static.push_back(std::make_unique<Clock>(&(Singleton::instance().getObjTexture(presentKind + 7))));
		break;
	case 3:
		m_static.push_back(std::make_unique<Heart>(&(Singleton::instance().getObjTexture(presentKind + 7))));
		break;
	case 4:
		m_static.push_back(std::make_unique<Bomb>(&(Singleton::instance().getObjTexture(presentKind + 7))));
		break;
	case 5:
		m_static.push_back(std::make_unique<Faster>(&(Singleton::instance().getObjTexture(presentKind + 7))));
		break;
	}
}

void Controller::run(sf::RenderWindow &window)
{
	window.create(sf::VideoMode(1.25 * m_width, m_height), "The Game");

	m_clock.restart();
	m_freezeClock.restart();

	while (window.isOpen())
	{
		checkLevelConditions(window);

		m_deltaTime = m_clock.restart();
		window.clear();
		drawAll(window);
		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_gameInfo->setPlayerLife(0);
				window.close();
				break;
			}
		}

		handleKeyPressed(event.key.code, m_deltaTime);
		handleCollisions();
		handleBoard();

		if (!m_player->getFreezeCats())
		{
			moveCats();
		}
	}
}

void Controller::checkLevelConditions(sf::RenderWindow& window)
{
	if (m_wonLevel)
	{
		m_player->setPoints(25 + 5 * m_catCount);
		updateInfo();

		m_gameInfo->youLoseWin(window, true);

		window.display();
		sf::sleep(sf::seconds(4));
		window.close();
	}
	else if (m_lostLevel || m_runOutOfTime)
	{
		m_gameInfo->setTimeOut(true);

		if (m_lostLevel)
		{
			updateInfo();
		}
		else
		{
			m_player->setLife(-1, false);
			m_gameInfo->setPlayerLife(m_player->getLife());
		}

		m_sound.setBuffer(Singleton::instance().getSoundBuffer(GAME_OVER));
		m_sound.play();

		m_gameInfo->youLoseWin(window, false);

		window.display();
		sf::sleep(sf::seconds(4));
		window.close();
	}
}

void Controller::handleKeyPressed(sf::Keyboard::Key keyCode, sf::Time deltaTime)
{
	m_player->setDirection(keyCode);
	m_player->move(deltaTime);
}

void Controller::handleCollisions()
{
	checkBoundies(*m_player);
	auto collided = false;
	for (int i = 1; i < m_movables.size(); i++)
	{
		if (m_player->checkCollision(*m_movables[i]))
		{
			m_player->handleCollision(*m_movables[i]);
			collided = true;
		}
	}

	if (collided)
	{
		returnTheAnimals();
		return;
	}

	for (int i = 0; i < m_static.size(); i++)
	{
		for (int j = 1; j < m_movables.size(); j++)
		{
			if (m_movables[j]->checkCollision(*m_static[i]))
			{
				m_movables[j]->handleCollision(*m_static[i]);
			}
		}
	}

	for (int i = 2; i < m_movables.size(); i++)
	{
		for (int j = 1; j < m_movables.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			if (m_movables[j]->checkCollision(*m_movables[i]))
			{
				m_movables[j]->handleCollision(*m_movables[i]);
			}
		}
	}
}

void Controller::handleBoard()
{
	auto eraseObj = false;
	int eraseIndex;

	for (int i = 0; i < m_static.size(); i++)
	{
		if (m_player->checkCollision(*m_static[i]))
		{
			m_player->handleCollision(*m_static[i]);

			if (findErase(i))
			{
				eraseObj = true;
				eraseIndex = i;
				break;
			}
			else if (dynamic_cast<Door*>(m_static[i].get()))
			{
				if (m_player->getKeys() > 0)
				{
					m_player->setKeys(-1);
					eraseObj = true;
					eraseIndex = i;
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	if (m_player->getLife() <= 0)
	{
		m_lostLevel = true;
	}

	handleKillCat();
	handleFreezeCats();
	handleFasterMouse();
	handleBomb();

	if (eraseObj)
	{
		m_static.erase(m_static.begin() + eraseIndex);
	}
	if (m_player->getCheese() >= m_cheeseCount)
	{
		m_wonLevel = true;
	}
}

void Controller::moveCats()
{
	for (int i = 1; i < m_movables.size(); i++)
	{
		if (!(dynamic_cast<Cat*>(m_movables[i].get())->getCrazy()))
		{
			dynamic_cast<Cat*>(m_movables[i].get())->setDestination(m_player->getLocation());
		}

		dynamic_cast<Cat*>(m_movables[i].get())->move(m_deltaTime);
		checkBoundies(*m_movables[i]);
	}
}

void Controller::checkBoundies(Base& obj) const
{
	if (obj.getLocation().x >= m_width - 15 ||
		obj.getLocation().y >= m_height - 15 ||
		obj.getLocation().x <= 15 ||
		obj.getLocation().y <= 15)
	{
		obj.setLocation(obj.getOldLocation());

		if (dynamic_cast<Cat*>(&obj))
		{
			static_cast<Cat*>(&obj)->setCrazy();
		}		
	}
}

void Controller::returnTheAnimals()
{
	for (int i = 0; i < m_movables.size(); i++)
	{
		//need twice because we need to reset the old location too
		m_movables[i]->setLocation(m_movables[i]->getStartLocation());
		m_movables[i]->setLocation(m_movables[i]->getStartLocation());
	}
}

bool Controller::findErase(int index) const
{
	return (dynamic_cast<Cheese*>(m_static[index].get()) ||
			dynamic_cast<Heart*>(m_static[index].get()) ||
			dynamic_cast<Frozen*>(m_static[index].get()) ||
			dynamic_cast<Clock*>(m_static[index].get()) ||
			dynamic_cast<KillCat*>(m_static[index].get()) ||
			dynamic_cast<Bomb*>(m_static[index].get()) ||
			dynamic_cast<Faster*>(m_static[index].get()) ||
			dynamic_cast<Key*>(m_static[index].get()));
}

void Controller::handleKillCat()
{
	if (m_player->getKillCat())
	{
		m_player->setKillCat(false);

		if (m_movables.size() > 1)
		{
			int killIndex = (rand() % (m_movables.size() - 1) + 1);
			m_movables.erase(m_movables.begin() + killIndex);
		}
	}
}

void Controller::handleFreezeCats()
{
	static float freeze = 5;

	for (int i = 1; i < m_movables.size(); i++)
	{
		static_cast<Cat*>(m_movables[i].get())->setColor(m_player->getFreezeCats());
	}

	if (!m_player->getFreezeCats())
	{
		freeze = 5;
		m_freezeClock.restart();
		return;
	}

	m_freezTime = m_freezeClock.restart();

	freeze -= m_freezTime.asSeconds();

	if (freeze <= 0)
	{
		m_player->setFreezeCats(false);
	}
}

void Controller::handleFasterMouse()
{
	static float faster = 5;

	if (!m_player->isFaster())
	{
		faster = 5;
		m_fasterClock.restart();
		return;
	}

	m_fasterTime = m_fasterClock.restart();
	faster -= m_fasterTime.asSeconds();

	if (faster <= 0)
	{
		m_player->setFaster(false);
		m_player->setSpeed(MOUSE_SPEED);
	}
}

void Controller::handleBomb()
{
	static float bomb = 1;

	m_player->setColor(m_player->isGotBombed());

	if (!m_player->isGotBombed())
	{
		bomb = 1;
		m_bombClock.restart();
		return;
	}

	m_hurtTime = m_bombClock.restart();
	bomb -= m_hurtTime.asSeconds();

	if (bomb <= 0)
	{
		m_player->setGotBombed(false);
	}
}

void Controller::updateInfo()
{
	m_gameInfo->setPlayerPoints(m_player->getPoints());
	m_gameInfo->setPlayerLife(m_player->getLife());
}

void Controller::drawAll(sf::RenderWindow& window)
{
	m_player->setCountDown(-m_deltaTime.asSeconds(), false);

	window.draw(m_background);

	for (int i = 0; i < m_static.size(); i++)
	{
		m_static[i]->drawObj(window);
	}

	for (int i = 1; i < m_movables.size(); i++)
	{
		m_movables[i]->drawObj(window);
	}

	m_movables[0]->drawObj(window);

	m_gameInfo->displayInfo(window, m_player->getCountDown(), m_player->getLife(), 
							m_player->getCheese(), m_player->getPoints(), 
							m_player->getKeys(), m_level);

	if (m_player->getCountDown() <= 0)
	{
		m_runOutOfTime = true;
	}
}