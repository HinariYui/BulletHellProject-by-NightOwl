#pragma once

#include "EnemyBullet.h"
#include "SpriteObject.h"

enum LandmineState
{
	L_START = 0,
	L_IDLE,
	L_EXPLODE,
	GONE
};

class Landmine :public EnemyBullet
{
public:
	LandmineState lState = L_START;
	DrawableObject* enemyBullet1 = NULL;
	DrawableObject* enemyBullet2 = NULL;
	SpriteObject* drone = NULL;
	glm::vec3 randomLocation;
	float timeCounter = 0.f;
	float maxStartTime = 500.f;
	float waitTimeCounter = 0.f;
	float waitTime = 2000.f;
	Landmine(Tag bulletType, string spriteFile, SpriteObject* drn);
	void update(float deltaTime);
};