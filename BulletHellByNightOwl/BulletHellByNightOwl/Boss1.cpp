#include <iostream>
#include "Boss1.h"
#include "EnemyBullet.h"
#include "Game.h"



Boss1::Boss1(Tag enemy, string fileName, int row, int col) : SpriteObject(fileName, row, col)
{
	tag = enemy;
	state = IDLE;
	idleTime = rand() % 1000 + 2000;
	stateTime = 0;
}

void Boss1::update(float deltaTime)
{
	//Game*  g = Game::getInstance();
	//GLuint objNum = g->getObjectRef()->size();
	//GameObject* obj = NULL;
	//
	//obj = dynamic_cast<GameObject*>(g->getObjectRef()->at(7)); // enemy index=7
	//
	//if (this->getTag() != obj->getTag())
	//{
	//	bool b = checkCollision(obj);
	//}
	GameObject::update(deltaTime);
	//shootCD++;
	//if (shootCD >= 10)//shoot every 10 frame
	//{
	//	shoot1();
	//	shootCD = 0;
	//}
	if (state == IDLE)
	{
		updateIDLE(deltaTime);
	}
	else if (state == ATK1)
	{
		updateATK1(deltaTime);
	}
	else if (state == ATK2)
	{
		updateATK2(deltaTime);
	}
	else if (state == ATK3)
	{
		updateATK3(deltaTime);
	}
}

void Boss1::updateIDLE(float deltaTime)
{
	stateTime += deltaTime;
	if (stateTime >= idleTime)
	{
		stateTime = 0;
		state = ATK1;
	}
}

void Boss1::updateATK1(float deltaTime)
{
	stateTime += deltaTime;
	ATKCount += deltaTime;
	if (ATKCount >= 50)//shoot every 0.05 sec
	{
		shoot1();
		ATKCount = 0;
	}
	if (stateTime >= 4000)
	{
		stateTime = 0;
		state = IDLE;
		idleTime = rand() % 1000 + 2000;
	}
}

void Boss1::updateATK2(float deltaTime)
{

}

void Boss1::updateATK3(float deltaTime)
{

}

void Boss1::shoot1()
{
	enemyBullet1 = new EnemyBullet(Tag::eBullet);

	dynamic_cast<GameObject*>(enemyBullet1)->setColor(1.0, 0.0, 0.0);
	enemyBullet1->setSize(10, 10);
	enemyBullet1->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	Game::getInstance()->getObjectRef()->push_back(enemyBullet1);
}

void Boss1::move()
{

}

Boss1::~Boss1()
{
	if (enemyBullet1 != NULL)
	{
		delete enemyBullet1;
	}
}
