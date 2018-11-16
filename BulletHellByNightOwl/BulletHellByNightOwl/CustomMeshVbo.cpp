#include "stdafx.h"
#include "CustomMeshVbo.h"

string const CustomMeshVbo::MESH_NAME = "square";

void CustomMeshVbo::loadData()
{
	//VBO data
	GLfloat vertexData[] =
	{
		-1.5f,   0.0f,
		-1.25f, -0.43f,
		-0.75f, -0.43f,
		-0.5f,   0.0f,
		-0.75f,  0.43f,
		-1.25f,  0.43f,
		-0.5f,  -0.5f,
		 0.5f,  -0.5f,
		 0.5f,   0.5f,
		-0.5f,   0.5f,
		 0.5f,   0.0f,
		 0.75f, -0.43f,
		 1.25f, -0.43f,
		 1.5f,   0.0f,
		 1.25f,  0.43f,
		 0.75f,  0.43f,
	};

	GLfloat texData[] =
	{
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f
	};

	//Create VBO
	glGenBuffers(1, &(this->posVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 16 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->texVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
	glBufferData(GL_ARRAY_BUFFER, 3 * 16 * sizeof(GLfloat), texData, GL_STATIC_DRAW);


}

CustomMeshVbo::CustomMeshVbo()
{
}

string CustomMeshVbo::getMeshName()
{
	return MESH_NAME;
}

void CustomMeshVbo::render()
{
	if (this->posAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
		glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	if (this->texAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
		glVertexAttribPointer(this->texAttribId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 10, 6);
}