#pragma once
#include "GameObject.h"
#include "Include.h"

class PlayerBlock : public GameObject
{
public:
	PlayerBlock();
	PlayerBlock(DirectX::XMFLOAT3 position);
	~PlayerBlock();
	void Initialize(DirectX::XMFLOAT3 position);
	void UpdatePosition() override;

private:
	DirectX::XMFLOAT4X4 m_rotationMatrix;
	float m_angle;
};

