#pragma once
#include "Vertices.h"

class Triangle
{
	Vertices tVertices[3]; //x,y,z
	float tNormal[3];


public:
	void CrossProduct(Vertices v0, Vertices v1);
	Triangle(Vertices v0, Vertices  v1, Vertices v2);
	~Triangle();
};

