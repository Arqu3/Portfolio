#include "Player.h"

using namespace std;

Player::Player(ResourceHandler &handler, sf::Vector2f &position) :
mPosition(position),
isOnPosition(true),
moveTo(position),
mActiveAnimation("Walk"),
mWalk(false),
mFrameTime(0.03f), //Lägre värde = Snabbare animation
mCurrentTime(0),
mCurrentFrame(0),
mFrameXOffset(0),
mFrameYOffset(0),
mSpeed(100.0f),
mFacingLeft(true),
mStepCooldown(0),
mThomasActive(true),
sequenceCounter(0),
mNextPosition(position),
mCorrecting(false),
mDownValid(true),
mUpValid(true),
mRightValid(true),
mLeftValid(true)
{
	//Sounds
	mWalkingSound.setBuffer(*handler.getSound("Footsteps_Thomas.ogg"));
	mWalkingSound.setVolume(25);

	//Spritesheet - Thomas
	mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
	mSprite.setOrigin(400, 700);

	/*mThomasTexture = *handler.getTexture("ThomasWalk.png");
	mHilmaTexture = *handler.getTexture("HilmaWalk.png");
	mHilmaPushTexture = *handler.getTexture("HilmaPush.png");
	mHilmaFishingTexture = *handler.getTexture("HilmaFishing.png");*/

	mThomasTexture.loadFromFile("Resources/Textures/ThomasWalk.png");
	mHilmaTexture.loadFromFile("Resources/Textures/HilmaWalk.png");
	mHilmaPushTexture.loadFromFile("Resources/Textures/HilmaPush.png");
	mHilmaFishingTexture.loadFromFile("Resources/Textures/HilmaFishing.png");
	mHilmaJumpTexture.loadFromFile("Resources/Textures/HilmaJump.png");

	mSprite.setTexture(mThomasTexture);
	mSprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
}


Player::~Player()
{

}


void Player::move(float deltaTime)
{
	mMoveToRect = sf::FloatRect(moveTo.x, moveTo.y, 10, 10);

	if (mRect.intersects(mMoveToRect))
	{
		isOnPosition = true;
		mDirectionSet = false;
		mWalk = false;
	}
	else
	{
		isOnPosition = false;
		mWalk = true;
	}


	if (isOnPosition == false)
	{
		mPosition += mDirection * mSpeed * deltaTime;
		if (!mCorrecting)
		{
			//mNextPosition += mDirection * mSpeed * deltaTime;
		}
	}
}

void Player::setPosition(float x, float y)
{
	mPosition = sf::Vector2f(x, y);
	mNextPosition = sf::Vector2f(x, y);
	mDirection = sf::Vector2f(0, 0);
	moveTo = sf::Vector2f(x, y);
}

void Player::moveToPosition(float x, float y)
{
	//Creates a unit-direction vector that the player follows
	moveTo = sf::Vector2f(x, y);

	float deltaX = (moveTo.x - mPosition.x);
	float deltaY = (moveTo.y - mPosition.y);

	mDirection = sf::Vector2f(deltaX, deltaY);

	float squareX = (deltaX * deltaX);
	float squareY = (deltaY * deltaY);

	float added = (squareX + squareY);
	float root = sqrt(added);

	sf::Vector2f unit(mDirection.x / root, mDirection.y / root);
	mDirection = unit;
}


void Player::update(float deltaTime)
{
	//Animation
	mCurrentTime += deltaTime;

	// Walk Animations
	if (mActiveAnimation == "Walk" && mWalk)
	{
		if (mThomasActive)
		{
			if (mCurrentTime >= mFrameTime)
			{
				mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 800, mFrameYOffset * 800, 800, 800));
				if (mCurrentFrame < 27)
				{
					if ((mCurrentFrame == 13 || mCurrentFrame == 26) && mWalkingSound.getStatus() != 2)
					{
						mWalkingSound.play();
					}

					mFrameXOffset += 1;
					if (mFrameXOffset % 11 == 10)
					{
						mFrameYOffset++;
					}
					if (mFrameXOffset >= 10)
					{
						mFrameXOffset = 0;
					}
					mCurrentFrame += 1;
				}
				else
				{
					mCurrentFrame = 0;
					mFrameXOffset = 0;
					mFrameYOffset = 0;
				}
				mCurrentTime = 0;
			}
		}
		else
		{
			if (mCurrentTime >= mFrameTime)
			{
				mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 600, mFrameYOffset * 600, 600, 600));
				if (mCurrentFrame < 27)
				{
					if ((mCurrentFrame == 3 || mCurrentFrame == 15) && mWalkingSound.getStatus() != 2)
					{
						mWalkingSound.play();
					}

					mFrameXOffset += 1;
					if (mFrameXOffset % 8 == 7)
					{
						mFrameYOffset++;
					}
					if (mFrameXOffset >= 7)
					{
						mFrameXOffset = 0;
					}
					mCurrentFrame += 1;
				}
				else
				{
					mCurrentFrame = 0;
					mFrameXOffset = 0;
					mFrameYOffset = 0;
				}
				mCurrentTime = 0;
			}
		}
	}
	else
	{
		mWalkingSound.pause();
	}

	if (mActiveAnimation == "Push")
	{
		if (mCurrentTime >= mFrameTime)
		{
			mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 600, mFrameYOffset * 600, 600, 600));
			if (mCurrentFrame < 27)
			{
				mFrameXOffset += 1;
				if (mFrameXOffset % 10 == 9)
				{
					mFrameYOffset++;
				}
				if (mFrameXOffset >= 9)
				{
					mFrameXOffset = 0;
				}
				mCurrentFrame += 1;
			}
			else
			{
				mCurrentFrame = 0;
				mFrameXOffset = 0;
				mFrameYOffset = 0;
			}
			mCurrentTime = 0;
		}
	}

	//Fishing Animation
	if (mActiveAnimation == "Fishing")
	{
		if (mCurrentTime >= mFrameTime)
		{
			mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 800, mFrameYOffset * 800, 800, 800));
			if (mCurrentFrame < 27)
			{
				mFrameXOffset += 1;
				if (mFrameXOffset % 7 == 6)
				{
					mFrameYOffset++;
				}
				if (mFrameXOffset >= 6)
				{
					mFrameXOffset = 0;
				}
				mCurrentFrame += 1;
			}
			else
			{
				mCurrentFrame = 27;
				mFrameXOffset = 3;
				mFrameYOffset = 4;
			}
			mCurrentTime = 0;
		}
	}

	//Fishing Pull Animation
	if (mActiveAnimation == "FishingPull")
	{
		if (mCurrentTime >= mFrameTime)
		{
			mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 800, mFrameYOffset * 800, 800, 800));
			if (mCurrentFrame < 11)
			{
				mFrameXOffset -= 1;
				if (mFrameXOffset % 7 == 0)
				{
					mFrameYOffset--;
				}
				if (mFrameXOffset <= 0)
				{
					mFrameXOffset = 5;
				}
				mCurrentFrame += 1;
			}
			else
			{
				mCurrentFrame = 11;
				mFrameXOffset = 3;
				mFrameYOffset = 4;
			}
			mCurrentTime = 0;
		}
	}

	//Jump animation
	if (mActiveAnimation == "Jump")
	{
		if (mCurrentTime >= mFrameTime)
		{
			mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 700, mFrameYOffset * 700, 700, 700));
			if (mCurrentFrame < 40)
			{
				mFrameXOffset++;
				if (mFrameXOffset % 6 == 5)
				{
					mFrameYOffset++;
				}
				if (mFrameXOffset >= 5)
				{
					mFrameXOffset = 0;
				}
				mCurrentFrame++;
			}
			else
			{
				mCurrentFrame = 40;
				mFrameXOffset = 4;
				mFrameYOffset = 7;
			}
			mCurrentTime = 0;
		}
	}

	//If Player is moving to the left (getDirection.x < 0) and isn't already facing left, flip Player
	if (getDirection().x < 0 && !isFacingLeft())
	{
		flipPlayer();
	}
	//If Player is moving to the right (getDirection.x > 0) and is facing left, flip Player
	if (getDirection().x > 0 && isFacingLeft())
	{
		flipPlayer();
	}

	mRect = sf::FloatRect(mPosition.x, mPosition.y, 10, 10);
	mSprite.setPosition(mPosition);
	move(deltaTime);
}



void Player::draw(sf::RenderWindow &window)
{
	//Help Rectangles to visualize getGlobalRect()
	/*sf::RectangleShape rectangle(mPosition);
	rectangle.setPosition(sf::Vector2f(mPosition.x - 50, mPosition.y - 200));
	rectangle.setSize(sf::Vector2f(100, 220));
	sf::RectangleShape rectangleHilma(mPosition);
	rectangleHilma.setPosition(sf::Vector2f(mPosition.x - 30, mPosition.y - 115));
	rectangleHilma.setSize(sf::Vector2f(50, 130));
	if (mThomasActive)
		window.draw(rectangle);
	else
		window.draw(rectangleHilma);*/

	window.draw(mSprite);
}



sf::FloatRect Player::getRect()
{
	return mRect;
}



sf::Vector2f Player::getPosition()
{
	return mPosition;
}

sf::Vector2f Player::getDirection()
{
	return mDirection;
}

void Player::flipPlayer()
{
	mFacingLeft = !mFacingLeft;
	mSprite.scale(sf::Vector2f(-1, 1));
}

bool Player::isFacingLeft()
{
	return mFacingLeft;
}

//Return a Rect that covers the whole character
sf::FloatRect Player::getGlobalRect()
{
	sf::FloatRect globalRect;
	//Creates a FloatRect at Players current position and size, compensated for previously set Origin and Scale
	if (mThomasActive)
	{
		globalRect = sf::FloatRect(sf::Vector2f(mPosition.x - 50, mPosition.y - 200), sf::Vector2f(100, 220));
	}
	else
	{
		globalRect = sf::FloatRect(sf::Vector2f(mPosition.x - 30, mPosition.y - 115), sf::Vector2f(50, 130));
	}

	return globalRect;
}

void Player::setActiveAnimation(std::string animation)
{
	if (animation == "Walk")
	{
		//Avoid starting animation over if already walking
		if (mActiveAnimation != "Walk")
		{
			mCurrentFrame = 0;
			mFrameXOffset = 0;
			mFrameYOffset = 0;

			if (mThomasActive)
			{
				mSprite.setTexture(mThomasTexture);
			}
			else
			{
				mSprite.setTexture(mHilmaTexture);
			}
		}
		mWalk = true;
	}
	else if (animation == "Push")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
		mSprite.setTexture(mHilmaPushTexture);
		mWalk = false;
	}
	else if (animation == "Fishing")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
		mSprite.setTexture(mHilmaFishingTexture);
		mWalk = false;
	}
	else if (animation == "FishingPull")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 3;
		mFrameYOffset = 4;
		mSprite.setTexture(mHilmaFishingTexture);
		mWalk = false;
	}
	else if (animation == "Jump")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
		mSprite.setTexture(mHilmaJumpTexture);
		mWalk = false;
	}
	else if (animation == "Idle")
	{
		if (mThomasActive)
		{
			mSprite.setTexture(mThomasTexture);
			mSprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
		}
		else
		{
			mSprite.setTexture(mHilmaTexture);
			mSprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
		}
		mWalk = false;
	}
	else
	{
		mWalk = false;
	}

	mActiveAnimation = animation;
}

std::string Player::getActiveAnimation()
{
	return mActiveAnimation;
}

void Player::togglePlayer()
{
	mThomasActive = !mThomasActive;

	if (mThomasActive)
	{
		mSprite.setTexture(mThomasTexture);
		mSprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setOrigin(400, 700);
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
		mFacingLeft = true;
	}
	else
	{
		mSprite.setTexture(mHilmaTexture);
		mSprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
		mSprite.setScale(sf::Vector2f(0.25f, 0.25f));
		mSprite.setOrigin(300, 500);
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;
		mFacingLeft = true;
	}
}

float Player::getSpeed()
{
	return mSpeed;
}

void Player::setSpeed(float speed)
{
	mSpeed = speed;
}

bool Player::getIsOnPosition()
{
	return isOnPosition;
}

void Player::setScale(sf::Vector2f scale)
{
	mSprite.setScale(scale);
}

int Player::getCurrentFrame()
{
	return mCurrentFrame;
}

void Player::setFrameTime(float frametime)
{
	mFrameTime = frametime;
}

void Player::navigate(std::vector<Item*> items, float deltaTime)
{
	for (std::vector<Item*>::size_type i = 0; i < items.size(); i++)
	{
		if (!items[i]->getWalkable())
		{
			//Check if any items are in the way
			if (items[i]->getRectangle().contains(mNextPosition))
			{
				//Check valid directions around item
				if (mPosition.x - 10 > items[i]->getRectangle().left)
				{
					if (items[i]->getRectangle().contains(mPosition.x + 10, mPosition.y + 10))
					{
						mDownValid = false;
					}
					if (items[i]->getRectangle().contains(mPosition.x + 10, mPosition.y - 10))
					{
						mUpValid = false;
					}
				}
				else if (mPosition.x - 10 > (items[i]->getRectangle().left + items[i]->getRectangle().width))
				{
					if (items[i]->getRectangle().contains(mPosition.x - 10, mPosition.y + 10))
					{
						mDownValid = false;
					}
					if (items[i]->getRectangle().contains(mPosition.x - 10, mPosition.y - 10))
					{
						mUpValid = false;
					}
				}
				if (mPosition.y - 10 > items[i]->getRectangle().top)
				{
					if (items[i]->getRectangle().contains(mPosition.x + 10, mPosition.y + 10))
					{
						mRightValid = false;
					}
					if (items[i]->getRectangle().contains(mPosition.x - 10, mPosition.y + 10))
					{
						mLeftValid = false;
					}
				}
				else if (mPosition.y - 10 > (items[i]->getRectangle().top + items[i]->getRectangle().height))
				{
					if (items[i]->getRectangle().contains(mPosition.x + 10, mPosition.y - 10))
					{
						mRightValid = false;
					}
					if (items[i]->getRectangle().contains(mPosition.x - 10, mPosition.y - 10))
					{
						mLeftValid = false;
					}
				}

				//Choose best direction around item
				if (!mDirectionSet)
				{
					if (mPosition.x >= moveTo.x)
					{
						mRightValid = false;
					}
					else
					{
						mLeftValid = false;
					}
					if (mPosition.y >= moveTo.y)
					{
						mDownValid = false;
					}
					else
					{
						mUpValid = false;
					}
					mDirectionSet = true;
				}

				//Walk around item using best direction
				if (mDownValid && (!mRightValid || !mLeftValid))
				{
					mPosition += sf::Vector2f(0, 1) * mSpeed * deltaTime;
					mCorrecting = true;
					if (!items[i]->getRectangle().contains(mPosition.x, mPosition.y + 1))
					{
						mCorrecting = false;
						mNextPosition = mPosition;
					}
				}
				else if (mUpValid && (!mRightValid || !mLeftValid))
				{
					mPosition += sf::Vector2f(0, -1) * mSpeed * deltaTime;
					mCorrecting = true;
					if (!items[i]->getRectangle().contains(mPosition.x, mPosition.y - 1))
					{
						mCorrecting = false;
						mNextPosition = mPosition;
					}
				}
				else if (mRightValid && (!mUpValid || !mDownValid))
				{
					mPosition += sf::Vector2f(1, 0) * mSpeed * deltaTime;
					mCorrecting = true;
					if (!items[i]->getRectangle().contains(mPosition.x + 1, mPosition.y))
					{
						mCorrecting = false;
						mNextPosition = mPosition;
					}
				}
				else if (mLeftValid && (!mUpValid || !mDownValid))
				{
					mPosition += sf::Vector2f(-1, 0) * mSpeed * deltaTime;
					mCorrecting = true;
					if (!items[i]->getRectangle().contains(mPosition.x - 1, mPosition.y))
					{
						mCorrecting = false;
						mNextPosition = mPosition;
					}
				}
			}
			else if (!mCorrecting)
			{
				mDownValid = true;
				mUpValid = true;
				mRightValid = true;
				mLeftValid = true;
				mDirectionSet = false;
				moveToPosition(moveTo.x, moveTo.y);
				mPosition = mNextPosition;
			}
		}
		else
		{
			moveToPosition(moveTo.x, moveTo.y);
			mPosition = mNextPosition;
		}
	}
}

void Player::sequenceMove1()
{
	setSpeed(400.0f);

	if (sequenceCounter == 0)
	{
		moveToPosition(486, 457);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 1)
	{
		moveToPosition(530, 407);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 2)
	{
		moveToPosition(584, 420);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 3)
	{
		moveToPosition(593, 377);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 4)
	{
		moveToPosition(604, 318);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 5)
	{
		moveToPosition(688, 321);
		if (getIsOnPosition())
		{
			setPosition(688, 321);
			sequenceCounter++;
		}
	}
}

void Player::sequenceMove2()
{
	setSpeed(400.0f);

	if (sequenceCounter == 0)
	{
		moveToPosition(615, 255);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 1)
	{
		moveToPosition(550, 300);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 2)
	{
		moveToPosition(515, 350);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 3)
	{
		moveToPosition(495, 425);
		if (getIsOnPosition())
		{
			sequenceCounter++;
		}
	}

	else if (sequenceCounter == 4)
	{
		moveToPosition(490, 500);
		if (getIsOnPosition())
		{
			setPosition(490, 500);
			setSpeed(100.0f);
		}
	}
}

void Player::resetSequence()
{
	sequenceCounter = 0;
}
