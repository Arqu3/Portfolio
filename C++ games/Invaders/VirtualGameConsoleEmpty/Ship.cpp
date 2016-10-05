#include "Ship.h"

using namespace std;

static int speed = 5;

static int height = 32;
static int width = 32;
static string fileName = "Ship.png";
static VGCImage image;

//Text output
const VGCColor textColor(255, 255, 255, 255);
//Score text
const VGCVector scoreTPosition(600, 0);
const VGCAdjustment scoreTAdjustment(1.0, 0.0);
//Health text
const VGCVector healthTPosition(0, 0);
const VGCAdjustment healthTAdjustment(0.0, 0.0);

Ship::Ship(VGCVector &Position) :
	Entity(),
	mPosition(Position),
	mHealth(100),
	mScore(0),
	mBulletCD(0.0f),
	mDamage(0),
	mRadius(16),
	mType(FRIEND),
	damageTaken(0)
{
	mIsBullet = false;
}


Ship::~Ship()
{
}

void Ship::update(EntityVector &entities)
{
	move();

	//Set shoot timer
	mBulletCD++;
	if (mBulletCD >= 12.5f)
	{
		mBulletCD = 0.0f;
	}

	//Add bullets
	if (VGCKeyboard::isPressed(VGCKey::SPACE_KEY) && mBulletCD == 0.0f)
	{
		addBullet(entities);
	}

	//Checks if alive at end of each frame
	isAlive();
}

bool Ship::isAlive()
{
	if (mHealth > 0)
	{
		mIsAlive = true;
	}
	else
	{
		mIsAlive = false;
	}

	return mIsAlive;
}

void Ship::takeDMG()
{
	mHealth -= damageTaken;
}

void Ship::addScore(int score)
{
	mScore += score;
}

Ship::Type Ship::getType()
{
	return mType;
}

int Ship::getScore()
{
	return 0;
}

void Ship::move()
{
	//Set movement restrictions
	const int minX = width / 2;
	const int minY = height / 2;
	const int maxX = VGCDisplay::getWidth() - width / 2;
	const int maxY = VGCDisplay::getHeight() - height / 2;

	//Get position
	int x = mPosition.getX();
	int y = mPosition.getY();

	//Input & movement restrictions
	if (VGCKeyboard::isPressed(VGCKey::D_KEY))
	{
		x += speed;
		if (x > maxX)
		{
			x = maxX;
		}
	}
	if (VGCKeyboard::isPressed(VGCKey::A_KEY))
	{
		x -= speed;
		if (x < minX)
		{
			x = minX;
		}
	}
	if (VGCKeyboard::isPressed(VGCKey::W_KEY))
	{
		y -= speed;
		if (y < minY)
		{
			y = minY;
		}
	}
	if (VGCKeyboard::isPressed(VGCKey::S_KEY))
	{
		y += speed;
		if (y > maxY)
		{
			y = maxY;
		}
	}
	//Set position
	mPosition.setX(x);
	mPosition.setY(y);
}

int Ship::getDamage()
{
	return mDamage;
}

int Ship::getRadius()
{
	return mRadius;
}

VGCVector Ship::getPosition()
{
	return mPosition;
}

void Ship::addBullet(EntityVector &entities)
{
	//Middle
	VGCVector directionM(0, -1);
	entities.push_back(new Bullet(mType, mPosition, directionM));
	
	//Right
	VGCVector directionR(1, -1);
	entities.push_back(new Bullet(mType, mPosition, directionR));
	
	//Left
	VGCVector directionL(-1, -1);
	entities.push_back(new Bullet(mType, mPosition, directionL));
}

void Ship::render()
{
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}

void Ship::renderText()
{
	//Open font
	static const int fontSize = 30;
	VGCFont font = VGCDisplay::openFont("Arial", fontSize);

	//Render text
	//Score
	const string sText = "Score: " + to_string(mScore);
	VGCDisplay::renderString(font, sText, textColor, scoreTPosition, scoreTAdjustment);

	//Health
	const string hText = "Health: " + to_string(mHealth);
	VGCDisplay::renderString(font, hText, textColor, healthTPosition, healthTAdjustment);

	VGCDisplay::closeFont(font);
}

void Ship::initialize()
{
	//Open on initialization
	image = VGCDisplay::openImage(fileName, 1, 1);
}

void Ship::finalize()
{
	//Close image before application exit
	VGCDisplay::closeImage(image);
}