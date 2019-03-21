#include "GameObject.h"

using namespace DirectX;

GameObject::GameObject() :
	m_normalMaterial(nullptr)
{
	m_ground = true;

	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_defaultXAxis = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_defaultYAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_defaultZAxis = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMStoreFloat4x4(&m_modelMatrix, XMMatrixIdentity());
}

GameObject::~GameObject()
{
}

void GameObject::Render(ID3D11DeviceContext *context, ID3D11Buffer *primitiveConstantBuffer
)
{
	if ((m_mesh == nullptr) || (m_normalMaterial == nullptr))
	{
		return;
	}

	ConstantBufferChangesEveryPrim constantBuffer;

	XMStoreFloat4x4(
		&constantBuffer.worldMatrix,
		XMMatrixTranspose(ModelMatrix())
	);


	m_normalMaterial->RenderSetup(context, &constantBuffer);

	context->UpdateSubresource(primitiveConstantBuffer, 0, nullptr, &constantBuffer, 0, 0);

	m_mesh->Render(context);
}