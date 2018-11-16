#pragma once

#include "GameObject.h"
#include "BulletGameObject.h"

class Boss1 :public GameObject
{
	bool isShooting = false;
	DrawableObject* enemyBullet = NULL;

public:
	Boss1(Tag enemy) : GameObject(enemy) {};
	~Boss1();
	void move();
	void shoot();
	void update(float deltaTime);
};