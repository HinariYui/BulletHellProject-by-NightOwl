#pragma once

#include "BulletGameObject.h"

class EnemyBullet :public BulletGameObject
{

public:
	EnemyBullet(Tag bulletType) : BulletGameObject(bulletType) { velocity = glm::vec3(0, -5, 0); };
	//void SetBulletVelocity(glm::vec3 vel);
	~EnemyBullet();
	void update(float deltaTime);
};