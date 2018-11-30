#pragma once

#include <vector>
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "Spawner.h"

using namespace std;
class Game
{	
	float timer = 0.0f;
	static Game* instance;
	int winWidth, winHeight;
	vector<DrawableObject*> objects;
	vector<Spawner*> spawners;
	GLRenderer *renderer;
	DrawableObject* player;
	DrawableObject* menu;
	Game();
	float e1SpawnRate = 0;

public:
	bool firstRound = true;
	bool menuIsDestroyed = false;
	bool playerIsDead = true;
	static Game* getInstance();
	GLRenderer * getRenderer();
	vector<DrawableObject*>* getObjectRef();//added by me
	void handleMouse(int x, int y);
	void handleKey(char ch);
	void init(int width, int height);
	void render();
	void update(float deltaTime);
	DrawableObject* getPlayerRef();

};