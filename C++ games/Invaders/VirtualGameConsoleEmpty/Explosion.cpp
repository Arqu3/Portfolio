#include "Explosion.h"

using namespace std;

static VGCImage image;
static string fileName = "Explosion.png";

Explosion::Explosion(VGCVector &Position) :
	mPosition(Position),
	mTimer(50.0f),
	mDamage(0),
	mRadius(16)
{
	mIsBullet = false;
}

Explosion::~Explosion()
{
}

void Explosion::initialize()
{
	image = VGCDisplay::openImage(fileName, 1, 1);
}

void Explosion::finalize()
{
	VGCDisplay::closeImage(image);
}

void Explosion::update(EntityVector &entities)
{
	//Set to not alive if timer has run out
	mTimer--;
	if (mTimer <= 0)
	{
		mIsAlive = false;
	}
}

void Explosion::render()
{
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}

bool Explosion::isAlive()
{
	return mIsAlive;
}

int Explosion::getDamage()
{
	return mDamage;
}

int Explosion::getRadius()
{
	return mRadius;
}

VGCVector Explosion::getPosition()
{
	return mPosition;
}

Explosion::Type Explosion::getType()
{
	return FRIEND;
}

int Explosion::getScore()
{
	return 0;
}

void Explosion::takeDMG()
{
}