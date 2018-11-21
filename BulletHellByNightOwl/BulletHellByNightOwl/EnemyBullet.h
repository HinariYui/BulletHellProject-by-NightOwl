#pragma once

#include "BulletGameObject.h"

class EnemyBullet :public BulletGameObject
{
	glm::vec3 velocity;

public:
	EnemyBullet(Tag bulletType) : BulletGameObject(bulletType) { velocity = glm::vec3(0, -5, 0); };
	~EnemyBullet();
	void update(float deltaTime);
};