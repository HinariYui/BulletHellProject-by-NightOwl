#pragma once

#include "EnemyBase.h"

class Enemy2 :public EnemyBase
{
private:
	AudioEngine audio;
	SoundEffect shootSound = audio.loadSoundEffect("Attack1.mp3");

	EnemyState state;
	bool shootSoundActive = false;
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

	void Behavior1();

public:
	Enemy2(Tag enemy, string fileName, int row, int col);
	~Enemy2();
	void move();
	void shoot1();
	void update(float deltaTime);
	bool isInPlayArea();
	void setShootSound(bool boolean);
};