#pragma once

#include "Include.h"
#include "GameObject.h"

class RoomBlock : public GameObject
{
public:
	RoomBlock();
	RoomBlock(DirectX::XMFLOAT3 position);
	~RoomBlock();
	void Initialize(DirectX::XMFLOAT3 position);
	void UpdatePosition() override;

private:
	DirectX::XMFLOAT4X4 m_rotationMatrix;
	float m_angle;
};

