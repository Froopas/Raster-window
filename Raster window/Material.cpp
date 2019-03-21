#include "Material.h"

using namespace DirectX;

Material::Material()
{
}

Material::~Material()
{
}

Material::Material(
	XMFLOAT4 meshColor,
	XMFLOAT4 diffuseColor,
	XMFLOAT4 specularColor,
	float specularExponent,
	_In_ ID3D11ShaderResourceView* textureResourceView,
	_In_ ID3D11VertexShader* vertexShader,
	_In_ ID3D11PixelShader* pixelShader
)
{
	m_meshColor = meshColor;
	m_diffuseColor = diffuseColor;
	m_specularColor = specularColor;
	m_specularExponent = specularExponent;

	m_vertexShader = vertexShader;
	m_pixelShader = pixelShader;
	m_textureRV = textureResourceView;
}

void Material::RenderSetup(
	_In_ ID3D11DeviceContext* context,
	_Inout_ ConstantBufferChangesEveryPrim* constantBuffer
)
{
	constantBuffer->meshColor = m_meshColor;
	constantBuffer->specularColor = m_specularColor;
	constantBuffer->specularPower = m_specularExponent;
	constantBuffer->diffuseColor = m_diffuseColor;

	context->PSSetShaderResources(0, 1, &m_textureRV);
	context->VSSetShader(m_vertexShader, nullptr, 0);
	context->PSSetShader(m_pixelShader, nullptr, 0);
}