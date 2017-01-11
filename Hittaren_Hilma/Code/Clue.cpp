#include "Clue.h"

using namespace std;

Clue::Clue(ResourceHandler &handler, string backgroundName) :
mClues()
{
	mBackground.setTexture(*handler.getTexture(backgroundName));
	mBackground.setPosition(sf::Vector2f(0, 0)); //Set proper position
	mBackground.setScale(0.5f, 0.5f);
}

Clue::~Clue()
{
	mClues.clear();
}

void Clue::draw(sf::RenderWindow &window)
{
	window.draw(mBackground);
	for (unsigned int i = 0; i < mClues.size(); i++)
	{
		mClues[i]->draw(window);
	}
}

void Clue::add(ResourceHandler &handler, string textureName, sf::Vector2f &position)
{
	mClues.push_back(new InternalClue(handler, textureName, position));
}

Clue::InternalClue* Clue::getClue(int index)
{
	return mClues[index];
}

void Clue::setCluesPosition(sf::Vector2f viewCenter)
{
	//viewCenter.x - (512 - distance from left edge of screen)

	for (ClueVector::size_type i = 0; i < mClues.size(); i++)
	{
		mClues[i]->setXPosition(viewCenter.x - (512 - mClues[i]->getXPosition()));
		mClues[i]->setTextPosition(viewCenter.x - (512 - 343));
	}

	mBackground.setPosition(viewCenter.x - 512, 0);
}
