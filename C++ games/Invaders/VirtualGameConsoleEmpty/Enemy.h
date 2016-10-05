#ifndef INCLUDED_ENEMY
#define INCLUDED_ENEMY

#include "VGCVirtualGameConsole.h"
#include "Entity.h"
#include "Bullet.h"
#include "Explosion.h"
#include <string>

class Enemy : public Entity
{
public:
	Enemy(VGCVector &Position, int &WDirection, float bulletCD);
	~Enemy();
	void update(EntityVector &entities);
	void render();
	VGCVector getPosition();
	void setDead();
	bool isAlive();
	void takeDMG();

	int getDamage();
	int getRadius();
	int getScore();
	Type getType();
	static void initialize();
	static void finalize();

private:
	float mBulletCD;
	VGCVector mPosition;
	int mDirection;
	int mDamage;
	int mRadius;
	Type mType;

	bool visibilityCheck();
	bool canAddBullet();
	void move();
	void cdTick();
	void addBullet(EntityVector &entities);
	void addExplosion(EntityVector &entities);
};

#endif