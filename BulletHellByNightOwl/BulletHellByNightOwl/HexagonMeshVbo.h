#pragma once

#include "MeshVbo.h"

class HexagonMeshVbo : public MeshVbo {
protected:

public:
	static string const MESH_NAME;
	HexagonMeshVbo();
	virtual string getMeshName();
	virtual void render();
	virtual void loadData();
};