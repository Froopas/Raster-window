#include "RoomBlock.h"

using namespace DirectX;

RoomBlock::RoomBlock() {
	Initialize(XMFLOAT3(0,2.5f, 0));
}

RoomBlock::RoomBlock(DirectX::XMFLOAT3 position) {
	Initialize(position);
}

RoomBlock::~RoomBlock() {
}

void RoomBlock::Initialize(DirectX::XMFLOAT3 position) {
	Position(position);
	XMMATRIX mat1 = XMMatrixIdentity();
	XMStoreFloat4x4(&m_rotationMatrix, mat1);
}

void RoomBlock::UpdatePosition() {
	XMStoreFloat4x4(&m_modelMatrix, XMMatrixScaling(1.0f, 1.0f, 1.0f) *	XMLoadFloat4x4(&m_rotationMatrix) *	XMMatrixTranslation(m_position.x, m_position.y, m_position.z));
}