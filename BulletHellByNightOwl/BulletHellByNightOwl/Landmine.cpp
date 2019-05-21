#include "Landmine.h"
#include "Game.h"
#include <iostream>

#define PI 3.141592653589793f

Landmine::Landmine(Tag bulletType, string spriteFile, glm::vec3 dir) : EnemyBullet(bulletType, spriteFile)
{
	BulletGameObject::addSprite(spriteFile, 1, 3);
	BulletGameObject::setAnimationLoop(1, 1, 1, 500);
	droneDir = dir;
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
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
			glm::vec4 temp = glm::vec4(droneDir, 1);
			temp = rotationMatrix * temp;

			// bullet 1
			enemyBullet1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

			enemyBullet1->setSize(15, 15);
			enemyBullet1->setPosition(getPosition());

			glm::vec3 bulDir = glm::normalize(glm::vec3(temp.x, temp.y, temp.z));

			dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir * bulletSpeed);

			Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

			// bullet 2
			enemyBullet2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

			enemyBullet2->setSize(15, 15);
			enemyBullet2->setPosition(getPosition());

			dynamic_cast<GameObject*>(enemyBullet2)->setVelocity(-bulDir * bulletSpeed);

			Game::getInstance()->getObjectRef()->push_back(enemyBullet2);

			lState = GONE;
		}
		setPosition(glm::vec3(0, 500, 0));
	}
}