//#pragma once
//
//#include "SpriteObject.h"
//#include "EnemyBullet.h"
//
//enum Enemy2State
//{
//	MOVE = 0,
//	ATK,
//	EXIT
//};
//
//class Enemy2 :public SpriteObject
//{
//private:
//	Enemy2State state;
//	bool isShooting = false;
//	bool reachDestination = false;
//	int shootCD = 0;
//	float idleTime = 0;
//	float stateTime = 0;
//	float ATKCount = 0;
//	float bulletSpeed;
//
//	//void updateMOVE(float deltaTime);
//	//void updateATK(float deltaTime);
//	//void updateEXIT(float deltaTime);
//
//	void Behavior1();
//
//public:
//	Enemy2(Tag enemy, string fileName, int row, int col);
//	~Enemy2();
//	void move();
//	void shoot1();
//	void update(float deltaTime);
//};