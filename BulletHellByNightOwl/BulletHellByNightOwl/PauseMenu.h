#include "GameObject.h"
#include "stdafx.h"
#include "SquareMeshVbo.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class PauseMenu :public DrawableObject
{
private:
	glm::vec3 color;
	vector<PauseMenu*> options;
	//vector<string> optionSpriteFileName;
	int optionNum = 0;
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
	float blinkTime = 0;
	bool isBlinking = false;


public:
	PauseMenu();
	PauseMenu(string fileName, int optNum);
	~PauseMenu();
	void setColor(float r, float g, float b);
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

	void setNumberOfOptions(int num);
	void destroyComponents();
};


