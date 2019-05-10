#include <iostream>
#include <SDL_image.h>
#include "OptionMenu.h"
#include "Game.h"

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
	optionNum = optNum;
	this->spriteNum = spriteNum;
	addSprite(fileName.at(0), 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
	setNumberOfOptions(optionNum);
	Game::getInstance()->getObjectRef()->push_back(this);

	c1 = new GameObject(Tag::NONE);
	c1->setColor(0.5, 0.7, 1);
	c1->setSize(460, 210);
	c1->setPosition(glm::vec3(0, 90, 0));
	Game::getInstance()->getObjectRef()->push_back(c1);

	for (int i = 1; i <= optionNum; i++)
	{
		AnimatedSelection* p = new AnimatedSelection(fileName.at(i), 1, 1);
		p->setSize(450, 200);
		p->setPosition(glm::vec3(0,300+(i*-210), 0));
		options.push_back(p);
		Game::getInstance()->getObjectRef()->push_back(p);
	}

	c2 = new AnimatedSelection(fileName.at(3), 1, 1);//ON BGM
	c2->setSize(450, 200);
	c2->setPosition(glm::vec3(0, 90, 0));
	Game::getInstance()->getObjectRef()->push_back(c2);

	c3 = new AnimatedSelection(fileName.at(3), 1, 1);//ON SFX
	c3->setSize(450, 200);
	c3->setPosition(glm::vec3(0, -120, 0));
	Game::getInstance()->getObjectRef()->push_back(c3);

	c4 = new AnimatedSelection(fileName.at(4), 1, 1);//OFF BGM
	c4->setSize(450, 200);
	c4->setPosition(glm::vec3(0, 90, 0));
	c4->enable = false;
	Game::getInstance()->getObjectRef()->push_back(c4);

	c5 = new AnimatedSelection(fileName.at(4), 1, 1);//OFF SFX
	c5->setSize(450, 200);
	c5->setPosition(glm::vec3(0, -120, 0));
	c5->enable = false;
	Game::getInstance()->getObjectRef()->push_back(c5);


	p1 = new AnimatedSelection(fileName.at(5), 1, 1);//0 BGM
	p1->setSize(450, 200);
	p1->setPosition(glm::vec3(0, 90, 0));
	p1->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p1);

	p2 = new AnimatedSelection(fileName.at(5), 1, 1);//0 SFX
	p2->setSize(450, 200);
	p2->setPosition(glm::vec3(0, -120, 0));
	p2->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p2);


	p3 = new AnimatedSelection(fileName.at(6), 1, 1);//25 BGM
	p3->setSize(450, 200);
	p3->setPosition(glm::vec3(0, 90, 0));
	p3->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p3);

	p4 = new AnimatedSelection(fileName.at(6), 1, 1);//25 SFX
	p4->setSize(450, 200);
	p4->setPosition(glm::vec3(0, -120, 0));
	p4->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p4);


	p5 = new AnimatedSelection(fileName.at(7), 1, 1);//50 BGM
	p5->setSize(450, 200);
	p5->setPosition(glm::vec3(0, 90, 0));
	Game::getInstance()->getObjectRef()->push_back(p5);

	p6 = new AnimatedSelection(fileName.at(7), 1, 1);//50 SFX
	p6->setSize(450, 200);
	p6->setPosition(glm::vec3(0, -120, 0));
	Game::getInstance()->getObjectRef()->push_back(p6);


	p7 = new AnimatedSelection(fileName.at(8), 1, 1);//75 BGM
	p7->setSize(450, 200);
	p7->setPosition(glm::vec3(0, 90, 0));
	p7->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p7);

	p8 = new AnimatedSelection(fileName.at(8), 1, 1);//75 SFX
	p8->setSize(450, 200);
	p8->setPosition(glm::vec3(0, -120, 0));
	p8->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p8);


	p9 = new AnimatedSelection(fileName.at(9), 1, 1);//100 BGM
	p9->setSize(450, 200);
	p9->setPosition(glm::vec3(0, 90, 0));
	p9->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p9);

	p10 = new AnimatedSelection(fileName.at(9), 1, 1);//100 SFX
	p10->setSize(450, 200);
	p10->setPosition(glm::vec3(0, -120, 0));
	p10->enable = false;
	Game::getInstance()->getObjectRef()->push_back(p10);

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
	if (currentChoice <= 0) //BGM
	{
		c1->setPosition(glm::vec3(0, 90, 0));

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

		if (volBGM <= 0)//0% volume
		{
			p1->enable = true;
			p3->enable = false;
			p5->enable = false;
			p7->enable = false;
			p9->enable = false;
		}
		else if (volBGM == 1)//25% volume
		{
			p1->enable = false;
			p3->enable = true;
			p5->enable = false;
			p7->enable = false;
			p9->enable = false;
		}
		else if (volBGM == 2)//50% volume
		{
			p1->enable = false;
			p3->enable = false;
			p5->enable = true;
			p7->enable = false;
			p9->enable = false;
		}
		else if (volBGM == 3)//75% volume
		{
			p1->enable = false;
			p3->enable = false;
			p5->enable = false;
			p7->enable = true;
			p9->enable = false;
		}
		else //100% volume
		{
			p1->enable = false;
			p3->enable = false;
			p5->enable = false;
			p7->enable = false;
			p9->enable = true;
		}
	}
	else //SFX
	{
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

		c1->setPosition(glm::vec3(0, -120, 0));
		if (volSFX <= 0)//0% volume
		{
			p2->enable = true;
			p4->enable = false;
			p6->enable = false;
			p8->enable = false;
			p10->enable = false;
		}
		else if (volSFX == 1)//25% volume
		{
			p2->enable = false;
			p4->enable = true;
			p6->enable = false;
			p8->enable = false;
			p10->enable = false;
		}
		else if (volSFX == 2)//50% volume
		{
			p2->enable = false;
			p4->enable = false;
			p6->enable = true;
			p8->enable = false;
			p10->enable = false;
		}
		else if (volSFX == 3)//75% volume
		{
			p2->enable = false;
			p4->enable = false;
			p6->enable = false;
			p8->enable = true;
			p10->enable = false;
		}
		else //100% volume
		{
			p2->enable = false;
			p4->enable = false;
			p6->enable = false;
			p8->enable = false;
			p10->enable = true;
		}
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
		if (instance->getObjId() == c1->getObjId())
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

bool OptionMenu::CheckIfAllComponentNotNull()
{
	if (c1 != NULL && c2 != NULL && c3 != NULL && c4 != NULL && p1 != NULL && p2 != NULL && p3 != NULL && p4 != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

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
		if (volBGM < 5)
		{
			volBGM++;
		}
	}
	else
	{
		if (volSFX < 5)
		{
			volSFX++;
		}
	}
	cout << "BGM = " << volBGM << endl;
	cout << "SFX = " << volSFX << endl;

}
void OptionMenu::decreaseVol()
{
	if (currentChoice <= 0)
	{
		if (volBGM > 0)
		{
			volBGM--;
		}
	}
	else
	{
		if (volSFX > 0)
		{
			volSFX--;
		}
	}

	cout << "BGM = " << volBGM << endl;
	cout << "SFX = " << volSFX << endl;
}

void OptionMenu::toggleOnOff()
{
	if (currentChoice <= 0)//BGM
	{
		if (onBGM == true)
		{
			onBGM = false;
		}
		else
		{
			onBGM = true;
		}
	}
	else//SFX
	{
		if (onSFX == true)
		{
			onSFX = false;
		}
		else
		{
			onSFX = true;
		}
	}
}
