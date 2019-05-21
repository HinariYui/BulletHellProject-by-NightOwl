#pragma once

#include "EnemyBase.h"

class Enemy1 :public EnemyBase
{
private:
	bool isShooting = false;
	bool reachDestination = false;
	int shootCD = 0;
	float idleTime = 0;
	float stateTime = 0;
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