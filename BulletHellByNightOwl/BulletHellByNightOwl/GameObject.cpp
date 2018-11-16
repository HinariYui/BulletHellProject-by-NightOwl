#include "GameObject.h"

GameObject::GameObject(Tag newTag)
{
	color = glm::vec3(0.0, 0.0, 0.0);
	tag = newTag;
	if (tag == Tag::pBullet)
	{
		setVelocity(glm::vec3(0, 8, 0));
	}

	Game*  g = Game::getInstance();
	GLuint objNum = g->getObjectRef()->size();
	GameObject* obj = NULL;

	for (int i = objNum - 1; i >= 0; i--)
	{
		obj = dynamic_cast<GameObject*>(g->getObjectRef()->at(i));

		if (this->getTag() != obj->getTag())
		{
			bool b = this->checkCollision(obj);
			//cout << "                           " << b << "    " << endl; //i << endl;
		}

	}
	
}


GameObject::~GameObject()
{
}

void GameObject::setColor(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}

void GameObject::render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo *squareMesh = dynamic_cast<SquareMeshVbo*> (Game::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));

	MeshVbo * mesh = NULL;

	GLuint modelMatixId = Game::getInstance()->getRenderer()->getModelMatrixAttrId();
	GLuint colorId = Game::getInstance()->getRenderer()->getColorUniformId();
	GLuint modeId = Game::getInstance()->getRenderer()->getModeUniformId();


	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (colorId == -1) {
		cout << "Error: Can't set color " << endl;
		return;
	}
	vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {
	
		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, color.x, color.y, color.z);
		glUniform1i(modeId, 0);
		squareMesh->render();
	}
	
}

void GameObject::update(float deltaTime)
{
	this->translate(velocity * glm::vec3(3, 3, 3));

	if (hp < 1)
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

void GameObject::setVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

void GameObject::addVelocity(glm::vec3 velocity)
{
	velocity = glm::normalize(velocity);
	this->velocity += velocity;
	if (this->velocity != glm::vec3(0, 0, 0))
	{
		this->velocity = glm::normalize(this->velocity);
	}
}

glm::vec3 GameObject::getVelocity()
{
	return this->velocity;
}

bool GameObject::checkCollision(GameObject* obj)
{
	glm::vec3 center = getPosition();//this object
	glm::vec3 size = getSize();
	GLfloat minX = center.x - (size.x*0.5);
	GLfloat maxX = center.x + (size.x*0.5);
	GLfloat minY = center.y - (size.y*0.5);
	GLfloat maxY = center.y + (size.y*0.5);

	glm::vec3 objPos = obj->getPosition();//others object
	glm::vec3 objSize = obj->getSize();
	GLfloat objMinX = objPos.x - (objSize.x*0.5);
	GLfloat objMaxX = objPos.x + (objSize.x*0.5);
	GLfloat objMinY = objPos.y - (objSize.y*0.5);
	GLfloat objMaxY = objPos.y + (objSize.y*0.5);

		
	if (maxX < objMinX || minX > objMaxX)
	{
		isCollide = false;
		return false;
	}
	if (maxY < objMinY || minY > objMaxY)
	{
		isCollide = false;
		return false;
	}
	// Overlapping on all axes means AABBs are intersecting

	

	if (this->tag == pBullet && obj->tag == Enemy)
	{
		isCollide = true;
		if(obj->isCollide == false)
		{
			cout << obj->hp << endl;
			(obj->hp)--;
			cout << obj->hp << endl;
		}
		

		
		

		//EnemyHP--
		//cout << endl;	
		//cout << endl;
		//cout << endl;
		//cout << "                    " << "HIT" << endl;
		//cout << endl;
		//cout << endl;
		//cout << endl;

		//cout << ".........................................."<<Game::getInstance()->getObjectRef()->size() << endl;

		for (int i = Game::getInstance()->getObjectRef()->size()-1; i >= 0; i--)
		{
			DrawableObject* instance = Game::getInstance()->getObjectRef()->at(i);

			if (instance->getObjId() == this->objID)
			{
				Game::getInstance()->getObjectRef()->erase(Game::getInstance()->getObjectRef()->begin() + i);
				Game::getInstance()->getObjectRef()->end();
			}
			//cout << "__________________________________________" << Game::getInstance()->getObjectRef()->size() << endl;

		}

	}

	return true;
}

void GameObject::resetVelocityX()
{
	this->velocity.x = 0;
}

void GameObject::resetVelocityY()
{
	this->velocity.y = 0;
}

void GameObject::resetVelocityZ()
{
	this->velocity.z = 0;
}


