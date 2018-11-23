#include "stdafx.h"
#include "Game.h"
#include "GLRendererColor.h"
#include "SquareMeshVbo.h"
#include "HexagonMeshVbo.h"
#include "CustomMeshVbo.h"
#include "PlayerGameObject.h"
#include "CircleMeshVbo.h"
#include "SpriteObject.h"

Game* Game::instance = nullptr;
//
//float playerSizeX = 35;
//float playerSizeY = 35;
float playerSizeX = 40;
float playerSizeY = 40;

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
	if (!playerIsDead)
	{

		cout << ch << endl;
		if (this->objects.size() > 0) {
			DrawableObject * playerObj = this->objects.at(playerIndex);
			PlayerGameObject * player = dynamic_cast<PlayerGameObject *>(playerObj);

			if (ch == 'l')
			{
				player->move('l');
			}
			if (ch == 'r')
			{
				player->move('r');
			}
			if (ch == 'u')
			{
				player->move('u');
			}
			if (ch == 'd')
			{
				player->move('d');
			}
			if (ch == 'L')//release button
			{
				player->move('L');
			}
			if (ch == 'R')
			{
				player->move('R');
			}
			if (ch == 'U')
			{
				player->move('U');
			}
			if (ch == 'D')
			{
				player->move('D');
			}
			if (ch == 'z')
			{
				player->shoot('z');
			}
			if (ch == 'Z')
			{
				player->shoot('Z');
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

	GameObject * PA = new GameObject(Tag::BG); //Play Area
	PA->setSize(500, 660);
	PA->setPosition(glm::vec3(-128, 0, 0));
	objects.push_back(PA); // index 0
	cout << "IIIIIIIIIIIIDDDDDDDDDD     0          " << PA->getObjId()<< endl;

	//GameObject * perBG1 = new GameObject(Tag::BG);
	//perBG1->setColor(0, 1, 0);
	//perBG1->setSize(116, 670);
	//perBG1->setRotation(-10);
	//perBG1->setPosition(glm::vec3(-377, 10, 0));
	//objects.push_back(perBG1); // index 1
	//cout << "IIIIIIIIIIIIDDDDDDDDDD     1        " << perBG1->getObjId() << endl;


	//GameObject * perBG2 = new GameObject(Tag::BG);
	//perBG2->setColor(0, 1, 0);
	//perBG2->setSize(116, 670);
	//perBG2->setRotation(10);
	//perBG2->setPosition(glm::vec3(121, 10, 0));
	//objects.push_back(perBG2); // index 2
	
	GameObject * BG1 = new GameObject(Tag::Wall);
	BG1->setColor(1, 0.7, 0);
	BG1->setSize(518, 720);
	BG1->setPosition(glm::vec3(381, 0, 0));
	objects.push_back(BG1); // index 3
	
	GameObject * BG2 = new GameObject(Tag::Wall);
	BG2->setColor(1, 0.7, 0);
	BG2->setSize(262, 720);
	BG2->setPosition(glm::vec3(-509, 0, 0));
	objects.push_back(BG2); // index 4
	
	GameObject * BG3 = new GameObject(Tag::Wall);
	BG3->setColor(1, 0.7, 0);
	BG3->setSize(500, 30);
	BG3->setPosition(glm::vec3(-128, -345, 0));
	objects.push_back(BG3); // index 5
	
	GameObject * BG4 = new GameObject(Tag::Wall);
	BG4->setColor(1, 0.7, 0);
	BG4->setSize(500, 30);
	BG4->setPosition(glm::vec3(-128, 345, 0));
	objects.push_back(BG4); // index 6

	PlayerGameObject * player = new PlayerGameObject(Tag::Player);
	player->setSize(playerSizeX, playerSizeY);
	player->setRotation(180);
	player->setPosition(glm::vec3(-128, -250, 0));
	player->setAnimationLoop(1,1,4,1000);
	objects.push_back(player); // index 7
	
	GameObject * boss = new GameObject(Tag::Enemy);
	boss->setColor(1.0, 0.0, 0.0);
	boss->setSize(100, 100);
	boss->setPosition(glm::vec3(-128, 200, 0));
	objects.push_back(boss); // index 8

	
	



	//SpriteObject * character = new SpriteObject("character.png", 4, 4);
	//character->setSize(200, -200 * 1.5);
	//character->setAnimationLoop(1, 1, 16, 4000);
	//objects.push_back(character);
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
	
	timer += deltaTime;
	if (timer > 3000)
	{
		if (playerIsDead)
		{
			PlayerGameObject * player = new PlayerGameObject(Tag::Player);
			player->setSize(playerSizeX, playerSizeY);
			player->setRotation(180);
			player->setPosition(glm::vec3(-128, -250, 0));
			player->setAnimationLoop(1, 1, 4, 1000);
			objects.push_back(player);
			
			for (int i = objects.size() - 1; i >= 0; i--)
			{
				DrawableObject* instance = objects.at(i);

				if (instance->getObjId() == player->getObjId())
				{
					playerIndex = i;
					break;
				}
			}

			playerIsDead = false;
		}
	}

	//for (DrawableObject *obj : this->objects)
	for(int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(deltaTime);
		//obj->update(deltaTime);
	}


}

vector<DrawableObject*>* Game::getObjectRef()
{
	return &objects;
}





