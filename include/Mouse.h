#pragma once

#include "Animal.h"
#include <SFML/Graphics.hpp>

class Mouse : public Animal
{
public:
	Mouse(sf::Texture* aTexture);
	virtual ~Mouse() {};

	int getLife() const;
	int getCheese() const;
	int getPoints() const;
	int getKeys() const;
	float getCountDown() const;
	bool getKillCat() const;
	bool getFreezeCats() const;
	bool isFaster() const;
	float getSpeed() const;
	bool isGotBombed() const;

	void setDirection(sf::Keyboard::Key keyCode);
	void setCheese(int amount);
	void setLife(int amount, bool play);
	void setPoints(int amount);
	void setKeys(int amount);
	void setCountDown(float amount, bool play);
	void setKillCat(bool state);
	void setFreezeCats(bool state);
	void setGotBombed(bool state);
	void setSpeed(float speed);
	void setFaster(bool state);
	virtual void setColor(bool state);

	void doBomb();
	void playSound(enum Sound sound);

	virtual void handleCollision(Base& unknownObj);
	virtual void handleCollision(Mouse& theMouse) {};
	virtual void handleCollision(Wall& wall);
	virtual void handleCollision(Door& door);
	virtual void handleCollision(Key& key);
	virtual void handleCollision(Present& present);
	virtual void handleCollision(Cheese& cheese);
	virtual void handleCollision(Cat& cat);

	virtual void move(sf::Time deltaTime);

private:
	sf::Vector2f m_direction;

	int m_life;
	int m_keysCount;
	int m_cheeseCount;
	int m_points;
	bool m_killCat;
	bool m_toFreezeCats;
	bool m_isFasterState;
	bool m_isBombed;
	float m_countDown;
};