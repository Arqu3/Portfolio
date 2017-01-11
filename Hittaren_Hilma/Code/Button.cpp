#include "Button.h"

using namespace std;

//Creates a sf::rectangleshape representing a button with given color
Button::Button(float x, float y, float width, float height, sf::Color col) :
mRect(sf::Vector2f(width, height)),
mMoveToPosition(x, y),
mIsOnPosition(true),
mDirection(0, 0),
mSpeed(100),
mMode(RectangleShape)
{
	mRect.setPosition(x, y);
	mRect.setFillColor(col);
}

//Creates a sf::rectangleshape without color
Button::Button(float x, float y, float width, float height) :
mRect(sf::Vector2f(width, height)),
mMoveToPosition(x, y),
mIsOnPosition(true),
mDirection(0, 0),
mSpeed(100),
mMode(RectangleShape)
{
	mRect.setPosition(x, y);
}

Button::Button(float width, float height, sf::Color col):
mRect(sf::Vector2f(width, height)),
mIsOnPosition(true),
mDirection(0, 0),
mSpeed(100),
mMode(RectangleShape)
{
	mRect.setPosition(0, 0);
	mRect.setFillColor(col);
}

Button::Button(float width, float height) :
mRect(sf::Vector2f(width, height)),
mIsOnPosition(true),
mDirection(0, 0),
mSpeed(100),
mMode(RectangleShape)
{
	mRect.setPosition(0, 0);
}

//Creates a sf::rectangleshape representing a button with given color
Button::Button(sf::RectangleShape &rect, sf::Color col) :
mRect(rect),
mMoveToPosition(rect.getPosition().x, rect.getPosition().y),
mDirection(0, 0),
mIsOnPosition(true),
mSpeed(100),
mMode(RectangleShape)
{
	mRect.setPosition(rect.getPosition().x, rect.getPosition().y);
	mRect.setFillColor(col);
}

//Creates a sprite representing a button
Button::Button(ResourceHandler &handler, float x, float y, string textureName):
mTextureName(textureName),
mMoveToPosition(x, y),
mDirection(0, 0),
mIsOnPosition(true),
mSpeed(100),
mMode(Texture)
{
	mSprite.setTexture(*handler.getTexture(textureName));
	mSprite.setPosition(x, y);
}

//Creates a sprite representing a button
Button::Button(ResourceHandler &handler, sf::Vector2f &pos, string textureName):
mTextureName(textureName),
mMoveToPosition(pos),
mDirection(0, 0),
mIsOnPosition(true),
mSpeed(100),
mMode(Texture)
{
	mSprite.setTexture(*handler.getTexture(textureName));
	mSprite.setPosition(pos);
}

Button::Button(ResourceHandler &handler, sf::RectangleShape &rect, std::string textureName, std::string hoverName):
mTextureName(textureName),
mRect(rect),
mHoverRect(rect),
mMoveToPosition(rect.getPosition().x, rect.getPosition().y),
mDirection(0, 0),
mIsOnPosition(true),
mSpeed(100),
mMode(RectangleShape)
{
	mRect.setTexture(handler.getTexture(textureName));
	mHoverRect.setTexture(handler.getTexture(hoverName));
}

Button::~Button()
{

}

bool Button::isPressed(sf::RenderWindow &window)
{
	mPixelPos = sf::Mouse::getPosition(window);
	mWorldPos = window.mapPixelToCoords(mPixelPos);

	switch (mMode)
	{
	case RectangleShape:
		if (mRect.getGlobalBounds().contains(mWorldPos))
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	case Texture:
		if (mSprite.getGlobalBounds().contains(mWorldPos))
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
	return false;
}

void Button::setPosition(float x, float y)
{
	switch (mMode)
	{
	case RectangleShape:
		mRect.setPosition(x, y);
		mHoverRect.setPosition(x, y);
		mMoveToPosition = sf::Vector2f(x, y);
		mDirection = sf::Vector2f(0, 0);
		break;

	case Texture:
		mSprite.setPosition(x, y);
		mMoveToPosition = sf::Vector2f(x, y);
		mDirection = sf::Vector2f(0, 0);
		break;
	}
}
void Button::setPosition(sf::Vector2f &pos)
{
	switch (mMode)
	{
	case RectangleShape:
		mRect.setPosition(pos);
		mHoverRect.setPosition(pos);
		mMoveToPosition = pos;
		mDirection = sf::Vector2f(0, 0);
		break;
	case Texture:
		mSprite.setPosition(pos);
		mMoveToPosition = pos;
		mDirection = sf::Vector2f(0, 0);
		break;
	}
}

void Button::moveTo(float x, float y)
{
	float deltaX;
	float deltaY;

	float squareX;
	float squareY;

	float added;
	float root;

	sf::Vector2f unit;

	switch (mMode)
	{
	case RectangleShape:
		//Creates a unit-direction vector that the player follows
		mMoveToPosition = sf::Vector2f(x, y);

		deltaX = (mMoveToPosition.x - mRect.getPosition().x);
		deltaY = (mMoveToPosition.y - mRect.getPosition().y);

		mDirection = sf::Vector2f(deltaX, deltaY);

		squareX = (deltaX * deltaX);
		squareY = (deltaY * deltaY);

		added = (squareX + squareY);
		root = sqrt(added);

		unit = sf::Vector2f(mDirection.x / root, mDirection.y / root);
		mDirection = unit;
		break;

	case Texture:
		//Creates a unit-direction vector that the player follows
		mMoveToPosition = sf::Vector2f(x, y);

		deltaX = (mMoveToPosition.x - mSprite.getPosition().x);
		deltaY = (mMoveToPosition.y - mSprite.getPosition().y);

		mDirection = sf::Vector2f(deltaX, deltaY);

		squareX = (deltaX * deltaX);
		squareY = (deltaY * deltaY);

		added = (squareX + squareY);
		root = sqrt(added);

		unit = sf::Vector2f(mDirection.x / root, mDirection.y / root);
		mDirection = unit;
		break;
	}
}
void Button::moveTo(sf::Vector2f &pos)
{
	float deltaX;
	float deltaY;

	float squareX;
	float squareY;

	float added;
	float root;

	sf::Vector2f unit;

	switch (mMode)
	{
	case RectangleShape:
		//Creates a unit-direction vector that the player follows
		mMoveToPosition = pos;

		deltaX = (mMoveToPosition.x - mRect.getPosition().x);
		deltaY = (mMoveToPosition.y - mRect.getPosition().y);

		mDirection = sf::Vector2f(deltaX, deltaY);

		squareX = (deltaX * deltaX);
		squareY = (deltaY * deltaY);

		added = (squareX + squareY);
		root = sqrt(added);

		unit = sf::Vector2f(mDirection.x / root, mDirection.y / root);
		mDirection = unit;
		break;

	case Texture:
		//Creates a unit-direction vector that the player follows
		mMoveToPosition = pos;

		deltaX = (mMoveToPosition.x - mSprite.getPosition().x);
		deltaY = (mMoveToPosition.y - mSprite.getPosition().y);

		mDirection = sf::Vector2f(deltaX, deltaY);

		squareX = (deltaX * deltaX);
		squareY = (deltaY * deltaY);

		added = (squareX + squareY);
		root = sqrt(added);

		unit = sf::Vector2f(mDirection.x / root, mDirection.y / root);
		mDirection = unit;
		break;
	}
}

void Button::move(float deltaTime)
{
	sf::FloatRect mMoveToRect;
	switch (mMode)
	{
	case RectangleShape:
		mMoveToRect = sf::FloatRect(mMoveToPosition.x, mMoveToPosition.y, 10, 10);

		if (mRect.getGlobalBounds().intersects(mMoveToRect))
		{
			mIsOnPosition = true;
		}
		else
		{
			mIsOnPosition = false;
		}

		if (mIsOnPosition == false)
		{
			mSetPos += mDirection * mSpeed * deltaTime;
			mRect.setPosition(mSetPos);
			mHoverRect.setPosition(mSetPos);
		}
		break;

	case Texture:
		mMoveToRect = sf::FloatRect(mMoveToPosition.x, mMoveToPosition.y, 10, 10);

		if (mSprite.getGlobalBounds().intersects(mMoveToRect))
		{
			mIsOnPosition = true;
		}
		else
		{
			mIsOnPosition = false;
		}

		if (mIsOnPosition == false)
		{
			mSetPos += mDirection * mSpeed * deltaTime;
			mSprite.setPosition(mSetPos);
		}
		break;
	}
}

void Button::update(float deltaTime)
{
	move(deltaTime);
}
void Button::draw(sf::RenderWindow &window)
{
	switch (mMode)
	{
	case RectangleShape:
		window.draw(mRect);
		if (isPressed(window))
		{
			window.draw(mHoverRect);
		}
		break;

	case Texture:
		window.draw(mSprite);
		break;
	}
}

sf::FloatRect Button::getRect()
{
	switch (mMode)
	{
	case RectangleShape:
		return mRect.getGlobalBounds();
		break;

	case Texture:
		return mSprite.getGlobalBounds();
		break;
	}
	return sf::FloatRect();
}

std::string Button::getTexureName()
{
	switch (mMode)
	{
	case RectangleShape:
		return "NULL";
		break;

	case Texture:
		return mTextureName;
		break;
	}
	return "NULL";
}
void Button::setSpeed(float value)
{
	mSpeed = value;
}

sf::Sprite Button::getSprite()
{
	switch (mMode)
	{
	case RectangleShape:
		return sf::Sprite();
		break;

	case Texture:
		return mSprite;
		break;
	}
	return sf::Sprite();
}