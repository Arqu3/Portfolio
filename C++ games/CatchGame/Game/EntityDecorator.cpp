#include "EntityDecorator.h"

using namespace std;

EntityDecorator::EntityDecorator(Type type, Entity *entity):
mEntity(entity),
mType(type)
{
	//Set sprite color depending on type
	mSprite = mEntity->getSprite();
	switch (mType)
	{
	case Type::Fast:
		mSprite.setColor(sf::Color::Blue);

		//Also set speed if type is fast
		setSpeed(mEntity->getSpeed() * 5.0f);
		break;

	case Type::Damage:
		mSprite.setColor(sf::Color::Red);
		break;

	case Type::Score:
		mSprite.setColor(sf::Color::Yellow);
		break;
	}
}

EntityDecorator::~EntityDecorator()
{
	delete mEntity;
}

void EntityDecorator::update(float deltaTime)
{
	return mEntity->update(deltaTime);
}

void EntityDecorator::draw(sf::RenderWindow &window)
{
	//Draw new sprite (new color)
	window.draw(mSprite);
	mSprite.setPosition(mEntity->getPosition());
}

bool EntityDecorator::isAlive()
{
	return mEntity->isAlive();
}

void EntityDecorator::setDead()
{
	return mEntity->setDead();
}

sf::Vector2f EntityDecorator::getPosition()
{
	return mEntity->getPosition();
}

sf::FloatRect EntityDecorator::getRectangle()
{
	return mEntity->getRectangle();
}

int EntityDecorator::getScore()
{
	//All specials give bonus score
	switch (mType)
	{
	default:
		return mEntity->getScore() + 1;
		break;

	case Type::Score:
		//Score type enemy gives 5 times regular score
		return mEntity->getScore() + 4;
		break;
	}
}

int EntityDecorator::getDamage()
{
	switch (mType)
	{
	default:
		return mEntity->getDamage();
		break;

	case Type::Damage:
		//Damage type deals double damage to player
		return mEntity->getDamage() * 2;
		break;
	}
}

sf::Sprite EntityDecorator::getSprite()
{
	return mSprite;
}

float EntityDecorator::getSpeed()
{
	return mEntity->getSpeed();
}

float EntityDecorator::setSpeed(float value)
{
	return mEntity->setSpeed(value);
}