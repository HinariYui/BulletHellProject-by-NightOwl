#include <iostream>
#include <SDL_image.h>
#include "PlayerGameObject.h"



void PlayerGameObject::update(float deltaTime)
{
	if (getVelocity() != glm::vec3(0, 0, 0))
	{
		translate(glm::normalize(getVelocity()) * 3.0f);
	}
	checkMovement();
	
	shootCD++;
	if (shootCD >= 5)//shoot every 5 frame
	{
		checkAction();
		shootCD = 0;
	}
	resetVelocityZ();

	//update sprite
	timeCount += deltaTime;
	if (timeCount > animationTime / loopMax)
	{
		this->nextAnimation();
		this->genUV();
		timeCount = 0;
	}

	Game*  g = Game::getInstance();
	GLuint objNum = g->getObjectRef()->size();
	GameObject* obj = NULL;

	//for (int i = 0; i < objNum; i++)
	{
		obj = dynamic_cast<GameObject*>(g->getObjectRef()->at(7)); // enemy index=7

		if (this->getTag() != obj->getTag())
		{
			bool b = checkCollision(obj);
			//cout << "                           " << b << "    " << endl; //i << endl;
		}

	}
}

void PlayerGameObject::shoot(char status)
{
	if (status == 'z')
	{
		isShooting = true;
	}
	if (status == 'Z')
	{
		isShooting = false;
	}
	//checkAction();
}

void PlayerGameObject::checkAction()
{
	if (isShooting == true)
	{	
		//std::cout << "nnnnnnnnnnnnnnnnnnXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXnnn" << isShooting << std::endl;

		DrawableObject* playerBullet= new BulletGameObject(Tag::pBullet);
		
		dynamic_cast<GameObject*>(playerBullet)->setColor(1.0, 1.0, 1.0);
		playerBullet->setSize(10, 10);
		playerBullet->setPosition(this->getPosition() + glm::vec3(0, 18, 0));
		


		//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
		//std::cout << ":::::::::::::::::::::::::::::::::::::::::::::::::" << Game::getInstance()->getObjectRef()->capacity() << std::endl;// always 9
		//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;

		Game::getInstance()->getObjectRef()->push_back(playerBullet);

		//std::cout <<"INDEXXXXXXXXXXXXXXXXXXXXX                  = "<< index << std::endl;



		//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
		//std::cout << ":::::::::::::::::::::::::::::::::::::::::::::::::" << Game::getInstance()->getObjectRef()->capacity() << std::endl;// always 9
		//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;

	}
	
}

void PlayerGameObject::move(char direction)
{

	if (direction == 'l')
	{
		moveLeft = true;
	}
	if (direction == 'L')
	{
		moveLeft = false;
	}

	if (direction == 'r')
	{
		moveRight = true;
	}
	if (direction == 'R')
	{
		moveRight = false;
	}

	if (direction == 'u')
	{
		moveUp = true;
	}
	if (direction == 'U')
	{
		moveUp = false;
	}

	if (direction == 'd')
	{
		moveDown = true;
	}
	if (direction == 'D')
	{
		moveDown = false;
	}

}

void PlayerGameObject::checkMovement()
{
	glm::vec3 newVelocity;
	glm::vec3 newPosition;
	float halfSizeX = size.x * 0.5f +1;
	float halfSizeY = size.y * 0.5f +1;

	setVelocity(glm::vec3(0, 0, 0));

	if (moveLeft == true)
	{
		//cout << "left" << endl;
		this->addVelocity(glm::vec3(-1, 0, 0));

		if (pos.x <= -378 + halfSizeX)
		{
			newVelocity = getVelocity();
			newVelocity.x = 0;
			setVelocity(newVelocity);

			newPosition = getPosition();
			newPosition.x = -378 + halfSizeX;
			setPosition(newPosition);
		}
	}
	if (moveRight == true)
	{
		//cout << "right" << endl;
		this->addVelocity(glm::vec3(1, 0, 0));
		
		if (pos.x >= 122 - halfSizeX)
		{
			newVelocity = getVelocity();
			newVelocity.x = 0;
			setVelocity(newVelocity);
		
			newPosition = getPosition();
			newPosition.x = 122 - halfSizeX;
			setPosition(newPosition);
		}
	}

	if (moveUp == true)
	{
		//cout << "up" << endl;
		this->addVelocity(glm::vec3(0, 1, 0));
		
		if (pos.y >= 330 - halfSizeY)
		{
			newVelocity = getVelocity();
			newVelocity.y = 0;
			setVelocity(newVelocity);

			newPosition = getPosition();
			newPosition.y = 330 - halfSizeY;
			setPosition(newPosition);
		}
	}
	if (moveDown == true)
	{
		//cout << "down" << endl;
		this->addVelocity(glm::vec3(0, -1, 0));
		
		if (pos.y <= -330 + halfSizeY)
		{
			newVelocity = getVelocity();
			newVelocity.y = 0;
			setVelocity(newVelocity);

			newPosition = getPosition();
			newPosition.y = -330 + halfSizeY;
			setPosition(newPosition);
		}
	}

}


PlayerGameObject::~PlayerGameObject()
{
	//if (playerBullet != NULL)
	//{
	//	delete playerBullet;
	//}
}

//for Sprite
void PlayerGameObject::addSprite(string fileName, int row, int column)
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

void PlayerGameObject::render(glm::mat4 globalModelTransform)
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


void PlayerGameObject::setRow(int r)
{
	this->row = r;
}

void PlayerGameObject::setColumn(int c)
{
	this->column = c;
}

int PlayerGameObject::getRow()
{
	return this->row;
}

int PlayerGameObject::getColumn()
{
	return this->column;
}

void PlayerGameObject::genUV()
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

void PlayerGameObject::setAnimationLoop(int row, int column, int loop, int time)
{
	this->animRow = row;
	this->animColumn = column;
	this->loopMax = loop;
	this->loopCount = 0;
	this->animationTime = time;
}

void PlayerGameObject::nextAnimation()
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
