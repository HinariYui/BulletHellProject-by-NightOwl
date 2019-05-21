#pragma once

#include <ctime>
#include <iostream>
#include "Enemy1.h"
#include "Enemy2.h"

class Spawner
{
	float time;
	float spawnCD = 0;
	float spawnRate = 0;
	int pattern = 0;

	Enemy1* e1_1 = NULL;
	Enemy1* e1_2 = NULL;
	Enemy1* e1_3 = NULL;
	Enemy1* e1_4 = NULL;
	Enemy1* e1_5 = NULL;

	Enemy2* e2_1 = NULL;
	Enemy2* e2_2 = NULL;
	Enemy2* e2_3 = NULL;
	Enemy2* e2_4 = NULL;
	Enemy2* e2_5 = NULL;
	Enemy2* e2_6 = NULL;
	Enemy2* e2_7 = NULL;
	Enemy2* e2_8 = NULL;

public:
	int eNum = 0;
	Spawner();
	~Spawner();
	void update(float deltatime);
	void SetSpawnRate(float rate);
	void EnemySpawn(float rate);
	void EnemySpawn(int i);
};