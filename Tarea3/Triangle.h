#pragma once
#include "Vertices.h"

class Triangle
{
	Vertices tVertices[3];
	float tNormal[3];


public:
	Triangle(Vertices v0, Vertices  v1, Vertices v2);
	~Triangle();
};

