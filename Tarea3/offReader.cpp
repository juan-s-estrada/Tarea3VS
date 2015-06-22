#include "offReader.h"
#include <fstream>
#include <iostream>

offReader::offReader(std::string fPath)
{

	std::string line;
	std::ifstream objF;
	std::vector<Vertices> vertexData;
	std::vector<int> indexData;
	
	float x, y, z;
	int numVertices, numFaces, numEdges, facexVerts,aux ;
	objF.open(fPath);
	if (!objF) std::cout << "Error al abrir el archivo, causa probable: nombre erroneo" << std::endl;

	objF >> line;

	if (line != "OFF ") { std::cout << "Archivo no es .OFF" << std::endl; return; }

	objF >> numVertices >> numFaces >> numEdges;
	
	for (int i = 0; i < numVertices; i++){
		objF >> x >> y >> z;
		vertexData.push_back(Vertices(x, y, z));
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
				fs.Face.push_back(Triangle(vertexData[faceVerts[0]], vertexData[faceVerts[indI]], vertexData[faceVerts[indI + 1]]));
				indexData.push_back(faceVerts[0]);
				indexData.push_back(faceVerts[indI]);
				indexData.push_back(faceVerts[indI + 1]);
			}
		}
		else{
			fs.Face.push_back(Triangle(vertexData[faceVerts[0]], vertexData[faceVerts[1]], vertexData[faceVerts[2]]));
			indexData.push_back(faceVerts[0]);
			indexData.push_back(faceVerts[1]);
			indexData.push_back(faceVerts[2]);
			}

	mesh.Faces.push_back(fs);
	
	}
	
	if (objF.eof()) std::cout << "Todo bien" << std::endl;
	objF.close();

}


offReader::~offReader()
{
}
