#pragma once

#include "Include.h"
#include "MeshObject.h"

class RoomMesh : public MeshObject
{
public:
	RoomMesh(ID3D11Device* device);
	~RoomMesh();
};

