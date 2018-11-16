#pragma once

#include "MeshVbo.h"

class CircleMeshVbo : public MeshVbo {
protected:

public:
	static string const MESH_NAME;
	CircleMeshVbo();
	virtual string getMeshName();
	virtual void render();
	virtual void loadData();
};