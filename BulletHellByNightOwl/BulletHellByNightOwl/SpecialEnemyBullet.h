#pragma once

#include "EnemyBullet.h"

enum BulletState
{
	START = 0,
	SPECIALIDLE,
	SHOOT
};

class SpecialEnemyBullet :public EnemyBullet
{
public:
	BulletState bState = START;
	glm::vec3 randomLocation;
	float timeCounter = 0.f;
	float maxStartTime = 500.f;
	float waitTimeCounter = 0.f;
	float waitTime = 3000.f;
	SpecialEnemyBullet(Tag bulletType, string spriteFile);
	void update(float deltaTime);
};