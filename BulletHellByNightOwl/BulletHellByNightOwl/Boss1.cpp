#include <iostream>
#include "Boss1.h"



void Boss1::update(float deltaTime)
{
	if (getVelocity() != glm::vec3(0, 0, 0))
	{
		translate(glm::normalize(getVelocity()) * 3.0f);
	}
	resetVelocityZ();

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
}

void Boss1::shoot()
{
	enemyBullet = new BulletGameObject(Tag::eBullet);

	dynamic_cast<GameObject*>(enemyBullet)->setColor(1.0, 0.0, 0.0);
	enemyBullet->setSize(10, 10);
	enemyBullet->setPosition(this->getPosition() + glm::vec3(0, -26, 0));
}

void Boss1::move()
{

}

Boss1::~Boss1()
{
	//if (playerBullet != NULL)
	//{
	//	delete playerBullet;
	//}
}
