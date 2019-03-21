#include "Game.h"

using namespace DirectX;

Game::Game() {
}

Game::~Game() {
}

void Game::Initialize(Controller* controller, Renderer* renderer) {
	m_controller = controller;
	m_renderer = renderer;
	
	m_renderObjects = std::vector<GameObject*>();

	m_timer = new GameTimer();
	srand(time(NULL));
	m_timer->Start();

	m_player = new PlayerBlock();
	m_player->Position(XMFLOAT3(0.0f, 0.0f, 0.0f));

	m_renderObjects.push_back(m_player);

	m_room = new RoomBlock();

	m_renderObjects.push_back(m_room);
	
	m_camera = new Camera;
	m_camera->SetProjParams(XM_PI / 4, 800 / 600, 0.01f, 100.0f);
	m_camera->SetViewParams(
		XMFLOAT3(0, 3, -8),
		XMFLOAT3(0.0f, -1.0f, 0.0f),
		XMFLOAT3(0.0f, 1.0f, 0.0f)
	);

	m_controller->Pitch(m_camera->Pitch());
	m_controller->Yaw(m_camera->Yaw());
}

void Game::Shutdown() {
	delete m_player;
	delete m_room;

	delete m_timer;
	m_timer = nullptr;
	delete m_player;
	m_player = nullptr;
	delete m_camera;
	m_camera = nullptr;
}

GameState Game::RunGame() {
	m_timer->Update();

	//m_camera->LookDirection(m_controller->LookDirection());
	//m_controller->Pitch(m_camera->Pitch());
	//m_controller->Yaw(m_camera->Yaw());

	m_player->Velocity(m_controller->Velocity());

	UpdateDynamics();

	return GameState::Active;
}

void Game::UpdateDynamics() {
	float timeTotal = m_timer->PlayingTime();
	float timeFrame = m_timer->DeltaTime();

	float timeLeft = timeFrame;
	float deltaTime;
	while (timeLeft > 0.0f) {
		deltaTime = min(timeLeft, GameConstants::Physics::FrameLength);
		timeLeft -= deltaTime;

		m_player->Position(m_player->VectorPosition() + m_player->VectorVelocity()*deltaTime);
	}
}