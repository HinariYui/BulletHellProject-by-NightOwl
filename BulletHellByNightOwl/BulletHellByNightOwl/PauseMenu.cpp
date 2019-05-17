#include <iostream>
#include <SDL_image.h>
#include "PauseMenu.h"
#include "Game.h"

PauseMenu::PauseMenu()
{
	addSprite("pauseMenu.png", 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
}

PauseMenu::PauseMenu(string fileName)
{
	addSprite(fileName, 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
}

PauseMenu::PauseMenu(vector<string> fileName,int spriteNum,int optNum)
{
	optionNum = optNum;
	this->spriteNum = spriteNum;
	addSprite(fileName.at(0), 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
	setNumberOfOptions(optionNum);
	Game::getInstance()->getObjectRef()->push_back(this);

	//c1 = new GameObject(Tag::NONE);
	//c1->setColor(0.5, 0.7, 1);
	//c1->setSize(460, 60);
	//c1->setPosition(glm::vec3(-205, 75, 0));
	//Game::getInstance()->getObjectRef()->push_back(c1);

	for (int i = 1; i <= optionNum; i++)
	{
		AnimatedSelection* p = new AnimatedSelection(fileName.at(i), 1, 1);
		p->setSize(438,129);
		p->setPosition(glm::vec3(0,150+(i*-75),0));
		options.push_back(p);
		Game::getInstance()->getObjectRef()->push_back(p);
	}

	c1 = new AnimatedSelection(fileName.at(5),1,5);
	c1->setSize(438, 129);
	c1->setPosition(glm::vec3(0, 75, 0));
	c1->setAnimationLoop(1, 5, 5, 1000);
	Game::getInstance()->getObjectRef()->push_back(c1);
	c2 = new AnimatedSelection(fileName.at(6), 1, 5);
	c2->setSize(438, 129);
	c2->setPosition(glm::vec3(0, 0, 0));
	c2->setAnimationLoop(1, 5, 5, 1000);
	Game::getInstance()->getObjectRef()->push_back(c2);
	c3 = new AnimatedSelection(fileName.at(7), 1, 5);
	c3->setSize(438, 129);
	c3->setPosition(glm::vec3(0, -75, 0));
	c3->setAnimationLoop(1, 5, 5, 1000);
	Game::getInstance()->getObjectRef()->push_back(c3);
	c4 = new AnimatedSelection(fileName.at(8), 1, 5);
	c4->setSize(438, 129);
	c4->setPosition(glm::vec3(0, -150, 0));
	c4->setAnimationLoop(1, 5, 5, 1000);
	Game::getInstance()->getObjectRef()->push_back(c4);

	p1 = new AnimatedSelection(fileName.at(9), 1, 7);// press Resume
	p1->setSize(438, 129);
	p1->setPosition(glm::vec3(0, 75, 0));
	p1->setAnimationLoop(1, 7, 1, 1000);
	p1->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p1);//press Mainmenu
	p2 = new AnimatedSelection(fileName.at(10), 1, 7);
	p2->setSize(438, 129);
	p2->setPosition(glm::vec3(0, 0, 0));
	p2->setAnimationLoop(1, 7, 1, 1000);
	p2->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p2); //press Option
	p3 = new AnimatedSelection(fileName.at(11), 1, 7);
	p3->setSize(438, 129);
	p3->setPosition(glm::vec3(0, -75, 0));
	p3->setAnimationLoop(1, 7, 1, 1000);
	p3->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p3);// press Quit
	p4 = new AnimatedSelection(fileName.at(12), 1, 7);
	p4->setSize(438, 129);
	p4->setPosition(glm::vec3(0, -150, 0));
	p4->setAnimationLoop(1, 7, 1, 1000);
	p4->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p4);


}

PauseMenu::~PauseMenu()
{

}

void PauseMenu::setColor(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}

void PauseMenu::update(float deltaTime)
{
	if(CheckIfAllComponentNotNull() == true)
	{
		if (pressed == false)
		{
			if (currentChoice <= 0) //subSprite=1 (y = 150 +  1*-75)
			{
				c1->enable = true;
				c2->enable = false;
				c3->enable = false;
				c4->enable = false;
				p1->enable = false;
				p2->enable = false;
				p3->enable = false;
				p4->enable = false;
			}
			else if (currentChoice == 1)
			{
				c1->enable = false;
				c2->enable = true;
				c3->enable = false;
				c4->enable = false;
				p1->enable = false;
				p2->enable = false;
				p3->enable = false;
				p4->enable = false;
			}
			else if (currentChoice == 2)
			{
				c1->enable = false;
				c2->enable = false;
				c3->enable = true;
				c4->enable = false;
				p1->enable = false;
				p2->enable = false;
				p3->enable = false;
				p4->enable = false;
			}
			else
			{
				c1->enable = false;
				c2->enable = false;
				c3->enable = false;
				c4->enable = true;
				p1->enable = false;
				p2->enable = false;
				p3->enable = false;
				p4->enable = false;
			}
		}
		else
		{
			if (currentChoice <= 0) //subSprite=1 (y = 150 +  1*-75)
			{
				c1->enable = false;
				c2->enable = false;
				c3->enable = false;
				c4->enable = false;
				p1->enable = true;
				p2->enable = false;
				p3->enable = false;
				p4->enable = false;
			}
			else if (currentChoice == 1)
			{
				c1->enable = false;
				c2->enable = false;
				c3->enable = false;
				c4->enable = false;
				p1->enable = false;
				p2->enable = true;
				p3->enable = false;
				p4->enable = false;
			}
			else if (currentChoice == 2)
			{
				c1->enable = false;
				c2->enable = false;
				c3->enable = false;
				c4->enable = false;
				p1->enable = false;
				p2->enable = false;
				p3->enable = true;
				p4->enable = false;
			}
			else
			{
				c1->enable = false;
				c2->enable = false;
				c3->enable = false;
				c4->enable = false;
				p1->enable = false;
				p2->enable = false;
				p3->enable = false;
				p4->enable = true;
			}
		}

		c1->update(deltaTime);
		c2->update(deltaTime);
		c3->update(deltaTime);
		c4->update(deltaTime);
		p1->update(deltaTime);
		p2->update(deltaTime);
		p3->update(deltaTime);
		p4->update(deltaTime);
	}
}

void PauseMenu::addSprite(string fileName, int row, int column)
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

void PauseMenu::render(glm::mat4 globalModelTransform)
{

	//if (currentChoice <= 0) //subSprite=1 (y = 150 +  1*-75)
	//{
	//	c1->addSprite(Game::getInstance()->pMenuSprite.at(4), 1, 5);
	//	c1->setPosition(glm::vec3(0, 75,0)); 
	//}
	//else if (currentChoice == 1)
	//{
	//	c1->addSprite(Game::getInstance()->pMenuSprite.at(5), 1, 5);
	//	c1->setPosition(glm::vec3(0, 0, 0));
	//}
	//else if (currentChoice == 2)
	//{
	//	c1->addSprite(Game::getInstance()->pMenuSprite.at(6), 1, 5);
	//	c1->setPosition(glm::vec3(0, -75, 0));
	//}
	//else
	//{
	//	c1->setPosition(glm::vec3(0, -150, 0));
	//}

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


void PauseMenu::setRow(int r)
{
	this->row = r;
}

void PauseMenu::setColumn(int c)
{
	this->column = c;
}

int PauseMenu::getRow()
{
	return this->row;
}

int PauseMenu::getColumn()
{
	return this->column;
}

void PauseMenu::genUV()
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

void PauseMenu::setAnimationLoop(int row, int column, int loop, int time)
{
	this->animRow = row;
	this->animColumn = column;
	this->loopMax = loop;
	this->loopCount = 0;
	this->animationTime = time;
}

void PauseMenu::nextAnimation()
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

void PauseMenu::setNumberOfOptions(int num)
{
	optionNum = num;
}


void PauseMenu::destroyComponents()
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

			if (instance->getObjId() == c1->getObjId() || instance->getObjId() == c2->getObjId() || instance->getObjId() == c3->getObjId() || instance->getObjId() == c4->getObjId()
				|| instance->getObjId() == p1->getObjId() || instance->getObjId() == p2->getObjId() || instance->getObjId() == p3->getObjId() || instance->getObjId() == p4->getObjId())

			{
				Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
				Game::getInstance()->getObjectRef()->end();
			}
		}
	}
}

bool PauseMenu::CheckIfAllComponentNotNull()
{
	if (c1!=NULL && c2 != NULL&& c3 != NULL&& c4 != NULL && p1 != NULL && p2 != NULL && p3 != NULL && p4 != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PauseMenu::setCurrentSelection(int num)
{
	currentChoice = num;
}

int PauseMenu::getCurrentSelection()
{
	return currentChoice;
}


void PauseMenu::updateComponent(char indicator)
{
	if (indicator == 'e')
	{
		pressed = true;
		p1->setAnimationLoop(1, 7, 7, 1000);
		p2->setAnimationLoop(1, 7, 7, 1000);
		p3->setAnimationLoop(1, 7, 7, 1000);
		p4->setAnimationLoop(1, 7, 7, 1000);

	}
	else
	{
		pressed = false;
		p1->setAnimationLoop(1, 7, 1, 1000);
		p2->setAnimationLoop(1, 7, 1, 1000);
		p3->setAnimationLoop(1, 7, 1, 1000);
		p4->setAnimationLoop(1, 7, 1, 1000);
	}
}

