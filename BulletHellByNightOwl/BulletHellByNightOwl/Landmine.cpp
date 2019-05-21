#include "Landmine.h"
#include "Game.h"
#include <iostream>

Landmine::Landmine(Tag bulletType, string spriteFile, SpriteObject* drn) : EnemyBullet(bulletType, spriteFile)
{
	BulletGameObject::addSprite(spriteFile, 1, 3);
	BulletGameObject::setAnimationLoop(1, 1, 1, 500);
	drone = drn;
}

void Landmine::update(float deltaTime)
{
	BulletGameObject::setVelocity(glm::vec3(0));
	BulletGameObject::update(deltaTime);
	timeCounter += deltaTime;
	if (lState == L_START)
	{
		float time = timeCounter / maxStartTime;
		glm::vec3 currentPos = getPosition();
		glm::vec3 result = (currentPos * (1 - time)) + (randomLocation * time); // lerp
		//setPosition(result);
		if (timeCounter > maxStartTime)
		{
			lState = L_IDLE;
		}
	}
	if (lState == L_IDLE)
	{
		waitTimeCounter += deltaTime;
		if (waitTimeCounter > waitTime)
		{
			lState = L_EXPLODE;
		}
	}
	if (lState == L_EXPLODE)
	{
		// Delete bullet + spawn 2 normal bullet

		//setVelocity(glm::vec3(0, -10, 0));
		//float constant = deltaTime * 0.05;
		//translate(constant * velocity);

		if (lState != GONE)
		{
			float bulletSpeed = 1.5f;
			// bullet 1
			enemyBullet1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

			enemyBullet1->setSize(15, 15);
			enemyBullet1->setPosition(getPosition());

			glm::vec3 bulDir1 = glm::normalize(glm::vec3(1, 0, 0));

			dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir1 * bulletSpeed);

			Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

			// bullet 2
			enemyBullet2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

			enemyBullet2->setSize(15, 15);
			enemyBullet2->setPosition(getPosition());

			glm::vec3 bulDir2 = glm::normalize(glm::vec3(-1, 0, 0));

			dynamic_cast<GameObject*>(enemyBullet2)->setVelocity(bulDir2 * bulletSpeed);

			Game::getInstance()->getObjectRef()->push_back(enemyBullet2);

			lState = GONE;
		}
		setPosition(glm::vec3(0, 500, 0));
	}
}