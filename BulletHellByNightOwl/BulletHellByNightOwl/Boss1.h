#pragma once

#include "SpriteObject.h"

enum Boss1State
{
	IDLE = 0,
	MOVEIN,
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
	DrawableObject* enemyBullet4 = NULL;
	GameObject* HPbar = NULL;
	SpriteObject* Drone1 = NULL; // 24 x 24 px
	SpriteObject* Drone2 = NULL; // 24 x 24 px
	SpriteObject* Drone3 = NULL; // 24 x 24 px
	SpriteObject* Drone4 = NULL; // 24 x 24 px

	float HPsize = 500;
	float HPpos = -212;
	float HPpercentage;
	float missingHP;

	int maxHP = 1000;

	int shootCD = 0;
	float idleTime;
	float stateTime;
	float ATKCount = 0;

	glm::vec3 velD = glm::vec3(0, -5, 0); //shoot down
	glm::vec3 velR = glm::vec3(5, 0, 0); //shoot right
	glm::vec3 velU = glm::vec3(0, 5, 0); //shoot up
	glm::vec3 velL = glm::vec3(-5, 0, 0); //shoot left

	float bulletSpeed;

	glm::mat4 rotationMatrix;

	void updateIDLE(float deltaTime);
	void updateMoveIn(float deltaTime);
	void updateATK1(float deltaTime);
	void updateATK2(float deltaTime);
	void updateATK3(float deltaTime);

public:
	Boss1(Tag enemy, string fileName, int row, int col);
	~Boss1();
	void move();
	void shoot2_1C();
	void shoot1_1A();
	void shoot2_1D();
	void update(float deltaTime);
	virtual void render(glm::mat4 globalModelTransform);
};