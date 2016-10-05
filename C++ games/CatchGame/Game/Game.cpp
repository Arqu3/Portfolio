#include "Game.h"

using namespace std;

const int screenW = 800;
const int screenH = 600;

Game::Game() :
mEntities(),
bSpawnInterval(250),
bSpawnTimer(0),
difficulty(0)
{
	loadPlayer();
	srand(time(NULL));
}

Game::~Game()
{

}

void Game::run()
{
	sf::RenderWindow window(sf::VideoMode(screenW, screenH), "Game");

	window.setMouseCursorVisible(false);

	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && mPlayer->isAlive())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		sf::Time elapsed = deltaClock.getElapsedTime();
		float deltaTime = elapsed.asSeconds();

		mPlayer->updateMouse(window);
		update(deltaTime);
		visibilityCheck();
		draw(window);

		detectCollisions();
		removeDeadEntities();

		deltaClock.restart();

		window.display();
	}
	destroy();
}

void Game::update(float deltaTime)
{
	addBlocks();

	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end(); i++)
	{
		Entity *entity = *i;
		entity->update(deltaTime);
	}
}

void Game::draw(sf::RenderWindow &window)
{
	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end(); i++)
	{
		Entity *entity = *i;
		entity->draw(window);
	}

	//Draw player score and lives last (text overlaps blocks, not the other way around)
	mPlayer->drawScore(window);
	mPlayer->drawHealth(window);
}

void Game::detectCollisions()
{
	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end(); i++)
	{
		Entity *entity = *i;
		if (mPlayer->getRectangle().intersects(entity->getRectangle()) && mPlayer != entity)
		{
			mPlayer->addScore(entity->getScore());
			entity->setDead();
		}
	}

}

void Game::removeDeadEntities()
{
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
			if (entity != mPlayer)
			{
				delete entity;
			}
		}
	}
	mEntities = entities;
}

void Game::visibilityCheck()
{
	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end(); i++)
	{
		Entity *entity = *i;
		if (entity->getPosition().y > 600)
		{
			mPlayer->takeDamage(entity->getDamage());
			entity->setDead();
		}
	}
}

void Game::addBlocks()
{
	int spawnSpecial;
	int random;

	//Difficuly handling based on player score
	if (mPlayer->getScore() > 80 && mPlayer->getScore() <= 175)
	{
		difficulty = 1;
	}
	if (mPlayer->getScore() > 175 && mPlayer->getScore() <= 270)
	{
		difficulty = 2;
	}
	if (mPlayer->getScore() > 270)
	{
		difficulty = 3;
	}

	int posX = rand() % screenW;
	sf::Vector2f spawnPos(posX, -40);
	sf::FloatRect spawnRect(spawnPos, sf::Vector2f(0, 0));

	bSpawnTimer += 0.1f;
	if (bSpawnTimer > bSpawnInterval)
	{
		bSpawnTimer = 0.0f;
	}

	if (bSpawnTimer == 0.0f)
	{
		//Change how blocks spawn depending on difficulty
		if (difficulty == 0)
		{
			spawnSpecial = rand() % 2 + 1;
		}
		else if (difficulty > 0)
		{
			spawnSpecial = 1;
		}

		if (difficulty == 2)
		{
			//Spawn enemies 33% faster at difficulty 2
			bSpawnInterval = 167;
		}

		if (difficulty == 3)
		{
			//Spawn enemies 50% faster at difficulty 3
			bSpawnInterval = 90.0f;
		}

	    random = rand() % 10 + 1;

		//Add special blocks
		if (spawnSpecial < 2)
		{
			if (random == 10)
			{
				mEntities.push_back(new EntityDecorator(EntityDecorator::Type::Score, (new Block(spawnPos, spawnRect))));
			}
			if (random > 5 && random < 10)
			{
				mEntities.push_back(new EntityDecorator(EntityDecorator::Type::Damage, (new Block(spawnPos, spawnRect))));
			}
			if (random > 0 && random < 8)
			{
				mEntities.push_back(new EntityDecorator(EntityDecorator::Type::Fast, (new Block(spawnPos, spawnRect))));
			}
		}
		//Add regular blocks
		else
		{
			mEntities.push_back(new Block(spawnPos, spawnRect));
		}
	}
}

void Game::loadPlayer()
{
	while (!mEntities.empty())
	{
		mEntities.pop_back();
	}
	mPlayer = new Player(sf::Vector2f(screenW / 2 - 32, screenH -50), sf::FloatRect(0, 0, 0, 0));
	mEntities.push_back(mPlayer);
}

void Game::destroy()
{
	while (!mEntities.empty())
	{
		delete mEntities.back();
		mEntities.pop_back();
	}
}