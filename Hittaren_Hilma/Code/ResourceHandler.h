#ifndef INCLUDED_RH
#define INCLUDED_RH

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
#include <cassert>
#include <iostream>
#include <string>

class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler();

	//Get resources via index
	sf::Texture* getTexture(int index);
	sf::SoundBuffer* getSound(int index);
	std::string getMusic(int index);

	//Get resources via name
	sf::Texture* getTexture(std::string name);
	sf::SoundBuffer* getSound(std::string name);
	std::string getMusic(std::string name);

	void loadGeneral(sf::RenderWindow &window);

	void loadLevel1(sf::RenderWindow &window);
	void loadLevel2(sf::RenderWindow &window);
	void loadLevel3(sf::RenderWindow &window);
	void loadLastLevel(sf::RenderWindow &window);

	void drawLoadScreen(sf::RenderWindow &window, std::string loadMessage);


private:
	//Clear
	void internalClear();

	//Add texture
	void addTexture(std::string fileName);
	int textureCounter;

	//Add sound
	void addSound(std::string fileName);
	int soundCounter;

	//Add music
	void addMusic(std::string fileName);
	int musicCounter;

	typedef std::vector<std::string> StringVector;

	//Texture variables
	typedef std::vector<sf::Texture*> TextureVector;
	TextureVector mTextures;
	StringVector mTextureNames;

	//Sound variables
	typedef std::vector<sf::SoundBuffer*> SoundVector;
	SoundVector mSounds;
	StringVector mSoundNames;

	//Music variables
	StringVector mMusicNames;

	//Loading Message
	sf::Font mFont;
	sf::Text mLoadMessage;

	//Loading screen
	sf::RectangleShape loadScreen;

	bool mLevel1Loaded;
	bool mLevel2Loaded;
	bool mLevel3Loaded;
	bool mLastLevelLoaded;

	sf::View mView;
};

#endif