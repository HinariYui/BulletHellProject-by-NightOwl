#pragma once
#include "stdafx.h"
#include "SquareMeshVbo.h"
#include "HexagonMeshVbo.h"
#include "CustomMeshVbo.h"
#include "CircleMeshVbo.h"
#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

enum Tag{Player, Enemy, pBullet, eBullet, Wall, BG};

class GameObject :public DrawableObject
{
protected:
	int hp = 10;
	GLuint vertexNum = 0;
	glm::vec3 color;
	glm::vec3 velocity;
	bool isCollide = false;
	Tag tag;

public:
	GameObject(Tag newTag);
	~GameObject();
	void setColor(float r, float g, float b);
	void render(glm::mat4 globalModelTransform);
	void update(float deltaTime);
	void setVelocity(glm::vec3 velocity);
	void addVelocity(glm::vec3 velocity);
	glm::vec3 getVelocity();
	bool checkCollision(GameObject* obj);
	Tag getTag() { return this->tag; };
	void resetVelocityX();
	void resetVelocityY();
	void resetVelocityZ();
};

