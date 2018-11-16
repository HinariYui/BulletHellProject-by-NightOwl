#include <iostream>
#include "PlayerGameObject.h"



void PlayerGameObject::update(float deltaTime)
{
	if (getVelocity() != glm::vec3(0, 0, 0))
	{
		translate(glm::normalize(getVelocity()) * 3.0f);
	}
	checkMovement();
	resetVelocityZ();

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
	checkAction();
}

void PlayerGameObject::checkAction()
{
	if (isShooting == true)
	{	
		//std::cout << "nnnnnnnnnnnnnnnnnnXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXnnn" << isShooting << std::endl;

		playerBullet= new BulletGameObject(Tag::pBullet);
		
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
	else
	{
		playerBullet = NULL;
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
