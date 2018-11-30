#pragma once

#include <vector>
#include "DrawableObject.h"
#include "GLRenderer.h"

using namespace std;
class Game
{	
	float timer = 0.0f;
	static Game* instance;
	int winWidth, winHeight;
	vector<DrawableObject*> objects;
	GLRenderer *renderer;
	DrawableObject* player;
	Game();
	float e1SpawnRate = 0;

public:
	bool playerIsDead = false;
	static Game* getInstance();
	GLRenderer * getRenderer();
	vector<DrawableObject*>* getObjectRef();//added by me
	void handleMouse(int x, int y);
	void handleKey(char ch);
	void init(int width, int height);
	void render();
	void update(float deltaTime);

};