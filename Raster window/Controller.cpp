#include "Controller.h"

#include <Winuser.h>
#include <DirectXMath.h>

#define MOVEMENT_GAIN 2.0f

Controller::Controller() {
	ResetState();

	m_pitch = 0.0f;
	m_yaw = 0.0f;
}

Controller::~Controller() {
}

bool Controller::IsPauseRequested() {
	switch (m_state) {
	case MoveLookControllerState::Active:
		if (m_pausePressed) {
			m_pausePressed = false;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool Controller::IsPressComplete() {
	switch (m_state) {
	case MoveLookControllerState::WaitForInput:
		if (m_buttonPressed) {
			m_buttonPressed = false;
			return true;
		}
		else {
			return false;
		}
		break;
	}
	return false;
}

void Controller::OnKeyDown(int wParam) {
	switch (wParam) {
	case 87:
		m_forward = true;
		break;
	case 83:
		m_back = true;
		break;
	case 65:
		m_left = true;
		break;
	case 68:
		m_right = true;
		break;
	}	
}

void Controller::OnKeyUp(int wParam) {
	switch (wParam) {
	case 87:
		m_forward = false;
		break;
	case 83:
		m_back = false;
		break;
	case 65:
		m_left = false;
		break;
	case 68:
		m_right = false;
		break;
	}
}

void Controller::ResetState() {
	// Reset the state of the controller.
	// Disable any active pointer IDs to stop all interaction.
	m_buttonPressed = false;
	m_pausePressed = false;
	m_buttonInUse = false;
	m_moveInUse = false;
	m_mouseInUse = false;
	m_mouseLeftInUse = false;
	m_mouseRightInUse = false;
	m_velocity = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_moveCommand = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_forward = false;
	m_back = false;
	m_left = false;
	m_right = false;
	m_up = false;
	m_down = false;
	m_pause = false;
}

DirectX::XMFLOAT3 Controller::Velocity() {
	return m_velocity;
}

DirectX::XMFLOAT3 Controller::LookDirection() {
	DirectX::XMFLOAT3 lookdirection;

	float r = cosf(m_pitch);
	lookdirection.y = sinf(m_pitch);
	lookdirection.z = r*cosf(m_yaw);
	lookdirection.x = r*sinf(m_yaw);

	return lookdirection;
}

float Controller::Pitch() {
	return m_pitch;
}

void Controller::Pitch(float pitch) {
	m_pitch = pitch;
}

float Controller::Yaw() {
	return m_yaw;
}

void Controller::Yaw(float yaw) {
	m_yaw = yaw;
}

void Controller::Update() {
	if (m_forward) {
		m_moveCommand.y += 1.0f;
	}
	if (m_back) {
		m_moveCommand.y -= 1.0f;
	}
	if (m_left) {
		m_moveCommand.x += 1.0f;
	}
	if (m_right) {
		m_moveCommand.x -= 1.0f;
	}

	if (fabsf(m_moveCommand.x) > 0.1f ||
		fabsf(m_moveCommand.y) > 0.1f ||
		fabsf(m_moveCommand.z) > 0.1f)
	{
		XMStoreFloat3(&m_moveCommand, DirectX::XMVector3Normalize(XMLoadFloat3(&m_moveCommand)));
	}

	// Rotate command to align with our direction (world coordinates).
	DirectX::XMFLOAT3 wCommand;
	wCommand.x = m_moveCommand.x * cosf(m_yaw) - m_moveCommand.y * sinf(m_yaw);
	wCommand.y = m_moveCommand.x * sinf(m_yaw) + m_moveCommand.y * cosf(m_yaw);
	wCommand.z = m_moveCommand.z;

	// Scale for sensitivity adjustment.
	// Our velocity is based on the command. Y is up.
	m_velocity.x = -wCommand.x * MOVEMENT_GAIN;
	m_velocity.z = wCommand.y * MOVEMENT_GAIN;
	m_velocity.y = wCommand.z * MOVEMENT_GAIN;

	m_moveCommand = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}