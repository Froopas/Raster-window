#include "RoomMesh.h"

using namespace DirectX;

RoomMesh::RoomMesh(ID3D11Device* device) {
	D3D11_BUFFER_DESC bd = { 0 };
	D3D11_SUBRESOURCE_DATA initData = { 0 };

	PNTVertex playerVertices[] = {
		{ XMFLOAT3(-5.0f, -5.0f, -5.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.63f, 0.005f) },
		{ XMFLOAT3(-5.0f, -5.0f, 5.0f), XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.99f, 0.005f) },
		{ XMFLOAT3(-5.0f, 5.0f, -5.0f), XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.6345f, 0.01f) },
		{ XMFLOAT3(-5.0f, 5.0f, 5.0f), XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(0.99f, 0.01f) },
		{ XMFLOAT3(5.0f, -5.0f, -5.0f), XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.6f, 0.36f) },
		{ XMFLOAT3(5.0f, -5.0f, 5.0f), XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.99f, 0.36f) },
		{ XMFLOAT3(5.0f, 5.0f, -5.0f), XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.6345f, 0.3655f) },
		{ XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.3655f) }
	};

	WORD playerIndices[] = {
		2, 1, 0, // -x
		2, 3, 1,

		5, 6, 4, // +x
		7, 6, 5,

		1, 5, 0, // -y
		5, 4, 0,

		6, 7, 2, // +y
		7, 3, 2,

		4, 6, 0, // -z
		6, 2, 0,

		3, 7, 1, // +z
		7, 5, 1
	};

	m_vertexCount = 8;
	m_indexCount = ARRAYSIZE(playerIndices);

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PNTVertex)* m_vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	initData.pSysMem = playerVertices;
	device->CreateBuffer(&bd, &initData, &m_vertexBuffer);

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD)* m_indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	initData.pSysMem = playerIndices;
	device->CreateBuffer(&bd, &initData, &m_indexBuffer);
}


RoomMesh::~RoomMesh()
{
}
