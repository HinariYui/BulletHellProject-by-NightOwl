#include "Laser.h"
#include "Game.h"
#include <iostream>
#include <time.h>

Laser::Laser(Tag bulletType, string spriteFile) : EnemyBullet(bulletType, spriteFile)
{
	BulletGameObject::addSprite(spriteFile, 1, 5);
	BulletGameObject::setAnimationLoop(1, 1, 1, 500);
	i = rand() % 2;
}

void Laser::update(float deltaTime)
{
	if (lsState == LS_START)
	{
		if (!pillarActive)
		{
			// Pillar 1

			pillar1 = new EnemyBullet(Tag::eBullet, "bigred.png");
			pillar1->setSize(40, 40);
			pillar1->setPosition(glm::vec3(-212, 200, 0));

			pilDir = normalize(glm::vec3(-1, 0, 0));

			dynamic_cast<GameObject*>(pillar1)->setVelocity(pilDir * pillarSpeed);

			Game::getInstance()->getObjectRef()->push_back(pillar1);

			// Pillar 2

			pillar2 = new EnemyBullet(Tag::eBullet, "bigred.png");
			pillar2->setSize(40, 40);
			pillar2->setPosition(glm::vec3(-212, 200, 0));

			pilDir = normalize(glm::vec3(1, 0, 0));

			dynamic_cast<GameObject*>(pillar2)->setVelocity(pilDir * pillarSpeed);

			Game::getInstance()->getObjectRef()->push_back(pillar2);
			pillarActive = true;
		}
		if (pillarActive && (pillar1->getPosition().x <= -440))
		{
			if (i == 0)
			{
				laser = new EnemyBullet(Tag::eBullet, "pillars_activate_577x45.png");
				laser->setSize(abs(pillar1->getPosition().x - pillar2->getPosition().x) + 15, 45);
				laser->setPosition(glm::vec3(-212, pillar1->getPosition().y, 0));

				dynamic_cast<GameObject*>(laser)->setVelocity(glm::vec3(0, -1, 0) * pillarSpeed);
				dynamic_cast<GameObject*>(pillar1)->setVelocity(glm::vec3(0, -1, 0) * pillarSpeed);
				dynamic_cast<GameObject*>(pillar2)->setVelocity(glm::vec3(0, -1, 0) * pillarSpeed);

				dynamic_cast<BulletGameObject*>(laser)->update(deltaTime);

				Game::getInstance()->getObjectRef()->push_back(laser);
			}

			dynamic_cast<GameObject*>(pillar1)->setVelocity(glm::vec3(0, -1, 0) * pillarSpeed);
			dynamic_cast<GameObject*>(pillar2)->setVelocity(glm::vec3(0, -1, 0) * pillarSpeed);
			lsState = LS_MOVE;
		}
	}
	if (lsState == LS_MOVE)
	{
		if (pillar1->getPosition().y <= -230)
		{
			if (i == 1)
			{
				laser = new EnemyBullet(Tag::eBullet, "pillars_activate_577x45.png");
				laser->setSize(abs(pillar1->getPosition().x - pillar2->getPosition().x) + 15, 45);
				laser->setPosition(glm::vec3(-212, pillar1->getPosition().y, 0));

				dynamic_cast<GameObject*>(laser)->setVelocity(glm::vec3(0, -1, 0) * pillarSpeed);
				dynamic_cast<GameObject*>(pillar1)->setVelocity(glm::vec3(0, -1, 0) * pillarSpeed);
				dynamic_cast<GameObject*>(pillar2)->setVelocity(glm::vec3(0, -1, 0) * pillarSpeed);

				dynamic_cast<BulletGameObject*>(laser)->update(deltaTime);

				Game::getInstance()->getObjectRef()->push_back(laser);
			}
			lsState = LS_END;
		}
		if (waitTimeCounter > waitTime)
		{
			lsState = LS_END;
		}
	}
	if (lsState == LS_END)
	{
		if (i == 0)
		{
			laser->setPosition(glm::vec3(0, 900, 0));
		}
	}
}