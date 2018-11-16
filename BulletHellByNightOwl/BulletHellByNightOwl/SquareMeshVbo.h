#pragma once

#include "MeshVbo.h"

class SquareMeshVbo : public MeshVbo {
protected:

	const GLuint vertexNum = 4;

	//GLfloat* vertexData = NULL;

public:
	static string const MESH_NAME;
	SquareMeshVbo();
	virtual string getMeshName();
	virtual void render();
	virtual void loadData();
	void adjustTexcoord(float * uv);
	//GLfloat* getVertexData();
};