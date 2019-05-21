#pragma once
#include "GameObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Life :public GameObject
{
private:
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
	bool isRendered = true;

public:

	Life(string fileName, int row, int column);
	~Life();

	void addSprite(string fileName, int row, int column);
	void render(glm::mat4 globalModelTransform);
	void update(float deltaTime);
	void setRow(int r);
	void setColumn(int c);
	int getRow();
	int getColumn();
	void genUV();
	void loopUV(float deltaTime);
	void setAnimationLoop(int row, int column, int loop, int time); // 1000 = 1 secone
	void nextAnimation();
	void setRender(bool boolean);
};