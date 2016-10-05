#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

class Entity
{
public:
	typedef std::vector<Entity*> EntityVector;

	Entity();
	virtual ~Entity();

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual bool isAlive() = 0;
	virtual void setDead() = 0;

	virtual sf::Vector2f getPosition() = 0;
	virtual sf::FloatRect getRectangle() = 0;
	virtual int getScore() = 0;
	virtual int getDamage() = 0;
	virtual sf::Sprite getSprite() = 0;
	virtual float getSpeed() = 0;
	virtual float setSpeed(float value) = 0;
};

#endif