#pragma once

#include <vector>
#include "TextObject.h"
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "Spawner.h"
#include "Audio.h"

using namespace std;
class Game
{	
	AudioEngine audio;
	Music BGM1, BGM2, BGM3, BGM4;
	unsigned int highScore = 0;
	int pMenuCurrentSelection = 0;
	int optionCurrentSelection = 0;
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
	DrawableObject* optionMenu;
	DrawableObject* pauseMenu;
	Game();
	float e1SpawnRate = 0;
	TextObject * scoreText;
	TextObject * highScoreText;
	TextObject * godModeIndicator;



	bool bossSpawn = false;

public:
	~Game();

	bool BGMisPlaying[4] = { false ,false ,false ,false };

	bool gameBGMisOn = true;
	bool gameSFXisOn = true;

	int gameBGM = 75;
	int gameSFX = 75;


	bool godMode = false;
	vector<string> pMenuSprite;
	vector<string> optMenuSprite;


	bool bombAvailable = false;//true;
	SpriteObject * bomb;

	bool isOptionMenu = false;
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
	void checkOptionMenuInput(char input);

	void writeHighScore();
	void readHighScore();

};