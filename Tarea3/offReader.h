#pragma once

#include "mesh.h"
#include <string>
#include <GLFW/glfw3.h>

class offReader
{

public:
	Mesh mesh;

	std::vector<Vertices> BBox;
	std::vector<GLshort> indexData;
	std::vector<Vertices> vertexData;
	std::vector<GLfloat> fVertexData;
	offReader(std::string fPath);
	~offReader();
};

