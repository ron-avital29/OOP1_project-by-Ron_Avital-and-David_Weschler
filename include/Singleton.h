#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>

enum ClickKind {NEWGAME, 
                EXIT, 
                SOUNDON, 
                HELP, 
                SOUNDOFF};


enum  Objects {SPACE = ' ',
               WALL = '#',
               CHEESE = '*',
               MOUSE = '%',
               CAT = '^',
               DOOR = 'D',
               KEY = 'F',
               PRESENT = '$'};

enum Sound {FASTER, 
            GAME_OVER, 
            CHEESE_SOUND, 
            KILL_CAT, 
            FREEZE_SOUND, 
            DOOR_SOUND, 
            DIE_SOUND,  
            CLOCK_SOUND, 
            KEY_SOUND, 
            EXTRA_LIFE, 
            BOMB, 
            PASSLEVEL,
            CAT_SOUND};

const int BUTTONS = 5;
const int NUM_OF_LEVELS = 5;
const int NUM_OF_BUTTONS = 4;
const int NUM_OF_PRESENTS = 6;
const int VOLUME = 25;
const int LIFE = 3;
const float DESIRED_SIZE = 30.f;
const float MOUSE_SPEED = 160.f;
const float COUNT_DOWND = 120.f;

class Singleton
{
public:
    ~Singleton() = default;
	static Singleton& instance();
        
    sf::Texture& getMenuBackround();
    sf::Texture& getGamePlay();
    sf::Texture& getButtonTextures(int num);
    sf::Texture& getEnd(int num);
    sf::Music& getMusic();
	sf::Texture& getObjTexture(int num);
	sf::SoundBuffer& getSoundBuffer(int num);
    sf::Font& getFont();

	void LoadFromFile();

private:
    Singleton();
	Singleton(const Singleton&) = delete;
	Singleton operator=(const Singleton&) = delete;

    std::vector<sf::Texture> m_buttonTextures;
    std::vector<std::string> m_buttonNames = {"NewGame.png",
                                              "Exit.png",
                                              "VolumeOn.png",
                                              "Help.png",
                                              "VolumeOff.png"};

    sf::Texture m_gamePlay;
    sf::Texture m_menuBackround;
	sf::Music m_music;

	std::vector<sf::Texture> m_objTextures;
    std::vector<std::string> m_objNames = {"Grass.png",
                                           "Wall.png",
                                           "Cheese.png",
                                           "Mouse.png",
                                           "Cat.png",
                                           "Door.png",
                                           "Key.png",
                                           "Freeze.png",
                                           "KillCat.png",
                                           "Clock.png", 
                                           "Heart.png",
                                           "Bomb.png",
                                           "Faster.png"};	

    sf::Font m_font;

    std::vector<sf::SoundBuffer> m_buffSounds;  
    std::vector<std::string> m_soundNames = {"Faster.ogg",
                                             "GameOver.ogg",
                                             "Eat.ogg",
                                             "KillCatSound.ogg",
                                             "FreezeSound.ogg",
                                             "UnlockSound.ogg",
                                             "DieSound.ogg", 
                                             "ClockSound.ogg",
                                             "KeySound.ogg",
                                             "LifeSound.ogg",
                                             "BombSound.ogg",
                                             "Passlevel.ogg",
                                             "CatSound.ogg"};

	std::vector<sf::Texture> m_endTextures;
    std::vector<std::string> m_endNames = {"Loser.png",
                                           "Winner.jpg"};
};