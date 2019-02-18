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

PauseMenu::PauseMenu(vector<string> fileName,int spriteNum)
{
	addSprite(fileName.at(0), 1, 1);
	setAnimationLoop(1, 1, 1, 1000);
	setNumberOfOptions(spriteNum-1);

	for (int i = 1; i <= optionNum; i++)
	{
		PauseMenu* p = new PauseMenu(fileName.at(i));
		p->setSize(450.0,50.0);
		p->setPosition(glm::vec3(0,0+(i*75),0));
		options.push_back(p);
		Game::getInstance()->getObjectRef()->push_back(p);
	}
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
	//if (IsInvincible()) //in the process of making blinking selection
	//{
	//	if (blinkTime >= 100)
	//	{
	//		blinkTime = 0;
	//		isBlinking = !isBlinking;
	//	}
	//	if (!isBlinking)
	//	{
	//		return;
	//	}
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
	for (int j = options.size() - 1; j >= 0; j--)
	{
		for (int i = Game::getInstance()->getObjectRef()->size() - 1; i >= 0; i--)
		{
			DrawableObject* instance = Game::getInstance()->getObjectRef()->at(i);

			if (instance->getObjId() == options.at(j)->getObjId())
			{
				Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
				Game::getInstance()->getObjectRef()->end();
			}
		}
	}

}





