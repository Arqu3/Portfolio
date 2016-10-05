#include "Menu.h"

using namespace std;

VGCColor red(255, 255, 0, 0);
VGCColor white(255, 255, 255, 255);

Menu::Menu() :
	mBlinkTimer(0.0f),
	mIsvisible(true)
{
}

Menu::~Menu()
{
}

void Menu::update()
{
	//Update text blinking timer
	mBlinkTimer++;
	if (mBlinkTimer >= 60.0f)
	{
		mBlinkTimer = 0.0f;
	}
	if (mBlinkTimer >= 60.0f || mBlinkTimer < 15.0f)
	{
		mIsvisible = false;
	}
	else
	{
		mIsvisible = true;
	}
}

void Menu::renderMainMenu()
{
	//Title
	VGCVector titlePosition(VGCDisplay::getWidth() / 2, 200);
	VGCAdjustment titleAdjustment(0.5, 0.5);

	//Instructions
	VGCVector instrPosition(VGCDisplay::getWidth() / 2, 300);
	VGCAdjustment instrAdjustment(0.3, 0.3);

	//Start
	VGCVector startPosition(VGCDisplay::getWidth() / 2, 500);
	VGCAdjustment startAdjustment(0.5, 0.5);

	static const int fontSize = 30;
	VGCFont font = VGCDisplay::openFont("Arial", fontSize);

	//Render title
	const string titleText = "Project: INVADER";
	VGCDisplay::renderString(font, titleText, white, titlePosition, titleAdjustment);

	//Render instructions
	const string instrText = "W A S D to move \nSPACE to shoot \nESCAPE to pause/unpause";
	VGCDisplay::renderString(font, instrText, white, instrPosition, instrAdjustment);

	//Render start
	const string startText = "ENTER to start";
	if (mIsvisible == true)
	{
		VGCDisplay::renderString(font, startText, red, startPosition, startAdjustment);
	}

	VGCDisplay::closeFont(font);
}

void Menu::renderPause()
{
	//Title
	VGCVector titlePosition(VGCDisplay::getWidth() / 2, 200);
	VGCAdjustment titleAdjustment(0.5, 0.5);

	//Unpause
	VGCVector unPPosition(VGCDisplay::getWidth() / 2, 300);
	VGCAdjustment unPAdjustment(0.5, 0.5);

	//Exit to main menu
	VGCVector mainMPosition(VGCDisplay::getWidth() / 2, 400);
	VGCAdjustment mainMAdjustment(0.5, 0.5);

	static const int fontSize = 30;
	VGCFont font = VGCDisplay::openFont("Arial", fontSize);

	//Render title
	const string titleText = "GAME PAUSED";
	VGCDisplay::renderString(font, titleText, white, titlePosition, titleAdjustment);

	//Render unpause
	const string unpauseText = "ESCAPE to unpause";
	if (mIsvisible == true)
	{
		VGCDisplay::renderString(font, unpauseText, red, unPPosition, unPAdjustment);
	}

	//Render exit to main menu
	const string mainMText = "Q to exit to main menu";
	VGCDisplay::renderString(font, mainMText, white, mainMPosition, mainMAdjustment);

	VGCDisplay::closeFont(font);
}

void Menu::renderGameOver()
{
	//Title
	VGCVector titlePosition(VGCDisplay::getWidth() / 2, 200);
	VGCAdjustment titleAdjustment(0.5, 0.5);

	//Instructions
	VGCVector instrPosition(VGCDisplay::getWidth() / 2, 300);
	VGCAdjustment instrAdjustment(0.5, 0.5);

	VGCVector retryPosition(VGCDisplay::getWidth() / 2, 360);

	static const int fontSize = 40;
	VGCFont font = VGCDisplay::openFont("Arial", fontSize);

	//Render title
	const string titleText = "GAME OVER";
	VGCDisplay::renderString(font, titleText, red, titlePosition, titleAdjustment);

	//Render instructions
	const string instrText = "Q to exit to main menu";
	VGCDisplay::renderString(font, instrText, white, instrPosition, instrAdjustment);

	//Render Retry text
	const string retryText = "R to retry";
	if (mIsvisible == true)
	{
		VGCDisplay::renderString(font, retryText, red, retryPosition, instrAdjustment);
	}

	VGCDisplay::closeFont(font);
}