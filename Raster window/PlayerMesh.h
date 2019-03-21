#pragma once

#include "Include.h"
#include "MeshObject.h"

class PlayerMesh : public MeshObject
{
public:
	PlayerMesh(ID3D11Device* device);
	~PlayerMesh();
};

