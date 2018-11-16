#pragma once
#include "glm.hpp"
#include <vector>

using namespace std;

class DrawableObject
{
protected:

	static unsigned int objNum;
	unsigned int objID;
	glm::vec3 pos;
	glm::vec3 size;
	float angle;

public:
	glm::mat4 getTransform();

	DrawableObject();
	~DrawableObject();
	virtual void render(glm::mat4 globalModelTransform) = 0;
	virtual void update(float deltaTime) = 0;
	void setSize(float sizeX, float sizeY);
	void setRotation(float newAngle);
	void setPosition(glm::vec3 newPosition);
	glm::vec3 getPosition();
	glm::vec3 getSize();
	void translate(glm::vec3 moveDistance);
	unsigned int getObjId();

	//Rotate, Scale ???

};

