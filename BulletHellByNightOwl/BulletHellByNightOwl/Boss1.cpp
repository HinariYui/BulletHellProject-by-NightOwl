#include <iostream>
#include "Boss1.h"
#include "EnemyBullet.h"
#include "SpecialEnemyBullet.h"
#include "Landmine.h"
#include "Game.h"

Boss1::Boss1(Tag enemy, string fileName, int row, int col) : SpriteObject(fileName, row, col)
{
	setVelocity(glm::vec3(0, -1, 0));
	tag = enemy;
	state = MOVEIN;
	idleTime = rand() % 1000 + 2000;
	stateTime = 0;
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, 0.25f, glm::vec3(0.0f, 0.0f, 1.0f)); //0.25f -> radiant
	hp = maxHP;
	HPbg = new SpriteObject("HP-bg.png", 1, 1);
	HPbar = new SpriteObject("HP-green.png", 1, 1);
	HPframe = new SpriteObject("HP-tube.png", 1, 1);
	HPbg->setSize(HPsize, 20);
	HPbar->setSize(HPsize, 20);
	HPframe->setSize(HPsize + 1, 20);
	HPbar->setPosition(glm::vec3(HPpos, 340, 0));
	HPbg->setPosition(glm::vec3(HPpos, 340, 0));
	HPframe->setPosition(glm::vec3(HPpos, 340, 0));

	Drone1 = new SpriteObject("WeaponDrone_48x48.png", 1, 1);
	Drone2 = new SpriteObject("WeaponDrone_48x48.png", 1, 1);
	Drone3 = new SpriteObject("WeaponDrone_48x48.png", 1, 1);
	Drone4 = new SpriteObject("WeaponDrone_48x48.png", 1, 1);

	Drone1->setSize(48, 48);
	Drone2->setSize(48, 48);
	Drone3->setSize(48, 48);
	Drone4->setSize(48, 48);
}

void Boss1::update(float deltaTime)
{
	if (hp < 1)
	{
		Game::getInstance()->eSpawn = true;
		Game::getInstance()->bossSpawn = false;
		Game::getInstance()->spawnBoss1 = false;
		Game::getInstance()->boss1Died = true;
		Game::getInstance()->eSpawnCD = 0;
		Game::getInstance()->spawnPattern = 1;
		Game::getInstance()->spawnNum = 0;
	}

	drone1DefaultPos = getPosition() + glm::vec3(-100, 70, 0);
	drone2DefaultPos = getPosition() + glm::vec3(100, 70, 0);
	drone3DefaultPos = getPosition() + glm::vec3(-100, -70, 0);
	drone4DefaultPos = getPosition() + glm::vec3(100, -70, 0);

	HPpercentage = (float)hp / (float)maxHP;
	if (HPpercentage <= 0.67 && HPpercentage > 0.33) HPbar->addSprite("HP-yellow.png", 1, 1);
	else if (HPpercentage <= 0.33) HPbar->addSprite("HP-red.png", 1, 1);
	HPbar->setSize(HPsize * HPpercentage, 20);
	missingHP = (float)maxHP - (float)hp;
	HPbar->setPosition(glm::vec3(HPpos - missingHP / (maxHP / (HPsize / 2)), 340, 0));
	GameObject::update(deltaTime);

	if (state == IDLE)
	{
		updateIDLE(deltaTime);
	}
	else if (state == MOVEIN)
	{
		updateMoveIn(deltaTime);
		hp = maxHP;
	}
	else if (state == ATK1)
	{
		updateATK1(deltaTime);
	}
	else if (state == ATK2)
	{
		updateATK2(deltaTime);
	}
	else if (state == ATK3)
	{
		updateATK3(deltaTime);
	}
}

void Boss1::updateIDLE(float deltaTime)
{
	stateTime += deltaTime;
	if (Drone1->getPosition() != drone1DefaultPos)
	{
		DroneMoveBack(deltaTime / (idleTime - 1000));
		droneIsMovingBack = true;
	}
	if (stateTime >= idleTime - 1000)
	{
		droneIsMovingBack = false;
	}
	if (stateTime >= idleTime)
	{
		stateTime = 0;
		int pattern = rand() % 3 + 1;
		//pattern = 2;
		if (pattern == 1)
		{
			state = ATK1;
		}
		else if (pattern == 2)
		{
			state = ATK2;
		}
		else
		{
			state = ATK3;
		}
	}
}

void Boss1::updateMoveIn(float deltaTime)
{
	Drone1->setPosition(drone1DefaultPos);
	Drone2->setPosition(drone2DefaultPos);
	Drone3->setPosition(drone3DefaultPos);
	Drone4->setPosition(drone4DefaultPos);

	float y = getPosition().y;
	if (y <= 200)
	{
		state = IDLE;
		setVelocity(glm::vec3(0, 0, 0));
	}
}

void Boss1::updateATK1(float deltaTime)
{
	stateTime += deltaTime;
	ATKCount += deltaTime;
	if (ATKCount >= 30) // shoot every 0.03 sec
	{
		shoot2_1C();
		shootSound.play();
		ATKCount = 0;
	}
	if (stateTime >= 4000)
	{
		stateTime = 0;
		state = IDLE;
		idleTime = rand() % 1000 + 2000;
	}
}

void Boss1::updateATK2(float deltaTime)
{
	stateTime += deltaTime;
	ATKCount += deltaTime;
	if (ATKCount >= 100 && stateTime < 3000) // shoot every 0.1 sec
	{
		shoot1_1A();
		shootSound.play();
		ATKCount = 0;
	}
	if (stateTime < 3000)
	{
		DroneMove1(deltaTime / 3000);
		droneIsMoving1 = true;
	}
	else if (stateTime >= 4000 && stateTime < 6000)
	{
		droneIsMoving1 = false;
		DroneMove2(deltaTime / 2000);
		droneIsMoving2 = true;
	}
	else if (stateTime >= 8000 && stateTime < 14000)
	{
		shoot1_1B(deltaTime * 0.15f, deltaTime);
		droneIsMoving1 = true;
	}
	else if (stateTime >= 14000)
	{
		droneIsMoving1 = false;
		droneIsMoving2 = false;
		stateTime = 0;
		state = IDLE;
		idleTime = rand() % 1000 + 4000;
	}
}

void Boss1::updateATK3(float deltaTime)
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
		state = IDLE;
		idleTime = rand() % 1000 + 3000;
	}
}

void Boss1::shoot2_1C() // pattern 2_1C
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

void Boss1::shoot1_1A() // pattern 1_1A
{
	bulletSpeed = 7.0f;

	glm::vec3 ePos1 = Drone1->getPosition();
	glm::vec3 ePos2 = Drone2->getPosition();
	glm::vec3 ePos3 = Drone3->getPosition();
	glm::vec3 ePos4 = Drone4->getPosition();
	glm::vec3 pPos = Game::getInstance()->getPlayerRef()->getPosition();

	glm::vec3 bulDir;

	// Bullet 1

	enemyBullet1 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	enemyBullet1->setSize(10, 10);
	enemyBullet1->setPosition(Drone1->getPosition());

	bulDir = glm::normalize(pPos - ePos1);

	dynamic_cast<GameObject*>(enemyBullet1)->setVelocity(bulDir * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet1);

	// Bullet2

	enemyBullet2 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	enemyBullet2->setSize(10, 10);
	enemyBullet2->setPosition(Drone2->getPosition());

	bulDir = glm::normalize(pPos - ePos2);

	dynamic_cast<GameObject*>(enemyBullet2)->setVelocity(bulDir * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet2);

	// Bullet 3

	enemyBullet3 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	enemyBullet3->setSize(10, 10);
	enemyBullet3->setPosition(Drone3->getPosition());

	bulDir = glm::normalize(pPos - ePos3);

	dynamic_cast<GameObject*>(enemyBullet3)->setVelocity(bulDir * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet3);

	// Bullet 4

	enemyBullet4 = new EnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");

	enemyBullet4->setSize(10, 10);
	enemyBullet4->setPosition(Drone4->getPosition());

	bulDir = glm::normalize(pPos - ePos4);

	dynamic_cast<GameObject*>(enemyBullet4)->setVelocity(bulDir * bulletSpeed);

	Game::getInstance()->getObjectRef()->push_back(enemyBullet4);
}

void Boss1::shoot1_1B(float constant, float deltaTime)
{
	ATKCount += deltaTime;

	glm::vec3 pPos = Game::getInstance()->getPlayerRef()->getPosition();

	drone1MoveToPos = pPos;
	drone2MoveToPos = pPos;
	drone3MoveToPos = pPos;
	drone4MoveToPos = pPos;

	if (!droneIsMoving1)
	{
		drone1MoveDir = glm::normalize(drone1MoveToPos - Drone1->getPosition());
		drone2MoveDir = glm::normalize(drone2MoveToPos - Drone2->getPosition());
		drone3MoveDir = glm::normalize(drone3MoveToPos - Drone3->getPosition());
		drone4MoveDir = glm::normalize(drone4MoveToPos - Drone4->getPosition());
	}
	if (Drone1->getPosition().x > -442 && Drone1->getPosition().x < 18 && Drone1->getPosition().y > -310 && Drone1->getPosition().y < 310)
	{
		drone1IsMoving = true;
		dynamic_cast<GameObject*>(Drone1)->translate(drone1MoveDir * constant);
	}
	else drone1IsMoving = false;
	if (Drone2->getPosition().x > -442 && Drone2->getPosition().x < 18 && Drone2->getPosition().y > -310 && Drone2->getPosition().y < 310)
	{
		drone2IsMoving = true;
		dynamic_cast<GameObject*>(Drone2)->translate(drone2MoveDir * constant);
	}
	else drone2IsMoving = false;
	if (Drone3->getPosition().x > -442 && Drone3->getPosition().x < 18 && Drone3->getPosition().y > -310 && Drone3->getPosition().y < 310)
	{
		drone3IsMoving = true;
		dynamic_cast<GameObject*>(Drone3)->translate(drone3MoveDir * constant);
	}
	else drone3IsMoving = false;
	if (Drone4->getPosition().x > -442 && Drone4->getPosition().x < 18 && Drone4->getPosition().y > -310 && Drone4->getPosition().y < 310)
	{
		drone4IsMoving = true;
		dynamic_cast<GameObject*>(Drone4)->translate(drone4MoveDir * constant);
	}
	else drone4IsMoving = false;

	if (ATKCount >= 900) // every 0.9 sec
	{
		if (drone1IsMoving)
		{
			// Bullet 1
			DrawableObject* lm = new Landmine(Tag::eBullet, "Mine_50x50.png", drone1MoveDir);
			BulletGameObject* mine = dynamic_cast<BulletGameObject *>(lm);
			lm->setSize(50, 50);
			lm->setPosition(Drone1->getPosition());
			mine->setAnimationLoop(1, 1, 3, 1000);
			Game::getInstance()->getObjectRef()->push_back(lm);
		}
		if (drone2IsMoving)
		{
			// Bullet2
			DrawableObject* lm = new Landmine(Tag::eBullet, "Mine_50x50.png", drone2MoveDir);
			BulletGameObject* mine = dynamic_cast<BulletGameObject *>(lm);
			lm->setSize(50, 50);
			lm->setPosition(Drone2->getPosition());
			mine->setAnimationLoop(1, 1, 3, 1000);
			Game::getInstance()->getObjectRef()->push_back(lm);
		}
		if (drone3IsMoving)
		{
			// Bullet 3
			DrawableObject* lm = new Landmine(Tag::eBullet, "Mine_50x50.png", drone3MoveDir);
			BulletGameObject* mine = dynamic_cast<BulletGameObject *>(lm);
			lm->setSize(50, 50);
			lm->setPosition(Drone3->getPosition());
			mine->setAnimationLoop(1, 1, 3, 1000);
			Game::getInstance()->getObjectRef()->push_back(lm);
		}
		if (drone4IsMoving)
		{
			// Bullet 4
			DrawableObject* lm = new Landmine(Tag::eBullet, "Mine_50x50.png", drone4MoveDir);
			BulletGameObject* mine = dynamic_cast<BulletGameObject *>(lm);
			lm->setSize(50, 50);
			lm->setPosition(Drone4->getPosition());
			mine->setAnimationLoop(1, 1, 3, 1000);
			Game::getInstance()->getObjectRef()->push_back(lm);
		}

		ATKCount = 0;
	}
}

void Boss1::shoot2_1D()
{
	DrawableObject* specialBullet1 = new SpecialEnemyBullet(Tag::eBullet, "Boss1Bullet20x20.png");
	specialBullet1->setSize(30, 30);
	specialBullet1->setPosition(this->getPosition());
	Game::getInstance()->getObjectRef()->push_back(specialBullet1);
}

void Boss1::DroneMove1(float constant)
{
	drone1MoveToPos = glm::vec3(-252, 40, 0);
	drone2MoveToPos = glm::vec3(-172, 40, 0);
	drone3MoveToPos = glm::vec3(-252, -40, 0);
	drone4MoveToPos = glm::vec3(-172, -40, 0);

	if (!droneIsMoving1)
	{
		drone1MoveDir = glm::normalize(drone1MoveToPos - Drone1->getPosition());
		drone2MoveDir = glm::normalize(drone2MoveToPos - Drone2->getPosition());
		drone3MoveDir = glm::normalize(drone3MoveToPos - Drone3->getPosition());
		drone4MoveDir = glm::normalize(drone4MoveToPos - Drone4->getPosition());

		drone1MoveSpeed = sqrt(((drone1MoveToPos.x - Drone1->getPosition().x) * (drone1MoveToPos.x - Drone1->getPosition().x)) + ((drone1MoveToPos.y - Drone1->getPosition().y) * (drone1MoveToPos.y - Drone1->getPosition().y))) * constant;
		drone2MoveSpeed = sqrt(((drone2MoveToPos.x - Drone2->getPosition().x) * (drone2MoveToPos.x - Drone2->getPosition().x)) + ((drone2MoveToPos.y - Drone2->getPosition().y) * (drone2MoveToPos.y - Drone2->getPosition().y))) * constant;
		drone3MoveSpeed = sqrt(((drone3MoveToPos.x - Drone3->getPosition().x) * (drone3MoveToPos.x - Drone3->getPosition().x)) + ((drone3MoveToPos.y - Drone3->getPosition().y) * (drone3MoveToPos.y - Drone3->getPosition().y))) * constant;
		drone4MoveSpeed = sqrt(((drone4MoveToPos.x - Drone4->getPosition().x) * (drone4MoveToPos.x - Drone4->getPosition().x)) + ((drone4MoveToPos.y - Drone4->getPosition().y) * (drone4MoveToPos.y - Drone4->getPosition().y))) * constant;
	}

	dynamic_cast<GameObject*>(Drone1)->translate(drone1MoveDir * drone1MoveSpeed);
	dynamic_cast<GameObject*>(Drone2)->translate(drone2MoveDir * drone2MoveSpeed);
	dynamic_cast<GameObject*>(Drone3)->translate(drone3MoveDir * drone3MoveSpeed);
	dynamic_cast<GameObject*>(Drone4)->translate(drone4MoveDir * drone4MoveSpeed);
}

void Boss1::DroneMove2(float constant)
{
	drone1MoveToPos = glm::vec3(-422, 290, 0); // top left
	drone2MoveToPos = glm::vec3(-2, 290, 0); // top right
	drone3MoveToPos = glm::vec3(-422, -290, 0); // bottom left
	drone4MoveToPos = glm::vec3(-2, -290, 0); // bottom right

	if (!droneIsMoving2)
	{
		drone1MoveDir = glm::normalize(drone1MoveToPos - Drone1->getPosition());
		drone2MoveDir = glm::normalize(drone2MoveToPos - Drone2->getPosition());
		drone3MoveDir = glm::normalize(drone3MoveToPos - Drone3->getPosition());
		drone4MoveDir = glm::normalize(drone4MoveToPos - Drone4->getPosition());

		drone1MoveSpeed = sqrt(((drone1MoveToPos.x - Drone1->getPosition().x) * (drone1MoveToPos.x - Drone1->getPosition().x)) + ((drone1MoveToPos.y - Drone1->getPosition().y) * (drone1MoveToPos.y - Drone1->getPosition().y))) * constant;
		drone2MoveSpeed = sqrt(((drone2MoveToPos.x - Drone2->getPosition().x) * (drone2MoveToPos.x - Drone2->getPosition().x)) + ((drone2MoveToPos.y - Drone2->getPosition().y) * (drone2MoveToPos.y - Drone2->getPosition().y))) * constant;
		drone3MoveSpeed = sqrt(((drone3MoveToPos.x - Drone3->getPosition().x) * (drone3MoveToPos.x - Drone3->getPosition().x)) + ((drone3MoveToPos.y - Drone3->getPosition().y) * (drone3MoveToPos.y - Drone3->getPosition().y))) * constant;
		drone4MoveSpeed = sqrt(((drone4MoveToPos.x - Drone4->getPosition().x) * (drone4MoveToPos.x - Drone4->getPosition().x)) + ((drone4MoveToPos.y - Drone4->getPosition().y) * (drone4MoveToPos.y - Drone4->getPosition().y))) * constant;
	}

	dynamic_cast<GameObject*>(Drone1)->translate(drone1MoveDir * drone1MoveSpeed);
	dynamic_cast<GameObject*>(Drone2)->translate(drone2MoveDir * drone2MoveSpeed);
	dynamic_cast<GameObject*>(Drone3)->translate(drone3MoveDir * drone3MoveSpeed);
	dynamic_cast<GameObject*>(Drone4)->translate(drone4MoveDir * drone4MoveSpeed);
}

void Boss1::DroneMoveBack(float constant)
{
	if (!droneIsMovingBack)
	{
		drone1MoveDir = glm::normalize(drone1DefaultPos - Drone1->getPosition());
		drone2MoveDir = glm::normalize(drone2DefaultPos - Drone2->getPosition());
		drone3MoveDir = glm::normalize(drone3DefaultPos - Drone3->getPosition());
		drone4MoveDir = glm::normalize(drone4DefaultPos - Drone4->getPosition());

		drone1MoveSpeed = sqrt(((drone1DefaultPos.x - Drone1->getPosition().x) * (drone1DefaultPos.x - Drone1->getPosition().x)) + ((drone1DefaultPos.y - Drone1->getPosition().y) * (drone1DefaultPos.y - Drone1->getPosition().y))) * constant;
		drone2MoveSpeed = sqrt(((drone2DefaultPos.x - Drone2->getPosition().x) * (drone2DefaultPos.x - Drone2->getPosition().x)) + ((drone2DefaultPos.y - Drone2->getPosition().y) * (drone2DefaultPos.y - Drone2->getPosition().y))) * constant;
		drone3MoveSpeed = sqrt(((drone3DefaultPos.x - Drone3->getPosition().x) * (drone3DefaultPos.x - Drone3->getPosition().x)) + ((drone3DefaultPos.y - Drone3->getPosition().y) * (drone3DefaultPos.y - Drone3->getPosition().y))) * constant;
		drone4MoveSpeed = sqrt(((drone4DefaultPos.x - Drone4->getPosition().x) * (drone4DefaultPos.x - Drone4->getPosition().x)) + ((drone4DefaultPos.y - Drone4->getPosition().y) * (drone4DefaultPos.y - Drone4->getPosition().y))) * constant;
	}

	dynamic_cast<GameObject*>(Drone1)->translate(drone1MoveDir * drone1MoveSpeed);
	dynamic_cast<GameObject*>(Drone2)->translate(drone2MoveDir * drone2MoveSpeed);
	dynamic_cast<GameObject*>(Drone3)->translate(drone3MoveDir * drone3MoveSpeed);
	dynamic_cast<GameObject*>(Drone4)->translate(drone4MoveDir * drone4MoveSpeed);
}

void Boss1::move()
{

}


void Boss1::render(glm::mat4 globalModelTransform)
{
	SpriteObject::render(globalModelTransform);
	if (state != MOVEIN)
	{
		HPbg->render(globalModelTransform);
		HPbar->render(globalModelTransform);
		HPframe->render(globalModelTransform);
	}
	Drone1->render(globalModelTransform);
	Drone2->render(globalModelTransform);
	Drone3->render(globalModelTransform);
	Drone4->render(globalModelTransform);
}

Boss1::~Boss1()
{
	if (enemyBullet1 != NULL)
	{
		delete enemyBullet1;
	}
}
