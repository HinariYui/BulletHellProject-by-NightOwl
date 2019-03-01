#include "SpecialEnemyBullet.h"
#include <iostream>

SpecialEnemyBullet::SpecialEnemyBullet(Tag bulletType, string spriteFile) : EnemyBullet(bulletType, spriteFile)
{
	int x, y;
	x = rand() % 400 - 412;
	y = rand() % 100 + 150;
	randomLocation = glm::vec3(x, y, 0);
}

void SpecialEnemyBullet::update(float deltaTime)
{
	timeCounter += deltaTime;
	if (bState == START)
	{
		float time = timeCounter / maxStartTime;
		glm::vec3 currentPos = getPosition();
		glm::vec3 result = (currentPos * (1 - time)) + (randomLocation * time); // lerp
		setPosition(result);
		if (timeCounter > maxStartTime)
		{
			bState = SPECIALIDLE;
		}
	}
	if (bState == SPECIALIDLE)
	{
		waitTimeCounter += deltaTime;
		if (waitTimeCounter > waitTime)
		{
			bState = SHOOT;
		}
	}
	if (bState == SHOOT)
	{
		setVelocity(glm::vec3(0, -10, 0));
		float constant = deltaTime * 0.05;
		translate(constant * velocity);
	}
}