#pragma once

#include "SampleDX.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "systemclass.h"

enum class MoveLookControllerState {
	None,
	WaitForInput,
	Active,
};

class Controller
{
public:
	Controller();
	~Controller();

	void Update();
	bool IsPressComplete();
	bool IsPauseRequested();

	void OnKeyDown(int);
	void OnKeyUp(int);

	DirectX::XMFLOAT3 Velocity();
	DirectX::XMFLOAT3 LookDirection();
	float Pitch();
	void  Pitch(_In_ float pitch);
	float Yaw();
	void  Yaw(_In_ float yaw);

private:
	// Properties of the controller object.
	MoveLookControllerState     m_state;
	DirectX::XMFLOAT3           m_velocity;             // How far we move in this frame.
	float                       m_pitch;
	float                       m_yaw;      // Orientation euler angles in radians.

	// Properties of the Move control.
	DirectX::XMFLOAT2           m_moveUpperLeft;        // Bounding box where this control will activate.
	DirectX::XMFLOAT2           m_moveLowerRight;
	bool                        m_moveInUse;            // The move control is in use.
	//uint32                      m_movePointerID;        // Id of the pointer in this control.
	DirectX::XMFLOAT2           m_moveFirstDown;        // Point where initial contact occurred.
	DirectX::XMFLOAT2           m_movePointerPosition;  // Point where the move pointer is currently located.
	DirectX::XMFLOAT3           m_moveCommand;

	bool                        m_mouseInUse;
	//uint32                      m_mousePointerID;
	DirectX::XMFLOAT2           m_mouseLastPoint;
	bool                        m_mouseLeftInUse;
	bool                        m_mouseRightInUse;

	bool                        m_buttonInUse;
	//uint32                      m_buttonPointerID;
	DirectX::XMFLOAT2           m_buttonUpperLeft;
	DirectX::XMFLOAT2           m_buttonLowerRight;
	bool                        m_buttonPressed;
	bool                        m_pausePressed;

	// Input states for Keyboard.
	bool                        m_forward;
	bool                        m_back;                    // States for movement.
	bool                        m_left;
	bool                        m_right;
	bool                        m_up;
	bool                        m_down;
	bool                        m_pause;

	void     ResetState();
};

