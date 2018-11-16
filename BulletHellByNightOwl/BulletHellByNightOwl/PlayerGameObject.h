
#include "GameObject.h"
#include "BulletGameObject.h"

class PlayerGameObject :public GameObject
{
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
	bool isShooting = false;
	DrawableObject* playerBullet = NULL;

public:
	PlayerGameObject(Tag player) : GameObject(player){};
	~PlayerGameObject();
	void checkMovement();
	void checkAction();
	void move(char direction);
	void shoot(char status);
	void update(float deltaTime);
};