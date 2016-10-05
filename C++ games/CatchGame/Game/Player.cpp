#include "Player.h"

using namespace std;

Player::Player(sf::Vector2f &position, sf::FloatRect &rectangle) :
mPosition(position),
mRectangle(rectangle),
mIsAlive(true),
mScore(0),
mHealth(10),
mDamage(0)
{
	if (!mTexture.loadFromFile("PlayerTexture.png"))
	{
		cout << "Could not load player texture" << endl;
	}
	mSprite.setTexture(mTexture);

	if (!mFont.loadFromFile("Arimo-Regular.ttf"))
	{
		cout << "Could not load player font" << endl;
	}
	mSText.setFont(mFont);
	mHText.setFont(mFont);
}

Player::~Player()
{

}

void Player::update(float deltaTime)
{
	updateRectangle();
	aliveCheck();
}

void Player::updateMouse(sf::RenderWindow &window)
{
	//Restrict mouse to current window
	if (mMouse.getPosition(window).x < 0)
	{
		mMouse.setPosition(sf::Vector2i(1, mPosition.y), window);
	}

	if (mMouse.getPosition(window).x > 800 - mSprite.getGlobalBounds().width)
	{
		mMouse.setPosition(sf::Vector2i(800 - mSprite.getGlobalBounds().width - 1, mPosition.y), window);
	}

	if (mMouse.getPosition(window).y > 550)
	{
		mMouse.setPosition(sf::Vector2i(mPosition.x, 549), window);
	}

	if (mMouse.getPosition(window).y < 10)
	{
		mMouse.setPosition(sf::Vector2i(mPosition.x, 11), window);
	}

	//Set player X position to mouse position X
	mPosition.x = mMouse.getPosition(window).x;
}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(mSprite);
	mSprite.setPosition(mPosition);
}

void Player::drawScore(sf::RenderWindow &window)
{
	string score = to_string(mScore);
	mSText.setString("Score: " + score);
	mSText.setPosition(sf::Vector2f(25, 60));
	window.draw(mSText);
}

void Player::drawHealth(sf::RenderWindow &window)
{
	string health = to_string(mHealth);
	mHText.setString("Lives left: " + health);
	mHText.setPosition(sf::Vector2f(25, 25));
	window.draw(mHText);
}

void Player::updateRectangle()
{
	mRectangle.height = mSprite.getGlobalBounds().height;
	mRectangle.width = mSprite.getGlobalBounds().width;

	mRectangle.left = mPosition.x;
	mRectangle.top = mPosition.y;
}

void Player::takeDamage(int damage)
{
	mHealth -= damage;
}

void Player::aliveCheck()
{
	if (mHealth < 1)
	{
		mIsAlive = false;
	}
}

bool Player::isAlive()
{
	return mIsAlive;
}

void Player::setDead()
{
	mIsAlive = false;
}

sf::Vector2f Player::getPosition()
{
	return mPosition;
}

sf::FloatRect Player::getRectangle()
{
	return mRectangle;
}

int Player::getScore()
{
	return mScore;
}

int Player::getDamage()
{
	return mDamage;
}

sf::Sprite Player::getSprite()
{
	return mSprite;
}

float Player::getSpeed()
{
	return 0.0f;
}

float Player::setSpeed(float value)
{
	return 0.0f;
}

void Player::addScore(int num)
{
	mScore += num;
}