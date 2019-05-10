#pragma once

#include "GameObject.h"

class BulletGameObject :public GameObject
{
	static unsigned int bulletNum;

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
	BulletGameObject(Tag bulletType,string spriteFile) : GameObject(bulletType) { addSprite(spriteFile, 1, 1); bulletNum++;};
	BulletGameObject(Tag bulletType) : GameObject(bulletType) { bulletNum++; };
	~BulletGameObject();
	void update(float deltaTime);

	//for sprite
	void addSprite(string fileName, int row, int column);
	void render(glm::mat4 globalModelTransform);
	void setRow(int r);
	void setColumn(int c);
	int getRow();
	int getColumn();
	void genUV();
	void setAnimationLoop(int row, int column, int loop, int time); // 1000 = 1 second
	void nextAnimation();
};