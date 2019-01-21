#include <iostream>
#include <SDL_image.h>
#include "PlayerGameObject.h"
#include "Game.h"



void PlayerGameObject::update(float deltaTime)
{

	if (getVelocity() != glm::vec3(0, 0, 0))
	{
		if (Game::getInstance()->shiftPressed == false)
		{
			translate(glm::normalize(getVelocity()) * 3.0f);
		}
		else
		{
			translate(glm::normalize(getVelocity()) * 1.5f);
		}

	}
	checkMovement();
	
	shootCD += deltaTime;
	if (shootCD >= 50)//shoot every 0.05 sec
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

	if (!IsInvincible())
	{
		for (int i = 0; i < objNum; i++)
		{
			obj = dynamic_cast<GameObject*>(g->getObjectRef()->at(i)); // enemy index=7
			if (obj)
			{
				if (this->getTag() != obj->getTag())
				{
					bool b = checkCollision(obj);
					//cout << "                           " << b << "    " << endl; //i << endl;
				}
			}
		}
	}
	else
	{
		invincibleTime += deltaTime;
		blinkTime += deltaTime;
		if (invincibleTime >= 3000)
		{
			SetInvincible(false);
		}
	}

	if (Game::getInstance()->playerIsDead)
	{
		for (int i = Game::getInstance()->getObjectRef()->size() - 1; i >= 0; i--)
		{
			DrawableObject* instance = Game::getInstance()->getObjectRef()->at(i);

			if (instance->getObjId() == this->objID)
			{
				Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
				Game::getInstance()->getObjectRef()->end();
			}
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
	
		glm::vec3 bulletVel[3] = { glm::normalize(glm::vec3(-1, 4, 0)) ,glm::vec3(0, 1, 0) ,glm::normalize(glm::vec3(1, 4, 0)) };
	
		//std::cout << "nnnnnnnnnnnnnnnnnnXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXnnn" << isShooting << std::endl;

		if (Game::getInstance()->shiftPressed == true)
		{
			bulletVel[0] = glm::normalize(glm::vec3(-0.5, 4, 0));
			bulletVel[2] = glm::normalize(glm::vec3(0.5, 4, 0));
		}
	

		for (int i = 0; i < 3; i++)
		{
			DrawableObject* bullet = new BulletGameObject(Tag::pBullet);

			BulletGameObject * playerBullet = dynamic_cast<BulletGameObject*>(bullet);
			playerBullet->setColor(1.0, 1.0, 1.0);
			playerBullet->setSize(5, 5);
			playerBullet->setPosition(this->getPosition());// +glm::vec3(0, 18, 0));
			playerBullet->setVelocity(bulletSpeed * bulletVel[i]);

			Game::getInstance()->getObjectRef()->push_back(bullet);
		}





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
	if (moveLeft == false && moveRight == false && moveUp == false && moveDown == false && isIdle == false)
	{
		setAnimationLoop(1, 1, 4, 1000);
		isIdle = true;
	}

	if (moveLeft == true)
	{
		//cout << "left" << endl;
		this->addVelocity(glm::vec3(-1, 0, 0));

		if (pos.x <= -462 + halfSizeX)
		{
			newVelocity = getVelocity();
			newVelocity.x = 0;
			setVelocity(newVelocity);

			newPosition = getPosition();
			newPosition.x = -462 + halfSizeX;
			setPosition(newPosition);
		}
	}
	if (moveRight == true)
	{
		//cout << "right" << endl;
		this->addVelocity(glm::vec3(1, 0, 0));
		
		if (pos.x >= 38 - halfSizeX)
		{
			newVelocity = getVelocity();
			newVelocity.x = 0;
			setVelocity(newVelocity);
		
			newPosition = getPosition();
			newPosition.x = 38 - halfSizeX;
			setPosition(newPosition);
		}
	}

	if (moveUp == true)
	{
		if (isIdle == true)
		{
			setAnimationLoop(2,1,4,1000);
			isIdle = false;
		}

		//cout << "up" << endl;
		this->addVelocity(glm::vec3(0, 1, 0));

		//setAnimationLoop(2, 1, 4, 1000);
		
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
		if (isIdle == true)
		{
			setAnimationLoop(2, 1, 4, 1000);
			isIdle = false;
		}

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
	
	//setAnimationLoop(1, 1, 4, 1000);

	
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
	if (IsInvincible())
	{
		if (blinkTime >= 100)
		{
			blinkTime = 0;
			isBlinking = !isBlinking;
		}
		if (!isBlinking)
		{
			return;
		}
	}




	SquareMeshVbo *squareMesh = dynamic_cast<SquareMeshVbo *> (Game::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = Game::getInstance()->getRenderer()->getModelMatrixAttrId();
	GLuint modeId = Game::getInstance()->getRenderer()->getModeUniformId();

	glBindTexture(GL_TEXTURE_2D, texture);
	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}

	glm::mat4 currentMatrix = this->getTransform();
	currentMatrix = glm::scale(currentMatrix, glm::vec3(5, 5, 1)); //5 times bigger

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

bool PlayerGameObject::IsInvincible()
{
	return invincible;
}

void PlayerGameObject::SetInvincible(bool inv)
{
	invincible = inv;
}
