#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include "ResourceHandler.h"
#include "Item.h"
#include "SFML\System.hpp"
#include <cmath>

class Player{
public:
	Player(ResourceHandler &handler, sf::Vector2f &position); 
	~Player();
	
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	sf::FloatRect getRect();
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	void moveToPosition(float x, float y);
	sf::Vector2f getDirection();
	void flipPlayer();
	bool isFacingLeft();
	sf::FloatRect getGlobalRect();
	void setActiveAnimation(std::string animation);
	std::string getActiveAnimation();
	void togglePlayer();
	float getSpeed();
	void setSpeed(float speed);
	bool getIsOnPosition();
	void setScale(sf::Vector2f scale);
	int getCurrentFrame();
	void setFrameTime(float frametime);
	void sequenceMove1();
	void sequenceMove2();
	void resetSequence();

	void navigate(std::vector<Item*> items, float deltaTime);

private:

	void move(float deltaTime);

	int sequenceCounter;

	sf::Vector2f mPosition;
	sf::Vector2f mDirection;
	sf::Vector2f moveTo;
	sf::Sprite mSprite;

	float mSpeed;

	bool mFacingLeft;
	bool isOnPosition;
	sf::FloatRect mRect;
	sf::FloatRect mMoveToRect;
	//void waitForClick(sf::RenderWindow &window);
	bool mThomasActive;

	//Animations
	bool mWalk;
	bool mPush;
	//Animation Values
	int mCurrentFrame;
	int mFrameYOffset;
	int mFrameXOffset;
	float mCurrentTime;
	float mFrameTime;
	std::string mActiveAnimation;

	//Sounds
	sf::Sound mWalkingSound;
	int mStepCooldown;
	
	//Animation Textures
	sf::Texture mThomasTexture;
	sf::Texture mHilmaTexture;
	sf::Texture mHilmaPushTexture;
	sf::Texture mHilmaFishingTexture;
	sf::Texture mHilmaJumpTexture;

	sf::Vector2f mNextPosition;
	bool mCorrecting;
	bool mDownValid;
	bool mUpValid;
	bool mRightValid;
	bool mLeftValid;
	bool mDirectionSet;
};
#endif
