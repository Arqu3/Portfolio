#include "Menu.h"

using namespace std;

Menu::Menu(ResourceHandler &handler):
mMainButtons(),
mExitButtons(),
mState(Main)
{
	//mBackground.setSize(sf::Vector2f(1024, 576));
	//mBackground.setTexture(handler.getTexture("MainMenuBackground.png"));

	////Adds main menu buttons
	//mMainButtons.push_back(new Button(200, 100, sf::Color::Red));
	//mMainButtons.push_back(new Button(200, 100, sf::Color::Blue));
	//mMainButtons.push_back(new Button(200, 100, sf::Color::Green));

	//for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
	//{
	//	mMainButtons[i]->setPosition(512.0f - mMainButtons[0]->getRect().width / 2, 100.0f + (160.0f * i));
	//}

	//mExitButtons.push_back(new Button(200, 100, sf::Color::Red));
	//mExitButtons.push_back(new Button(200, 100, sf::Color::Green));

	//for (ButtonVector::size_type i = 0; i < mExitButtons.size(); i++)
	//{
	//	mExitButtons[i]->setPosition(512.0f - mExitButtons[0]->getRect().width + (260.0f * i), 288);
	//}
}

Menu::~Menu()
{
	mMainButtons.clear();
	mExitButtons.clear();
}

void Menu::update(float deltaTime)
{
	switch (mState)
	{
	case Menu::Main:
		for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
		{
			mMainButtons[i]->update(deltaTime);
		}
		break;

	case Menu::Exit:
		for (ButtonVector::size_type i = 0; i < mExitButtons.size(); i++)
		{
			mExitButtons[i]->update(deltaTime);
		}
		break;

	default:
		break;
	}
}

void Menu::eventListen(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			switch (mState)
			{
			case Menu::Main:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;

			case Menu::Exit:
				if (event.key.code == sf::Keyboard::Escape)
				{
					setState(InGame);
				}
				break;
			}
			break;

		case sf::Event::MouseButtonPressed:
			switch (mState)
			{
			case Menu::Main:
				if (mMainButtons[0]->isPressed(window))
				{
					setState(InGame);
				}

				if (mMainButtons[2]->isPressed(window))
				{
					window.close();
				}
				break;

			case Menu::Exit:
				if (mExitButtons[0]->isPressed(window))
				{
					setState(Main);
				}
				if (mExitButtons[1]->isPressed(window))
				{
					setState(InGame);
				}
				break;
			}
			break;
		}
	}
}

void Menu::draw(sf::RenderWindow &window)
{
	switch (mState)
	{
	case Menu::Main:
		window.draw(mBackground);
		for (ButtonVector::size_type i = 0; i < mMainButtons.size(); i++)
		{
			mMainButtons[i]->draw(window);
		}
		break;

	case Menu::Exit:
		for (ButtonVector::size_type i = 0; i < mExitButtons.size(); i++)
		{
			mExitButtons[i]->draw(window);
		}
		break;

	default:
		break;
	}
}

Menu::State Menu::getState()
{
	return mState;
}

void Menu::setState(Menu::State state)
{
	mState = state;
}