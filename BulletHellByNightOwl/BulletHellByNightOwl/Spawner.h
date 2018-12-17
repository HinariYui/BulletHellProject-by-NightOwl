#pragma once

#include <ctime>
#include <iostream>
#include "Enemy1.h"

class Spawner
{
	float time;
	float spawnCD = 0;
	float spawnRate = 0;
public:
	int eNum = 0;
	Spawner();
	~Spawner();
	void update(float deltatime);
	void SetSpawnRate(float rate);
	void EnemySpawn(float rate);
};