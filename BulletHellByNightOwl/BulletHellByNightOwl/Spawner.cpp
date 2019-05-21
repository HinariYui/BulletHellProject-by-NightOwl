#include "Spawner.h"
#include "Game.h"

#define MID_PLAYAREA_X -212
#define LEFT_PLAYAREA_X -462
#define RIGHT_PLAYAREA_X 38

Spawner::Spawner()
{
}

void Spawner::update(float deltaTime)
{
	spawnCD += deltaTime;
	EnemySpawn(spawnRate);
}

void Spawner::EnemySpawn(float rate)
{
	if (spawnCD >= rate)
	{
		if (eNum != 10)
		{
			int x = rand() % 500 + LEFT_PLAYAREA_X;
			Enemy1 * enemy = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy->setRotation(180);
			enemy->setSize(35, 35);
			enemy->setPosition(glm::vec3(x, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy);
		}
		spawnCD = 0;
		eNum++;
	}
}

void Spawner::EnemySpawn(int i)
{
	pattern = i;
	switch (pattern)
	{
		case(1):
		{
			Enemy2* enemy1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(LEFT_PLAYAREA_X - 20, 300, 0));
			enemy1->setVelocity(normalize(glm::vec3(7, -6, 0)) * 1.5f);
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			break;
		}
		case(2):
		{
			Enemy1 * enemy1 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			Enemy1 * enemy2 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy2->setRotation(180);
			enemy2->setSize(35, 35);
			enemy2->setPosition(glm::vec3(MID_PLAYAREA_X, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy2);

			Enemy1 * enemy3 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy3->setRotation(180);
			enemy3->setSize(35, 35);
			enemy3->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy3);

			break;
		}
	}
}

void Spawner::SetSpawnRate(float rate)
{
	spawnRate = rate;
}