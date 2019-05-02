#pragma once

#include <vector>
#include "TextObject.h"
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "Spawner.h"

using namespace std;
class Game
{	
	unsigned int highScore = 0;
	int pMenuCurrentSelection = 0;
	float playtime = 0.0f;
	float timer = 0.0f;
	static Game* instance;
	int winWidth, winHeight;
	GameObject* life[3];
	vector<DrawableObject*> objects;
	vector<Spawner*> spawners;
	GLRenderer *renderer;
	DrawableObject* player;
	DrawableObject* menu;
	DrawableObject* pauseMenu;
	Game();
	float e1SpawnRate = 0;
	TextObject * scoreText;
	TextObject * highScoreText;
	TextObject * godModeIndicator;


	bool bossSpawn = false;

public:
	~Game();
	bool godMode = false;
	vector<string> pMenuSprite;

	bool bombAvailable = true;
	SpriteObject * bomb;

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
	int getXMLspawnData();
	void checkPauseMenuInput(char input);

	void writeHighScore();
	void readHighScore();

};