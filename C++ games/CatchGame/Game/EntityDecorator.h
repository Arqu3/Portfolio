#ifndef INCLUDED_ENTITYDECORATOR
#define INCLUDED_ENTITYDECORATOR

#include "Entity.h"
#include <iostream>

class EntityDecorator : public Entity
{
public:
	enum Type
	{
		Fast,
		Damage,
		Score
	};

	EntityDecorator(Type type, Entity *entity);
	~EntityDecorator();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	bool isAlive();
	void setDead();

	sf::Vector2f getPosition();
	sf::FloatRect getRectangle();
	int getScore();
	int getDamage();
	sf::Sprite getSprite();
	float getSpeed();
	float setSpeed(float value);

private:
	Entity *mEntity;
	Type mType;
	sf::Sprite mSprite;
};

#endif