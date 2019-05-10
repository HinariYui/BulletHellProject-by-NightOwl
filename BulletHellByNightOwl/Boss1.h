#pragma once

#include "SpriteObject.h"
#include "Audio.h"

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
	SpriteObject* Drone1 = NULL; // 48 x 48 px , top left
	SpriteObject* Drone2 = NULL; // 48 x 48 px , top right
	SpriteObject* Drone3 = NULL; // 48 x 48 px , bottom left
	SpriteObject* Drone4 = NULL; // 48 x 48 px , bottom right

	glm::vec3 drone1DefaultPos;
	glm::vec3 drone2DefaultPos;
	glm::vec3 drone3DefaultPos;
	glm::vec3 drone4DefaultPos;

	glm::vec3 drone1MoveToPos;
	glm::vec3 drone2MoveToPos;
	glm::vec3 drone3MoveToPos;
	glm::vec3 drone4MoveToPos;

	bool droneIsMoving1 = false;
	bool droneIsMoving2 = false;
	bool droneIsMovingBack = false;
	bool drone1IsMoving = false;
	bool drone2IsMoving = false;
	bool drone3IsMoving = false;
	bool drone4IsMoving = false;
	glm::vec3 drone1MoveDir, drone2MoveDir, drone3MoveDir, drone4MoveDir;
	float drone1MoveSpeed, drone2MoveSpeed, drone3MoveSpeed, drone4MoveSpeed;

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
	void shoot1_1B(float constant, float deltaTime);
	void shoot2_1D();
	void DroneMove1(float constant);
	void DroneMove2(float constant);
	void DroneMoveBack(float constant);
	void update(float deltaTime);
	virtual void render(glm::mat4 globalModelTransform);
};