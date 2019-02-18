#include <iostream>
#include <ctime>
#include "Enemy1.h"
#include "Game.h"

Enemy1::Enemy1(Tag enemy, string fileName, int row, int col) : EnemyBase(enemy, fileName, row, col)
{
	tag = enemy;
	state = MOVE;
	setVelocity(glm::vec3(0, -2, 0));
	hp = 1;
	bulletSpeed = 5.0f;
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
	if (y <= 100)
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
	glm::vec3 ePos = this->getPosition();
	glm::vec3 pPos = Game::getInstance()->getPlayerRef()->getPosition();

	DrawableObject* enemyBullet1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	dynamic_cast<GameObject*>(enemyBullet1)->setColor(1.0, 0.0, 0.0);
	enemyBullet1->setSize(10, 10);
	enemyBullet1->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	glm::vec3 temp = glm::normalize(pPos - ePos);
	glm::vec4 bulDir(temp.x, temp.y, temp.z, 1);
	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, 7.5f / 180.0f * 3.14f, glm::vec3(0.0f, 0.0f, 1.0f));
	bulDir = rotationMatrix * bulDir;
	glm::vec3 realBulDir1 = glm::vec3(bulDir.x, bulDir.y, bulDir.z);

	dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(realBulDir1 * bulletSpeed);
	
	Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

	DrawableObject* enemyBullet2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	dynamic_cast<GameObject*>(enemyBullet2)->setColor(1.0, 0.0, 0.0);
	enemyBullet2->setSize(10, 10);
	enemyBullet2->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	bulDir = glm::vec4(temp.x, temp.y, temp.z, 1);
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, -7.5f / 180.0f * 3.14f, glm::vec3(0.0f, 0.0f, 1.0f));
	bulDir = rotationMatrix * bulDir;
	glm::vec3 realBulDir2 = glm::vec3(bulDir.x, bulDir.y, bulDir.z);

	dynamic_cast<GameObject*>(enemyBullet2)->setVelocity(realBulDir2 * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet2);

	DrawableObject* enemyBullet3 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	dynamic_cast<GameObject*>(enemyBullet3)->setColor(1.0, 0.0, 0.0);
	enemyBullet3->setSize(10, 10);
	enemyBullet3->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	bulDir = glm::vec4(temp.x, temp.y, temp.z, 1);
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, 22.5f / 180.0f * 3.14f, glm::vec3(0.0f, 0.0f, 1.0f));
	bulDir = rotationMatrix * bulDir;
	glm::vec3 realBulDir3 = glm::vec3(bulDir.x, bulDir.y, bulDir.z);

	dynamic_cast<GameObject*>(enemyBullet3)->setVelocity(realBulDir3 * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet3);

	DrawableObject* enemyBullet4 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	dynamic_cast<GameObject*>(enemyBullet4)->setColor(1.0, 0.0, 0.0);
	enemyBullet4->setSize(10, 10);
	enemyBullet4->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	bulDir = glm::vec4(temp.x, temp.y, temp.z, 1);
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, -22.5f / 180.0f * 3.14f, glm::vec3(0.0f, 0.0f, 1.0f));
	bulDir = rotationMatrix * bulDir;
	glm::vec3 realBulDir4 = glm::vec3(bulDir.x, bulDir.y, bulDir.z);

	dynamic_cast<GameObject*>(enemyBullet4)->setVelocity(realBulDir4 * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet4);
}

void Enemy1::move()
{

}

Enemy1::~Enemy1()
{
	
}