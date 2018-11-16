#include "stdafx.h"
#include "DrawableObject.h"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

unsigned int DrawableObject::objNum = 0;

glm::mat4 DrawableObject::getTransform()
{
	glm::mat4 transform = glm::mat4(1.0);
	transform = glm::translate(transform, glm::vec3(pos.x, pos.y, 0));
	transform = glm::rotate(transform, angle * 3.14f / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(size.x, size.y, 1));
	return transform;
}

DrawableObject::DrawableObject()
{
	pos = glm::vec3(0.0, 0.0, 0.0);
	size = glm::vec3(1.0, 1.0, 1.0);
	angle = 0;

	objID = objNum;
	objNum++;
}


DrawableObject::~DrawableObject()
{
}

void DrawableObject::setSize(float sizeX, float sizeY)
{
	size = glm::vec3(sizeX, sizeY, 1);
}

void DrawableObject::setRotation(float newAngle)
{
	angle = newAngle;
}

void DrawableObject::setPosition(glm::vec3 newPosition)
{
	pos = newPosition;
}

glm::vec3 DrawableObject::getPosition()
{
	return pos;
}

void DrawableObject::translate(glm::vec3 moveDistance)
{
	pos = pos + moveDistance;
}

glm::vec3 DrawableObject::getSize()
{
	return size;
}

unsigned int DrawableObject::getObjId()
{
	return objID;
}

