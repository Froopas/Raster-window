#include "MeshObject.h"



MeshObject::MeshObject()
{
}

MeshObject::~MeshObject()
{
}

void MeshObject::Render(ID3D11DeviceContext* context) {
	unsigned int stride = sizeof(PNTVertex);
	unsigned int offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->DrawIndexed(m_indexCount, 0, 0);
}