#include <iostream>
#include <ctime>
#include "Enemy1.h"



Enemy1::Enemy1(Tag enemy, string fileName, int row, int col) : SpriteObject(fileName, row, col)
{
	tag = enemy;
	state = MOVE;
	setVelocity(glm::vec3(0, -2, 0));
	hp = 1;
}

void Enemy1::update(float deltaTime)
{ 
	GameObject::update(deltaTime);
	if (state == MOVE)
	{
		updateMOVE(deltaTime);
	}
	else if (state == ATK)
	{
		updateATK(deltaTime);
	}
	else if (state == EXIT)
	{
		updateEXIT(deltaTime);
	}
}

void Enemy1::updateMOVE(float deltaTime)
{
	float y = getPosition().y;
	if (y <= 0)
	{
		state = ATK;
		setVelocity(glm::vec3(0, 0, 0));
	}
}

void Enemy1::updateATK(float deltaTime)
{
	stateTime += deltaTime;
	if (stateTime >= 1000)
	{
		stateTime = 0;
		shoot1();
		state = EXIT;
	}
}

void Enemy1::updateEXIT(float deltaTime)
{
	float y = getPosition().y;
	stateTime += deltaTime;
	if (stateTime >= 1000)
	{
		stateTime = 0;
		setVelocity(glm::vec3(0, 2, 0));
	}
	if (y >= 400)
	{
		hp = 0;
	}
}

void Enemy1::shoot1()
{
	enemyBullet1 = new EnemyBullet(Tag::eBullet);

	dynamic_cast<GameObject*>(enemyBullet1)->setColor(1.0, 0.0, 0.0);
	enemyBullet1->setSize(10, 10);
	enemyBullet1->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	Game::getInstance()->getObjectRef()->push_back(enemyBullet1);
}

void Enemy1::move()
{

}

Enemy1::~Enemy1()
{
	if (enemyBullet1 != NULL)
	{
		delete enemyBullet1;
	}
}