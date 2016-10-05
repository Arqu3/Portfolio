#include "Game.h"

using namespace std;

//FPS and update time
static const double FPS = 60;
static const double updateT = 1.0 / FPS;

Game::Game() :
	mEntities(),
	mCurrentState(MainMenu),
	isPaused(false),
	endGame(false),
	spawnTimer(0.0f),
	spawnInterval(50.0f)
{
	Ship::initialize();
	Bullet::initialize();
	Enemy::initialize();
	Explosion::initialize();
	menu = new Menu();
}


Game::~Game()
{
	Ship::finalize();
	Bullet::finalize();
	Enemy::finalize();
	Explosion::finalize();
	VGCVirtualGameConsole::finalize();
}

void Game::start()
{
	//Open timer
	VGCTimer timer = VGCClock::openTimer(updateT);

	while (endGame == false && VGCVirtualGameConsole::beginLoop())
	{
		//Update objects
		VGCClock::reset(timer);
		if (VGCDisplay::beginFrame())
		{
			//Clear background
			VGCColor backgroundColor(255, 0, 0, 0);
			VGCDisplay::clear(backgroundColor);

			handleStates();
			menuHandler();

			//Render objects while not in the main menu
			if (mCurrentState != MainMenu)
			{
				render();
			}
			menu->update();

			switch (mCurrentState)
			{
			case MainMenu:
				//Menu rendering
				menu->renderMainMenu();
				break;

			case InGame:
				//Update entities
				detectCollisions();
				update();
				removeDeadEntities();
				break;

			case Paused:
				//Pause rendering
				menu->renderPause();
				break;

			case Over:
				//Game over rendering
				menu->renderGameOver();
				break;
			}

			VGCDisplay::endFrame();
		}
		VGCVirtualGameConsole::endLoop();
		VGCClock::wait(timer);
	}

	VGCClock::closeTimer(timer);
	destroy();
}

void Game::handleStates()
{
	//Update only if player is alive
	if (mCurrentState == InGame)
	{
		if (!ship->isAlive())
		{
			mCurrentState = Over;
		}
	}

	if (mCurrentState == Over)
	{
		//Exit to menu when pressing escape
		if (VGCKeyboard::wasPressed(VGCKey::Q_KEY))
		{
			mCurrentState = MainMenu;
		}
		//Reload game when pressing R
		if (VGCKeyboard::wasPressed(VGCKey::R_KEY))
		{
			//destroy();
			load();
			mCurrentState = InGame;
		}
	}

	//Toggle game pause
	if (mCurrentState == Paused || mCurrentState == InGame)
	{
		//Can only toggle if InGame or Paused
		if (VGCKeyboard::wasPressed(VGCKey::ESCAPE_KEY))
		{
			isPaused = !isPaused;
		}
		//Switch states
		if (isPaused == true)
		{
			mCurrentState = Paused;
		}
		else
		{
			mCurrentState = InGame;
		}
	}
	//Exit to main menu if paused & pressed Q
	if (mCurrentState == Paused)
	{
		if (VGCKeyboard::wasPressed(VGCKey::Q_KEY))
		{
			//Create new menu
			menu = new Menu();
			mCurrentState = MainMenu;
			isPaused = false;
		}
	}
}

void Game::menuHandler()
{
	if (mCurrentState == MainMenu)
	{
		//Start game when pressing Enter
		if (VGCKeyboard::wasPressed(VGCKey::RETURN_KEY))
		{
			//Load new ship on startup
			load();
			mCurrentState = InGame;
		}
		//Close program when pressing Escape
		if (VGCKeyboard::wasPressed(VGCKey::ESCAPE_KEY))
		{
			endGame = true;
		}
	}

}

void Game::load()
{
	//Empty vector before loading new ship
	while (!mEntities.empty())
	{
		mEntities.pop_back();
	}
	ship = new Ship(VGCVector(VGCDisplay::getWidth() / 2, VGCDisplay::getHeight() / 2));
	mEntities.push_back(ship);
}

void Game::update()
{
	//Update all entities
	EntityVector entities(mEntities);
	for (EntityVector::iterator i = entities.begin(); i != entities.end(); i++)
	{
		Entity *entity = *i;
		entity->update(mEntities);
	}

	//Add enemies
	addEnemies();
}

void Game::render()
{
	//Render all entities
	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end(); i++)
	{
		Entity *entity = *i;
		entity->render();
	}
	//Render UI last
	ship->renderText();
}

void Game::addEnemies()
{
	//Timer tick and reset
	spawnTimer++;
	if (spawnTimer >= spawnInterval)
	{
		spawnTimer = 0.0f;
	}

	VGCRandomizer::initializeRandomizer();

	//Randomize starting position and starting direction
	int posX = VGCRandomizer::getInt(0 + 16, VGCDisplay::getWidth() - 16);
	int direction = VGCRandomizer::getInt(0, 1);
	VGCVector pos(posX, -20);
	float bulletCD(0.0f);

	//Add enemies
	if (spawnTimer == 0.0f)
	{
		mEntities.push_back(new Enemy(pos, direction, bulletCD));
	}

	VGCRandomizer::finalizeRandomizer();
}

void Game::removeDeadEntities()
{
	//Remove each entity that returns isAlive() = false
	EntityVector entities;
	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end(); i++)
	{
		Entity *entity = *i;
		if (entity->isAlive())
		{
			entities.push_back(entity);
		}
		else
		{
			if (entity != ship)
			{
				delete entity;
			}
		}
	}
	mEntities = entities;
}

void Game::detectCollisions()
{
	EntityVector entities(mEntities);
	for (EntityVector::size_type i = 0; i < entities.size(); i++)
	{
		Entity *entity0 = entities[i];
		for (EntityVector::size_type j = i + 1; j < entities.size(); j++)
		{
			Entity *entity1 = entities[j];
			//If entities overlap & they don't share type or are bullets
			if (isOverlap(entity0, entity1) 
				&& entity0->getType() != entity1->getType())
			{
				//Enemy + Ship collision
				if (entity0->mIsBullet == false && entity1->mIsBullet == false)
				{
					ship->damageTaken = entity0->getDamage() + entity1->getDamage();
					entity0->takeDMG();
					entity1->takeDMG();
					ship->addScore(entity0->getScore() + entity1->getScore());
				}
				//Enemy + Bullet or Ship + Bullet collision
				if (entity0->mIsBullet != entity1->mIsBullet)
				{
					ship->damageTaken = entity0->getDamage() + entity1->getDamage();
					entity0->takeDMG();
					entity1->takeDMG();
					ship->addScore(entity0->getScore() + entity1->getScore());
				}
			}
		}
	}
}

bool Game::isOverlap(Entity *entity0, Entity *entity1)
{
	//Collision using pythagoras theorem
	const VGCVector position0 = entity0->getPosition();
	const int X0 = position0.getX();
	const int Y0 = position0.getY();
	const int R0 = entity0->getRadius();

	const VGCVector position1 = entity1->getPosition();
	const int X1 = position1.getX();
	const int Y1 = position1.getY();
	const int R1 = entity1->getRadius();

	const int DX = X0 - X1;
	const int DY = Y0 - Y1;

	return (DX * DX) + (DY * DY) < (R0 + R1) * (R0 + R1);
}

void Game::destroy()
{
	//Remove all objects before closing application
	delete menu;
	while (!mEntities.empty())
	{
		delete mEntities.back();
		mEntities.pop_back();
	}
}
