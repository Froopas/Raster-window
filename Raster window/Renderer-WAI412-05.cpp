#include "Renderer.h"
#include "ConstantBuffers.h"
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"

using namespace DirectX;

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::Initialize(int width, int height, HWND hWnd, bool fullscreen, float nearPlane, float farPLane) {

	InitializeDX(width, height, hWnd, fullscreen, nearPlane, farPLane);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	bd.ByteWidth = (sizeof(ConstantBufferNeverChanges) + 15 / 16 * 16);
	m_d3dDevice->CreateBuffer(&bd, nullptr, &m_constantBufferNeverChanges);

	bd.ByteWidth = (sizeof(ConstantBufferChangeOnResize) + 15) / 16 * 16;
	m_d3dDevice->CreateBuffer(&bd, nullptr, &m_constantBufferChangeOnResize);

	bd.ByteWidth = (sizeof(ConstantBufferChangesEveryFrame) + 15) / 16 * 16;
	m_d3dDevice->CreateBuffer(&bd, nullptr, &m_constantBufferChangesEveryFrame);

	bd.ByteWidth = (sizeof(ConstantBufferChangesEveryPrim) + 15) / 16 * 16;
	m_d3dDevice->CreateBuffer(&bd, nullptr, &m_constantBufferChangesEveryPrim);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));

	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = FLT_MAX;
	m_d3dDevice->CreateSamplerState(&sampDesc, &m_samplerLinear);

	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	ID3D10Blob* errorMessage;

	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;
	errorMessage = 0;

	HRESULT result;
	
	D3DCompileFromFile(L"VertexShader.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);

	D3DCompileFromFile(L"PixelShader.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);

	m_d3dDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	m_d3dDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);

	m_playerTexture = nullptr;

	CreateDDSTextureFromFile(m_d3dDevice,L"Seafloor.dds",nullptr,&m_playerTexture);

	unsigned int numLayout = sizeof(PNTVertexLayout) / sizeof(PNTVertexLayout[0]);

	result=m_d3dDevice->CreateInputLayout(PNTVertexLayout, numLayout, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_vertexLayout);

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;
	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;
}

void Renderer::Shutdown() {
	m_playerTexture->Release();
	m_cylinderTexture->Release();
	m_enemyTexture->Release();
	m_floorTexture->Release();
	m_wallsTexture->Release();
	m_constantBufferNeverChanges->Release();
	m_constantBufferChangeOnResize->Release();
	m_constantBufferChangesEveryFrame->Release();
	m_constantBufferChangesEveryPrim->Release();
	m_samplerLinear->Release();
	m_vertexShader->Release();
	m_vertexShaderFlat->Release();
	m_pixelShader->Release();
	m_pixelShaderFlat->Release();
	m_vertexLayout->Release();


}

void Renderer::CreateGameDeviceResources(Game* game) {
	m_game = game;

	ConstantBufferNeverChanges constantBufferNeverChanges;
	constantBufferNeverChanges.lightPosition[0] = XMFLOAT4(3.5f, 2.5f, 5.5f, 1.0f);
	constantBufferNeverChanges.lightPosition[1] = XMFLOAT4(3.5f, 2.5f, -5.5f, 1.0f);
	constantBufferNeverChanges.lightPosition[2] = XMFLOAT4(-3.5f, 2.5f, -5.5f, 1.0f);
	constantBufferNeverChanges.lightPosition[3] = XMFLOAT4(3.5f, 2.5f, 5.5f, 1.0f);
	constantBufferNeverChanges.lightColor = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	m_d3dContext->UpdateSubresource(m_constantBufferNeverChanges, 0, nullptr, &constantBufferNeverChanges, 0, 0);
	
	Material* playerMaterial = new Material(
		XMFLOAT4(0.8f, 0.8f, 0.8f, .5f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, .5f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		15.0f,
		m_playerTexture,
		m_vertexShader,
		m_pixelShader
	);

	Material* roomMaterial = new Material(
		XMFLOAT4(0.8f, 0.8f, 0.8f, .5f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, .5f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		15.0f,
		m_playerTexture,
		m_vertexShader,
		m_pixelShader
	);
	
	MeshObject* playerMesh = new PlayerMesh(m_d3dDevice);
	MeshObject* roomMesh = new RoomMesh(m_d3dDevice);

	auto objects = m_game->RenderObjects();

	for (auto object = objects.begin(); object != objects.end(); object++)
	{
		if (PlayerBlock* playerBlock = dynamic_cast<PlayerBlock*>(*object)) {
			playerBlock->Mesh(playerMesh);
			playerBlock->NormalMaterial(playerMaterial);
		}
		if (RoomBlock* roomBlock = dynamic_cast<RoomBlock*>(*object)) {
			roomBlock->Mesh(roomMesh);
			roomBlock->NormalMaterial(roomMaterial);
		}
	}


	m_game->GameCamera()->SetProjParams(
		XM_PI / 2,
		8.0f / 6.0f,
		0.01f,
		100.0f
	);
	XMStoreFloat4x4(&m_rotationTransform3D,
		XMMATRIX(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		)
	);

	ConstantBufferChangeOnResize changesOnResize;
	XMStoreFloat4x4(&changesOnResize.projection,
		XMMatrixMultiply(
			XMMatrixTranspose(m_game->GameCamera()->Projection()),
			XMMatrixTranspose(XMLoadFloat4x4(&m_rotationTransform3D))
		)
	);
	m_d3dContext->UpdateSubresource(m_constantBufferChangeOnResize, 0, nullptr, &changesOnResize, 0, 0);
	m_gameResourcesLoaded = true;

}

void Renderer::Render() {
	m_d3dContext->OMSetRenderTargets(1, &m_d3dRenderTargetView, m_d3dDepthStencilView);
	m_d3dContext->ClearDepthStencilView(m_d3dDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	const float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_d3dContext->ClearRenderTargetView(m_d3dRenderTargetView, ClearColor);

	if (m_game != nullptr)
	{
		// This section is only used after the game state has been initialized and all device
		// resources needed for the game have been created and associated with the game objects.

		// Update variables that change once per frame.
		ConstantBufferChangesEveryFrame constantBufferChangesEveryFrame;
		XMStoreFloat4x4(
			&constantBufferChangesEveryFrame.view,
			XMMatrixTranspose(m_game->GameCamera()->View())
		);

		m_d3dContext->UpdateSubresource(
			m_constantBufferChangesEveryFrame,
			0,
			nullptr,
			&constantBufferChangesEveryFrame,
			0,
			0
		);

		// Setup the graphics pipeline. This sample uses the same InputLayout and set of
		// constant buffers for all shaders, so they only need to be set once per frame.

		m_d3dContext->IASetInputLayout(m_vertexLayout);
		m_d3dContext->VSSetConstantBuffers(0, 1, &m_constantBufferNeverChanges);
		m_d3dContext->VSSetConstantBuffers(1, 1, &m_constantBufferChangeOnResize);
		m_d3dContext->VSSetConstantBuffers(2, 1, &m_constantBufferChangesEveryFrame);
		m_d3dContext->VSSetConstantBuffers(3, 1, &m_constantBufferChangesEveryPrim);

		m_d3dContext->PSSetConstantBuffers(2, 1, &m_constantBufferChangesEveryFrame);
		m_d3dContext->PSSetConstantBuffers(3, 1, &m_constantBufferChangesEveryPrim);
		m_d3dContext->PSSetSamplers(0, 1, &m_samplerLinear);

		//now walk through the render objects list and draw each object to screen
		auto objects = m_game->RenderObjects();
		for (auto object = objects.begin(); object != objects.end(); object++)
		{
			(*object)->Render(m_d3dContext, m_constantBufferChangesEveryPrim);
		}
	}

	Present();
}