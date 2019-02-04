#pragma once

#include "SpriteObject.h"
#include "EnemyBullet.h"



class Enemy1 :public SpriteObject
{

public:
	enum EnemyState
	{
		MOVE = 0,
		ATK,
		EXIT
	};
private:
	EnemyState state;
	bool isShooting = false;
	bool reachDestination = false;
	int shootCD = 0;
	float idleTime = 0;
	float stateTime = 0;
	float ATKCount = 0;
	float bulletSpeed;

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