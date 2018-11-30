#pragma once

#include "SpriteObject.h"

enum Boss1State
{
	IDLE = 0,
	ATK1,
	ATK2,
	ATK3
};

class Boss1 :public SpriteObject
{
private:
	Boss1State state;
	bool isShooting = false;
	bool reachDestination = false;
	DrawableObject* enemyBullet1 = NULL;
	DrawableObject* enemyBullet2 = NULL;
	DrawableObject* enemyBullet3 = NULL;
	int shootCD = 0;
	float idleTime;
	float stateTime;
	float ATKCount = 0;

	void updateIDLE(float deltaTime);
	void updateATK1(float deltaTime);
	void updateATK2(float deltaTime);
	void updateATK3(float deltaTime);

public:
	Boss1(Tag enemy, string fileName, int row, int col);
	~Boss1();
	void move();
	void shoot1();
	void update(float deltaTime);
};