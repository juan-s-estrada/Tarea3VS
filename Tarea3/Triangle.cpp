#include "Triangle.h"


Triangle::Triangle(Vertices v0, Vertices  v1, Vertices v2)
{
	tVertices[0] = v0;
	tVertices[1] = v1;
	tVertices[2] = v2;
	CrossProduct(v0, v1);
	NormalVector();

}
void Triangle::NormalVector(){


	tNormalVector[0] = (tVertices[0].Vertex[0] + tVertices[1].Vertex[0]) * 0.5 + (tVertices[0].Vertex[0] + tVertices[2].Vertex[0])*0.5;
	tNormalVector[1] = (tVertices[0].Vertex[1] + tVertices[1].Vertex[1])* 0.5 + (tVertices[0].Vertex[1] + tVertices[2].Vertex[1])*0.5;
	tNormalVector[2] = (tVertices[0].Vertex[2] + tVertices[1].Vertex[2])* 0.5 + (tVertices[0].Vertex[2] + tVertices[2].Vertex[2])*0.5;
	
	tNormalVector[0] *= 0.5f;
	tNormalVector[1] *= 0.5f;
	tNormalVector[2] *= 0.5f;



}

void Triangle::CrossProduct(Vertices v0, Vertices v1){

	tNormal[0] = v0.Vertex[1] * v1.Vertex[2] - v0.Vertex[2] * v1.Vertex[1];
	tNormal[1] = -(v0.Vertex[0] * v1.Vertex[2] - v0.Vertex[2] * v1.Vertex[0]);
	tNormal[2] = v0.Vertex[0] * v1.Vertex[1] - v0.Vertex[1] * v1.Vertex[0];
	float norm = sqrt(tNormal[0] * tNormal[0] + tNormal[1] * tNormal[1] + tNormal[2] * tNormal[2]);
	tNormal[0] = tNormal[0] / norm;
	tNormal[1] = tNormal[1] / norm;
	tNormal[2] = tNormal[2] / norm;
}


Triangle::~Triangle()
{
}
