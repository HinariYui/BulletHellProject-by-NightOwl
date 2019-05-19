#include <iostream>
#include "Boss2.h"
#include "EnemyBullet.h"
#include "SpecialEnemyBullet.h"
#include "Laser.h"
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
	HPbg = new SpriteObject("HP-bg.png", 1, 1);
	HPbar = new SpriteObject("HP-green.png", 1, 1);
	HPframe = new SpriteObject("HP-tube.png", 1, 1);
	HPbg->setSize(HPsize, 20);
	HPbar->setSize(HPsize, 20);
	HPframe->setSize(HPsize, 20);
	HPbar->setPosition(glm::vec3(HPpos, 340, 0));
	HPbg->setPosition(glm::vec3(HPpos, 340, 0));
	HPframe->setPosition(glm::vec3(HPpos, 340, 0));
}

void Boss2::update(float deltaTime)
{
	HPpercentage = (float)hp / (float)maxHP;
	if (HPpercentage <= 0.67 && HPpercentage > 0.33) HPbar->addSprite("HP-yellow.png", 1, 1);
	else if (HPpercentage <= 0.33) HPbar->addSprite("HP-red.png", 1, 1);
	HPbar->setSize(HPsize * HPpercentage, 20);
	missingHP = (float)maxHP - (float)hp;
	HPbar->setPosition(glm::vec3(HPpos - missingHP / (maxHP / (HPsize / 2)), 340, 0));
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
		int pattern = rand() % 2 + 1;
		if (pattern == 1)
		{
			state = ATK2_1;
		}
		else if (pattern == 2)
		{
			state = ATK2_3;
		}
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
	if (stateTime >= 6500) // 6.5 sec
	{
		stateTime = 0;
		state = IDLE2;
		idleTime = rand() % 1000 + 1000;
		isShooting = false;
		isShooting2 = false;
		isShooting3 = false;
		isShooting4 = false;
		isShooting5 = false;
		isShooting6 = false;
		isShooting1_1 = true;
		isShooting1_2 = true;
		isShooting2_1 = true;
		isShooting2_2 = true;
		isShooting3_1 = true;
		isShooting3_2 = true;
		isShooting4_1 = true;
		isShooting4_2 = true;
		isShooting5_1 = true;
		isShooting5_2 = true;
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
	if (ATKCount >= 1200) // shoot every 1 sec
	{
		shoot1_2C();
		ATKCount = 0;
		laserNum++;
	}
	if (laserNum >= 12)
	{
		laserNum = 0;
		stateTime = 0;
		state = IDLE2;
		idleTime = rand() % 1000 + 4000;
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
	bulletSpeed = 3.0f;
	float bulletSpeed2 = 5.0f;
	float bulletSpeed3 = 7.0f;

	glm::vec3 ePos = this->getPosition();
	glm::vec3 pPos = Game::getInstance()->getPlayerRef()->getPosition();

	glm::vec3 bulDir;
	glm::vec3 bulDir2;
	glm::vec3 bulDir3;

	glm::vec3 bul1PosTemp;
	glm::vec3 bul1_1PosTemp;
	glm::vec3 bul1_2PosTemp;
	glm::vec3 bul2PosTemp;
	glm::vec3 bul2_1PosTemp;
	glm::vec3 bul2_2PosTemp;
	glm::vec3 bul3PosTemp;
	glm::vec3 bul3_1PosTemp;
	glm::vec3 bul3_2PosTemp;
	glm::vec3 bul4PosTemp;
	glm::vec3 bul4_1PosTemp;
	glm::vec3 bul4_2PosTemp;
	glm::vec3 bul5PosTemp;
	glm::vec3 bul5_1PosTemp;
	glm::vec3 bul5_2PosTemp;

	if (isShooting == false)
	{
		shootSound.play();

		// Bullet 1

		enemyBullet1 = new EnemyBullet(Tag::eBullet, "smallyellow.png");
		enemyBullet1->setSize(60, 60);
		enemyBullet1->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(-1, 0, 0));

		dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

		// Bullet2

		enemyBullet2 = new EnemyBullet(Tag::eBullet, "smallyellow.png");

		enemyBullet2->setSize(60, 60);
		enemyBullet2->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(1, 0, 0));

		dynamic_cast<GameObject*>(enemyBullet2)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet2);

		// Bullet 3

		enemyBullet3 = new EnemyBullet(Tag::eBullet, "smallyellow.png");

		enemyBullet3->setSize(60, 60);
		enemyBullet3->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(-1, -1, 0));

		dynamic_cast<GameObject*>(enemyBullet3)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet3);

		// Bullet 4

		enemyBullet4 = new EnemyBullet(Tag::eBullet, "smallyellow.png");

		enemyBullet4->setSize(60, 60);
		enemyBullet4->setPosition(this->getPosition());

		bulDir = glm::normalize(glm::vec3(1, -1, 0));

		dynamic_cast<GameObject*>(enemyBullet4)->setVelocity(bulDir * bulletSpeed);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet4);

		// Bullet 5

		enemyBullet5 = new EnemyBullet(Tag::eBullet, "smallyellow.png");

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

		enemyBullet1_1 = new EnemyBullet(Tag::eBullet, "midorange.png");
		enemyBullet1_2 = new EnemyBullet(Tag::eBullet, "midorange.png");

		enemyBullet1_1->setSize(40, 40);
		enemyBullet1_2->setSize(40, 40);

		enemyBullet1_1->setPosition(bul1PosTemp);
		enemyBullet1_2->setPosition(bul1PosTemp);

		bulDir2 = glm::normalize(glm::vec3(1, -0.2f, 0));
		bulDir3 = glm::normalize(glm::vec3(1, -0.5f, 0));

		dynamic_cast<GameObject*>(enemyBullet1_1)->setVelocity(bulDir2 * bulletSpeed2);
		dynamic_cast<GameObject*>(enemyBullet1_2)->setVelocity(bulDir3 * bulletSpeed2);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet1_1);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet1_2);

		isShooting2 = true;
		isShooting1_1 = false;
		isShooting1_2 = false;
	}
	// Bullet2 OOB
	if (dynamic_cast<EnemyBullet*>(enemyBullet2)->oob == true && isShooting3 == false)
	{
		bul2PosTemp = enemyBullet2->getPosition();
		bul2PosTemp.x = 38 + 20;

		enemyBullet2_1 = new EnemyBullet(Tag::eBullet, "midorange.png");
		enemyBullet2_2 = new EnemyBullet(Tag::eBullet, "midorange.png");

		enemyBullet2_1->setSize(40, 40);
		enemyBullet2_2->setSize(40, 40);

		enemyBullet2_1->setPosition(bul2PosTemp);
		enemyBullet2_2->setPosition(bul2PosTemp);

		bulDir2 = glm::normalize(glm::vec3(-1, -0.2f, 0));
		bulDir3 = glm::normalize(glm::vec3(-1, -0.5f, 0));

		dynamic_cast<GameObject*>(enemyBullet2_1)->setVelocity(bulDir2 * bulletSpeed2);
		dynamic_cast<GameObject*>(enemyBullet2_2)->setVelocity(bulDir3 * bulletSpeed2);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet2_1);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet2_2);

		isShooting3 = true;
		isShooting2_1 = false;
		isShooting2_2 = false;
	}
	//Bullet3 OOB
	if (dynamic_cast<EnemyBullet*>(enemyBullet3)->oob == true && isShooting4 == false)
	{
		bul3PosTemp = enemyBullet3->getPosition();
		bul3PosTemp.x = -462 - 20;

		enemyBullet3_1 = new EnemyBullet(Tag::eBullet, "midorange.png");
		enemyBullet3_2 = new EnemyBullet(Tag::eBullet, "midorange.png");
	
		enemyBullet3_1->setSize(40, 40);
		enemyBullet3_2->setSize(40, 40);
	
		enemyBullet3_1->setPosition(bul3PosTemp);
		enemyBullet3_2->setPosition(bul3PosTemp);
	
		bulDir2 = glm::normalize(glm::vec3(1, -0.3f, 0));
		bulDir3 = glm::normalize(glm::vec3(1, -0.7f, 0));
	
		dynamic_cast<GameObject*>(enemyBullet3_1)->setVelocity(bulDir2 * bulletSpeed2);
		dynamic_cast<GameObject*>(enemyBullet3_2)->setVelocity(bulDir3 * bulletSpeed2);
	
		Game::getInstance()->getObjectRef()->push_back(enemyBullet3_1);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet3_2);
	
		isShooting4 = true;
		isShooting3_1 = false;
		isShooting3_2 = false;
	}
	//Bullet4 OOB
	if (dynamic_cast<EnemyBullet*>(enemyBullet4)->oob == true && isShooting5 == false)
	{
		bul4PosTemp = enemyBullet4->getPosition();
		bul4PosTemp.x = 38 + 20;

		enemyBullet4_1 = new EnemyBullet(Tag::eBullet, "midorange.png");
		enemyBullet4_2 = new EnemyBullet(Tag::eBullet, "midorange.png");
	
		enemyBullet4_1->setSize(40, 40);
		enemyBullet4_2->setSize(40, 40);
	
		enemyBullet4_1->setPosition(bul4PosTemp);
		enemyBullet4_2->setPosition(bul4PosTemp);
	
		bulDir2 = glm::normalize(glm::vec3(-1, -0.3f, 0));
		bulDir3 = glm::normalize(glm::vec3(-1, -0.7f, 0));
	
		dynamic_cast<GameObject*>(enemyBullet4_1)->setVelocity(bulDir2 * bulletSpeed2);
		dynamic_cast<GameObject*>(enemyBullet4_2)->setVelocity(bulDir3 * bulletSpeed2);
	
		Game::getInstance()->getObjectRef()->push_back(enemyBullet4_1);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet4_2);
	
		isShooting5 = true;
		isShooting4_1 = false;
		isShooting4_2 = false;
	}
	// Bullet5 OOB
	if (dynamic_cast<EnemyBullet*>(enemyBullet5)->oob == true && isShooting6 == false)
	{
		bul5PosTemp = enemyBullet5->getPosition();
		bul5PosTemp.y = -330 + 20;

		enemyBullet5_1 = new EnemyBullet(Tag::eBullet, "midorange.png");
		enemyBullet5_2 = new EnemyBullet(Tag::eBullet, "midorange.png");
	
		enemyBullet5_1->setSize(40, 40);
		enemyBullet5_2->setSize(40, 40);
	
		enemyBullet5_1->setPosition(bul5PosTemp);
		enemyBullet5_2->setPosition(bul5PosTemp);
	
		bulDir2 = glm::normalize(glm::vec3(-1, 1, 0));
		bulDir3 = glm::normalize(glm::vec3(1, 1, 0));
	
		dynamic_cast<GameObject*>(enemyBullet5_1)->setVelocity(bulDir2 * bulletSpeed2);
		dynamic_cast<GameObject*>(enemyBullet5_2)->setVelocity(bulDir3 * bulletSpeed2);
	
		Game::getInstance()->getObjectRef()->push_back(enemyBullet5_1);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet5_2);
	
		isShooting6 = true;
		isShooting5_1 = false;
		isShooting5_2 = false;
	}
	// Bullet1_1 OOB
	if (isShooting1_1 == false && dynamic_cast<EnemyBullet*>(enemyBullet1_1)->oob == true)
	{
		bul1_1PosTemp = enemyBullet1_1->getPosition();
		bul1_1PosTemp.x = 38 - 10;
		DrawableObject* enemyBullet1_3 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet1_4 = new EnemyBullet(Tag::eBullet, "bigred.png");

		enemyBullet1_3->setSize(20, 20);
		enemyBullet1_4->setSize(20, 20);

		enemyBullet1_3->setPosition(bul1_1PosTemp);
		enemyBullet1_4->setPosition(bul1_1PosTemp);

		bulDir2 = glm::normalize(glm::vec3(-1, -0.2f, 0));
		bulDir3 = glm::normalize(glm::vec3(-1, -0.5f, 0));

		dynamic_cast<GameObject*>(enemyBullet1_3)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet1_4)->setVelocity(bulDir3 * bulletSpeed3);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet1_3);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet1_4);

		isShooting1_1 = true;
	}
	// Bullet1_2 OOB
	if (isShooting1_2 == false && dynamic_cast<EnemyBullet*>(enemyBullet1_2)->oob == true)
	{
		bul1_2PosTemp = enemyBullet1_2->getPosition();
		bul1_2PosTemp.x = 38 - 10;
		DrawableObject* enemyBullet1_5 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet1_6 = new EnemyBullet(Tag::eBullet, "bigred.png");
	
		enemyBullet1_5->setSize(20, 20);
		enemyBullet1_6->setSize(20, 20);
	
		enemyBullet1_5->setPosition(bul1_2PosTemp);
		enemyBullet1_6->setPosition(bul1_2PosTemp);
	
		bulDir2 = glm::normalize(glm::vec3(-1, -0.4f, 0));
		bulDir3 = glm::normalize(glm::vec3(-1, -0.7f, 0));
	
		dynamic_cast<GameObject*>(enemyBullet1_5)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet1_6)->setVelocity(bulDir3 * bulletSpeed3);
	
		Game::getInstance()->getObjectRef()->push_back(enemyBullet1_5);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet1_6);

		isShooting1_2 = true;
	}
	// Bullet2_1 OOB
	if (isShooting2_1 == false && dynamic_cast<EnemyBullet*>(enemyBullet2_1)->oob == true)
	{
		bul2_1PosTemp = enemyBullet2_1->getPosition();
		bul2_1PosTemp.x = -462 + 10;
		DrawableObject* enemyBullet2_3 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet2_4 = new EnemyBullet(Tag::eBullet, "bigred.png");
	
		enemyBullet2_3->setSize(20, 20);
		enemyBullet2_4->setSize(20, 20);
	
		enemyBullet2_3->setPosition(bul2_1PosTemp);
		enemyBullet2_4->setPosition(bul2_1PosTemp);
	
		bulDir2 = glm::normalize(glm::vec3(1, -0.2f, 0));
		bulDir3 = glm::normalize(glm::vec3(1, -0.5f, 0));
	
		dynamic_cast<GameObject*>(enemyBullet2_3)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet2_4)->setVelocity(bulDir3 * bulletSpeed3);
	
		Game::getInstance()->getObjectRef()->push_back(enemyBullet2_3);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet2_4);

		isShooting2_1 = true;
	}
	// Bullet2_2 OOB
	if (isShooting2_2 == false && dynamic_cast<EnemyBullet*>(enemyBullet2_2)->oob == true)
	{
		bul2_2PosTemp = enemyBullet2_2->getPosition();
		bul2_2PosTemp.x = -462 + 10;
		DrawableObject* enemyBullet2_5 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet2_6 = new EnemyBullet(Tag::eBullet, "bigred.png");
	
		enemyBullet2_5->setSize(20, 20);
		enemyBullet2_6->setSize(20, 20);
	
		enemyBullet2_5->setPosition(bul2_2PosTemp);
		enemyBullet2_6->setPosition(bul2_2PosTemp);
	
		bulDir2 = glm::normalize(glm::vec3(1, -0.4f, 0));
		bulDir3 = glm::normalize(glm::vec3(1, -0.7f, 0));
	
		dynamic_cast<GameObject*>(enemyBullet2_5)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet2_6)->setVelocity(bulDir3 * bulletSpeed3);
	
		Game::getInstance()->getObjectRef()->push_back(enemyBullet2_5);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet2_6);

		isShooting2_2 = true;
	}
	// Bullet3_1 OOB
	if (isShooting3_1 == false && dynamic_cast<EnemyBullet*>(enemyBullet3_1)->oob == true)
	{
		bul3_1PosTemp = enemyBullet3_1->getPosition();
		bul3_1PosTemp.x = 38 - 10;
		DrawableObject* enemyBullet3_3 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet3_4 = new EnemyBullet(Tag::eBullet, "bigred.png");

		enemyBullet3_3->setSize(20, 20);
		enemyBullet3_4->setSize(20, 20);

		enemyBullet3_3->setPosition(bul3_1PosTemp);
		enemyBullet3_4->setPosition(bul3_1PosTemp);

		bulDir2 = glm::normalize(glm::vec3(-1, -0.2f, 0));
		bulDir3 = glm::normalize(glm::vec3(-1, -0.5f, 0));

		dynamic_cast<GameObject*>(enemyBullet3_3)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet3_4)->setVelocity(bulDir3 * bulletSpeed3);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet3_3);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet3_4);

		isShooting3_1 = true;
	}
	// Bullet3_2 OOB
	if (isShooting3_2 == false && dynamic_cast<EnemyBullet*>(enemyBullet3_2)->oob == true)
	{
		bul3_2PosTemp = enemyBullet3_2->getPosition();
		bul3_2PosTemp.y = -330 + 10;
		DrawableObject* enemyBullet3_5 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet3_6 = new EnemyBullet(Tag::eBullet, "bigred.png");
	
		enemyBullet3_5->setSize(20, 20);
		enemyBullet3_6->setSize(20, 20);
	
		enemyBullet3_5->setPosition(bul3_2PosTemp);
		enemyBullet3_6->setPosition(bul3_2PosTemp);
	
		bulDir2 = glm::normalize(glm::vec3(-0.1f, 1, 0));
		bulDir3 = glm::normalize(glm::vec3(-1, 1, 0));
	
		dynamic_cast<GameObject*>(enemyBullet3_5)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet3_6)->setVelocity(bulDir3 * bulletSpeed3);
	
		Game::getInstance()->getObjectRef()->push_back(enemyBullet3_5);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet3_6);
	
		isShooting3_2 = true;
	}
	// Bullet4_1 OOB
	if (isShooting4_1 == false && dynamic_cast<EnemyBullet*>(enemyBullet4_1)->oob == true)
	{
		bul4_1PosTemp = enemyBullet4_1->getPosition();
		bul4_1PosTemp.x = -462 + 10;
		DrawableObject* enemyBullet4_3 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet4_4 = new EnemyBullet(Tag::eBullet, "bigred.png");

		enemyBullet4_3->setSize(20, 20);
		enemyBullet4_4->setSize(20, 20);

		enemyBullet4_3->setPosition(bul4_1PosTemp);
		enemyBullet4_4->setPosition(bul4_1PosTemp);

		bulDir2 = glm::normalize(glm::vec3(1, -0.2f, 0));
		bulDir3 = glm::normalize(glm::vec3(1, -0.5f, 0));

		dynamic_cast<GameObject*>(enemyBullet4_3)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet4_4)->setVelocity(bulDir3 * bulletSpeed3);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet4_3);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet4_4);

		isShooting4_1 = true;
	}
	// Bullet4_2 OOB
	if (isShooting4_2 == false && dynamic_cast<EnemyBullet*>(enemyBullet4_2)->oob == true)
	{
		bul4_2PosTemp = enemyBullet4_2->getPosition();
		bul4_2PosTemp.y = -330 + 10;
		DrawableObject* enemyBullet4_5 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet4_6 = new EnemyBullet(Tag::eBullet, "bigred.png");

		enemyBullet4_5->setSize(20, 20);
		enemyBullet4_6->setSize(20, 20);

		enemyBullet4_5->setPosition(bul4_2PosTemp);
		enemyBullet4_6->setPosition(bul4_2PosTemp);

		bulDir2 = glm::normalize(glm::vec3(0.1f, 1, 0));
		bulDir3 = glm::normalize(glm::vec3(1, 1, 0));

		dynamic_cast<GameObject*>(enemyBullet4_5)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet4_6)->setVelocity(bulDir3 * bulletSpeed3);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet4_5);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet4_6);

		isShooting4_2 = true;
	}
	// Bullet5_1 OOB
	if (isShooting5_1 == false && dynamic_cast<EnemyBullet*>(enemyBullet5_1)->oob == true)
	{
		bul5_1PosTemp = enemyBullet5_1->getPosition();
		bul5_1PosTemp.x = -462 + 10;
		DrawableObject* enemyBullet5_3 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet5_4 = new EnemyBullet(Tag::eBullet, "bigred.png");

		enemyBullet5_3->setSize(20, 20);
		enemyBullet5_4->setSize(20, 20);

		enemyBullet5_3->setPosition(bul5_1PosTemp);
		enemyBullet5_4->setPosition(bul5_1PosTemp);

		bulDir2 = glm::normalize(glm::vec3(1, 1, 0));
		bulDir3 = glm::normalize(glm::vec3(1, -1, 0));

		dynamic_cast<GameObject*>(enemyBullet5_3)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet5_4)->setVelocity(bulDir3 * bulletSpeed3);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet5_3);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet5_4);

		isShooting5_1 = true;
	}
	// Bullet5_2 OOB
	if (isShooting5_2 == false && dynamic_cast<EnemyBullet*>(enemyBullet5_2)->oob == true)
	{
		bul5_2PosTemp = enemyBullet5_2->getPosition();
		bul5_2PosTemp.x = 38 - 10;
		DrawableObject* enemyBullet5_5 = new EnemyBullet(Tag::eBullet, "bigred.png");
		DrawableObject* enemyBullet5_6 = new EnemyBullet(Tag::eBullet, "bigred.png");

		enemyBullet5_5->setSize(20, 20);
		enemyBullet5_6->setSize(20, 20);

		enemyBullet5_5->setPosition(bul5_2PosTemp);
		enemyBullet5_6->setPosition(bul5_2PosTemp);

		bulDir2 = glm::normalize(glm::vec3(-1, 1, 0));
		bulDir3 = glm::normalize(glm::vec3(-1, -1, 0));

		dynamic_cast<GameObject*>(enemyBullet5_5)->setVelocity(bulDir2 * bulletSpeed3);
		dynamic_cast<GameObject*>(enemyBullet5_6)->setVelocity(bulDir3 * bulletSpeed3);

		Game::getInstance()->getObjectRef()->push_back(enemyBullet5_5);
		Game::getInstance()->getObjectRef()->push_back(enemyBullet5_6);

		isShooting5_2 = true;
	}
}

void Boss2::shoot1_2B()
{
	glm::vec3 bulDir;

	// Bullet 1

	enemyBullet1 = new EnemyBullet(Tag::eBullet, "bigred.png");
	enemyBullet1->setSize(60, 60);
	enemyBullet1->setPosition(this->getPosition());

	bulDir = normalize(glm::vec3(0, -1, 0));

	dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

	// Bullet2

	enemyBullet2 = new EnemyBullet(Tag::eBullet, "bigred.png");

	enemyBullet2->setSize(60, 60);
	enemyBullet2->setPosition(this->getPosition());

	bulDir = glm::normalize(glm::vec3(1, 0, 0));

	dynamic_cast<GameObject*>(enemyBullet2)->setVelocity(bulDir * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet2);
}

void Boss2::shoot1_2C()
{
		Laser* ls = new Laser(Tag::eBullet, "bigred.png");
		Game::getInstance()->getObjectRef()->push_back(ls);
}

void Boss2::move()
{

}


void Boss2::render(glm::mat4 globalModelTransform)
{
	SpriteObject::render(globalModelTransform);
	if (state != MOVEIN2)
	{
		HPbg->render(globalModelTransform);
		HPbar->render(globalModelTransform);
		HPframe->render(globalModelTransform);
	}
}

Boss2::~Boss2()
{
	if (enemyBullet1 != NULL)
	{
		delete enemyBullet1;
	}
}
