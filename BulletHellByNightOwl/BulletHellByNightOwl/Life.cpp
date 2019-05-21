#include "stdafx.h"
#include "Life.h"
#include "Game.h"
#include "SquareMeshVbo.h"
#include <SDL_image.h>

Life::Life(string fileName, int row, int column) : GameObject(NONE)
{
	addSprite(fileName, row, column);
}


void Life::addSprite(string fileName, int row, int column)
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

Life::~Life()
{
}

void Life::render(glm::mat4 globalModelTransform)
{
	if (isRendered)
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
}

void Life::update(float deltaTime)
{
	//timeCount += deltaTime;
	//if (timeCount > animationTime / loopMax)
	//{
	//	this->nextAnimation();
	//	//this->genUV();
	//	timeCount = 0;
	//}
}

void Life::setRow(int r)
{
	this->row = r;
}

void Life::setColumn(int c)
{
	this->column = c;
}

int Life::getRow()
{
	return this->row;
}

int Life::getColumn()
{
	return this->column;
}

void Life::genUV()
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

void Life::loopUV(float deltaTime)
{
	float speed = deltaTime * 0.00015f;
	uv[1] += speed;
	uv[3] += speed;
	uv[5] += speed;
	uv[7] += speed;
}

void Life::setAnimationLoop(int row, int column, int loop, int time)
{
	this->animRow = row;
	this->animColumn = column;
	this->loopMax = loop;
	this->loopCount = 0;
	this->animationTime = time;
}

void Life::nextAnimation()
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

void Life::setRender(bool boolean)
{
	isRendered = boolean;
}
