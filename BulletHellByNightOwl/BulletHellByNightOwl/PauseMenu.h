#include "AnimatedSelection.h"
#include "stdafx.h"
#include "SquareMeshVbo.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class PauseMenu :public DrawableObject
{
private:
	
	AnimatedSelection * c1;
	//GameObject * c1;//choiceIndicator
	int currentChoice = 0;
	glm::vec3 color;
	vector<AnimatedSelection*> options;
	int optionNum = 0;
	int spriteNum = 0;
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
	PauseMenu();
	PauseMenu(string fileName);
	PauseMenu(vector<string> fileName, int spriteNum, int optNum);
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

	void setCurrentSelection(int num);
	int getCurrentSelection();

};


