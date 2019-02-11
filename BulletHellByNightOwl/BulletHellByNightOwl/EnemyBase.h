#pragma once

#include "SpriteObject.h"
#include "EnemyBullet.h"


class EnemyBase :public SpriteObject
{
public:
	enum EnemyState
	{
		MOVE = 0,
		ATK,
		EXIT
	};

	EnemyBase(Tag enemy, string fileName, int row, int col);
	~EnemyBase();
	void update(float deltaTime); 
	
	EnemyState state;
	float bulletSpeed;
};