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
	int menuCurrentSelection = 0;
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
	TextObject * scoreText;
	TextObject * highScoreText;
	TextObject * godModeIndicator;

public:
	~Game();

	bool BGMisPlaying[4] = { false ,false ,false ,false };

	bool gameBGMisOn = true;
	bool gameSFXisOn = true;

	int gameBGM = 75;
	int gameSFX = 75;

	bool bossSpawn = false;
	bool spawnBoss1 = false;
	bool spawnBoss2 = false;
	bool boss1Died = false;
	bool boss2Died = false;

	int spawnPattern = 1;
	float eSpawnRate = 8000;
	float eSpawnCD = 1500;
	bool eSpawn = true;
	int spawnNum = 0;

	bool godMode = false;
	vector<string> menuSprite;
	vector<string> pMenuSprite;
	vector<string> optMenuSprite;
	SpriteObject* transition;

	bool bombAvailable = false;//true;
	SpriteObject * bomb;
	//bool optionComponentStatus[15];

	bool isMainMenu = true;
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
	void checkMenuInput(char input);

	void writeHighScore();
	void readHighScore();

	int feedBack();
};