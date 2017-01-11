#ifndef INCLUDED_CLUE
#define INCLUDED_CLUE

#include "ResourceHandler.h"

class Clue
{
public:
	Clue(ResourceHandler &handler, std::string backgroundName);
	~Clue();

	void draw(sf::RenderWindow &window);
	void add(ResourceHandler &handler, std::string textureName, sf::Vector2f &position);

	struct InternalClue
	{
		InternalClue(ResourceHandler &handler, std::string textureName, sf::Vector2f &position) :
			mState1(false),
			mState2(false)
		{
			mSprite.setTexture(*handler.getTexture(textureName));
			mSprite.setPosition(position);
			originalX = position.x;
			//TODO - Add sf::Vector2f scale parameter and use that to set the proper scale for mSprite?
			if (textureName == "InfoIcon.png")
			{
				mSprite.setScale(sf::Vector2f(0.5f, 0.5f));
			}
			mText.setPosition(sf::Vector2f(343, 315)); //Add proper position
			mFont.loadFromFile("Resources/Fonts/Lora-Regular.ttf");
			mText.setCharacterSize(18);
			mText.setColor(sf::Color::Black);
			mText.setFont(mFont);
		}

		sf::Sprite mSprite;
		bool mState1;
		bool mState2;
		std::string mText1;
		std::string mText2;
		sf::Text mText;
		sf::Font mFont;
		float originalX;

		void setState1()
		{
			//Safety check
			if (!mState2)
			{
				mState1 = true;
				mText.setString(mText1);

				if (mText2 != "")
				{
					mSprite.setColor(sf::Color(255, 255, 255, 128));
				}
			}
		}
		void setState2()
		{
			mState2 = true;
			mText.setString(mText2);

			mSprite.setColor(sf::Color(255, 255, 255, 255));
		}

		bool getState1()
		{
			return mState1;
		}

		bool getState2()
		{
			return mState2;
		}

		void setStrings(std::string string1, std::string string2)
		{
			mText1 = string1;
			mText2 = string2;
		}

		bool isHover(sf::Vector2f point)
		{
			if (mSprite.getGlobalBounds().contains(point))
			{
				return true;
			}
			return false;
		}

		void draw(sf::RenderWindow &window)
		{
			if (mState1 || mState2)
			{
				window.draw(mSprite);
			}
		}
		void drawText(sf::RenderWindow &window)
		{
			window.draw(mText);
		}
		void setXPosition(float x)
		{
			mSprite.setPosition(sf::Vector2f(x, mSprite.getPosition().y));
		}
		void setTextPosition(float x)
		{
			mText.setPosition(sf::Vector2f(x, mText.getPosition().y));
		}
		float getXPosition()
		{
			return originalX;
		}
	};

	//Get clue at specific index
	InternalClue* getClue(int index);
	std::vector<InternalClue*> getClues()
	{
		return mClues;
	}

	void setCluesPosition(sf::Vector2f viewCenter);

private:
	typedef std::vector<InternalClue*> ClueVector;
	ClueVector mClues;
	sf::Sprite mBackground;
};

#endif