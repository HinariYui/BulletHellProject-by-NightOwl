#include "Spawner.h"
#include "Game.h"

#define MID_PLAYAREA_X -212
#define LEFT_PLAYAREA_X -462

Spawner::Spawner()
{

}

void Spawner::update(float deltaTime)
{
	spawnRate += deltaTime;
	EnemySpawn(2500);
}

void Spawner::EnemySpawn(float rate)
{
	if (spawnRate >= rate)
	{
		int x = rand() % 500 + LEFT_PLAYAREA_X;
		Enemy1 * enemy = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
		enemy->setRotation(180);													   //boss->setColor(1.0, 0.0, 0.0);
		enemy->setSize(35, 35);
		enemy->setPosition(glm::vec3(x, 400, 0));
		//objects.push_back(enemy);
		Game::getInstance()->getObjectRef()->push_back(enemy);
		spawnRate = 0;
	}
}