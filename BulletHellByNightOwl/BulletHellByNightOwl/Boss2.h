#pragma once

#include "SpriteObject.h"
#include "Audio.h"

enum Boss2State
{
	IDLE2 = 0,
	MOVEIN2,
	ATK2_1,
	ATK2_2,
	ATK2_3
};

class Boss2 :public SpriteObject
{
private:
	Boss2State state;
	bool isShooting = false;
	bool isShooting2 = false;
	bool isShooting3 = false;
	bool isShooting4 = false;
	bool isShooting5 = false;
	bool isShooting6 = false;
	bool isShooting1_1 = true;
	bool isShooting1_2 = true;
	bool isShooting2_1 = true;
	bool isShooting2_2 = true;
	bool isShooting3_1 = true;
	bool isShooting3_2 = true;
	bool isShooting4_1 = true;
	bool isShooting4_2 = true;
	bool isShooting5_1 = true;
	bool isShooting5_2 = true;
	bool reachDestination = false;
	DrawableObject* enemyBullet1 = NULL;
	DrawableObject* enemyBullet1_1 = NULL;
	DrawableObject* enemyBullet1_2 = NULL;
	DrawableObject* enemyBullet2 = NULL;
	DrawableObject* enemyBullet2_1 = NULL;
	DrawableObject* enemyBullet2_2 = NULL;
	DrawableObject* enemyBullet3 = NULL;
	DrawableObject* enemyBullet3_1 = NULL;
	DrawableObject* enemyBullet3_2 = NULL;
	DrawableObject* enemyBullet4 = NULL;
	DrawableObject* enemyBullet4_1 = NULL;
	DrawableObject* enemyBullet4_2 = NULL;
	DrawableObject* enemyBullet5 = NULL;
	DrawableObject* enemyBullet5_1 = NULL;
	DrawableObject* enemyBullet5_2 = NULL;
	GameObject* HPbar = NULL;

	AudioEngine audio;

	SoundEffect shootSound = audio.loadSoundEffect("Attack1.mp3");

	float HPsize = 500;
	float HPpos = -212;
	float HPpercentage;
	float missingHP;

	int maxHP = 1000;

	int shootCD = 0;
	float idleTime;
	float stateTime;
	float ATKCount = 0;
	int shootCount = 0;

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
	Boss2(Tag enemy, string fileName, int row, int col);
	~Boss2();
	void move();
	void shoot2_1C();
	void shoot1_2A();
	void shoot2_1D();
	void update(float deltaTime);
	virtual void render(glm::mat4 globalModelTransform);
};