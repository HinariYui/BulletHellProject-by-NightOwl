#pragma once

#include "Spawner.h"

class SpawnerA :public Spawner
{
	int type = 0;
	int number = 0;
	float posLeft = 0.f;
	float dis = 0.f; //distance between each enemy
public:
	SpawnerA();
	~SpawnerA();
	void update(float deltatime);
	void Spawn(int t, int n, float p, float d);
};