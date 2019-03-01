#include "EnemyBullet.h"
#include "Game.h"

#define LEFTBORDER -462
#define	RIGHTBORDER 38

void EnemyBullet::update(float deltaTime)
{
	float constant = deltaTime * 0.05; //to scale according to deltaTime
	translate(constant*velocity);

	float halfSizeX = (size.x * 0.5f) + 4;
	float halfSizeY = (size.y * 0.5f) + 4;

	if ((pos.x > RIGHTBORDER + halfSizeX) || (pos.x < LEFTBORDER - halfSizeX) || (pos.y > 330 + halfSizeY) || (pos.y < -330 - halfSizeY))
	{
		for (int i = Game::getInstance()->getObjectRef()->size() - 1; i >= 0; i--)
		{
			DrawableObject* instance = Game::getInstance()->getObjectRef()->at(i);

			if (instance->getObjId() == objID)
			{
				Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
				Game::getInstance()->getObjectRef()->end();
			}
			//cout << "__________________________________________" << Game::getInstance()->getObjectRef()->size() << endl;
		}
	}
}