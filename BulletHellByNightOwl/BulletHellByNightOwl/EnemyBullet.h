#pragma once

#include "BulletGameObject.h"

class EnemyBullet :public BulletGameObject
{
public:
	EnemyBullet(Tag bulletType, string spriteFile) : BulletGameObject(bulletType, spriteFile) { setVelocity(glm::vec3(0, -5, 0)); };
	EnemyBullet(Tag bulletType) : BulletGameObject(bulletType) {setVelocity(glm::vec3(0, -5, 0));};
	//~EnemyBullet();
	void update(float deltaTime);
};