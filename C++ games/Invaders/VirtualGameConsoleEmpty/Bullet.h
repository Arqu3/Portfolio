#ifndef INCLUDED_BULLET
#define INCLUDED_BULLET

#include "Entity.h"
#include <string>

class Bullet : public Entity
{
public:
	Bullet(Type &Type, VGCVector &Position, VGCVector &Direction);
	~Bullet();
	void update(EntityVector &entities);
	void render();
	bool isAlive();
	void takeDMG();
	int getDamage();
	int getRadius();
	int getScore();
	VGCVector getPosition();
	Type getType();
	static void initialize();
	static void finalize();


private:
	VGCVector mPosition;
	VGCVector mDirection;
	Type mType;
	int mDamage;
	int mRadius;
	void visibilityCheck();

	virtual float clamp(float n, float lower, float upper);
};

#endif

