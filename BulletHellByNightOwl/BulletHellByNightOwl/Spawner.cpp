#include "Spawner.h"

#define MID_PLAYAREA_X -212

void Spawner::update(float deltaTime)
{
	spawnRate += deltaTime;
	EnemySpawn(2500);
}

void Spawner::EnemySpawn(float rate)
{
	if (spawnRate >= rate)
	{
		int x = rand() % 300 - MID_PLAYAREA_X - 462;
		Enemy1 * enemy = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
		enemy->setRotation(180);													   //boss->setColor(1.0, 0.0, 0.0);
		enemy->setSize(35, 35);
		enemy->setPosition(glm::vec3(x, 300, 0));
		//objects.push_back(enemy);
		Game::getInstance()->getObjectRef()->push_back(enemy);
		spawnRate = 0;
	}
}