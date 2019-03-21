#include "PlayerBlock.h"

using namespace DirectX;

PlayerBlock::PlayerBlock() {
	Initialize(XMFLOAT3(0, 0, 0));
}

PlayerBlock::PlayerBlock(DirectX::XMFLOAT3 position) {
	Initialize(position);
}

PlayerBlock::~PlayerBlock() {
}

void PlayerBlock::Initialize(DirectX::XMFLOAT3 position) {
	Position(position);
	XMMATRIX mat1 = XMMatrixIdentity();
	XMStoreFloat4x4(&m_rotationMatrix, mat1);
}

void PlayerBlock::UpdatePosition() {
	XMStoreFloat4x4(&m_modelMatrix, XMMatrixScaling(1.0f, 1.0f, 1.0f) *	XMLoadFloat4x4(&m_rotationMatrix) *	XMMatrixTranslation(m_position.x, m_position.y, m_position.z));
}