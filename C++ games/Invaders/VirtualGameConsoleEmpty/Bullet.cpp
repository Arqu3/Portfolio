#include "Bullet.h"

using namespace std;

static const int speed = 6;

static string fileName = "Bullet.png";
static VGCImage image;

Bullet::Bullet(Type &Type, VGCVector &Position, VGCVector &Direction) :
	mPosition(Position),
	mDirection(Direction),
	mDamage(5),
	mRadius(3),
	mType(Type)
{
	mIsBullet = true;
}


Bullet::~Bullet()
{
}

void Bullet::update(EntityVector &entities)
{
	int y = mPosition.getY();
	int x = mPosition.getX();

	//Clamp movement to speed max value, add positive/negative direction when added, not speed
	if (mDirection.getY() != 0)
	{
		y += clamp(speed * mDirection.getY(), -speed, speed);
	}
	if (mDirection.getX() != 0)
	{
		x += clamp(speed * mDirection.getX(), -speed / 3, speed / 3);
	}

	//Set position
	mPosition.setY(y);
	mPosition.setX(x);

	//Check visibility
	visibilityCheck();
}

void Bullet::render()
{
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}

void Bullet::initialize()
{
	image = VGCDisplay::openImage(fileName, 1, 1);
}

void Bullet::finalize()
{
	VGCDisplay::closeImage(image);
}

void Bullet::visibilityCheck()
{
	//Set to not alive when outside screen
	if (mPosition.getX() > VGCDisplay::getWidth() || mPosition.getX() < 0
		|| mPosition.getY() > VGCDisplay::getHeight() || mPosition.getY() < 0)
	{
		mIsAlive = false;
	}
}

bool Bullet::isAlive()
{
	return mIsAlive;
}

int Bullet::getDamage()
{
	return mDamage;
}

int Bullet::getRadius()
{
	return mRadius;
}

VGCVector Bullet::getPosition()
{
	return mPosition;
}

Bullet::Type Bullet::getType()
{
	return mType;
}

int Bullet::getScore()
{
	return 0;
}

void Bullet::takeDMG()
{
	mIsAlive = false;
}

float Bullet::clamp(float n, float lower, float upper)
{
	return std::fmaxf(lower, std::fminf(n, upper));
}