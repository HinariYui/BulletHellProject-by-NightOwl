#pragma once

#include "GameObject.h"

class BulletGameObject :public GameObject
{
	static unsigned int bulletNum;


public:
	BulletGameObject(Tag bulletType) : GameObject(bulletType) { bulletNum++;};
	~BulletGameObject();
	void update(float deltaTime);
};