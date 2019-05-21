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
	glm::vec3 droneDir;
	glm::mat4 rotationMatrix;
	float timeCounter = 0.f;
	float maxStartTime = 500.f;
	float waitTimeCounter = 0.f;
	float waitTime = 2000.f;
	Landmine(Tag bulletType, string spriteFile, glm::vec3 dir);
	void update(float deltaTime);
};