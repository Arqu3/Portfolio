#ifndef ITEM
#define ITEM

#include "ResourceHandler.h"
#include <string>

class Item
{
public:
	Item(ResourceHandler &handler, sf::Vector2f &position, std::string id);
	~Item();
 
	//Toggle functions for flags
	void toggleActive();
	void toggleLookable();
	void toggleInteractable();
	void togglePickupable();
	void toggleIsLookedAt();
	void toggleInteracted();

	std::string getId();

	int getIndex();
	void setIndex(int value);

	//Draw
	void draw(sf::RenderWindow &window);
	void drawINV(sf::RenderWindow &window);
	
	//Get functions to check flags
	bool getActive();
	bool getLookable();
	bool getInteractable();
	bool getPickupable();
	bool isLookedAt();
	bool isInteracted();

	//Get Name
	std::string getName();

	//Get Description
	std::string getDescription();

	//Get bounding boxes
	sf::FloatRect getRectangle();
	sf::FloatRect getINVRectangle();

	//Get position of item
	sf::Vector2f getPosition();
	sf::Vector2f getINVPosition();

	//Get crafting index of item
	int getCraftIndex();

	//Set position of item
	void setPosition(float x, float y);
	void setINVPosition(float x, float y);

	void moveToPosition(float x, float y);

	void move(float deltaTime);

	bool getIsOnPosition();

	//Set scale of item
	void setScale(float x, float y);

	sf::Sprite getSprite();
	sf::Sprite getINVSprite();

	void update(float deltaTime);

	float getSpeed();
	void setSpeed(float speed);

	//Change texture
	void changeTexture(ResourceHandler &handler, std::string filename);

	//Animations
	void setActiveAnimation(std::string animation);
	std::string getActiveAnimation();

	void setCraftIndex(int craftIndex);

	bool getWalkable();
	void toggleWalkable();

private:
	bool mIsActive;
	bool mIsLookable;
	bool mIsInteractable;
	bool mIsPickupable;
	bool mIsLookedAt;
	bool mInteracted;
	bool mWalkable;

	int mIndex;
	int mCraftIndex;

	std::string mId;
	std::string mName;
	std::string mDescription;

	sf::Vector2f mPosition;
	sf::Vector2f mDirection;
	sf::Vector2f moveTo;
	sf::Sprite mSprite;
	sf::Sprite mINVSprite;

	sf::FloatRect mMoveToRect;
	bool isOnPosition;

	float mSpeed;


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

	//Animation Textures
	sf::Texture mGardenLady;
	sf::Texture mDog;
	sf::Texture mCatWalking;
	sf::Texture mCatEating;
	sf::Texture mRogerSwim;

};

#endif