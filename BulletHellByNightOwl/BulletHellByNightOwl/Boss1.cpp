#include <iostream>
#include "Boss1.h"
#include "EnemyBullet.h"


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
	shootCD++;
	if (shootCD >= 10)//shoot every 10 frame
	{
		shoot();
		shootCD = 0;
	}
}

void Boss1::shoot()
{
	enemyBullet = new EnemyBullet(Tag::eBullet);

	dynamic_cast<GameObject*>(enemyBullet)->setColor(1.0, 0.0, 0.0);
	enemyBullet->setSize(10, 10);
	enemyBullet->setPosition(this->getPosition() + glm::vec3(0, -26, 0));

	Game::getInstance()->getObjectRef()->push_back(enemyBullet);
}

void Boss1::move()
{

}

Boss1::~Boss1()
{
	if (enemyBullet != NULL)
	{
		delete enemyBullet;
	}
}
