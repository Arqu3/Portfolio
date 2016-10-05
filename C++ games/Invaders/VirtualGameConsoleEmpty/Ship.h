#ifndef INCLUDED_SHIP
#define INCLUDED_SHIP

#include "Entity.h"
#include "VGCVirtualGameConsole.h"
#include "Bullet.h"
#include <string>


class Ship : public Entity
{
public:
	Ship(VGCVector &Position);
	 ~Ship();
	void update(EntityVector &entities);
	void render();
	void renderText();
	static void initialize();
	static void finalize();
	bool isAlive();
	int getDamage();
	int getRadius();
	int getScore();
	VGCVector getPosition();
	Type getType();
	void takeDMG();
	int damageTaken;
	void addScore(int score);

private:
	VGCVector mPosition;
	int mDamage;
	int mRadius;
	float mBulletCD;
	int mHealth;
	int mScore;
	Type mType;

	void addBullet(EntityVector &entities);
	void move();
};

#endif