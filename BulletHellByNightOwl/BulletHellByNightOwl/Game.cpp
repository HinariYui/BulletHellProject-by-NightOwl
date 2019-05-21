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
#include "OptionMenu.h"
#include "Spawner.h"
#include "tinyxml2.h"
#include "Audio.h"

#include <fstream>

#define MID_PLAYAREA_X -212

int bombSize = 5;

using namespace tinyxml2;

Game* Game::instance = nullptr;
//
//float playerSizeX = 35;
//float playerSizeY = 35;
float playerSizeX = 35;
float playerSizeY = 60;

int scoreTemp;
int lifeTemp;
int BGMTemp;
int SFXTemp;


bool spawnBoss1 = false;
bool spawnBoss2 = false;
int bossIndex;

Boss1* boss1;
Boss2* boss2;
Spawner* e;

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
	if (ch == 'e')
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

				if (isOptionMenu == false)
				{
					p->updateComponent('e');
				}
				else
				{
					//in optionMenu
					checkOptionMenuInput('e');
				}
			}
		}
	}
	if (ch == 'E') 
	{
		if (isPaused == true)
		{
			PauseMenu* p = dynamic_cast<PauseMenu*>(pauseMenu);
			if (isOptionMenu == false)
			{
				p->updateComponent('E');
				if (p->getCurrentSelection() <= 0)
				{
					handleKey('x');//resume
				}
				else if (p->getCurrentSelection() == 1)
				{
					menu = new Menu();
					menu->setSize(1280, 720);
					menu->setPosition(glm::vec3(0, 0, 0));
					objects.clear();
					objects.push_back(menu);
					menuIsDestroyed = false;
					handleKey('x');
					firstRound = true;
					spawners[0]->eNum = 0;
					bossSpawn = false;
					godMode = false;
				}
				else if (p->getCurrentSelection() == 2)
				{
					//optionMenu
					optionCurrentSelection = 0;
					optionMenu = new OptionMenu(optMenuSprite, 3, 2);
					optionMenu->setSize(1280, 720);
					optionMenu->setPosition(glm::vec3(0, 0, 0));
					isOptionMenu = true;
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
		if (isOptionMenu == false)
		{
			checkPauseMenuInput(ch);
		}
		else
		{

		}
	}

	if (!playerIsDead)
	{
		if (this->objects.size() > 0)
		{
			PlayerGameObject *p = dynamic_cast<PlayerGameObject*>(this->player);

			if (ch == ' ')
			{
				//SPACEBAR = bomb trigger
				if (bombAvailable == true)
				{
					//create bomb + clear all minion
					bomb = new SpriteObject(" ", 1, 1); //BG
					bomb->setSize(bombSize, bombSize);
					bomb->setPosition(glm::vec3(-212, 0, 0));
					objects.push_back(bomb);
					bombAvailable = false;
				}
			}
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
				if (isOptionMenu == true)
				{
					checkOptionMenuInput('l');
				}
			}
			if (ch == 'r')
			{
				p->move('r');
				if (isOptionMenu == true)
				{
					checkOptionMenuInput('r');
				}
			}
			if (ch == 'u')
			{
				p->move('u');
				if (isOptionMenu == true)
				{
					checkOptionMenuInput('u');
				}
			}
			if (ch == 'd')
			{
				p->move('d');
				if (isOptionMenu == true)
				{
					checkOptionMenuInput('d');
				}
			}
			if (ch == 'L')//release button
			{
				p->move('L');
				if (isOptionMenu == true)
				{
					checkOptionMenuInput('L');
				}
			}
			if (ch == 'R')
			{
				p->move('R');
				if (isOptionMenu == true)
				{
					checkOptionMenuInput('R');
				}
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
			if (ch == 'x')
			{
				if (isPaused == false)
				{
					if (menuIsDestroyed == true)
					{
						pMenuCurrentSelection = 0;
						pauseMenu = new PauseMenu(pMenuSprite, 13, 4);
						pauseMenu->setSize(1280, 720);
						pauseMenu->setPosition(glm::vec3(0, 0, 0));
						//objects.push_back(pauseMenu); // index 8

						isPaused = true;
					}
				}
				else
				{
					if (isOptionMenu == false)
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
					else
					{
						//to exit optionMenu
						OptionMenu* opt = dynamic_cast<OptionMenu*>(optionMenu);
						opt->destroyComponents();
						for (int i = objects.size() - 1; i >= 0; i--)
						{
							DrawableObject* instance = objects.at(i);
							if (instance->getObjId() == optionMenu->getObjId())
							{
								objects.erase(objects.begin() + i);
								objects.end();
							}
						}

						isOptionMenu = false;
					}
				}
			}
		}
		if (ch == 'o')
		{
			spawnBoss1 = true;
			spawnBoss2 = false;
			bossSpawn = false;
		}
		if (ch == 'p')
		{
			spawnBoss2 = true;
			spawnBoss1 = false;
			bossSpawn = false;
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

	readHighScore();//get saved highScore

	//PA = Play Area
	SquareMeshVbo * squareMesh = new SquareMeshVbo();
	squareMesh->loadData();
	renderer->addMesh(SquareMeshVbo::MESH_NAME, squareMesh);

	menu = new Menu();
	menu->setSize(1280, 720);
	menu->setPosition(glm::vec3(0, 0, 0));
	objects.push_back(menu); // index 8

	e = new Spawner();
	e->SetSpawnRate(1000);
	spawners.push_back(e);

	pMenuSprite.push_back("pauseMenu.png");
	pMenuSprite.push_back("Buttons/Idle_ResumeFIX_219x129.png");//idle
	pMenuSprite.push_back("Buttons/Idle_MainmenuFIX_219x129.png");
	pMenuSprite.push_back("Buttons/Idle_Option_219x129.png");
	pMenuSprite.push_back("Buttons/Idle_QuitFIX_219x129.png");
	pMenuSprite.push_back("Buttons/Hovered_ResumeFIX_219x129.png");//hover
	pMenuSprite.push_back("Buttons/Hovered_MainmenuFIX_219x129.png");
	pMenuSprite.push_back("Buttons/Hovered_Option_219x129.png");
	pMenuSprite.push_back("Buttons/Hovered_QuitFIX_219x129.png");
	pMenuSprite.push_back("Buttons/Press_ResumeFIX_219x129.png");//press
	pMenuSprite.push_back("Buttons/Pressed_MainmenuFIX_219x129.png");
	pMenuSprite.push_back("Buttons/Press_Option_219x129.png");
	pMenuSprite.push_back("Buttons/Pressed_QuitFIX_219x129.png");

	optMenuSprite.push_back("Option/Option_BG.png");
	optMenuSprite.push_back("Option/Idle_BackgroundMusic_219x129.png");
	optMenuSprite.push_back("Option/Idle_SoundEffect_219x129.png");

	optMenuSprite.push_back("Option/Option219x129.png");
	optMenuSprite.push_back("Option/Speaker50x50.png");
	optMenuSprite.push_back("Option/SpeakerSilence50x50.png");
	optMenuSprite.push_back("Option/Idle_LArrow50x50.png");
	optMenuSprite.push_back("Option/Idle_RArrow50x50.png");

	optMenuSprite.push_back("Option/Selected_BackgroundMusic_219x129.png");
	optMenuSprite.push_back("Option/Selected_SoundEffect_219x129.png");


	optMenuSprite.push_back("Option/LArrow50x50.png");
	optMenuSprite.push_back("Option/RArrow50x50.png");




	//optMenuSprite.push_back("tempSFXSelection");
	//optMenuSprite.push_back("tempBGMSelection");
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
	//cout << "gameLife"<< lifeTemp << endl;

	if (bomb != NULL)
	{
		bombSize = bombSize * 1.2 ;
		bomb->setSize(bombSize, bombSize);

		if (bombSize > 720)
		{
			for (int i = objects.size() - 1; i >= 0; i--)
			{
				DrawableObject* instance = objects.at(i);

				if (instance->getObjId() == bomb->getObjId())
				{
					objects.erase(objects.begin() + i);
					objects.end();
				}
			}
		}
	}


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

			color = { 255, 165, 0 };
			TextObject * text2 = new TextObject();
			text2->loadText("HIGHSCORE", color, 20);
			text2->setPosition(glm::vec3(535, -300, 0));
			objects.push_back(text2); // index 8

			std::string s2 = std::to_string(highScore);

			highScoreText = new TextObject();
			highScoreText->loadText(s2, color, 20);
			highScoreText->setPosition(glm::vec3(535, -325, 0));
			objects.push_back(highScoreText);

			playerIsDead = false;
			firstRound = false;
		}
			
		SDL_Color color = { 255, 165, 255 };
		PlayerGameObject* p = dynamic_cast<PlayerGameObject *>(player);
		std::string s = std::to_string(p->score);
		scoreText->loadText(s, color, 30);
		scoreTemp = p->score;
		lifeTemp = p->life;

		if (p->score > highScore)
		{
			highScore = p->score;
			writeHighScore();
			SDL_Color color = { 255, 165, 0 };
			std::string s = std::to_string(highScore);
			highScoreText->loadText(s, color, 20);
		}

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
					handleKey('x');
					firstRound = true;
					spawners[0]->eNum = 0;
					//bossSpawn = false; //เปิดแล้วมีบัคตอน Gameover
				}

				playerIsDead = false;
				timer = 0;
			}
		}


		e1SpawnRate += deltaTime;
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
		if (e1SpawnRate >= 2000)
		{
			e->EnemySpawn(1);
			e1SpawnRate = 0;
		}
		
		//for (DrawableObject *obj : this->objects)
		
		if (isPaused == false)
		{
			//for (int i = 0; i < spawners.size(); i++)
			//{
			//	spawners[i]->update(deltaTime);
			//}
			//
			//if (spawners[0]->eNum > 1 && bossSpawn == false)
			//{
			//	spawners[0]->SetSpawnRate(2500);
			//	Boss2 * boss = new Boss2(Tag::Enemy, "bossgirl-sample.png", 1, 1); //Tag enemy, string fileName, int row, int col
			//	boss->setRotation(180);													   //boss->setColor(1.0, 0.0, 0.0);
			//	boss->setSize(100, 100);
			//	boss->setPosition(glm::vec3(-212, 400, 0));
			//	objects.push_back(boss);
			//	bossSpawn = true;
			//}

			if (spawnBoss1 && !bossSpawn)
			{

				if (boss1 != nullptr)
				{
					for (int i = objects.size() - 1; i >= 0; i--)
					{
						DrawableObject* instance = objects.at(i);

						if (instance->getObjId() == boss1->getObjId())
						{
							objects.erase(objects.begin() + i);
							objects.end();
						}
					}
				}
				if (boss2 != nullptr)
				{
					for (int i = objects.size() - 1; i >= 0; i--)
					{
						DrawableObject* instance = objects.at(i);

						if (instance->getObjId() == boss2->getObjId())
						{
							objects.erase(objects.begin() + i);
							objects.end();
						}
					}
				}

				boss1 = new Boss1(Tag::Enemy, "Boss1_Idle_ColorVer3_82x100.png", 1, 1); //Tag enemy, string fileName, int row, int col
				boss1->setRotation(180);													   //boss->setColor(1.0, 0.0, 0.0);
				boss1->setSize(100, 120);
				boss1->setPosition(glm::vec3(-212, 400, 0));
				objects.push_back(boss1);
				bossSpawn = true;
			}
			if (spawnBoss2 && !bossSpawn)
			{
				if (boss1 != nullptr)
				{
					for (int i = objects.size() - 1; i >= 0; i--)
					{
						DrawableObject* instance = objects.at(i);

						if (instance->getObjId() == boss1->getObjId())
						{
							objects.erase(objects.begin() + i);
							objects.end();
						}
					}
				}
				if (boss2 != nullptr)
				{
					for (int i = objects.size() - 1; i >= 0; i--)
					{
						DrawableObject* instance = objects.at(i);

						if (instance->getObjId() == boss2->getObjId())
						{
							objects.erase(objects.begin() + i);
							objects.end();
						}
					}
				}

				boss2 = new Boss2(Tag::Enemy, "bossgirl-sample.png", 1, 1); //Tag enemy, string fileName, int row, int col
				boss2->setRotation(180);													   //boss->setColor(1.0, 0.0, 0.0);
				boss2->setSize(100, 100);
				boss2->setPosition(glm::vec3(-212, 400, 0));
				objects.push_back(boss2);
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
		else
		{
			pauseMenu->update(deltaTime);
			if (isOptionMenu == true)
			{
				optionMenu->update(deltaTime);
			}
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

void Game::checkOptionMenuInput(char input)
{
	OptionMenu* opt = dynamic_cast<OptionMenu*>(optionMenu);

	if (optionCurrentSelection <= 0) //on resume
	{
		if (input == 'u')
		{
			optionCurrentSelection = 0;
			opt->setCurrentSelection(optionCurrentSelection);

		}
		else if (input == 'd')
		{
			optionCurrentSelection = 1;
			opt->setCurrentSelection(optionCurrentSelection);
		}
		else if (input == 'l')
		{
			opt->decreaseVol();
		}
		else if (input == 'r')
		{
			opt->increaseVol();

		}
		else if (input == 'e')
		{
			opt->toggleOnOff();
		}
		else if (input == 'L')
		{
			opt->decreaseVolUpdate();
		}
		else if (input == 'R')
		{
			opt->increaseVolUpdate();

		}

	}
	else 
	{
		if (input == 'u')
		{
			optionCurrentSelection = 0;
			opt->setCurrentSelection(optionCurrentSelection);
		}
		else if (input == 'd')
		{
			optionCurrentSelection = 1;
			opt->setCurrentSelection(optionCurrentSelection);
		}
		else if (input == 'l')
		{
			opt->decreaseVol();
		}
		else if (input == 'r')
		{
			opt->increaseVol();
		}
		else if (input == 'e')
		{
			opt->toggleOnOff();
		}
		else if (input == 'L')
		{
			opt->decreaseVolUpdate();
		}
		else if (input == 'R')
		{
			opt->increaseVolUpdate();

		}
	}

	cout << "optionCurrentSelection " << optionCurrentSelection << endl;
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


void Game::writeHighScore()
{
	ofstream myfile("highScore.txt");
	if (myfile.is_open())
	{
		myfile << highScore;
		myfile.close();
	}
	else cout << "Unable to open file";

}
void Game::readHighScore()
{
	string line;
	ifstream myfile("highScore.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
			highScore = stoi(line);
			cout << highScore << ":)\n";
		}
		myfile.close();
	}
	else cout << "Unable to open file";


}


