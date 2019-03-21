#include "Camera.h"

using namespace DirectX;

Camera::Camera() {
	SetViewParams(
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 1.0f),
		XMFLOAT3(0.0f, 1.0f, 0.0f)
	);

	SetProjParams(XM_PI / 4, 1.0f, 1.0f, 1000.0f);
}

Camera::~Camera() {
}

void Camera::LookDirection(XMFLOAT3 lookdirection) {
	XMFLOAT3 lookat;
	lookat.x = m_eye.x + lookdirection.x;
	lookat.y = m_eye.y + lookdirection.y;
	lookat.z = m_eye.z + lookdirection.z;

	SetViewParams(m_eye, lookat, m_up);
}

void Camera::Eye(XMFLOAT3 eye) {
	SetViewParams(eye, m_lookAt, m_up);
}

void Camera::SetViewParams(XMFLOAT3 eye, XMFLOAT3 lookAt, XMFLOAT3 up) {
	m_eye = eye;
	m_lookAt = lookAt;
	m_up = up;

	XMMATRIX view = XMMatrixLookAtLH(
		XMLoadFloat3(&m_eye),
		XMLoadFloat3(&m_lookAt),
		XMLoadFloat3(&m_up)
	);

	XMVECTOR det;
	XMMATRIX inverseView = XMMatrixInverse(&det, view);
	XMStoreFloat4x4(&m_viewMatrix, view);
	XMStoreFloat4x4(&m_inverseView, inverseView);

	XMFLOAT3 zBasis;
	XMStoreFloat3(&zBasis, inverseView.r[2]);

	m_cameraYawAngle = atan2f(zBasis.x, zBasis.z);

	float len = sqrtf(zBasis.z * zBasis.z + zBasis.x * zBasis.x);
	m_cameraPitchAngle = atan2f(zBasis.y, len);
}

void Camera::SetProjParams(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
	m_fieldOfView = fieldOfView;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;
	XMStoreFloat4x4(
		&m_projectionMatrix,
		XMMatrixPerspectiveFovLH(
			m_fieldOfView,
			m_aspectRatio,
			m_nearPlane,
			m_farPlane
		)
	);
}

XMMATRIX Camera::View() {
	return XMLoadFloat4x4(&m_viewMatrix);
}

XMMATRIX Camera::Projection() {
	return XMLoadFloat4x4(&m_projectionMatrix);
}

XMMATRIX Camera::World() {
	return XMLoadFloat4x4(&m_inverseView);
}

XMFLOAT3 Camera::Eye() {
	return m_eye;
}

XMFLOAT3 Camera::LookAt() {
	return m_lookAt;
}

XMFLOAT3 Camera::Up() {
	return m_up;
}

float Camera::NearClipPlane() {
	return m_nearPlane;
}

float Camera::FarClipPlane() {
	return m_farPlane;
}

float Camera::Pitch() {
	return m_cameraPitchAngle;
}

float Camera::Yaw() {
	return m_cameraYawAngle;
}