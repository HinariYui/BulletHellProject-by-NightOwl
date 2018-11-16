#pragma once

#include "MeshVbo.h"

class CustomMeshVbo : public MeshVbo {
protected:

public:
	static string const MESH_NAME;
	CustomMeshVbo();
	virtual string getMeshName();
	virtual void render();
	virtual void loadData();
};