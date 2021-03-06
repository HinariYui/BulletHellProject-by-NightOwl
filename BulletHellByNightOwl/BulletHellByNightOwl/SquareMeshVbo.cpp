#include "stdafx.h"
#include "SquareMeshVbo.h"

string const SquareMeshVbo::MESH_NAME = "square";

void SquareMeshVbo::loadData()
{
	////VBO data
	//vertexData = new GLfloat[2 * 4];

	//vertexData[0] = -0.5f; vertexData[1] = -0.5f;
	//vertexData[2] = 0.5; vertexData[3] = -0.5f;
	//vertexData[4] = 0.5; vertexData[5] = 0.5;
	//vertexData[6] = -0.5f; vertexData[7] = 0.5;

	GLfloat vertexData[] =
	{
	  -0.5f, -0.5f,
	  0.5f, -0.5f,
	  0.5f,  0.5f,
	  -0.5f,  0.5f
	};

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
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->texVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), texData, GL_STATIC_DRAW);


}

SquareMeshVbo::SquareMeshVbo()
{
}

string SquareMeshVbo::getMeshName()
{
	return MESH_NAME;
}

void SquareMeshVbo::render()
{
	if (this->posAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
		glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	if (this->texAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
		glVertexAttribPointer(this->texAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	glDrawArrays(GL_POLYGON, 0, 4);
}

void SquareMeshVbo::adjustTexcoord(float * uv)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), uv, GL_STATIC_DRAW);
}

//GLfloat* SquareMeshVbo::getVertexData()
//{
//	return vertexData;
//}
void SquareMeshVbo::resetTexcoord()
{
	GLfloat texData[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), texData, GL_STATIC_DRAW);
}


