#pragma once

#include "Include.h"
#include "ConstantBuffers.h"

class Material
{
public:
	Material();
	~Material();

	Material(
		DirectX::XMFLOAT4 meshColor,
		DirectX::XMFLOAT4 diffuseColor,
		DirectX::XMFLOAT4 specularColor,
		float specularExponent,
		_In_ ID3D11ShaderResourceView* textureResourceView,
		_In_ ID3D11VertexShader* vertexShader,
		_In_ ID3D11PixelShader* pixelShader
	);

	void RenderSetup(
		_In_ ID3D11DeviceContext* context,
		_Inout_ ConstantBufferChangesEveryPrim* constantBuffer
	);

	void SetTexture(_In_ ID3D11ShaderResourceView* textureResourceView)
	{
		m_textureRV = textureResourceView;
	}

private:
	DirectX::XMFLOAT4   m_meshColor;
	DirectX::XMFLOAT4   m_diffuseColor;
	DirectX::XMFLOAT4   m_hitColor;
	DirectX::XMFLOAT4   m_specularColor;
	float               m_specularExponent;

	ID3D11VertexShader*       m_vertexShader;
	ID3D11PixelShader*        m_pixelShader;
	ID3D11ShaderResourceView* m_textureRV;
};

