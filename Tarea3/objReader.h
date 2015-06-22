#pragma once

#include <string>
#include "mesh.h"

class objReader
{
	Mesh mesh;


public:

	objReader(std::string fpath);
	~objReader();
};

