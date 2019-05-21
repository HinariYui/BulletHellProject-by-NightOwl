#include <iostream>
#include <SDL_image.h>
#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
	addSprite("tempMenu.png", 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
}
Menu::Menu(string sprite)
{
	addSprite(sprite, 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
}

Menu::Menu(vector<string> fileName, int spriteNum, int optNum)
{
	optionNum = optNum;
	this->spriteNum = spriteNum;
	addSprite(fileName.at(0), 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
	setNumberOfOptions(optionNum);
	Game::getInstance()->getObjectRef()->push_back(this);

	for (int i = 1; i <= optionNum; i++)
	{
		AnimatedSelection* p = new AnimatedSelection(fileName.at(i), 1, 1);
		p->setSize(270, 100);
		p->setPosition(glm::vec3(0,  + (i*-75), 0));
		options.push_back(p);
		Game::getInstance()->getObjectRef()->push_back(p);
	}

	c1 = new AnimatedSelection(fileName.at(4), 1, 1);
	c1->setSize(270, 100);
	c1->setPosition(glm::vec3(0, -75, 0));
	c1->setAnimationLoop(1, 1, 1, 1000);
	Game::getInstance()->getObjectRef()->push_back(c1);

	c2 = new AnimatedSelection(fileName.at(5), 1, 1);
	c2->setSize(270, 100);
	c2->setPosition(glm::vec3(0, -150, 0));
	c2->setAnimationLoop(1, 1, 1, 1000);
	Game::getInstance()->getObjectRef()->push_back(c2);

	c3 = new AnimatedSelection(fileName.at(6), 1, 1);
	c3->setSize(270, 100);
	c3->setPosition(glm::vec3(0, -225, 0));
	c3->setAnimationLoop(1, 1, 1, 1000);
	Game::getInstance()->getObjectRef()->push_back(c3);

	//p1 = new AnimatedSelection(fileName.at(7), 1, 7);
	//p1->setSize(438, 120);
	//p1->setPosition(glm::vec3(0, -75, 0));
	//p1->setAnimationLoop(1, 7, 7, 1000);
	//p1->enable = false;
	//Game::getInstance()->getObjectRef()->push_back(p1);

	//p2 = new AnimatedSelection(fileName.at(8), 1, 7);
	//p2->setSize(438, 120);
	//p2->setPosition(glm::vec3(0, -150, 0));
	//p2->setAnimationLoop(1, 7, 7, 1000);
	//p2->enable = false;
	//Game::getInstance()->getObjectRef()->push_back(p2);

	//p3 = new AnimatedSelection(fileName.at(9), 1, 7);
	//p3->setSize(438, 120);
	//p3->setPosition(glm::vec3(0, -225, 0));
	//p3->setAnimationLoop(1, 7, 7, 1000);
	//p3->enable = false;
	//Game::getInstance()->getObjectRef()->push_back(p3);
}

Menu::~Menu()
{

}

void Menu::setColor(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}

void Menu::update(float deltaTime)
{
	if (CheckIfAllComponentNotNull() == true)
	{
		//if (pressed == false)
		{
			if (currentChoice <= 0) //subSprite=1 (y = 150 +  1*-75)
			{
				c1->enable = true;
				c2->enable = false;
				c3->enable = false;
				//p1->enable = false;
				//p2->enable = false;
				//p3->enable = false;
			}
			else if (currentChoice == 1)
			{
				c1->enable = false;
				c2->enable = true;
				c3->enable = false;
				//p1->enable = false;
				//p2->enable = false;
				//p3->enable = false;
			}
			else //if (currentChoice == 2)
			{
				c1->enable = false;
				c2->enable = false;
				c3->enable = true;
				//p1->enable = false;
				//p2->enable = false;
				//p3->enable = false;
			}
		/*	else
			{
				c1->enable = false;
				c2->enable = false;
				c3->enable = false;
				p1->enable = false;
				p2->enable = false;
				p3->enable = false;
			}*/
		}
	//	else
	//	{
	//		if (currentChoice <= 0) //subSprite=1 (y = 150 +  1*-75)
	//		{
	//			c1->enable = false;
	//			c2->enable = false;
	//			c3->enable = false;
	//			p1->enable = true;
	//			p2->enable = false;
	//			p3->enable = false;
	//		}
	//		else if (currentChoice == 1)
	//		{
	//			c1->enable = false;
	//			c2->enable = false;
	//			c3->enable = false;
	//			p1->enable = false;
	//			p2->enable = true;
	//			p3->enable = false;
	//		}
	//		else //if (currentChoice == 2)
	//		{
	//			c1->enable = false;
	//			c2->enable = false;
	//			c3->enable = false;
	//			p1->enable = false;
	//			p2->enable = false;
	//			p3->enable = true;
	//		}
	///*		else
	//		{
	//			c1->enable = false;
	//			c2->enable = false;
	//			c3->enable = false;
	//			p1->enable = false;
	//			p2->enable = false;
	//			p3->enable = false;
	//		}*/
	//	}

		c1->update(deltaTime);
		c2->update(deltaTime);
		c3->update(deltaTime);
		//p1->update(deltaTime);
		//p2->update(deltaTime);
		//p3->update(deltaTime);
	}
}


void Menu::addSprite(string fileName, int row, int column)
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

void Menu::render(glm::mat4 globalModelTransform)
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


void Menu::setRow(int r)
{
	this->row = r;
}

void Menu::setColumn(int c)
{
	this->column = c;
}

int Menu::getRow()
{
	return this->row;
}

int Menu::getColumn()
{
	return this->column;
}

void Menu::genUV()
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

void Menu::setAnimationLoop(int row, int column, int loop, int time)
{
	this->animRow = row;
	this->animColumn = column;
	this->loopMax = loop;
	this->loopCount = 0;
	this->animationTime = time;
}

void Menu::nextAnimation()
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

void Menu::setNumberOfOptions(int num)
{
	optionNum = num;
}


void Menu::destroyComponents()
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

	if (CheckIfAllComponentNotNull() == true)
	{
		for (int i = Game::getInstance()->getObjectRef()->size() - 1; i >= 0; i--)
		{
			instance = Game::getInstance()->getObjectRef()->at(i);

			if (instance->getObjId() == c1->getObjId() || instance->getObjId() == c2->getObjId() || instance->getObjId() == c3->getObjId())
				//|| instance->getObjId() == p1->getObjId() || instance->getObjId() == p2->getObjId() || instance->getObjId() == p3->getObjId() )

			{
				Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
				Game::getInstance()->getObjectRef()->end();
			}
		}
	}
}

bool Menu::CheckIfAllComponentNotNull()
{
	//if (c1 != NULL && c2 != NULL && c3 != NULL && p1 != NULL && p2 != NULL && p3 != NULL )
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	return true;
}

void Menu::setCurrentSelection(int num)
{
	currentChoice = num;
}

int Menu::getCurrentSelection()
{
	return currentChoice;
}


void Menu::updateComponent(char indicator)
{
	//if (indicator == 'e')
	//{
	//	if (CheckIfAllComponentNotNull())
	//	{
	//		p1->setAnimationLoop(1, 7, 7, 1000);
	//		p2->setAnimationLoop(1, 7, 7, 1000);
	//		p3->setAnimationLoop(1, 7, 7, 1000);
	//	}
	//	pressed = true;
	//}
	//else
	//{
	//	pressed = false;
	//	if (CheckIfAllComponentNotNull())
	//	{
	//		p1->setAnimationLoop(1, 7, 1, 1000);
	//		p2->setAnimationLoop(1, 7, 1, 1000);
	//		p3->setAnimationLoop(1, 7, 1, 1000);

	//	}
	//}
}


