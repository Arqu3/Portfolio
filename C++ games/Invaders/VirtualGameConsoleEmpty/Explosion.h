#ifndef INCLUDED_EXPLOSION
#define INCLUDED_EXPLOSION

#include "VGCVirtualGameConsole.h"
#include <string>
#include "Entity.h"

class Explosion : public Entity
{
public:
	Explosion(VGCVector &Position);
	~Explosion();

	static void initialize();
	static void finalize();

	void render();
	void update(EntityVector &entities);
	bool isAlive();
	void takeDMG();
	int getDamage();
	int getRadius();
	int getScore();
	VGCVector getPosition();
	Type getType();


private:
	VGCVector mPosition;
	float mTimer;
	int mDamage;
	int mRadius;
};

#endif