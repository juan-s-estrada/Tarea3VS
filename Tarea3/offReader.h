#pragma once

#include "mesh.h"
#include <string>


class offReader
{
	Mesh mesh;


public:
	offReader(std::string fPath);
	~offReader();
};

