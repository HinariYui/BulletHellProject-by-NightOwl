#include "BulletGameObject.h"
#include <SDL_image.h>
#include "Game.h"

unsigned int BulletGameObject::bulletNum = 0;

#define LEFTBORDER -462
#define	RIGHTBORDER 38

BulletGameObject::~BulletGameObject()
{
	bulletNum--;
}

void BulletGameObject::update(float deltaTime)
{
	float constant = deltaTime * 0.05;
	translate(constant*getVelocity());

	float halfSizeX = (size.x * 0.5f)+4;
	float halfSizeY = (size.y * 0.5f)+4;

	if ((pos.x > RIGHTBORDER +halfSizeX) || (pos.x < LEFTBORDER -halfSizeX) || (pos.y > 330+halfSizeY) || (pos.y < -330-halfSizeY))
	{
		for (int i = Game::getInstance()->getObjectRef()->size() - 1; i >= 0; i--)
		{
			DrawableObject* instance = Game::getInstance()->getObjectRef()->at(i);

			if (instance->getObjId() == objID)
			{
				Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
				Game::getInstance()->getObjectRef()->end();
			}
			//cout << "__________________________________________" << Game::getInstance()->getObjectRef()->size() << endl;
		}
	}

	Game*  g = Game::getInstance();
	GLuint objNum = g->getObjectRef()->size();
	GameObject* obj = NULL;

	//left border(-509+131=-378, 0, 0) >> -462
	//right border(381-259=122, 0, 0) >> 38
	//top border(0, 345-15=330, 0)
	//bottom border(0,-345+15=-330, 0)

	for (int i = objNum -1; i >= 0; i--)
	{
		obj = dynamic_cast<GameObject*>(g->getObjectRef()->at(i));
		if (obj)
		{
			if (this->getTag() != obj->getTag())
			{
				bool b = this->checkCollision(obj);
				//cout << "                           " << b << "    " << endl; //i << endl;
			}
		}

	}
}

//for Sprite
void BulletGameObject::addSprite(string fileName, int row, int column)
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

void BulletGameObject::render(glm::mat4 globalModelTransform)
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
	//currentMatrix = glm::scale(currentMatrix, glm::vec3(5, 5, 1)); //5 times bigger

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(modeId, 1);
		squareMesh->adjustTexcoord(uv);
		squareMesh->render();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}


void BulletGameObject::setRow(int r)
{
	this->row = r;
}

void BulletGameObject::setColumn(int c)
{
	this->column = c;
}

int BulletGameObject::getRow()
{
	return this->row;
}

int BulletGameObject::getColumn()
{
	return this->column;
}

void BulletGameObject::genUV()
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

void BulletGameObject::setAnimationLoop(int row, int column, int loop, int time)
{
	this->animRow = row;
	this->animColumn = column;
	this->loopMax = loop;
	this->loopCount = 0;
	this->animationTime = time;
}

void BulletGameObject::nextAnimation()
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


