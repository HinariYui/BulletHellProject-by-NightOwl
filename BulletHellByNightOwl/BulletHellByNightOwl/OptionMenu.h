#include "AnimatedSelection.h"
#include "stdafx.h"
#include "SquareMeshVbo.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "TextObject.h"

class OptionMenu :public DrawableObject
{
private:

	TextObject * s1, *s2;
	AnimatedSelection *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *p1, *p2, *p3, *p4, *p5, *p6;
	bool onBGM = true;
	bool onSFX = true;
	int BGMpercent = 75;
	int SFXpercent = 75;
	int volBGM = 96;
	int volSFX = 96;
	//AnimatedSelection * c1, *c2, *c3, *c4, *p1, *p2, *p3, *p4;
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
	bool pressed = false;

	OptionMenu();
	OptionMenu(string fileName);
	OptionMenu(vector<string> fileName, int spriteNum, int optNum);
	~OptionMenu();
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

	//bool CheckIfAllComponentNotNull();

	void increaseVol();
	void decreaseVol();
	void toggleOnOff();
	void increaseVolUpdate();
	void decreaseVolUpdate();

	void updateComponent(char indicator);

};
