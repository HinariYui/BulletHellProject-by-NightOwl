
#include "GameObject.h"
#include "EnemyBullet.h"

class Boss1 :public GameObject
{
	bool isShooting = false;
	DrawableObject* enemyBullet1 = NULL;
	DrawableObject* enemyBullet2 = NULL;
	DrawableObject* enemyBullet3 = NULL;
	int shootCD = 0;

public:
	Boss1(Tag enemy) : GameObject(enemy) {};
	~Boss1();
	void move();
	void shoot1();
	void update(float deltaTime);
};