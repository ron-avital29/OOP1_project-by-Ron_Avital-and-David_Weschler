#include "Mouse.h"
#include "Present.h"
#include "Heart.h"

Mouse::Mouse(sf::Texture* aTexture)
	: Animal(aTexture)
{
	m_life = m_keysCount = m_cheeseCount = m_points = m_direction.x = m_direction.y = m_countDown = 0;
	m_killCat = m_toFreezeCats = m_isFasterState = m_isBombed= false;
	m_speed = MOUSE_SPEED;
}

int Mouse::getLife() const
{
	return m_life;
}

int Mouse::getCheese() const
{
	return m_cheeseCount;
}

int Mouse::getPoints() const
{
	return m_points;
}

int Mouse::getKeys() const
{
	return m_keysCount;
}

float Mouse::getCountDown() const
{
	return m_countDown;
}

bool Mouse::getKillCat() const
{
	return m_killCat;
}

bool Mouse::getFreezeCats() const
{
	return m_toFreezeCats;
}

bool Mouse::isFaster() const
{
	return m_isFasterState;
}

float Mouse::getSpeed() const
{
	return m_speed;
}

bool Mouse::isGotBombed() const
{
	return m_isBombed;
}

void Mouse::setDirection(sf::Keyboard::Key keyCode)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || 
		(sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
	{
		m_direction = sf::Vector2f(0, -1);
		m_sprite.setRotation(-90);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || 
			 (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		m_direction = sf::Vector2f(0, 1);
		m_sprite.setRotation(90);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
			 (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		m_direction = sf::Vector2f(-1, 0);
		m_sprite.setRotation(180);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || 
			 (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		m_direction = sf::Vector2f(1, 0);
		m_sprite.setRotation(0);
	}
	else
	{
		m_direction = sf::Vector2f(0, 0);
	}
}

void Mouse::setCheese(int amount)
{
	m_cheeseCount += amount;
}

void Mouse::setLife(int amount, bool play)
{
	if (play)
	{
		playSound(EXTRA_LIFE);
	}
	m_life += amount;
}

void Mouse::setPoints(int amount)
{
	m_points += amount;
}

void Mouse::setKeys(int amount)
{
	m_keysCount += amount;
}

void Mouse::setCountDown(float amount, bool play)
{
	if (play)
	{
		playSound(CLOCK_SOUND);
	}
	m_countDown += amount;
}

void Mouse::setKillCat(bool state)
{
	if (state)
	{
		playSound(KILL_CAT);
	}
	m_killCat = state;
}

void Mouse::setFreezeCats(bool state)
{
	if (state)
	{
		playSound(FREEZE_SOUND);
	}
	m_toFreezeCats = state;
}

void Mouse::setGotBombed(bool state)
{
	m_isBombed = state;
}

void Mouse::setSpeed(float speed)
{
	if (speed > MOUSE_SPEED)
	{
		playSound(FASTER);
	}
	m_speed = speed;
}

void Mouse::setFaster(bool state)
{
	m_isFasterState = state;
}

void Mouse::setColor(bool state)
{
	m_sprite.setColor((state) ? sf::Color(255, 51, 51) : sf::Color(255, 255, 255));
}

void Mouse::doBomb()
{
	playSound(BOMB);

	m_life--;
}

void Mouse::playSound(enum Sound sound)
{
	m_sound.setBuffer(Singleton::instance().getSoundBuffer(sound));
	m_sound.play();
}

void Mouse::handleCollision(Base& unknownObj)
{
	unknownObj.handleCollision(*this);
}

void Mouse::handleCollision(Wall& wall)
{
	m_location = m_oldLocation;
	m_sprite.move(m_location);
}

void Mouse::handleCollision(Door& door)
{
	if (m_keysCount <= 0)
	{
		m_location = m_oldLocation;
		m_sprite.move(m_location);
	}
	else
	{
		m_points += 2;
		playSound(DOOR_SOUND);
	}
}

void Mouse::handleCollision(Key& key)
{
	m_keysCount++;
	playSound(KEY_SOUND);
}

void Mouse::handleCollision(Present& present)
{
	present.handlePresent(*this);
}

void Mouse::handleCollision(Cheese& cheese)
{
	playSound(CHEESE_SOUND);
	m_cheeseCount++;
	m_points += 10;
}

void Mouse::handleCollision(Cat& cat)
{
	playSound(DIE_SOUND);
	m_life--;
}

void Mouse::move(sf::Time deltaTime)
{
	m_sprite.move(m_direction * m_speed * deltaTime.asSeconds());
	setLocation(m_sprite.getPosition());
}