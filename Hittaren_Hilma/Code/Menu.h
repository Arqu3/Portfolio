#ifndef INCLUDED_MENU
#define INCLUDED_MENU

#include "Button.h"

class Menu
{
public:
	Menu(ResourceHandler &handler);
	~Menu();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	void eventListen(sf::RenderWindow &window);

	enum State
	{
		Main,
		InGame,
		Exit
	};
	State mState;

	State getState();
	void setState(State state);

private:
	//typedef std::vector<Button*> ButtonVector;
	//ButtonVector mMainButtons;
	//ButtonVector mExitButtons;
	//sf::RectangleShape mBackground;
};

#endif