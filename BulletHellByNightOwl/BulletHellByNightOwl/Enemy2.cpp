#include <iostream>
#include <ctime>
#include "Enemy2.h"
#include "Game.h"


Enemy2::Enemy2(Tag enemy, string fileName, int row, int col) : SpriteObject(fileName, row, col)
{
	tag = enemy;
	state = MOVE;
	setVelocity(glm::vec3(0, -2, 0));
	hp = 1;
	bulletSpeed = 5.0f;
}

void Enemy2::update(float deltaTime)
{
	GameObject::update(deltaTime);
	if(getPosition().y <= 200 && getPosition().y >= -200)
	{
		updateATK(deltaTime);
	}
	if (getPosition().y <= -400)
	{
		hp = 0;
	}
	//if (state == Enemy2State::MOVE)
	//{
	//	updateMOVE(deltaTime);
	//}
	//else if (state == Enemy2State::ATK)
	//{
	//	updateATK(deltaTime);
	//}
	//else if (state == Enemy2State::EXIT)
	//{
	//	updateEXIT(deltaTime);
	//}
}

//void Enemy2::updateMOVE(float deltaTime)
//{
//	float y = getPosition().y;
//	if (y <= 100)
//	{
//		state = Enemy2State::ATK;
//		setVelocity(glm::vec3(0, 0, 0));
//	}
//}
//
void Enemy2::updateATK(float deltaTime)
{
	stateTime += deltaTime;
	if (stateTime >= 50)
	{
		stateTime = 0;
		shoot1();
		//state = EXIT;
	}
}
//
//void Enemy2::updateEXIT(float deltaTime)
//{
//	float y = getPosition().y;
//	stateTime += deltaTime;
//	if (stateTime >= 1000)
//	{
//		stateTime = 0;
//		setVelocity(glm::vec3(0, 2, 0));
//	}
//	if (y >= 400)
//	{
//		hp = 0;
//	}
//}

void Enemy2::Behavior1()
{

}

void Enemy2::shoot1()
{
	glm::vec3 ePos = this->getPosition();
	glm::vec3 pPos = Game::getInstance()->getPlayerRef()->getPosition();

	DrawableObject* enemyBullet1 = new EnemyBullet(Tag::eBullet);

	dynamic_cast<GameObject*>(enemyBullet1)->setColor(1.0, 0.0, 0.0);
	enemyBullet1->setSize(10, 10);
	enemyBullet1->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	glm::vec3 bulDir = glm::normalize(pPos - ePos);

	dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir * bulletSpeed);
}

void Enemy2::move()
{

}

Enemy2::~Enemy2()
{

}