#ifndef INCLUDED_RS
#define INCLUDED_RS

#include "ResourceHandler.h"

class RiddleSpider
{
public:
	RiddleSpider(ResourceHandler &handler, sf::Vector2f position);
	~RiddleSpider();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);

	enum State
	{
		ENTERING,
		LEAVING,
		DIALOGUE,
		IDLE,
		INACTIVE
	};

	void setState(State newState);
	State getState();
	sf::FloatRect getRect();
	void addText(std::string text);
	void setText(std::string text);
	std::string getText();
	void resetActiveTimer();
	void resetMoveTimer();

private:
	State mState;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	float mMoveTimer;
	float mActiveTimer;
	int mTextCounter;
	sf::Font mFont;
	sf::Text mText;

	typedef std::vector<sf::Text> TextVector;
	TextVector mTexts;

	void moveUp(float deltaTime);
	void moveDown(float deltaTime);
	void idleMove(float deltaTime);
	void activeTimerTick();
};

#endif