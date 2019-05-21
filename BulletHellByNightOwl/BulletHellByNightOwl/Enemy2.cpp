#include <iostream>
#include <ctime>
#include "Enemy2.h"
#include "Game.h"

#define MID_PLAYAREA_X -212
#define LEFT_PLAYAREA_X -462
#define RIGHT_PLAYAREA_X 38
#define TOP_PLAYAREA_Y 330
#define BOTTOM_PLAYAREA_Y -330

Enemy2::Enemy2(Tag enemy, string fileName, int row, int col) : EnemyBase(enemy, fileName, row, col)
{
	tag = enemy;
	state = MOVE;
	setVelocity(glm::vec3(0, 0, 0));
	hp = 10;
	bulletSpeed = 5.0f;
}

void Enemy2::update(float deltaTime)
{
	GameObject::update(deltaTime);
	if(isInPlayArea())
	{
		updateATK(deltaTime);
	}
	if (getPosition().x <= -1000 || getPosition().x >= 425 || getPosition().y <= -1000 || getPosition().y >= 1000)
	{
		setRender(false);
	}
	else
	{
		setRender(true);
	}
	if (getPosition().x <= -2000 || getPosition().x >= 1000 || getPosition().y <= -1000 || getPosition().y >= 1000)
	{
		hp = 0;
	}
	//if (state == MOVE)
	//{
	//	updateMOVE(deltaTime);
	//}
	else if (state == ATK)
	{
		updateATK(deltaTime);
	}
	else if (state == EXIT)
	{
		updateEXIT(deltaTime);
	}
}

void Enemy2::updateMOVE(float deltaTime)
{
	//float y = getPosition().y;
	//if (y <= 100)
	//{
	//	state = ATK;
	//	//setVelocity(glm::vec3(0, 0, 0));
	//}
}

void Enemy2::updateATK(float deltaTime)
{
	shootCD += deltaTime;
	if (shootCD >= 150)
	{
		shoot1();
		shootCD = 0;
	}
}

void Enemy2::updateEXIT(float deltaTime)
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

void Enemy2::Behavior1()
{

}

void Enemy2::shoot1()
{
	glm::vec3 ePos = this->getPosition();
	glm::vec3 pPos = Game::getInstance()->getPlayerRef()->getPosition();

	DrawableObject* enemyBullet1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	enemyBullet1->setSize(10, 10);
	enemyBullet1->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	glm::vec3 bulDir = glm::normalize(pPos - ePos);

	dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet1);
}

bool Enemy2::isInPlayArea()
{
	if (getPosition().x >= LEFT_PLAYAREA_X + 10 && getPosition().x <= RIGHT_PLAYAREA_X - 10 && getPosition().y >= BOTTOM_PLAYAREA_Y + 10 && getPosition().y <= TOP_PLAYAREA_Y - 10)
	{
		return true;
	}
	return false;
}

void Enemy2::move()
{

}

Enemy2::~Enemy2()
{

}