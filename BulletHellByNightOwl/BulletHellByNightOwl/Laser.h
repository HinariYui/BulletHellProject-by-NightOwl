#pragma once

#include "EnemyBullet.h"

enum LaserState
{
	LS_START = 0,
	LS_MOVE,
	LS_END
};

class Laser :public EnemyBullet
{
public:
	LaserState lsState = LS_START;
	DrawableObject* pillar1 = NULL;
	DrawableObject* pillar2 = NULL;
	DrawableObject* laser = NULL;
	bool pillarActive = false;
	bool laserActive = false;
	int i = 0;
	float pillarSpeed = 3.0f;
	glm::vec3 pilDir = glm::vec3(0, -1, 0);
	float timeCounter = 0.f;
	float maxStartTime = 1000.f;
	float waitTimeCounter = 0.f;
	float waitTime = 2000.f;
	Laser(Tag bulletType, string spriteFile);
	void update(float deltaTime);
};