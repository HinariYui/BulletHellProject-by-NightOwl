#include "Spawner.h"
#include "Game.h"

#define MID_PLAYAREA_X -212
#define LEFT_PLAYAREA_X -462
#define RIGHT_PLAYAREA_X 38

Spawner::Spawner()
{
}

void Spawner::update(float deltaTime)
{
	spawnCD += deltaTime;
}

void Spawner::EnemySpawn(float rate)
{
	if (spawnCD >= rate)
	{
		if (eNum != 10)
		{
			int x = rand() % 500 + LEFT_PLAYAREA_X;
			Enemy1 * enemy = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy->setRotation(180);
			enemy->setSize(35, 35);
			enemy->setPosition(glm::vec3(x, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy);
		}
		spawnCD = 0;
		eNum++;
	}
}

void Spawner::EnemySpawn(int i)
{
	pattern = i;
	switch (pattern)
	{
		case(1):
		{
			Enemy2* enemy1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(-530, 390, 0));
			enemy1->setVelocity(normalize(glm::vec3(7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			Enemy2* enemy2 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy2->setRotation(180);
			enemy2->setSize(35, 35);
			enemy2->setPosition(glm::vec3(-530 - 35, 390 + 25, 0));
			enemy2->setVelocity(normalize(glm::vec3(7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy2);

			Enemy2* enemy3 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy3->setRotation(180);
			enemy3->setSize(35, 35);
			enemy3->setPosition(glm::vec3(-530 - 35*2, 390 + 25*2, 0));
			enemy3->setVelocity(normalize(glm::vec3(7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy3);

			Enemy2* enemy4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy4->setRotation(180);
			enemy4->setSize(35, 35);
			enemy4->setPosition(glm::vec3(-530 - 35*3, 390 + 25*3, 0));
			enemy4->setVelocity(normalize(glm::vec3(7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy4);

			Enemy2* enemy5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy5->setRotation(180);
			enemy5->setSize(35, 35);
			enemy5->setPosition(glm::vec3(106, 390, 0));
			enemy5->setVelocity(normalize(glm::vec3(-7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy5);

			Enemy2* enemy6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy6->setRotation(180);
			enemy6->setSize(35, 35);
			enemy6->setPosition(glm::vec3(106 + 35, 390 + 25, 0));
			enemy6->setVelocity(normalize(glm::vec3(-7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy6);

			Enemy2* enemy7 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy7->setRotation(180);
			enemy7->setSize(35, 35);
			enemy7->setPosition(glm::vec3(106 + 35*2, 390 + 25*2, 0));
			enemy7->setVelocity(normalize(glm::vec3(-7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy7);

			Enemy2* enemy8 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy8->setRotation(180);
			enemy8->setSize(35, 35);
			enemy8->setPosition(glm::vec3(106 + 35*3, 390 + 25*3, 0));
			enemy8->setVelocity(normalize(glm::vec3(-7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy8);

			break;
		}
		case(2):
		{
			Enemy1 * enemy1 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			Enemy1 * enemy2 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy2->setRotation(180);
			enemy2->setSize(35, 35);
			enemy2->setPosition(glm::vec3(MID_PLAYAREA_X, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy2);

			Enemy1 * enemy3 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy3->setRotation(180);
			enemy3->setSize(35, 35);
			enemy3->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy3);

			break;
		}
		case(3):
		{
			Enemy2* enemy1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340, 0));
			enemy1->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			Enemy2* enemy2 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy2->setRotation(180);
			enemy2->setSize(35, 35);
			enemy2->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43, 0));
			enemy2->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy2);

			Enemy2* enemy3 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy3->setRotation(180);
			enemy3->setSize(35, 35);
			enemy3->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43*2, 0));
			enemy3->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy3);

			Enemy2* enemy4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy4->setRotation(180);
			enemy4->setSize(35, 35);
			enemy4->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43*3, 0));
			enemy4->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy4);

			Enemy2* enemy5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy5->setRotation(180);
			enemy5->setSize(35, 35);
			enemy5->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340, 0));
			enemy5->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy5);

			Enemy2* enemy6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy6->setRotation(180);
			enemy6->setSize(35, 35);
			enemy6->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43, 0));
			enemy6->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy6);

			Enemy2* enemy7 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy7->setRotation(180);
			enemy7->setSize(35, 35);
			enemy7->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43*2, 0));
			enemy7->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy7);

			Enemy2* enemy8 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy8->setRotation(180);
			enemy8->setSize(35, 35);
			enemy8->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43*3, 0));
			enemy8->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy8);

			break;
		}
		case(4):
		{
			Enemy1 * enemy1 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			Enemy1 * enemy2 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy2->setRotation(180);
			enemy2->setSize(35, 35);
			enemy2->setPosition(glm::vec3(MID_PLAYAREA_X, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy2);

			Enemy1 * enemy3 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy3->setRotation(180);
			enemy3->setSize(35, 35);
			enemy3->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy3);

			break; 
		}
		case(5):
		{
			Enemy2* enemy1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(MID_PLAYAREA_X - 50, 340, 0));
			enemy1->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			//Enemy2* enemy2 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			//enemy2->setRotation(180);
			//enemy2->setSize(35, 35);
			//enemy2->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43, 0));
			//enemy2->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			//Game::getInstance()->getObjectRef()->push_back(enemy2);
			//
			//Enemy2* enemy3 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			//enemy3->setRotation(180);
			//enemy3->setSize(35, 35);
			//enemy3->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43 * 2, 0));
			//enemy3->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			//Game::getInstance()->getObjectRef()->push_back(enemy3);
			//
			//Enemy2* enemy4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			//enemy4->setRotation(180);
			//enemy4->setSize(35, 35);
			//enemy4->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43 * 3, 0));
			//enemy4->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			//Game::getInstance()->getObjectRef()->push_back(enemy4);
			//
			//Enemy2* enemy5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			//enemy5->setRotation(180);
			//enemy5->setSize(35, 35);
			//enemy5->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340, 0));
			//enemy5->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			//Game::getInstance()->getObjectRef()->push_back(enemy5);
			//
			//Enemy2* enemy6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			//enemy6->setRotation(180);
			//enemy6->setSize(35, 35);
			//enemy6->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43, 0));
			//enemy6->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			//Game::getInstance()->getObjectRef()->push_back(enemy6);

			break;
		}
		case(6):
		{
			Enemy2* enemy1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340, 0));
			enemy1->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			Enemy2* enemy2 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy2->setRotation(180);
			enemy2->setSize(35, 35);
			enemy2->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43, 0));
			enemy2->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy2);

			Enemy2* enemy3 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy3->setRotation(180);
			enemy3->setSize(35, 35);
			enemy3->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43 * 2, 0));
			enemy3->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy3);

			Enemy2* enemy4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy4->setRotation(180);
			enemy4->setSize(35, 35);
			enemy4->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43 * 3, 0));
			enemy4->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy4);

			Enemy2* enemy5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy5->setRotation(180);
			enemy5->setSize(35, 35);
			enemy5->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340, 0));
			enemy5->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy5);

			Enemy2* enemy6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy6->setRotation(180);
			enemy6->setSize(35, 35);
			enemy6->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43, 0));
			enemy6->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy6);

			Enemy2* enemy7 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy7->setRotation(180);
			enemy7->setSize(35, 35);
			enemy7->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43 * 2, 0));
			enemy7->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy7);

			Enemy2* enemy8 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy8->setRotation(180);
			enemy8->setSize(35, 35);
			enemy8->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43 * 3, 0));
			enemy8->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(enemy8);

			break;
		}
		case(7):
		{
			break;
		}
		case(8):
		{
			Enemy1 * enemy1 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy1->setRotation(180);
			enemy1->setSize(35, 35);
			enemy1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 20, 420, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy1);

			Enemy1 * enemy2 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy2->setRotation(180);
			enemy2->setSize(35, 35);
			enemy2->setPosition(glm::vec3(MID_PLAYAREA_X, 420, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy2);

			Enemy1 * enemy3 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			enemy3->setRotation(180);
			enemy3->setSize(35, 35);
			enemy3->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 20, 420, 0));
			Game::getInstance()->getObjectRef()->push_back(enemy3);

			Enemy2* enemy4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy4->setRotation(180);
			enemy4->setSize(35, 35);
			enemy4->setPosition(glm::vec3(LEFT_PLAYAREA_X + 120, 420 - 60, 0));
			enemy4->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(enemy4);

			Enemy2* enemy5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy5->setRotation(180);
			enemy5->setSize(35, 35);
			enemy5->setPosition(glm::vec3(LEFT_PLAYAREA_X + 120, 420, 0));
			enemy5->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(enemy5);

			Enemy2* enemy6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy6->setRotation(180);
			enemy6->setSize(35, 35);
			enemy6->setPosition(glm::vec3(LEFT_PLAYAREA_X + 120, 420 + 60, 0));
			enemy6->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(enemy6);

			Enemy2* enemy7 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy7->setRotation(180);
			enemy7->setSize(35, 35);
			enemy7->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 120, 420 - 60, 0));
			enemy7->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(enemy7);

			Enemy2* enemy8 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy8->setRotation(180);
			enemy8->setSize(35, 35);
			enemy8->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 120, 420, 0));
			enemy8->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(enemy8);

			Enemy2* enemy9 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			enemy9->setRotation(180);
			enemy9->setSize(35, 35);
			enemy9->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 120, 420 + 60, 0));
			enemy9->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(enemy9);

			break;
		}
	}
}

void Spawner::SetSpawnRate(float rate)
{
	spawnRate = rate;
}