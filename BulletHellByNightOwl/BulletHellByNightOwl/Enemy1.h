#pragma once

#include "SpriteObject.h"
#include "EnemyBullet.h"

enum Enemy1State
{
	MOVE = 0,
	ATK,
	EXIT
};

class Enemy1 :public SpriteObject
{
private:
	Enemy1State state;
	bool isShooting = false;
	bool reachDestination = false;
	DrawableObject* enemyBullet1 = NULL;
	DrawableObject* enemyBullet2 = NULL;
	DrawableObject* enemyBullet3 = NULL;
	int shootCD = 0;
	float idleTime;
	float stateTime;
	float ATKCount = 0;

	void updateMOVE(float deltaTime);
	void updateATK(float deltaTime);
	void updateEXIT(float deltaTime);

public:
	Enemy1(Tag enemy, string fileName, int row, int col);
	~Enemy1();
	void move();
	void shoot1();
	void update(float deltaTime);
};