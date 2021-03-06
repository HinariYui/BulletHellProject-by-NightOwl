#include "Landmine.h"
#include "Game.h"
#include <iostream>

Landmine::Landmine(Tag bulletType, string spriteFile) : EnemyBullet(bulletType, spriteFile)
{

}

void Landmine::update(float deltaTime)
{
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
			enemyBullet1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

			enemyBullet1->setSize(10, 10);
			enemyBullet1->setPosition(getPosition());

			glm::vec3 bulDir = glm::normalize(glm::vec3(1, 0, 0));
			float bulletSpeed = 2.0f;

			dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir * bulletSpeed);

			Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

			lState = GONE;
		}
		setPosition(glm::vec3(0, 500, 0));
	}
}