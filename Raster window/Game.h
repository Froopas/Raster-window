#pragma once

#include <vector>

#include "Controller.h"
#include "Camera.h"
#include "GameObject.h"
#include "GameTimer.h"
#include "GameConstants.h"
#include "Renderer.h"
#include "RoomBlock.h"
#include "Include.h"

#include <time.h>

class Renderer;
class GameTimer;
class Controller;
class PlayerBlock;

enum class GameState
{
	Waiting,
	Active,
	PlayerLost,
	GameComplete,
};

class Game
{
public:
	Game();
	~Game();

	void Initialize(Controller*, Renderer*);

	GameState RunGame();

	void Shutdown();


	bool IsActivePlay() { return m_timer->Active(); }
	int RoundTime() { return m_timer->PlayingTime(); }

	bool GameActive() { return m_gameActive; }

	Camera* GameCamera() { return m_camera; }
	std::vector<GameObject*> RenderObjects() { return m_renderObjects; }

private:
	void UpdateDynamics();

	Controller*									m_controller;
	Renderer*									m_renderer;
	Camera*                                     m_camera;

	GameTimer*                                  m_timer;
	bool                                        m_gameActive;

	PlayerBlock*                                m_player;
	RoomBlock*									m_room;
	//AISumoBlock^								m_enemy;
	std::vector<GameObject*>                    m_renderObjects;

};

