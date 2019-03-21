#pragma once

#include "Include.h"
#include "DDSTextureLoader.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

class DXBase
{
public:
	DXBase();
	~DXBase();

	bool InitializeDX(int, int, HWND, bool, float, float);
	void Shutdown();
	
	void Present();
	//void Render();

	ID3D11Device* GetDevice() { return m_d3dDevice; }
	ID3D11DeviceContext* GetDeviceContext() { return m_d3dContext; }

	int m_videoCardMemory;
	char m_videoCardDescription[128];

	ID3D11Device*				m_d3dDevice;
	ID3D11DeviceContext*		m_d3dContext;
	IDXGISwapChain*				m_swapChain;
	ID3D11RenderTargetView*		m_d3dRenderTargetView;
	ID3D11RenderTargetView*		m_d3dRenderTargetViewRight;
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11RasterizerState*		m_rasterState;
	ID3D11DepthStencilState*	m_depthStencilState;

	ID3D11DepthStencilView*		m_d3dDepthStencilView;

	D3D_FEATURE_LEVEL                               m_featureLevel;
	//Windows::Foundation::Size                       m_renderTargetSize;
	//Windows::Foundation::Rect                       m_windowBounds;
	float                                           m_dpi;
	//Windows::Graphics::Display::DisplayOrientations m_orientation;
	bool                                            m_windowSizeChangeInProgress;

	// Transforms used for display orientation.
	//D2D1::Matrix3x2F                                m_rotationTransform2D;
	DirectX::XMFLOAT4X4                             m_rotationTransform3D;
};

