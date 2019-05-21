#include "Spawner.h"
#include "Game.h"

#define MID_PLAYAREA_X -212
#define LEFT_PLAYAREA_X -462
#define RIGHT_PLAYAREA_X 38
#define LEFT_EDGE -849
#define RIGHT_EDGE 425

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
			e2_1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_1->setRotation(180);
			e2_1->setSize(35, 35);
			e2_1->setPosition(glm::vec3(-530, 390, 0));
			e2_1->setVelocity(normalize(glm::vec3(7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_1);

			e2_2 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_2->setRotation(180);
			e2_2->setSize(35, 35);
			e2_2->setPosition(glm::vec3(-530 - 35, 390 + 25, 0));
			e2_2->setVelocity(normalize(glm::vec3(7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_2);

			e2_3 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_3->setRotation(180);
			e2_3->setSize(35, 35);
			e2_3->setPosition(glm::vec3(-530 - 35*2, 390 + 25*2, 0));
			e2_3->setVelocity(normalize(glm::vec3(7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_3);

			e2_4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_4->setRotation(180);
			e2_4->setSize(35, 35);
			e2_4->setPosition(glm::vec3(-530 - 35*3, 390 + 25*3, 0));
			e2_4->setVelocity(normalize(glm::vec3(7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_4);

			e2_5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_5->setRotation(180);
			e2_5->setSize(35, 35);
			e2_5->setPosition(glm::vec3(106, 390, 0));
			e2_5->setVelocity(normalize(glm::vec3(-7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_5);

			e2_6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_6->setRotation(180);
			e2_6->setSize(35, 35);
			e2_6->setPosition(glm::vec3(106 + 35, 390 + 25, 0));
			e2_6->setVelocity(normalize(glm::vec3(-7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_6);

			e2_7 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_7->setRotation(180);
			e2_7->setSize(35, 35);
			e2_7->setPosition(glm::vec3(106 + 35*2, 390 + 25*2, 0));
			e2_7->setVelocity(normalize(glm::vec3(-7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_7);

			e2_8 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_8->setRotation(180);
			e2_8->setSize(35, 35);
			e2_8->setPosition(glm::vec3(106 + 35*3, 390 + 25*3, 0));
			e2_8->setVelocity(normalize(glm::vec3(-7, -5, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_8);

			break;
		}
		case(2):
		{
			e1_1 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_1->setRotation(180);
			e1_1->setSize(35, 35);
			e1_1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_1);

			e1_2 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_2->setRotation(180);
			e1_2->setSize(35, 35);
			e1_2->setPosition(glm::vec3(MID_PLAYAREA_X, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_2);

			e1_3 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_3->setRotation(180);
			e1_3->setSize(35, 35);
			e1_3->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_3);

			break;
		}
		case(3):
		{
			e2_1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_1->setRotation(180);
			e2_1->setSize(35, 35);
			e2_1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340, 0));
			e2_1->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_1);

			e2_2 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_2->setRotation(180);
			e2_2->setSize(35, 35);
			e2_2->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43, 0));
			e2_2->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_2);

			e2_3 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_3->setRotation(180);
			e2_3->setSize(35, 35);
			e2_3->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43*2, 0));
			e2_3->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_3);

			e2_4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_4->setRotation(180);
			e2_4->setSize(35, 35);
			e2_4->setPosition(glm::vec3(LEFT_PLAYAREA_X + 10, -340 - 43*3, 0));
			e2_4->setVelocity(normalize(glm::vec3(0, 1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_4);

			e2_5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_5->setRotation(180);
			e2_5->setSize(35, 35);
			e2_5->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340, 0));
			e2_5->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_5);

			e2_6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_6->setRotation(180);
			e2_6->setSize(35, 35);
			e2_6->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43, 0));
			e2_6->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_6);

			e2_7 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_7->setRotation(180);
			e2_7->setSize(35, 35);
			e2_7->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43*2, 0));
			e2_7->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_7);

			e2_8 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_8->setRotation(180);
			e2_8->setSize(35, 35);
			e2_8->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 10, 340 + 43*3, 0));
			e2_8->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_8);

			break;
		}
		case(4):
		{
			e1_1 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_1->setRotation(180);
			e1_1->setSize(35, 35);
			e1_1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_1);

			e1_2 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_2->setRotation(180);
			e1_2->setSize(35, 35);
			e1_2->setPosition(glm::vec3((LEFT_PLAYAREA_X + MID_PLAYAREA_X + 20)/2, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_2);

			e1_3 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_3->setRotation(180);
			e1_3->setSize(35, 35);
			e1_3->setPosition(glm::vec3(MID_PLAYAREA_X, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_3);

			e1_4 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_4->setRotation(180);
			e1_4->setSize(35, 35);
			e1_4->setPosition(glm::vec3((RIGHT_PLAYAREA_X + MID_PLAYAREA_X - 20) / 2, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_4);

			e1_5 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_5->setRotation(180);
			e1_5->setSize(35, 35);
			e1_5->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 20, 400, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_5);

			break; 
		}
		case(5):
		{
			e2_1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_1->setRotation(180);
			e2_1->setSize(35, 35);
			e2_1->setPosition(glm::vec3(MID_PLAYAREA_X - 50, 340, 0));
			e2_1->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.2f);
			Game::getInstance()->getObjectRef()->push_back(e2_1);

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
			e2_1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_1->setRotation(180);
			e2_1->setSize(35, 35);
			e2_1->setPosition(glm::vec3(LEFT_EDGE - 50, 150, 0));
			e2_1->setVelocity(normalize(glm::vec3(1, 0, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_1);

			e2_2 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_2->setRotation(180);
			e2_2->setSize(35, 35);
			e2_2->setPosition(glm::vec3(LEFT_EDGE - 50*2, 150, 0));
			e2_2->setVelocity(normalize(glm::vec3(1, 0, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_2);

			e2_3 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_3->setRotation(180);
			e2_3->setSize(35, 35);
			e2_3->setPosition(glm::vec3(LEFT_EDGE - 50*3, 150, 0));
			e2_3->setVelocity(normalize(glm::vec3(1, 0, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_3);

			e2_4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_4->setRotation(180);
			e2_4->setSize(35, 35);
			e2_4->setPosition(glm::vec3(LEFT_EDGE - 50*4, 150, 0));
			e2_4->setVelocity(normalize(glm::vec3(1, 0, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_4);

			e2_5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_5->setRotation(180);
			e2_5->setSize(35, 35);
			e2_5->setPosition(glm::vec3(RIGHT_EDGE + 50, 250, 0));
			e2_5->setVelocity(normalize(glm::vec3(-1, 0, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_5);

			e2_6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_6->setRotation(180);
			e2_6->setSize(35, 35);
			e2_6->setPosition(glm::vec3(RIGHT_EDGE + 50*2, 250, 0));
			e2_6->setVelocity(normalize(glm::vec3(-1, 0, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_6);

			e2_7 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_7->setRotation(180);
			e2_7->setSize(35, 35);
			e2_7->setPosition(glm::vec3(RIGHT_EDGE + 50*3, 250, 0));
			e2_7->setVelocity(normalize(glm::vec3(-1, 0, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_7);

			e2_8 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_8->setRotation(180);
			e2_8->setSize(35, 35);
			e2_8->setPosition(glm::vec3(RIGHT_EDGE + 50*4, 250, 0));
			e2_8->setVelocity(normalize(glm::vec3(-1, 0, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_8);

			break;
		}
		case(7):
		{
			break;
		}
		case(8):
		{
			e1_1 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_1->setRotation(180);
			e1_1->setSize(35, 35);
			e1_1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 20, 420, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_1);

			e1_2 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_2->setRotation(180);
			e1_2->setSize(35, 35);
			e1_2->setPosition(glm::vec3(MID_PLAYAREA_X, 420, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_2);

			e1_3 = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
			e1_3->setRotation(180);
			e1_3->setSize(35, 35);
			e1_3->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 20, 420, 0));
			Game::getInstance()->getObjectRef()->push_back(e1_3);

			e2_1 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_1->setRotation(180);
			e2_1->setSize(35, 35);
			e2_1->setPosition(glm::vec3(LEFT_PLAYAREA_X + 120, 420 - 60, 0));
			e2_1->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_1);

			e2_2 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_2->setRotation(180);
			e2_2->setSize(35, 35);
			e2_2->setPosition(glm::vec3(LEFT_PLAYAREA_X + 120, 420, 0));
			e2_2->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_2);

			e2_3 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_3->setRotation(180);
			e2_3->setSize(35, 35);
			e2_3->setPosition(glm::vec3(LEFT_PLAYAREA_X + 120, 420 + 60, 0));
			e2_3->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_3);

			e2_4 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_4->setRotation(180);
			e2_4->setSize(35, 35);
			e2_4->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 120, 420 - 60, 0));
			e2_4->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_4);

			e2_5 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_5->setRotation(180);
			e2_5->setSize(35, 35);
			e2_5->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 120, 420, 0));
			e2_5->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_5);

			e2_6 = new Enemy2(Tag::Enemy, "bossgirl-minion2.png", 1, 1);
			e2_6->setRotation(180);
			e2_6->setSize(35, 35);
			e2_6->setPosition(glm::vec3(RIGHT_PLAYAREA_X - 120, 420 + 60, 0));
			e2_6->setVelocity(normalize(glm::vec3(0, -1, 0)) * 1.0f);
			Game::getInstance()->getObjectRef()->push_back(e2_6);

			break;
		}
		default:
		{
			break;
		}
	}
}

void Spawner::SetSpawnRate(float rate)
{
	spawnRate = rate;
}