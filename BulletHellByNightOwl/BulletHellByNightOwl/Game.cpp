#include <string>
#include "stdafx.h"
#include "Game.h"
#include "GLRendererColor.h"
#include "SquareMeshVbo.h"
#include "HexagonMeshVbo.h"
#include "CustomMeshVbo.h"
#include "PlayerGameObject.h"
#include "CircleMeshVbo.h"
#include "TextObject.h" 
#include "Boss1.h"
#include "Boss2.h"
#include "Enemy1.h"
#include "Menu.h"
#include "PauseMenu.h"
#include "Spawner.h"
#include "tinyxml2.h"

#define MID_PLAYAREA_X -212

using namespace tinyxml2;

Game* Game::instance = nullptr;
//
//float playerSizeX = 35;
//float playerSizeY = 35;
float playerSizeX = 35;
float playerSizeY = 60;

int scoreTemp;
int lifeTemp;

Game * Game::getInstance()
{
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}

GLRenderer * Game::getRenderer()
{
	return this->renderer;
}

void Game::handleMouse(int x, int y)
{
	float realX, realY;
	realX = -3 + x * (6.0 / winWidth);
	realY = -3 + (winHeight - y) * (6.0 / winHeight);
	if (this->objects.size() > 0) {
		//DrawableObject *obj = this->objects.at(0);
		//obj->setPosition(glm::vec3(realX, realY, 0));

		//GameObject * obj = new GameObject();
		//obj->setColor((realX+3)/6, (realY+3)/6, 0);
		//obj->setPosition(glm::vec3(realX, realY, 0));
		//objects.push_back(obj);
	}
}

void Game::handleKey(char ch)
{
	if(ch == 'e')
	{
		if (menuIsDestroyed == false)
		{
			cout << "in" << endl;
			objects.pop_back();
			menuIsDestroyed = true;
		}
		else
		{
			if (isPaused == true)
			{
				PauseMenu* p = dynamic_cast<PauseMenu*>(pauseMenu);
				if (p->getCurrentSelection() <= 0)
				{
					handleKey('E');//resume
				}
				else if (p->getCurrentSelection() == 1)
				{
					menu = new Menu();
					menu->setSize(1280, 720);
					menu->setPosition(glm::vec3(0, 0, 0));
					objects.clear();
					objects.push_back(menu);
					menuIsDestroyed = false;
					handleKey('E');
					firstRound = true;
					spawners[0]->eNum = 0;
					bossSpawn = false;
				}
				else if (p->getCurrentSelection() == 2)
				{
					exit(0);
				}
				else
				{
					exit(0);
				}
			}
		}
	}

	if (isPaused == true)
	{
		checkPauseMenuInput(ch);
	}

	if (!playerIsDead)
	{

		//cout << ch << endl;
		if (this->objects.size() > 0) {

			PlayerGameObject *p = dynamic_cast<PlayerGameObject*>(this->player);

			if (ch == 'g')
			{
				if (godMode == false)
				{
					SDL_Color color = { 0, 165, 255 };

					godMode = true;
					godModeIndicator = new TextObject();
					godModeIndicator->loadText("G", color, 10);
					godModeIndicator->setPosition(glm::vec3(-615, 325, 0));
					objects.push_back(godModeIndicator);
				}
				else
				{
					godMode = false;
					for (int i = objects.size() - 1; i >= 0; i--)
					{
						DrawableObject* instance = objects.at(i);

						if (instance->getObjId() == godModeIndicator->getObjId())
						{
							objects.erase(objects.begin() + i);
							objects.end();
						}
					}
				}
			}
			if (ch == 'l')
			{
				p->move('l');
			}
			if (ch == 'r')
			{
				p->move('r');
			}
			if (ch == 'u')
			{
				p->move('u');
			}
			if (ch == 'd')
			{
				p->move('d');
			}
			if (ch == 'L')//release button
			{
				p->move('L');
			}
			if (ch == 'R')
			{
				p->move('R');
			}
			if (ch == 'U')
			{
				p->move('U');
			}
			if (ch == 'D')
			{
				p->move('D');
			}
			if (ch == 'z')
			{
				p->shoot('z');
			}
			if (ch == 'Z')
			{
				p->shoot('Z');
			}
			if (ch == 's')
			{
				shiftPressed = true;
			}
			if (ch == 'S')
			{
				shiftPressed = false;
			}
			if (ch == 'E')
			{

				if (isPaused == false)
				{
					if (menuIsDestroyed == true)
					{
						pMenuCurrentSelection = 0;
						pauseMenu = new PauseMenu(pMenuSprite, 10, 3);
						pauseMenu->setSize(1280, 720);
						pauseMenu->setPosition(glm::vec3(0, 0, 0));
						//objects.push_back(pauseMenu); // index 8

						isPaused = true;
					}
				}
				else
				{
					PauseMenu* p = dynamic_cast<PauseMenu*>(pauseMenu);
					p->destroyComponents();

					for (int i = objects.size() - 1; i >= 0; i--)
					{
						DrawableObject* instance = objects.at(i);

						if (instance->getObjId() == pauseMenu->getObjId())
						{
							objects.erase(objects.begin() + i);
							objects.end();
						}
					}

					isPaused = false;
				}

			}
		}
	}


}

void Game::init(int width, int height)
{
	winWidth = width;
	winHeight = height;
	renderer = new GLRendererColor(width, height);
	renderer->initGL("Shaders/Texture/vertext.shd", "Shaders/Texture/fragment.shd");
	renderer->setOrthoProjection(-640, 640, -360, 360);
	renderer->setClearColor(1.0f, 1.0f, 200.0f / 255);

	//PA = Play Area
	SquareMeshVbo * squareMesh = new SquareMeshVbo();
	squareMesh->loadData();
	renderer->addMesh(SquareMeshVbo::MESH_NAME, squareMesh);

	menu = new Menu();
	menu->setSize(1280, 720);
	menu->setPosition(glm::vec3(0, 0, 0));
	objects.push_back(menu); // index 8

	Spawner* e1 = new Spawner();
	e1->SetSpawnRate(1000);
	spawners.push_back(e1);

	pMenuSprite.push_back("pauseMenu.png");
	pMenuSprite.push_back("Buttons/Idle_Resume_160x72.png");
	pMenuSprite.push_back("Buttons/Idle_Mainmenu_160x72.png");
	pMenuSprite.push_back("Buttons/Idle_Quit_160x72.png");
	pMenuSprite.push_back("Buttons/Hover_Resume_128x219.png");
	pMenuSprite.push_back("Buttons/Hover_Mainmenu_128x219.png");
	pMenuSprite.push_back("Buttons/Hover_Quit_128x219.png");
	pMenuSprite.push_back("Buttons/Pressed_Resume_128x219.png");
	pMenuSprite.push_back("Buttons/Pressed_Mainmenu1_128x219.png");
	pMenuSprite.push_back("Buttons/Pressed_Quit_128x219.png");
	//getXMLspawnData();



	//SpriteObject * BG = new SpriteObject("bgBase.png", 1, 1); //BG
	//BG->setSize(1280, 720);
	//BG->setPosition(glm::vec3(0, 0, 0));
	//objects.push_back(BG);

	//SpriteObject * PA = new SpriteObject("bg1.png", 1, 1); //Play Area
	//PA->setSize(1280, 720);
	//PA->setPosition(glm::vec3(-212, 0, 0));
	//objects.push_back(PA); // index 0
	//cout << "IIIIIIIIIIIIDDDDDDDDDD     0          " << PA->getObjId()<< endl;

	////GameObject * perBG1 = new GameObject(Tag::BG);
	////perBG1->setColor(0, 1, 0);
	////perBG1->setSize(116, 670);
	////perBG1->setRotation(-10);
	////perBG1->setPosition(glm::vec3(-377, 10, 0));
	////objects.push_back(perBG1); // index 1
	////cout << "IIIIIIIIIIIIDDDDDDDDDD     1        " << perBG1->getObjId() << endl;


	////GameObject * perBG2 = new GameObject(Tag::BG);
	////perBG2->setColor(0, 1, 0);
	////perBG2->setSize(116, 670);
	////perBG2->setRotation(10);
	////perBG2->setPosition(glm::vec3(121, 10, 0));
	////objects.push_back(perBG2); // index 2
	//
	//GameObject * BG1 = new GameObject(Tag::Wall);
	//BG1->setColor(1, 0.7, 0);
	//BG1->setSize(518, 720);
	//BG1->setPosition(glm::vec3(381, 0, 0));
	//objects.push_back(BG1); // index 3
	//
	//GameObject * BG2 = new GameObject(Tag::Wall);
	//BG2->setColor(1, 0.7, 0);
	//BG2->setSize(262, 720);
	//BG2->setPosition(glm::vec3(-509, 0, 0));
	//objects.push_back(BG2); // index 4
	//
	//GameObject * BG3 = new GameObject(Tag::Wall);
	//BG3->setColor(1, 0.7, 0);
	//BG3->setSize(500, 30);
	//BG3->setPosition(glm::vec3(-128, -345, 0));
	//objects.push_back(BG3); // index 5
	//
	//GameObject * BG4 = new GameObject(Tag::Wall);
	//BG4->setColor(1, 0.7, 0);
	//BG4->setSize(500, 30);
	//BG4->setPosition(glm::vec3(-128, 345, 0));
	//objects.push_back(BG4); // index 6

	//player = new PlayerGameObject(Tag::Player);

	//PlayerGameObject* p = dynamic_cast<PlayerGameObject *>(player);

	//p->setSize(playerSizeX, playerSizeY);
	//p->setRotation(180);
	//p->setPosition(glm::vec3(-212, -250, 0));
	//p->setAnimationLoop(1,1,4,1000);
	//objects.push_back(player); // index 7

	//Boss1 * boss = new Boss1(Tag::Enemy, "bg1.png", 4, 4); //Tag enemy, string fileName, int row, int col
	////boss->setColor(1.0, 0.0, 0.0);
	//boss->setSize(100, 100);
	//boss->setPosition(glm::vec3(-212, 200, 0));
	//p->setAnimationLoop(1, 1, 0, 1000);
	//objects.push_back(boss); // index 8

}

void Game::render()
{
	this->getRenderer()->render(this->objects);
}

Game::Game()
{
	for (DrawableObject* obj : objects) {
		delete obj;
	}
	renderer = nullptr;
}

void Game::update(float deltaTime)
{
	if (menuIsDestroyed == true)
	{
		if (firstRound == true)
		{
			SpriteObject * BG = new SpriteObject("bg1-3-base.png", 1, 1); //BG
			BG->setSize(1280, 720);
			BG->setPosition(glm::vec3(0, 0, 0));
			objects.push_back(BG);

			SpriteObject * PA = new SpriteObject("bg1-3.png", 2, 1); //Play Area
			PA->setSize(1280, 720);
			PA->setPosition(glm::vec3(-212, 0, 0));
			objects.push_back(PA); // index 0


			player = new PlayerGameObject(Tag::Player);
			PlayerGameObject* p = dynamic_cast<PlayerGameObject *>(player);

			p->setSize(playerSizeX/7, playerSizeY/12);
			p->setRotation(180);
			p->setPosition(glm::vec3(-212, -250, 0));
			p->setAnimationLoop(1, 1, 4, 1000);
			objects.push_back(player); // index 7

			//Boss1 * boss = new Boss1(Tag::Enemy, "bossgirl-sample.png", 1, 1); //Tag enemy, string fileName, int row, int col
			//boss->setRotation(180);													   //boss->setColor(1.0, 0.0, 0.0);
			//boss->setSize(100, 100);
			//boss->setPosition(glm::vec3(-212, 200, 0));
			//p->setAnimationLoop(1, 1, 0, 1000);
			//objects.push_back(boss); // index 8

			for (int i = 0; i < p->life; i++)
			{
				life[i] = new GameObject(Tag::NONE);
				life[i]->setColor(0.7, 0, 0);
				life[i]->setSize(20, 20);
				life[i]->setPosition(glm::vec3(485 + 50*i, 250, 0));
				objects.push_back(life[i]);
			}

			SDL_Color color = { 255, 165, 255 };

			TextObject * text1 = new TextObject();
			text1->loadText("SCORE", color, 30);
			text1->setPosition(glm::vec3(535, 185, 0));
			objects.push_back(text1); // index 8

			std::string s = std::to_string(p->score);

			scoreText = new TextObject();
			scoreText->loadText(s, color, 30);
			scoreText->setPosition(glm::vec3(535, 150, 0));
			objects.push_back(scoreText);

			playerIsDead = false;
			firstRound = false;
		}
			
		SDL_Color color = { 255, 165, 255 };
		PlayerGameObject* p = dynamic_cast<PlayerGameObject *>(player);
		std::string s = std::to_string(p->score);
		scoreText->loadText(s, color, 30);
		scoreTemp = p->score;
		lifeTemp = p->life;

		if (playerIsDead)
		{
			shiftPressed = false;
			isPaused = false;
			timer += deltaTime;
			if (timer > 1000)
			{
				player = new PlayerGameObject(Tag::Player);

				PlayerGameObject* p = dynamic_cast<PlayerGameObject*>(player);
				p->score = scoreTemp;
				p->life = lifeTemp;
				p->SetInvincible(true);
				p->setSize(playerSizeX/7, playerSizeY/12);
				p->setRotation(180);
				p->setPosition(glm::vec3(-212, -250, 0));
				p->setAnimationLoop(1, 1, 4, 1000);
				objects.push_back(player);

				if (p->life > 0)
				{
					for (int i = objects.size() - 1; i >= 0; i--)
					{
						DrawableObject* instance = objects.at(i);

						if (instance->getObjId() == life[(p->life)]->getObjId())
						{
							objects.erase(objects.begin() + i);
							objects.end();
						}
					}
				}
				else
				{
					menu = new Menu();
					menu->setSize(1280, 720);
					menu->setPosition(glm::vec3(0, 0, 0));
					objects.clear();
					objects.push_back(menu);
					menuIsDestroyed = false;
					handleKey('E');
					firstRound = true;
					spawners[0]->eNum = 0;
					bossSpawn = false;
				}

				playerIsDead = false;
				timer = 0;
			}
		}


		//e1SpawnRate += deltaTime;
		//if (e1SpawnRate >= 1000)
		//{
		//	int x = rand() % 300 - MID_PLAYAREA_X - 462;
		//	Enemy1 * enemy = new Enemy1(Tag::Enemy, "bossgirl-minion2.png", 1, 1); //Tag enemy, string fileName, int row, int col
		//	enemy->setRotation(180);													   //boss->setColor(1.0, 0.0, 0.0);
		//	enemy->setSize(35, 35);
		//	enemy->setPosition(glm::vec3(x, 300, 0));
		//	objects.push_back(enemy);
		//	e1SpawnRate = 0;
		//}

		//for (DrawableObject *obj : this->objects)
		
		if (isPaused == false)
		{
			for (int i = 0; i < spawners.size(); i++)
			{
				spawners[i]->update(deltaTime);
			}

			if (spawners[0]->eNum > 1 && bossSpawn == false)
			{
				spawners[0]->SetSpawnRate(2500);
				Boss2 * boss = new Boss2(Tag::Enemy, "bossgirl-sample.png", 1, 1); //Tag enemy, string fileName, int row, int col
				boss->setRotation(180);													   //boss->setColor(1.0, 0.0, 0.0);
				boss->setSize(100, 100);
				boss->setPosition(glm::vec3(-212, 400, 0));
				objects.push_back(boss);
				bossSpawn = true;
			}

			for (int i = 0; i < objects.size(); i++)
			{
				objects[i]->update(deltaTime);
				//obj->update(deltaTime);
			}

			//cout << playtime << "      ";
			playtime += deltaTime;
			//cout << playtime << endl;
		}
	}

}

vector<DrawableObject*>* Game::getObjectRef()
{
	return &objects;
}

DrawableObject* Game::getPlayerRef()
{
	return this->player;
}

int  Game::getXMLspawnData()
{
	//std::cout << "Hello World!\n";

	XMLDocument doc;
	int errorID = doc.LoadFile("SpawnData.xml");

	if (errorID != 0)
	{
		std::cout << "XMLDocument error : " << doc.ErrorName() << std::endl;

		std::cout << errorID << endl;
		return -1;
	}

	XMLElement * stageEle = doc.FirstChildElement("Root")->FirstChildElement("Stage1");
	XMLElement * enemyEle = stageEle->FirstChildElement("Boss");
	XMLElement * ele = enemyEle->FirstChildElement();

	while (ele != NULL)
	{
		const char* text = ele->GetText();
		cout << "From " << stageEle->Value() << "::" << enemyEle->Value() << "::"<< ele->Value() << " : " << text << endl;
		ele = ele->NextSiblingElement();
		if (ele == NULL)
		{
			if (enemyEle->NextSiblingElement() != NULL)
			{
				enemyEle = enemyEle->NextSiblingElement();
				ele = enemyEle->FirstChildElement();
			}
			else
			{
				if (stageEle->NextSiblingElement() != NULL)
				{
					stageEle = stageEle->NextSiblingElement();
					enemyEle = stageEle->FirstChildElement();
					ele = enemyEle->FirstChildElement();
				}
				else
				{
					break;
				}
			}
		}
	}
	//std::cout << "Finish\n";
	return 0;
}

void Game::checkPauseMenuInput(char input)
{
	PauseMenu* p = dynamic_cast<PauseMenu*>(pauseMenu);

	


	if (pMenuCurrentSelection <= 0) //on resume
	{
		if (input == 'u')
		{
			pMenuCurrentSelection = 0;
			p->setCurrentSelection(pMenuCurrentSelection);



		}
		else if (input == 'd')
		{
			pMenuCurrentSelection = 1;
			p->setCurrentSelection(pMenuCurrentSelection);
		}
	}
	else if (pMenuCurrentSelection == 1) // on main menu
	{
		if (input == 'u')
		{
			pMenuCurrentSelection = 0;
			p->setCurrentSelection(pMenuCurrentSelection);
		}
		else if (input == 'd')
		{
			pMenuCurrentSelection = 2;
			p->setCurrentSelection(pMenuCurrentSelection);
		}
	}
	else if (pMenuCurrentSelection == 2) // on setting?
	{
		if (input == 'u')
		{
			pMenuCurrentSelection = 1;
			p->setCurrentSelection(pMenuCurrentSelection);
		}
		else if (input == 'd')
		{
			pMenuCurrentSelection = 3;
			p->setCurrentSelection(pMenuCurrentSelection);
		}
	}
	else // on quit 
	{
		if (input == 'u')
		{
			pMenuCurrentSelection = 2;
			p->setCurrentSelection(pMenuCurrentSelection);
		}
		else if (input == 'd')
		{
			pMenuCurrentSelection = 3;
			p->setCurrentSelection(pMenuCurrentSelection);
		}

	}

	cout << "PMenuCurrentSelection " << pMenuCurrentSelection << endl;
}

Game::~Game()
{
	//cout << "destroying game" << endl;
	//delete instance;
	//delete scoreText;
	//delete pauseMenu;
	//delete menu;
	//delete player;
	//delete renderer;
	//spawners.clear();
	//objects.clear();
	//pMenuSprite.clear();
}


