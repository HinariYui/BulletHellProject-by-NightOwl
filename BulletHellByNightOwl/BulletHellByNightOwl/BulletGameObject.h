#include "GameObject.h"
#include "Game.h"

class BulletGameObject :public GameObject
{
	static unsigned int bulletNum;
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
	bool isShooting = false;

public:
	BulletGameObject(Tag bulletType) : GameObject(bulletType) { bulletNum++;};
	~BulletGameObject();
	void update(float deltaTime);
};