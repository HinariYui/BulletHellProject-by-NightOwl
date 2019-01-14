#pragma once

#include <vector>
#include "TextObject.h"
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
	DrawableObject* pauseMenu;
	Game();
	float e1SpawnRate = 0;
	TextObject * scoreText;

	bool bossSpawn = false;

public:
	bool isPaused = false;
	bool shiftPressed = false;
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