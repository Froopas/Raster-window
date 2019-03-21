#pragma once

#include "Game.h"
#include "DXBase.h"
#include "Material.h"
#include "MeshObject.h"
#include "PlayerMesh.h"
#include "Include.h"
#include "PlayerBlock.h"
#include "RoomMesh.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

class Game;


class Renderer : public DXBase
{
public:
	Renderer();
	~Renderer();

	void Initialize(int, int, HWND, bool, float, float);
	void CreateGameDeviceResources(Game* game);

	void Shutdown();

	void Render();

private:
	bool                        m_initialized;
	bool                        m_gameResourcesLoaded;
	bool                        m_levelResourcesLoaded;
	//GameInfoOverlay^                                    m_gameInfoOverlay;
	//GameHud^                                            m_gameHud;
	Game*						m_game;

	ID3D11ShaderResourceView*   m_playerTexture;
	ID3D11ShaderResourceView*   m_cylinderTexture;
	ID3D11ShaderResourceView*   m_enemyTexture;
	ID3D11ShaderResourceView*   m_floorTexture;
	ID3D11ShaderResourceView*   m_wallsTexture;

	ID3D11Buffer*               m_constantBufferNeverChanges;
	ID3D11Buffer*               m_constantBufferChangeOnResize;
	ID3D11Buffer*               m_constantBufferChangesEveryFrame;
	ID3D11Buffer*               m_constantBufferChangesEveryPrim;
	ID3D11SamplerState*         m_samplerLinear;
	ID3D11VertexShader*         m_vertexShader;
	ID3D11VertexShader*         m_vertexShaderFlat;
	ID3D11PixelShader*          m_pixelShader;
	ID3D11PixelShader*          m_pixelShaderFlat;
	ID3D11InputLayout*          m_vertexLayout;
};

