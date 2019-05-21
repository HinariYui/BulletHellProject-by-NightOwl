#include <iostream>
#include <SDL_image.h>
#include "OptionMenu.h"
#include "Game.h"
#include "Audio.h"

OptionMenu::OptionMenu()
{
	addSprite("pauseMenu.png", 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
}

OptionMenu::OptionMenu(string fileName)
{
	addSprite(fileName, 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
}

OptionMenu::OptionMenu(vector<string> fileName, int spriteNum, int optNum)
{
	BGMpercent = Game::getInstance()->gameBGM;
	SFXpercent = Game::getInstance()->gameSFX;

	optionNum = optNum;
	this->spriteNum = spriteNum;
	addSprite(fileName.at(0), 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
	setNumberOfOptions(optionNum);
	Game::getInstance()->getObjectRef()->push_back(this);

	SDL_Color color = { 255, 165, 255 };
	
	std::string s = std::to_string(BGMpercent) + '%';
	s1 = new TextObject();
	s1->setPosition(glm::vec3(100, 90, 0));
	//s1->setSize(50, 50);
	s1->loadText(s, color, 60);
	Game::getInstance()->getObjectRef()->push_back(s1);

	s = std::to_string(SFXpercent) + '%';
	s2 = new TextObject();
	s2->setPosition(glm::vec3(100, -120, 0));
	//s2->setSize(50, 50);
	s2->loadText(s, color, 60);
	Game::getInstance()->getObjectRef()->push_back(s2);

	for (int i = 1; i <= optionNum; i++)
	{
		AnimatedSelection* p = new AnimatedSelection(fileName.at(i), 1, 1);
		p->setSize(219, 129);
		p->setPosition(glm::vec3(-245,300+(i*-210), 0));
		options.push_back(p);
		Game::getInstance()->getObjectRef()->push_back(p);
	}

	c1 = new AnimatedSelection(fileName.at(3), 1, 1);
	c1->setSize(219, 129);
	c1->setPosition(glm::vec3(0, 250, 0));
	Game::getInstance()->getObjectRef()->push_back(c1);

	c2 = new AnimatedSelection(fileName.at(4), 1, 1);//ON BGM
	c2->setSize(50, 50);
	c2->setPosition(glm::vec3(350, 90, 0));
	c2->enable = false;
	Game::getInstance()->getObjectRef()->push_back(c2);

	c3 = new AnimatedSelection(fileName.at(4), 1, 1);//ON SFX
	c3->setSize(50, 50);
	c3->setPosition(glm::vec3(350, -120, 0));
	c3->enable = false;
	Game::getInstance()->getObjectRef()->push_back(c3);

	c4 = new AnimatedSelection(fileName.at(5), 1, 1);//OFF BGM
	c4->setSize(50, 50);
	c4->setPosition(glm::vec3(350, 90, 0));
	c4->enable = false;
	Game::getInstance()->getObjectRef()->push_back(c4);

	c5 = new AnimatedSelection(fileName.at(5), 1, 1);//OFF SFX
	c5->setSize(50, 50);
	c5->setPosition(glm::vec3(350, -120, 0));
	c5->enable = false;
	Game::getInstance()->getObjectRef()->push_back(c5);

	c6 = new AnimatedSelection(fileName.at(6), 1, 1);//-BGM
	c6->setSize(50, 50);
	c6->setPosition(glm::vec3(-10, 90, 0));
	Game::getInstance()->getObjectRef()->push_back(c6);

	c7 = new AnimatedSelection(fileName.at(7), 1, 1);//+BGM
	c7->setSize(50, 50);
	c7->setPosition(glm::vec3(210, 90, 0));
	Game::getInstance()->getObjectRef()->push_back(c7);

	c8 = new AnimatedSelection(fileName.at(6), 1, 1);//-SFX
	c8->setSize(50, 50);
	c8->setPosition(glm::vec3(-10, -120, 0));
	Game::getInstance()->getObjectRef()->push_back(c8);

	c9 = new AnimatedSelection(fileName.at(7), 1, 1);//+SFX
	c9->setSize(50, 50);
	c9->setPosition(glm::vec3(210, -120, 0));
	Game::getInstance()->getObjectRef()->push_back(c9);

	p1 = new AnimatedSelection(fileName.at(10), 1, 1);////-BGM
	p1->setSize(50, 50);
	p1->setPosition(glm::vec3(-10, 90, 0));
	p1->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p1);

	p2 = new AnimatedSelection(fileName.at(11), 1, 1);////+BGM
	p2->setSize(50, 50);
	p2->setPosition(glm::vec3(210, 90, 0));
	p2->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p2);

	p3 = new AnimatedSelection(fileName.at(10), 1, 1);////-SFX
	p3->setSize(50, 50);
	p3->setPosition(glm::vec3(-10, -120, 0));
	p3->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p3);

	p4 = new AnimatedSelection(fileName.at(11), 1, 1);////+SFX
	p4->setSize(50, 50);
	p4->setPosition(glm::vec3(210, -120, 0));
	p4->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p4);

	p5 = new AnimatedSelection(fileName.at(8), 1, 1); ////BGM
	p5->setSize(219, 129);
	p5->setPosition(glm::vec3(-245, 90, 0));
	Game::getInstance()->getObjectRef()->push_back(p5);

	p6 = new AnimatedSelection(fileName.at(9), 1, 1);////SFX
	p6->setSize(219, 129);
	p6->setPosition(glm::vec3(-245, -120, 0));
	p6->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p6);

	onBGM = Game::getInstance()->gameBGMisOn;
	onSFX = Game::getInstance()->gameSFXisOn;
	volBGM = Game::getInstance()->gameBGM;
	volSFX = Game::getInstance()->gameSFX;

	if (onBGM == true)
	{
		c2->enable = true;
		c4->enable = false;

	}
	else
	{
		c2->enable = false;
		c4->enable = true;
	}

	if (onSFX == true)
	{
		c3->enable = true;
		c5->enable = false;

	}
	else
	{
		c3->enable = false;
		c5->enable = true;
	}

	update(0);
}

OptionMenu::~OptionMenu()
{

}

void OptionMenu::setColor(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}

void OptionMenu::update(float deltaTime)
{
	//p1->enable = false;
	//p2->enable = false;
	//p3->enable = false;
	//p4->enable = false;


	SDL_Color color = { 255, 165, 255 };

	std::string s = std::to_string(BGMpercent) + '%';
	s1->loadText(s, color, 60);
	s = std::to_string(SFXpercent) + '%';
	s2->loadText(s, color, 60);
	volBGM = BGMpercent * 128 / 100;
	volSFX = SFXpercent * 128 / 100;

	Mix_VolumeMusic(volBGM);
	Mix_Volume(-1, volSFX);



	if (currentChoice <= 0) //BGM
	{
		p3->enable = false;
		p4->enable = false;

		p5->enable = true;
		p6->enable = false;

		if (onBGM == true)
		{
			c2->enable = true;
			c4->enable = false;
		}
		else
		{
			c2->enable = false;
			c4->enable = true;
		}

	}
	else //SFX
	{

		p1->enable = false;
		p2->enable = false;

		p5->enable = false;
		p6->enable = true;

		if (onSFX == true)
		{
			c3->enable = true;
			c5->enable = false;

		}
		else
		{
			c3->enable = false;
			c5->enable = true;
		}

	}

	p1->update(deltaTime);
	p2->update(deltaTime);
	p3->update(deltaTime);
	p4->update(deltaTime);
	p5->update(deltaTime);
	p6->update(deltaTime);


	if (onBGM == false)
	{
		Mix_VolumeMusic(0);
	}
	if (onSFX == false)
	{
		Mix_Volume(-1,0);
	}
}

void OptionMenu::addSprite(string fileName, int row, int column)
{
	glActiveTexture(GL_TEXTURE0);
	SDL_Surface *image = IMG_Load(fileName.c_str());
	if (image == NULL)
	{
		cerr << "IMG_Load: " << SDL_GetError() << endl;
		return;
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int Mode = GL_RGB;
	if (image->format->BytesPerPixel == 4)
	{
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode, GL_UNSIGNED_BYTE, image->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	SDL_FreeSurface(image);

	this->rowMax = row;
	this->columnMax = column;
	this->row = 1;
	this->column = 1;
	this->genUV();

	this->animRow = 1;
	this->animColumn = 1;
	this->loopMax = 1;
	this->loopCount = 0;
	this->animationTime = 0;
	this->timeCount = 0;
}

void OptionMenu::render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo *squareMesh = dynamic_cast<SquareMeshVbo *> (Game::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = Game::getInstance()->getRenderer()->getModelMatrixAttrId();
	GLuint modeId = Game::getInstance()->getRenderer()->getModeUniformId();

	glBindTexture(GL_TEXTURE_2D, texture);
	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(modeId, 1);
		squareMesh->adjustTexcoord(uv);
		squareMesh->render();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}


void OptionMenu::setRow(int r)
{
	this->row = r;
}

void OptionMenu::setColumn(int c)
{
	this->column = c;
}

int OptionMenu::getRow()
{
	return this->row;
}

int OptionMenu::getColumn()
{
	return this->column;
}

void OptionMenu::genUV()
{
	float ratioR = 1.0f / rowMax;
	float ratioC = 1.0f / columnMax;

	uv[0] = (column - 1) * ratioC;
	uv[1] = (row - 1) * ratioR;

	uv[2] = column * ratioC;
	uv[3] = (row - 1) * ratioR;

	uv[4] = column * ratioC;
	uv[5] = row * ratioR;

	uv[6] = (column - 1) * ratioC;
	uv[7] = row * ratioR;
}

void OptionMenu::setAnimationLoop(int row, int column, int loop, int time)
{
	this->animRow = row;
	this->animColumn = column;
	this->loopMax = loop;
	this->loopCount = 0;
	this->animationTime = time;
}

void OptionMenu::nextAnimation()
{
	loopCount++;
	if (loopCount < loopMax)
	{
		if (column < columnMax)
		{
			column++;
		}
		else
		{
			column = 1;
			row++;
		}
	}
	else
	{
		row = animRow;
		column = animColumn;
		loopCount = 0;
	}

}

void OptionMenu::setNumberOfOptions(int num)
{
	optionNum = num;
}


void OptionMenu::destroyComponents()
{
	DrawableObject* instance;

	for (int j = options.size() - 1; j >= 0; j--)
	{
		for (int i = Game::getInstance()->getObjectRef()->size() - 1; i >= 0; i--)
		{
			instance = Game::getInstance()->getObjectRef()->at(i);

			if (instance->getObjId() == options.at(j)->getObjId())
			{
				Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
				Game::getInstance()->getObjectRef()->end();
			}
		}
	}

	for (int i = Game::getInstance()->getObjectRef()->size() - 1; i >= 0; i--)
	{
		instance = Game::getInstance()->getObjectRef()->at(i);
		if (instance->getObjId() == c1->getObjId() || instance->getObjId() == c2->getObjId() || instance->getObjId() == c3->getObjId() || instance->getObjId() == c4->getObjId() || instance->getObjId() == c5->getObjId()
			|| instance->getObjId() == c6->getObjId() || instance->getObjId() == c7->getObjId() || instance->getObjId() == c8->getObjId() || instance->getObjId() == c9->getObjId() || instance->getObjId() == s1->getObjId() || instance->getObjId() == s2->getObjId()
			|| instance->getObjId() == p1->getObjId() || instance->getObjId() == p2->getObjId() || instance->getObjId() == p3->getObjId() || instance->getObjId() == p4->getObjId() || instance->getObjId() == p5->getObjId() || instance->getObjId() == p6->getObjId())


		{
			Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
			Game::getInstance()->getObjectRef()->end();
		}
	}

	//if (CheckIfAllComponentNotNull() == true)
	//{
	//	for (int i = Game::getInstance()->getObjectRef()->size() - 1; i >= 0; i--)
	//	{
	//		instance = Game::getInstance()->getObjectRef()->at(i);

	//		if (instance->getObjId() == c1->getObjId() || instance->getObjId() == c2->getObjId() || instance->getObjId() == c3->getObjId() || instance->getObjId() == c4->getObjId())
	//		{
	//			Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
	//			Game::getInstance()->getObjectRef()->end();
	//		}
	//	}
	//}
}

//bool OptionMenu::CheckIfAllComponentNotNull()
//{
//	if (c1 != NULL && c2 != NULL && c3 != NULL && c4 != NULL && p1 != NULL && p2 != NULL && p3 != NULL && p4 != NULL)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

void OptionMenu::setCurrentSelection(int num)
{
	currentChoice = num;
}

int OptionMenu::getCurrentSelection()
{
	return currentChoice;
}

void OptionMenu::increaseVol()
{
	if (currentChoice <= 0)
	{
		p2->enable = true;

		if (BGMpercent < 100)
		{
			Game::getInstance()->gameBGM++;
			BGMpercent++;
		}
	}
	else
	{
		p4->enable = true;

		if (SFXpercent < 100)
		{
			Game::getInstance()->gameSFX++;
			SFXpercent++;
		}
	}
}
void OptionMenu::decreaseVol()
{
	if (currentChoice <= 0)
	{
		p1->enable = true;
		if (BGMpercent > 0)
		{
			Game::getInstance()->gameBGM--;
			BGMpercent--;
		}
	}
	else
	{
		p3->enable = true;

		if (SFXpercent > 0)
		{
			Game::getInstance()->gameSFX--;
			SFXpercent--;
		}
	}
}

void OptionMenu::toggleOnOff()
{
	if (currentChoice <= 0)//BGM
	{
		if (onBGM == true)
		{
			Game::getInstance()->gameBGMisOn = false;
			onBGM = false;
		}
		else
		{
			Game::getInstance()->gameBGMisOn = true;
			onBGM = true;
		}
	}
	else//SFX
	{
		if (onSFX == true)
		{
			Game::getInstance()->gameSFXisOn = false;
			onSFX = false;
		}
		else
		{
			
			Game::getInstance()->gameSFXisOn = true;
			onSFX = true;
		}
	}
}

void OptionMenu::increaseVolUpdate()
{
	if (currentChoice <= 0)
	{
		p2->enable = false;
	}
	else
	{
		p4->enable = false;
	}
}
void OptionMenu::decreaseVolUpdate()
{
	if (currentChoice <= 0)
	{
		p1->enable = false;
	}
	else
	{
		p3->enable = false;
	}
}
