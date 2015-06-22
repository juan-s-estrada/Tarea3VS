#include "Triangle.h"


Triangle::Triangle(Vertices v0, Vertices  v1, Vertices v2)
{
	tVertices[0] = v0;
	tVertices[1] = v1;
	tVertices[2] = v2;
	CrossProduct(v0, v1);

}

void Triangle::CrossProduct(Vertices v0, Vertices v1){

	tNormal[0] = v0.Vertex[1] * v1.Vertex[2] - v0.Vertex[2] * v1.Vertex[1];
	tNormal[1] = -(v0.Vertex[0] * v1.Vertex[2] - v0.Vertex[2] * v1.Vertex[0]);
	tNormal[2] = v0.Vertex[0] * v1.Vertex[1] - v0.Vertex[1] * v1.Vertex[0];

}


Triangle::~Triangle()
{
}
