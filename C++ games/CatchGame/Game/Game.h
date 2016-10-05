#ifndef INCLUDED_GAME
#define INCLUDED_GAME

#include "Player.h"
#include "Block.h"
#include "EntityDecorator.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <time.h>

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	typedef std::vector<Entity*> EntityVector;
	EntityVector mEntities;

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	void detectCollisions();
	void removeDeadEntities();
	void visibilityCheck();

	void addBlocks();
	float bSpawnInterval;
	float bSpawnTimer;

	void loadPlayer();
	Player *mPlayer;

	sf::Clock deltaClock;
	int difficulty;

	void destroy();
};

#endif