#include "Enemy.h"

using namespace std;

static const int speed = 2;

static string fileName = "Invader.png";
static VGCImage image;

static int width;
static int height;

Enemy::Enemy(VGCVector &Position, int &WDirection, float BulletCD) :
	Entity(),
	mPosition(Position),
	mDirection(WDirection),
	mBulletCD(BulletCD),
	mDamage(10),
	mRadius(16),
	mType(ENEMY)
{
	mIsBullet = false;
}

Enemy::~Enemy()
{

}

void Enemy::update(EntityVector &entities)
{
	if (!isAlive())
	{
		//Check at beginning of each frame if about to die, if true add explosion
		addExplosion(entities);
	}

	move();

	cdTick();

	addBullet(entities);

	visibilityCheck();
}

void Enemy::render()
{
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}

void Enemy::initialize()
{
	image = VGCDisplay::openImage(fileName, 1, 1);
}

void Enemy::finalize()
{
	VGCDisplay::closeImage(image);
}

bool Enemy::visibilityCheck()
{
	//If outside lower screen boundary, set to not alive
	if (mPosition.getY() > VGCDisplay::getHeight() + height)
	{
		mIsAlive = false;
	}
	return mIsAlive;
}

void Enemy::setDead()
{
	mIsAlive = false;
}

bool Enemy::isAlive()
{
	return mIsAlive;
}

bool Enemy::canAddBullet()
{
	if (mBulletCD == 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::addBullet(EntityVector &entites)
{
	VGCVector direction(0, 1);
	if (canAddBullet())
	{
		//Add bullet when possible
		entites.push_back(new Bullet(mType, mPosition, direction));
	}
}

VGCVector Enemy::getPosition()
{
	return mPosition;
}

int Enemy::getDamage()
{
	return mDamage;
}

int Enemy::getRadius()
{
	return mRadius;
}

Enemy::Type Enemy::getType()
{
	return mType;
}

int Enemy::getScore()
{
	return 10;
}

void Enemy::takeDMG()
{
	mIsAlive = false;
}

void Enemy::cdTick()
{
	//Bullet CD
	mBulletCD++;
	if (mBulletCD >= 15.0f)
	{
		mBulletCD = 0.0f;
	}
}

void Enemy::move()
{
	width = VGCDisplay::getWidth(image);

	int x = mPosition.getX();
	int y = mPosition.getY();

	//Change X-direction if at the edge of screen
	if (x > VGCDisplay::getWidth() - width / 2)
	{
		mDirection = 0;
	}
	if (x < 0 + width / 2)
	{
		mDirection = 1;
	}

	if (mDirection == 0)
	{
		x -= speed;
	}
	else
	{
		x += speed;
	}
	y += speed;

	//Set position
	mPosition.setX(x);
	mPosition.setY(y);
}

void Enemy::addExplosion(EntityVector &entities)
{
	entities.push_back(new Explosion(mPosition));
}