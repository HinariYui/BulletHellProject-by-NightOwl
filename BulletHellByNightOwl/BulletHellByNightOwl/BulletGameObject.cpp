#include "BulletGameObject.h"

unsigned int BulletGameObject::bulletNum = 0;

BulletGameObject::~BulletGameObject()
{
	bulletNum--;
}

void BulletGameObject::update(float deltaTime)
{
	translate(getVelocity() * 1.0f);

	float halfSizeX = (size.x * 0.5f)+4;
	float halfSizeY = (size.y * 0.5f)+4;

	if ((pos.x > 122+halfSizeX) || (pos.x < -378-halfSizeX) || (pos.y > 330+halfSizeY) || (pos.y < -330-halfSizeY))
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

	Game*  g = Game::getInstance();
	GLuint objNum = g->getObjectRef()->size();
	GameObject* obj = NULL;

	//left border(-509+131=-378, 0, 0)
	//right border(381-259=122, 0, 0)
	//top border(0, 345-15=330, 0)
	//bottom border(0,-345+15=-330, 0)

	for (int i = objNum -1; i >= 0; i--)
	{
		obj = dynamic_cast<GameObject*>(g->getObjectRef()->at(i));

		if (this->getTag() != obj->getTag())
		{
			bool b = this->checkCollision(obj);
			//cout << "                           " << b << "    " << endl; //i << endl;
		}

	}
}