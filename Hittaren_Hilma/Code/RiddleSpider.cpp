#include "RiddleSpider.h"

using namespace std;

RiddleSpider::RiddleSpider(ResourceHandler &handler, sf::Vector2f position) :
mPosition(position),
mState(INACTIVE),
mMoveTimer(0),
mActiveTimer(0),
mTextCounter(-1),
mTexts()
{
	mSprite.setTexture(*handler.getTexture("RiddleSpider.png"));
	mSprite.setPosition(position);
	mFont.loadFromFile("Resources/Fonts/Lora-Regular.ttf");
}

RiddleSpider::~RiddleSpider()
{

}

void RiddleSpider::update(float deltaTime)
{
	switch (mState)
	{
	case ENTERING:
		moveDown(deltaTime);
		break;

	case LEAVING:
		moveUp(deltaTime);
		break;

	case IDLE:
		idleMove(deltaTime);
		break;

	case INACTIVE:
		activeTimerTick();

		//if (mActiveTimer >= 800)
		//{
		//	setState(ENTERING);
		//}

		break;
	}

	mSprite.setPosition(mPosition);
}

void RiddleSpider::draw(sf::RenderWindow &window)
{
	window.draw(mSprite);
}

void RiddleSpider::moveUp(float deltaTime)
{
	if (mPosition.y + mSprite.getGlobalBounds().height > 0)
	{
		mPosition.y -= 100.0f * deltaTime;
	}
}

void RiddleSpider::moveDown(float deltaTime)
{
	if (mPosition.y + mSprite.getGlobalBounds().height < 150)
	{
		mPosition.y += 100.0f * deltaTime;
	}
}

void RiddleSpider::idleMove(float deltaTime)
{
	mMoveTimer++;
	if (mMoveTimer >= 300)
	{
		mMoveTimer = 0;
	}

	if (mMoveTimer <= 150)
	{
		mPosition.y += 12.5f * deltaTime;
	}
	else if (mMoveTimer >= 151)
	{
		mPosition.y -= 12.5f * deltaTime;
	}
}

void RiddleSpider::activeTimerTick()
{
	mActiveTimer++;
}

void RiddleSpider::setState(State newState)
{
	resetMoveTimer();
	resetActiveTimer();
	mState = newState;
}

RiddleSpider::State RiddleSpider::getState()
{
	return mState;
}

sf::FloatRect RiddleSpider::getRect()
{
	return mSprite.getGlobalBounds();
}

void RiddleSpider::addText(string text)
{
	mTextCounter++;
	mTexts.push_back(sf::Text());

	//Isn't needed, this is made by the DialogueSystem Component
	//mTexts[mTextCounter].setCharacterSize(18);
	//mTexts[mTextCounter].setStyle(sf::Text::Bold);
	//mTexts[mTextCounter].setColor(sf::Color::Black);
	//mTexts[mTextCounter].setFont(mFont);
}

void RiddleSpider::setText(std::string text)
{
	mText.setString(text);
}

std::string RiddleSpider::getText()
{
	return mText.getString();
}

void RiddleSpider::resetActiveTimer()
{
	mActiveTimer = 0;
}

void RiddleSpider::resetMoveTimer()
{
	mMoveTimer = 0;
}
