#include "Singleton.h"
#include <iostream>

Singleton::Singleton()
{
	LoadFromFile();
}

sf::Texture& Singleton::getMenuBackround()
{
	return m_menuBackround;
}

sf::Texture& Singleton::getGamePlay()
{
	return m_gamePlay;
}

sf::Texture& Singleton::getButtonTextures(int num)
{
	return m_buttonTextures[num];
}

sf::Music& Singleton::getMusic()
{
	return m_music;
}

sf::Texture& Singleton::getObjTexture(int num)
{
	return m_objTextures[num];
}

sf::Texture& Singleton::getEnd(int num)
{
	return m_endTextures[num];
}


sf::SoundBuffer& Singleton::getSoundBuffer(int num)
{
	return m_buffSounds[num];
}

sf::Font& Singleton::getFont()
{
	return m_font;
}

Singleton& Singleton::instance()
{
	static Singleton Singleton;
	return Singleton;
}

void Singleton::LoadFromFile()
{
	//load button textures
	for (int num = NEWGAME; num <= SOUNDOFF; num++)
	{
		m_buttonTextures.push_back(sf::Texture());
		if (!(m_buttonTextures[num].loadFromFile(m_buttonNames[num])))
		{
			std::cerr << "cannot load textures\n";
			exit(EXIT_FAILURE);
		}
	}

	//load backround and help
	if (!(m_menuBackround.loadFromFile("MenuBackround.png")) ||
		!(m_gamePlay.loadFromFile("GamePlay.png")))
	{
		std::cerr << "cannot load graphic\n";
		exit(EXIT_FAILURE);
	}

	//load music
	if (!(m_music.openFromFile("music.ogg")))
	{
		std::cerr << "cannot load music\n";
		exit(EXIT_FAILURE);
	}


	//load objects
	for (int num = 0; num < 13; num++)
	{
		m_objTextures.push_back(sf::Texture());
		if (!(m_objTextures[num].loadFromFile(m_objNames[num])))
		{
			std::cerr << "cannot load objects textures\n";
			exit(EXIT_FAILURE);
		}
	}

	//load sounds
	for (int num = FASTER; num <= CAT_SOUND; num++)
	{
		m_buffSounds.push_back(sf::SoundBuffer());
		if (!(m_buffSounds[num].loadFromFile(m_soundNames[num])))
		{
			std::cerr << "cannot load sounds\n";
			exit(EXIT_FAILURE);
		}		
	}
	
	//load font
	if (!m_font.loadFromFile("infofont.ttf"))
	{
		std::cerr << "cannot load font\n";
		exit(EXIT_FAILURE);
	}

	//load end level textures
	for (int num = 0; num < 2; num++)
	{
		m_endTextures.push_back(sf::Texture());
		if (!(m_endTextures[num].loadFromFile(m_endNames[num])))
		{
			std::cerr << "cannot load textures\n";
			exit(EXIT_FAILURE);
		}
	}
}