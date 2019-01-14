#include <iostream>
#include "Boss1.h"
#include "EnemyBullet.h"
#include "Game.h"



Boss1::Boss1(Tag enemy, string fileName, int row, int col) : SpriteObject(fileName, row, col)
{
	setVelocity(glm::vec3(0, -1, 0));
	tag = enemy;
	state = MOVEIN;
	idleTime = rand() % 1000 + 2000;
	stateTime = 0;
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, 0.25f, glm::vec3(0.0f, 0.0f, 1.0f)); //0.1f -> radiant
	hp = maxHP;
	HPbar = new GameObject(NONE);

	HPbar->setSize(HPsize, 20);
	HPbar->setPosition(glm::vec3(HPpos, 340, 0));
	HPbar->setColor(1, 0.85, 0);
}

void Boss1::update(float deltaTime)
{
	HPpercentage = (float)hp / (float)maxHP;
	HPbar->setSize(HPsize * HPpercentage, 20);
	missingHP = (float)maxHP - (float)hp;
	HPbar->setPosition(glm::vec3(HPpos - missingHP/4, 340, 0));
	GameObject::update(deltaTime);

	if (state == IDLE)
	{
		updateIDLE(deltaTime);
	}
	else if (state == MOVEIN)
	{
		updateMoveIn(deltaTime);
		hp = maxHP;
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

void Boss1::updateMoveIn(float deltaTime)
{
	float y = getPosition().y;
	if (y <= 200)
	{
		state = IDLE;
		setVelocity(glm::vec3(0, 0, 0));
	}
}

void Boss1::updateATK1(float deltaTime)
{
	stateTime += deltaTime;
	ATKCount += deltaTime;
	if (ATKCount >= 30)//shoot every 0.03 sec
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
	EnemyBullet *eb1 = dynamic_cast<EnemyBullet*>(enemyBullet1);
	if (eb1)
	{
		eb1->setColor(1.0, 0.0, 0.0);
		eb1->setSize(10, 10);
		eb1->setPosition(this->getPosition());
		eb1->setVelocity(velD);
		glm::vec4 temp(velD.x, velD.y, velD.z, 1);
		temp = rotationMatrix * temp;
		velD.x = temp.x;
		velD.y = temp.y;
		velD.z = temp.z;
	}
	Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

	enemyBullet2 = new EnemyBullet(Tag::eBullet);
	EnemyBullet *eb2 = dynamic_cast<EnemyBullet*>(enemyBullet2);
	if (eb2)
	{
		eb2->setColor(1.0, 0.0, 0.0);
		eb2->setSize(10, 10);
		eb2->setPosition(this->getPosition());
		eb2->setVelocity(velR);
		glm::vec4 temp(velR.x, velR.y, velR.z, 1);
		temp = rotationMatrix * temp;
		velR.x = temp.x;
		velR.y = temp.y;
		velR.z = temp.z;
	}
	Game::getInstance()->getObjectRef()->push_back(enemyBullet2);

	enemyBullet3 = new EnemyBullet(Tag::eBullet);
	EnemyBullet *eb3 = dynamic_cast<EnemyBullet*>(enemyBullet3);
	if (eb3)
	{
		eb3->setColor(1.0, 0.0, 0.0);
		eb3->setSize(10, 10);
		eb3->setPosition(this->getPosition());
		eb3->setVelocity(velU);
		glm::vec4 temp(velU.x, velU.y, velU.z, 1);
		temp = rotationMatrix * temp;
		velU.x = temp.x;
		velU.y = temp.y;
		velU.z = temp.z;
	}
	Game::getInstance()->getObjectRef()->push_back(enemyBullet3);

	enemyBullet4 = new EnemyBullet(Tag::eBullet);
	EnemyBullet *eb4 = dynamic_cast<EnemyBullet*>(enemyBullet4);
	if (eb4)
	{
		eb4->setColor(1.0, 0.0, 0.0);
		eb4->setSize(10, 10);
		eb4->setPosition(this->getPosition());
		eb4->setVelocity(velL);
		glm::vec4 temp(velL.x, velL.y, velL.z, 1);
		temp = rotationMatrix * temp;
		velL.x = temp.x;
		velL.y = temp.y;
		velL.z = temp.z;
	}
	Game::getInstance()->getObjectRef()->push_back(enemyBullet4);
}

void Boss1::move()
{

}


void Boss1::render(glm::mat4 globalModelTransform)
{
	SpriteObject::render(globalModelTransform);
	if (state != MOVEIN)
	{
		HPbar->render(globalModelTransform);
	}
}

Boss1::~Boss1()
{
	if (enemyBullet1 != NULL)
	{
		delete enemyBullet1;
	}
}
