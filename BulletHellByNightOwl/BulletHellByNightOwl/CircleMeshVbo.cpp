#include "stdafx.h"
#include "CircleMeshVbo.h"

string const CircleMeshVbo::MESH_NAME = "circle";

void CircleMeshVbo::loadData()
{
	//VBO data
	GLfloat theta = 3.14159265358979323 / 180.0f;
	GLfloat * vertexData = new GLfloat[2 * 362];

	vertexData[0] = 0;
	vertexData[1] = 0;
	for (int i = 0; i < 362; i++)
	{
		vertexData[i * 2 + 2] = cos(theta * i);
		vertexData[i * 2 + 3] = sin(theta * i);
	}

	GLfloat texData[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	//Create VBO
	glGenBuffers(1, &(this->posVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 362 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->texVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(GLfloat), texData, GL_STATIC_DRAW);


}

CircleMeshVbo::CircleMeshVbo()
{
}

string CircleMeshVbo::getMeshName()
{
	return MESH_NAME;
}

void CircleMeshVbo::render()
{
	if (this->posAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
		glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	if (this->texAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
		glVertexAttribPointer(this->texAttribId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	}
	glDrawArrays(GL_TRIANGLE_FAN, 1, 361);
}