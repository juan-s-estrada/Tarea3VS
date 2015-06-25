#include "offReader.h"
#include <fstream>
#include <iostream>

offReader::offReader(std::string fPath)
{

	std::string line;
	std::ifstream objF;

	
	float x, y, z;
	float minX=0, maxX=0, minY=0, maxY=0, minZ=0, maxZ=0;
	int numVertices, numFaces, numEdges, facexVerts,aux ;
	objF.open(fPath);
	if (!objF) std::cout << "Error al abrir el archivo, causa probable: nombre erroneo" << std::endl;

	objF >> line;

	if (line != "OFF") { std::cout << "Archivo no es .OFF	" << line << std::endl; return; }

	objF >> numVertices >> numFaces >> numEdges;
	
	std::cout << numVertices << numFaces << numEdges;

	for (int i = 0; i < numVertices; i++){
		objF >> x >> y >> z;
		if (x < minX) minX = x;
		if (x > maxX) maxX = x;
		if (y < minY) minY = y;
		if (y > maxY) maxY = y;
		if (z < minZ) minZ = z;
		if (z > maxZ) maxZ = z;
		vertexData.push_back(Vertices(x, y, z));
		fVertexData.push_back((GLfloat)x);
		fVertexData.push_back((GLfloat)y);
		fVertexData.push_back((GLfloat)z);

	}
	for (int z = 0; z < numFaces; z++){
		objF >> facexVerts;
		Face fs;
		std::vector <int> faceVerts;

		for (int inner = 0; inner < facexVerts; inner++) {
			objF >> aux;
			faceVerts.push_back(aux);
		}

		if (facexVerts > 3){
			//Triangularizar
			for (int indI = 1; indI < facexVerts - 1; indI++)
			{
				fs.Faces.push_back(Triangle(vertexData[faceVerts[0]], vertexData[faceVerts[indI]], vertexData[faceVerts[indI + 1]]));
				indexData.push_back((GLshort)faceVerts[0]);
				indexData.push_back((GLshort)faceVerts[indI]);
				indexData.push_back((GLshort)faceVerts[indI + 1]);
			}
		}
		else{
			fs.Faces.push_back(Triangle(vertexData[faceVerts[0]], vertexData[faceVerts[1]], vertexData[faceVerts[2]]));
			indexData.push_back((GLshort)faceVerts[0]);
			indexData.push_back((GLshort)faceVerts[1]);
			indexData.push_back((GLshort)faceVerts[2]);
			}

		
	mesh.Faces.push_back(fs);
	
	}
	 //--BBox Verticies--//
	BBox.push_back(Vertices(minX, maxY, minZ)); //v0
	BBox.push_back(Vertices(maxX, maxY, minZ)); //v1
	BBox.push_back(Vertices(maxX, minY, minZ)); //v2
	BBox.push_back(Vertices(minX, minY, minZ)); //v3
	BBox.push_back(Vertices(minX, maxY, maxZ)); //v4
	BBox.push_back(Vertices(maxX, maxY, maxZ)); //v5
	BBox.push_back(Vertices(maxX, minY, maxZ)); //v6
	BBox.push_back(Vertices(minX, minY, maxZ)); //v7
	
	
	
	objF.close();

}


offReader::~offReader()
{
}
