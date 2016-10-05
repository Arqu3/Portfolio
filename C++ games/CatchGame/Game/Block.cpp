#include "Block.h"

using namespace std;

Block::Block(sf::Vector2f &position, sf::FloatRect &rectangle) :
mPosition(position),
mRectangle(rectangle),
mHealth(1),
mScore(1),
mSpeed(275),
mIsAlive(true),
mDamage(1)
{
	if (!mTexture.loadFromFile("BlockTexture1.png"))
	{
		cout << "Could not load Block1 texture" << endl;
	}
	mSprite.setTexture(mTexture);
	mSprite.setColor(sf::Color::Green);
}

Block::~Block()
{

}

void Block::update(float deltaTime)
{
	move(deltaTime);

	//Fix position X if spawned outside screen
	if (mPosition.x > 800 - mRectangle.width)
	{
		mPosition.x = 800 - mRectangle.width;
	}
}

void Block::draw(sf::RenderWindow &window)
{
	window.draw(mSprite);
	mSprite.setPosition(mPosition);
}

void Block::move(float deltaTime)
{
	mPosition.y += mSpeed * deltaTime;

	mRectangle.height = mSprite.getGlobalBounds().height;
	mRectangle.width = mSprite.getGlobalBounds().width;

	mRectangle.left = mPosition.x;
	mRectangle.top = mPosition.y;
}

bool Block::isAlive()
{
	return mIsAlive;
}

void Block::setDead()
{
	mIsAlive = false;
}

sf::Vector2f Block::getPosition()
{
	return mPosition;
}

sf::FloatRect Block::getRectangle()
{
	return mRectangle;
}

int Block::getScore()
{
	return mScore;
}

int Block::getDamage()
{
	return mDamage;
}

sf::Sprite Block::getSprite()
{
	return mSprite;
}

float Block::getSpeed()
{
	return mSpeed;
}

float Block::setSpeed(float value)
{
	return mSpeed = value;
}