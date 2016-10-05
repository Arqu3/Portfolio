#ifndef INCLUDED_BUTTON
#define INCLUDED_BUTTON

#include "ResourceHandler.h"

class Button
{
public:
	Button(float x, float y, float width, float height, sf::Color col);
	Button(float x, float y, float width, float height);
	Button(float width, float height, sf::Color col);
	Button(float width, float height);
	Button(sf::RectangleShape &rect, sf::Color col);
	Button(ResourceHandler &handler, float x, float y, std::string textureName);
	Button(ResourceHandler &handler, sf::Vector2f &pos, std::string textureName);
	Button(ResourceHandler &handler, sf::RectangleShape &rect, std::string textureName, std::string hoverName);
	~Button();

	bool isPressed(sf::RenderWindow &window);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f &pos);

	void moveTo(float x, float y);
	void moveTo(sf::Vector2f &pos);
	
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);

	sf::FloatRect getRect();
	std::string getTexureName();
	sf::Sprite getSprite();
	void setSpeed(float value);

private:
	//Variables
	sf::RectangleShape mRect;
	sf::RectangleShape mHoverRect;
	sf::FloatRect mFRect;
	sf::Vector2f mMoveToPosition;
	sf::Vector2f mDirection;
	sf::Vector2f mSetPos;
	bool mIsOnPosition;
	float mSpeed;
	sf::Sprite mSprite;
	std::string mTextureName;
	sf::Vector2i mPixelPos;
	sf::Vector2f mWorldPos;

	enum Mode
	{
		RectangleShape,
		Texture
	};
	Mode mMode;

	//Functions
	void move(float deltaTime);
};

#endif