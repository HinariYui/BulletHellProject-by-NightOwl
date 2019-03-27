#include <iostream>
#include "Boss2.h"
#include "EnemyBullet.h"
#include "SpecialEnemyBullet.h"
#include "Game.h"



Boss2::Boss2(Tag enemy, string fileName, int row, int col) : SpriteObject(fileName, row, col)
{
	setVelocity(glm::vec3(0, -1, 0));
	tag = enemy;
	state = MOVEIN2;
	idleTime = rand() % 1000 + 2000;
	stateTime = 0;
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, 0.25f, glm::vec3(0.0f, 0.0f, 1.0f)); //0.1f -> radiant
	hp = maxHP;
	HPbar = new GameObject(NONE);
	HPbar->setSize(HPsize, 20);
	HPbar->setPosition(glm::vec3(HPpos, 340, 0));
	HPbar->setColor(1, 0.85, 0);
}

void Boss2::update(float deltaTime)
{
	HPpercentage = (float)hp / (float)maxHP;
	HPbar->setSize(HPsize * HPpercentage, 20);
	missingHP = (float)maxHP - (float)hp;
	HPbar->setPosition(glm::vec3(HPpos - missingHP / 4, 340, 0));
	GameObject::update(deltaTime);

	if (state == IDLE2)
	{
		updateIDLE(deltaTime);
	}
	else if (state == MOVEIN2)
	{
		updateMoveIn(deltaTime);
		hp = maxHP;
	}
	else if (state == ATK2_1)
	{
		updateATK1(deltaTime);
	}
	else if (state == ATK2_2)
	{
		updateATK2(deltaTime);
	}
	else if (state == ATK2_3)
	{
		updateATK3(deltaTime);
	}
}

void Boss2::updateIDLE(float deltaTime)
{
	stateTime += deltaTime;
	if (stateTime >= idleTime)
	{
		stateTime = 0;
		//int pattern = rand() % 3 + 1;
		//if (pattern == 1)
		{
			state = ATK2_1;
		}
		//else if (pattern == 2)
		//{
		//	state = ATK2;
		//}
		//else
		//{
		//	state = ATK3;
		//}
	}
}

void Boss2::updateMoveIn(float deltaTime)
{
	float y = getPosition().y;
	if (y <= 200)
	{
		state = IDLE2;
		setVelocity(glm::vec3(0, 0, 0));
	}
}

void Boss2::updateATK1(float deltaTime)
{
	stateTime += deltaTime;

	//if (shootCount == 0) 
	{
		shoot1_2A();
		//shootCount++;
	}
	if (stateTime >= 4000)
	{
		stateTime = 0;
		state = IDLE2;
		idleTime = rand() % 1000 + 2000;
		//shootCount = 0;
		isShooting = false;
		isShooting2 = false;
		isShooting3 = false;
		isShooting4 = false;
		isShooting5 = false;
		isShooting6 = false;
		isShooting7 = false;
		isShooting8 = false;
		isShooting9 = false;
		isShooting10 = false;
	}
}

void Boss2::updateATK2(float deltaTime)
{
	stateTime += deltaTime;
	ATKCount += deltaTime;
	if (ATKCount >= 100) // shoot every 0.1 sec
	{
		shoot1_2A();
		shootSound.play();
		ATKCount = 0;
	}
	if (stateTime >= 3000)
	{
		stateTime = 0;
		state = IDLE2;
		idleTime = rand() % 1000 + 3000;
	}
}

void Boss2::updateATK3(float deltaTime)
{

	stateTime += deltaTime;
	ATKCount += deltaTime;
	if (ATKCount >= 100) // shoot every 0.1 sec
	{
		shoot2_1D();
		shootSound.play();
		ATKCount = 0;
	}
	if (stateTime >= 3000)
	{
		stateTime = 0;
		state = IDLE2;
		idleTime = rand() % 1000 + 3000;
	}
}

void Boss2::shoot2_1C() // pattern 2_1C
{
	enemyBullet1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	EnemyBullet *eb1 = dynamic_cast<EnemyBullet*>(enemyBullet1);
	if (eb1)
	{
		eb1->setColor(1.0, 0.0, 0.0);
		eb1->setSize(10, 10);
		eb1->setPosition(this->getPosition());
		eb1->setVelocity(velD);
		glm::vec4 temp(velD.x, velD.y, velD.z, 1);
		temp = rotationMatrix * temp;
		velD.x = temp.x;
		velD.y = temp.y;
		velD.z = temp.z;
	}
	Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

	enemyBullet2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	EnemyBullet *eb2 = dynamic_cast<EnemyBullet*>(enemyBullet2);
	if (eb2)
	{
		eb2->setColor(1.0, 0.0, 0.0);
		eb2->setSize(10, 10);
		eb2->setPosition(this->getPosition());
		eb2->setVelocity(velR);
		glm::vec4 temp(velR.x, velR.y, velR.z, 1);
		temp = rotationMatrix * temp;
		velR.x = temp.x;
		velR.y = temp.y;
		velR.z = temp.z;
	}
	Game::getInstance()->getObjectRef()->push_back(enemyBullet2);

	enemyBullet3 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	EnemyBullet *eb3 = dynamic_cast<EnemyBullet*>(enemyBullet3);
	if (eb3)
	{
		eb3->setColor(1.0, 0.0, 0.0);
		eb3->setSize(10, 10);
		eb3->setPosition(this->getPosition());
		eb3->setVelocity(velU);
		glm::vec4 temp(velU.x, velU.y, velU.z, 1);
		temp = rotationMatrix * temp;
		velU.x = temp.x;
		velU.y = temp.y;
		velU.z = temp.z;
	}
	Game::getInstance()->getObjectRef()->push_back(enemyBullet3);

	enemyBullet4 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	EnemyBullet *eb4 = dynamic_cast<EnemyBullet*>(enemyBullet4);
	if (eb4)
	{
		eb4->setColor(1.0, 0.0, 0.0);
		eb4->setSize(10, 10);
		eb4->setPosition(this->getPosition());
		eb4->setVelocity(velL);
		glm::vec4 temp(velL.x, velL.y, velL.z, 1);
		temp = rotationMatrix * temp;
		velL.x = temp.x;
		velL.y = temp.y;
		velL.z = temp.z;
	}
	Game::getInstance()->getObjectRef()->push_back(enemyBullet4);
}

void Boss2::shoot1_2A() // pattern 1_2A
{
	bulletSpeed = 5.0f;
	float bulletSpeed2 = 7.0f;
	float bulletSpeed3 = 9.0f;

	glm::vec3 ePos = this->getPosition();
	glm::vec3 pPos = Game::getInstance()->getPlayerRef()->getPosition();

	glm::vec3 bulDir;
	glm::vec3 bulDir2;
	glm::vec3 bulDir3;

	glm::vec3 bul1PosTemp;
	glm::vec3 bul2PosTemp;
	glm::vec3 bul3PosTemp;
	glm::vec3 bul4PosTemp;
	glm::vec3 bul5PosTemp;

	if (isShooting == false)
	{
		shootSound.play();

		// Bullet 1

		enemyBullet1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
		enemyBullet1->setSize(60, 60);
		enemyBullet1->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(-1, 0, 0));

		dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

		// Bullet2

		enemyBullet2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

		enemyBullet2->setSize(60, 60);
		enemyBullet2->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(1, 0, 0));

		dynamic_cast<GameObject*>(enemyBullet2)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet2);

		// Bullet 3

		enemyBullet3 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

		enemyBullet3->setSize(60, 60);
		enemyBullet3->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(-1, -1, 0));

		dynamic_cast<GameObject*>(enemyBullet3)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet3);

		// Bullet 4

		enemyBullet4 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

		enemyBullet4->setSize(60, 60);
		enemyBullet4->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(1, -1, 0));

		dynamic_cast<GameObject*>(enemyBullet4)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet4);

		// Bullet 5

		enemyBullet5 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

		enemyBullet5->setSize(60, 60);
		enemyBullet5->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(0, -1, 0));

		dynamic_cast<GameObject*>(enemyBullet5)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet5);

		isShooting = true;
	}

	// Bullet1 OOB
	if (dynamic_cast<EnemyBullet*>(enemyBullet1)->oob == true && isShooting2 == false)
	{
		bul1PosTemp = enemyBullet1->getPosition();
		bul1PosTemp.x = -462 - 20;
		DrawableObject* enemyBullet1_1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
		DrawableObject* enemyBullet1_2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

		enemyBullet1_1->setSize(40, 40);
		enemyBullet1_2->setSize(40, 40);

		enemyBullet1_1->setPosition(bul1PosTemp);
		enemyBullet1_2->setPosition(bul1PosTemp);

		bulDir2 = glm::normalize(glm::vec3(1, -0.5f, 0));
		bulDir3 = glm::normalize(glm::vec3(1, -0.8f, 0));

		dynamic_cast<GameObject*>(enemyBullet1_1)->setVelocity(bulDir2 * bulletSpeed2);
		dynamic_cast<GameObject*>(enemyBullet1_2)->setVelocity(bulDir3 * bulletSpeed2);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet1_1);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet1_2);

		isShooting2 = true;
	}
	// Bullet2 OOB
	if (dynamic_cast<EnemyBullet*>(enemyBullet2)->oob == true && isShooting3 == false)
	{
		cout << "test" << endl;
		bul2PosTemp = enemyBullet2->getPosition();
		bul2PosTemp.x = 38 + 20;
		DrawableObject* enemyBullet2_1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
		DrawableObject* enemyBullet2_2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

		enemyBullet2_1->setSize(40, 40);
		enemyBullet2_2->setSize(40, 40);

		enemyBullet2_1->setPosition(bul2PosTemp);
		enemyBullet2_2->setPosition(bul2PosTemp);

		bulDir2 = glm::normalize(glm::vec3(-1, -0.5f, 0));
		bulDir3 = glm::normalize(glm::vec3(-1, -0.8f, 0));

		dynamic_cast<GameObject*>(enemyBullet2_1)->setVelocity(bulDir2 * bulletSpeed2);
		dynamic_cast<GameObject*>(enemyBullet2_2)->setVelocity(bulDir3 * bulletSpeed2);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet2_1);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet2_2);

		isShooting3 = true;
	}
	////Bullet3 OOB
	//if (dynamic_cast<EnemyBullet*>(enemyBullet1)->oob == true && isShooting2 == false)
	//{
	//	bul1PosTemp = enemyBullet1->getPosition();
	//	bul1PosTemp.x = -462 - 20;
	//	DrawableObject* enemyBullet1_1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	//	DrawableObject* enemyBullet1_2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	//
	//	enemyBullet1_1->setSize(40, 40);
	//	enemyBullet1_2->setSize(40, 40);
	//
	//	enemyBullet1_1->setPosition(bul1PosTemp);
	//	enemyBullet1_2->setPosition(bul1PosTemp);
	//
	//	bulDir2 = glm::normalize(glm::vec3(1, -0.5f, 0));
	//	bulDir3 = glm::normalize(glm::vec3(1, -0.8f, 0));
	//
	//	dynamic_cast<GameObject*>(enemyBullet1_1)->setVelocity(bulDir2 * bulletSpeed2);
	//	dynamic_cast<GameObject*>(enemyBullet1_2)->setVelocity(bulDir3 * bulletSpeed2);
	//
	//	Game::getInstance()->getObjectRef()->push_back(enemyBullet1_1);
	//	Game::getInstance()->getObjectRef()->push_back(enemyBullet1_2);
	//
	//	isShooting2 = true;
	//}
	////Bullet4 OOB
	//if (dynamic_cast<EnemyBullet*>(enemyBullet1)->oob == true && isShooting2 == false)
	//{
	//	bul1PosTemp = enemyBullet1->getPosition();
	//	bul1PosTemp.x = -462 - 20;
	//	DrawableObject* enemyBullet1_1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	//	DrawableObject* enemyBullet1_2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	//
	//	enemyBullet1_1->setSize(40, 40);
	//	enemyBullet1_2->setSize(40, 40);
	//
	//	enemyBullet1_1->setPosition(bul1PosTemp);
	//	enemyBullet1_2->setPosition(bul1PosTemp);
	//
	//	bulDir2 = glm::normalize(glm::vec3(1, -0.5f, 0));
	//	bulDir3 = glm::normalize(glm::vec3(1, -0.8f, 0));
	//
	//	dynamic_cast<GameObject*>(enemyBullet1_1)->setVelocity(bulDir2 * bulletSpeed2);
	//	dynamic_cast<GameObject*>(enemyBullet1_2)->setVelocity(bulDir3 * bulletSpeed2);
	//
	//	Game::getInstance()->getObjectRef()->push_back(enemyBullet1_1);
	//	Game::getInstance()->getObjectRef()->push_back(enemyBullet1_2);
	//
	//	isShooting2 = true;
	//}
	//// Bullet5 OOB
	//if (dynamic_cast<EnemyBullet*>(enemyBullet1)->oob == true && isShooting2 == false)
	//{
	//	bul1PosTemp = enemyBullet1->getPosition();
	//	bul1PosTemp.x = -462 - 20;
	//	DrawableObject* enemyBullet1_1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	//	DrawableObject* enemyBullet1_2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	//
	//	enemyBullet1_1->setSize(40, 40);
	//	enemyBullet1_2->setSize(40, 40);
	//
	//	enemyBullet1_1->setPosition(bul1PosTemp);
	//	enemyBullet1_2->setPosition(bul1PosTemp);
	//
	//	bulDir2 = glm::normalize(glm::vec3(1, -0.5f, 0));
	//	bulDir3 = glm::normalize(glm::vec3(1, -0.8f, 0));
	//
	//	dynamic_cast<GameObject*>(enemyBullet1_1)->setVelocity(bulDir2 * bulletSpeed2);
	//	dynamic_cast<GameObject*>(enemyBullet1_2)->setVelocity(bulDir3 * bulletSpeed2);
	//
	//	Game::getInstance()->getObjectRef()->push_back(enemyBullet1_1);
	//	Game::getInstance()->getObjectRef()->push_back(enemyBullet1_2);
	//
	//	isShooting2 = true;
	//}
}

void Boss2::shoot2_1D()
{
	DrawableObject* specialBullet1 = new SpecialEnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	specialBullet1->setSize(30, 30);
	specialBullet1->setPosition(this->getPosition());
	Game::getInstance()->getObjectRef()->push_back(specialBullet1);
}

void Boss2::move()
{

}


void Boss2::render(glm::mat4 globalModelTransform)
{
	SpriteObject::render(globalModelTransform);
	if (state != MOVEIN2)
	{
		HPbar->render(globalModelTransform);
	}
}

Boss2::~Boss2()
{
	if (enemyBullet1 != NULL)
	{
		delete enemyBullet1;
	}
}
