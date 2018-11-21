#include "SpriteObject.h"
#include "GameObject.h"
#include "BulletGameObject.h"

class PlayerGameObject :public GameObject
{
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
	bool isShooting = false;
	//DrawableObject* playerBullet = NULL;
	int shootCD = 0;

	//for Sprite
	unsigned int texture;
	int rowMax;
	int columnMax;
	int row;
	int column;
	float uv[8];
	int animRow;
	int animColumn;
	int loopMax;
	int loopCount;
	int animationTime;
	int timeCount;

public:
	PlayerGameObject(Tag player) : GameObject(player) {addSprite("player.png", 2, 4); }; //: GameObject(player) { addSprite("player.png", 2, 4); };
	~PlayerGameObject();
	void checkMovement();
	void checkAction();
	void move(char direction);
	void shoot(char status);
	void update(float deltaTime);

	//for sprite
	void addSprite(string fileName, int row, int column);
	void render(glm::mat4 globalModelTransform);
	void setRow(int r);
	void setColumn(int c);
	int getRow();
	int getColumn();
	void genUV();
	void setAnimationLoop(int row, int column, int loop, int time); // 1000 = 1 secone
	void nextAnimation();

};