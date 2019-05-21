#include "GameObject.h"
#include "stdafx.h"
#include "SquareMeshVbo.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "AnimatedSelection.h"

class Menu :public DrawableObject
{
private:
	glm::vec3 color;
	AnimatedSelection *c1, *c2, *c3;// , *p1, *p2, *p3;
	
	//for Sprite
	int currentChoice = 0;
	vector<AnimatedSelection*> options;
	int optionNum = 0;
	int spriteNum = 0;

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
	bool pressed = false;

	Menu();
	Menu(string sprite);
	Menu(vector<string> fileName, int spriteNum, int optNum);
	~Menu();
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

	bool CheckIfAllComponentNotNull();
	void updateComponent(char indicator);
};

