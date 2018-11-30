#pragma once

#include <ctime>
#include <iostream>
#include "Enemy1.h"

class Spawner
{
	float time;
	float spawnRate = 0;
public:
	Spawner();
	~Spawner();
	void update(float deltatime);
	void EnemySpawn(float rate);
};