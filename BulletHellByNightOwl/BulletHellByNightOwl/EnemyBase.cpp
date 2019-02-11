#include <iostream>
#include <ctime>
#include "EnemyBase.h"
#include "Game.h"

EnemyBase::EnemyBase(Tag enemy, string fileName, int row, int col) : SpriteObject(fileName, row, col)
{
	tag = enemy;
	state = MOVE;
	setVelocity(glm::vec3(0, -2, 0));
	hp = 1;
	bulletSpeed = 5.0f;
}

void EnemyBase::update(float deltaTime)
{
	GameObject::update(deltaTime);
}

EnemyBase::~EnemyBase()
{

}