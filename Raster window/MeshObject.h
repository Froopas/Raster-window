#pragma once

#include "Include.h"
#include "ConstantBuffers.h"

class MeshObject
{
public:
	MeshObject();
	~MeshObject();
	void Render(ID3D11DeviceContext* context);

	ID3D11Buffer*	m_vertexBuffer;
	ID3D11Buffer*	m_indexBuffer;
	int				m_vertexCount;
	int				m_indexCount;

};

