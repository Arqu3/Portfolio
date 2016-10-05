#ifndef INCLUDED_GAME
#define INCLUDED_GAME

#include <string>
#include <vector>
#include "VGCVirtualGameConsole.h"
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Menu.h"

class Game
{
public:
	Game();
	~Game();
	void start();

private:
	void update();
	void render();
	void addEnemies();
	void destroy();
	void removeDeadEntities();
	void detectCollisions();
	void handleStates();
	void menuHandler();
	void load();

	bool isOverlap(Entity *entity0, Entity *entity1);

	//Ship reference
	Ship *ship;

	//Menu reference
	Menu *menu;

	typedef std::vector<Entity*> EntityVector;
	EntityVector mEntities;

	float spawnTimer;
	float spawnInterval;

	enum GameState
	{
		InGame,
		Paused,
		MainMenu,
		Over
	};
	GameState mCurrentState;
	bool isPaused;
	bool endGame;
};

#endif